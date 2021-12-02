#ifndef __STM32F411_KEYPAD4X4_DRIVER_H
#define __STM32F411_KEYPAD4X4_DRIVER_H

#include "stm32f411xe.h"

/********************************************* DEFINE THE GPIO PORTS AND PINS USED HERE ********************************************/

#define KEYPAD_C1_PORT											GPIOD
#define KEYPAD_C1_PIN												3

#define KEYPAD_C2_PORT											GPIOD
#define KEYPAD_C2_PIN												2

#define KEYPAD_C3_PORT											GPIOD
#define KEYPAD_C3_PIN												1

#define KEYPAD_C4_PORT											GPIOD
#define KEYPAD_C4_PIN												0

#define KEYPAD_R1_PORT											GPIOD
#define KEYPAD_R1_PIN												7

#define KEYPAD_R2_PORT											GPIOD
#define KEYPAD_R2_PIN												6

#define KEYPAD_R3_PORT											GPIOD
#define KEYPAD_R3_PIN												5

#define KEYPAD_R4_PORT											GPIOD
#define KEYPAD_R4_PIN												4



/********************************************* DRIVER EXPOSED APIs ****************************************************/

void keypad_Init(void);
/*

	initializes required gpio pins as outputs or inputs with pull up resistors
	
*/

uint8_t keypad_readKeyInASCII(void);
/*

	returns the key pressed on the keypad upon function call in ASCII format.

*/

uint8_t keypad_readKeyInHex(void);
/*

	returns the key pressed in HEX format
	Note: * is taken as 0x0E and # is taken as 0x0F

*/


#endif
