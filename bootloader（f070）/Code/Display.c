#include "Display.h"
/***************************************************************
*��    Ȩ������ŷķ�������Դ�Ƽ����޹�˾�����
*�ļ����ƣ�Display.c
*�޸��ˣ�����ǿ
*�޸����ڣ�2019.06.20
*��    ������Ļ��ʾ
***************************************************************/
INT8U lubScreenBuf[cMaxLine][cMaxRow];
const INT8U lubLCMINTable[4] = {0x38,0x08,0x06,0x0C};
const INT8U lubLCDAdr[4] = {0x00,0x40,0x14,0x54};

/*****************************************************************************
 * �������ƣ���ʱ����
 * �������룺ѭ������
 * ��������ֵ����
 * ������������
 ****************************************************************************/
void sDelay(INT16U i)
{
	while(i)
	{
		i--;
	}
}

/*****************************************************************************
 * �������ƣ�LCD�����жϺ���
 * �������룺��
 * ��������ֵ��LCDæ��־λ
 * ��������������1��ʾLCDæ������0��ʾLCD����
 ****************************************************************************/
INT8U sGetLCDState(void)
{
	INT8U lubBusyFlag;
	
	cLCMRSOff();
	cLCMRWOn();
	sDelay(4);
	LCDOUT(0xff);
	GPIOC->MODER = 0x00000000;													//��Ϊ����
	cLCMENOn();
	sDelay(4);
	lubBusyFlag = GPIO_ReadInputData(GPIOC);									//��ȡ״̬
	GPIOC->MODER = 0x55550000;													//��Ϊ���
	cLCMENOff();
	sDelay(4);
	return(lubBusyFlag & 0x8000);
}

/*****************************************************************************
 * �������ƣ�дLCD���ݺ���
 * �������룺���ݣ�ָ��
 * ��������ֵ����
 * ����������
 ****************************************************************************/
void sWriteLCDData(INT8U lubData,INT8U lubCmd)
{
	if(lubCmd)
	{
		cLCMRSOn();
	}
	else
	{
		cLCMRSOff();
	}
	cLCMRWOff();
	sDelay(70);
	cLCMENOn();
	sDelay(90);
	LCDOUT(lubData);
	sDelay(90);
	cLCMENOff();
	sDelay(70);
}

/*****************************************************************************
 * �������ƣ���ʾ�������ú���
 * �������룺���������������ȣ�����������
 * ��������ֵ����
 * ����������
 ****************************************************************************/
void sWriteScreenBuf(INT8U lubLine,INT8U lubRow,INT8U lubLength,INT8U *lubDataAdr)
{
	INT8U i;
	
	if(lubLine < cMaxLine)
	{
		for(i = lubRow;(i < cMaxRow) && (i < lubRow + lubLength) && (*lubDataAdr != '\0');i++)
		{
			lubScreenBuf[lubLine][i] = *lubDataAdr;
			lubDataAdr++;
		}
	}
}

void sWriteLCDAdr(INT8U lubLCDAdr)
{
	while(sGetLCDState());
	sWriteLCDData(0x80 | lubLCDAdr,0);
}

void sUpdateLCD(void)
{
	INT8U lubLine;
	INT8U lubRow;
	
	for(lubLine = 0;lubLine < cMaxLine;lubLine++)
	{
		for(lubRow = 0;lubRow < cMaxRow;lubRow++)
		{
			sWriteLCDAdr(lubLCDAdr[lubLine] + lubRow);
			while(sGetLCDState());
			sWriteLCDData(lubScreenBuf[lubLine][lubRow],1);
		}
	}
}

/*****************************************************************************
 * �������ƣ���ʾ��ʼ������
 * �������룺��
 * ��������ֵ����
 * ����������
 ****************************************************************************/
void sInitDisplay(void)
{
	INT8U i,j;
	
	/***************��ʼ����ʾ����***************/
	for(i = 0;i < 4;i++)
	{
		for(j = 0;j < 20;j++)
		{
			lubScreenBuf[i][j] = 0x20;
		}
	}
	
	/***************��ʼ����ʾ����***************/
	sWriteLCDData(0x38,0);
	sDelay(0x0F);
	sWriteLCDData(0x38,0);
	sDelay(0x0F);
	sWriteLCDData(0x38,0);
	sDelay(0x0F);
	for(i = 0;i < 4;i++)
	{
		while(sGetLCDState());
		sWriteLCDData(lubLCMINTable[i],0);
	}
	sWriteScreenBuf(1,0,20,"    Updataing...    ");
	sUpdateLCD();
}
