#ifndef __AUDIO_H
#define __AUDIO_H

/*
 * INCLUDES
 */

#include <stdlib.h>
#include "misc.h"

#include "filesystem.h"
#include "diodes.h"

/*
 * Structures
 */

struct Sample {
	FSIZE_t position;
	//int position;
	int id;
	int isEnd;

	struct Sample* prev;
	struct Sample* next;
};

/*
 * VARS
 */

struct Sample* sampleList;


/*
 * FUNCTIONS
 */

void configureAudio(void);

void tickAudio();

void runSample(int id);

u16 addSamples(int i);


#endif /* __AUDIO_H */
