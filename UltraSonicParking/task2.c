/*
 * task2.c
 *
 *  Created on: Sep 7, 2017
 *      Author: evidence
 */

#include "ee.h"
#include "UART_lib.h"



extern unsigned char Send_Data[4];
extern uint8_t disToObject[3];
extern char command;

TASK(Send){

		//Sending the sensor reading to the Bluetooth.


		UART_TxChar('<');

		if(command == 'r'){

			UART_TxChar(Send_Data[0]);

			UART_TxChar(Send_Data[1]);

			UART_TxChar(Send_Data[2]);
		}
		else if (command == 'd'){

			UART_TxChar(disToObject[0]);

			UART_TxChar(disToObject[1]);

			UART_TxChar(disToObject[2]);
		}



		UART_TxChar('>');
};
