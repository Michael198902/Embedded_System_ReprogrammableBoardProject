#include "mpu6050.h"

unsigned char MPU6050_Read[1];

void MPU6050_Init(void){
//	------------------- Enable write to EEPROM -------------------------------
    Delayms(50);

i2cReadByte(MPU6050_I2C, MPU6050_PWR_MGM_1, MPU6050_Read);
MPU6050_Read[0] &= (0<<7);

i2cWriteByte(MPU6050_I2C, MPU6050_PWR_MGM_1, MPU6050_Read[0]);
Delayms(1);
i2cReadByte(MPU6050_I2C, MPU6050_PWR_MGM_1, MPU6050_Read);
MPU6050_Read[0] |= 0x00;
i2cWriteByte(MPU6050_I2C, MPU6050_PWR_MGM_1, MPU6050_Read[0]);
Delayms(1);

    // CONFIGURACION power management 1
i2cReadByte(MPU6050_I2C, MPU6050_PWR_MGM_1, MPU6050_Read);
MPU6050_Read[0] &= (0<<7);

i2cWriteByte(MPU6050_I2C, MPU6050_PWR_MGM_1, MPU6050_Read[0]);
Delayms(1);
i2cReadByte(MPU6050_I2C, MPU6050_PWR_MGM_1, MPU6050_Read);
MPU6050_Read[0] |= 0x83;
i2cWriteByte(MPU6050_I2C, MPU6050_PWR_MGM_1, MPU6050_Read[0]);
Delayms(1);

// CONFIGURACION Sample Rate Divider
i2cReadByte(MPU6050_I2C, MPU6050_SMPRT_DIV , MPU6050_Read);
MPU6050_Read[0] = 0x4F;
i2cWriteByte(MPU6050_I2C, MPU6050_SMPRT_DIV , MPU6050_Read[0]);
Delayms(1);

//CONFIGURACION power management 2
i2cReadByte(MPU6050_I2C, MPU6050_PWR_MGM_2, MPU6050_Read);
MPU6050_Read[0] = 0xC0;
i2cWriteByte(MPU6050_I2C, MPU6050_PWR_MGM_2, MPU6050_Read[0]);
Delayms(1);


//CONFIGURACION  GYRO
i2cReadByte(MPU6050_I2C, MPU6050_GYRO_CONFIG, MPU6050_Read);
MPU6050_Read[0] = 0x00;
i2cWriteByte(MPU6050_I2C, MPU6050_GYRO_CONFIG, MPU6050_Read[0]);
Delayms(1);

//CONFIGURACION ACCEL
i2cReadByte(MPU6050_I2C, MPU6050_ACCEL_CONFIG, MPU6050_Read);
MPU6050_Read[0] = 0x00;
i2cWriteByte(MPU6050_I2C, MPU6050_ACCEL_CONFIG, MPU6050_Read[0]);
Delayms(1);
};

// ------------------------MPU6050 READ RAW DATA-------------------------------


unsigned char MPU6050_Read_RAW(int *data){
unsigned char error= 0, buffer[14];
error = i2cReadArray(MPU6050_I2C, MPU6050_ACCEL_XOUT_H, buffer,14);
*data++ = ((buffer[0]<<8)|buffer[1]);
*data++ = ((buffer[2]<<8)|buffer[3]);
*data++ = ((buffer[4]<<8)|buffer[5]);
*data++ = ((buffer[6]<<8)|buffer[7]);
*data++ = ((buffer[9]<<8)|buffer[8])>>2 & 0xFFFF;
*data++ = ((buffer[11]<<8)|buffer[10])>>2 & 0xFFFF;
*data++ = ((buffer[13]<<8)|buffer[12])>>2 & 0xFFFF;
return error;
};


