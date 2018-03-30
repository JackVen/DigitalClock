/***********************************************************************
 * Project name:			Digital Clock 
 * Project number:			19810328 
 * File name:				bluetooth.c
 * Description:				Implementation of the Bluetooth module (HC-06)
 * Compiler					AVR8/GNU C Compiler : 5.4.0
 * Controller:				ATmega328PA
 * Created:					2018-02-28 11:00:49
 * SW version				1.0
 * Author:					Jack Venturi                                                               
************************************************************************/

 #include <avr/io.h>
 #include <util/delay.h>
 #include <avr/interrupt.h>
 #include "twi_master.h"
 #include "lcd.h"
 #include "clock.h"
 #include "usart.h"
 #include "bluetooth.h"
 #include "buttons.h"
 #include "rtc.h"
 #include "lcdchars.h"
 #include <stdio.h>

uint8_t connectedflag = FALSE;

/************************************************************************/
/* Initialization of the Bluetooth module (port and pin)                */
/************************************************************************/
void init_bluetooth(void)
{
	//PIN 2 in PORT B as input
	DDRB &= ~(1 << PINB2);
	connectedflag = 0;
	
}

/************************************************************************/
/* ASCII to decimal converter				                            */
/************************************************************************/
uint8_t ascii2dec(uint8_t data)
{
	
		
	if (data < 48 || data > 57 )		//If data is out of range return 255 or (-1)
	{
	
		data = 255;
	
	return data;
	
	}
										
	else                              //Else make the conversion from ascii code to decimal
	{
		data = data - 48;
	}
	
	return data;
}

/************************************************************************/
/* Connecting the Bluetooth module function                             */
/************************************************************************/
void connectingBlueTooth(void)
{
	lcd_string_clear();
	//If the BT module is not connected
	if((PINB & BTPIN) == BT_NOTCONNECTED)
	{
		
		lcd_setcurstring(LCD_COL3, LCD_ROW1,"Connecting");
		lcd_generatechar(LCD_GC_CHAR0, btchar, LCD_SET_DDADR2, LCD_COL8);
		
		for (int i = 3; i < 8; i++)
		{
			lcd_setcurstring(i,LCD_ROW2,">");
			lcd_setcurstring(15-i,LCD_ROW2,"<");
			_delay_ms(200);
			
		}
		connectedflag = FALSE;
		
	}

	
	//If the BT module is connected and the flag is false
	else if (((PINB & BTPIN) == BT_CONNECTED) && (connectedflag == FALSE) )
	{
		lcd_setcurstring(3,1,"Connected");
		lcd_setcurstring(LCD_COL7,LCD_ROW2,"[");
		lcd_setcurstring(LCD_COL9,LCD_ROW2,"]");
		lcd_generatechar(LCD_GC_CHAR0, btchar, LCD_SET_DDADR2, LCD_COL8);
		connectedflag = TRUE;
		_delay_ms(1500);
		lcd_string_clear();					//Clear the LCD
		
	}
		
}

/************************************************************************/
/* Set the time from the phone (hours and minutes)                      */
/************************************************************************/
void SetTheTime(void)
{
	
	uint8_t count = 0;								//Variable count data bytes from usart
	uint8_t hour1 = 0;								//Variable to store a byte from usart
	uint8_t hour2 = 0;								//-||- to store the time after conversion from ascii to decimal 
	uint8_t min1  = 0;								//...same principle 
	uint8_t min2  = 0;								//......
	uint8_t hourarr[2];								//Store the 2 digits in a array

	//Clear the LCD before printing to it..
	lcd_string_clear();
	lcd_setcurstring(LCD_COL0, LCD_ROW1, "Hour:");
	lcd_setcurstring(LCD_COL13,LCD_ROW1,"[");
	lcd_setcurstring(LCD_COL15,LCD_ROW1,"]");
	lcd_generatechar(LCD_GC_CHAR0, btchar, LCD_SET_DDADR, LCD_COL14);		//Bluetooth character
	lcd_setcurstring(LCD_COL0, LCD_ROW2, "White btn to set:");
	
	
	//while the white button is not pressed and dispclocktemp and dispclock are false loop here (hours)
    while((PIND & WHITEBUTTONMSK) != WHITEBUTTON_NOTPRESSED && (dispclocktemp == FALSE) && (dispclock == FALSE))
	{
		if((hour1 = usart_recieve()) != '\0')							//Fetch data from usart (digits)
		{
			
			hourarr[count++] = hour1;									//Store data
			_delay_ms(5);
			
		}
		 
		else if(count >= DIGITLIMIT)									//Check if we have two digits on the array
		{
			 lcd_setcursor(LCD_COL5, LCD_ROW1);
			 lcd_Data(hourarr[0]);										//Print the digits on LCD
			 lcd_Data(hourarr[1]);
			 hour2 = ascii2dec(hourarr[0])*10;							//Convert the digits..
			 hour2 += ascii2dec(hourarr[1]);							//.....
			 count = 0;													//Reset the counter
			
			 if (hour2 > HOURLIMIT)										//Check if hour is bigger than 23
			 {
				 lcd_setcurstring(LCD_COL5, LCD_ROW1, "00-23");			//If bigger print the desire range
				 _delay_ms(600);
				 lcd_setcurstring(LCD_COL5, LCD_ROW1, "       ");
				 _delay_ms(600);
			 }
			
			 
			 else
			 {
				 hour = hour2;											//If everything is OK then store hour2 in hour
			 }
		 
		 }
		 		 
	}
	
	if ((dispclocktemp == FALSE) && (dispclock == FALSE))
	{
		lcd_setcurstring(LCD_COL0, LCD_ROW1, "Mins:  ");
		_delay_ms(200);
			
	}

	////while the white button is not pressed and dispclocktemp and dispclock are false loop here (minutes)
	while((PIND & WHITEBUTTONMSK) != WHITEBUTTON_NOTPRESSED && (dispclocktemp == FALSE) && (dispclock == FALSE))
	{
		
		
		if((min1 = usart_recieve()) != '\0')
		{
			
			hourarr[count++] = min1;
			_delay_ms(5);
			
		}
		
		else if(count >= 2)
		{
			lcd_setcursor(LCD_COL5, LCD_ROW1);
			lcd_Data(hourarr[0]);
			lcd_Data(hourarr[1]);
			min2 = ascii2dec(hourarr[0])*10;
			min2 += ascii2dec(hourarr[1]);
			count = 0;
			
			if (min2 > 59)
			{
				lcd_setcurstring(LCD_COL5, LCD_ROW1, "00-59");
				_delay_ms(600);
				lcd_setcurstring(LCD_COL5, LCD_ROW1, "       ");
				_delay_ms(600);
			}
			
			
			else
			{
				min = min2;
			}
			
		}
		
	}
	
	if ((dispclocktemp == FALSE) && (dispclock == FALSE))
	{
		rtc_set_time(0, min,hour);
		dispbluetooth=FALSE;
		dispclocktemp=TRUE;
		dispclock=FALSE;
		
	}
	lcd_string_clear();
}



void bluetoothMenu(uint8_t selecdata)
{

	
	lcd_setcurstring(LCD_COL0,LCD_ROW1,"Select:");
	lcd_setcurstring(LCD_COL13,LCD_ROW1,"[");
	lcd_setcurstring(LCD_COL15,LCD_ROW1,"]");
	lcd_generatechar(LCD_GC_CHAR0, btchar, LCD_SET_DDADR, LCD_COL14);
	
	if (selecdata == '\0')
	{
		lcd_setcurstring(LCD_COL0, LCD_ROW2, "1:Set the time");
		_delay_ms(500);
		lcd_setcurstring(LCD_COL0, LCD_ROW2, "2:Exit        ");
		_delay_ms(500);
		
	}
	
	else
	{
		lcd_setcursor(LCD_COL7, LCD_ROW1);
		lcd_Data(selecdata);
		_delay_ms(500);
		selecdata = ascii2dec(selecdata);
		
		switch(selecdata)
		{
			case 1:
			
			SetTheTime();
			
			case 2:
			
			dispbluetooth = FALSE;
			dispclocktemp = TRUE; 
			dispclock     = FALSE;
			
			default:
			
			lcd_string("No data");
			
		}
	}
	
	

		
	
}