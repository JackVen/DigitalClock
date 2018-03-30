/***********************************************************************
 * Project name:			Digital Clock 
 * Project number:			19810328 
 * File name:				rtc.c
 * Description:				Implementation of the RTC DS3231
 * Compiler					AVR8/GNU C Compiler : 5.4.0
 * Controller:				ATmega328PA
 * Created:					2017-09-20 20:01
 * SW version				1.0
 * Author:					Jack Venturi                                                               
************************************************************************/

#ifndef RTC_H_
#define RTC_H_

/************************************************************************/
/* Defines                                                              */
/************************************************************************/
//RTC address MAP
#define STARTREG		0x00			//Start register for the RTC address MAP
#define SECONDS			0x00			//Seconds		range 00-59
#define MINUTES			0x01			//Minutes		range 00-59
#define HOUR			0x02			//Hours			range 1-12 + AM/PM, 00-23
#define DAY				0x03			//Day			range 1-7
#define DATE			0x04			//Date			range 01-31 
#define MONTH			0x05			//Month/Century	range 1-12 + Century
#define YEAR			0x06			//Year			range 00-99
#define A1M1			0x07			//Alarm1 secs	range 00-59
#define A1M2			0x08			//Alarm1 mins	range 00-59
#define A1M3			0x09			//Alarm1 hours	range 1-12 + AM/PM, 00-23
#define A1M4			0x0A			//Alarm1 date/day range day 1-7, date 1-31
#define RTCCR			0x0E			//RTC control register
#define RTCSR			0x0F			//RTC status register
#define RTCTEMP1		0x11			//RTC temperature MSB register
#define RTCTEMP2		0x12			//RTC temperature LSB register
 
 
/************************************************************************/
/* Global variables                                                     */
/************************************************************************/

uint8_t min;
uint8_t sec;
uint8_t hour;
uint8_t temperature;


/************************************************************************/
/* Prototypes                                                           */
/************************************************************************/
uint8_t dec2bcd(uint8_t dec);						  //Decimal to bcd converter
uint8_t bcd2dec(uint8_t bcd);						  //bcd to decimal converter
void rtc_set_time(uint8_t seconds, uint8_t min, uint8_t hour); //Set the current time
void rtc_read_time(void);					 //Read time from RTC, mins hours, seconds
void rtc_set_regpoint(uint8_t regpoint);			 //Set register pointer
void rtc_read_temp(void);							//Reads the temperature in RTC


#endif /* RTC_H_ */