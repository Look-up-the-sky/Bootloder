#ifndef __MODBUS_H
#define __MODBUS_H
#include "Include.h"


/*Modbus 报文头部*/
typedef __packed struct{
	INT8U ID;
	INT8U func;
}modbus_head_t;

/*读保持寄存器请求 03*/
typedef __packed struct{
	INT8U ID;
	INT8U func;
	INT16U	addr;	/*寄存器地址*/
	INT16U	size;	/*寄存数*/
}modbus_holdreg_r_req;

/*读保持寄存器回复 03*/
typedef struct{
	INT8U ID;
	INT8U func;
	INT8U	bytes;	/*读出字节数*/
}modbus_holdreg_r_ack;

/*写单寄存器请求 06*/
typedef __packed struct{
	INT8U ID;
	INT8U func;
	INT16U	addr;	/*寄存器地址*/
	INT16U	value;	/*寄存器值*/
}modbus_holdreg_ws_req;

/*写单寄存器回复 06*/
typedef  struct{
	INT8U ID;
	INT8U func;
	INT16U	addr;	/*寄存器地址*/
	INT16U	value;	/*寄存器值*/
}modbus_holdreg_ws_ack;

/*写多寄存器请求 10*/
typedef  struct{
	INT8U ID;
	INT8U func;
	INT16U	addr;	/*寄存器地址*/
	INT16U	size;	/*输出数量*/
	INT8U	bytes;	/*字节计数*/
}modbus_holdreg_wm_req;

/*写多寄存器回复 10*/
typedef __packed struct{
	INT8U ID;
	INT8U func;
	INT16U	addr;	/*寄存器地址*/
	INT16U	size;	/*输出数量*/
}modbus_holdreg_wm_ack;

/*错误响应*/
typedef __packed struct{
	INT8U ID;
	INT8U func;
	INT8U  error;	//错误码
}modbus_error_ack;

#define INVALID_FUNC     0x01  //非法功能码
#define INVALID_ADDRESS  0x02  //非法数据地址
#define INVALID_VALUE    0x03  //非法数据值
#define ACCESS_ERR       0x04  //未授权的访问

#define MAX_RCVBUF_LEN   280   //最大接收长度
#define MAX_SENDBUF_LEN  50    //最大发送长度
#define SLAVE_ID         0x01  //通讯地址
#define MIN_ADDRESS  		 0x7000  //最小寄存器地址
#define MAX_ADDRESS  		 0x7029  //最大寄存器地址（不包含代码地址）
#define CRC_LEN  		     2     //CRC长度


extern INT8U Receive_BUF[MAX_RCVBUF_LEN];  //接收数组
extern INT8U Send_BUF[MAX_SENDBUF_LEN];		
extern INT8U  Receive_Finish_Flag;
extern INT16U Receive_Len;  //接收长度
extern INT16U Send_Len;  //发送长度
extern INT8U  Code_BUF[MAX_RCVBUF_LEN];  //程序数组
extern INT8U  Crc_Error_Flag;
extern INT8U  Code_Update_Flag;

void MODBUS_USART1_IRQHandler(void);
void MODBUS_USARTSend(USART_TypeDef* USARTx, INT8U *BufferPtr, INT16U Length);
void Read_03_Handle(INT8U *Send_Buf,INT8U *Error,INT16U *LEN);
//void Write_06_Handle(INT8U *Send_Buf,INT8U *Error,INT16U *LEN);
void Write_10_Handle(INT8U *Send_Buf,INT8U *Error,INT16U *LEN);
void MODBUS_Parsing(void);
#endif
