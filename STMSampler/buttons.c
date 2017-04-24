
#include "buttons.h"

void configureButtons(void) {
	blockedEXTI_0 = 0;

	// gpio config
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitButtonsStruct;
	GPIO_InitButtonsStruct.GPIO_Pin = BUTTONS_PINS;
	GPIO_InitButtonsStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitButtonsStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitButtonsStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitButtonsStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOD, &GPIO_InitButtonsStruct);

	// interrupt config
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	SYSCFG_EXTILineConfig(GPIOA, EXTI_PinSource0);

	// timer
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructureD1;
	TIM_TimeBaseStructureD1.TIM_Period = 8399;
	TIM_TimeBaseStructureD1.TIM_Prescaler = 1999;
	TIM_TimeBaseStructureD1.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructureD1.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructureD1);

	TIM_Cmd(TIM4, DISABLE);

	NVIC_InitTypeDef NVIC_InitStructure2;
	NVIC_InitStructure2.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure2);

	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

}


void EXTI0_IRQHandler(void)
{
         if(EXTI_GetITStatus(EXTI_Line0) != RESET)
         {
        	 if(blockedEXTI_0 == 0)
        	 {
     			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
     			{
     				runSample(createSample(91001));
     			}

     			 blockedEXTI_0= 1;
        		 TIM_Cmd(TIM4, ENABLE);
        	 }

        	 EXTI_ClearITPendingBit(EXTI_Line0);
         }
}


void TIM4_IRQHandler(void)
{
         	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
         	{
         			blockedEXTI_0 = 0;
					TIM_Cmd(TIM4, DISABLE);
					TIM_SetCounter(TIM4, 0);

                	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
         	}
}
