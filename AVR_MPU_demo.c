/*
 * AVR_Gyro.c
 *
 * Created: 12/21/2016 10:44:40 PM
 *  Author: Zsolt
 */ 
//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include <avr/io.h>
#include <avr/common.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// own headers
#include "USART_tools.h"
#include "TWI_tools.h"
#include "MPU6050.h"
#include "GPIO_tools.h"

//------------------------------------------------
//               MAIN
//------------------------------------------------
int main(void)
{
// local variables
	uint8_t TWIReadout;
	uint16_t XAxisValue, YAxisValue;
	uint16_t XOffset, YOffset;
	
// device initializations
	USARTInit(); 
	//TWIInit();
	//MPU6050Init();
	LEDInit();
	LEDTest();
// wait after the initialization is done
// it takes time to devices to get working...
    USART_string_send("\n\r Init Done :)\n\r");
	_delay_ms(500);
// read out values from X and Y, these will be the offset values 
// for further readouts
    //MPU6050Calibrate(&XOffset, &YOffset);

// infinite loop
    while(1)
    {
		USART_string_send("\n\r Init Done :) \n\r");
//		driveLED(&XAxisValue, &YAxisValue);				   // light up LEDs depending on values
		_delay_ms(1500);								   // wait 150 ms
    }
}