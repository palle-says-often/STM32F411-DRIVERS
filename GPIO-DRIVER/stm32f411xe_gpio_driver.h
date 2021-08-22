#ifndef __STM32F411X3_HAL_GPIO_DRIVER_H
#define __STM32F411X3_HAL_GPIO_DRIVER_H

#include "stm32f411xe.h"


/**************************************************************************************************/

/*********					MACROS					***************/

//MODE REGISTER (MODER)

#define MODER_INPUT										( (uint32_t) 0)
#define MODER_OUTPUT									( (uint32_t) 1)
#define MODER_AF											( (uint32_t) 2)
#define MODER_ANALOG									( (uint32_t) 3)

// OUTPUT TYPE REGISTER (OTYPER)

#define OTYPER_PUSHPULL							( (uint32_t) 0)
#define OTYPER_OPEN_DRAIN						( (uint32_t) 1)

// OUTPUT SPEED REGISTER (OSPEEDR)

#define OSPEEDR_LOW									( (uint32_t) 0x00)
#define OSPEEDR_MEDIUM							( (uint32_t) 0x01)
#define OSPEEDR_FAST								( (uint32_t) 0x02)
#define OSPEEDR_HIGH								( (uint32_t) 0x03)

// PUPDR REGISTER (PUPDR)

#define PUPDR_NO_PUPD								( (uint32_t) 0X00)
#define PUPDR_PULL_UP								( (uint32_t) 0X01)
#define PUPDR_PULL_DOWN							( (uint32_t) 0x02)
#define PUPDR_RESERVED							( (uint32_t) 0x03)

// ALTERNATE FUNCTION REGISTERS (AFR[2])

#define AFR_AF0											( (uint32_t) 0X00)
#define AFR_AF1											( (uint32_t) 0x01)
#define AFR_AF2											( (uint32_t) 0x02)
#define AFR_AF3											( (uint32_t) 0x03)
#define AFR_AF4											( (uint32_t) 0x04)
#define AFR_AF5											( (uint32_t) 0x05)
#define AFR_AF6											( (uint32_t) 0x06)
#define AFR_AF7											( (uint32_t) 0x07)
#define AFR_AF8											( (uint32_t) 0x08)
#define AFR_AF9											( (uint32_t) 0x09)
#define AFR_AF10										( (uint32_t) 0x0A)
#define AFR_AF11										( (uint32_t) 0x0B)
#define AFR_AF12										( (uint32_t) 0x0C)
#define AFR_AF13										( (uint32_t) 0x0D)
#define AFR_AF14										( (uint32_t) 0x0E)
#define AFR_AF15										( (uint32_t) 0x0F)

/* CLOCK CONFIGURATION */

#define PORTA												( (uint32_t) 0x00)
#define PORTB												( (uint32_t) 0x01)
#define PORTC												( (uint32_t) 0x02)
#define PORTD												( (uint32_t) 0x03)

//GPIO PINS

#define GPIO_PIN_0									(uint32_t) 0
#define GPIO_PIN_1									(uint32_t) 1
#define GPIO_PIN_2									(uint32_t) 2
#define GPIO_PIN_3									(uint32_t) 3
#define GPIO_PIN_4									(uint32_t) 4
#define GPIO_PIN_5									(uint32_t) 5
#define GPIO_PIN_6									(uint32_t) 6
#define GPIO_PIN_7									(uint32_t) 7
#define GPIO_PIN_8									(uint32_t) 8
#define GPIO_PIN_9									(uint32_t) 9
#define GPIO_PIN_10									(uint32_t) 10
#define GPIO_PIN_11									(uint32_t) 11
#define GPIO_PIN_12									(uint32_t) 12
#define GPIO_PIN_13									(uint32_t) 13
#define GPIO_PIN_14									(uint32_t) 14
#define GPIO_PIN_15									(uint32_t) 15

// SET RESET VALUES

#define GPIO_PIN_SET								1
#define GPIO_PIN_RESET							0


/* GPIO INITIALIZATION */

typedef struct
{
	
	uint32_t PortName;
	uint32_t Pin;
	uint32_t Mode;
	uint32_t OType;
	uint32_t PUPD;
	uint32_t Speed;
	uint32_t Alternate;
	
} GPIO_InitTypedef;

typedef enum 
{
	
	INT_RISING_EDGE,
	INT_FALLING_EDGE,
	INT_RISING_FALLING_EDGE

} int_edge_sel_t;

/******************				APIs FOR INITIALIZING GPIO PERIPHERAL REGISTERS     **************************/


void init_pin(GPIO_TypeDef *pGPIOx, GPIO_InitTypedef *gpioInit);


/******************				APIs FOR READ/WRITE OF PINS				     **************************/

uint8_t read_gpio_pin(GPIO_TypeDef *pGPIOx, uint32_t pinNumber);

void write_gpio_pin(GPIO_TypeDef *pGPIOx, uint32_t pinNumber, uint8_t value);

void toggle_gpio_pin(GPIO_TypeDef *pGPIOx, uint32_t pinNumber);

uint32_t read_multiple_gpio_pin(GPIO_TypeDef *pGPIOx, uint32_t basePin, uint32_t len);

void write_multiple_gpio_pin(GPIO_TypeDef *pGPIOx, uint32_t basePin, uint32_t value);

void toggle_multiple_gpio_pin(GPIO_TypeDef *pGPIOx, uint32_t basePin, uint32_t len);


/****************************** GPIO INTERRUPT APIs *****************************/

void config_interrupt(uint32_t pinNumber, int_edge_sel_t edge_sel);

void enable_interrupt(uint32_t pinNumber, IRQn_Type irqNumber);

void clear_interrupt (uint32_t pinNumber);

/***************************** DELAY FUNCTIONS ***********************************/

void delay_low(void);

void delay_medium(void);

void delay_high(void);

void delay_very_high(void);



#endif
