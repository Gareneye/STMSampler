#include "buttons.h"

void configureButtons(void) {
    int i;
    for(i = 0; i<8; i++)
    {
    	blockedEXTI[i] = 1;
    }
    blockedEXTI[0] = 0;

	/*
	 * GPIO
	 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitButtonsStruct;
	GPIO_InitButtonsStruct.GPIO_Pin = BUTTONS_PINS;
	GPIO_InitButtonsStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitButtonsStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitButtonsStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitButtonsStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOD, &GPIO_InitButtonsStruct);

	/*
	 * EXTI
	 */

	//
	// [ PIN 1 ]
	//

	// interrupt config
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

	// 4
	{
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		EXTI_InitTypeDef EXTI_InitStructure;
		EXTI_InitStructure.EXTI_Line = EXTI_Line4;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

		SYSCFG_EXTILineConfig(GPIOA, EXTI_PinSource4);
	}

	// 5
	{
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		EXTI_InitTypeDef EXTI_InitStructure;
		EXTI_InitStructure.EXTI_Line = EXTI_Line5;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

		SYSCFG_EXTILineConfig(GPIOA, EXTI_PinSource5);
	}

	// 6
	{
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		EXTI_InitTypeDef EXTI_InitStructure;
		EXTI_InitStructure.EXTI_Line = EXTI_Line6;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

		SYSCFG_EXTILineConfig(GPIOA, EXTI_PinSource6);
	}

	// 7
	{
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		EXTI_InitTypeDef EXTI_InitStructure;
		EXTI_InitStructure.EXTI_Line = EXTI_Line7;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

		SYSCFG_EXTILineConfig(GPIOA, EXTI_PinSource7);
	}

	/*
	 * TIMERS
	 */

	//
	// [TIM2]
	//
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

	//
	// [TIM3]
	//

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

	//
	// [TIM4]
	//

	{
		// timer
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructureD1;
		TIM_TimeBaseStructureD1.TIM_Period = 8399;
		TIM_TimeBaseStructureD1.TIM_Prescaler = 1999;
		TIM_TimeBaseStructureD1.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructureD1.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructureD1);

		TIM_Cmd(TIM4, DISABLE);

		// NVIC
		NVIC_InitTypeDef NVIC_InitStructure2;
		NVIC_InitStructure2.NVIC_IRQChannel = TIM4_IRQn;
		NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure2);

		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	}

	//
	// [TIM5]
	//

	{
		// timer
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructureD1;
		TIM_TimeBaseStructureD1.TIM_Period = 8399;
		TIM_TimeBaseStructureD1.TIM_Prescaler = 1999;
		TIM_TimeBaseStructureD1.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructureD1.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructureD1);

		TIM_Cmd(TIM5, DISABLE);

		// NVIC
		NVIC_InitTypeDef NVIC_InitStructure2;
		NVIC_InitStructure2.NVIC_IRQChannel = TIM5_IRQn;
		NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure2);

		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	}

	//
	// [TIM9]
	//

	{
		// timer
		RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);

		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructureD1;
		TIM_TimeBaseStructureD1.TIM_Period = 8399;
		TIM_TimeBaseStructureD1.TIM_Prescaler = 1999;
		TIM_TimeBaseStructureD1.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructureD1.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructureD1);

		TIM_Cmd(TIM9, DISABLE);

		// NVIC
		NVIC_InitTypeDef NVIC_InitStructure2;
		NVIC_InitStructure2.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn;
		NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure2);

		TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
		TIM_ITConfig(TIM9, TIM_IT_Update, ENABLE);
	}

	//
	// [TIM10]
	//

	{
		// timer
		RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);

		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructureD1;
		TIM_TimeBaseStructureD1.TIM_Period = 8399;
		TIM_TimeBaseStructureD1.TIM_Prescaler = 1999;
		TIM_TimeBaseStructureD1.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructureD1.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM10, &TIM_TimeBaseStructureD1);

		TIM_Cmd(TIM10, DISABLE);

		// NVIC
		NVIC_InitTypeDef NVIC_InitStructure2;
		NVIC_InitStructure2.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
		NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure2);

		TIM_ClearITPendingBit(TIM10, TIM_IT_Update);
		TIM_ITConfig(TIM10, TIM_IT_Update, ENABLE);
	}

	//
	// [TIM11]
	//

	{
		// timer
		RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);

		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructureD1;
		TIM_TimeBaseStructureD1.TIM_Period = 8399;
		TIM_TimeBaseStructureD1.TIM_Prescaler = 1999;
		TIM_TimeBaseStructureD1.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructureD1.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM11, &TIM_TimeBaseStructureD1);

		TIM_Cmd(TIM11, DISABLE);

		// NVIC
		NVIC_InitTypeDef NVIC_InitStructure2;
		NVIC_InitStructure2.NVIC_IRQChannel = TIM1_TRG_COM_TIM11_IRQn;
		NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure2);

		TIM_ClearITPendingBit(TIM11, TIM_IT_Update);
		TIM_ITConfig(TIM11, TIM_IT_Update, ENABLE);
	}


	//
	// [TIM12]
	//

	{
		// timer
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);

		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructureD1;
		TIM_TimeBaseStructureD1.TIM_Period = 8399;
		TIM_TimeBaseStructureD1.TIM_Prescaler = 1999;
		TIM_TimeBaseStructureD1.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructureD1.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM11, &TIM_TimeBaseStructureD1);

		TIM_Cmd(TIM12, DISABLE);

		// NVIC
		NVIC_InitTypeDef NVIC_InitStructure2;
		NVIC_InitStructure2.NVIC_IRQChannel = TIM8_BRK_TIM12_IRQn;
		NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure2);

		TIM_ClearITPendingBit(TIM12, TIM_IT_Update);
		TIM_ITConfig(TIM12, TIM_IT_Update, ENABLE);
	}

}

/*
 * EXTI
 */

void EXTI0_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {

		if (blockedEXTI[0] == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
			runSample(createSample(1));

			blockedEXTI[0] = 1;
			TIM_Cmd(TIM2, ENABLE);
		}

		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line1) != RESET) {

		if (blockedEXTI[1] == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)) {
			runSample(createSample(2));

			blockedEXTI[1] = 1;
			TIM_Cmd(TIM3, ENABLE);
		}

		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void EXTI2_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line2) != RESET) {

		if (blockedEXTI[2] == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)) {
			runSample(createSample(3));

			blockedEXTI[2] = 1;
			TIM_Cmd(TIM4, ENABLE);
		}

		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

void EXTI3_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line3) != RESET) {

		if (blockedEXTI[3] == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)) {
			runSample(createSample(4));

			blockedEXTI[3] = 1;
			TIM_Cmd(TIM5, ENABLE);
		}

		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

void EXTI4_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line4) != RESET) {

		if (blockedEXTI[4] == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)) {
			runSample(createSample(5));

			blockedEXTI[4] = 1;
			TIM_Cmd(TIM9, ENABLE);
		}

		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}


void EXTI9_5_IRQHandler(void) {
	// 5
	if (EXTI_GetITStatus(EXTI_Line5) != RESET) {

		if (blockedEXTI[5] == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)) {
			runSample(createSample(6));

			blockedEXTI[5] = 1;
			TIM_Cmd(TIM10, ENABLE);
		}

		EXTI_ClearITPendingBit(EXTI_Line5);
	}

	// 6
	if (EXTI_GetITStatus(EXTI_Line6) != RESET) {

		if (blockedEXTI[6] == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)) {
			runSample(createSample(7));

			blockedEXTI[6] = 1;
			TIM_Cmd(TIM11, ENABLE);
		}

		EXTI_ClearITPendingBit(EXTI_Line6);
	}

	// 7
	if (EXTI_GetITStatus(EXTI_Line7) != RESET) {

		if (blockedEXTI[7] == 0 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)) {
			runSample(createSample(8));

			blockedEXTI[7] = 1;
			TIM_Cmd(TIM12, ENABLE);
		}

		EXTI_ClearITPendingBit(EXTI_Line7);
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
		blockedEXTI[2] = 0;

		TIM_Cmd(TIM5, DISABLE);
		TIM_SetCounter(TIM5, 0);

		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
}

void TIM1_BRK_TIM9_IRQHandler(void) {
	if (TIM_GetITStatus(TIM9, TIM_IT_Update) != RESET) {
		blockedEXTI[3] = 0;

		TIM_Cmd(TIM9, DISABLE);
		TIM_SetCounter(TIM9, 0);

		TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
	}
}

void TIM1_UP_TIM10_IRQHandler(void) {
	if (TIM_GetITStatus(TIM10, TIM_IT_Update) != RESET) {
		blockedEXTI[4] = 0;

		TIM_Cmd(TIM10, DISABLE);
		TIM_SetCounter(TIM10, 0);

		TIM_ClearITPendingBit(TIM10, TIM_IT_Update);
	}
}

void TIM1_TRG_COM_TIM11_IRQHandler(void) {
	if (TIM_GetITStatus(TIM11, TIM_IT_Update) != RESET) {
		blockedEXTI[5] = 0;

		TIM_Cmd(TIM11, DISABLE);
		TIM_SetCounter(TIM11, 0);

		TIM_ClearITPendingBit(TIM11, TIM_IT_Update);
	}
}

void TIM8_BRK_TIM12_IRQHandler(void) {
	if (TIM_GetITStatus(TIM12, TIM_IT_Update) != RESET) {
		blockedEXTI[6] = 0;

		TIM_Cmd(TIM12, DISABLE);
		TIM_SetCounter(TIM12, 0);

		TIM_ClearITPendingBit(TIM12, TIM_IT_Update);
	}
}
