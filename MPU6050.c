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
//               void MPU6050WriteReg (uint8_t addr, uint8_t data)
//------------------------------------------------
// this function writes a value into a slave's internal register
// for this to happen a series of steps are done in conformity with 
// the MUP6050 datasheet. Steps are listed below.
void MPU6050WriteReg (uint8_t addr, uint8_t data)
{
	uint8_t status;
	TWIStart();                               // send S (Start bit)
	if (TWIGetStatus() != 0x08)               // verify if S was sent
		printf("S bit error\n\r");
	TWIWrite(MPU6050_I2C_ADDRESS << 1);       // write to the slave address with W (write) condition 
	status = TWIGetStatus();                  // get the status of the transfer
	if (status != 0x18)                       // verify if slave responds to his address
	{
		printf("%x SLAVE lost\n\r", status);
	}		
	TWIWrite(addr);                           // send to slave the internal register address which will be written
	status = TWIGetStatus();                  // get the status of the transfer
	if (status != 0x28)						  // verify if the slave responds to the written address with ACK
	{
		printf("%x internal addr found\n\r", status);
	}		
	TWIWrite(data);                           // write the internal register with the data
	status = TWIGetStatus();				  // get the status of the transfer
	if (status != 0x28)						  // verify if the slave accepted writted data with ACK
	{
		printf("%x Data not written\n\r", status);
	}	
	TWIStop();                                // send P (stop) bit
}

//------------------------------------------------
//               uint8_t MPU6050ReadReg (uint8_t addr)
//------------------------------------------------
// this function reads out a value from a slaves internal register
// it will return that data
// read out an internal register through TWI contains a few steps 
// which are listed below
uint8_t MPU6050ReadReg (uint8_t addr)
{
	uint8_t data, status;
	TWIStart();									  // send S (Start bit)
	if (TWIGetStatus() != 0x08)					  // verify if S was sent
		printf("S bit error\n\r");
	TWIWrite(MPU6050_I2C_ADDRESS << 1);			  // write to the slave address with W (write) condition
	status = TWIGetStatus();					  // get the status of the transfer
	if (status != 0x18)							  // verify if slave responds to his address
	{
		printf("%x SLAVE at W lost\n\r", status);
	}		
	TWIWrite(addr);								  // send to slave the internal register address which will be read
	status = TWIGetStatus();					  // get the status of the transfer
	if (status != 0x28)							  // verify if the slave responds to the written address with ACK
	{
		printf("%x internal addr lost\n\r", status);
	}		
	TWIStart();                                   // send a repeated S (start) condition
	status = TWIGetStatus();					  // get the status of the transfer
	if (status != 0x10)							  // verify if the slave responds to the repeated start condition
	{
		printf("%x repeated start failed\n\r", status);
	}
	TWIWrite((MPU6050_I2C_ADDRESS << 1) | 1);	  // write to the slave address with R (read) condition
	status = TWIGetStatus();					  // get the status of the transfer
	if (status != 0x40)							  // verify if slave responds to his address
	{
		printf("%x Slave at R lost\n\r", status);
	}
	data = TWIReadNACK();						  // read out data from with NACK (only one data will be read out, no need for ACK)
	status = TWIGetStatus();					  // get the status of the transfer
	if (status != 0x58)							  // verify if transfer was OK
	{
		printf("%x data with NACK lost\n\r", status);
	}
	TWIStop();                                   // send P (stop) bit
	return data;                                 // return the read out data
}

//------------------------------------------------
//               void MPU6050Init()
//------------------------------------------------
// this function initializes the MPU6050 by writing the devices configuration registers
// see MPU6050 register map document for more information..
void MPU6050Init()
{
//------------------------------------------------
//               TEMA 1
// momentan dispozitivul masoara numai pa axa X
// in fisierul MPU6050 modificati valorile de initializare
// astfel incat dispozitivul sa masoara si pe axa Y
// trebuie sa modificati valoarea numai la un singur registru
//      - TEMA 1.1 care este regitrul pe care trebuie modificat
//      - TEMA 1.2 care este noua valoare?
//------------------------------------------------
	MPU6050WriteReg(MPU6050_PWR_MGMT_1, 0x80);  // reset device
	MPU6050WriteReg(MPU6050_SMPLRT_DIV, 0x08);  // set sample rate to 1kHz by dividing sample rate with 8
	MPU6050WriteReg(MPU6050_CONFIG, 0x06);      // set the highest low pass filter DLPCGF 6
	MPU6050WriteReg(MPU6050_GYRO_CONFIG, 0x08); // set gyro range to 500 degrees/s
	MPU6050WriteReg(MPU6050_ACCEL_CONFIG, 0x08);// set accelero range to 4g
	MPU6050WriteReg(MPU6050_PWR_MGMT_1, 0x00);  // disable reset condition
	MPU6050WriteReg(MPU6050_PWR_MGMT_1, 0x08);  // disable temperature
	MPU6050WriteReg(MPU6050_PWR_MGMT_2, 0x10);  // enable all the axis on gyro and accelerometer
}

//------------------------------------------------
//               void MPU6050Calibrate(uint8_t*, uint8_t*)
//------------------------------------------------
//calibrating the accelerometer by definig x and y offset
void MPU6050Calibrate(uint16_t* XOffset, uint16_t* YOffset)
{
	uint8_t TWIReadout;
	TWIReadout = MPU6050ReadReg(MPU6050_ACCEL_XOUT_H); // read out accelerometer X axis upper byte
	*XOffset = TWIReadout << 8;                      // insert into final variable (higher 8bits)
	TWIReadout = MPU6050ReadReg(MPU6050_ACCEL_XOUT_L); // read out accelerometer X axis lower byte
	*XOffset |= TWIReadout;						   // insert into final variable (lower 8 bits)
	*XOffset = -(*XOffset);                             // offset is the negative read out value
	
	TWIReadout = MPU6050ReadReg(MPU6050_ACCEL_YOUT_H); // read out accelerometer Y axis upper byte
	*YOffset = TWIReadout << 8;					   // insert into final variable (higher 8bits)
	TWIReadout = MPU6050ReadReg(MPU6050_ACCEL_YOUT_L); // read out accelerometer Y axis lower byte
	*YOffset |= TWIReadout;						   // insert into final variable (lower 8 bits)
	*YOffset = -(*YOffset);							   // offset is the negative read out value
	
}