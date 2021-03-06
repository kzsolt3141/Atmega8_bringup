/*
 * ADC_tools.h
 *
 * Created: 1/18/2017 11:43:26 PM
 *  Author: Zsolt
 */ 


#ifndef ADC_TOOLS_H_
#define ADC_TOOLS_H_

//------------------------------------------------
//               HEADERS
//------------------------------------------------
// AVR studio headers
#include <avr/io.h>
#include <avr/common.h>
#include <avr/interrupt.h>

//------------------------------------------------
//               DEFINES
//------------------------------------------------

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------
extern void ADCInit();
extern uint16_t ADCRead();

//------------------------------------------------
//               VARIABLES
//------------------------------------------------
extern int16_t rawADC;


#endif /* ADC_TOOLS_H_ */