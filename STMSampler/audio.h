#ifndef __AUDIO_H
#define __AUDIO_H

#include <stdlib.h>
#include "misc.h"

struct SampleNode {
	int position;
	int id;
	int isEnd;

	struct SampleNode* prev;
	struct SampleNode* next;
};


struct SampleNode* samples;

struct SampleNode* runSample(int id);

uint16_t processSamples();

void deleteSample(struct SampleNode** sample);

void configureAudio(void);

#endif /* __AUDIO_H */
