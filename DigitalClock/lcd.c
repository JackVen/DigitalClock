/**********************************************************/
 /* Project name:			Digital Clock
 * Project number:			19810328 
 * File name:				lcd.c
 * Description:				Implementation of the LCD 1602A
 * Compiler					AVR8/GNU C Compiler : 5.4.0
 * Controller:				ATmega328PA
 * Created:					2017-09-20 20:01
 * SW version				1.0
 * Author:					Jack Venturi
***********************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "lcdchars.h"

//================================================
//Description: Sends an enable pulse to the LCD
//================================================
 void lcd_Enable(void)
{
	
	PORTB |=  (1 << LCD_EN);					//High pulse state
	_delay_us(LCD_ENABLE_US);					//wait
	PORTB &= ~(1 << LCD_EN);					//Low pulse state
	
}

//================================================
//Description: Sends 4-bit data to the LCD
//================================================
void lcd_Out(uint8_t data)
{
	data &= 0xF0;								// Mask upper 4-Bit in data
	
	LCD_PORTD &= ~(0xF0 >> (4 - LCD_D4));		// Delete upper mask in LCD PORT
	LCD_PORTD |= (data >> (4 - LCD_D4));		// Send the 4-bit data
	lcd_Enable();								// Enable LCD latch

}

//================================================
//Description: Sends LCD-commands to the LCD
//================================================
void lcd_Cmd(uint8_t data)
{
	PORTB &= ~(1<<LCD_RS);						// Send data command, RS=0
	
	lcd_Out(data);								// Send upper 4 bits to PORT D
	lcd_Out(data << 4 );						// Then lower 4 bits to PORT D
	_delay_us(LCD_COMMAND_US);
}

//================================================
//Description: Sends 8-bit data to print on the LCD
//================================================
void lcd_Data( uint8_t data )
{
	PORTB |= (1 << LCD_RS);						// Send print data to LCD, RS=1
	
	lcd_Out(data);								// Send upper data nibble
	lcd_Out(data << 4);						// Send lower data nibble
	_delay_us(LCD_WRITEDATA_US);							
}

//================================================
//Description: Clear LCD function
//================================================
void lcd_clear( void )
{
	lcd_Cmd(0x01);
	_delay_ms(LCD_CLEAR_DISPLAY_MS);
	
}

//================================================
//Description: Clears the LCD (faster mode)
//================================================
void lcd_string_clear(void)
{
	lcd_setcursor(LCD_COL0, LCD_ROW1);
	lcd_string("                 ");
	lcd_setcursor(LCD_COL0, LCD_ROW2);
	lcd_string("                 ");
}

//================================================
//Description: Write a string to the LCD
//================================================
void lcd_string( const char *data )
{
	while( *data != '\0' )
	lcd_Data( *data++ );
}



//==================================================
//Description: Send the cursor home command
//==================================================
void lcd_home( void )
{
	lcd_Cmd( LCD_CURSOR_HOME );
	_delay_ms( LCD_CURSOR_HOME_MS );
}


//==================================================
//Description: Sets the cursor in column x (0..15) Line y (1..2)
//==================================================
 
void lcd_setcursor(uint8_t x, uint8_t y)
{
    uint8_t data;
 
    switch (y)
    {
        case 1:    // 1. Row		Line 1
            data = LCD_SET_DDADR + LCD_DDADR_LINE1 + x;
            break;
 
        case 2:    // 2. Row		Line 2
            data = LCD_SET_DDADR + LCD_DDADR_LINE2 + x;
            break;
 
 
        default:
            return;                                   // default case
    }
 
    lcd_Cmd(data);
}

/************************************************************************
Description: Write a character into the character generator RAM                                              
************************************************************************/

void lcd_generatechar( uint8_t startaddress, const uint8_t *data, uint8_t line, uint8_t column){
	

    // Set the start position of the character 0,1,2,3,4,5,6,7
    lcd_Cmd( LCD_SET_CGADR | (startaddress << 3) ); 
    
    //Bit patterns
    for ( uint8_t i=0; i<8; i++ )
    {
	    lcd_Data( data[i] );
    }
	
	lcd_Cmd(line + column); // Set DRAM (Line1), address on the LCD where the bit patterns are displayed
	lcd_Data(startaddress);	// Display the bit pattern on the stored address
	
  
    
}
/************************************************************************/
/* Set the cursor to a certain position and prints a string				*/
/************************************************************************/
void lcd_setcurstring(uint8_t x, uint8_t y, const char *data)
{
	lcd_setcursor(x, y);
	lcd_string(data);
}


//==================================================
//Description: Initialization of the LCD
//==================================================

void lcd_Init(void)
{
	
	//Pins in PORT D and PORT B as outputs
	DDRD |=  (0X0F << LCD_D4);
	DDRB |= (1 << LCD_RS) | (1 << LCD_EN);
	
	//Initialize pins in PORT D and PORT B as Zero
	PORTB &= ~(1 << LCD_EN);
	PORTB &= ~(1 << LCD_RS);  
	LCD_PORTD &= ~(0x0F << LCD_D4);  
	
	
	//===============Start up sequence==========================	
	 _delay_ms(LCD_BOOTUP_MS);								//Power on delay
	 
	 lcd_Out(LCD_SOFT_RESET);								//Send first start up
	 _delay_ms(LCD_SOFT_RESET_MS1);			
	 
	 lcd_Enable();											//Send second start up					
	 _delay_ms(LCD_SOFT_RESET_MS2);
	 
	 lcd_Enable();											//Send third start up
	 _delay_ms(LCD_SOFT_RESET_MS3);
	
	 lcd_Out(LCD_SET_FUNCTION | LCD_FUNCTION_4BIT);			// 4-bit mode on
	 _delay_ms(LCD_SET_4BITMODE_MS);
	
	 lcd_Cmd(LCD_SET_FUNCTION | LCD_FUNCTION_4BIT | LCD_FUNCTION_2LINE | LCD_FUNCTION_5X7);					// 4-bit mode / 2 lines / 5x7 font size
	
	 
	 lcd_Cmd(LCD_SET_DISPLAY | LCD_DISPLAY_ON | LCD_CURSOR_OFF | LCD_BLINKING_OFF);					// Display on / Cursor on / Blinking on
	 
	  
	 lcd_Cmd(LCD_SET_ENTRY | LCD_ENTRY_INCREASE | LCD_ENTRY_NOSHIFT );						// Cursor increment and no scrolling of the LCD
	
	 lcd_clear();
	//===============End of the sequence==========================	

	
}

