#ifndef __DISPALY_H
#define __DISPALY_H
#include "Include.h"

#define cMaxLine	     4
#define cMaxRow	       20

#define cLCMENOn()	GPIO_SetBits(GPIOB,GPIO_Pin_2)
#define cLCMENOff()	GPIO_ResetBits(GPIOB,GPIO_Pin_2)
#define cLCMRWOn()	GPIO_SetBits(GPIOA,GPIO_Pin_0)
#define cLCMRWOff()	GPIO_ResetBits(GPIOA,GPIO_Pin_0)
#define cLCMRSOn()	GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define cLCMRSOff()	GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define cLCMAOn()		GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define cLCMAOff()	GPIO_ResetBits(GPIOB,GPIO_Pin_1)
#define	LCDOUT(x)		GPIOB->ODR = ((GPIOB->ODR & 0x00ff) | ((INT8U)(x) << 8))


INT8U sGetLCDState(void);
void sWriteLCDData(INT8U lubData,INT8U lubCmd);
void sWriteScreenBuf(INT8U lubLine,INT8U lubRow,INT8U lubLength,INT8U *lubDataAdr);
void sWriteLCDAdr(INT8U lubLCDAdr);
void sUpdateLCD(void);
void sInitDisplay(void);
#endif
