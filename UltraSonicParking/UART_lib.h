/*
 * UART_lib.h
 *
 *  Created on: Aug 27, 2017
 *      Author: evidence
 */

#ifndef UART_LIB_H_
#define UART_LIB_H_


#include "avr/io.h"


#define F_CPU 8000000UL //Defining frequency of the CPU
//#define UART_BAUDRATE 9600 //9600 is the default baud rate for the Data transfer mode
//for AT mode default baud rate it 38400

//Baud prescale is the value to load on the UBRR Register.
#define BAUD_PRESCALE(UART_BAUDRATE) (((F_CPU / (UART_BAUDRATE * 16UL))) - 1)

//Macros to check the state of the a certain bit
#define BIT_IS_SET(byte, bit) ( byte & (1 << bit) )
#define BIT_IS_CLEAR(byte, bit)( !(byte & (1 << bit)) )
#define DISABLED 0
#define ODD      1
#define EVEN     2

void UART_init(uint32_t baudrate, uint16_t DataFrameLength, uint8_t StopBitsNumber, uint8_t ParityMode){

	//enabling transmission and receiving
	UCSR0B |= ( 1 << TXEN0) | (1 << RXEN0);

	//choose the size of the frame.
	if(DataFrameLength == 5){
			UCSR0C &= ~(1<<UCSZ00);				//Bit #1 is reset in control and status reg C
			UCSR0C &= ~(1<<UCSZ01);				//Bit #2 is reset in control and status reg C
			UCSR0B &= ~(1<<UCSZ02);				//Bit #2 is reset in control and status reg B
		}
	if(DataFrameLength == 6){
	    UCSR0C |= (1 << UCSZ00); //Set Bit #1 in control and status reg C
	}
	if(DataFrameLength == 7){
		UCSR0C |= (1 << UCSZ01); //Set Bit #2 in control and status reg C
	}
	if(DataFrameLength == 8){
		UCSR0C |= (1 << UCSZ00)|(1 << UCSZ01); //Bits #2 and #1 are set to 1 in control and status reg C are set
		UCSR0B &= ~(1 << UCSZ02);			   //Bit #2 in control and status reg B is reset
	}
	if(DataFrameLength == 9){
		UCSR0C |= (1 << UCSZ00) |(1 << UCSZ01);	//Bits #2 and #1 are set in control and status reg C
		UCSR0B |= (1 << UCSZ02);				//Bit #2 is set in control and status reg B
	}
	//choose the UART mode (Asynch.)
	UCSR0C &= ~( (1 << UMSEL01) | (1 << UMSEL00) );

	//Parity Mode control
	if(ParityMode == DISABLED){
		UCSR0C &= ~( (1 << UPM00) | (1 << UPM01) ); //UPM00 and UPM01 are 00 means disable parity
	}
	if(ParityMode == ODD){
		UCSR0C &= ~(1<<UPM00);
		UCSR0C |=  (1<<UPM01);
	}
	if(ParityMode == EVEN){
		UCSR0C |=  (1<<UPM00);
		UCSR0C |=  (1<<UPM01);
	}

	//set stop bits number
	if(StopBitsNumber == 1){
		UCSR0C &= ~(1 << USBS0);
	}
	if(StopBitsNumber == 2){
		UCSR0C |= (1 << USBS0);
	}

	//load the baud rate on the UBRR register
	int baud_rate_prescaled = BAUD_PRESCALE(baudrate);
	UBRR0L = baud_rate_prescaled;
	UBRR0H = (baud_rate_prescaled >> 8);

}


//Receiving a character
unsigned char UART_RxChar(){

	//Keep on looping until data is received
	//RXC >> This flag bit is set when there is unread data in the UDR, can be also used to generate,
	while( !(UCSR0A & (1 << RXC0)) );// Check if the bit is clear.
	return(UDR0);
}

//Transmitting a character
 void UART_TxChar(unsigned char c){

	 /*
	  * UDRE >>UART Date Register Empty, if set it indicates that buffer is empty and that,
	  * the UDR is ready to save new date*/
	 while ( !(UCSR0A & (1 << UDRE0)) ); //check if the bit is clear
	 UDR0 = c;

 }

void UART_clearDR(void){
	UDR0 = 0;
}

 void UART_printString(char *string){

	 while (*string)
		 UART_TxChar(*string++);
 }


#endif /* UART_LIB_H_ */
