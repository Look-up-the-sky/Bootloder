#include "Modbus.h"
/***************************************************************
*版    权：苏州欧姆尼克新能源科技有限公司软件组
*文件名称：Modbus.c
*修改人：沈仕强
*修改日期：2019.06.20
*描    述：Modbus处理函数
***************************************************************/
#define RS485_DIR1_OUT()	GPIO_SetBits(GPIOA,GPIO_Pin_8) //485方向控制
#define RS485_DIR1_IN()	  GPIO_ResetBits(GPIOA,GPIO_Pin_8)
#define RS485_DIR2_OUT()	GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define RS485_DIR2_IN()	  GPIO_ResetBits(GPIOA,GPIO_Pin_1)
INT8U  Receive_BUF[MAX_RCVBUF_LEN];
INT16U Receive_Len;  //接收长度
INT16U Send_Len;  //发送长度
INT8U  Send_BUF[MAX_SENDBUF_LEN];
INT16U  PusData_BUF[MAX_SENDBUF_LEN];
INT8U  Code_BUF[MAX_RCVBUF_LEN];  //程序数组
INT8U  Receive_Finish_Flag = 0;
INT8U  Receiving_Flag = 0;
INT8U  Crc_Error_Flag = 0;
INT8U  Code_Update_Flag = 0;  //包接收标志位

void MODBUS_USART1_IRQHandler(void)
{
	 if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)        
	   {
			 Receive_BUF[Receive_Len++]=USART_ReceiveData(USART1);
			 USART_ClearITPendingBit(USART1, USART_IT_RXNE);
			 Receiving_Flag = 1;
	   }	 
	 else if((USART_GetFlagStatus(USART1,USART_FLAG_IDLE)!=RESET)&&(Receiving_Flag == 1))
			{					
				USART_ClearFlag(USART1, USART_FLAG_IDLE);						
				Receive_Finish_Flag = 1;
				Receiving_Flag = 0;
				Cnt_1ms_T = 0;   //接收到程序包则超时计时清零
      }	
			else
			{
				USART_ClearFlag(USART1, USART_FLAG_IDLE);	
			}


}
//***********************************发送函数**********************************
void MODBUS_USARTSend(USART_TypeDef* USARTx, INT8U *BufferPtr, INT16U Length)
{
	RS485_DIR1_OUT();
	while ( Length != 0 )
		{
			USART_SendData(USARTx, (unsigned char)*BufferPtr);
			while( USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET);
			BufferPtr++;
			Length--;
		}
	RS485_DIR1_IN();
}


void MODBUS_Parsing(void)
{
	INT8U error = 0;
	INT16U crc,len,Rx_crc;
	modbus_head_t* head;
	modbus_error_ack err_ack;
	if(Receive_Finish_Flag == 1)
	{
		if(Cnt_1ms_T > 2000)     //超时退出，防止死机
		{
			Receive_Finish_Flag = 0;
			return;
		}
		crc =crc16(Receive_BUF,Receive_Len-CRC_LEN);
		memcpy(&Rx_crc,&(Receive_BUF[Receive_Len-CRC_LEN]),CRC_LEN);
		head = (modbus_head_t*)Receive_BUF;
		Receive_Finish_Flag = 0;
		Receive_Len = 0;
		if(head->ID == SLAVE_ID)
		{
			if(crc != Rx_crc)    //crc校验
			{
				error = INVALID_VALUE;	
				Crc_Error_Flag = 1;
			}
			else
			{
				switch(head->func)
				{
					case 0x03:
						Read_03_Handle(Send_BUF,&error,&len);
						break;
					case 0x06:
						//Write_06_Handle(Send_BUF,&error,&len);
						break;
					case 0x10:
						Write_10_Handle(Send_BUF,&error,&len);
						break;
					default:	
						error = INVALID_FUNC;
						break;
				}
			}	
			if(Iap_Update_Flag == 0)  //非升级过程中，升级过程中的包回复放在升级程序中
			{
				if(error != 0)
				{
					err_ack.ID = head->ID;
					err_ack.func = head->func|0x80;
					err_ack.error = error;
					len = sizeof(modbus_error_ack);
					memcpy(Send_BUF,&err_ack,len);
					crc = crc16(Send_BUF,len);
					memcpy(&Send_BUF[len],&crc,CRC_LEN);
					MODBUS_USARTSend(USART1, Send_BUF, len+CRC_LEN);
					Crc_Error_Flag = 0;
				}
				else
				{
					crc = crc16(Send_BUF,len);
					memcpy(&Send_BUF[len],&crc,CRC_LEN);
					MODBUS_USARTSend(USART1, Send_BUF, len+CRC_LEN);
				}		
			}
			else
			{
				Send_Len = len;
			}
		}
	}
}

void Read_03_Handle(INT8U *Send_Buf,INT8U *Error,INT16U *LEN)
{
	INT16U address,length,i;
	modbus_holdreg_r_req* r_req = (modbus_holdreg_r_req*)Receive_BUF;

	if((__REV16(r_req->addr) < MIN_ADDRESS)||((__REV16(r_req->addr)+__REV16(r_req->size)) > MAX_ADDRESS))
	{
		*Error = INVALID_ADDRESS;
		return;
	}
	else
	{
		*Error = 0;			
		address = __REV16(r_req->addr);
		length = __REV16(r_req->size);
		*LEN = length*2;
		CFG_LoadParam(PusData_BUF, address, length);
		for(i = 0;i < length;i++)
		{
			PusData_BUF[i] = __REV16(PusData_BUF[i]);
		}
		Send_Buf[0] = r_req->ID;
		Send_Buf[1] = r_req->func;
		Send_Buf[2] = *LEN;
		memcpy(&Send_Buf[3],PusData_BUF,*LEN);
		*LEN = *LEN+3;
	}
	
	
}

//void Write_06_Handle(INT8U *Send_Buf,INT8U *Error,INT16U *LEN)
//{
//	INT16U address,length;
//	modbus_holdreg_ws_req* ws_req = (modbus_holdreg_ws_req*)Receive_BUF;
//	if(Iap_Enable_Flag == 0)  //判断IAPE授权
//	{
//		*Error = ACCESS_ERR;	
//		return;
//	}	
//	if((__REV16(ws_req->addr) < MIN_ADDRESS)||(__REV16(ws_req->addr) > (MAX_ADDRESS-1)))
//	{
//		*Error = INVALID_ADDRESS;
//		return;
//	}
//	else
//	{
//		*Error = 0;			
//		address = __REV16(ws_req->addr);
//		length = 1;
//		*LEN = 2;
//		memcpy(PusData_BUF,&Receive_BUF[4],*LEN);
//		PusData_BUF[0] = __REV16(PusData_BUF[0]);
//		CFG_ParamCfg(PusData_BUF, address, length);
//		*LEN = *LEN+4;
//		memcpy(Send_Buf,Receive_BUF,*LEN);
//		
//	}
//}

void Write_10_Handle(INT8U *Send_Buf,INT8U *Error,INT16U *LEN)
{
	INT16U address,length,i;
	modbus_holdreg_wm_req* wm_req = (modbus_holdreg_wm_req*)Receive_BUF;
	if(Iap_Enable_Flag == 0)  //判断IAPE授权
	{
		if((__REV16(wm_req->addr) != 0x7000)||(__REV16(wm_req->size) != 2))
		{
		  *Error = ACCESS_ERR;	
			return;
		}
	}	
	if(Iap_Update_Flag == 1)
	{
		if(__REV16(wm_req->addr) < MIN_ADDRESS)
		{
			*Error = INVALID_ADDRESS;
			return;
		}
	}
	else if((__REV16(wm_req->addr) < MIN_ADDRESS)||((__REV16(wm_req->addr)+__REV16(wm_req->size)) > MAX_ADDRESS))
		{
			*Error = INVALID_ADDRESS;
			return;
		}
		
		*Error = 0;			
		address = __REV16(wm_req->addr);
		length = __REV16(wm_req->size);
		*LEN = length*2;
		if(Iap_Update_Flag == 1)
		{
			memcpy(Code_BUF,&Receive_BUF[7],*LEN);
			memcpy(PusData_BUF,&Receive_BUF[7],2);
			PusData_BUF[0] = __REV16(PusData_BUF[0]);
			CFG_ParamCfg( PusData_BUF, address, 1);
			Code_Update_Flag = 1;
		}
		else
		{
			memcpy(PusData_BUF,&Receive_BUF[7],*LEN);
			for(i = 0;i < length;i++)
			{
				PusData_BUF[i] = __REV16(PusData_BUF[i]);
			}	
		CFG_ParamCfg( PusData_BUF, address, length);
		}
		
	
		memcpy(Send_Buf,Receive_BUF,6);
		*LEN = 6;

}
