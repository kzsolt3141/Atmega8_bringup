/*
 * BMP280.h
 *
 * Created: 2/26/2017 11:27:13 PM
 *  Author: Zsolt
 */ 

#include "defines.h"
#include <stdio.h>

#ifndef BMP280_H_
#define BMP280_H_

#define BMP280_I2C_ADDRESS            (0x76)
#define BMP280_CHIPID                 (0x58)

#define BMP280_REGISTER_DIG_T1             0x88
#define BMP280_REGISTER_DIG_T2             0x8A
#define BMP280_REGISTER_DIG_T3             0x8C
#define BMP280_REGISTER_DIG_P1             0x8E
#define BMP280_REGISTER_DIG_P2             0x90
#define BMP280_REGISTER_DIG_P3             0x92
#define BMP280_REGISTER_DIG_P4             0x94
#define BMP280_REGISTER_DIG_P5             0x96
#define BMP280_REGISTER_DIG_P6             0x98
#define BMP280_REGISTER_DIG_P7             0x9A
#define BMP280_REGISTER_DIG_P8             0x9C
#define BMP280_REGISTER_DIG_P9             0x9E
#define BMP280_REGISTER_CHIPID             0xD0
#define BMP280_REGISTER_VERSION            0xD1
#define BMP280_REGISTER_SOFTRESET          0xE0
#define BMP280_REGISTER_CAL26              0xE1  // R calibration stored in 0xE1-0xF0
#define BMP280_REGISTER_CONTROL            0xF4
#define BMP280_REGISTER_CONFIG             0xF5
#define BMP280_REGISTER_PRESSUREDATA       0xF7
#define BMP280_REGISTER_TEMPDATA           0xFA

#define BMP280_CALIB_SIZE 24


typedef struct
{
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;
} BMP280CalibData;

typedef struct  
{
	uint8_t baro[3];
	uint8_t temp[3];
} BMP280RawData;

typedef struct  
{
	int32_t baro;
	uint32_t temp;
} BMP280FinalData;

extern void BMP280Init();
extern void BMP280_getData(BMP280FinalData * final);

extern BMP280CalibData calib;

#endif /* BMP280_H_ */