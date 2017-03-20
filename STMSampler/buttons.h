
#ifndef __BUTTONS_H
#define __BUTTONS_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define BUTTONS_PINS GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11

void configureButtons(void);

#endif
