#ifndef __STM32F4_LCD16X2_DRIVER_H
#define __STM32F4_LCD16X2_DRIVER_H

#include "lcd_GPIO_definitions.h"


/************************************** MACROS ***********************************************/

#define LCD_FUNCTION_SET												0x20U
#define LCD_FS_DATA_LENGTH_8bits										0x10U
#define LCD_FS_DATA_LENGTH_4bits										0x00U
#define LCD_FS_DISPLAY_LINES_2											0x08U
#define LCD_FS_DISPLAY_LINES_1											0x00U
#define LCD_FS_CHARACTER_FONT_5X10										0x04U
#define LCD_FS_CHARACTER_FONT_5X8										0x00U


#define LCD_DISPLAY_CONTROL												0x08U
#define LCD_DC_DISPLAY_ON												0x04U
#define LCD_DC_DISPLAY_OFF												0x00U
#define LCD_DC_CURSOR_ON												0x02U
#define LCD_DC_CURSOR_OFF												0x00U
#define LCD_DC_CURSOR_BLINK_ON											0x01U
#define LCD_DC_CURSOR_BLINK_OFF											0x00U


#define LCD_ENTRY_MODE_SET												0x04U
#define LCD_EM_INCREMENT_ADDRESS										0x02U
#define LCD_EM_DECREMENT_ADDRESS										0x00U
#define LCD_EM_DISPLAY_SHIFT_ON											0x01U
#define LCD_EM_DISPLAY_SHIFT_OFF										0x00U

#define LCD_SHIFT_CURSOR_RIGHT											0x14U
#define LCD_SHIFT_CURSOR_LEFT											0x10U
#define LCD_SHIFT_DISPLAY_RIGHT											0x1CU
#define LCD_SHIFT_DISPLAY_LEFT											0x18U


/************************************ DATA STRUCTURE ******************************************/

typedef struct {

	uint8_t dataLength;
	uint8_t displayLines;
	uint8_t characterFont;
	uint8_t var;

} lcd_config_t;




/************************************ DRIVER EXPOSED APIs *************************************/

void lcd_Init(lcd_config_t* myLCD);

void lcd_ClearScreen(void);

void lcd_ReturnHome(void);

void lcd_displayON(void);

void lcd_displayOFF(void);

void lcd_cursonON(void);

void lcd_cursorOFF(void);

void lcd_cursorBlinkON(void);

void lcd_cursorBlinkOFF(void);

void lcd_displayShiftOn(void);

void lcd_displayShiftOff(void);

void lcd_shiftCursorOrDisplayDirection(uint8_t direction);

void lcd_setCursorPosition(uint8_t addr);

void lcd_printChar(char letter);

void lcd_scrollLeft(void);

void lcd_scrollRight(void);

void lcd_scrollUP(void);

void lcd_scrollDOWN(void);



/******************************************** USEFUL FUNCTIONS ***************************************/

uint32_t findStrLen(char* str);




#endif
