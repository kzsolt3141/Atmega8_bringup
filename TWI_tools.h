/*
 * TWI_tools.h
 *
 * Created: 12/22/2016 6:42:20 PM
 *  Author: Zsolt
 *-------------------------------
 * Do NOT modify this code!
 *-------------------------------
 */ 


#ifndef TWI_TOOLS_H_
#define TWI_TOOLS_H_
//------------------------------------------------
//               HEADERS
//------------------------------------------------
// TWI definitions, AVR Studio libraries
#include "defines.h"
#include <avr/io.h>
#include <avr/common.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include <util/delay.h>

//------------------------------------------------
//               DEFINES
//------------------------------------------------

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------
void TWIInit();
void TWIStart();
void TWIStop();
void TWIWrite(uint8_t);
uint8_t TWIReadACK();
uint8_t TWIReadNACK();
uint8_t TWIGetStatus();

#endif /* TWI_TOOLS_H_ */