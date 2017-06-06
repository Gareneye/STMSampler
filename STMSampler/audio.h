#ifndef __AUDIO_H
#define __AUDIO_H

#include <stdlib.h>

#include "filesystem.h"
#include "STM32F4-Discovery/stm32f4_discovery_audio_codec.h"

uint32_t retVal_Init;
uint32_t retVal_Play;
uint32_t retVal_PauseResume;

struct SampleNode {
	int pointer;
	int idSample;
	int finish;

	struct SampleNode* prev;
	struct SampleNode* next;
};

struct SampleNode* samples;

struct SampleNode* createSample(int id);

void runSample(struct SampleNode* newSample);

uint16_t processSamples(struct SampleNode** sample, uint16_t value);

void deleteSample(struct SampleNode** sample);

void configureAudio(void);

#endif /* __AUDIO_H */
