#ifndef __STM32F411_TM1637_DRIVER_H
#define __STM32F411_TM1637_DRIVER_H


#include "stm32f411xe.h"

/********************************************** GPIO DEFINITIONS ****************************************/

#define CLK_PORT							GPIOD
#define CLK_PIN								1

#define DIO_PORT							GPIOD
#define DIO_PIN								0


/********************************************** TM1637 COMMANDS DEFINITIONS *********************************/

// BRIGHTNESS SETTINGS

#define TM1637_BRIGHTNESS_1					0x88
#define TM1637_BRIGHTNESS_2					0x89
#define TM1637_BRIGHTNESS_3					0x8A
#define TM1637_BRIGHTNESS_4					0x8B
#define TM1637_BRIGHTNESS_5					0x8C
#define TM1637_BRIGHTNESS_6					0x8D
#define TM1637_BRIGHTNESS_7					0x8E
#define TM1637_BRIGHTNESS_8					0x8F

// DISPLAY CONTROL

#define TM1637_DISPLAY_ON					0x88
#define TM1637_DISPLAY_OFF					0X80

// REGISTER ADDRESSES

#define TM1637_DISPLAY1_ADDR				0XC0
#define TM1637_DISPLAY2_ADDR				0XC1
#define TM1637_DISPLAY3_ADDR				0XC2
#define TM1637_DISPLAY4_ADDR				0XC3


/********************************************** GPIO STATE DEFINITIONS *************************************/

#define CLK_LOW()							( CLK_PORT->ODR &= ~(1U << CLK_PIN) )
#define CLK_HIGH()							( CLK_PORT->ODR |= (1U << CLK_PIN) )

#define DIO_LOW()							( DIO_PORT->ODR &= ~(1U << DIO_PIN) )
#define DIO_HIGH()							( DIO_PORT->ODR |= (1U << DIO_PIN) )


/********************************************* APIs *************************************************/

void tm1637_Init(void);
/*
 *	This function initializes the CLK and DIO pins as OUTPUTS in Open drain mode with pull up registers
 *	Then the TM1637 display is initialized with default brightness set to 3/8
 *	Lowest brightness setting is at TM1637_BRIGHTNESS_1 AND BRIGHTEST SETTING IS OBTAINED AT TM1637_BRIGHTNESS_8
 *	After the initialization, - - - - is shown on the display
 *
 */

void tm1637_displayOn(void);
/*
 *
 * Turns on the TM1637 display, if turned off previously
 *
 */

void tm1637_displayOff(void);
/*
 *
 * Turns of the display, doesn't remove the data from the registers
 *
 */

void tm1637_setBrightness(uint8_t intensity);
/*
 *
 * The intensity variable can take 8 values
 * TM1637_BRIGHTNESS_1 is the lowest brightness setting (dimmest)
 * TM1637_BRIGHTNESS_8 is the highest brightness setting (highest)
 * Please use the function as shown below
 *
 * tm1637_setBrightness(TM1637_BRIGHTNESS_6);
 *
 */

void tm1637_showColon(void);
/*
 *
 * Puts on the colon between display 2 and display 3 if hidden
 *
 */

void tm1637_hideColon(void);
/*
 *
 * Hides the colon if active
 *
 */

void tm1637_putNumbers(uint8_t dig1, uint8_t dig2, uint8_t dig3, uint8_t dig4, uint8_t colon);
/*
 *
 * Give 4 numbers (in decimal or hexadecimal) as inputs along with another colon input
 * dig1 corresponds to the 1st display from the left
 * dig4 corresponds to the 4th display from the left
 *
 * if colon = 1, colon is displayed
 * if colon = 0, colon is hidden
 *
 */

void tm1637_putNumber_4Dig(uint32_t num, uint8_t colon);
/*
 *
 * give a number in hex or decimal to be displayed on the screen
 * Example:		tm1637_putNumber_4Dig(1234, 1);		// displays 1234 on the display along with a colon
 *
 */

void tm1637_putNumber_Custom(uint8_t addr, uint8_t num);
/*
 *
 * This allows you to put a number in a given address
 * Example:		tm1637_putNumber_Custom(TM1637_DISPLAY4_ADDR, 1);	//displays 1 on the 4th display from the left
 *
 */

void tm1637_putChar_Custom(uint8_t addr, uint8_t hgfedcba);
/*
 *
 * This allows you to put any character (or alphabet beyond F) on any display
 * The input must be in the order described in the argument (h->a) and the h bit is always 0.
 * Refer to 7-segment display diagrams for more ideas.
 * Example:		tm1637_putChar_Custom(TM1637_DISPLAY3_ADDR, 0b00000110);	//displays 1 on the 3rd display
 *
 */



#endif
