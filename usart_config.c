#include "usart_config.h"

uint32_t USARTx_BRRegister(uint32_t BaudRate, uint32_t APBxCLK)
{
	double BR_All;
	uint32_t BR_Reg;
	
	BR_All = APBxCLK / BaudRate; /* / 16; */
	BR_Reg = (uint32_t)BR_All;
	
	return BR_Reg;
}

void USART_conf(USART_TypeDef* USARTx)
{
	/***** Set USART Clock *****/
	if (USARTx == USART1) RCC->APB2ENR|= RCC_APB2ENR_USART1EN;
	if (USARTx == USART2) RCC->APB1ENR|= RCC_APB1ENR_USART2EN;
	if (USARTx == USART3) RCC->APB1ENR|= RCC_APB1ENR_USART3EN;
	if (USARTx == USART6) RCC->APB2ENR|= RCC_APB2ENR_USART6EN;

	/***** Set USART *****/
	USARTx->CR1 &= ~USART_CR1_M;
	USARTx->CR2 &= ~USART_CR2_STOP;
	//USARTx->BRR = 0x68; 	// for 1MHz 9600 baudrate
	//USARTx->BRR = 0xD0; 	// for 2MHz 9600 baudrate
	//USARTx->BRR = 0x341; 	// for 16MHz 9600 baudrate
	//USARTx->BRR = 0x1117; 	// for 42MHz 9600 baudrate
	//USARTx->BRR = 0x1940; 	// for 120MHz 9600 baudrate
	USARTx->BRR = USARTx_BRRegister(115200, 48000000);
	USARTx->CR1 |= USART_CR1_RE;
	USARTx->CR1 |= USART_CR1_TE;
	USARTx->CR1 |= USART_CR1_RXNEIE;
	//USARTx->CR1 |= USART_CR1_TCIE;
	USARTx->CR1 |= USART_CR1_UE;
	
	if (USARTx == USART1) NVIC_EnableIRQ(USART1_IRQn);
	if (USARTx == USART2) NVIC_EnableIRQ(USART2_IRQn);
	if (USARTx == USART3) NVIC_EnableIRQ(USART3_IRQn);
	if (USARTx == USART6) NVIC_EnableIRQ(USART6_IRQn);
}

/* Transmit USART Data and waiting for the end of transfer */
void USART_sendByte(USART_TypeDef* USARTx, uint8_t data)
{
	GPIOD->ODR |= GPIO_ODR_ODR_15;
	
	USARTx->DR = data;
	while((USARTx->SR & USART_SR_TC) == 0); // Waiting for transfer completed
	
	GPIOD->ODR &= ~GPIO_ODR_ODR_15;
}

/* Transmit USART Data and waiting for the end of transfer */
void USART_sendBytes(USART_TypeDef* USARTx, uint8_t* data, uint8_t len)
{
	
	while(len--)
	{
		GPIOD->ODR |= GPIO_ODR_ODR_15;
		
		USARTx->DR = (uint8_t)*data++;
		while((USARTx->SR & USART_SR_TC) == 0); // Waiting for completed transfer
		
		GPIOD->ODR &= ~GPIO_ODR_ODR_15;
	}
}

/* Transmit USART Data and waiting for the end of transfer */
void USART_sendMessage(USART_TypeDef* USARTx, uint8_t* data)
{
	
	while(*data)
	{
		GPIOD->ODR |= GPIO_ODR_ODR_15;
		
		USARTx->DR = (uint8_t)*data++;
		while((USARTx->SR & USART_SR_TC) == 0); // Waiting for completed transfer
		
		GPIOD->ODR &= ~GPIO_ODR_ODR_15;
	}
}


