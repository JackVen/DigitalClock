/***********************************************************************
 * Project name:			Digital Clock
 * Project number:			19810328 
 * File name:				buttons.h
 * Description:				Implementation of buttons.h
 * Compiler					AVR8/GNU C Compiler : 5.4.0
 * Controller:				ATmega328PA
 * Created:					2018-02-06 15:08:28
 * SW version				1.0
 * Author:					Jack Venturi                                                               
************************************************************************/


#ifndef BUTTONS_H_
#define BUTTONS_H_

//========Global variables==================
uint8_t dispclock;
uint8_t	dispclocktemp;
uint8_t dispbluetooth;
uint8_t debounce;
	
//========Defines==========================
#define		PORTBON						0x01		//Turns on PORT B 
#define		BLBUTTON					0X08		//Bluetooth button mask bit
#define		REDCLKTEMPBUTTON			0x20		//Clock button mask bit
#define		GREENCLKBUTTON				0x10		//Clock temp button mask bit
#define		DEBOUNCELIM					0x01		//Debounce limit
#define		WHITEBUTTON					PIND3		//White button connected to PIN3 in PORT D
#define		WHITEBUTTONMSK				0x08		//White button mask bit
#define		WHITEBUTTON_NOTPRESSED		0x08		//White button pressed mask bit
#define     DIGITLIMIT					   2		//Digit limit to set the clock
#define		HOURLIMIT					  23		//Hour limit set to 23


/*************************************************
			Function Prototypes                                               
*************************************************/
 void buttons_Init(void);							//Initialization of buttons


#endif /* BUTTONS_H_ */