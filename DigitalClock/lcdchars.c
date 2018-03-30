/***********************************************************************
 * Project name:			Digital Money Box
 * Project number:			19810328 
 * File name:				lcdchars.h
 * Description:				Implementation of the characters to display on the LCD
 * Compiler					AVR8/GNU C Compiler : 5.4.0
 * Controller:				ATmega328PA
 * Created:					2017-09-20 20:01
 * SW version				1.0
 * Author:					Jack Venturi                                                               
************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "lcdchars.h"
#include "buttons.h"
#include "clock.h"

//Declarations of global variables 
const uint8_t customChar0[8] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };	// buffer for  |
const uint8_t customChar1[8] = { 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F };	// buffer =
const uint8_t customChar2[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F };	// buffer for lower -
const uint8_t customChar3[8] = { 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };	// buffer for upper -
const uint8_t customChar4[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0E, 0x00 };	// buffer for upper dot
const uint8_t customChar5[8] = { 0x00, 0x0E, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00 };	// buffer for lower dot
const uint8_t clockchar  [8] = { 0x00, 0x0E, 0x15, 0x15, 0x17, 0x11, 0x0E, 0x00 };	// buffer for clock character
const uint8_t tempchar   [8] = { 0x04, 0x0A, 0x0A, 0x0E, 0x0E, 0x1F, 0x1F, 0x0E };	// buffer for the temperature char
const uint8_t celsiuschar[8] = { 0x08, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00 };	// buffer for the Celsius char
const uint8_t smalldots  [8] = { 0x00, 0x00, 0x04, 0x04, 0x00, 0x04, 0x04, 0x00 };	// buffer for small dots clock
const uint8_t btchar     [8] = { 0x04, 0x06, 0x05, 0x16, 0x0E, 0x15, 0x06, 0x04 };	// buffer for the Bluetooth char
const uint8_t sqbracketL [8] = { 0x00, 0x0F, 0x1F, 0x11, 0x17, 0x17, 0x17, 0x11 };	// buffer for the c char in the menu
const uint8_t sqbracketR [8] = { 0x00, 0x1f, 0x1F, 0x17, 0x17, 0x17, 0x17, 0x11 };	// buffer for the l char in the menu






/**************************************************************************************************
Description: Displays when the system, is powered on

parameters : -

return: -
***************************************************************************************************/

void display_Loading(void)
{
	
	
	lcd_string_clear();
	
	lcd_setcursor(LCD_COL2, LCD_ROW1);
	lcd_string("Loading...");
	
	for (int i = 0; i < 16; i++)
	{
		
		
		lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR2, i);
		lcd_setcursor(LCD_COL11, LCD_ROW1);
		lcd_Data((i*6/10) + ASCIICHARINDEX);
		lcd_Data((i%10) + ASCIICHARINDEX);
		lcd_setcursor(LCD_COL13, LCD_ROW1);
		lcd_string("%");
		_delay_ms(150);
		
	
	}
	
	lcd_setcursor(LCD_COL2, LCD_ROW1);
	lcd_string("    100%         ");
	_delay_ms(600);
	lcd_clear();
	lcd_setcursor(LCD_COL4, LCD_ROW2);
}


/**************************************************************************************************
Description: Display number one on LCD, uses CHAR0

parameters : Column position (LCD_COL0..LCD_COL16)

return: -
***************************************************************************************************/

void display_one(uint8_t col)
{
	
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR, col+1);
	lcd_generatechar(LCD_GC_CHAR3, customChar3, LCD_SET_DDADR, col);
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR2, col+1);
	lcd_generatechar(LCD_GC_CHAR2, customChar2, LCD_SET_DDADR2, col+2);
	lcd_generatechar(LCD_GC_CHAR2, customChar2, LCD_SET_DDADR2, col);
	
}

/**************************************************************************************************
Description: Display number two on LCD, uses CHAR1, CHAR2, CHAR3

parameters : Memory position (LCD_GC_CHAR0...LCD_GC_CHAR7),
			 row position (LCD_SET_DDADR,LCD_SET_DDADR2), column position (LCD_COL0..LCD_COL16)

return: -
***************************************************************************************************/
void display_two(uint8_t col)
{
	
	
	lcd_generatechar(LCD_GC_CHAR1, customChar1, LCD_SET_DDADR, col);
	lcd_generatechar(LCD_GC_CHAR1, customChar1, LCD_SET_DDADR, col+1);
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR, col+2);
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR2, col);
	lcd_generatechar(LCD_GC_CHAR2, customChar2, LCD_SET_DDADR2, col+1);
	lcd_generatechar(LCD_GC_CHAR2, customChar2, LCD_SET_DDADR2, col+2);

	
}

/**************************************************************************************************
Description: Display number three on LCD

parameters : Memory position (LCD_GC_CHAR0...LCD_GC_CHAR7),
			 row position (LCD_SET_DDADR,LCD_SET_DDADR2), column position (LCD_COL0..LCD_COL16)

return: -
***************************************************************************************************/
void display_three(uint8_t col)
{
	
	//======================Number three==================================================
	
	lcd_generatechar(LCD_GC_CHAR3, customChar3, LCD_SET_DDADR, col);
	lcd_generatechar(LCD_GC_CHAR1, customChar1, LCD_SET_DDADR, col+1);
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR2, col+2);
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR, col+2);
	lcd_generatechar(LCD_GC_CHAR2, customChar2, LCD_SET_DDADR2, col+1);
	lcd_generatechar(LCD_GC_CHAR2, customChar2, LCD_SET_DDADR2, col);
	//==================================================================================

	
}

/**************************************************************************************************
Description: Display number four on LCD

parameters : Memory position (LCD_GC_CHAR0...LCD_GC_CHAR7),
			 row position (LCD_SET_DDADR,LCD_SET_DDADR2), column position (LCD_COL0..LCD_COL16)

return: -
***************************************************************************************************/
void display_four(uint8_t col)
{
	
		//======================Number four==================================================
	
		
		lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR, col);
		lcd_generatechar(LCD_GC_CHAR2, customChar2, LCD_SET_DDADR, col+1);
		lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR, col+2);
		lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR2, col+2);
		
		//==================================================================================

	
}

/**************************************************************************************************
Description: Display number five on LCD

parameters : Memory position (LCD_GC_CHAR0...LCD_GC_CHAR7),
			 row position (LCD_SET_DDADR,LCD_SET_DDADR2), column position (LCD_COL0..LCD_COL16)

return: -
***************************************************************************************************/
void display_five(uint8_t col)
{
	
	//======================Number five==================================================
	
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR, col);
	lcd_generatechar(LCD_GC_CHAR1, customChar1, LCD_SET_DDADR, col+1);
	lcd_generatechar(LCD_GC_CHAR1, customChar1, LCD_SET_DDADR, col+2);
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR2, col+2);
	lcd_generatechar(LCD_GC_CHAR2, customChar2, LCD_SET_DDADR2, col+1);
	lcd_generatechar(LCD_GC_CHAR2, customChar2, LCD_SET_DDADR2, col);
	
	//==================================================================================

	
}

/**************************************************************************************************
Description: Display number six on LCD

parameters : Memory position (LCD_GC_CHAR0...LCD_GC_CHAR7),
			 row position (LCD_SET_DDADR,LCD_SET_DDADR2), column position (LCD_COL0..LCD_COL16)

return: -
***************************************************************************************************/
void display_six(uint8_t col)
{
	
	
//======================Number six==================================================
	
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR, col);
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR2, col);
	lcd_generatechar(LCD_GC_CHAR1, customChar1, LCD_SET_DDADR, col+1);
	lcd_generatechar(LCD_GC_CHAR1, customChar1, LCD_SET_DDADR, col+2);
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR2, col+2);
	lcd_generatechar(LCD_GC_CHAR2, customChar2, LCD_SET_DDADR2, col+1);
//==================================================================================
	
}
//Starts the memory again
/**************************************************************************************************
Description: Display number seven on LCD

parameters : Memory position (LCD_GC_CHAR0...LCD_GC_CHAR7),
			 row position (LCD_SET_DDADR,LCD_SET_DDADR2), column position (LCD_COL0..LCD_COL16)

return: -
***************************************************************************************************/
void display_seven(uint8_t col)
{
	
	//======================Number seven==================================================
	
	lcd_generatechar(LCD_GC_CHAR3, customChar3, LCD_SET_DDADR, col);
	lcd_generatechar(LCD_GC_CHAR3, customChar3, LCD_SET_DDADR, col+1);
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR, col+2);
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR2, col+2);

	//==================================================================================
	
}

/**************************************************************************************************
Description: Display number eight on LCD

parameters : Memory position (LCD_GC_CHAR0...LCD_GC_CHAR7),
			 row position (LCD_SET_DDADR,LCD_SET_DDADR2), column position (LCD_COL0..LCD_COL16)

return: -
***************************************************************************************************/
void display_eight(uint8_t col)
{
	
	
	//======================Number eight==================================================
	
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR, col);
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR2, col);
	lcd_generatechar(LCD_GC_CHAR1, customChar1, LCD_SET_DDADR, col+1);
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR, col+2);
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR2, col+2);
	lcd_generatechar(LCD_GC_CHAR2, customChar2, LCD_SET_DDADR2, col+1);
	//==================================================================================

	
}


/**************************************************************************************************
Description: Display number nine on LCD

parameters : Memory position (LCD_GC_CHAR0...LCD_GC_CHAR7),
			 row position (LCD_SET_DDADR,LCD_SET_DDADR2), column position (LCD_COL0..LCD_COL16)

return: -
***************************************************************************************************/
void display_nine(uint8_t col)
{
	
	//======================Number nine==================================================
		
		lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR, col);
		lcd_generatechar(LCD_GC_CHAR1, customChar1, LCD_SET_DDADR, col+1);
		lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR, col+2);
		lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR2, col+2);
	

	//==================================================================================

	
}

/**************************************************************************************************
Description: Display number zero on LCD

parameters : Memory position (LCD_GC_CHAR0...LCD_GC_CHAR7),
			 row position (LCD_SET_DDADR,LCD_SET_DDADR2), column position (LCD_COL0..LCD_COL16)

return: -
***************************************************************************************************/
void display_zero(uint8_t col)
{
	
	//======================Number zero==================================================
	
	
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR, col);
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR2, col);
	lcd_generatechar(LCD_GC_CHAR3, customChar3, LCD_SET_DDADR, col+1);
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR, col+2);
	lcd_generatechar(LCD_GC_CHAR0, customChar0, LCD_SET_DDADR2, col+2);
	lcd_generatechar(LCD_GC_CHAR2, customChar2, LCD_SET_DDADR2, col+1);


	//==================================================================================
	
	
}

/**************************************************************************************************
Description: Display dots on LCD

parameters : 

return: -
***************************************************************************************************/
void display_dots(void)
{
	

	lcd_generatechar(LCD_GC_CHAR4, customChar4, LCD_SET_DDADR, LCD_COL7);
	lcd_generatechar(LCD_GC_CHAR5, customChar5, LCD_SET_DDADR2, LCD_COL7);
	_delay_ms(400);
	lcd_setcursor(LCD_COL7, LCD_ROW1);
	lcd_string(" ");
	lcd_setcursor(LCD_COL7, LCD_ROW2);
	lcd_string(" ");
	_delay_ms(400);
	
	
	

}


/**************************************************************************************************
Description: Display the small dots on the LCD

parameters : 

return: -
***************************************************************************************************/

void display_smalldots(void)
{
	
	lcd_generatechar(LCD_GC_CHAR6, smalldots, LCD_SET_DDADR, LCD_COL4);
	_delay_ms(400);
	lcd_setcursor(LCD_COL4, LCD_ROW1);
	lcd_string(" ");
	_delay_ms(400);
	
}


/**************************************************************************************************
Description: Display the menu bar on the LCD

parameters : 

return: -
***************************************************************************************************/

void display_menu_bar(void)
{
	
	lcd_generatechar(LCD_GC_CHAR0, btchar, LCD_SET_DDADR2, LCD_COL1);
	lcd_generatechar(LCD_GC_CHAR1, clockchar, LCD_SET_DDADR2, LCD_COL7);
	lcd_generatechar(LCD_GC_CHAR2, tempchar, LCD_SET_DDADR2, LCD_COL13);
	


	
	if (dispclocktemp)
	{
			
		lcd_setcursor(LCD_COL0, LCD_ROW2);
		lcd_string("[");
		lcd_setcursor(LCD_COL2, LCD_ROW2);
		lcd_string("]");
		lcd_setcursor(LCD_COL6, LCD_ROW2);
		lcd_string("[");
		lcd_setcursor(LCD_COL8, LCD_ROW2);
		lcd_string("]");
		lcd_setcursor(LCD_COL12, LCD_ROW2);
		lcd_string(">");
		lcd_setcursor(LCD_COL14, LCD_ROW2);
		lcd_string("<");
				
			
	}
	
	if (dispbluetooth)
	{
			
		lcd_setcursor(LCD_COL0, LCD_ROW2);
		lcd_string(">");
		lcd_setcursor(LCD_COL2, LCD_ROW2);
		lcd_string("<");
		lcd_setcursor(LCD_COL6, LCD_ROW2);
		lcd_string("[");
		lcd_setcursor(LCD_COL8, LCD_ROW2);
		lcd_string("]");
		lcd_setcursor(LCD_COL12, LCD_ROW2);
		lcd_string("[");
		lcd_setcursor(LCD_COL14, LCD_ROW2);
		lcd_string("]");
			
	}
	
	

}