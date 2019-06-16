#include "gpio_config.h"

/********** SET AF FOR ANY GPIO PIN **********/
void Setting_GPIO_AF(GPIO_TypeDef* GPIOx, uint8_t GPIO_PinSource, uint8_t GPIO_AF)
{
	uint32_t temp, temp2;
	temp = ((uint32_t)(GPIO_AF) << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4)) ;
	GPIOx->AFR[12 >> 0x03] &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4)) ;
	temp2 = GPIOD->AFR[GPIO_PinSource >> 0x03] | temp;
	GPIOx->AFR[GPIO_PinSource >> 0x03] |= temp2;
}
