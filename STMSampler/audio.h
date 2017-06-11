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
	int id;
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

void finishSample();


#endif /* __AUDIO_H */
