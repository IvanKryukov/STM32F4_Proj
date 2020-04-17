#include "rcc_config.h"

void RCC_conf(void)
{
	RCC->CFGR |= RCC_CFGR_HPRE_DIV4;
	RCC->CFGR &= ~RCC_CFGR_HPRE;		// Reset AHB1 Prescaler
	//RCC->CFGR |= RCC_CFGR_HPRE_2;		// Set AHB1 Prescaler (div 2)
	
	RCC->CFGR &= ~RCC_CFGR_SW;			// Clear SW bits in CFGR register
	//RCC->CFGR |= RCC_CFGR_SW_HSE;		// Set HSE clock as system clock
	RCC->CFGR |= RCC_CFGR_SW_PLL;		// Set PLL clock as system clock
	
	RCC->CFGR &= ~RCC_CFGR_PPRE1;		// Reset APB1 Prescaler
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
	
	RCC->CFGR &= ~RCC_CFGR_PPRE1;		// Reset APB2 Prescaler
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
	
	RCC->CR |= RCC_CR_PLLON;
	
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC; 		// Reset PLL Source
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;	// Set the HSE as source of PLL
}

