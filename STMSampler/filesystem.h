#ifndef __FILESYSTEM_H
#define __FILESYSTEM_H

#include "misc.h"
#include "audio.h"

#include "delay/delay.h"
#include "lib_cm4/fpu.h"
#include "FatFs_SD/spi_sd.h"
#include "FatFs_SD/ff.h"

// Disc
FATFS fatfs;
FIL plik[8];
FRESULT fresult;

void configureFileSystem(void);
uint16_t getNext(struct SampleNode** targetSample);



#endif /* __FILESYSTEM_H */
