#include "main.h"

uint8_t input_line[255], temp_line[255];
uint8_t *p_input = &input_line[0], *p_temp = &temp_line[0];

void clean_input_line(void)
{
	int i;
	for (i = 0; i < 255; i++)
		input_line[i] = 0;
}

void copy_to_temp_line(void)
{
	int i;
	for (i = 0; i < 255; i++)
		temp_line[i] = input_line[i];
}

void delay_kcycles(uint32_t kcycles)
{
	kcycles *= 1000;
	while(kcycles--);
}

void GPIO_conf(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN|RCC_AHB1ENR_GPIOBEN|RCC_AHB1ENR_GPIOCEN|RCC_AHB1ENR_GPIODEN; // Set clock for all GPIO
	
	/******************** Set PC6 Pin USART6 (TX) ********************/
	GPIOC->MODER &= ~(GPIO_MODER_MODER6);
	GPIOC->MODER |= GPIO_MODER_MODER6_1;
	GPIOC->OTYPER &= ~(GPIO_OTYPER_OT_6);
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPDR6);
	GPIOC->PUPDR |= GPIO_PUPDR_PUPDR6_0;
	GPIOC->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR6);
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6;
	
	/******************** Set PC7 Pin USART6 (RX) ********************/
	GPIOC->MODER &= ~(GPIO_MODER_MODER7);
	GPIOC->MODER |= GPIO_MODER_MODER7_1;
	GPIOC->OTYPER &= ~(GPIO_OTYPER_OT_7);
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPDR7);
	GPIOC->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR7);
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7;
	
	/******************** Set PD15 Pin LED Blue for TX ********************/
	GPIOD->MODER &= ~(GPIO_MODER_MODER15);
	GPIOD->MODER |= GPIO_MODER_MODER15_0;
	GPIOD->OTYPER &= ~(GPIO_OTYPER_OT_15);
	GPIOD->PUPDR &= ~(GPIO_PUPDR_PUPDR15);
	GPIOD->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR15);
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15;
	
	/******************** Set PD14 Pin LED Red for RX ********************/
	GPIOD->MODER &= ~(GPIO_MODER_MODER14);
	GPIOD->MODER |= GPIO_MODER_MODER14_0;
	GPIOD->OTYPER &= ~(GPIO_OTYPER_OT_14);
	GPIOD->PUPDR &= ~(GPIO_PUPDR_PUPDR14);
	GPIOD->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR14);
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14;
}

int main(void)
{
	__enable_irq();
	RCC_conf();
	GPIO_conf();
	GPIOD->ODR &= ~(GPIO_ODR_ODR_14 | GPIO_ODR_ODR_15);
	
	USART_conf(USART6);
	Setting_GPIO_AF(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
	Setting_GPIO_AF(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);
	
	while(1)
	{
		
	}
}

void USART6_IRQHandler(void)
{
	uint8_t buf = 0;	
	USART6->SR |= USART_SR_RXNE;
	buf = USART6->DR;	// read a key
	
	if (buf == 0x0D)	// if user pressed 'Enter' 
	{
		USART_sendMessage(USART6, "\n\r");
		USART_sendMessage(USART6, "cmd >> ");
		USART_sendMessage(USART6, input_line);
		USART_sendMessage(USART6, "\n\r");
		p_input = &input_line[0];
		copy_to_temp_line();
		clean_input_line();
	}
	else if (buf == 0x7F)
	{
		USART_sendByte(USART6, 0x7F);
		if (p_input > &input_line[0]) 
		{
			p_input--;
			*p_input = 0;
		}
	}
	else 							// if pressed another key
	{
		USART_sendByte(USART6, buf);
		*p_input++ = buf;
	}	
	
	GPIOD->ODR ^= GPIO_ODR_ODR_14;
}

