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

#include "ee.h"
#include "avr/io.h"
#include "Avr_DIO.h"
#include "util/delay.h"
#include "Ultrasonic.h"



#define US_PORT PORTB
#define US_PIN PINB
#define US_POS PB1
#define US_DDR DDRB

uint16_t duration;
uint8_t disToObject[3];
unsigned char Send_Data[3];



//Function Prototype
//uint16_t getPulseWidth();


TASK(MeasureDistance){

		//=====Getting the reading from the first Sensor=====.
		//Function That trigger the sensor and sends the ultrasonic pulses.
		U_TRIGGER(PB0, B);
		//Calculating distance.
		duration 	= U_GET_PULSEWIDTH(PB1, B);
		disToObject[0] = U_GET_DISTANCE(duration);
		//We now have the measured the distance.
	if(disToObject[0]  > 30){
		Send_Data[0] = '0';
	}
	else if(disToObject[0]  <= 30 && disToObject[0]  > 20){
		Send_Data[0] = '1';
	}
	else if(disToObject[0]  <= 20 && disToObject[0]  > 10){
		Send_Data[0] = '2';
	}
	else if(disToObject[0]  <= 10){
		Send_Data[0] = '3';
	}
	else {
		Send_Data[0] = 'z';
	}

	//=====Getting the Reading of the second Sensor=====
	U_TRIGGER(PB2, B);

	duration 	= U_GET_PULSEWIDTH(PB3, B);
	disToObject[1] = U_GET_DISTANCE(duration);

	if(disToObject[1] > 30){
			Send_Data[1] = '0';
		}
		else if(disToObject[1]  <= 30 && disToObject[1]  > 20){
			Send_Data[1] = '1';
		}
		else if(disToObject[1]  <= 20 && disToObject[1]  > 10){
			Send_Data[1] = '2';
		}
		else if(disToObject[1]  <= 10){
			Send_Data[1] = '3';
		}
		else {
			Send_Data[1] = 'z';
		}

	//=====Getting the Reading of the third Sensor=====
	U_TRIGGER(PD6, D);

		duration 	= U_GET_PULSEWIDTH(PD7, D);
		disToObject[2] = U_GET_DISTANCE(duration);

		if(disToObject[2]  > 30){
				Send_Data[2] = '0';
			}
			else if(disToObject[2]  <= 30 && disToObject[2]  > 20){
				Send_Data[2] = '1';
			}
			else if(disToObject[2]  <= 20 && disToObject[2]  > 10){
				Send_Data[2] = '2';
			}
			else if(disToObject[2]  <= 10){
				Send_Data[2] = '3';
			}
			else {
				Send_Data[2] = 'z';
			}

	};
