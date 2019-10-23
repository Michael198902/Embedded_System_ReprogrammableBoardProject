// Simple Module for reading BMA180 data by Mazeyar Cheguini

#if !defined (__BMA180_H)
#define __BMA180_H

#include "../I2C/I2C.h"
#include "../DELAY/DELAY.h"
//---------------- BMA180 Register Address ------------------
#define	BMA180_I2C				0x40
#define BMA180_offset_lsb1		0x35
#define BMA180_tco_z			0x30
#define BMA180_gain_x			0x32
#define BMA180_high_dur			0x27
#define BMA180_ctrl_reg3		0x21
#define BMA180_bw_tcs			0x20
#define BMA180_ctrl_reg0		0x0D
#define BMA180_acc_x_lsb		0x02
#define ee_w					4
#define	dis_reg					0
#define	dis_i2c					0
#define	adv_int					2
#define	new_data				1
#define	lat_int					0
//Function Prototype
void BMA180_Init(void);
unsigned char BMA180_Read_RAW(int *data);

#endif


