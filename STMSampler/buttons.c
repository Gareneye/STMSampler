#include "buttons.h"

int blockedEXTI[8] = { 0 };

void configureButtons(void) {

	/*
	 * GPIO
	 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	{
	GPIO_InitTypeDef GPIO_InitButtonsStruct;
	GPIO_InitButtonsStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1  | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitButtonsStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitButtonsStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitButtonsStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitButtonsStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitButtonsStruct);
	}

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	// 0
	{
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		EXTI_InitTypeDef EXTI_InitStructure;
		EXTI_InitStructure.EXTI_Line = EXTI_Line0;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

		SYSCFG_EXTILineConfig(GPIOA, EXTI_PinSource0);
	}


	{
		// timer
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_TimeBaseStructure.TIM_Period = 8399;
		TIM_TimeBaseStructure.TIM_Prescaler = 1999;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

		TIM_Cmd(TIM2, DISABLE);

		// NVIC
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	}


	// 1
	{
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		EXTI_InitTypeDef EXTI_InitStructure;
		EXTI_InitStructure.EXTI_Line = EXTI_Line1;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

		SYSCFG_EXTILineConfig(GPIOA, EXTI_PinSource1);
	}

	{
		// timer
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_TimeBaseStructure.TIM_Period = 8399;
		TIM_TimeBaseStructure.TIM_Prescaler = 1999;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

		TIM_Cmd(TIM3, DISABLE);

		// NVIC
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	}


	// 2
	{
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		EXTI_InitTypeDef EXTI_InitStructure;
		EXTI_InitStructure.EXTI_Line = EXTI_Line2;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

		SYSCFG_EXTILineConfig(GPIOA, EXTI_PinSource2);
	}

	{
		// timer
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_TimeBaseStructure.TIM_Period = 8399;
		TIM_TimeBaseStructure.TIM_Prescaler = 1999;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

		TIM_Cmd(TIM4, DISABLE);

		// NVIC
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	}


	// 3
	{
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		EXTI_InitTypeDef EXTI_InitStructure;
		EXTI_InitStructure.EXTI_Line = EXTI_Line3;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

		SYSCFG_EXTILineConfig(GPIOA, EXTI_PinSource3);
	}

	{
		// timer
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_TimeBaseStructure.TIM_Period = 8399;
		TIM_TimeBaseStructure.TIM_Prescaler = 1999;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

		TIM_Cmd(TIM5, DISABLE);

		// NVIC
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	}

}

/*
 * EXTI
 */

void EXTI0_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {

		if (blockedEXTI[0] == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
			runSample(3);

			blockedEXTI[0] = 1;
			TIM_Cmd(TIM2, ENABLE);
		}

		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line1) != RESET) {

		if (blockedEXTI[1] == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)) {
			runSample(2);

			blockedEXTI[1] = 1;
			TIM_Cmd(TIM3, ENABLE);
		}

		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void EXTI2_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line2) != RESET) {

		if (blockedEXTI[2] == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)) {
			runSample(6);

			blockedEXTI[2] = 1;
			TIM_Cmd(TIM4, ENABLE);
		}

		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}


void EXTI3_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line3) != RESET) {

		if (blockedEXTI[3] == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)) {
			runSample(8);

			blockedEXTI[3] = 1;
			TIM_Cmd(TIM5, ENABLE);
		}

		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

/*
 * TIMERS
 */


void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		blockedEXTI[0] = 0;

		TIM_Cmd(TIM2, DISABLE);
		TIM_SetCounter(TIM2, 0);

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}


void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
		blockedEXTI[1] = 0;

		TIM_Cmd(TIM3, DISABLE);
		TIM_SetCounter(TIM3, 0);

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

void TIM4_IRQHandler(void) {
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
		blockedEXTI[2] = 0;

		TIM_Cmd(TIM4, DISABLE);
		TIM_SetCounter(TIM4, 0);

		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}

void TIM5_IRQHandler(void) {
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) {
		blockedEXTI[3] = 0;

		TIM_Cmd(TIM5, DISABLE);
		TIM_SetCounter(TIM5, 0);

		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
}

