#include "Jump_to_app.h"
/***************************************************************
*��    Ȩ������ŷķ�������Դ�Ƽ����޹�˾�����
*�ļ����ƣ�Jump_to_app.c
*�޸��ˣ�����ǿ
*�޸����ڣ�2019.06.20
*��    ������ת��������
***************************************************************/

void (*pIapFun)(void);


//��ת��Ӧ�ó����
//appxaddr:�û�������ʼ��ַ.
void Jump(void)
{
	INT32U IapSpInitVal;
	INT32U IapJumpAddr;	
	IapSpInitVal = *(INT32U *)APP_FLASH_ADDRESS;
	IapJumpAddr = *(INT32U *)(APP_FLASH_ADDRESS + 4);

	if((IapSpInitVal & 0x2FFE0000)==0x20000000)//���ջ����ַ�Ƿ�Ϸ�.
	{
		__set_PRIMASK(1);
		__set_MSP (IapSpInitVal);
		pIapFun = (void (*)(void))IapJumpAddr;
		(*pIapFun) ();
	}

}

