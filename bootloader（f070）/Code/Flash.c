#include "Flash.h"
/***************************************************************
*��    Ȩ������ŷķ�������Դ�Ƽ����޹�˾�����
*�ļ����ƣ�Flash.c
*�޸��ˣ�����ǿ
*�޸����ڣ�2019.06.20
*��    ����Flash���ܺ���
***************************************************************/
/***************����1�ɹ�������0 ʧ��******************/
INT8U Flash_Update(void)
{
	INT8U i;
	INT8U Code_Temp_Buf[MAX_DATA_LEN];
	INT32U Flash_Buf[MAX_WORD_LEN];
	INT32U Data;
	INT32U FlashAdr;
	INT16U Cur_PKG_Len;
	FLASH_Status status = FLASH_COMPLETE;
	if(PKG_Cnt != 0)
	{		
		FlashAdr = APP_FLASH_ADDRESS+(PKG_Cnt-1)*MAX_DATA_LEN;
		memcpy(&Cur_PKG_Len,&Code_BUF[6],2);
		memcpy(Code_Temp_Buf,&Code_BUF[8],__REV16(Cur_PKG_Len));
		if(__REV16(Cur_PKG_Len) < MAX_DATA_LEN)
		{
			for(i = __REV16(Cur_PKG_Len); i < 236; i++)
			{
				Code_Temp_Buf[i] = 0xFF;
			}
			
		}
		memcpy(Flash_Buf,Code_Temp_Buf,MAX_DATA_LEN);
		
		for(i = 0; i < 59; i++)
		{
			Data = Flash_Buf[i];
			status = FLASH_ProgramWord(FlashAdr,Data);			
			if(status == FLASH_COMPLETE)
			{
				FlashAdr += 4;
			}
			else
			{
				return 0;
			}
		}		
	}
	return 1;
}

INT8U Flash_Erase(void)
{
		INT8U i;
		INT32U FlashAdr;
		FLASH_Status status = FLASH_COMPLETE;
		/* Clear All pending flags */
		FLASH_ClearFlag( FLASH_FLAG_BSY|FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGERR);
		FLASH_Unlock();
		FlashAdr = APP_FLASH_ADDRESS;
			for(i = 0;i < 117;i++)
			{
				status = FLASH_ErasePage(FlashAdr);
				if(status == FLASH_COMPLETE)
				{
					FlashAdr += 1024;
				}
				else
				{
					return 0;
				}
			}
		return 1;
}

