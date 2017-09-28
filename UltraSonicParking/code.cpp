/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2014  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */
/*-------------------------------------Includes------------------------------------------*/
#include "ee.h"
#include "Arduino.h"
#include "Avr_DIO.h"
#include "avr/io.h"
#include "util/delay.h"
#include "UART_lib.h"
#include "Ultrasonic.h"

/*-------------------------------------Functions------------------------------------------*/
//the function that has the pattern of schedule

char command;
void loop(void)
{
	//Command from the application denoting it's ready to receive data.
	command = UART_RxChar();

	if(command == 'r' || command == 'd' ){
		ActivateTask(MeasureDistance);
		ActivateTask(Send);			//will Preempt  MeasureDistance since it has higher priority
	}
	command = '/0';
}

//Initialization function
void setup(void)
{
	//Initializing the Ultrasonic sensor
//	pin_Dir(B,PB1,input); 	//Make pin8 input (clear it) - echo
//	pin_Write(B,PB1,1);		//Activate pull-up resistor for pin8
//	pin_Dir(B,PB0,output);  //Make pin9 output (Set it) - Trigger
//	pin_Dir(B,PB5,output);  //Led conf.

	//This function initializes the ultrasonic.
	//it's arguments are (triggerPIN,triggerPORT,echoPIN,echoPORT,max_distance ) RESPECTIVELY.
	//PB0 >> Pin 8 	(trig.)
	//PB1 >> Pin 9 	(echo)
	//PB2 >> Pin 10 (trig.)
	//PB3 >> Pin 11 (echo)
	//PD6 >> Pin 6	(trig.)
	//PD7 >> Pin 7 	(echo)

	U_Init(PB0, B, PB1, B);
	U_Init(PB2, B, PB3, B);
	U_Init(PD6, D, PD7, D);


	//Initializing the UART
	UART_init(4800,8,1,DISABLED);

}
/*-------------------------------------Main------------------------------------------*/
int main(void)
{
	EE_mcu_init();

	init();

#if defined(USBCON)
	USBDevice.attach();
#endif
	
	setup();

	for (;;) {
		loop();
		if (serialEventRun) serialEventRun();
	}

	return 0;

}
