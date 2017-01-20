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
#include <util/delay.h>

// own headers
#include "USART_tools.h"
#include "ADC_tools.h"
#include "Kalman_filter.h"
#include "FIR_tools.h"

//------------------------------------------------
//               MAIN
//------------------------------------------------
int main(void)
{
// local variables

// device initializations
	USARTInit(); 
	kalman_init(&ks, 0.1, 5, 50, 51);
	ADCInit();

// wait after the initialization is done
// it takes time to devices to get working...
    printf("Init Done... :)\n\r");
	_delay_ms(200);

// infinite loop
    while(1)
    {
		printf("%d\n\r",ADCRead());
    }
}