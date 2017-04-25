/*
 * USART_tools.h
 *
 * Created: 12/21/2016 10:47:01 PM
 *  Author: Zsolt
 */ 


#ifndef USART_TOOLS_H_
#define USART_TOOLS_H_
//------------------------------------------------
//               HEADERS
//------------------------------------------------
// USART definitions, AVR Studio libraries
#include "defines.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/common.h>
#include <avr/interrupt.h>

//------------------------------------------------
//               DEFINES
//------------------------------------------------

//define USART baud rate, this value will be identical with the
// baud rate of the COM port in windows with which the Arduino 
// communicates with PC (see Device Manager!!)
#define USART_BAUDRATE 38400
//calculate from Baud rate the prescaler value for the microcontroller
// baud rate counter
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1) 

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------
extern void USARTInit();
extern void USART_char_send(char *c);
extern int USART_printf(char c, FILE *stream);
ISR(USART_RXC_vect);

//------------------------------------------------
//               VARIABLES
//------------------------------------------------
extern uint8_t USART_ReadByte;
static FILE mystdout = FDEV_SETUP_STREAM(USART_printf, NULL, _FDEV_SETUP_WRITE);
#endif /* USART_TOOLS_H_ */