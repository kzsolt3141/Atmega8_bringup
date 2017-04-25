/*
 * Timers.c
 *
 * Created: 4/15/2017 8:57:43 PM
 *  Author: Zsolt
 */ 

#include "Timers.h"

void TIMER0Init()
{
	cli();
	SREG |= 1 << SREG_I;   // enable interrupt
	TCCR0 |= ((1 << CS02) | 
	          (0 << CS01) |
			  (1 << CS00)); // set prescaler to 1024
	TIMSK |= (1 << TOIE0);  // overflow interrupt enable
	sei();
}

ISR (TIMER0_OVF_vect)
{
	PORTB ^= 0x02;
}


