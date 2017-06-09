#include "stm32f4xx.h"

#include "audio.h"
#include "filesystem.h"


int main(void) {
	SystemInit();

	configureFileSystem();
	configureAudio();
	//configureButtons();


	for (;;) {
		tickAudio();
	}
}
