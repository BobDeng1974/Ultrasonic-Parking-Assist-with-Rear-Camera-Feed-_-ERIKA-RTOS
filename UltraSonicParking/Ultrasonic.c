/*
 * Ultrasonic.c
 *
 *  Created on: Sep 9, 2017
 *      Author: Assassin
 *
 *  This driver is meant only Ultrasonic Sensor HC-SR04. You can
 *  initialize the sensor using any GPIO pins and the known detection range.
 */

#include "ee.h"
#include "avr/io.h"
#include <avr/interrupt.h>
#include "TimerAVR.h"
#include "Avr_DIO.h"

// global variables to be shared between the timer and the ultrasonic, and interrupts.
/*volatile uint16_t MAX_DISTANCE;
volatile uint16_t MAX_TIMEOUT;
volatile uint16_t distance = 30;
volatile char running;
volatile char up;
volatile extern uint16_t timerCounter;*/

//volatile uint16_t MAX_DISTANCE;
//volatile uint16_t MAX_TIMEOUT; // to determine if sensor is out of range.
volatile uint16_t distance;

/* This function initializes the sensor and stores the sensor pin data into global
 * variables. */
// arguments: uint8_t - both PIN and PORT for the trigger and echo of the sensor AND the sensor range.
// return: void
void U_Init(uint8_t triggerPIN, uint8_t triggerPORT, uint8_t echoPIN, uint8_t echoPORT)
{
	// In case of using a different sensor, passing its known range may be beneficial.
	//MAX_DISTANCE = max_distance;
	//MAX_TIMEOUT = (((MAX_DISTANCE/100)/171.5)*1000000)/0.05; // Use a correct formula to calculate the max timeout.

	// Set the direction of the specified pins/ports and save them into global variables.
	pin_Dir(triggerPORT, triggerPIN, 1);
	pin_Dir(echoPORT, echoPIN, 0);


	// Use this part in case of using edge triggered external interrupts.
	// Be sure to use interrupt-capable pins.
	/* sei();
	EICRA |= (0 << ISC11) | (1 << ISC10); // enable interrupt on any(rising/dropping) edge
	EIMSK |= (1 << INT1);	// Turns on INT1 */
}

/* This function triggers the sensor and sends the ultrasonic pulses. */
// arguments: none
// return: void
void U_TRIGGER(uint8_t triggerPIN,uint8_t triggerPORT)
{
	// Flag initializations used for the interrupts if implemented.
	/* running = 1;
	up = 0; */

	pin_Write(triggerPORT, triggerPIN, 0);	//Clear trigger pin
	_delay_us(2);					//Delaying for 2u seconds to make sure the Port  is ready.
	pin_Write(triggerPORT, triggerPIN, 1);	//Setting the pIn.
	_delay_us(10);					//Delaying for 10u seconds for the second wave to be sent.
	pin_Write(triggerPORT, triggerPIN, 0);	//Then again Clear the Pin.
}

/* This function calculates the ECHO signal width and returns the duration. */
// arguments: none
// return: uint16_t
uint16_t U_GET_PULSEWIDTH(uint8_t echoPIN,uint8_t echoPORT)
{
	uint32_t i,result;

	//Wait for the rising edge
	for(i = 0; i < 6000000; i++)
	{
		if(!pin_State(echoPORT, echoPIN)) continue;
		else	break;
	}

	if(i == 6000000)
		return 0xffff; //Indicates time out

	//High Edge Found

	//Setup Timer1 to start counting
	timer_start();

	//Now wait for the falling edge
	for(i = 0; i < 6000000; i++)
	{
		if(pin_State(echoPORT, echoPIN))
		{
			if(get_counter() > 60000) break;
			else	continue;
		}
		else
			break;
	}

	if(i == 6000000)
		return 0xffff; //Indicates time out

	//Falling edge found
	result = get_counter();

	//Stop Timer
	timer_stop();

	if(result > 60000)
		return 0xfffe; //No obstacle
	else
		return (result >> 1);
}

/* This function takes the duration of the ECHO signal and uses it calculate
 * the distance of the obstacle detected by the sensor. */
// arguments: uint16_t - duration
// return: uint16_t
uint16_t U_GET_DISTANCE(uint16_t duration)
{
	distance = ((duration * 0.0343) / 2);
	return distance;
}

// Interrupt Service Routine for the edge-triggered interrupt implemented on ECHO pin
/*
ISR(INT1_vect)
{
	cli();
	if(running)
	{
		//accept interrupts only when sonar was started
		if(up == 0)
		{
			// voltage rise, start time measurement
			up = 1;
			timer_start();
		}
		else
		{
			// voltage drop, stop time measurement
			up = 0;
			timer_stop();

			// convert from time to distance(millimeters): d = [ time_s * 340m/s ] / 2 = time_us/58
			distance = (timerCounter * 65535 + TCNT1) / 58;
			running = 0;
		}
	}
}
*/
