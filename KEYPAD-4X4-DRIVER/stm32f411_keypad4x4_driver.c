#include "stm32f411_keypad4x4_driver.h"


void keypad_Init(void) {

	//set column pins as input
	KEYPAD_C1_PORT->MODER &= ~(3U << 2*KEYPAD_C1_PIN);
	KEYPAD_C2_PORT->MODER &= ~(3U << 2*KEYPAD_C2_PIN);
	KEYPAD_C3_PORT->MODER &= ~(3U << 2*KEYPAD_C3_PIN);
	KEYPAD_C4_PORT->MODER &= ~(3U << 2*KEYPAD_C4_PIN);
	
	//set columns with pull up resistors
	KEYPAD_C1_PORT->PUPDR &= ~(3U << 2*KEYPAD_C1_PIN);
	KEYPAD_C1_PORT->PUPDR |= (1U << 2*KEYPAD_C1_PIN);
	KEYPAD_C2_PORT->PUPDR &= ~(3U << 2*KEYPAD_C2_PIN);
	KEYPAD_C2_PORT->PUPDR |= (1U << 2*KEYPAD_C2_PIN);
	KEYPAD_C3_PORT->PUPDR &= ~(3U << 2*KEYPAD_C3_PIN);
	KEYPAD_C3_PORT->PUPDR |= (1U << 2*KEYPAD_C3_PIN);
	KEYPAD_C4_PORT->PUPDR &= ~(3U << 2*KEYPAD_C4_PIN);
	KEYPAD_C4_PORT->PUPDR |= (1U << 2*KEYPAD_C4_PIN);
	

	//set row pins as outputs
	KEYPAD_R1_PORT->MODER &= ~(3U << 2*KEYPAD_R1_PIN);
	KEYPAD_R1_PORT->MODER |= (1U << 2*KEYPAD_R1_PIN);
	KEYPAD_R2_PORT->MODER &= ~(3U << 2*KEYPAD_R2_PIN);
	KEYPAD_R2_PORT->MODER |= (1U << 2*KEYPAD_R2_PIN);
	KEYPAD_R3_PORT->MODER &= ~(3U << 2*KEYPAD_R3_PIN);
	KEYPAD_R3_PORT->MODER |= (1U << 2*KEYPAD_R3_PIN);
	KEYPAD_R4_PORT->MODER &= ~(3U << 2*KEYPAD_R4_PIN);
	KEYPAD_R4_PORT->MODER |= (1U << 2*KEYPAD_R4_PIN);
	
	
	KEYPAD_R1_PORT->ODR |= (1 << KEYPAD_R1_PIN);
	KEYPAD_R2_PORT->ODR |= (1 << KEYPAD_R2_PIN);
	KEYPAD_R3_PORT->ODR |= (1 << KEYPAD_R3_PIN);
	KEYPAD_R4_PORT->ODR |= (1 << KEYPAD_R4_PIN);
	

}


uint8_t keypad_readKeyInASCII(void) {

	while(1) {
		//make all rows high
		KEYPAD_R1_PORT->ODR |= (1 << KEYPAD_R1_PIN);
		KEYPAD_R2_PORT->ODR |= (1 << KEYPAD_R2_PIN);
		KEYPAD_R3_PORT->ODR |= (1 << KEYPAD_R3_PIN);
		KEYPAD_R4_PORT->ODR |= (1 << KEYPAD_R4_PIN);
	
	
		//clear row 1
		KEYPAD_R1_PORT->ODR &= ~(1U << KEYPAD_R1_PIN);
		if(!(GPIOD->IDR & 0x08)) {
			return '1';
		}
		else if(!(GPIOD->IDR & 0x04)) {
			return '2';
		}
		else if (!(GPIOD->IDR & 0x02)) {
			return '3';
		}
		else if (!(GPIOD->IDR & 0x01)) {
			return 'A';
		}
		
		
		//clear row 2
		KEYPAD_R1_PORT->ODR |= (1 << KEYPAD_R1_PIN);
		KEYPAD_R2_PORT->ODR &= ~(1U << KEYPAD_R2_PIN);
		if(!(GPIOD->IDR & 0x08)) {
			return '4';
		}
		else if(!(GPIOD->IDR & 0x04)) {
			return '5';
		}
		else if (!(GPIOD->IDR & 0x02)) {
			return '6';
		}
		else if (!(GPIOD->IDR & 0x01)) {
			return 'B';
		}
		
		
		//clear row 3
		KEYPAD_R2_PORT->ODR |= (1 << KEYPAD_R2_PIN);
		KEYPAD_R3_PORT->ODR &= ~(1U << KEYPAD_R3_PIN);
		if(!(GPIOD->IDR & 0x08)) {
			return '7';
		}
		else if(!(GPIOD->IDR & 0x04)) {
			return '8';
		}
		else if (!(GPIOD->IDR & 0x02)) {
			return '9';
		}
		else if (!(GPIOD->IDR & 0x01)) {
			return 'C';
		}
		
		
		//clear row 4
		KEYPAD_R3_PORT->ODR |= (1 << KEYPAD_R3_PIN);
		KEYPAD_R4_PORT->ODR &= ~(1U << KEYPAD_R4_PIN);
		if(!(GPIOD->IDR & 0x08)) {
			return '*';
		}
		else if(!(GPIOD->IDR & 0x04)) {
			return '0';
		}
		else if (!(GPIOD->IDR & 0x02)) {
			return '#';
		}
		else if (!(GPIOD->IDR & 0x01)) {
			return 'D';
		}
	
	}

}

uint8_t keypad_readKeyInHex(void) {

	while(1) {
		//make all rows high
		KEYPAD_R1_PORT->ODR |= (1 << KEYPAD_R1_PIN);
		KEYPAD_R2_PORT->ODR |= (1 << KEYPAD_R2_PIN);
		KEYPAD_R3_PORT->ODR |= (1 << KEYPAD_R3_PIN);
		KEYPAD_R4_PORT->ODR |= (1 << KEYPAD_R4_PIN);
	
	
		//clear row 1
		KEYPAD_R1_PORT->ODR &= ~(1U << KEYPAD_R1_PIN);
		if(!(GPIOD->IDR & 0x08)) {
			return 0x01;
		}
		else if(!(GPIOD->IDR & 0x04)) {
			return 0x02;
		}
		else if (!(GPIOD->IDR & 0x02)) {
			return 0x03;
		}
		else if (!(GPIOD->IDR & 0x01)) {
			return 0x0A;
		}
		
		
		//clear row 2
		KEYPAD_R1_PORT->ODR |= (1 << KEYPAD_R1_PIN);
		KEYPAD_R2_PORT->ODR &= ~(1U << KEYPAD_R2_PIN);
		if(!(GPIOD->IDR & 0x08)) {
			return 0x04;
		}
		else if(!(GPIOD->IDR & 0x04)) {
			return 0x05;
		}
		else if (!(GPIOD->IDR & 0x02)) {
			return 0x06;
		}
		else if (!(GPIOD->IDR & 0x01)) {
			return 0x0B;
		}
		
		
		//clear row 3
		KEYPAD_R2_PORT->ODR |= (1 << KEYPAD_R2_PIN);
		KEYPAD_R3_PORT->ODR &= ~(1U << KEYPAD_R3_PIN);
		if(!(GPIOD->IDR & 0x08)) {
			return 0x07;
		}
		else if(!(GPIOD->IDR & 0x04)) {
			return 0x08;
		}
		else if (!(GPIOD->IDR & 0x02)) {
			return 0x09;
		}
		else if (!(GPIOD->IDR & 0x01)) {
			return 0x0C;
		}
		
		
		//clear row 4
		KEYPAD_R3_PORT->ODR |= (1 << KEYPAD_R3_PIN);
		KEYPAD_R4_PORT->ODR &= ~(1U << KEYPAD_R4_PIN);
		if(!(GPIOD->IDR & 0x08)) {
			return 0x0E;
		}
		else if(!(GPIOD->IDR & 0x04)) {
			return 0x00;
		}
		else if (!(GPIOD->IDR & 0x02)) {
			return 0x0F;
		}
		else if (!(GPIOD->IDR & 0x01)) {
			return 0x0D;
		}
	
	}

}

