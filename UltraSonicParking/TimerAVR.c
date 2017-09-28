/*
 * TimerAVR.c
 *
 *  Created on: Sep 9, 2017
 *      Author: Assassin
 *
 *  This driver is meant only for Timer 1 (16-bit timer). Usage of any other
 *  timer will demand modifying the driver itself to include the needed functions.
 */

#include "ee.h"
#include "avr/io.h"
#include <avr/interrupt.h>

// global variables to be shared between the timer and the ultrasonic.
/* volatile uint16_t timerCounter = 0;
volatile extern uint16_t MAX_DISTANCE;
volatile extern uint16_t MAX_TIMEOUT;
volatile extern uint16_t distance;
volatile extern char running; */

/* This function configures the timer to operate without any prescaler and resets
 * the timer counter, it can be used to enable overflow interrupts by removing
 * the comments in the function. */
// arguments: none
// return: void
void timer_start()
{
	// setup 16 bit timer & enable interrupts, timer increments to 65535 //and interrupts on overflow
	TCCR1A = 0X00;
	TCCR1B = (0<<CS12)|(1<<CS11)|(0<CS10); // select internal clock with 1/8 prescaling
	TCNT1 = 0; // reset counter to zero

	// This part is used when using overflow interrupts
	/* TIMSK1 = 1<<TOIE1; // enable timer interrupt
	sei(); // enable all(global) interrupts */
}

/* This function stops the entire timer by clearing its clock, and it also
 * resets the counter timer. */
// arguments: none
// return: void
void timer_stop()
{
	TCCR1B = (0<<CS02)|(0<<CS01)|(0<<CS00); // stop timer
	TCNT1 = 0; // reset counter to zero
	//timerCounter = 0; // reset the overflow counter
}

/* This function only resets the counter so that it starts again from zero,
 * but it doesn't stop the counter. */
// arguments: none
// return: void
void timer_clear()
{
	TCNT1 = 0;
}

/* This function returns the value of the counter at the time it is called. */
// arguments: none
// return: uint16_t
uint16_t get_counter()
{
	return TCNT1;
}

// timer overflow interrupt, each time when timer value passes 65355 value
/*ISR(TIMER1_OVF_vect)
{
	cli();
	timerCounter++; // count the number of overflows
	// dont wait too long for the sonar end response, stop if time for measuring the distance exceeded limits
	uint32_t ticks = timerCounter * 65535 + TCNT1;
	if (ticks > 174927)
	{
		// timeout
		DDRB |= 0x10;
		PORTB |= 0x10;
		running = 0; // ultrasound scan done
		distance = MAX_DISTANCE + 2; // show that measurement failed with a timeout (could return max distance here if needed)
		timer_stop();
	}
}
*/
