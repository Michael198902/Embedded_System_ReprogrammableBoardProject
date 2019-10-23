#if !defined(__MPU6050_H)
#define __MPU6050_H

#include "I2C/I2C.h"
#include "DELAY/DELAY.h"



// A Simple Module for control MPU6050 by
// ------------- MPU6050 REGISTERS ------------------------
// MPU6050 startup time 50m[s]
#define MPU6050_startup			50
// AD0 pin to GND
#define MPU6050_I2C			0x68
// AD0 pin to VDD
//#define MPU6050_I2C			0x69


#define MPU6050_TEMP_OUT_H		0x41
#define MPU6050_TEMP_OUT_L		0x42
#define MPU6050_PWR_MGM_1               0x6B
#define MPU6050_PWR_MGM_2               0x6C
#define MPU6050_SMPRT_DIV               0x19
#define MPU6050_CONFIG                  0x1A
#define MPU6050_GYRO_CONFIG             0x1B
#define MPU6050_ACCEL_CONFIG            0x1C
#define MPU6050_ACCEL_XOUT_H            0x3B
#define MPU6050_ACCEL_XOUT_L            0x3C
#define MPU6050_ACCEL_YOUT_H            0x3D
#define MPU6050_ACCEL_YOUT_L            0x3E
#define MPU6050_ACCEL_ZOUT_H            0x3F
#define MPU6050_ACCEL_ZOUT_L            0x40
#define MPU6050_GYRO_XOUT_H             0x43
#define MPU6050_GYRO_XOUT_L             0x44
#define MPU6050_GYRO_YOUT_H             0x45
#define MPU6050_GYRO_YOUT_L             0x46
#define MPU6050_GYRO_ZOUT_H             0x47
#define MPU6050_GYRO_ZOUT_L             0x48
#define MPU6050_USER_CTRL               0x6A


// Function Prototype
void MPU6050_Init(void);

unsigned char MPU6050_Read_RAW(int *data);
#endif

