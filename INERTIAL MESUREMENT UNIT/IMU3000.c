#include "IMU3000.h"
unsigned char IMU3000_Read[1];
void IMU3000_Init(void){
//	------------------- Enable write to EEPROM -------------------------------
// Reset device @ first and select clock source to Internal Oscillator @P42
i2cReadByte(IMU3000_I2C, IMU3000_PWR_MGM, IMU3000_Read);
IMU3000_Read[0] |= (1<<7);
i2cWriteByte(IMU3000_I2C, IMU3000_PWR_MGM, IMU3000_Read[0]);
Delayms(5);
i2cReadByte(IMU3000_I2C, IMU3000_PWR_MGM, IMU3000_Read);
IMU3000_Read[0] |= 0b00000011;
i2cWriteByte(IMU3000_I2C, IMU3000_PWR_MGM, IMU3000_Read[0]);
Delayms(5);
// Set AUX VDDIO I2C Acc Logic ???????????????????????????????????????? 
i2cReadByte(IMU3000_I2C, IMU3000_AUX_VDDIO, IMU3000_Read);
IMU3000_Read[0] = 0x04;
i2cWriteByte(IMU3000_I2C, IMU3000_AUX_VDDIO, IMU3000_Read[0]);
Delayms(5);
// Set Acc Address @P32 
i2cReadByte(IMU3000_I2C, IMU3000_AUX_SLV_ADDR, IMU3000_Read);
IMU3000_Read[0] = 0b01000000;
i2cWriteByte(IMU3000_I2C, IMU3000_AUX_SLV_ADDR, IMU3000_Read[0]);
Delayms(5);
// Set Sample Rate Divider @P32     100=1K/Div+1  Div=9 0b00001001 
i2cReadByte(IMU3000_I2C, IMU3000_SMPLRT_DIV, IMU3000_Read);
IMU3000_Read[0] = 0x09;
i2cWriteByte(IMU3000_I2C, IMU3000_SMPLRT_DIV, IMU3000_Read[0]);
Delayms(5);
// Set range and LPF @P33 
i2cReadByte(IMU3000_I2C, IMU3000_DLPF_FS, IMU3000_Read);
IMU3000_Read[0] = 0x02;
i2cWriteByte(IMU3000_I2C, IMU3000_DLPF_FS, IMU3000_Read[0]);
Delayms(5);
// Set RAW_RDY_EN as Data Ready interrupt source @P35
i2cReadByte(IMU3000_I2C, IMU3000_INT_CFG, IMU3000_Read);
IMU3000_Read[0] |= 0b00110001;
i2cWriteByte(IMU3000_I2C, IMU3000_INT_CFG, IMU3000_Read[0]);
Delayms(5);
// Set Acc as Trough pass mode @P41
i2cReadByte(IMU3000_I2C, IMU3000_USER_CTRL, IMU3000_Read);
IMU3000_Read[0] |= 0b00001000;
i2cWriteByte(IMU3000_I2C, IMU3000_USER_CTRL, IMU3000_Read[0]);
Delayms(5);

};

// ------------------------IMU3000 READ RAW DATA-------------------------------
unsigned char IMU3000_Read_RAW(int *data){
unsigned char error= 0, buffer[14];
error = i2cReadArray(IMU3000_I2C, IMU3000_TEMP_OUT_H, buffer,14);
*data++ = ((buffer[0]<<8)|buffer[1]);
*data++ = ((buffer[2]<<8)|buffer[3]);
*data++ = ((buffer[4]<<8)|buffer[5]);
*data++ = ((buffer[6]<<8)|buffer[7]);
*data++ = ((buffer[9]<<8)|buffer[8])>>2 & 0xFFFF;
*data++ = ((buffer[11]<<8)|buffer[10])>>2 & 0xFFFF;
*data++ = ((buffer[13]<<8)|buffer[12])>>2 & 0xFFFF;
return error;
};

