/*
 * MPU6050.c
 *
 * Created: 12/24/2016 1:14:32 AM
 *  Author: Zsolt
 */ 

//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include "MPU6050.h"

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------

//------------------------------------------------
//               void MPU6050Init()
//------------------------------------------------
// this function initializes the MPU6050 by writing the devices configuration registers
// see MPU6050 register map document for more information..
void MPU6050Init()
{
	TWIWriteReg(MPU6050_I2C_ADDRESS, MPU6050_PWR_MGMT_1, 0x80);  // reset device
	TWIWriteReg(MPU6050_I2C_ADDRESS, MPU6050_SMPLRT_DIV, 0x08);  // set sample rate to 1kHz by dividing sample rate with 8
	TWIWriteReg(MPU6050_I2C_ADDRESS, MPU6050_CONFIG, 0x06);      // set the highest low pass filter DLPCGF 6
	TWIWriteReg(MPU6050_I2C_ADDRESS, MPU6050_GYRO_CONFIG, 0x08); // set gyro range to 500 degrees/s
	TWIWriteReg(MPU6050_I2C_ADDRESS, MPU6050_ACCEL_CONFIG, 0x08);// set accelero range to 4g
	TWIWriteReg(MPU6050_I2C_ADDRESS, MPU6050_PWR_MGMT_1, 0x00);  // disable reset condition
	TWIWriteReg(MPU6050_I2C_ADDRESS, MPU6050_PWR_MGMT_1, 0x08);  // disable temperature
	TWIWriteReg(MPU6050_I2C_ADDRESS, MPU6050_PWR_MGMT_2, 0x10);  // enable all the axis on gyro and accelerometer
}