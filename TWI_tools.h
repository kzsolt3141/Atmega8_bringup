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
#include <util/twi.h>
#include "USART_tools.h"

//------------------------------------------------
//               DEFINES
//------------------------------------------------

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------
extern void TWIInit();
extern void TWIStart();
extern void TWIStop();
extern void TWISniff();
extern void TWIWrite(uint8_t);
extern uint8_t TWIReadACK();
extern uint8_t TWIReadNACK();
extern uint8_t TWIGetStatus();
extern void TWIWriteReg (const uint8_t, const uint8_t, const uint8_t);
void TWIReadRegBurst (uint8_t* buffer,const uint8_t slave_addr ,const uint8_t internal_addr, const uint8_t size);
#endif /* TWI_TOOLS_H_ */