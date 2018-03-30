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


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "twi_master.h"
#include "rtc.h"
#include "clock.h"
#include "lcd.h"




/************************************************************************/
/* Decimal to BCD converter                                             */
/************************************************************************/
uint8_t dec2bcd(uint8_t dec)
{

	return (((dec / 10) << 4) | (dec % 10));	

}

/************************************************************************/
/*BCD to decimal converter                                             */
/************************************************************************/
uint8_t bcd2dec(uint8_t bcd)
{
	
	return(((bcd & 0xF0) >> 4) * 10) + (bcd & 0x0F);
}

/************************************************************************/
/* Sets the time and date for the RTC                          */
/************************************************************************/
void rtc_set_time(uint8_t seconds, uint8_t min, uint8_t hour)
{
	uint8_t timearray[5];					//Time buffer;
	uint8_t regpointer = SECONDS;			//Initial address register for the RTC
	
	timearray[0] = SLA_ADD_W;				//Write command for the TWI interface
	timearray[1] = regpointer;				//Pointer to the register in RTC
	timearray[2] = dec2bcd(seconds);		//Decimal to bcd converter seconds
	timearray[3] = dec2bcd(min);			//..minutes
	timearray[4] = dec2bcd(hour);			//..hours
	
	TWI_Transmit_Data(timearray, 5);		//Write the time to RTC registers		
	

}

/************************************************************************/
/* Set the register point to a certain address on the RTC		         */
/************************************************************************/
void rtc_set_regpoint(uint8_t regpoint)
{
	uint8_t regpointarray[2];					//Register pointer buffer
	
	regpointarray[0] = SLA_ADD_W;				//Store write command
	regpointarray[1] = regpoint;				//Store the pointer address
			
	
	TWI_Transmit_Data(regpointarray, 2);		//set the reg pointer to the address
	
		
}

/************************************************************************/
/* Reads the time from the RTC                                          */
/************************************************************************/
void rtc_read_time(void)
{
	
	uint8_t buff1[6];							//Prepare buffer to send
	uint8_t buff2[6];							//Prepare buffer to receive
	
	buff1[0]=SLA_ADD_R;							//Store Read command in write buffer
	TWI_Transmit_Data(buff1, 6);				//Send the read command and receive data
	TWI_Get_Data(buff2, 6);						//Get the data received in TWI operation
	sec = bcd2dec(buff2[3]);					//Get seconds
	min = bcd2dec(buff2[4]);					//Get minutes
	hour = bcd2dec(buff2[5]);					//Get hours
	
	rtc_set_regpoint(SECONDS);					//Set register point in RTC
	
	
		
	
}

/************************************************************************/
/* Reads the temperature on the RTC										*/
/************************************************************************/

void rtc_read_temp(void)
{
	uint8_t buff1[3];						//Prepare buffer
	uint8_t buff2[3];						//...
	
	rtc_set_regpoint(RTCTEMP1);				//Set pointer at temperature register	
	
	buff1[0]=SLA_ADD_R;						//Store Read command at read buffer
	TWI_Transmit_Data(buff1, 3);			//Transmit and receive data
	TWI_Get_Data(buff2, 3);					//Get the data received
	temperature = buff2[2];					//Store the temperature data in variable
	
	

}
