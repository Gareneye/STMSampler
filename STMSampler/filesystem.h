#ifndef __FILESYSTEM_H
#define __FILESYSTEM_H

/*
 * DEFINES
 */
#define FILL_FIRST_HALF DMA_FLAG_HTIF5
#define FILL_SECOND_HALF DMA_FLAG_TCIF5

#define BUFFER_SIZE 2048

/*
 * INCLUDES
 */
#include "stm32f4xx_dma.h"
#include <stdlib.h>
#include "misc.h"

#include "misc.h"
#include "delay.h"
#include "codec.h"
#include "ff.h"

#include "audio.h"
#include "diodes.h"

/*
 * VARS
 */
u16 sample_buffer[BUFFER_SIZE];
u16 cache[BUFFER_SIZE];


/*
 * FUNCTIONS
 */
void configureFileSystem(void);
void applySample(uint32_t portionFlag);

void loadSample(struct Sample** targetSample);

#endif /* __FILESYSTEM_H */
