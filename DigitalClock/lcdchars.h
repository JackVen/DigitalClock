/***********************************************************************
 * Project name:			Digital Clock
 * Project number:			19810328 
 * File name:				lcdchars.h
 * Description:				Implementation of characters to display on the LCD
 * Compiler					AVR8/GNU C Compiler : 5.4.0
 * Controller:				ATmega328PA
 * Created:					2017-09-20 20:01
 * SW version				1.0
 * Author:					Jack Venturi                                                               
************************************************************************/


#ifndef LCDCHARS_H_
#define LCDCHARS_H_


//Global variables
const uint8_t customChar0[8]; // buffer for  |
const uint8_t customChar1[8]; // buffer =
const uint8_t customChar2[8]; // buffer for lower -
const uint8_t customChar3[8]; // buffer for upper -
const uint8_t customChar4[8]; // buffer for upper dot
const uint8_t customChar5[8]; // buffer for lower dot
const uint8_t clockchar  [8]; // buffer for clock character
const uint8_t tempchar   [8]; // buffer for the temperature char
const uint8_t celsiuschar[8];// buffer for the Celsius char
const uint8_t smalldots  [8];	// buffer for small dots clock
const uint8_t btchar     [8];	// buffer for the Bluetooth char
const uint8_t sqbracketL [8];	// buffer for the c char in the menu
const uint8_t sqbracketR [8];	// buffer for the l char in the menu

/*************************************************
			Function Prototypes                                               
*************************************************/

void display_Introanimation(void);		//Displays DMB sign
void display_Loading(void);				//Display loading text		
void display_one(uint8_t col);			//Display #1 on LCD
void display_two(uint8_t col);			//Display #2 on LCD
void display_three(uint8_t col);		//Display #3 on LCD
void display_four(uint8_t col);			//Display #4 on LCD
void display_five(uint8_t col);			//Display #5 on LCD
void display_six(uint8_t col);			//Display #6 on LCD
void display_seven(uint8_t col);		//Display #7 on LCD
void display_eight(uint8_t col);		//Display #8 on LCD
void display_nine(uint8_t col);			//Display #9 on LCD
void display_zero(uint8_t col);			//Display #0 on LCD
void display_dots(void);				//Display clock dots
void display_celsiuschar(void);			//Display Celsius character
void display_smalldots(void);			//Display small dots for the clock
void display_menu_bar(void);			//Display initial menu

#endif 