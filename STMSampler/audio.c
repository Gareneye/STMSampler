#include "audio.h"
#include "audio_sample.h"
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"

void configureAudio(void) {
	samples = NULL;

	// For tests
	runSample(createSample(91001));

	RCC_PLLI2SCmd(ENABLE);

	EVAL_AUDIO_SetAudioInterface(AUDIO_INTERFACE_I2S);
	retVal_Init = EVAL_AUDIO_Init(OUTPUT_DEVICE_HEADPHONE, 70, 44000);
}

/*
 *
 * SAMPLES
 *
 */

// TODO: Configure SD Card
/*
typedef enum { TRUE = 1, FALSE = 0 } bool;

static volatile
DSTATUS Stat = STA_NOINIT;

static volatile
BYTE Timer1, Timer2;

static
BYTE CardType;

static
BYTE PowerFlag = 0;

static
void SELECT (void) 				// CS w stan niski
{
	GPIOB->BSRRH |= GPIO_BSRR_BS_11;
}

static
void DESELECT (void) 			// CS w stan wysoki
{
	GPIOB->BSRRL |= GPIO_BSRR_BS_11;
}

  void SPI_SD_Init( void )
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;



	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE); //taktowanie dla SPI2
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //taktowanie dla B

	// GPIOB - PB11( CS ) to na pewno dziala
		GPIOB->MODER |= GPIO_MODER_MODER11_0;
		GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11;

		//Serial Clock, sluzy do przesylania sygnalu zegarowego

		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		//							SPI
		SPI_InitTypeDef SPI_InitStructure;

		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
		SPI_InitStructure.SPI_CRCPolynomial = 7;
		SPI_Init(SPI2, &SPI_InitStructure);

		SPI_CalculateCRC(SPI2, DISABLE);
		SPI_Cmd(SPI2, ENABLE);					// Wlacz SPI2

		RCC->APB1RSTR |= RCC_APB1RSTR_SPI2RST;
	    delay_ms( 10 );
	    RCC->APB1RSTR &= ~RCC_APB1RSTR_SPI2RST;


	DESELECT(); //ustawienie CS na 1, w stan wysoki
}

 static
  BYTE rcvr_spi (void) 		// Odebranie bajtu z SD
  {
    u8 Data = 0;
  u8 i;
  	while( !( SPI2->SR & SPI_SR_TXE ));
  	SPI2->DR = 0xFF;
  	while( !( SPI2->SR & SPI_SR_RXNE ));
  	for(i=0;i<10;i++);
  	Data = SPI2->DR;

    return Data;
  }


  static
  void rcvr_spi_m (BYTE *dst)
  {
      *dst = rcvr_spi();
  }

  static
  BYTE wait_ready (void)
  {
      BYTE res;

      Timer2 = 50;    // Wait for ready in timeout of 500ms
      rcvr_spi();
      do
          res = rcvr_spi();
      while ((res != 0xFF) && Timer2);

      return res;
  }

  static
  bool rcvr_datablock (
      BYTE *buff,            // Data buffer to store received data
      UINT btr            // Byte count (must be even number)
  )
  {
      BYTE token;

      Timer1 = 10;
      do {                            // Wait for data packet in timeout of 100ms
          token = rcvr_spi();
      } while ((token == 0xFF) && Timer1);
      if(token != 0xFE) return FALSE;    // If not valid data token, retutn with error

      do {                            // Receive the data block into buffer
          rcvr_spi_m(buff++);
          rcvr_spi_m(buff++);
      } while (btr -= 2);
      rcvr_spi();                        // Discard CRC
      rcvr_spi();

      return TRUE;                    // Return with success
  }
*/


// do przetworzenia

/*
 #include <SDCard.hpp>

SDCard::SDCard(SPI_HandleTypeDef* hspi, uint16_t cs1Pin,
		GPIO_TypeDef* cs1Port) {
	_spi = hspi;
	_cs1Pin = cs1Pin;
	_cs1Port = cs1Port;
	_sdSize = 0;
}

uint32_t SDCard::getSize() {
	if (_sdSize == 0) {
		//We have not read the disk size just yet :O
		csd_t csd;
		if (!readCSD(&csd))
			return 0;
		if (csd.v1.csd_ver == 0) {
			uint8_t read_bl_len = csd.v1.read_bl_len;
			uint16_t c_size = (csd.v1.c_size_high << 10)
					| (csd.v1.c_size_mid << 2) | csd.v1.c_size_low;
			uint8_t c_size_mult = (csd.v1.c_size_mult_high << 1)
					| csd.v1.c_size_mult_low;
			c_size = (uint32_t) (c_size + 1) << (c_size_mult + read_bl_len - 7);
			c_size /= 1024;
		} else if (csd.v2.csd_ver == 1) {
			uint32_t c_size = ((uint32_t) csd.v2.c_size_high << 16)
					| (csd.v2.c_size_mid << 8) | csd.v2.c_size_low;
			c_size *= 1024;
			_sdSize = c_size;

		} else {
		}
	}
	return _sdSize;
}
// read CID or CSR register
uint8_t SDCard::readRegister(uint8_t cmd, void* buf) {
	uint8_t* dst = reinterpret_cast<uint8_t*>(buf);
	if (cardCommand(cmd, 0)) {
		deselectCard();
		return false;
	}
	uint8_t temp = 0xFF;
	while (temp == 0xFF) {
		SPI_Recieve(&temp, 1);
	}
	// transfer data
	SPI_Recieve(dst, 16);
	SPI_Recieve(&temp, 1); //CRC1
	SPI_Recieve(&temp, 1); //CRC2
	deselectCard();
	return true;
}
bool SDCard::readBlock(uint32_t blockaddr, uint8_t* buffer) {
	if (cardCommand(CMD17, blockaddr)) {
		// Error
		deselectCard();
		return false;
	}
	uint8_t temp = 0xFF;
	while (temp == 0xFF) {
		HAL_SPI_Receive(_spi, &temp, 1, 100);
	}

	SPI_Recieve(buffer, 512);
	//eat the CRC
	temp = 0xFF;
	SPI_Recieve(&temp, 1);
	temp = 0xFF;
	SPI_Recieve(&temp, 1);
	deselectCard();
	return true;
}

bool SDCard::writeBlock(uint32_t blockaddr, uint8_t* buffer) {
	//The cardCommand will select the card so we have to make sure we clean up
	if (cardCommand(CMD24, blockaddr)) {

		 // Error

		deselectCard();
		return false;
	}

	 // Write the data

	uint8_t temp = DATA_START_BLOCK;
	HAL_SPI_Transmit(_spi, &temp, 1, 100);
	HAL_SPI_Transmit(_spi, buffer, 512, 100);
	temp = 0xFF;
	HAL_SPI_Transmit(_spi, &temp, 1, 100);
	HAL_SPI_Transmit(_spi, &temp, 1, 100);
	//read response
	SPI_Recieve(&temp, 1);
	if ((temp & DATA_RES_MASK) != DATA_RES_ACCEPTED) {

		 // Error

		deselectCard();
		return false;
	}
	// wait for flash programming to complete
	waitUntilReady();

	// response is r2 so get and check two bytes for nonzero
	if (cardCommand(CMD13, 0)) {

		 // Error

		deselectCard();
		return false;
	}
	SPI_Recieve(&temp, 1);
	if (temp) {

		 // Error

		deselectCard();
		return false;
	}
	deselectCard();
	return true;
}

void SDCard::waitUntilReady() {
	uint8_t ans[1] = { 0 };
	while (ans[0] != 0xFF) {
		SPI_Recieve(ans, 1);
	}
}

bool SDCard::initalize() {
	_spi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256; //slow down at first
	HAL_SPI_Init(_spi); //apply the speed change
	deselectCard();
//We must supply at least 74 clocks with CS high
	uint8_t buffer[4] = { 0xFF, 0xFF, 0xFF, 0xFF };
	HAL_SPI_Transmit(_spi, buffer, 4, 100);
	HAL_SPI_Transmit(_spi, buffer, 4, 100);
	HAL_SPI_Transmit(_spi, buffer, 4, 100);
	HAL_Delay(5);
	selectCard();
	uint8_t status;
	// command to go idle in SPI mode
	while ((status = cardCommand(CMD0, 0)) != R1_IDLE_STATE) {

	}
	// check SD version
	if ((cardCommand(CMD8, 0x1AA) & R1_ILLEGAL_COMMAND)) {
		deselectCard();
		return false; //Unsupported
	} else {
		// only need last byte of r7 response
		HAL_SPI_Receive(_spi, buffer, 4, 100);
		if (buffer[3] != 0XAA) {
			return false; //failed check
		}

	}
	// initialize card and send host supports SDHC
	while ((status = cardAcmd(ACMD41, 0X40000000)) != R1_READY_STATE) {

	}
	// if SD2 read OCR register to check for SDHC card
	if (cardCommand(CMD58, 0)) {
		deselectCard();
		return false;
	}
	//discard OCR reg

	SPI_Recieve(buffer, 4);
	deselectCard();
	_spi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4; //speed back up
	HAL_SPI_Init(_spi); //apply the speed change
	return true;
}

uint8_t SDCard::cardCommand(uint8_t command, uint32_t arg) {
	uint8_t res = 0xFF;
	//HAL_SPI_Transmit(_spi, &res, 1, 100);
	// HAL_SPI_Transmit(_spi, &res, 1, 100);
	 //HAL_SPI_Transmit(_spi, &res, 1, 100);
	 //HAL_SPI_Transmit(_spi, &res, 1, 100);
	 //HAL_SPI_Transmit(_spi, &res, 1, 100);
	 //HAL_SPI_Transmit(_spi, &res, 1, 100);
	 //HAL_SPI_Transmit(_spi, &res, 1, 100);

	selectCard();
	waitUntilReady(); //wait for card to no longer be busy
	uint8_t commandSequence[] = { (uint8_t) (command | 0x40), (uint8_t) (arg
			>> 24), (uint8_t) (arg >> 16), (uint8_t) (arg >> 8), (uint8_t) (arg
			& 0xFF), 0xFF };
	if (command == CMD0)
		commandSequence[5] = 0x95;
	else if (command == CMD8)
		commandSequence[5] = 0x87;
	HAL_SPI_Transmit(_spi, commandSequence, 6, 100);
	//Data sent, now await Response
	uint8_t count = 20;
	while ((res & 0x80) && count) {
		SPI_Recieve(&res, 1);
		count--;
	}
	return res;
}

void SDCard::selectCard() {
	HAL_GPIO_WritePin(_cs1Port, _cs1Pin, GPIO_PIN_RESET);
}

HAL_StatusTypeDef SDCard::SPI_Recieve(uint8_t* pData, uint16_t Size) {

	HAL_StatusTypeDef errorcode = HAL_OK;

	// Process Locked
	__HAL_LOCK(_spi);

	// Don't overwrite in case of HAL_SPI_STATE_BUSY_RX
	if (_spi->State == HAL_SPI_STATE_READY) {
		_spi->State = HAL_SPI_STATE_BUSY_TX_RX;
	}

	// Set the transaction information
	_spi->ErrorCode = HAL_SPI_ERROR_NONE;
	_spi->pRxBuffPtr = (uint8_t *) pData;
	_spi->RxXferCount = Size;
	_spi->RxXferSize = Size;
	_spi->pTxBuffPtr = (uint8_t *) pData;
	_spi->TxXferCount = Size;
	_spi->TxXferSize = Size;

	//Init field not used in handle to zero
	_spi->RxISR = NULL;
	_spi->TxISR = NULL;
	// Check if the SPI is already enabled
	if ((_spi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE) {
		// Enable SPI peripheral
		__HAL_SPI_ENABLE(_spi);
	}
	// Transmit and Receive data in 8 Bit mode
	while ((_spi->RxXferCount > 0U)) {
		*(__IO uint8_t *) &_spi->Instance->DR = 0xFF; //send data
		while (!(__HAL_SPI_GET_FLAG(_spi, SPI_FLAG_TXE)))
			;
		while (!(__HAL_SPI_GET_FLAG(_spi, SPI_FLAG_RXNE)))
			;
		(*(uint8_t *) pData++) = _spi->Instance->DR;
		_spi->RxXferCount--;
	}

	if (lSPI_WaitFlagStateUntilTimeout(_spi, SPI_FLAG_BSY, RESET, 100,
			HAL_GetTick()) != HAL_OK) {
		_spi->ErrorCode |= HAL_SPI_ERROR_FLAG;

		errorcode = HAL_TIMEOUT;
	}

	_spi->State = HAL_SPI_STATE_READY;
	__HAL_UNLOCK(_spi);
	return errorcode;
}

void SDCard::deselectCard() {
	HAL_GPIO_WritePin(_cs1Port, _cs1Pin, GPIO_PIN_SET);
}

 // @brief Handle SPI Communication Timeout.
 //@param hspi: pointer to a SPI_HandleTypeDef structure that contains
 //             the configuration information for SPI module.
 //@param Flag: SPI flag to check
 //@param State: flag state to check
 //@param Timeout: Timeout duration
 //@param Tickstart: tick start value
 //@retval HAL status

HAL_StatusTypeDef SDCard::lSPI_WaitFlagStateUntilTimeout(
		SPI_HandleTypeDef *hspi, uint32_t Flag, uint32_t State,
		uint32_t Timeout, uint32_t Tickstart) {
	while ((hspi->Instance->SR & Flag) != State) {
		if (Timeout != HAL_MAX_DELAY) {
			if ((Timeout == 0U) || ((HAL_GetTick() - Tickstart) >= Timeout)) {
				// Disable the SPI and reset the CRC: the CRC value should be cleared
				// on both master and slave sides in order to resynchronize the master
				// and slave for their respective CRC calculation

				// Disable TXE, RXNE and ERR interrupts for the interrupt process
				__HAL_SPI_DISABLE_IT(hspi,
						(SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));

				if ((hspi->Init.Mode == SPI_MODE_MASTER)
						&& ((hspi->Init.Direction == SPI_DIRECTION_1LINE)
								|| (hspi->Init.Direction
										== SPI_DIRECTION_2LINES_RXONLY))) {
					// Disable SPI peripheral
					__HAL_SPI_DISABLE(hspi);
				}

				// Reset CRC Calculation
				if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE) {
					SPI_RESET_CRC(hspi);
				}

				hspi->State = HAL_SPI_STATE_READY;

				// Process Unlocked
				__HAL_UNLOCK(hspi);

				return HAL_TIMEOUT;
			}
		}
	}

	return HAL_OK;
}
 */
struct SampleNode* createSample(uint32_t size)
{
	struct SampleNode* newSample =
			(struct SampleNode*)malloc(sizeof(struct SampleNode));

	newSample->size = size;
	newSample->pointer = 0;

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

	if((*targetSample)->pointer == (*targetSample)->size)
	{
		deleteSample(targetSample);
	}
	else
	{
		value += AUDIO_SAMPLE[(*targetSample)->pointer];

		(*targetSample)->pointer++;
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

