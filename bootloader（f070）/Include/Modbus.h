#ifndef __MODBUS_H
#define __MODBUS_H
#include "Include.h"


/*Modbus ����ͷ��*/
typedef __packed struct{
	INT8U ID;
	INT8U func;
}modbus_head_t;

/*�����ּĴ������� 03*/
typedef __packed struct{
	INT8U ID;
	INT8U func;
	INT16U	addr;	/*�Ĵ�����ַ*/
	INT16U	size;	/*�Ĵ���*/
}modbus_holdreg_r_req;

/*�����ּĴ����ظ� 03*/
typedef struct{
	INT8U ID;
	INT8U func;
	INT8U	bytes;	/*�����ֽ���*/
}modbus_holdreg_r_ack;

/*д���Ĵ������� 06*/
typedef __packed struct{
	INT8U ID;
	INT8U func;
	INT16U	addr;	/*�Ĵ�����ַ*/
	INT16U	value;	/*�Ĵ���ֵ*/
}modbus_holdreg_ws_req;

/*д���Ĵ����ظ� 06*/
typedef  struct{
	INT8U ID;
	INT8U func;
	INT16U	addr;	/*�Ĵ�����ַ*/
	INT16U	value;	/*�Ĵ���ֵ*/
}modbus_holdreg_ws_ack;

/*д��Ĵ������� 10*/
typedef  struct{
	INT8U ID;
	INT8U func;
	INT16U	addr;	/*�Ĵ�����ַ*/
	INT16U	size;	/*�������*/
	INT8U	bytes;	/*�ֽڼ���*/
}modbus_holdreg_wm_req;

/*д��Ĵ����ظ� 10*/
typedef __packed struct{
	INT8U ID;
	INT8U func;
	INT16U	addr;	/*�Ĵ�����ַ*/
	INT16U	size;	/*�������*/
}modbus_holdreg_wm_ack;

/*������Ӧ*/
typedef __packed struct{
	INT8U ID;
	INT8U func;
	INT8U  error;	//������
}modbus_error_ack;

#define INVALID_FUNC     0x01  //�Ƿ�������
#define INVALID_ADDRESS  0x02  //�Ƿ����ݵ�ַ
#define INVALID_VALUE    0x03  //�Ƿ�����ֵ
#define ACCESS_ERR       0x04  //δ��Ȩ�ķ���

#define MAX_RCVBUF_LEN   280   //�����ճ���
#define MAX_SENDBUF_LEN  50    //����ͳ���
#define SLAVE_ID         0x01  //ͨѶ��ַ
#define MIN_ADDRESS  		 0x7000  //��С�Ĵ�����ַ
#define MAX_ADDRESS  		 0x7029  //���Ĵ�����ַ�������������ַ��
#define CRC_LEN  		     2     //CRC����


extern INT8U Receive_BUF[MAX_RCVBUF_LEN];  //��������
extern INT8U Send_BUF[MAX_SENDBUF_LEN];		
extern INT8U  Receive_Finish_Flag;
extern INT16U Receive_Len;  //���ճ���
extern INT16U Send_Len;  //���ͳ���
extern INT8U  Code_BUF[MAX_RCVBUF_LEN];  //��������
extern INT8U  Crc_Error_Flag;
extern INT8U  Code_Update_Flag;

void MODBUS_USART1_IRQHandler(void);
void MODBUS_USARTSend(USART_TypeDef* USARTx, INT8U *BufferPtr, INT16U Length);
void Read_03_Handle(INT8U *Send_Buf,INT8U *Error,INT16U *LEN);
//void Write_06_Handle(INT8U *Send_Buf,INT8U *Error,INT16U *LEN);
void Write_10_Handle(INT8U *Send_Buf,INT8U *Error,INT16U *LEN);
void MODBUS_Parsing(void);
#endif
