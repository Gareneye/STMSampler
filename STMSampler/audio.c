#include "audio.h"

volatile ITStatus it_status;

/*
 * Init audio
 */
void configureAudio(void) {
	// Codec
	codec_init();
	codec_ctrl_init();
	I2S_Cmd(CODEC_I2S, ENABLE);

	// DMA for buffer
	init_DMA_M2P();

	// Sound Volume 0x0000 - 0xFFFF
	Codec_VolumeCtrl(0x9999);


	// DEBUG
	runSample(1);

}

void runSample(int id)
{
	struct Sample* newSample = (struct Sample*) malloc(sizeof(struct Sample));
	newSample->position = 0;
	newSample->id = id;
	newSample->isEnd = 0;

	newSample->prev = NULL;
	newSample->next = NULL;

	if(sampleList != NULL)
	{
		newSample->next = sampleList;
		sampleList->prev = newSample;
	}

	sampleList = newSample;
}


void tickAudio()
{
	loadSample(&sampleList);

	/*
	 * Wait for First half
	 */

	it_status = RESET;
	while (it_status == RESET) {
		it_status = DMA_GetFlagStatus(DMA1_Stream5, DMA_FLAG_HTIF5);
	}

	applySample(FILL_FIRST_HALF); // First half

	DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_HTIF5);

	/*
	 * Wait for Second half
	 */


	it_status = RESET;
	while (it_status == RESET) {
		it_status = DMA_GetFlagStatus(DMA1_Stream5, DMA_FLAG_TCIF5);
	}

	applySample(FILL_SECOND_HALF); // First half

	DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF5);


	/*
	 * Finished sampled collector
	 */

	utilizeSamples();
}


void utilizeSamples()
{
	struct Sample** head = &sampleList;

	if((*head) == NULL)
		return;

	while((*head) != NULL)
	{
		if((*head)->isEnd)
		{
			if((*head)->prev != NULL)
			{
				(*head)->prev->next = (*head)->next;
			}

			if((*head)->next != NULL)
			{
				(*head)->next->prev = (*head)->prev;
			}

			struct Sample* toDel = *head;
			head = &((*head)->next);
			free(toDel);
		}
		else
		{
			head = &((*head)->next);
		}
	}
}

/*
 * Init DMA
 */
void init_DMA_M2P(void) {
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Stream5);
	DMA_InitStructure.DMA_Channel = DMA_Channel_0; // wybor kanalu DMA
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; // ustalenie rodzaju transferu (memory2memory / peripheral2memory /memory2peripheral)
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; // tryb pracy - pojedynczy transfer badz powtarzany
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; // ustalenie priorytetu danego kanalu DMA
	DMA_InitStructure.DMA_BufferSize = 2048; // liczba danych do przeslania
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) & sample_buffer; // adres zrodlowy
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(SPI3->DR)); // adres docelowy
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; // zezwolenie na inkrementacje adresu po kazdej przeslanej paczce danych
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; // ustalenie rozmiaru przesylanych danych
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; // ustalenie trybu pracy - jednorazwe przeslanie danych
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; // wylaczenie kolejki FIFO
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;

	DMA_Init(DMA1_Stream5, &DMA_InitStructure); // zapisanie wypelnionej struktury do rejestrow wybranego polaczenia DMA
	DMA_Cmd(DMA1_Stream5, ENABLE); // uruchomienie odpowiedniego polaczenia DMA

	SPI_I2S_DMACmd(SPI3, SPI_I2S_DMAReq_Tx, ENABLE);
	SPI_Cmd(SPI3, ENABLE);
}
