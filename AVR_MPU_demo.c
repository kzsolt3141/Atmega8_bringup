/*
 * AVR_Gyro.c
 *
 * Created: 12/21/2016 10:44:40 PM
 *  Author: Zsolt
 */ 
//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include "defines.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/common.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// own headers
#include "USART_tools.h"

//------------------------------------------------
//               MAIN
//------------------------------------------------
int main(void)
{
// local variables
char i = 0;
// device initializations
	USARTInit(); 

// wait after the initialization is done
// it takes time to devices to get working...
    printf("Init Done :)\n\r");
	_delay_ms(200);

// infinite loop
    while(1)
    {
		printf("%d, %d\n\r",i, 255-i);
		_delay_ms(150);	
		i++;							   // wait 150 ms
    }
}