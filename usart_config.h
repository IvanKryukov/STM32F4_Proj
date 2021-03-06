#ifndef USART_CONFIG_H
#define USART_CONFIG_H

#include "stm32f4xx.h"

uint32_t USARTx_BRRegister(uint32_t BaudRate, uint32_t APBxCLK);
void USART_conf(USART_TypeDef* USARTx);
void USART_sendByte(USART_TypeDef* USARTx, uint8_t data);
void USART_sendBytes(USART_TypeDef* USARTx, uint8_t* data, uint8_t len);
void USART_sendMessage(USART_TypeDef* USARTx, uint8_t* data);
uint8_t USART_readByte(USART_TypeDef* USARTx);

void print(unsigned char *out_line);
void print_byte(unsigned char out_byte);
void print_bytes(unsigned char *out_bytes, unsigned char bytes_count);
unsigned char read_byte(void);

#endif

