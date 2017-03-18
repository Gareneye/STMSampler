
#include "buttons.h"

void configureButtons(void) {
	// GPIO
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIO_InitButtonsStruct;
	GPIO_InitButtonsStruct.GPIO_Pin = BUTTONS_PINS;
	GPIO_InitButtonsStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitButtonsStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitButtonsStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitButtonsStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOD, &GPIO_InitButtonsStruct);
}
