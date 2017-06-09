#include "filesystem.h"

FRESULT fresult;
FATFS fatfs;
FIL file[8];

volatile ITStatus it_status;

void configureFileSystem(void)
{
	/*
	 * HARDWARE Config
	 */

	delay_init(80); // wyslanie 80 impulsow zegarowych; do inicjalizacji SPI
	SPI_SD_Init(); // inicjalizacja SPI pod SD

	// SysTick_CLK... >> taktowany z f = ok. 82MHz/8 = ok. 10MHz
	// Systick_Config >> generuje przerwanie co <10ms
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); // zegar 24-bitowy
	SysTick_Config(90000);

	disk_initialize(0); // inicjalizacja karty
	fresult = f_mount(&fatfs, 1, 1); // zarejestrowanie dysku logicznego w systemie

	/*
	 * Setup
	 */

    int i;
    for(i = 0; i<8; i++)
    {
    	char name[5];
    	sprintf(name, "%d.wav", i+1);

    	fresult = f_open( &file[i], name, FA_READ ) || fresult;
    }
}

void closeFiles()
{
    int i;
    for(i = 0; i < 8; i++)
    {
    	fresult = f_close( &file[i] ) || fresult;
    }
}


#define sample (*targetSample)
void applySample(struct Sample** targetSample, uint32_t portionFlag)
{
	FIL* targetFile = &(file[sample->id - 1]);
	int bufferPointer;
	UINT read_bytes;

	// skip 44 bytes in .wav
	if(sample->position < 44)
		sample->position = 44;

	fresult = f_lseek(targetFile, sample->position);

	switch(portionFlag)
	{
		case FILL_FIRST_HALF:
			bufferPointer = 0;
			break;
		case FILL_SECOND_HALF:
			bufferPointer = 1024;
			break;
	}

	fresult = f_read(targetFile, &sample_buffer[bufferPointer], 1024 * 2, &read_bytes);

	if (fresult != FR_OK || read_bytes < 1024 * 2) {
		sample->isEnd = 1;
	}

	sample->position = targetFile->fptr;
}

/*
 * MUST BE
 * Tick for disk
 */
void SysTick_Handler() {
	disk_timerproc();
}
