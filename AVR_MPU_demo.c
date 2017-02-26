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
#include "MPU9250.h"
#include "BMP280.h"

//------------------------------------------------
//               MAIN
//------------------------------------------------
int main(void)
{
// local variables

// device initializations
	USARTInit(); 
	ADCInit();
	MPU9250Init();
	

// wait after the initialization is done
// it takes time to devices to get working...
    printf("Init Done... :)\n\r");
	_delay_ms(200);
	printf("%x\n\r",TWIReadReg(AK8963_DEFAULT_ADDRESS, AK8963_RA_WIA));
	printf("%x\n\r",TWIReadReg(BMP280_I2C_ADDRESS, BMP280_REGISTER_CHIPID));
// infinite loop
    while(1)
    {
		/*
		printf("%d %d %d %x\n\r",TWIReadReg(MPU9250_I2C_ADDRESS, MPU9250_ACCEL_XOUT_H), 
				TWIReadReg(MPU9250_I2C_ADDRESS, MPU9250_ACCEL_YOUT_H), 
				TWIReadReg(MPU9250_I2C_ADDRESS, MPU9250_ACCEL_ZOUT_H),
				TWIReadReg(MPU9250_I2C_ADDRESS, AK8963_RA_WIA));
				*/
    }
}