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
//                void USART_hex_send(uint8_t *h)
//------------------------------------------------
// USART_hex_send receives a 8 bit int type pointer, it will print out
// 2 hex values one for the lower 4 bits and one for the upper 4 bits
void USART_hex_send(uint8_t *h)
{
	char aux;
	aux = (char) ((*h) >> 4);                      // put in the aux the upper 4 bits
	aux = (aux > 9) ? (aux + 0x37) : (aux + 0x30); // transform the value to the propper ASCII value
	USART_char_send(&aux);                         // send out one character
	aux = (char) ((*h) & 0x0F);                    // put in the aux the lower 4 bits
	aux = (aux > 9) ? (aux + 0x37) : (aux + 0x30); // transform the value to the propper ASCII value 
	USART_char_send(&aux);						   // send out one character
}

//------------------------------------------------
//                void USART_string_send(char* c)
//------------------------------------------------
// USART_string_send receives a pointer from a beginning of a string
// the function will print out character after character until it reaches 
// the 0x00 (terminate) character
void USART_string_send(char* c)
{
	while (*c != 0x00)      //0x00 end of a string
	{
		USART_char_send(c); // send out the character on which the pointer points
		c++;                // increment the pointer to point to the next character
	}
}	

//------------------------------------------------
//                void USART_int_send(uint16_t *i)
//------------------------------------------------
// USART_int_send receive a pointer of a 16 bit value and sends out trough USART
void USART_int_send(uint16_t *i)
{
	char string[8];            // this string will contain the cipher
	itoa(*i, string,10);       // stdlib.h function to transform signed integer into string
	USART_string_send(string); // send out the string containing the integer and the sign
}

//------------------------------------------------
//                void USART_int_send(uint16_t *i)
//------------------------------------------------
// interrupt service routine for receive complete
// each time a character is sent from serial terminal 
// the routine saves the character into a global variable
ISR(USART_RXC_vect)
{
	USART_ReadByte = UDR; // save the contain
}