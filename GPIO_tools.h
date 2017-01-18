/*
 * GPIO_tools.h
 *
 * Created: 1/4/2017 10:30:30 PM
 *  Author: Zsolt
 *-------------------------------
 * Do NOT modify this code!
 *-------------------------------
 */ 


#ifndef GPIO_TOOLS_H_
#define GPIO_TOOLS_H_
//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include "defines.h"
#include <avr/io.h>
#include <avr/common.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//------------------------------------------------
//               DEFINES
//------------------------------------------------
// define the losition of the LEDS on the board,
// and with which pin are they connected
#define LEFT 2  // pin 1 of the PORTB
#define RIGHT 4 // pin 3 of the PORTB
#define FRONT 3 // pin 2 of the PORTB
#define BACK 1	// pin 0 of the PORTB

// define signed maximum and minimum values 
// for comparison at 16bit (MSB is the sign, negative numbers in C2)
// note: use an offset in each direction to get a
// smooth response
#define MIN_POS_VAL (0x0000 + 0x800)
#define MAX_POS_VAL (0x7FFF - 0x800)
#define MAX_NEG_VAL (0xFFFF - 0x800)
#define MIN_NEG_VAL (0x8000 + 0x800)
//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------
void LEDInit();
void LEDTest();
void driveLED(uint16_t *xAxis, uint16_t *yAxis);


#endif /* GPIO_TOOLS_H_ */