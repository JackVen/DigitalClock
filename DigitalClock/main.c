/*------------------------------------------------------------------------
 * Project name:			Digital Clock
 * Project number:			19810328 
 * File name:				main.c
 * Description:				Implementation of main.c
 * Compiler					AVR8/GNU C Compiler : 5.4.0
 * Controller:				ATmega328PA
 * Created:					2017-09-05 20:01
 * SW version				1.0
 * Author:					Jack Venturi
 *------------------------------------------------------------------------*/



#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "lcdchars.h"
#include "clock.h"
#include "twi_master.h"
#include "rtc.h"
#include "buttons.h"
#include "usart.h"
#include "bluetooth.h"
#include <avr/interrupt.h>

//Main menu globals
uint8_t showclockonetime;





/******************************/
/* Initialization functions  */
/****************************/
void init(void)
{
	
	lcd_Init();						//LCD initialization
	TWI_Master_Init();				//Twi Master initialization
	buttons_Init();					//Buttons initialization
	usart_Init();					//USART initialization
	init_bluetooth();				//Bluetooth module initialization
}
	

int main (void)
{
	
	init();							//Initialization functions
	
	//display_Loading();				//Displays intro 

	
	//rtc_set_time(58,03,11);		   //Set time, secs, mins, hours
	lcd_home();
	sei();							//Enable interrupts

	while(1) 
	{
			
			
			rtc_read_time();
			rtc_read_temp();
			
			if (dispclock)
			{
				
			 if (sec == 0 || showclockonetime == 1)
				{
			
					display_clock(hour, min);
					showclockonetime = FALSE;
						
				}
				
				display_dots();
					
			}
			
	
				
			if (dispclocktemp)
			{
					
					if (sec == 0 || showclockonetime == 1)
					{
					   
					   display_menu_bar();	 
					   display_clocktemp(hour, min, temperature);
					   showclockonetime = FALSE;
							 
					}
						 
						 display_smalldots();
				}
				
			if (dispbluetooth)
			{
				
					connectingBlueTooth();
					if (connectedflag == TRUE)
					{
						bluetoothMenu(usart_recieve());
					}
					
			}	
				
			
			
	}
	
	return 0;
	
}


