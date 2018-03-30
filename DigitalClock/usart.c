/**********************************************************/
 /* Project name:			Digital Clock
 * Project number:			19810328 
 * File name:				lcd.c
 * Description:				Implementation of the LCD 1602A
 * Compiler					AVR8/GNU C Compiler : 5.4.0
 * Controller:				ATmega328PA
 * Created:					2018-02-17 14:46:09
 * SW version				1.0
 * Author:					Jack Venturi
***********************************************************/
 
 
 #include <avr/io.h>
 #include <util/delay.h>
 #include <avr/interrupt.h>
 #include "lcd.h"
 #include "clock.h"
 #include "usart.h"
 #include "twi_master.h"
 
 #define FOSC		F_CPU
 #define BAUDRATE	9600
 #define MYUBBRR	FOSC/16/BAUDRATE-1
 

  volatile uint8_t usartindexpnt = 0;

 
 /************************************************************************/
 /* Serial communication initialization	(to be used in Bluetooth)		 */
 /************************************************************************/
 void usart_Init(void)
 {
	 
	 UBRR0H = ((MYUBBRR) >> 8);								//Set the baud rate at higher register
	 UBRR0L = (MYUBBRR);									//..baud rate at lower register
	 UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);  //Enable receiver & transmitter		    
	 UCSR0C = (3 << UCSZ00);								//8-bit character size		
 }
 
/************************************************************************/
/* Send char data (polling)													*/
/************************************************************************/
 void usart_transmit(const char *data)
 {

	while(*data !='\0')
	{
		
		while(!(UCSR0A & (1 << UDRE0)));
		UDR0 = *data++;
	}
	
	
 }
 
 unsigned char usart_recieve(void)
 {
	
	char datachar = 0;
	
	if (usartindexpnt > 0)
	{
		 
		 for(int i = 0; i < usartindexpnt; i++)
		 {
			 
			 datachar = usart_Rxbuf[i];
			 
		 }
		
		usartindexpnt = 0;
	}
	
	

	return datachar;
 }
  
 
 
 
 
 ISR(USART_RX_vect)
 {
	
	usart_Rxbuf[usartindexpnt++] = UDR0;
	
 }