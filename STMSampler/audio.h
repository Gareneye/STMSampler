#ifndef __AUDIO_H
#define __AUDIO_H

#include "STM32F4-Discovery/stm32f4_discovery_audio_codec.h"

uint32_t retVal_Init;
uint32_t retVal_Play;
uint32_t retVal_PauseResume;
uint32_t pointer;
uint32_t pointer2;

void configureAudio(void);

#endif /* __AUDIO_H */
