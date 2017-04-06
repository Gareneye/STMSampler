#include "audio.h"

int main(void)
{
	SystemInit();
	
	configureAudio();

	while(1) {}
}

