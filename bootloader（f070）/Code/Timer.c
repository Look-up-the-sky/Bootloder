#include "Timer.h"
/***************************************************************
*版    权：苏州欧姆尼克新能源科技有限公司软件组
*文件名称：Timer.c
*修改人：沈仕强
*修改日期：2019.06.20
*描    述：定时器
***************************************************************/
INT32U Cnt_1ms = 0;
INT32U Cnt_1ms_T = 0;
INT32U Cnt_1MS_tt = 0;
void TIM16_Configuration(void)								//1ms定时
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	/* Enable the TIM16 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM16_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* TIM16 DeInit */
	TIM_DeInit(TIM16);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	
	TIM_TimeBaseStructure.TIM_Period = 100 - 1;									//10us * 100 = 1ms
	TIM_TimeBaseStructure.TIM_Prescaler = 480 - 1;							//48MHz/480 = 0.1MHz 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM16, &TIM_TimeBaseStructure);
	/* clear overflow interrupt flag*/
	TIM_ClearFlag(TIM16,TIM_FLAG_Update);
	/* TIM Interrupts enable */
	TIM_ITConfig(TIM16,TIM_IT_Update, ENABLE);
	/* TIM16 enable counter */
	TIM_Cmd(TIM16, ENABLE);	
}


void TIM16_IRQHandler(void)				//定时中断 1MS
{

	if(TIM_GetITStatus(TIM16,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM16,TIM_FLAG_Update);
		
	}
	Cnt_1MS_tt++;
	if(Cnt_1MS_tt < 1000)
		GPIO_SetBits(GPIOB,GPIO_Pin_3);
	if(Cnt_1MS_tt > 1000)	
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);

	if(Cnt_1MS_tt > 2000)
		Cnt_1MS_tt = 0;
	Cnt_1ms++;
	Cnt_1ms_T++;

}
