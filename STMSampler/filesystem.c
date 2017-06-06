#include "filesystem.h"

//#include "audio_sample.h"


void configureFileSystem(void) {
	// Configure spi
    fpu_enable();
    delay_init( 168 );
    SPI_SD_Init();

    // Mount disc
    fresult = f_mount( 0, &fatfs );

    // hardcoded
    //fresult = f_open( &plik, "Bell.wav", FA_OPEN_EXISTING | FA_READ );
    //fresult = f_open( &plik, "plik.txt", FA_OPEN_EXISTING | FA_READ );
    //fresult = f_open( &plik, "Bell.wav", FA_OPEN_EXISTING | FA_READ );
    //fresult = f_open( &plik, "pcm16_44.wav", FA_OPEN_EXISTING | FA_READ );

    int i;
    for(i = 0; i<8; i++)
    {
    	char name[5];
    	sprintf(name, "%d.wav", i);

    	fresult = f_open( &plik[i], name, FA_OPEN_EXISTING | FA_READ ) || fresult;
    }
}


uint16_t getNext(struct SampleNode** targetSample)
{
	int id = (*targetSample)->idSample;

	f_lseek(&(plik[id]), (*targetSample)->pointer);

	(*targetSample)->pointer += sizeof(int16_t);

	// :(
	int16_t buffer;
	UINT *br;
	fresult = f_read(&plik[id], (void*) &buffer, (UINT) sizeof(int16_t), &br);

	if(*br < sizeof(int16_t))
	{
		(*targetSample)->finish = 1;
	}

	return (uint16_t) buffer;
}
