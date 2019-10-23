#include "BMA180.h"
unsigned char BMA180_Read[1];
void BMA180_Init(void){
//	------------------- Enable write to EEPROM -------------------------------
i2cReadByte(BMA180_I2C, BMA180_ctrl_reg0, BMA180_Read);
BMA180_Read[0] |= (1<<ee_w);
i2cWriteByte(BMA180_I2C, BMA180_ctrl_reg0, BMA180_Read[0]);
// EEPROM needs 10ms for writing @P11
Delayms(10);
// Set corresponding BandWith 0b0100 @P27
i2cReadByte(BMA180_I2C, BMA180_bw_tcs, BMA180_Read);
BMA180_Read[0] |= (1<<5) | (1<<6) | (1<<4) | (1<<3);
BMA180_Read[0] &= (0<<7);
i2cWriteByte(BMA180_I2C, BMA180_bw_tcs, BMA180_Read[0]);
Delayms(10);
// Set the range of operation to 2g @P27
i2cReadByte(BMA180_I2C, BMA180_offset_lsb1, BMA180_Read);
BMA180_Read[0] |= (1<<2);
BMA180_Read[0] &= (0<<1) & (0<<3);
i2cWriteByte(BMA180_I2C, BMA180_offset_lsb1, BMA180_Read[0]);
Delayms(10);
// Set the mode of operation:  Ultra low noise highest current  lowest noise@P28
i2cReadByte(BMA180_I2C, BMA180_tco_z, BMA180_Read);
BMA180_Read[0] |= (1<<0);
BMA180_Read[0] &= (0<<1);
i2cWriteByte(BMA180_I2C, BMA180_tco_z, BMA180_Read[0]);
//Delayms(10);
// Set internal regulator ?????????????????? PROBLEM
//i2cReadByte(BMA180_I2C, BMA180_gain_x, BMA180_Read);
//BMA180_Read[0] = 0b10101000;
//i2cWriteByte(BMA180_I2C, 0x52, BMA180_Read[0]);
//i2cWriteByte(BMA180_I2C, 0x32, BMA180_Read[0]);
Delayms(10);
// Set I2C
i2cReadByte(BMA180_I2C, BMA180_high_dur, BMA180_Read);
BMA180_Read[0] &= (0<<dis_i2c);
i2cWriteByte(BMA180_I2C, BMA180_high_dur, BMA180_Read[0]);
Delayms(10);
//Disable Advance Interrupts and enable New Data Interrupt
i2cReadByte(BMA180_I2C, BMA180_ctrl_reg3, BMA180_Read);
// ??????????????????????????????????????????????
// BMA180_Read[0] &= (0<<adv_int) & (0<<lat_int);
BMA180_Read[0] |= (1<<new_data);
i2cWriteByte(BMA180_I2C, BMA180_ctrl_reg3, BMA180_Read[0]);
Delayms(10);
};

// ------------------------BMA180 READ RAW DATA-------------------------------
unsigned char BMA180_Read_RAW(int *data){
unsigned char error= 0, buffer[6];
error = i2cReadArray(BMA180_I2C, BMA180_acc_x_lsb, buffer,6);

*data++ = ((buffer[1]<<8)|buffer[0])>>2 & 0xFFFF;
*data++ = ((buffer[3]<<8)|buffer[2])>>2 & 0xFFFF;
*data++ = ((buffer[5]<<8)|buffer[4])>>2 & 0xFFFF;
//*data++ = buffer[6];
return error;
};

