#include "stm32f4xx.h"

#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_rcc.h"

#include "misc.h"
#include "delay.h"
#include "codec.h"
#include "ff.h"

FATFS fatfs;
FIL file;
u16 sample_buffer[2048];

void MY_DMA_initM2P() {
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

void SysTick_Handler() {
	disk_timerproc();
}

int main(void) {
	SystemInit();

	delay_init(80); // wyslanie 80 impulsow zegarowych; do inicjalizacji SPI
	SPI_SD_Init(); // inicjalizacja SPI pod SD

	// SysTick_CLK... >> taktowany z f = ok. 82MHz/8 = ok. 10MHz
	// Systick_Config >> generuje przerwanie co <10ms
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); // zegar 24-bitowy
	SysTick_Config(90000);

	// SD CARD
	FRESULT fresult;

	disk_initialize(0); // inicjalizacja karty
	fresult = f_mount(&fatfs, 1, 1); // zarejestrowanie dysku logicznego w systemie

	///

	codec_init();
	codec_ctrl_init();
	I2S_Cmd(CODEC_I2S, ENABLE); // Integrated Interchip Sound to connect digital devices
	MY_DMA_initM2P();

	Codec_VolumeCtrl(0x9999);

	//

	UINT read_bytes; // uzyta w f_read
	fresult = f_open(&file, "1.wav", FA_READ);
	if (fresult == FR_OK) {
		fresult = f_lseek(&file, 44); // pominiecie 44 B naglowka pliku .wav
		volatile ITStatus it_status; // sprawdza flage DMA
		while (1) {

			// Czekanie az przesle polowe
			it_status = RESET;
			while (it_status == RESET) {
				it_status = DMA_GetFlagStatus(DMA1_Stream5, DMA_FLAG_HTIF5);
			}

			// Wczytywanie pierwszej polowy
			fresult = f_read(&file, &sample_buffer[0], 1024 * 2, &read_bytes);

			DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_HTIF5);

			if (fresult != FR_OK || read_bytes < 1024 * 2) {
				break;
			}


			// Czekanie az przesle calosc
			it_status = RESET;
			while (it_status == RESET) {
				it_status = DMA_GetFlagStatus(DMA1_Stream5, DMA_FLAG_TCIF5);
			}

			// Wczytywanie drugiej polowy
			fresult = f_read(&file, &sample_buffer[1024], 1024 * 2, &read_bytes);

			DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF5);

			if (fresult != FR_OK || read_bytes < 1024 * 2) {
				break;
			}

		}
		fresult = f_close(&file);
	}

	for (;;) {
	}
}



/*
int main(void)
{
	SystemInit();

    //configureFileSystem();
	//configureButtons();
	//configureAudio();

	while(1) {}
}

*/
