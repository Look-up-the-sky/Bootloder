#include "Include.h"
/***************************************************************
*��    Ȩ������ŷķ�������Դ�Ƽ����޹�˾�����
*�ļ����ƣ�main.c
*�޸��ˣ�����ǿ
*�޸����ڣ�2019.06.20
*��    ����������
*�汾V1.0 ����
*�汾v1.1 �޸Ĵ���2Ϊ����1 
***************************************************************/
int main(void)
{

	if((*(INT32U*)FLAG_FLASH_ADDRESS) == APP_TO_BOOT)
	{
		Iap_Update_Req_Flag = 1;
	}
	else if ((*(INT32U*)FLAG_FLASH_ADDRESS) == BOOT_TO_APP)
	{
		Jump();	
	}	
	else
	{
		Iap_Update_Req_Flag = 1;
	}
	GPIO_Configuration();
	TIM16_Configuration();
	Usart_Configuration(9600);
	sInitDisplay();
	while(1)
	{
		Iap_Status_Check();
		MODBUS_Parsing();
		Iap_Update();
	}
}
