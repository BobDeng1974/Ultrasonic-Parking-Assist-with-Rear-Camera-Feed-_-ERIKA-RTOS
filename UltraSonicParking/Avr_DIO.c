/*
 * Avr_DIO.c
 *
 *  Created on: Sep 6, 2017
 *      Author: evidence
 */

//Includes

#include "ee.h"
#include "avr/io.h"

//Functions implementation

//Function that determines whether the pin is input or output
void pin_Dir(uint8_t port, uint8_t pin, char direction){
	if(direction == output){
		SET_BIT( (*((volatile unsigned char*)(port+1))), pin );
		//Type casting to pointer then dereference
		//Port+1 gives us the reg. right after the base reg. which has address "port"
		//now the pin is set to 1 which indicates to output
	}
	if(direction == input){
		CLEAR_BIT( (*((volatile unsigned char*)(port+1))), pin );
	}
}

//Function that
void pin_Write(uint8_t port, uint8_t pin, uint8_t data){
	if(data == 1){
		SET_BIT( (*((volatile unsigned char*)(port+2))), pin );
		//set corresponding bit to "pin" in register PORTx to one (Setting the pin)
	}
	if(data == 0){
		CLEAR_BIT( (*((volatile unsigned char*)(port+2))), pin );
		//set corresponding bit to "pin" in register PORTx to zero (clearing the pin)
	}
}


uint8_t pin_State(uint8_t port,uint8_t pin){

	uint8_t state  = (*(volatile unsigned char*)port);
	uint8_t result =  state & (1 << pin);

	return result;
}

