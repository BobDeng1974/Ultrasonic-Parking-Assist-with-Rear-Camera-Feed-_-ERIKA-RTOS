/*
 * Ultrasonic.h
 *
 *  Created on: Sep 9, 2017
 *      Author: Assassin
 *
 *  This driver is meant only Ultrasonic Sensor HC-SR04. You can
 *  initialize the sensor using any GPIO pins and the known detection range.
 */

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#define F_CPU 8000000 // MHz
#define SOUND_SPEED 343 // meters/sec
#define SAMPLING_RATE 20 // msec (use any arbitrary value or not at all)
#define RESPONSE_MAX 200 // msec, arbitrary use - can be used to check for sensor trigger errors.

void U_INIT(uint8_t triggerPIN, uint8_t triggerPORT, uint8_t echoPIN, uint8_t echoPORT);
void U_TRIGGER(uint8_t triggerPin, uint8_t triggerPort);
uint16_t U_GET_PULSEWIDTH(uint8_t echoPIn,uint8_t echoPort);
uint16_t U_GET_DISTANCE(uint16_t duration);

#include "stdint.h"
#include "Ultrasonic.c"

#endif
