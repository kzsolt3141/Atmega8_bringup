/*
 * GPIO_tools.c
 *
 * Created: 1/4/2017 10:32:03 PM
 *  Author: Zsolt
 */ 
//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include "GPIO_tools.h"

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------

//------------------------------------------------
//               void LEDInit()
//------------------------------------------------
// initialize the PORTB to which LEDs are connected
void LEDInit()
{
	DDRB = 0xff;  // set PORTB data direction to OUTPUT
	PORTB = 0x00; // initialize PORTB with 0
}

//------------------------------------------------
//               void LEDTest()
//------------------------------------------------
// function will light up LEDs on board one by one
void LEDTest()
{
	PORTB = 1 << RIGHT; // light up right LED
	_delay_ms(300);     // wait 300 ms
	PORTB = 1 << FRONT; // light up front LED
	_delay_ms(300);		// wait 300 ms
	PORTB = 1 << LEFT;  // light up left LED
	_delay_ms(300);		// wait 300 ms
	PORTB = 1 << BACK;	// light up back LED
	_delay_ms(300);		// wait 300 ms
	PORTB = 0xFF;		// light up all LEDs
	_delay_ms(1000);		// wait 100 ms
	PORTB = ~PORTB;		// turn off all LEDs
	_delay_ms(1000);		// wait 100 ms
	PORTB = ~PORTB;		// light up all LEDs
	_delay_ms(1000);		// wait 100 ms
	PORTB = 0x00;		// turn off all LEDs
}					
//------------------------------------------------
//               void driveLED(uint16_t *xAxis, uint16_t *yAxis)
//------------------------------------------------
// get the pointer which points to  X and Y values 
// received from the accelerometer and light up LED 
// depending on the values
void driveLED(uint16_t *xAxis, uint16_t *yAxis)
{
	PORTB = 0x00;                                                //initialize PORTB with 0
	if (((*xAxis) > MIN_POS_VAL) & ((*xAxis) < MAX_POS_VAL))     //xAxis points to a positive value
	{															 
		PORTB |= 1 << BACK;                                      // light up BACK  LED
		PORTB &= ~ (1 << FRONT);                                 // turn off FRONT LED
	}
		else
		if (((*xAxis) > MIN_NEG_VAL) & ((*xAxis) < MAX_NEG_VAL)) //xAxis points to a negative value
	{
		PORTB |= 1 << FRONT;									 // light up FRONT  LED
		PORTB &= ~ (1 << BACK);									 // turn off BACK LED
	}
}