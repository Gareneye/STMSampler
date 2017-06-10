#include "stm32f4xx.h"

#include "diodes.h"
#include "buttons.h"
#include "filesystem.h"


int main(void) {
	SystemInit();

	configureDiodes();
	configureFileSystem();
	configureAudio();
	configureButtons();

	for (;;) {
		tickAudio();
	}
}
