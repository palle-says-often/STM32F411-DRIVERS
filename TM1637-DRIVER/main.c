#include "stm32f411_tm1637_driver.h"

void delay(void);

int main(void) {

	RCC->AHB1ENR |= (1U << 3);
	
	tm1637_Init();				//initializes display with	- - - - @ brightness level 3
	delay();
	tm1637_displayOff();		//turns off display
	delay();
	tm1637_displayOn();			//turns display on
	delay();
	tm1637_putNumbers(1, 2, 3, 4, 1);		//puts 1 2:3 4 on the display
	delay();
	tm1637_setBrightness(TM1637_BRIGHTNESS_8);		//highest brightness level
	tm1637_putNumber_4Dig(5678, 0);			//puts 5 6 7 8 on the display
	delay();
	tm1637_putNumber_Custom(TM1637_DISPLAY2_ADDR, 9);		//puts 9 on display 2
	delay();
	tm1637_putChar_Custom(TM1637_DISPLAY4_ADDR, 0b01110110);	//puts H on display 4
	delay();
	tm1637_setBrightness(TM1637_BRIGHTNESS_1);			//lowest brightness level


	return 0;

}

void delay(void) {
	for(uint32_t i=0; i<2000000; i++);
}
