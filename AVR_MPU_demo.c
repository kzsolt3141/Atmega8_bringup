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

typedef struct  
{
	float angle;
	float bias;
	float P[2][2];
}Kalman_rotate;

//------------------------------------------------
//               GLOBAL VARIABLES
//------------------------------------------------
MPU9250Data aux;
BMP280FinalData aux2;
float xg = 0;
float yg = 0;
float zg = 0;
float rollAngle, pitchAngle;

Kalman_rotate krx,kry;
const float Q_angle = 0.0003;
const float Q_bias = 0.001;
const float R_measure = 0.1;
//------------------------------------------------
//               MAIN
//------------------------------------------------

void dothemath(Kalman_rotate* , int16_t, float);

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
		printf("%d %d\n\r\n\r", (int)pitchAngle, (int)krx.angle);
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
	
	//xg = (xg + (float)aux.gyro[0]/252/GYRO_SNS) * 0.9 + pitchAngle * 0.1;
	//yg = (yg + (float)aux.gyro[1]/252/GYRO_SNS) * 0.9 + rollAngle * 0.1;
	dothemath(&krx, aux.gyro[0], pitchAngle);

}

void dothemath(Kalman_rotate* kr, int16_t gyro, float acc_angle)
{
	float S;
	float K[2];
	float y;
	
	kr->angle += DT * ((float)gyro/GYRO_SNS - kr->bias);
	kr->P[0][0] += DT * (DT*kr->P[1][1] - kr->P[0][1] - kr->P[1][0] + Q_angle);
    kr->P[0][1] -= DT * kr->P[1][1];
    kr->P[1][0] -= DT * kr->P[1][1];
    kr->P[1][1] += Q_bias * DT;
	
	S = kr->P[0][0] + R_measure; 

    K[0] = kr->P[0][0] / S;
    K[1] = kr->P[1][0] / S;
	
	y = acc_angle - kr->angle;
	
	kr->angle += K[0] * y;
    kr->bias += K[1] * y;
	
	float P00_temp = kr->P[0][0];
    float P01_temp = kr->P[0][1];
	
	kr->P[0][0] -= K[0] * P00_temp;
    kr->P[0][1] -= K[0] * P01_temp;
    kr->P[1][0] -= K[1] * P00_temp;
    kr->P[1][1] -= K[1] * P01_temp;
};