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
//               GLOBAL VARIABLES
//------------------------------------------------
MPU9250Data aux;
BMP280FinalData aux2;
float xg = 0;
float yg = 0;
float zg = 0;
float rollAngle, pitchAngle;

float state_angle = 0;
float state_bias = 0;
float P[2][2];
const float Q_angle = 0.0003;
const float Q_bias = 0.001;
const float R_measure = 0.1;
//------------------------------------------------
//               MAIN
//------------------------------------------------

int main(void)
{
// local variables

// device initializations
	USARTInit(); 
	TWIInit();
	MPU9250Init();
	MPU9250Calib();
	BMP280Init();
	TIMER0Init();
	
// wait after the initialization is done
// it takes time to devices to get working...
    printf("Init Done usbasp\n\r");
// infinite loop
    while(1)
    {
		//printf("%d %d %d\n\r", (int)xg, (int)yg, (int)zg );
		printf("%d %d\n\r\n\r", (int)xg, (int)state_angle);
		//_delay_ms(100);
    }
}

ISR (TIMER0_OVF_vect)
{
	TCNT0 = TIMER0_PRELOAD;
	MPU9250_getData(&aux);
    BMP280_getData(&aux2);
	//xg += (float)aux.gyro[0]/252/GYRO_SNS;
	//yg += (float)aux.gyro[1]/252/GYRO_SNS;
	//zg += (float)aux.gyro[2]/252/GYRO_SNS;
	rollAngle = atan2(-aux.acc[0],aux.acc[2])*R2D;
	pitchAngle = atan2(aux.acc[1], sqrt((float)aux.acc[0]*(float)aux.acc[0] + (float)aux.acc[2]*(float)aux.acc[2]))*R2D;
	
	xg = (xg + (float)aux.gyro[0]/252/GYRO_SNS) * 0.98 + pitchAngle * 0.02;
	
	float S;
	float K[2];
	float y;
	
	state_angle += DT * ((float)aux.gyro[0]/GYRO_SNS - state_bias);
	P[0][0] += DT * (DT*P[1][1] - P[0][1] - P[1][0] + Q_angle);
    P[0][1] -= DT * P[1][1];
    P[1][0] -= DT * P[1][1];
    P[1][1] += Q_bias * DT;
	
	S = P[0][0] + R_measure; 

    K[0] = P[0][0] / S;
    K[1] = P[1][0] / S;
	
	y = pitchAngle - state_angle;
	
	state_angle += K[0] * y;
    state_bias += K[1] * y;
	
	float P00_temp = P[0][0];
    float P01_temp = P[0][1];
	
	P[0][0] -= K[0] * P00_temp;
    P[0][1] -= K[0] * P01_temp;
    P[1][0] -= K[1] * P00_temp;
    P[1][1] -= K[1] * P01_temp;
	
}


