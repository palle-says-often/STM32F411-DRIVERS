#include "stm32f411xe_maxClkConfig.h"


int main(void) {

	sysclockConfig();
	
	RCC->AHB1ENR |= 1<<3;
	GPIOD->MODER |= 1<<24;
	GPIOD->ODR |= 1<<12;
	
	while(1);
	
	return 0;
}

