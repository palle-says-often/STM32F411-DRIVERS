
#include "stm32f411_keypad4x4_driver.h"

int main(void) {

	
	//enable the gpiod peripheral
	RCC->AHB1ENR |= (1<<3);
	
	keypad_Init();
	
	uint8_t phoneNumber[10];
	
	for(uint8_t i=0; i<10; i++) {
	
		*(phoneNumber+i) = keypad_readKeyInASCII();
	
	}
	
	
	return 0;

}

