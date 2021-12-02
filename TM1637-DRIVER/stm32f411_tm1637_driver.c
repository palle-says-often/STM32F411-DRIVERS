#include "stm32f411_tm1637_driver.h"


/*************************************************** HELPFUL DATA STRUCTURES ********************************************/
typedef struct {
	uint8_t currentDisplay2;
	uint8_t currentBrightness;
} tm1637_private_t;

static tm1637_private_t tm1637_private;

static uint8_t hex2seg[16] = {
		0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
};


/******************************************************** HELPER FUNCTIONS *********************************************/

static void tm1637_delay_Xusec(uint8_t x_sec) {

	for(uint8_t i=0; i<3*x_sec; i++);

}

static void tm1637_start(void) {

	CLK_HIGH();
	DIO_HIGH();
	tm1637_delay_Xusec(2);
	DIO_LOW();	

}

static void tm1637_stop(void) {

	CLK_LOW();
	DIO_LOW();
	tm1637_delay_Xusec(2);
	CLK_HIGH();
	tm1637_delay_Xusec(2);
	DIO_HIGH();

}

static void tm1637_getAck(void) {

	CLK_LOW();
	tm1637_delay_Xusec(2);		//dio will be pulled down by the display during this delay
	CLK_HIGH();
	tm1637_delay_Xusec(2);
	CLK_LOW();

}

static void tm1637_writeByte(uint8_t put_byte) {

	for(uint8_t i=0; i<8; i++) {
	
		CLK_LOW();
		if((put_byte & 0x01U) == 0) {
			DIO_LOW();
		}
		else {
			DIO_HIGH();
		}
	
		tm1637_delay_Xusec(2);
		put_byte >>= 1;
		CLK_HIGH();
		tm1637_delay_Xusec(2);
	
	}

}

static void tm1637_writeCmd(uint8_t cmd) {
		
	tm1637_start();
	tm1637_delay_Xusec(2);
	tm1637_writeByte(cmd);
	tm1637_getAck();
	tm1637_stop();

}


/******************************************************* APIs ******************************************************/

void tm1637_Init(void) {

	//initialize GPIO with pull up resistors
	
	//configure mode as output
	CLK_PORT->MODER &= ~(3U << 2*CLK_PIN);
	CLK_PORT->MODER |= (1U << 2*CLK_PIN);
	DIO_PORT->MODER &= ~(3U << 2*DIO_PIN);
	DIO_PORT->MODER |= (1U << 2*DIO_PIN);
	
	//configure output type as open drain
	CLK_PORT->OTYPER |= (1U << CLK_PIN);
	DIO_PORT->OTYPER |= (1U << DIO_PIN);
	
	//set up pull up resistors for CLK and DIO pins
	CLK_PORT->PUPDR &= ~(3U << 2*CLK_PIN);
	CLK_PORT->PUPDR |= (1U << 2*CLK_PIN);
	DIO_PORT->PUPDR &= ~(3U << 2*DIO_PIN);
	DIO_PORT->PUPDR |= (1U << 2*DIO_PIN);
	
	//set write mode with auto increment (normal mode)
	tm1637_writeCmd(0x40);
	tm1637_displayOff();

	//		- - - - 	to be displayed
	for(uint8_t i=0; i<4; i++) {
		tm1637_putChar_Custom(0xC0+i, 0x40);
	}
	
	//set display on with default brightness
	tm1637_displayOn();
	tm1637_setBrightness(TM1637_BRIGHTNESS_3);

}

void tm1637_displayOn(void) {

	tm1637_writeCmd(TM1637_DISPLAY_ON | tm1637_private.currentBrightness);

}


void tm1637_displayOff(void) {

	tm1637_writeCmd(TM1637_DISPLAY_OFF);

}


void tm1637_setBrightness(uint8_t intensity) {

	tm1637_writeCmd(intensity);
	tm1637_private.currentBrightness = intensity;

}


void tm1637_showColon(void) {

	if((tm1637_private.currentDisplay2 & 0x80U) == 0) {
		tm1637_private.currentDisplay2 |= 0x80U;
		tm1637_putChar_Custom(0xC1, tm1637_private.currentDisplay2);
	}

}


void tm1637_hideColon(void) {

	if((tm1637_private.currentDisplay2 >> 7) == 1) {
		tm1637_private.currentDisplay2 &= ~(0x80U);
		tm1637_putChar_Custom(0xC1, tm1637_private.currentDisplay2);
	}

}


void tm1637_putNumber_4Dig(uint32_t num, uint8_t colon) {

	uint8_t thousands = (uint8_t)( num / 1000);
	num = num % 1000;
	uint8_t hundreds = (uint8_t) (num / 100);
	num = num % 100;
	uint8_t tens = (uint8_t) (num / 10);
	num = num%10;
	uint8_t ones = (uint8_t) num;
	
	tm1637_putNumbers(thousands, hundreds, tens, ones, colon);
	tm1637_private.currentDisplay2 = hex2seg[hundreds];

}


void tm1637_putNumbers(uint8_t dig1, uint8_t dig2, uint8_t dig3, uint8_t dig4, uint8_t colon) {

	tm1637_start();
	tm1637_delay_Xusec(2);
	tm1637_writeByte(0xC0);
	tm1637_getAck();
	tm1637_writeByte(hex2seg[dig1]);
	tm1637_getAck();
	if(colon) {
		tm1637_writeByte(hex2seg[dig2] | 0x80);
	}
	else {
		tm1637_writeByte(hex2seg[dig2]);
	}
	tm1637_getAck();
	tm1637_writeByte(hex2seg[dig3]);
	tm1637_getAck();
	tm1637_writeByte(hex2seg[dig4]);
	tm1637_getAck();
	tm1637_stop();
	
	tm1637_private.currentDisplay2 = hex2seg[dig2];

}


void tm1637_putNumber_Custom(uint8_t addr, uint8_t num) {

	tm1637_start();
	tm1637_delay_Xusec(2);
	tm1637_writeByte(addr);
	tm1637_getAck();
	tm1637_writeByte(hex2seg[num]);
	tm1637_getAck();
	tm1637_stop();
	
	if(addr == 0xC1) {
		tm1637_private.currentDisplay2 = hex2seg[num];
	}

}


void tm1637_putChar_Custom(uint8_t addr, uint8_t hgfedcba) {
	tm1637_start();
	tm1637_delay_Xusec(2);
	tm1637_writeByte(addr);
	tm1637_getAck();
	tm1637_writeByte(hgfedcba);
	tm1637_getAck();
	tm1637_stop();
	
	if(addr == 0xC1) {
		tm1637_private.currentDisplay2 = hgfedcba;
	}
}

