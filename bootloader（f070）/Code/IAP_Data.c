#include "IAP_Data.h"
/***************************************************************
*��    Ȩ������ŷķ�������Դ�Ƽ����޹�˾�����
*�ļ����ƣ�IAP_Data.c
*�޸��ˣ�����ǿ
*�޸����ڣ�2019.06.20
*��    ����IAP��������
***************************************************************/
INT8U  Iap_Update_Req_Flag = 0; //��������
INT8U  Flash_Erase_Flag = 0; 
INT8U  Iap_Enable_Flag = 0; //Iapʹ��
INT8U  Iap_Start_Flag = 0; //Iap����
INT8U  Iap_Password_Flag = 0; //Iap����
INT8U  Iap_Baud_1152_Flag = 0; //������115200
INT8U  Iap_File_Info_Flag = 0; //�ļ���Ϣ�������
INT8U  Iap_Update_Flag = 0; //����������
INT8U  Flash_Boot_To_App = 0; 


INT16U IAP_Enable[2];
INT16U IAP_Status;
INT16U IAP_Fault;
INT16U IAP_Baud ;
INT16U IAP_Com;
INT16U IAP_Password[4];
INT16U MCU_Model;
INT16U Software_Version[16];
INT16U File_Check_Val[2];
INT16U File_Length[2];
INT16U PKG_Length = 0;
INT16U PKG_Sum = 0;
INT16U PKG_Cnt = 0;
INT16U Reserved;

const PARAM_CFG_TBL_STR g_astrParamCfgTblAttr[PARAM_NUM]=
{
//**********************ͨѶ����**************************
 {0x7000,&IAP_Enable[0]},
 {0x7001,&IAP_Enable[1]},
 {0x7002,&Reserved},
 {0x7003,&Reserved},
 {0x7004,&Reserved},
 {0x7005,&Reserved},
 {0x7006,&IAP_Status},
 {0x7007,&IAP_Fault},
 {0x7008,&IAP_Baud},
 {0x7009,&IAP_Com},
 {0x700A,&IAP_Password[0]},
 {0x700B,&IAP_Password[1]},
 {0x700C,&IAP_Password[2]},
 {0x700D,&IAP_Password[3]},
 {0x700E,&MCU_Model},
 {0x700F,&Reserved},
 {0x7010,&Reserved},
 {0x7011,&Reserved},
 {0x7012,&Software_Version[0]},
 {0x7013,&Software_Version[1]},
 {0x7014,&Software_Version[2]},
 {0x7015,&Software_Version[3]},
 {0x7016,&Software_Version[4]},
 {0x7017,&Software_Version[5]},
 {0x7018,&Software_Version[6]},
 {0x7019,&Software_Version[7]},
 {0x701A,&Software_Version[8]},
 {0x701B,&Software_Version[9]},
 {0x701C,&Software_Version[10]},
 {0x701D,&Software_Version[11]},
 {0x701E,&Software_Version[12]},
 {0x701F,&Software_Version[13]},
 {0x7020,&Software_Version[14]},
 {0x7021,&Software_Version[15]},
 {0x7022,&File_Check_Val[0]},
 {0x7023,&File_Check_Val[1]},
 {0x7024,&File_Length[0]},
 {0x7025,&File_Length[1]},
 {0x7026,&PKG_Length},
 {0x7027,&PKG_Sum},
 {0x7028,&PKG_Cnt} 
};

void Iap_Status_Check()
{
	if(((IAP_Enable[0]>>8) != 0x49)||((IAP_Enable[0]&0xFF) != 0x41)  //�ж�IAPE��Ȩ
		||((IAP_Enable[1]>>8) != 0x50)||((IAP_Enable[1]&0xFF) != 0x45))
	{
		Iap_Enable_Flag = 0;
	}
	else
	{
		Iap_Enable_Flag = 1;
	}
	if(IAP_Com == 0xAAAA)   //�ж�IAP��������
	{
		Iap_Start_Flag = 1;
	}
	else
	{
		Iap_Start_Flag = 0;
	}
	if(((IAP_Password[0]>>8) != 0x45)||((IAP_Password[0]&0xFF) != 0x41)  //�ж�IAP����
		||((IAP_Password[1]>>8) != 0x53)||((IAP_Password[1]&0xFF) != 0x54)
		||((IAP_Password[2]>>8) != 0x46)||((IAP_Password[2]&0xFF) != 0x49)
		||((IAP_Password[3]>>8) != 0x52)||((IAP_Password[3]&0xFF) != 0x4D))
	{
		Iap_Password_Flag = 0;
	}
	else
	{
		Iap_Password_Flag = 1;
	}
	if((PKG_Length != 0)&&(PKG_Sum != 0))
	{
		Iap_File_Info_Flag = 1;
	}
	else
	{
		Iap_File_Info_Flag = 0;
	}
//	if(IAP_Baud == 1152)  //��������
//	{
//		Iap_Baud_1152_Flag = 1;
//		Usart_Configuration(IAP_Baud*100);
//	}
//	else
//	{
//		Iap_Baud_1152_Flag = 0;
//	}
}


void Iap_Update(void)
{
	static INT16U PKG_Cnt_Temp = 0;
	static INT8U Error_Cnt = 0;
	INT8U State;
	INT16U crc;
	if(Iap_Update_Req_Flag == 1)   //��������
	{
		if(Flash_Erase_Flag == 0)  //Flash����
		{
			State = Flash_Erase();
			if(State == 1)
			{
			 Flash_Erase_Flag = 1;
			}
		}
		if(Flash_Erase_Flag == 1)   //Flash�����ɹ�
		{
			if(Iap_Enable_Flag == 1)   //Iapʹ��
			{
				if(Cnt_1ms_T > 10000)
				{
					Cnt_1ms_T = 0;
					__set_PRIMASK(1);
					NVIC_SystemReset();	 //��λ
				}
					if(Iap_Start_Flag == 1)  //Iap����
					{
						if(Iap_Password_Flag == 1)  //Iap������ȷ
						{
							if(Iap_File_Info_Flag == 1)  //�ļ���Ϣ�������
							{
								
								IAP_Status = IAP_Codeing;
								Iap_Update_Flag = 1;

								if(Iap_Update_Flag == 1)
								{
									if(PKG_Cnt <= PKG_Sum)  
									{
										
										if(PKG_Cnt == PKG_Cnt_Temp)  //��ֹ�ظ���д
										return;
										if(Code_Update_Flag == 1)  //���յ������
										{
											Code_Update_Flag = 0;
											PKG_Cnt_Temp = PKG_Cnt;
											State = Flash_Update(); //����
											if((State == 1)&&(Crc_Error_Flag == 0))   //flash��¼�ɹ���CRCУ������
											{									
												crc = crc16(Send_BUF,Send_Len);
												memcpy(&Send_BUF[Send_Len],&crc,CRC_LEN);
												MODBUS_USARTSend(USART1, Send_BUF, Send_Len+CRC_LEN);
											}
											else    //�ظ�������Ϣ���ٴ���Ҫ�˰�����
											{
												if((State == 0)||(Crc_Error_Flag == 1))  
												{
													Error_Cnt++;
													PKG_Cnt_Temp = 0;
													Crc_Error_Flag = 0;
													Send_BUF[0] = 0x01;
													Send_BUF[1] = 0x90;
													Send_BUF[2] = INVALID_VALUE;
													crc = crc16(Send_BUF,3);
													memcpy(&Send_BUF[3],&crc,CRC_LEN);
													MODBUS_USARTSend(USART1, Send_BUF, 5);
												}
											}
										}
									}
									if(PKG_Cnt == PKG_Sum)  //�������
									{
										IAP_Status = IAP_Update_Succuss;
										Iap_Update_Flag = 0;
										Iap_Update_Req_Flag = 0;
										Cnt_1ms = 0;
									}
							
								}
							}
						}
						else
						{
							IAP_Status = IAP_Update_Fault;
							IAP_Fault = IAP_Password_Err;
						}
					}
					else
					{
						IAP_Status = IAP_Update_Fault;
						IAP_Status = IAP_Ready;
					}
			}
			else
			{
				IAP_Status = IAP_Update_Fault;
				IAP_Fault = IAP_Disable;
			}
		}
	}
	else
	{
		if(Flash_Boot_To_App == 0)
		{
			/* Clear All pending flags */
			FLASH_ClearFlag( FLASH_FLAG_BSY|FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGERR);
			FLASH_Unlock();
			FLASH_ErasePage(FLAG_FLASH_ADDRESS);
			if(FLASH_ProgramWord(FLAG_FLASH_ADDRESS,BOOT_TO_APP) == FLASH_COMPLETE)
			{
				Flash_Boot_To_App = 1;
				FLASH_Lock();
				Cnt_1ms = 0;
			}
		}
		else
		{
			
			if(Cnt_1ms >3000)
			{

				__set_PRIMASK(1);
				NVIC_SystemReset();
			}
		}
		
	}
}

