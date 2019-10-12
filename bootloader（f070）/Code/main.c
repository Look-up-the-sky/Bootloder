#include "Include.h"
/***************************************************************
*版    权：苏州欧姆尼克新能源科技有限公司软件组
*文件名称：main.c
*修改人：沈仕强
*修改日期：2019.06.20
*描    述：主函数
*版本V1.0 创建
*版本v1.1 修改串口2为串口1 
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
