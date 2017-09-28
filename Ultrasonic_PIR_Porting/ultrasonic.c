/*
 * ultrasonic.c
 *	Ultrasonic sensor implementation test
 *  Created on: Aug 10, 2017
 *      Author: Ahmed
 */

#include "ee.h"
#include "Arduino.h"

extern int led;
extern int ECHO;
extern int TRIGGER;
extern long duration;
extern long distance;
long temp = 0;

long measure_time();
void calculate_distance();

TASK(USonicTask) {
	calculate_distance();
	if(distance > 20) digitalWrite(led, HIGH);
	else digitalWrite(led, LOW);
	delay(200);
};

long measure_time()
{
	digitalWrite(TRIGGER, LOW);
	delayMicroseconds(2);
	digitalWrite(TRIGGER, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIGGER, LOW);
	duration = pulseIn(ECHO,HIGH,3000);
	if (duration == 0)
	{
		duration = 10000;
	}
	return duration;
}

void calculate_distance()
{
	measure_time();
	distance = duration /29 / 2 ;
}
