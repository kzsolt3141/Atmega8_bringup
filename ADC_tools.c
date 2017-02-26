/*
 * ADC_tools.c
 *
 * Created: 1/18/2017 11:43:26 PM
 *  Author: Zsolt
 */ 
//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include "ADC_tools.h"

//------------------------------------------------
//               EXTERN REDEFINITIONS
//------------------------------------------------
int16_t rawADC = 0;

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------

//------------------------------------------------
//                void ADCInit()
//------------------------------------------------
//initialize ADC
void ADCInit()
{
	ADMUX |= (1 << REFS0) ; // voltage ref = AVCC (also ADC0 channel selected)
	ADCSRA |= (1 << ADEN) | // enable ADC
	          (1 << ADSC) | // start conversion
		   // (1 << ADIE) | // ADC interrupt enable
			  (1 << ADPS2)| // sample prescaler
			  (1 << ADPS1)| // sample prescaler
			  (1 << ADPS0) ;// sample prescaler
}

//------------------------------------------------
//                uint16_t ADCRead()
//------------------------------------------------
//read one value from ADC
uint16_t ADCRead()
{
	ADCSRA |= (1<<ADSC);        // Start conversion
    while (ADCSRA & (1<<ADSC)); // wait for conversion to complete
    return ADC;                 //Store ADC value	
}

//------------------------------------------------
//                ISR(ADC_vect)
//------------------------------------------------
// interrupt from ADC conversion complete
// you can use filters in this ISR 
// but it will slow down the process
ISR(ADC_vect)
{
	rawADC = ADC;        // save ADC value in global variable
	ADCSRA |= (1<<ADSC); // start a new conversion
}