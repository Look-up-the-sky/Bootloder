#ifndef __INCLUDE_H
#define __INCLUDE_H
#ifdef __cplusplus
extern "C" {
#endif


/*********************************************************************************************************
  通用数据类型重定义
*********************************************************************************************************/
typedef unsigned char       BOOLEAN;                                    /* 布尔变量                     */
typedef unsigned char       INT8U;                                      /* 无符号8位整型变量            */
typedef signed   char       INT8S;                                      /* 有符号8位整型变量            */
typedef unsigned short      INT16U;                                     /* 无符号16位整型变量           */
typedef signed   short      INT16S;                                     /* 有符号16位整型变量           */
typedef unsigned long       INT32U;                                     /* 无符号32位整型变量           */
typedef signed   long       INT32S;                                     /* 有符号32位整型变量           */
typedef unsigned long long  INT64U;                                     /* 无符号64位整型变量           */
typedef signed long long    INT64S;                                     /* 有符号64位整型变量           */
typedef float               FP32;                                       /* 单精度浮点数（32位长度）     */
typedef double              FP64;                                       /* 双精度浮点数（64位长度）     */

typedef unsigned char       uint8;                                      /* 无符号8位整型变量            */
typedef unsigned short int  uint16;                                     /* 无符号16位整型变量           */
typedef unsigned int   			uint32;                                     /* 无符号32位整型变量           */

typedef char                int8;                                       /* 有符号8位整型变量            */
typedef short int           int16;                                      /* 有符号16位整型变量           */
typedef int                 int32;                                      /* 有符号32位整型变量           */

typedef volatile int8       vint8;                                      /*  8 bits                      */
typedef volatile int16      vint16;                                     /* 16 bits                      */
typedef volatile int32      vint32;                                     /* 32 bits                      */

typedef volatile uint8      vuint8;                                     /*  8 bits                      */
typedef volatile uint16     vuint16;                                    /* 16 bits                      */
typedef volatile uint32     vuint32;                                    /* 32 bits                      */

/*********************************************************************************************************
  Standard header files 标准头文件
*********************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
/*********************************************************************************************************
  Common's header files  公共头文件 
*********************************************************************************************************/
#include "stm32f0xx.h"
/*********************************************************************************************************
  Core's header files   内核头文件 
*********************************************************************************************************/
#include <core_cm0.h>                                                   /* CMSIS File of Cortex-M3      */
/*********************************************************************************************************
  Driver's header files  驱动头文件 
*********************************************************************************************************/
#include "stm32f0xx_conf.h"

/*********************************************************************************************************
  User's header files 用户头文件
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
