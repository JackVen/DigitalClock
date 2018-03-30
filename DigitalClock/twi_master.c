/***********************************************************************
 * Project name:			Digital Clock 
 * Project number:			19810328 
 * File name:				TWI.c
 * Description:				Implementation of the TWI-protocol in master mode
 * Compiler					AVR8/GNU C Compiler : 5.4.0
 * Controller:				ATmega328PA
 * Created:					2017-09-20 20:01
 * SW version				1.0
 * Author:					Jack Venturi                                                               
************************************************************************/



#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
#include "twi_master.h"



/************************************************************************/
/* Initialization of the TWI Master                                     */
/************************************************************************/
void TWI_Master_Init(void)
{
	
	TWBR = SCL_400K;										//SCL speed
	TWSR = TWI_PRESCALER;									//Pre-scaler value
	TWIEnable();											//Enable TWI bit in TWCR, all other bits disable
	TWIOpInfo.LastOperationOK = FALSE;						//Set Last op flag to false
	
	
}

/************************************************************************/
/* Send TWI data														*/
/************************************************************************/
void TWI_Transmit_Data(uint8_t *data, uint8_t datalen)
{
	
	uint8_t temp;
	Tx_Buff_len = Rx_Buff_Len = datalen;						//Number of data bytes to send
	TWI_State = TWI_NO_STATE;								   //TWI state default
	
	if (datalen < TX_MAX_BUFF_LEN)
	{
		
		while(TWI_Is_Busy());							       //Check if the TWI lines are busy
		
		TWI_Tx_Buff[0] = data[0];							   //Store the Sla + R/W bit
		if (data[0] == SLA_ADD_W)							   //Check if the data has a W-bit command 
		{
			
			for (temp = 1; temp < datalen; temp++)			  //Then store data to write in the TWI TX-buffer
			{
				
				TWI_Tx_Buff[temp] = data[temp];
			}
			
			
		}
		
		TWISendStart();										 //Send start condition
		
	}
	
	else 
	{
		
		TWI_State = DATALEN2BIG;							//Data length bigger than max buffer value
		
	}	
			
	TWIOpInfo.LastOperationOK = FALSE;					 //Last operation not finish
	
}

/************************************************************************/
/* Get data from TWI-Rx Buffer after Twi finished                      */
/************************************************************************/

uint8_t TWI_Get_Data(uint8_t * data, uint8_t datalen)
{
	uint8_t temp;
	
	while(TWI_Is_Busy());
	
	if (TWIOpInfo.LastOperationOK)
	{
		for (temp = 0; temp < datalen; temp++)
		{
			data[temp] = TWI_Rx_Buff[temp];
		}
		
	}

	return TWIOpInfo.LastOperationOK;
}

/************************************************************************/
/* Check if TWI lines are busy                                           */
/************************************************************************/
uint8_t TWI_Is_Busy(void)
{
	
	return (TWCR & (1 << TWIE));			//While TWEI in TWCR is 1, then TWI-lines are busy
}

/************************************************************************/
/* Get TWI state info                                                   */
/************************************************************************/
uint8_t TWI_State_Info (void)
{
	while(TWI_Is_Busy());
	
	return TWI_State;
}



/************************************************************************/
/* Interrupt vector function for the TWI-Op                             */
/************************************************************************/
ISR (TWI_vect)
{
	
	switch(TWSR)										//Check the status code for the TWSR
	{
		case TWI_START:									//Start condition has been sent code: 0x08
			
		case TWI_REP_START:								//Repeat start has been sent code:0x10
			 
			 TWI_Buff_Pt = 0;							//Set/Reset the pointer	
				 
		case TWI_MTX_ADR_ACK:							//Slave + W has been sent and ACK received code:0x18
		
		case TWI_MTX_DATA_ACK:							//Data byte has been transmitted and ACK received code:0x28
		
			if (TWI_Buff_Pt < Tx_Buff_len )
			{
				
				TWDR = TWI_Tx_Buff[TWI_Buff_Pt++];
				TWISendTransmit();						//Send the byte loaded into the TWDR
				
			}
			
			else
			{
				TWIOpInfo.LastOperationOK = TRUE;		//Last operation went OK
				TWISendStop();							//Last byte has been sent, stop operation
				
			}
			break;
			
		case TWI_MRX_ADR_ACK:						    //SLA + R byte received ACK sent
			
		case TWI_MRX_DATA_ACK:						    //Data byte received ACK sent
		
			TWI_Rx_Buff[TWI_Buff_Pt++] = TWDR;			//Store the data received to TWI receive buffer	
			
			
			if (TWI_Buff_Pt < (Rx_Buff_Len - 1 ))		//As long as it is not the last one byte to receive send an ACK
			{
				
				TWISendACK();
				
			}
			 
			else										// If it is the last byte send an NACK
			{
		
				TWISendNACK();
			
			}
			break;
		
		case TWI_MRX_DATA_NACK:							//Data byte has been received NACK transmitted code:0x58
			
			TWI_Rx_Buff[TWI_Buff_Pt] = TWDR;			//Receive the last byte cause NACK has been transmitted
			
			TWIOpInfo.LastOperationOK = TRUE;		    //Last operation went OK
			TWISendStop();								//Stop operation
			
			break;
			
		case TWI_ARB_LOST:								//Arbitration lost, restart operation
		
			 TWISendStart();
			 
			 break;
			
		case TWI_MTX_ADR_NACK:           				//SLA + W has been transmitted and NACK received code: 0x20
	
		case TWI_MTX_DATA_NACK:          				//Data byte has been transmitted and NACK received code:0x30
			
		case TWI_MRX_ADR_NACK:							//SLA + R has been transmitted and NACK received code: 0x48
		
		case TWI_BUS_ERROR:								//TWI Bus error code: 0x00
		
		default:										
			
			TWI_State = TWSR;							//Store the error-state code
			TWIReset();									//Reset the TWI interface
			
	}
	
}