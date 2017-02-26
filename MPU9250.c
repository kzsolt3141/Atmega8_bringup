/*
 * MPU9250.c
 *
 * Created: 2/26/2017 8:33:40 PM
 *  Author: Zsolt
 */ 

//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include "MPU9250.h"

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------

//------------------------------------------------
//               void MPU9250Init()
//------------------------------------------------
// this function initializes the MPU9250 by writing the devices configuration registers
// see MPU9250 register map document for more information..
void MPU9250Init()
{
	TWIWriteReg(MPU9250_I2C_ADDRESS,MPU9250_PWR_MGMT_1, 0x80);    // reset device
	_delay_ms(100);												  
	TWIWriteReg(MPU9250_I2C_ADDRESS,MPU9250_PWR_MGMT_1, 0x03);    // disable reset condition
	TWIWriteReg(MPU9250_I2C_ADDRESS,MPU9250_CONFIG, 0x00);        // set the highest low pass filter DLPCGF 6
	TWIWriteReg(MPU9250_I2C_ADDRESS,MPU9250_GYRO_CONFIG, 0x18);   // set gyro range to 500 degrees/s
	TWIWriteReg(MPU9250_I2C_ADDRESS, MPU9250_ACCEL_CONFIG, 0x10); // set accelero range
	TWIWriteReg(MPU9250_I2C_ADDRESS,MPU9250_INT_PIN_CFG, 0x02); // i2c bypass mode
	_delay_ms(100);
	TWIWriteReg(AK8963_DEFAULT_ADDRESS, AK8963_RA_CNTL1, 0x11);
	_delay_ms(100);
	
	
}
