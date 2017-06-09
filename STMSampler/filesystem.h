#ifndef __FILESYSTEM_H
#define __FILESYSTEM_H

/*
 * DEFINES
 */
#define FILL_FIRST_HALF DMA_FLAG_HTIF5
#define FILL_SECOND_HALF DMA_FLAG_TCIF5

/*
 * INCLUDES
 */
#include "stm32f4xx_dma.h"

#include "misc.h"
#include "delay.h"
#include "codec.h"
#include "ff.h"

#include "audio.h"

/*
 * VARS
 */



/*
 * FUNCTIONS
 */
void configureFileSystem(void);
void applySample(struct Sample** targetSample, uint32_t portionFlag);

#endif /* __FILESYSTEM_H */
