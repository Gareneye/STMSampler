#include "audio.h"

void configureAudio(void) {
	samples = NULL;

	// For tests
	//runSample(createSample(1));

	RCC_PLLI2SCmd(ENABLE);

	EVAL_AUDIO_SetAudioInterface(AUDIO_INTERFACE_I2S);
	retVal_Init = EVAL_AUDIO_Init(OUTPUT_DEVICE_HEADPHONE, 70, 44100);
}

/*
 *
 * SAMPLES
 *
 */

struct SampleNode* createSample(int id)
{
	struct SampleNode* newSample =
			(struct SampleNode*)malloc(sizeof(struct SampleNode));

	newSample->pointer = 0;
	newSample->idSample = id;
	newSample->finish = 0;

	newSample->prev = NULL;
	newSample->next = NULL;

	return newSample;
}

void runSample(struct SampleNode* newSample)
{
	newSample->next = samples;

	if(samples != NULL)
		samples->prev = newSample;

	samples = newSample;
}

uint16_t processSamples(struct SampleNode** targetSample, uint16_t value)
{
	if((*targetSample) == NULL)
		return value;

	struct SampleNode** next = &((*targetSample)->next);

	if((*targetSample)->finish == 1)
	{
		deleteSample(targetSample);
	}
	else
	{
		//value += AUDIO_SAMPLE[(*targetSample)->pointer];
		value += getNext(targetSample);
		//value += 0x1111;
	}

	return processSamples(next, value);
}

void deleteSample(struct SampleNode** targetSample)
{
	if(samples == *targetSample)
	{
		samples = (*targetSample)->next;
	}
	else
	{
		(*targetSample)->prev->next = (*targetSample)->next;
	}

	if((*targetSample)->next != NULL)
	{
		(*targetSample)->next->prev = (*targetSample)->prev;
	}

	free(*targetSample);
	*targetSample = NULL;
}



/*
 *
 * CALLBACKS
 *
 */

uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
	return processSamples(&samples, 0x0000);
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

