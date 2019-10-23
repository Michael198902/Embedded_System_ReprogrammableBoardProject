#if !defined(__IMU3000_H)
#define __IMU3000_H

#include "I2C/I2C.h"
#include "DELAY.h"
// A Simple Module for control IMU3000 by Mazeyar Cheguini March of 2012
// ------------- IMU3000 REGISTERS ------------------------
// IMU3000 startup time 50m[s]
#define IMU3000_startup			50
// AD0 pin to GND
#define IMU3000_I2C				0x68
// AD0 pin to VDD
//#define IMU3000_I2C			0x69
#define IMU3000_TEMP_OUT_H		0x1B
#define IMU3000_PWR_MGM			0x3E
#define IMU3000_X_OFFS_H		0x0C
#define IMU3000_X_OFFS_L		0x0D
#define IMU3000_Y_OFFS_H		0x0E
#define IMU3000_Y_OFFS_L		0x0F
#define IMU3000_Z_OFFS_H		0x10
#define IMU3000_Z_OFFS_L		0x11
// I2C I/O loggical ?????????????????????????
#define IMU3000_AUX_VDDIO		0x13
#define IMU3000_AUX_SLV_ADDR	0x14
#define IMU3000_SMPLRT_DIV		0x15
#define IMU3000_DLPF_FS			0x16
#define IMU3000_INT_CFG			0x17
#define IMU3000_AUX_BURST_ADDR	0x18
#define IMU3000_USER_CTRL		0x3D
#define	AUX_ID					0b01000000
#define	SMPLRT_DIV				0b00001001
#define	H_RESET					7

// Function Prototype
void IMU3000_Init(void);
unsigned char IMU3000_Read_RAW(int *data);
#endif

