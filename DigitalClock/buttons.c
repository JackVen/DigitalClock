/**********************************************************************
 * Project name:			Digital Clock 
 * Project number:			19810328 
 * File name:				buttons.c
 * Description:				Implementation of push buttons 
 * Compiler					AVR8/GNU C Compiler : 5.4.0
 * Controller:				ATmega328PA
 * Created:					2018-02-06 15:08:12
 * SW version				1.0
 * Author:					Jack Venturi                                                               
************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "buttons.h"
#include "lcd.h"
#include "clock.h"
#include "twi_master.h" 
#include "bluetooth.h"

 
 /************************************************************************/
 /* Button initialization function										*/                                            
 /************************************************************************/
 void buttons_Init(void)
{
	PCICR  |= PORTBON;								// turn on pin change interrupt control register on PORT B
	PCMSK0 |= GREENCLKBUTTON;						// Mask if Clock button is pressed
	PCMSK0 |= REDCLKTEMPBUTTON;						// Mask if Clock temp button is pressed
	PCMSK0 |= BLBUTTON;								// Mask if Clock temp button is pressed
 	DDRD   &= ~(1 << WHITEBUTTON);				   // PIN 3 in PORT D as input White button
	PORTD  &= ~(1 << WHITEBUTTON);				   // Start Pin 3 in PORT D as Zero white button
	
	
	
	showclockonetime = TRUE;						//One time variable for the clock
	dispclock = FALSE;								//Initialization values...
	dispclocktemp = TRUE;							//..first time the system 
	dispbluetooth = FALSE;							//..in powered on
	debounce = 0;									//debounce variable, when pushing a button.
}

 /************************************************************************/
 /* Interrupt service routine, when detecting a button press			*/
 /************************************************************************/
 ISR(PCINT0_vect)
 {
	debounce++;													//Count how many times debounce variable is added when entering  to ISR
	
	
	if ((debounce >= DEBOUNCELIM) && (PINB & REDCLKTEMPBUTTON))			//Check if RED clock temp button is pressed and check debounce variable
	{
		if (dispclocktemp == FALSE)							    //..if false clear lcd, due to another button has been pressed
		{
			lcd_string_clear();
			showclockonetime = TRUE;
				
		}
		
		dispclocktemp = TRUE;								    
		dispclock = FALSE;	
		dispbluetooth = FALSE;
		debounce = 0;
	
		
		
	}
	
	else if ((debounce >= DEBOUNCELIM) && (PINB & GREENCLKBUTTON))		//Check if GREEN clock button is pressed and check debounce variable
	{
		if (dispclock == FALSE)									//..if true clear lcd, due to another button has been pressed
		{												
			lcd_string_clear();
			showclockonetime = TRUE;							//...and set showclocktime variable to true
		}
		
		dispclocktemp = FALSE;									//if false continue with the same variables due to the same button has been pressed
		dispclock = TRUE;
		dispbluetooth = FALSE;
		debounce = 0;
	}
	
	else if((debounce >=  DEBOUNCELIM) && (PINB & BLBUTTON))				//Check if blue-tooth button has been pressed*/
	{
		
		
		if (dispbluetooth == FALSE)
		{
			lcd_string_clear();
			showclockonetime = TRUE;
			
		
		}
		
		dispclocktemp = FALSE;
		dispclock = FALSE;	
		dispbluetooth = TRUE;
		debounce = 0;
		
		
	}
	
	
 }
