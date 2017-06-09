#ifndef __AUDIO_H
#define __AUDIO_H

/*
 * INCLUDES
 */

#include <stdlib.h>
#include "misc.h"

#include "filesystem.h"

/*
 * Structures
 */

struct Sample {
	FSIZE_t position;
	int id;
	int isEnd;

	struct Sample* next;
};

/*
 * VARS
 */

u16 sample_buffer[2048];
struct Sample* sampleList;


/*
 * FUNCTIONS
 */

void configureAudio(void);

void tickAudio();

//struct SampleNode* runSample(int id);

//uint16_t processSamples();

//void deleteSample(struct SampleNode** sample);


#endif /* __AUDIO_H */
