#include "stm32f411xe_maxClkConfig.h"

void sysclockConfig(void) {

	//1. enable hse and wait until ready
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));
	
	//2. set power enable clock and voltage regulator
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS;
	
	//3. configure flash and latency related settings
	FLASH->ACR |= ( FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_3WS );
	
	//4. configure prescalars for the main clock (hclk, pclk1, pclk2)
	//4.1 ahb1
	RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk);
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	//4.2 apb1
	RCC->CFGR &= ~(RCC_CFGR_PPRE1_Msk);
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	//4.3 apb2
	RCC->CFGR &= ~(RCC_CFGR_PPRE2_Msk);
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
	
	//5. configure the main pll
	RCC->PLLCFGR &= ~( 0x7FFFU<<0 | 1<<16U | 1<<17U | 1<<22U );
	RCC->PLLCFGR |= ( PLL_M<<0 | PLL_N<<6 |  1<<22 );
	
	//6. enable pll and wait until ready
	RCC->CR |= RCC_CR_PLLON;
	while(!( RCC->CR & RCC_CR_PLLRDY ));
	
	//7. select the clock source
	RCC->CFGR &= ~(3U);
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
	
}
