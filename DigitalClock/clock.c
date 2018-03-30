/***********************************************************************
 * Project name:			Digital Clock 
 * Project number:			19810328 
 * File name:				clock.c
 * Description:				Implementation of the clock, (when green buttons is pressed) 
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
#include "clock.h"
#include "rtc.h"
#include "twi_master.h"




/************************************************************************/
/* Displays the first digit on the clock  */
/************************************************************************/

void FirstDigit(uint8_t hour1)
{			
	switch(hour1)
	{
	
	case 0:
		display_zero(LCD_COL0);	
	break;
	
	case 1:
		display_one(LCD_COL0);
	break;
	
	case 2:
		display_two(LCD_COL0);		
	break;
	
	default:
		display_zero(LCD_COL0);
	break;
			
	}
		
}

/************************************************************************/
/* Displays the second digit on the clock                                */
/************************************************************************/
void SecondDigit(uint8_t hour2)
{

	switch(hour2)
	{

	case 0:
		display_zero(LCD_COL4);
	break;
	
	case 1:
		display_one(LCD_COL4);
	break;
	
	case 2:
		display_two(LCD_COL4);
	break;
	
	case 3:
		display_three(LCD_COL4);
	break;
	
	case 4:
		display_four(LCD_COL4);
	break;
	
	case 5:
		display_five(LCD_COL4);
	break;
	
	case 6:
		display_six(LCD_COL4);
	break;
	
	case 7:
		display_seven(LCD_COL4);
	break;
	
	case 8:
		display_eight(LCD_COL4);
	break;
	
	case 9:
		display_nine(LCD_COL4);
	break;
	
	default:
		display_zero(LCD_COL4);
	break;
	}
}

/************************************************************************/
/* Displays the third digit on the clock                                */
/************************************************************************/
void ThirdDigit(uint8_t min1)
{
	
	switch(min1)
	{
	
	case 0:
		display_zero(LCD_COL8);
	break;
	
	case 1:
		display_one(LCD_COL8);
	break;
	
	case 2:
		display_two(LCD_COL8);
	break;
	
	case 3:
		display_three(LCD_COL8);
	break;
	
	case 4:
		display_four(LCD_COL8);
	break;
	
	case 5:
		display_five(LCD_COL8);
	break;
	
	default:
		display_zero(LCD_COL8);
	break;
	
	

	}
}

/************************************************************************/
/* Displays the Fourth digit on the clock                                */
/************************************************************************/
void FourthDigit(uint8_t min2)
{
	
	
	switch(min2)
	{
		
	
	case 0:
		display_zero(LCD_COL12);
	break;
		
	case 1:
		display_one(LCD_COL12);
	break;
	
	case 2:
		display_two(LCD_COL12);
	break;
	
	case 3:
		display_three(LCD_COL12);
	break;
	
	case 4:
		display_four(LCD_COL12);
	break;
	
	case 5:
		display_five(LCD_COL12);
	break;
	
	case 6:
		display_six(LCD_COL12);
	break;
	
	case 7:
		display_seven(LCD_COL12);
	break;
	
	case 8:
		display_eight(LCD_COL12);
	break;
	
	case 9:
		display_nine(LCD_COL12);
	break;	
	
	default:
		display_zero(LCD_COL12);
	break;
	
	}
	
}

/************************************************************************/
/* Displays the all four digits together on the LCD                              */
/************************************************************************/
void display_clock(uint8_t hour, uint8_t min)
{
	
		
			
		lcd_setcursor(LCD_COL0, LCD_ROW1);			//Set the LCD cursor at desire position
		lcd_string("   ");							//Clear the chars at desire position
		lcd_setcursor(LCD_COL0, LCD_ROW2);		
		lcd_string("   ");
		FirstDigit(hour/10);						//Divide the hour by 10 to subtract the first digit, e.g. 20/10 = 2
			
		lcd_setcursor(LCD_COL3, LCD_ROW1);			
		lcd_string("   ");							
		lcd_setcursor(LCD_COL3, LCD_ROW2);
		lcd_string("   ");
		SecondDigit(hour%10);					   //Modulus the hour by 10 to subtract the second digit , e.g. 20%10 = 0 
		
		
			
		lcd_setcursor(LCD_COL8, LCD_ROW1);			//Set the LCD cursor at desire position
		lcd_string("   ");							//Clear the chars at desire position
		lcd_setcursor(LCD_COL8, LCD_ROW2);
		lcd_string("   ");
		ThirdDigit(min/10);							//Divide the hour by 10 to subtract the first digit, e.g. 20/10 = 2
			
		lcd_setcursor(LCD_COL11, LCD_ROW1);
		lcd_string("    ");
		lcd_setcursor(LCD_COL11, LCD_ROW2);
		lcd_string("    ");
		FourthDigit(min%10);						  //Modulus the hour by 10 to subtract the second digit , e.g. 20%10 = 0 
			
		

}


/************************************************************************/
/* Display clock and temperature at the first row in the LCD            */
/************************************************************************/
void display_clocktemp(uint8_t hour, uint8_t min, uint8_t temp)
{
	
	lcd_setcursor(LCD_COL0, LCD_ROW1);											//Set the cursor at the beginning of the display
	lcd_string("               ");												//Clear LCD
	lcd_generatechar(LCD_GC_CHAR1, clockchar, LCD_SET_DDADR, LCD_COL0);			//Generate the clock character
	lcd_setcursor(LCD_COL2, LCD_ROW1);											//Set cursor at specific point
	lcd_Data(hour/10 + ASCIICHARINDEX);											//Print the hour decimal variable + ASCII index
	lcd_Data(hour%10 + ASCIICHARINDEX);											//...print remainder of variable hour
	
	
	
	lcd_setcursor(LCD_COL5, LCD_ROW1);											//Same as above
	lcd_Data(min/10 + ASCIICHARINDEX);											//...
	lcd_Data(min%10 + ASCIICHARINDEX);											//...
	
	
	lcd_generatechar(LCD_GC_CHAR2, tempchar, LCD_SET_DDADR, LCD_COL9);			//Generate the temperature character
	lcd_setcursor(LCD_COL11, LCD_ROW1);											//Same as above
	lcd_Data(temp/10 + ASCIICHARINDEX);
	lcd_Data(temp%10 + ASCIICHARINDEX);

	
	lcd_generatechar(LCD_GC_CHAR3, celsiuschar, LCD_SET_DDADR, LCD_COL13);		//Genereate the celsius character
	lcd_setcursor(LCD_COL14, LCD_ROW1);
	lcd_string("C");
	
	
	
	
}