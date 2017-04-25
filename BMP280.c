/*
 * BMP280.c
 *
 * Created: 3/3/2017 11:13:51 PM
 *  Author: Zsolt
 */ 
#include "BMP280.h"
#include "TWI_tools.h"

BMP280CalibData calib;

void BMP280Init()
{
	uint8_t cal[24];
	TWIWriteReg(BMP280_I2C_ADDRESS, BMP280_REGISTER_CONTROL, 0xFF); //high resolution and normal mode
	TWIWriteReg(BMP280_I2C_ADDRESS, BMP280_REGISTER_CONFIG, 0xB0);  //
	
	TWIReadRegBurst(cal,BMP280_I2C_ADDRESS,BMP280_REGISTER_DIG_T1,BMP280_CALIB_SIZE);
	calib.dig_T1 = ((uint16_t)cal[1] << 8) + (uint16_t)cal[0];
	calib.dig_T2 = ((uint16_t)cal[3] << 8) + (uint16_t)cal[2];
	calib.dig_T3 = ((uint16_t)cal[5] << 8) + (uint16_t)cal[4];
	calib.dig_P1 = ((uint16_t)cal[7] << 8) + (uint16_t)cal[6];
	calib.dig_P2 = ((uint16_t)cal[9] << 8) + (uint16_t)cal[8];
	calib.dig_P3 = ((uint16_t)cal[11] << 8) + (uint16_t)cal[10];
	calib.dig_P4 = ((uint16_t)cal[13] << 8) + (uint16_t)cal[12];
	calib.dig_P5 = ((uint16_t)cal[15] << 8) + (uint16_t)cal[14];
	calib.dig_P6 = ((uint16_t)cal[17] << 8) + (uint16_t)cal[16];
	calib.dig_P7 = ((uint16_t)cal[19] << 8) + (uint16_t)cal[18];
	calib.dig_P8 = ((uint16_t)cal[21] << 8) + (uint16_t)cal[20];
	calib.dig_P9 = ((uint16_t)cal[23] << 8) + (uint16_t)cal[22];
}


extern void BMP280_getData(BMP280FinalData * final)
{
	int32_t t_fine, adc_T, adc_P;
	int32_t var1, var2, p;
	//uint8_t data[6];
	BMP280RawData data;
	
	//readout raw data
	TWIReadRegBurst(&data,BMP280_I2C_ADDRESS,BMP280_REGISTER_PRESSUREDATA,6);
	adc_P = ((int32_t)data.baro[0] << 16) + ((int32_t)data.baro[1] << 8) + (int32_t)(data.baro[2] >> 4);
	adc_T = ((int32_t)data.temp[0] << 16) + ((int32_t)data.temp[1] << 8) + (int32_t)(data.temp[2] >> 4);
		// calculate temperature from raw	var1 = ((((adc_T >> 3) - ((int32_t)calib.dig_T1 << 1))) * ((int32_t)calib.dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)calib.dig_T1)) * ((adc_T >> 4) - ((int32_t)calib.dig_T1))) >> 12) * ((int32_t)calib.dig_T3)) >> 14;	t_fine = var1 + var2;
	final->temp =  ((t_fine * 5 + 128) >> 8);
	
	//calculate pressure from raw
	var1 = (((int32_t)t_fine)>>1) - (int32_t)64000;
	var2 = (((var1>>2) * (var1>>2)) >> 11 ) * ((int32_t)calib.dig_P6);
	var2 = var2 + ((var1*((int32_t)calib.dig_P5))<<1);
	var2 = (var2>>2)+(((int32_t)calib.dig_P4)<<16);
	var1 = (((calib.dig_P3 * (((var1>>2) * (var1>>2)) >> 13 )) >> 3) + ((((int32_t)calib.dig_P2) * var1)>>1))>>18;
	var1 =((((32768+var1))*((int32_t)calib.dig_P1))>>15);
	if (var1 == 0)
	{
		return 0; // avoid exception caused by division by zero
	}
	p = (((uint32_t)(((int32_t)1048576)-adc_P)-(var2>>12)))*3125;
	if (p < 0x80000000)
	{
		p = (p << 1) / ((uint32_t)var1);
	}
	else
	{
		p = (p / (uint32_t)var1) * 2;
	}
	var1 = (((int32_t)calib.dig_P9) * ((int32_t)(((p>>3) * (p>>3))>>13)))>>12;
	var2 = (((int32_t)(p>>2)) * ((int32_t)calib.dig_P8))>>13;
	final->baro = ((uint32_t)((int32_t)p + ((var1 + var2 + calib.dig_P7) >> 4)));
}	
