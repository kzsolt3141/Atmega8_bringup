/*
 * USART_tools.c
 *
 * Created: 12/21/2016 10:46:13 PM
 *  Author: Zsolt
 * -------------------------------
 * Do NOT modify this code!
 *--------------------------------
 */ 
//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include "USART_tools.h"

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------

//------------------------------------------------
//                void USARTInit ()
//------------------------------------------------
//USARTInit function writes the registers needed for USARTinitialization
 void USARTInit ()
{
	cli();                                // disable all interrupts
	UCSRB |= (1 << RXEN)  | (1 << TXEN);  // Turn on the transmission and reception circuitry
	UCSRB |= (1 << RXCIE);                // interrupt in receive complete
    UCSRC |= (1 << UCSZ0) | (1 << UCSZ1); // Use 8-bit character sizes
    UBRRH = BAUD_PRESCALE >> 8;           // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
    UBRRL = BAUD_PRESCALE;                // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
	stdout = &mystdout;                   //Required for printf init
	sei();                                // enable interrupts
}

//------------------------------------------------
//                void USART_char_send(char *c)
//------------------------------------------------
//USART_char_send gets a parameter as a char pointer
// it will send out the character in which the pointer points trough USART
void USART_char_send(char *c)
{
	while ((UCSRA & (1 << UDRE)) == 0) {}; // wait until the USATR Data register is empty
	UDR = *c;                               // put the value from the pointed location in the USART Data register
}

//------------------------------------------------
//                int USART_printf(char , FILE *);
//------------------------------------------------
//USART_char_send gets a parameter as a char pointer
// it will send out the character in which the pointer points trough USART
int USART_printf(char c, FILE *stream) {
    USART_char_send(&c);
    return 0;
}

//------------------------------------------------
//                ISR(USART_RXC_vect)
//------------------------------------------------
// interrupt service routine for receive complete
// each time a character is sent from serial terminal 
// the routine saves the character into a global variable
ISR(USART_RXC_vect)
{
	USART_ReadByte = UDR; // save the contain
}