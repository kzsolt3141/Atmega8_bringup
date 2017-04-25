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
#include <math.h>
#include <avr/io.h>
#include <util/delay.h>

// own headers
#include "USART_tools.h"
#include "TWI_tools.h"
#include "MPU9250.h"
#include "BMP280.h"
#include "Timers.h"

//------------------------------------------------
//               MAIN
//------------------------------------------------
int main(void)
{
// local variables
MPU9250Data aux;
BMP280FinalData aux2;
int8_t i = 0;
float xg = 0;
float yg = 0;
float zg = 0;
uint16_t a = 0;
// device initializations
	USARTInit(); 
	TWIInit();
	MPU9250Init();
	MPU9250Calib();
	BMP280Init();
	TIMER0Init();
	
	DDRB |= 0x02;
	PORTB |= 0x00;
	
// wait after the initialization is done
// it takes time to devices to get working...
    printf("Init Done usbasp\n\r");
// infinite loop
    while(1)
    {
		//TCCR1A = 0x00; // normal operation	
		//TCCR1B = 0x00;
		//TCCR1B |= 0x01;
		//TCNT1 = 0x0000;

		//MPU9250_getData(&aux);
		//BMP280_getData(&aux2);
		//xg += (float)aux.gyro[0]/40/GYRO_SNS;
		//yg += (float)aux.gyro[1]/40/GYRO_SNS;
		//zg += (float)aux.gyro[2]/40/GYRO_SNS;
		//printf("%d %d %d\n\r", (int)xg, (int)yg, (int)zg );

		//a = TCNT1;
		//printf("%u\n\r", a);
		
    }
}