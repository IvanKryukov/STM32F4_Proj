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
	USARTx->CR1 |= USART_CR1_UE;
	USARTx->CR1 &= ~USART_CR1_M;
	USARTx->CR2 &= ~USART_CR2_STOP;
	//USARTx->BRR = 0x68; 	// for 1MHz 9600 baudrate
	//USARTx->BRR = 0xD0; 	// for 2MHz 9600 baudrate
	//USARTx->BRR = 0x341; 	// for 16MHz 9600 baudrate
	//USARTx->BRR = 0x1117; 	// for 42MHz 9600 baudrate
	//USARTx->BRR = 0x1940; 	// for 120MHz 9600 baudrate
	USARTx->BRR = USARTx_BRRegister(9600, 1000000);
	USARTx->CR1 |= USART_CR1_RE;
	USARTx->CR1 |= USART_CR1_TE;
	USARTx->CR1 |= USART_CR1_RXNEIE;
	//USARTx->CR1 |= USART_CR1_TCIE;
	
	if (USARTx == USART1) NVIC_EnableIRQ(USART1_IRQn);
	if (USARTx == USART2) NVIC_EnableIRQ(USART2_IRQn);
	if (USARTx == USART3) NVIC_EnableIRQ(USART3_IRQn);
	if (USARTx == USART6) NVIC_EnableIRQ(USART6_IRQn);
}
