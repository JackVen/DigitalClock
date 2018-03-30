/***********************************************************************
 * Project name:			Digital Clock 
 * Project number:			19810328 
 * File name:				TWI.h
 * Description:				Implementation of the TWI protocol Master mode
 * Compiler					AVR8/GNU C Compiler : 5.4.0
 * Controller:				ATmega328PA
 * Created:					2017-09-20 20:01
 * SW version				1.0
 * Author:					Jack Venturi                                                               
************************************************************************/


#ifndef TWI_H_
#define TWI_H_

//TWI operation status

typedef struct TWI_OP_INFO
{

uint8_t LastOperationOK;

}TWI_OP_INFO;

TWI_OP_INFO TWIOpInfo;



/************************************************************************/
/* Operation commands for the TWI                                       */
/************************************************************************/
//TWI Reset interface
#define TWIReset()			(TWCR = (1<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE))
//TWI enable 
#define TWIEnable()			(TWCR = (0<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE))
//Send the START signal, enable interrupts and TWI, clear TWINT flag to resume transfer.
#define TWISendStart()		(TWCR = (1<<TWINT)|(0<<TWEA)|(1<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(1<<TWIE))
//Send the STOP signal, enable interrupts and TWI, clear TWINT flag.
#define TWISendStop()		(TWCR = (1<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(1<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE))
//Used to resume a transfer, clear TWINT and ensure that TWI and interrupts are enabled.
#define TWISendTransmit()	(TWCR = (1<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(1<<TWIE))
//FOR MR mode. Resume a transfer, ensure that TWI and interrupts are enabled and respond with an ACK if the device is addressed as a slave or after it receives a byte.		   
#define TWISendACK()		(TWCR = (1<<TWINT)|(1<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(1<<TWIE))
//FOR MR mode. Resume a transfer, ensure that TWI and interrupts are enabled but DO NOT respond with an ACK if the device is addressed as a slave or after it receives a byte.
#define TWISendNACK()		(TWCR = (1<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(1<<TWIE))		   


/************************************************************************/
/* Defines                                                              */
/************************************************************************/

#define SCL_400K					  12			//Speed for the SCL
#define TWI_START					0x08			//Start condition transmitted
#define TWI_PRESCALER				0x00			//Pre-scaler value 1
#define TX_MAX_BUFF_LEN				0x14		    //Length of the TX-buffer
#define RX_MAX_BUFF_LEN				0x14		    //Length of the RX-buffer
#define DATALEN2BIG					0x01			//Data length bigger than Max buffer len
#define SLA_ADD_R					0xD1			//Slave address + Read
#define SLA_ADD_W					0xD0			//Slave address + Write
#define TRUE						0x01
#define FALSE						0x00

/****************************************************************************/
/* TWI State codes															*/
/****************************************************************************/

// TWI Master Receiver status codes
#define TWI_MRX_ADR_ACK            0x40				// SLA+R has been transmitted and ACK received
#define TWI_MRX_ADR_NACK           0x48				// SLA+R has been transmitted and NACK received
#define TWI_MRX_DATA_ACK           0x50				// Data byte has been received and ACK transmitted
#define TWI_MRX_DATA_NACK          0x58				// Data byte has been received and NACK transmitted

// TWI Master Transmitter status codes
#define TWI_MTX_ADR_ACK            0x18				// SLA+W has been transmitted and ACK received
#define TWI_MTX_ADR_NACK           0x20				// SLA+W has been transmitted and NACK received
#define TWI_MTX_DATA_ACK           0x28				// Data byte has been transmitted and ACK received
#define TWI_MTX_DATA_NACK          0x30				// Data byte has been transmitted and NACK received

//Miscellaneous state codes
#define TWI_NO_STATE               0xF8				//No relevant state information available; TWINT = '0'
#define TWI_BUS_ERROR              0x00				//Bus error due to an illegal START or STOP condition
#define TWI_START				   0x08				//Start condition transmitted
#define TWI_REP_START			   0x10				// Repeated START has been transmitted
#define TWI_BUFFER_SIZE				 16			    //Set this to the largest message size that will be sent including address byte.

// General TWI Master status codes
#define TWI_START                  0x08				// START has been transmitted
#define TWI_REP_START              0x10				// Repeated START has been transmitted
#define TWI_ARB_LOST               0x38				// Arbitration lost

/************************************************************************/
/* Globals                                                              */
/************************************************************************/
uint8_t TWI_Buff_Pt;							//Buffer pointer
uint8_t TWI_Rx_Buff[RX_MAX_BUFF_LEN];			//Received buffer
uint8_t Rx_Buff_Len;							//Length of the received buffer
uint8_t TWI_Tx_Buff[TX_MAX_BUFF_LEN];			//Transmit buffer
uint8_t Tx_Buff_len;							//Length of the transmit buffer
uint8_t TWI_State;								//Twi state info variable

/************************************************************************/
/* Prototypes                                                           */
/************************************************************************/

void TWI_Master_Init(void);										//Master initialization function
void TWI_Transmit_Data(uint8_t *data, uint8_t datalen);			//Send TWI Data
uint8_t TWI_Is_Busy(void);										//Check for the TWI Status
uint8_t TWI_State_Info (void);									//Get the state info of the TWI
uint8_t TWI_Get_Data(uint8_t * data, uint8_t datalen);			//Get data from TWI-Rx buffer

#endif /* TWI_H_ */



