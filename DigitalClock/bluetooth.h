/*
 * bluetooth.h
 *
 * Created: 2018-02-28 11:20:14
 *  Author: Jack
 */ 


#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

//Defines
#define BTPIN							0x04					//BTPIN mask bit
#define BT_NOTCONNECTED					0x00					//Not connected mask bit
#define BT_CONNECTED					0x04					//BT connected mask bit
#define SETBUTTON_PRESSED				0x08					//Set button pressed bit mask
#define SETBUTTON_NOT_PRESSED			0x04					//Set button not pressed bit mask
#define OUTOFRANGE0_9					255						//Return value when a number is out of range


//Globals
uint8_t connectedflag;



//Prototypes
void init_bluetooth(void);										//Initialization  of Bluetooth module
void connectingBlueTooth(void);									//Connecting Bluetooth function
void bluetoothMenu(uint8_t data);								//Bluetooth Menu receives data from USART
uint8_t ascii2dec(uint8_t data);								//Ascii to decimal converter from 0-9




#endif /* BLUETOOTH_H_ */