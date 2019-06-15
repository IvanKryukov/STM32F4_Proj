#ifndef USART_CONFIG_H
#define USART_CONFIG_H

#include "stm32f4xx.h"

uint32_t USARTx_BRRegister(uint32_t BaudRate, uint32_t APBxCLK);
void USART_conf(USART_TypeDef* USARTx);

#endif

