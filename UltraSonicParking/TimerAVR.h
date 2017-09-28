/*
 * TimerAVR.h
 *
 *  Created on: Sep 9, 2017
 *      Author: Assassin
 *
 *  This driver is meant only for Timer 1 (16-bit timer). Usage of any other
 *  timer will demand modifying the driver itself to include the needed functions.
 */

#ifndef AVR_TIMER_H_
#define AVR_TIMER_H_

// Constant Definitions
#define F_CPU 8000000 // 8 MHz

// Function Prototypes
void timer_start();
void timer_stop();
void timer_clear();
uint16_t get_counter();


// Library Includes
#include "stdint.h"
#include "TimerAVR.c"

#endif
