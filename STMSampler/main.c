#include "audio.h"

int main(void)
{
	SystemInit();
	
	configureButtons();
	configureAudio();

	while(1) {}
}

