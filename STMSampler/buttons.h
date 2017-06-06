
#ifndef __BUTTONS_H
#define __BUTTONS_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_tim.h"
#include "misc.h"

#include "audio.h"

#define BUTTONS_PINS GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7

void configureButtons(void);

void EXTI0_IRQHandler(void);
void TIM4_IRQHandler(void);

int blockedEXTI[8];

#endif
