/*
 * Avr_DIO.h
 *
 *  Created on: Sep 6, 2017
 *      Author: evidence
 */

#ifndef AVR_DIO_H_
#define AVR_DIO_H_


//Defines of input and output to be changed if using PIC
#define input		0
#define output 		1

//Macros for setting bits, clearing them and toggling them
#define SET_BIT(Port_reg, PIN)    Port_reg |= 1 << PIN
#define CLEAR_BIT(Port_reg, PIN)  Port_reg &= ~(1 << PIN)
#define TOGGLE_BIT(Port_reg, PIN) Port_reg ^= 1 << PIN

//Definition of Addresses
#define   B		0x23
#define   C		0x26
#define   D		0x29

//Needed files
#include "stdint.h"
#include "Avr_DIO.c"

//Function prototypes
void pin_Dir(uint8_t port, uint8_t pin, char direction);
void pin_write(uint8_t port, uint8_t pin, uint8_t data);
uint8_t pin_state(uint8_t port,uint8_t pin);


#endif /* AVR_DIO_H_ */
