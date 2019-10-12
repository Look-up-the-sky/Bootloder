#include "Jump_to_app.h"
/***************************************************************
*版    权：苏州欧姆尼克新能源科技有限公司软件组
*文件名称：Jump_to_app.c
*修改人：沈仕强
*修改日期：2019.06.20
*描    述：跳转主程序函数
***************************************************************/

void (*pIapFun)(void);


//跳转到应用程序段
//appxaddr:用户代码起始地址.
void Jump(void)
{
	INT32U IapSpInitVal;
	INT32U IapJumpAddr;	
	IapSpInitVal = *(INT32U *)APP_FLASH_ADDRESS;
	IapJumpAddr = *(INT32U *)(APP_FLASH_ADDRESS + 4);

	if((IapSpInitVal & 0x2FFE0000)==0x20000000)//检查栈顶地址是否合法.
	{
		__set_PRIMASK(1);
		__set_MSP (IapSpInitVal);
		pIapFun = (void (*)(void))IapJumpAddr;
		(*pIapFun) ();
	}

}

