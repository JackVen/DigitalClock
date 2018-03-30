/***********************************************************************
 * Project name:			Digital Money Box
 * Project number:			19810328 
 * File name:				clock.h
 * Description:				Implementation of the clock.h
 * Compiler					AVR8/GNU C Compiler : 5.4.0
 * Controller:				ATmega328PA
 * Created:					2017-09-20 20:01
 * SW version				1.0
 * Author:					Jack Venturi                                                               
************************************************************************/


#ifndef CLOCK_H_
#define CLOCK_H_


//========Global variables==========================
uint8_t showclockonetime;

//========Defines==========================
#define ASCIICHARINDEX		48


/*************************************************
			Function Prototypes                                               
*************************************************/				
void FirstDigit(uint8_t hour1);
void SecondDigit(uint8_t hour2);
void ThirdDigit(uint8_t min1);
void FourthDigit(uint8_t min2);
void display_clock(uint8_t hour, uint8_t min);
void display_clocktemp(uint8_t hour, uint8_t min, uint8_t temp);

#endif /* CLOCK_H_ */