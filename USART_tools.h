/*
 * USART_tools.h
 *
 * Created: 12/21/2016 10:47:01 PM
 *  Author: Zsolt
 * -------------------------------
 * Do NOT modify this code!
 *--------------------------------
 */ 


#ifndef USART_TOOLS_H_
#define USART_TOOLS_H_
//------------------------------------------------
//               HEADERS
//------------------------------------------------
// USART definitions, AVR Studio libraries
#include <stdlib.h>
#include <avr/io.h>
#include <avr/common.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//------------------------------------------------
//               DEFINES
//------------------------------------------------

//define USART baud rate, this value will be identical with the
// baud rate of the COM port in windows with which the Arduino 
// communicates with PC (see Device Manager!!)
#define USART_BAUDRATE 1200 
//calculate from Baud rate the prescaler value for the microcontroller
// baud rate counter
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1) 

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------
void USARTInit();
void USART_char_send(char *c);
void USART_hex_send(uint8_t * h);
void USART_string_send(char *c);
void USART_int_send(uint16_t *i);
ISR(USART_RXC_vect);

//------------------------------------------------
//               VARIABLES
//------------------------------------------------
uint8_t USART_ReadByte;

#endif /* USART_TOOLS_H_ */