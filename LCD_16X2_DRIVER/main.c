#include "stm32f4_lcd16x2_driver.h"


int main(void) {

	RCC->AHB1ENR |= (1<<3);
	
	lcd_config_t myLCD;
	myLCD.characterFont = LCD_FS_CHARACTER_FONT_5X8;
	myLCD.dataLength = LCD_FS_DATA_LENGTH_8bits;
	myLCD.displayLines = LCD_FS_DISPLAY_LINES_2;
	
	lcd_Init(&myLCD);
	
	char name[] = "Krishna Palle";
	char bp[] = "Battery   90%";
	
	for(uint32_t i=0; i<findStrLen(name); i++) {
		lcd_printChar(*(name+i));
	}
	lcd_setCursorPosition(0x40);
	for(uint32_t i=0; i<findStrLen(bp); i++) {
		lcd_printChar(*(bp+i));
	}
	
	for(uint8_t i=0; i<12; i++) {
		lcd_scrollLeft();
	}
	
	lcd_scrollLeft();
	lcd_scrollLeft();
	
	lcd_scrollUP();
	lcd_scrollDOWN();
	
	for(uint32_t i=0; i<14; i++) {
		lcd_scrollRight();
	}
	lcd_scrollUP();
	

	return 0;
}

