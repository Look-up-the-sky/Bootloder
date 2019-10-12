#include "GPIO.h"
/***************************************************************
*��    Ȩ������ŷķ�������Դ�Ƽ����޹�˾�����
*�ļ����ƣ�Gpio.c
*�޸��ˣ�����ǿ
*�޸����ڣ�2019.06.20
*��    ����IO��ʼ��
***************************************************************/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*Enable GPIOA and GPIOB clock */
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE); 
	/*Enable TIM16 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16 , ENABLE);
	
	/*
	PA0-RW/PA1-RS485DIR1/PA8-RS485DIR0/PA12-SPEAK is for output pushpull
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1); //485����
	GPIO_ResetBits(GPIOA,GPIO_Pin_8); //485����

	/*
	PA4-KEY0/PA5-KEY1/PA6-KEY2/PA7-KEY3 is for input pushpull
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*
	PB0-RS/PB1-RC/PB2-LCMEN/PB3-COMM/PB4-FAULT/PB5-NORMAL is for output pushpull
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Configure PB8/PB9/PB10/PB11/PB12/PB13/PB14/PB15 for LCD data in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | 		//����TL2��Ϊ˫���I/O��st�в�����λ˫��I/O��������ҪΪ����ڵ�ʱ��ı�
								  GPIO_Pin_12 |GPIO_Pin_13 |GPIO_Pin_14 |GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
}

