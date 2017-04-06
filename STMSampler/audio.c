#include "audio.h"
#include "audio_sample.h"

void configureAudio(void) {
	pointer = 0;

	pointer2 = 3000;

	RCC_PLLI2SCmd(ENABLE);

	EVAL_AUDIO_SetAudioInterface(AUDIO_INTERFACE_I2S);
	retVal_Init = EVAL_AUDIO_Init(OUTPUT_DEVICE_HEADPHONE, 70, 44000);
}

/*
 *
 * CALLBACKS
 *
 */

uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
	if(pointer > 400000)
		pointer = 0;
	else
		pointer++;

	if(pointer2 > 400000)
		pointer2 = 3000;
	else
		pointer2++;

	float v1 = (float) AUDIO_SAMPLE[pointer];
	float v2 = (float) AUDIO_SAMPLE[pointer2];

	float v = (v1 + v2);

	return (uint16_t)v;
}



void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size) {
}

void EVAL_AUDIO_HalfTransfer_CallBack(uint32_t pBuffer, uint32_t Size) {
}

void EVAL_AUDIO_Error_CallBack(void* pData) {
	while (1);
}

uint32_t Codec_TIMEOUT_UserCallback(void) {
	while (1);
	return 1;
}

