#ifndef __INCLUDE_H
#define __INCLUDE_H
#ifdef __cplusplus
extern "C" {
#endif


/*********************************************************************************************************
  ͨ�����������ض���
*********************************************************************************************************/
typedef unsigned char       BOOLEAN;                                    /* ��������                     */
typedef unsigned char       INT8U;                                      /* �޷���8λ���ͱ���            */
typedef signed   char       INT8S;                                      /* �з���8λ���ͱ���            */
typedef unsigned short      INT16U;                                     /* �޷���16λ���ͱ���           */
typedef signed   short      INT16S;                                     /* �з���16λ���ͱ���           */
typedef unsigned long       INT32U;                                     /* �޷���32λ���ͱ���           */
typedef signed   long       INT32S;                                     /* �з���32λ���ͱ���           */
typedef unsigned long long  INT64U;                                     /* �޷���64λ���ͱ���           */
typedef signed long long    INT64S;                                     /* �з���64λ���ͱ���           */
typedef float               FP32;                                       /* �����ȸ�������32λ���ȣ�     */
typedef double              FP64;                                       /* ˫���ȸ�������64λ���ȣ�     */

typedef unsigned char       uint8;                                      /* �޷���8λ���ͱ���            */
typedef unsigned short int  uint16;                                     /* �޷���16λ���ͱ���           */
typedef unsigned int   			uint32;                                     /* �޷���32λ���ͱ���           */

typedef char                int8;                                       /* �з���8λ���ͱ���            */
typedef short int           int16;                                      /* �з���16λ���ͱ���           */
typedef int                 int32;                                      /* �з���32λ���ͱ���           */

typedef volatile int8       vint8;                                      /*  8 bits                      */
typedef volatile int16      vint16;                                     /* 16 bits                      */
typedef volatile int32      vint32;                                     /* 32 bits                      */

typedef volatile uint8      vuint8;                                     /*  8 bits                      */
typedef volatile uint16     vuint16;                                    /* 16 bits                      */
typedef volatile uint32     vuint32;                                    /* 32 bits                      */

/*********************************************************************************************************
  Standard header files ��׼ͷ�ļ�
*********************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
/*********************************************************************************************************
  Common's header files  ����ͷ�ļ� 
*********************************************************************************************************/
#include "stm32f0xx.h"
/*********************************************************************************************************
  Core's header files   �ں�ͷ�ļ� 
*********************************************************************************************************/
#include <core_cm0.h>                                                   /* CMSIS File of Cortex-M3      */
/*********************************************************************************************************
  Driver's header files  ����ͷ�ļ� 
*********************************************************************************************************/
#include "stm32f0xx_conf.h"

/*********************************************************************************************************
  User's header files �û�ͷ�ļ�
*********************************************************************************************************/
#include "GPIO.h"
#include "Flash.h"
#include "Usart.h"
#include "Jump_to_app.h"
#include "Check.h"
#include "Modbus.h"
#include "config.h"
#include "IAP_Data.h"
#include "Timer.h"
#include "Display.h"
/*********************************************************************************************************
  Globle 
*********************************************************************************************************/



#ifdef __cplusplus
}
#endif


#endif
