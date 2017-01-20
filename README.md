# Atmega8_bringup
This project will try all the interfaces for an ATMEGA8 
1.) set up printf for UART printout:
	- create this: static FILE mystdout = FDEV_SETUP_STREAM(USART_printf, NULL, _FDEV_SETUP_WRITE);
	- create: int USART_printf(char c, FILE *stream) {
					    USART_char_send(&c);
					    return 0; }
	- use USART_char_send(&c) as a standard USART character output function

2.) printf is working with floating point valued too, 
	you need to do the following modifications in your project:
	a.) go to project properties: alt+F7
	b.) AVR/GNU C Linker -> Libraries
		- add libprintf_flt.a
		- add libm.a
	c.) AVR/GNU C Linker -> Miscellaneous
		- Other Link Flags : -Wl,-u,vfprintf -lprintf_flt -lm
	d.) now you can use printf for float and double printouts
