#include "STM32F4-Discovery/stm32f4_discovery_audio_codec.h"
#include "audio_sample.h"
#include "codec.h"

uint32_t retVal_Init;
uint32_t retVal_Play;
uint32_t retVal_PauseResume;

void configureAudio(void) {
	EVAL_AUDIO_SetAudioInterface(AUDIO_INTERFACE_I2S);
	retVal_Init = EVAL_AUDIO_Init(OUTPUT_DEVICE_HEADPHONE, 70, 44000);

	retVal_Play = EVAL_AUDIO_Play((uint16_t*)(AUDIO_SAMPLE + 58), 900000);
}

int main(void)
{
	SystemInit();
	
	/* Magic! */
	codec_init();
	codec_ctrl_init();
	configureAudio();

	while(1) {}
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
	return 1;
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
	retVal_Play = EVAL_AUDIO_Play((uint16_t*)(AUDIO_SAMPLE + 58), 900000);
}

void EVAL_AUDIO_HalfTransfer_CallBack(uint32_t pBuffer, uint32_t Size)
{
}

void EVAL_AUDIO_Error_CallBack(void* pData)
{
	while(1);
}

uint32_t Codec_TIMEOUT_UserCallback(void)
{
	while(1);
	return 1;
}
