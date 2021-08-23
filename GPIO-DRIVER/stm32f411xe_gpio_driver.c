#include "stm32f411xe_gpio_driver.h"

/**************** HELPER FUNCTIONS FOR GPIO PIN INITIALIZATION *****************/

static void enable_clock_GPIOx(uint32_t portName) {

	RCC->AHB1ENR |= (1<<portName);
	
}

static void config_mode(GPIO_TypeDef *pGPIOx, uint32_t pinNumber, uint32_t mode) {
	
	pGPIOx->MODER &= ~( (uint32_t) 3 << (pinNumber*2 ) );
	pGPIOx->MODER |= ( mode << (pinNumber*2) );
	
}

static void config_otype(GPIO_TypeDef *pGPIOx, uint32_t pinNumber, uint32_t oType) {

	pGPIOx->OTYPER &= ~(1<<pinNumber);
	pGPIOx->OTYPER |= (oType<<pinNumber);
	
}

static void config_pupd(GPIO_TypeDef *pGPIOx, uint32_t pinNumber, uint32_t pupd) {
	
	pGPIOx->PUPDR &= ~( (uint32_t) 3<<(pinNumber*2));
	pGPIOx->PUPDR |= (pupd<<(pinNumber*2));
	
}

static void config_ospeed(GPIO_TypeDef *pGPIOx, uint32_t pinNumber, uint32_t oSpeed) {

	pGPIOx->OSPEEDR &= ~( (uint32_t) 3<<(pinNumber*2) );
	pGPIOx->OSPEEDR |= (oSpeed<<(pinNumber*2));

}

static void config_afr(GPIO_TypeDef *pGPIOx, uint32_t pinNumber, uint32_t afrNumber) {

	if(pinNumber<8) {
		pGPIOx->AFR[0] &= ~( (uint32_t) 0xF<<(pinNumber*4) );
		pGPIOx->AFR[0] |= ( afrNumber << (pinNumber*4) );
	}
	else {
		pGPIOx->AFR[1] &= ~( (uint32_t) 0xF<<( (pinNumber-8)*4 ) );
		pGPIOx->AFR[1] |= ( (uint32_t) afrNumber << ( (pinNumber-8 )*4) );
	}
	

}


/******************************************************** DRIVER EXPOSED APIs *******************************************************/


/**************** INITIALIZING GPIO PIN *****************/

void init_pin(GPIO_TypeDef *pGPIOx, GPIO_InitTypedef *pGpioInit) {
	
	//1. enable clock for the port
	enable_clock_GPIOx(pGpioInit->PortName);
	
	//2. configure the MODER
	config_mode(pGPIOx, pGpioInit->Pin, pGpioInit->Mode);
	
	//3. configure the OTYPER
	config_otype(pGPIOx, pGpioInit->Pin, pGpioInit->OType);
	
	//4. configure the PUPDR
	config_pupd(pGPIOx, pGpioInit->Pin, pGpioInit->PUPD);
	
	//5. configure the OSPEEDR
	config_ospeed(pGPIOx, pGpioInit->Pin, pGpioInit->Speed);
	
	//6. configure the AFR
	config_afr(pGPIOx, pGpioInit->Pin, pGpioInit->Alternate);
	
}



/********************** API FOR READING/WRITING TO GPIO PINS *********************/

uint8_t read_gpio_pin(GPIO_TypeDef *pGPIOx, uint32_t pinNumber) {
	
	uint8_t value;
	value = (pGPIOx->IDR >> pinNumber) & 0x00000001;
	
	return value;

}

void write_gpio_pin(GPIO_TypeDef *pGPIOx, uint32_t pinNumber, uint8_t value) {

	if(value) {
		pGPIOx->ODR |= (1<<pinNumber);
	}
	else {
		pGPIOx->ODR &= ~(1<<pinNumber);
	}

}

void toggle_gpio_pin(GPIO_TypeDef *pGPIOx, uint32_t pinNumber) {

	uint8_t value = read_gpio_pin(pGPIOx, pinNumber);
	if(value) {
		write_gpio_pin(pGPIOx, pinNumber, GPIO_PIN_RESET);
	}
	else {
		write_gpio_pin(pGPIOx, pinNumber, GPIO_PIN_SET);
	}

}

uint32_t read_multiple_gpio_pin(GPIO_TypeDef *pGPIOx, uint32_t basePin, uint32_t len) {

	uint32_t value;
	
	uint32_t mask_value = 1;
	for(uint32_t i=0; i<len; i++) {
		mask_value *= 2;
	}
	mask_value -= 1;
	
	value = ( (pGPIOx->ODR >> basePin) &  mask_value);

	return value;
}

void write_multiple_gpio_pin(GPIO_TypeDef *pGPIOx, uint32_t basePin, uint32_t value, uint32_t len) {

	uint32_t mask_value = 1;
	for(uint32_t i=0; i<len; i++) {
		mask_value *= 2;
	}
	mask_value -= 1;
	
	pGPIOx->ODR &= ~(mask_value<<basePin);
	pGPIOx->ODR |= (value<<basePin);

}

void toggle_multiple_gpio_pin(GPIO_TypeDef *pGPIOx, uint32_t basePin, uint32_t len) {

	for(uint32_t i=0; i<len; i++) {
		toggle_gpio_pin(pGPIOx, basePin+i);
	}
	
}

/*************************** INTERRUPT APIs *************************/

void config_interrupt(uint32_t pinNumber, int_edge_sel_t edge_sel) {
	
	if(edge_sel == INT_RISING_EDGE) {
		EXTI->RTSR |= 1<<pinNumber;
	}
	else if (edge_sel == INT_FALLING_EDGE) {
		EXTI->FTSR |= 1<<pinNumber;
	}
	else if (edge_sel == INT_RISING_FALLING_EDGE) {
		EXTI->FTSR |= 1<<pinNumber;
		EXTI->RTSR |= 1<<pinNumber;
	}
	else {
		
	}
	
}

void enable_interrupt(uint32_t pinNumber, IRQn_Type irqNumber) {
	
	EXTI->IMR |= 1<<pinNumber;
	NVIC_EnableIRQ(irqNumber);
	
}

void clear_interrupt (uint32_t pinNumber) {

	if(EXTI->PR & (1<<pinNumber)) {
		EXTI->PR |= 1<<pinNumber ;
	}
	
}


/************************** USEFUL DELAY FUNCTIONS **************************/


void delay_low(void) {

	for(uint32_t i=0; i<200000; i++);
	
}

void delay_medium(void) {

	delay_low();
	delay_low();
	delay_low();
	delay_low();
	delay_low();

}

void delay_high(void) {
	
	for(uint32_t i=0; i<10; i++) {
		delay_low();
	}
	
}


