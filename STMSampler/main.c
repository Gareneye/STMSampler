#include "audio.h"
#include "filesystem.h"


int main(void)
{
	SystemInit();

    configureFileSystem();
	configureButtons();
	configureAudio();

	/*
	FATFS fatfs;
	FIL plik;
	FRESULT fresult;
	UINT zapisanych_bajtow = 0;
	UINT zapianie_bajtow = 0;
	char * buffor = "MATEUSZ\r\n";
	uint16_t i;

    fresult = f_mount( 0, &fatfs );
    fresult = f_open( &plik, "plik.txt", FA_OPEN_EXISTING | FA_READ );
    if( fresult == FR_OK )
    {
        fresult = f_write( &plik, ( const void * ) buffor, 17, &zapisanych_bajtow );
    }

    fresult = f_close( &plik );
    */


	while(1) {}
}

