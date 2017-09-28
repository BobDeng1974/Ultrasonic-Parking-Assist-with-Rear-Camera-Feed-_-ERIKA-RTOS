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
#include "Arduino.h"
#include "avr/io.h"
#include "util/delay.h"



#define US_PORT PORTB
#define US_PIN PINB
#define US_POS PB1
#define US_DDR DDRB

int distance;
long duration;

//Function Prototype
uint16_t getPulseWidth();

TASK(TaskL1) {

	//Clearing and Setting the Trigger Pin

	PORTB &= ~(1 << PB0);	//CLearing the Pin
	_delay_us(2);			//Delaying for 2u seconds to make sure the Port  is ready
	PORTB |= (1 << PB0);	//Setting the pIn
	_delay_us(10);			//Delaying for 10u seconds for the second wave to be sent.
	PORTB &= ~(1 << PB0);	//Thn again Clear the Pin

	//Calculating distance.
	duration = getPulseWidth();
	distance = ( (duration*.0343)/2 );


	/* Testing the distance between the Ultrasonic and an Object,
	 * The Buzzer's sound recurrence depends on the distance measured */

	if( distance >20 ){
		PORTB &= ~(1 << PB5);
	}
	else if( (distance <=20) &&(distance > 15) ){
		PORTB |= (1 << PB5);
		_delay_ms(750);
		PORTB &= ~(1 << PB5);
		_delay_ms(750);
	}
	else if( (distance <=15)&&(distance >10) ){
		PORTB |= (1 << PB5);
		_delay_ms(300);
		PORTB &= ~(1 << PB5);
		_delay_ms(300);
	}
	else if( distance <=10 ){
		PORTB |= (1 << PB5);
	}




};


uint16_t getPulseWidth()
		    {
		       uint32_t i,result;

		       //Wait for the rising edge
		       for(i=0;i<600000;i++)
		       {
		          if(!(US_PIN & (1<<US_POS))) continue; else break;
		       }

		       if(i==600000)
		          return 0xffff; //Indicates time out

		       //High Edge Found

		       //Setup Timer1
		       TCCR1A=0X00;
		       TCCR1B=(1<<CS11); //Prescaler = Fcpu/8
		       TCNT1=0x00;       //Init counter

		       //Now wait for the falling edge
		       for(i=0;i<600000;i++)
		       {
		          if(US_PIN & (1<<US_POS))
		          {
		             if(TCNT1 > 60000) break; else continue;
		          }
		          else
		             break;
		       }

		       if(i==600000)
		          return 0xffff; //Indicates time out

		       //Falling edge found

		       result=TCNT1;

		       //Stop Timer
		       TCCR1B=0x00;

		       if(result > 60000)
		          return 0xfffe; //No obstacle
		       else
		          return (result>>1);
		    }





