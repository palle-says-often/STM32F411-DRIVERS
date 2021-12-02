#include "stm32f4_lcd16x2_driver.h"

typedef struct {

	uint8_t displayControl;
	uint8_t entryModeSet;
	uint8_t cursorPosition;

} lcd_private_t;

static lcd_private_t lcd_private;

/*************************************** USEFUL FUNCTIONS *****************************************/

uint32_t findStrLen(char* str) {
	
	uint32_t len = 0;
	while(1) {
		if(*(str+len) == '\0') {
			return len;
		}
		else {
			len++;
		}
	}

}


/***************************************** HELPER FUNCTIONS ***********************************************/

static void trigger_enable(void) {

	LCD_EN_PORT->ODR |= (1U << LCD_EN_PIN);
	for(uint32_t i=0; i<5000; i++);
	LCD_EN_PORT->ODR &= ~(1U << LCD_EN_PIN);

}

static void clearAllPins(void) {

	LCD_D0_PORT->ODR &= ~(1U << LCD_D0_PIN);
	LCD_D1_PORT->ODR &= ~(1U << LCD_D1_PIN);
	LCD_D2_PORT->ODR &= ~(1U << LCD_D2_PIN);
	LCD_D3_PORT->ODR &= ~(1U << LCD_D3_PIN);
	LCD_D4_PORT->ODR &= ~(1U << LCD_D4_PIN);
	LCD_D5_PORT->ODR &= ~(1U << LCD_D5_PIN);
	LCD_D6_PORT->ODR &= ~(1U << LCD_D6_PIN);
	LCD_D7_PORT->ODR &= ~(1U << LCD_D7_PIN);

}

static void writeToDataPins(uint8_t cmd) {

	clearAllPins();
	
	LCD_D0_PORT->ODR |= (((cmd>>0) & 0x01U) << LCD_D0_PIN);
	LCD_D1_PORT->ODR |= (((cmd>>1) & 0x01U) << LCD_D1_PIN);
	LCD_D2_PORT->ODR |= (((cmd>>2) & 0x01U) << LCD_D2_PIN);
	LCD_D3_PORT->ODR |= (((cmd>>3) & 0x01U) << LCD_D3_PIN);
	LCD_D4_PORT->ODR |= (((cmd>>4) & 0x01U) << LCD_D4_PIN);
	LCD_D5_PORT->ODR |= (((cmd>>5) & 0x01U) << LCD_D5_PIN);
	LCD_D6_PORT->ODR |= (((cmd>>6) & 0x01U) << LCD_D6_PIN);
	LCD_D7_PORT->ODR |= (((cmd>>7) & 0x01U) << LCD_D7_PIN);
	

}

static void instructionMode(void) {

	LCD_RS_PORT->ODR &= ~(1U << LCD_RS_PIN);

}

static void dataMode(void) {

	LCD_RS_PORT->ODR |= (1U << LCD_RS_PIN);

}

/*
static void readMode(void) {

	LCD_RW_PORT->ODR |= (1U << LCD_RW_PIN);

}
*/

static void writeMode(void) {

	LCD_RW_PORT->ODR &= ~(1U << LCD_RW_PIN);

}


static void lcd_initGPIO(void) {

	LCD_D0_PORT->MODER &= ~(3U << 2*LCD_D0_PIN);
	LCD_D0_PORT->MODER |= (1 << 2*LCD_D0_PIN);
	
	LCD_D1_PORT->MODER &= ~(3U << 2*LCD_D1_PIN);
	LCD_D1_PORT->MODER |= (1 << 2*LCD_D1_PIN);
	
	LCD_D2_PORT->MODER &= ~(3U << 2*LCD_D2_PIN);
	LCD_D2_PORT->MODER |= (1 << 2*LCD_D2_PIN);
	
	LCD_D3_PORT->MODER &= ~(3U << 2*LCD_D3_PIN);
	LCD_D3_PORT->MODER |= (1 << 2*LCD_D3_PIN);
	
	LCD_D4_PORT->MODER &= ~(3U << 2*LCD_D4_PIN);
	LCD_D4_PORT->MODER |= (1 << 2*LCD_D4_PIN);
	
	LCD_D5_PORT->MODER &= ~(3U << 2*LCD_D5_PIN);
	LCD_D5_PORT->MODER |= (1 << 2*LCD_D5_PIN);
	
	LCD_D6_PORT->MODER &= ~(3U << 2*LCD_D6_PIN);
	LCD_D6_PORT->MODER |= (1 << 2*LCD_D6_PIN);
	
	LCD_D7_PORT->MODER &= ~(3U << 2*LCD_D7_PIN);
	LCD_D7_PORT->MODER |= (1 << 2*LCD_D7_PIN);
	
	LCD_EN_PORT->MODER &= ~(3U << 2*LCD_EN_PIN);
	LCD_EN_PORT->MODER |= (1 << 2*LCD_EN_PIN);
	
	LCD_RW_PORT->MODER &= ~(3U << 2*LCD_RW_PIN);
	LCD_RW_PORT->MODER |= (1 << 2*LCD_RW_PIN);
	
	LCD_RS_PORT->MODER &= ~(3U << 2*LCD_RS_PIN);
	LCD_RS_PORT->MODER |= (1 << 2*LCD_RS_PIN);
	
	LCD_EN_PORT->ODR &= ~(1U << LCD_EN_PIN);

}

static void lcd_functionSet(lcd_config_t* myLCD) {

	uint8_t instruction = LCD_FUNCTION_SET;
	instruction |= (myLCD->dataLength) | (myLCD->displayLines) | (myLCD->characterFont);
	writeMode();
	instructionMode();
	writeToDataPins(instruction);
	trigger_enable();

}

static void lcd_controlDisplay(uint8_t instruction) {

	writeMode();
	instructionMode();
	writeToDataPins(instruction);
	trigger_enable();

}

static void lcd_entryModeSet(uint8_t instruction) {

	writeMode();
	instructionMode();
	writeToDataPins(instruction);
	trigger_enable();

}



/****************************************** DRIVER EXPOSED APIs *******************************************/

void lcd_Init(lcd_config_t* myLCD) {

	//init gpio
	lcd_initGPIO();
	
	//function set
	lcd_functionSet(myLCD);
	
	//display control
	lcd_private.displayControl = LCD_DISPLAY_CONTROL | LCD_DC_CURSOR_ON | LCD_DC_CURSOR_BLINK_OFF | LCD_DC_DISPLAY_ON;
	lcd_controlDisplay(lcd_private.displayControl);
	
	//clear
	lcd_ClearScreen();
	
	//entry mode set
	lcd_private.entryModeSet = LCD_ENTRY_MODE_SET | LCD_EM_INCREMENT_ADDRESS | LCD_EM_DISPLAY_SHIFT_OFF;
	lcd_entryModeSet(lcd_private.entryModeSet);
	

}

void lcd_ClearScreen(void) {

	uint8_t instruction = 0x01;
	writeMode();
	instructionMode();
	writeToDataPins(instruction);
	trigger_enable();
	lcd_private.cursorPosition = 0;

}

void lcd_ReturnHome(void) {

	uint8_t instruction = 0x02;
	writeMode();
	instructionMode();
	writeToDataPins(instruction);
	trigger_enable();
	lcd_private.cursorPosition = 0;

}

void lcd_displayON(void) {

	lcd_private.displayControl |= LCD_DC_DISPLAY_ON;
	lcd_controlDisplay(lcd_private.displayControl);

}

void lcd_displayOFF(void) {

	lcd_private.displayControl &= ~(LCD_DC_DISPLAY_ON);
	lcd_controlDisplay(lcd_private.displayControl);

}

void lcd_cursonON(void) {

	lcd_private.displayControl |= (LCD_DC_CURSOR_ON);
	lcd_controlDisplay(lcd_private.displayControl);

}

void lcd_cursorOFF(void) {

	lcd_private.displayControl &= ~(LCD_DC_CURSOR_ON);
	lcd_controlDisplay(lcd_private.displayControl);


}

void lcd_cursorBlinkON(void) {

	lcd_private.displayControl |= (LCD_DC_CURSOR_BLINK_ON);
	lcd_controlDisplay(lcd_private.displayControl);

}

void lcd_cursorBlinkOFF(void) {

	lcd_private.displayControl &= ~(LCD_DC_CURSOR_BLINK_ON);
	lcd_controlDisplay(lcd_private.displayControl);

}

void lcd_setCursorPosition(uint8_t addr) {

	writeMode();
	instructionMode();
	uint8_t instruction = 0x80;
	instruction |= addr;
	writeToDataPins(instruction);
	trigger_enable();
	lcd_private.cursorPosition = addr;

}

void lcd_printChar(char letter) {

	writeMode();
	dataMode();
	if(lcd_private.cursorPosition < 0x27) {
		writeToDataPins(letter);
		trigger_enable();
		lcd_private.cursorPosition++;
	}
	else if(lcd_private.cursorPosition == 0x27) {
		writeToDataPins(letter);
		trigger_enable();
		lcd_setCursorPosition(0x40);
	}
	else if(lcd_private.cursorPosition < 0x67) {
		writeToDataPins(letter);
		trigger_enable();
		lcd_private.cursorPosition++;
	}
	else if(lcd_private.cursorPosition == 0x67) {
		writeToDataPins(letter);
		trigger_enable();
		lcd_setCursorPosition(0);
	}
	

}

void lcd_displayShiftOn(void) {

	lcd_private.entryModeSet |= LCD_EM_DISPLAY_SHIFT_ON;
	lcd_entryModeSet(lcd_private.entryModeSet);

}

void lcd_displayShiftOff(void) {

	lcd_private.entryModeSet &= ~LCD_EM_DISPLAY_SHIFT_ON;
	lcd_entryModeSet(lcd_private.entryModeSet);

}

void lcd_shiftCursorOrDisplayDirection(uint8_t direction) {

	writeMode();
	instructionMode();
	writeToDataPins(direction);
	trigger_enable();
	if(direction == LCD_SHIFT_CURSOR_RIGHT) {
		lcd_private.cursorPosition++;
	}
	else if(direction == LCD_SHIFT_CURSOR_LEFT) {
		lcd_private.cursorPosition--;
	}
	
}

void lcd_scrollLeft(void) {

	if(lcd_private.cursorPosition>0 && lcd_private.cursorPosition <= 0x27) {
		lcd_shiftCursorOrDisplayDirection(LCD_SHIFT_CURSOR_LEFT);
		lcd_shiftCursorOrDisplayDirection(LCD_SHIFT_DISPLAY_RIGHT);
	}
	else if(lcd_private.cursorPosition == 0) {
		lcd_setCursorPosition(0x27);
		lcd_shiftCursorOrDisplayDirection(LCD_SHIFT_DISPLAY_RIGHT);
	}
	else if(lcd_private.cursorPosition>0x40 && lcd_private.cursorPosition<=0x67) {
		lcd_shiftCursorOrDisplayDirection(LCD_SHIFT_CURSOR_LEFT);
		lcd_shiftCursorOrDisplayDirection(LCD_SHIFT_DISPLAY_RIGHT);
	}
	else if(lcd_private.cursorPosition == 0x40) {
		lcd_setCursorPosition(0x67);
		lcd_shiftCursorOrDisplayDirection(LCD_SHIFT_DISPLAY_RIGHT);
	}
	
}

void lcd_scrollRight(void) {
	
	if(lcd_private.cursorPosition < 0x27) {
		lcd_shiftCursorOrDisplayDirection(LCD_SHIFT_CURSOR_RIGHT);
		lcd_shiftCursorOrDisplayDirection(LCD_SHIFT_DISPLAY_LEFT);
	}
	else if(lcd_private.cursorPosition == 0x27) {
		lcd_setCursorPosition(0);
		lcd_shiftCursorOrDisplayDirection(LCD_SHIFT_DISPLAY_LEFT);
	}
	else if(lcd_private.cursorPosition>=0x40 && lcd_private.cursorPosition<0x67) {
		lcd_shiftCursorOrDisplayDirection(LCD_SHIFT_CURSOR_RIGHT);
		lcd_shiftCursorOrDisplayDirection(LCD_SHIFT_DISPLAY_LEFT);
	}
	else if(lcd_private.cursorPosition == 0x67) {
		lcd_setCursorPosition(0x40);
		lcd_shiftCursorOrDisplayDirection(LCD_SHIFT_DISPLAY_LEFT);
	}
	
}

void lcd_scrollUP(void) {

	if(lcd_private.cursorPosition >= 0x40) {
		lcd_setCursorPosition(lcd_private.cursorPosition - 0x40);
	}

}

void lcd_scrollDOWN(void) {

	if(lcd_private.cursorPosition <= 0x27) {
		lcd_setCursorPosition(lcd_private.cursorPosition + 0x40);
	}
	
}

