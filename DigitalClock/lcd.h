/***********************************************************************
 * Project name:			Digital Clock
 * Project number:			19810328 
 * File name:				lcd.h
 * Description:				Implementation of the LCD 1602A
 * Compiler					AVR8/GNU C Compiler : 5.4.0
 * Controller:				ATmega328PA
 * Created:					2017-09-20 20:01
 * SW version				1.0
 * Author:					Jack Venturi                                                               
************************************************************************/
#ifndef LCD_H
#define LCD_H
#endif

/******************************
	LCD ports and pins                                        
********************************/
//  LCD	 RS		<-->	Port B, bit PIN0			(RS: Command data=0, Write data=1)
#define  LCD_RS			PINB1
				

//  LCD	 Enable	<-->	Port B, bit PIN1			(E: Disable LCD=0, Enable LCD=1)   
#define	 LCD_EN			PINB0
				

//  LCD  D4-D7  <-->	Port D, bit PIN3 - PIN6
#define	 LCD_D4			PIND4
#define  LCD_D5			PIND5
#define  LCD_D6			PIND6
#define  LCD_D7			PIND7

//	LCD PORTD and Data direction Register
#define  LCD_PORTD		PORTD
#define  LCD_DDR		DDRD


/*************************************************************
	LCD Execution Times (MS = milliseconds, US = microseconds)                                          
*************************************************************/
#define LCD_BOOTUP_MS           15
#define LCD_ENABLE_US           20
#define LCD_WRITEDATA_US        46
#define LCD_COMMAND_US          42

#define LCD_SOFT_RESET_MS1      5
#define LCD_SOFT_RESET_MS2      1
#define LCD_SOFT_RESET_MS3      1
#define LCD_SET_4BITMODE_MS     5

#define LCD_CLEAR_DISPLAY_MS    2
#define LCD_CURSOR_HOME_MS      2

/*************************************************************
Line definition of the LCD used, The entries here should fit for an 
LCD with a line length of 16 characters
*************************************************************/
#define LCD_DDADR_LINE1         0x00
#define LCD_DDADR_LINE2         0x40


 
/*************************************************************
				LCD Commands/Settings
*************************************************************/
// Clear Display -------------- 0b00000001
#define LCD_CLEAR_DISPLAY       0x01

// Cursor Home ---------------- 0b0000001x
#define LCD_CURSOR_HOME         0x02

// Set Entry Mode ------------- 0b000001xx
#define LCD_SET_ENTRY           0x04

#define LCD_ENTRY_DECREASE      0x00
#define LCD_ENTRY_INCREASE      0x02
#define LCD_ENTRY_NOSHIFT       0x00
#define LCD_ENTRY_SHIFT         0x01

// Set Display ---------------- 0b00001xxx
#define LCD_SET_DISPLAY         0x08

#define LCD_DISPLAY_OFF         0x00
#define LCD_DISPLAY_ON          0x04
#define LCD_CURSOR_OFF          0x00
#define LCD_CURSOR_ON           0x02
#define LCD_BLINKING_OFF        0x00
#define LCD_BLINKING_ON         0x01

// Set Shift ------------------ 0b0001xxxx
#define LCD_SET_SHIFT           0x10

#define LCD_CURSOR_MOVE         0x00
#define LCD_DISPLAY_SHIFT       0x08
#define LCD_SHIFT_LEFT          0x00
#define LCD_SHIFT_RIGHT         0x04

// Set Function --------------- 0b001xxxxx
#define LCD_SET_FUNCTION        0x20

#define LCD_FUNCTION_4BIT       0x00
#define LCD_FUNCTION_8BIT       0x10
#define LCD_FUNCTION_1LINE      0x00
#define LCD_FUNCTION_2LINE      0x08
#define LCD_FUNCTION_5X7        0x00
#define LCD_FUNCTION_5X10       0x04

#define LCD_SOFT_RESET          0x30

// Set CG RAM Address --------- 0b01xxxxxx  (Character Generator RAM)
#define LCD_SET_CGADR           0x40

#define LCD_GC_CHAR0            0
#define LCD_GC_CHAR1            1
#define LCD_GC_CHAR2            2
#define LCD_GC_CHAR3            3
#define LCD_GC_CHAR4            4
#define LCD_GC_CHAR5            5
#define LCD_GC_CHAR6            6
#define LCD_GC_CHAR7            7
#define LCD_GC_CHAR8            8
#define LCD_GC_CHAR9            9
#define LCD_GC_CHAR10           10
#define LCD_GC_CHAR11           11
#define LCD_GC_CHAR12           12
#define LCD_GC_CHAR13           13
#define LCD_GC_CHAR14           14
#define LCD_GC_CHAR15           15


// Set DD RAM Address --------- 0b1xxxxxxx  (Display Data RAM)
#define LCD_SET_DDADR           0x80		//Display character on the first Line of the LCD
#define LCD_SET_DDADR2			0xC0		//Display character on the second Line of the LCD 

//Column numbers on the LCD
#define LCD_COL0            0
#define LCD_COL1            1
#define LCD_COL2            2
#define LCD_COL3            3
#define LCD_COL4            4
#define LCD_COL5            5
#define LCD_COL6            6
#define LCD_COL7            7
#define LCD_COL8            8
#define LCD_COL9            9
#define LCD_COL10           10
#define LCD_COL11           11	
#define LCD_COL12           12
#define LCD_COL13           13
#define LCD_COL14           14
#define LCD_COL15           15

//Row numbers on the LCD
#define  LCD_ROW1			1
#define  LCD_ROW2			2		

/*************************************************
			Function Prototypes                                               
*************************************************/

void lcd_Enable(void);						// Sends enable pulse to the LCD
void lcd_Init(void);						// Initialization function
void lcd_Data(uint8_t data);				// Prints data in the LCD
void lcd_Out(uint8_t data);					// Sends a 4-bit data to the LCD
void lcd_Cmd(uint8_t data);					// Sends commands data to the LCD
void lcd_string(const char *data);			// Sends a String to the LCD
void lcd_home(void);						// Sends the cursor home command
void lcd_setcursor(uint8_t x, uint8_t y);   // Sets the cursor in a specific position
void lcd_clear(void);						// Clears screen 
void lcd_generatechar(uint8_t startaddress, const uint8_t *data, uint8_t line, uint8_t column);  // Character generator, start address and data
void display_Loading(void);				    //Loading display animation
void lcd_string_clear(void);				//Lcd clear from string
void lcd_setcurstring(uint8_t x, uint8_t y, const char *data);	//Set the position of the text and the text

