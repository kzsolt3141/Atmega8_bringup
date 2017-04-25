/*
 * Timers.h
 *
 * Created: 4/15/2017 8:57:29 PM
 *  Author: Zsolt
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

#include "avr/io.h"
#include "avr/interrupt.h"

extern void TIMER0Init();
ISR (TIMER0_OVF_vect);


#endif /* TIMERS_H_ */