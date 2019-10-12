#include "Display.h"
/***************************************************************
*版    权：苏州欧姆尼克新能源科技有限公司软件组
*文件名称：Display.c
*修改人：沈仕强
*修改日期：2019.06.20
*描    述：屏幕显示
***************************************************************/
INT8U lubScreenBuf[cMaxLine][cMaxRow];
const INT8U lubLCMINTable[4] = {0x38,0x08,0x06,0x0C};
const INT8U lubLCDAdr[4] = {0x00,0x40,0x14,0x54};

/*****************************************************************************
 * 函数名称：延时函数
 * 函数输入：循环次数
 * 函数返回值：无
 * 函数描述：无
 ****************************************************************************/
void sDelay(INT16U i)
{
	while(i)
	{
		i--;
	}
}

/*****************************************************************************
 * 函数名称：LCD空闲判断函数
 * 函数输入：无
 * 函数返回值：LCD忙标志位
 * 函数描述：返回1表示LCD忙，返回0表示LCD空闲
 ****************************************************************************/
INT8U sGetLCDState(void)
{
	INT8U lubBusyFlag;
	
	cLCMRSOff();
	cLCMRWOn();
	sDelay(4);
	LCDOUT(0xff);
	GPIOC->MODER = 0x00000000;													//设为输入
	cLCMENOn();
	sDelay(4);
	lubBusyFlag = GPIO_ReadInputData(GPIOC);									//读取状态
	GPIOC->MODER = 0x55550000;													//设为输出
	cLCMENOff();
	sDelay(4);
	return(lubBusyFlag & 0x8000);
}

/*****************************************************************************
 * 函数名称：写LCD数据函数
 * 函数输入：数据，指令
 * 函数返回值：无
 * 函数描述：
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
 * 函数名称：显示缓存设置函数
 * 函数输入：行数，列数，长度，待设置数据
 * 函数返回值：无
 * 函数描述：
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
 * 函数名称：显示初始化函数
 * 函数输入：无
 * 函数返回值：无
 * 函数描述：
 ****************************************************************************/
void sInitDisplay(void)
{
	INT8U i,j;
	
	/***************初始化显示缓存***************/
	for(i = 0;i < 4;i++)
	{
		for(j = 0;j < 20;j++)
		{
			lubScreenBuf[i][j] = 0x20;
		}
	}
	
	/***************初始化显示界面***************/
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
