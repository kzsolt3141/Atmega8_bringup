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
BMP280CalibData calib;
//------------------------------------------------
//               void MPU9250Init()
//------------------------------------------------
// this function initializes the MPU9250 by writing the devices configuration registers
// see MPU9250 register map document for more information..
void MPU9250Init()
{
	uint8_t cal[24];
	//general device settings
	TWIWriteReg(MPU9250_I2C_ADDRESS,MPU9250_PWR_MGMT_1, 0x80);                             // reset device 1_0000000
	_delay_ms(100);												                           
	TWIWriteReg(MPU9250_I2C_ADDRESS,MPU9250_PWR_MGMT_1, 0x03);                             // disable reset condition 00000_000
	
	// gyro settings											                           
	TWIWriteReg(MPU9250_I2C_ADDRESS,MPU9250_CONFIG, 0x00);                                 // set the  low pass filter DLPCGF 00000_000
	TWIWriteReg(MPU9250_I2C_ADDRESS,MPU9250_GYRO_CONFIG, 0x08);                            // set gyro range to 500 (65.5) degrees/s 000_01_X_00
	
	// accelero settings										                           
	TWIWriteReg(MPU9250_I2C_ADDRESS, MPU9250_ACCEL_CONFIG, 0x08);                          // set accelero range 4g 000_01_000 (8192)
	TWIWriteReg(MPU9250_I2C_ADDRESS, MPU9250_ACCEL_CONFIG2, 0x00);   					   // set accelero low pass filter DLPCFG 00000_000
	
	// i2c settings
	TWIWriteReg(MPU9250_I2C_ADDRESS,MPU9250_INT_PIN_CFG, 0x02);                            // bypass mode
	_delay_ms(100);
	
	// magneto settings
	TWIWriteReg(AK8963_DEFAULT_ADDRESS, AK8963_RA_CNTL1, 0x16);							   // 16 bit values with continiuos measurement mode
	_delay_ms(100);
	
	// switch to I2C to master mode (internal I2C bus isolated from external SDA SCL)
	
	// https://github.com/kriswiner/MPU-9250/issues/86
	TWIWriteReg(MPU9250_I2C_ADDRESS, MPU9250_INT_PIN_CFG,  0x00);                          // normal mode (bypass disabled)
	TWIWriteReg(MPU9250_I2C_ADDRESS, MPU9250_I2C_MST_CTRL, 0x5D);                          // I2C multi master enable at 300kHz
	TWIWriteReg(MPU9250_I2C_ADDRESS, MPU9250_USER_CTRL,    0x20);
	
	TWIWriteReg(MPU9250_I2C_ADDRESS, MPU9250_I2C_SLV0_CTRL, 0x00);                         // disable slave
	TWIWriteReg(MPU9250_I2C_ADDRESS, MPU9250_I2C_SLV0_ADDR, AK8963_DEFAULT_ADDRESS | 0x80);// set first slave to magnetometer
	TWIWriteReg(MPU9250_I2C_ADDRESS, MPU9250_I2C_SLV0_REG,  AK8963_RA_HXL);                // start reading magneto from this addr
	TWIWriteReg(MPU9250_I2C_ADDRESS, MPU9250_I2C_SLV0_CTRL, 0x87);                         // read transfer, 7 registers
}

void MPU9250Calib()
{
	uint8_t i, low, high;
	int16_t medx = 0;
	int16_t medy = 0;
	int16_t medz = 0;
	MPU9250RawData buf;
	
// gyro calibration	
	for(i = 0; i < 64; i++)
	{
		TWIReadRegBurst(&buf.accx, MPU9250_I2C_ADDRESS, MPU9250_ACCEL_XOUT_H, 21);
		medx -= ((uint16_t)buf.gyrox[0]<<8) + buf.gyrox[1];
		medy -= ((uint16_t)buf.gyroy[0]<<8) + buf.gyroy[1];
		medz -= ((uint16_t)buf.gyroz[0]<<8) + buf.gyroz[1];
	}
	// calculate half of the offset
	medx = medx >> 7;
	medy = medy >> 7;
	medz = medz >> 7;
	// set X offset
	low = medx;
	high = medx >> 8;
	TWIWriteReg(MPU9250_I2C_ADDRESS, MPU9250_XG_OFFSET_H, high);
	TWIWriteReg(MPU9250_I2C_ADDRESS, MPU9250_XG_OFFSET_L, low);
	// set Y offset
	low = medy;
	high = medy >> 8;
	TWIWriteReg(MPU9250_I2C_ADDRESS, MPU9250_YG_OFFSET_H, high);
	TWIWriteReg(MPU9250_I2C_ADDRESS, MPU9250_YG_OFFSET_L, low);
	// set Z offset
	low = medz;
	high = medz >> 8;
	TWIWriteReg(MPU9250_I2C_ADDRESS, MPU9250_ZG_OFFSET_H, high);
	TWIWriteReg(MPU9250_I2C_ADDRESS, MPU9250_ZG_OFFSET_L, low);
}

void MPU9250_getData(MPU9250Data * data)
{
	MPU9250RawData buf;
	TWIReadRegBurst(&buf.accx, MPU9250_I2C_ADDRESS, MPU9250_ACCEL_XOUT_H, 21);
	data->acc[0] = ((uint16_t)buf.accx[0]<<8) + buf.accx[1];
	data->acc[1] = ((uint16_t)buf.accy[0]<<8) + buf.accy[1];
	data->acc[2] = ((uint16_t)buf.accz[0]<<8) + buf.accz[1];		
	
	data->tmp = ((uint16_t)buf.tmp[0]<<8) + buf.tmp[1];
	
	data->gyro[0] = ((uint16_t)buf.gyrox[0]<<8) + buf.gyrox[1];
	data->gyro[1] = ((uint16_t)buf.gyroy[0]<<8) + buf.gyroy[1];
	data->gyro[2] = ((uint16_t)buf.gyroz[0]<<8) + buf.gyroz[1];
	
	data->mag[0] = ((uint16_t)buf.magx[1]<<8) + buf.magx[0];
	data->mag[1] = ((uint16_t)buf.magy[1]<<8) + buf.magy[0];
	data->mag[2] = ((uint16_t)buf.magz[1]<<8) + buf.magz[0];
	
	////processing...
	////angles accelero
	//rollAngle = atan2(Ay,Az)*R2D;
	//pitchAngle = atan2((double)-Ax, sqrt((double)Ay*(double)Ay + (double)Az*(double)Az))*R2D;
	////temperature mpu9250
	//realTemp = (T - 21)/333.87 + 21;
	////magnetom processing
	//p = ((float)aux.mag[0] - 202.0) / (-4.9);
	//r = ((float)aux.mag[1] - 310.0) / (-4.74444);
	//y = ((float)aux.mag[2] - 74) / (-5.53333);
}