#ifndef SPI_CONFIG
#define SPI_CONFIG

#include "stm32f4xx.h"
#include "main.h"

#define SPI_Slave		0
#define SPI_Master	1

void SPI_INIT(SPI_TypeDef* SPIx, uint8_t SPI_MasterSlave_Mode, uint8_t DMA_Mode);

#endif

