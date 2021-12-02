#include "stm32f411xe_gpio_driver.h"

void init_peripherals(void);

int main() {

	//program to toggle all the LEDS on the discovery board (GPIOD pin 12, 13, 14, 15)
	
	//0. enable the peripheral clock for GPIOD
	/******* read more about this in the README *******/
	//RCC->AHB1ENR |= (1<<3);
	
	//1. initialize the pins
	init_peripherals();
	
	//example of how to use write_multiple_gpio_pin
	write_multiple_gpio_pin(GPIOD, GPIO_PIN_12, 0xF);
	
	while(1) {
		
		toggle_multiple_gpio_pin(GPIOD, GPIO_PIN_12, 4);
		delay_low();
		toggle_multiple_gpio_pin(GPIOD, GPIO_PIN_12, 4);
		delay_low();
		
	}
	

	return 0;
}


//using the driver to initialize peripherals
//can be done in main as well
void init_peripherals(void) {

	GPIO_InitTypedef gpioInit;
	
	gpioInit.PortName = PORTD;
	gpioInit.Pin = GPIO_PIN_12;
	gpioInit.Mode = MODER_OUTPUT;
	
	//initialize pin12
	init_pin(GPIOD, &gpioInit);
	
	//initialize pin13
	gpioInit.Pin = GPIO_PIN_13;
	init_pin(GPIOD, &gpioInit);
	
	//initialize pin14
	gpioInit.Pin = GPIO_PIN_14;
	init_pin(GPIOD, &gpioInit);
	
	//initialize pin15
	gpioInit.Pin = GPIO_PIN_15;
	init_pin(GPIOD, &gpioInit);
	
}
