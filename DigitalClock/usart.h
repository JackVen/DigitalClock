/*
 * usart.h
 *
 * Created: 2018-02-18 17:01:18
 *  Author: Jack
 */ 


#ifndef USART_H_
#define USART_H_

//Defines
#define USARTBUFFSZ			12							//Size of the USART buffer

//Global variables
volatile char usart_Rxbuf[USARTBUFFSZ];					//USART receive buffer
volatile char usart_Txbuf[USARTBUFFSZ];					//USART transmit buffer
volatile uint8_t usartindexpnt;									//USART index pointer for the buffer
volatile char usartdata;




void usart_Init(void);
void usart_transmit(const char *data);
unsigned char usart_recieve(void);



#endif /* USART_H_ */