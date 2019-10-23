#include "HMC5883L.h"
//I2C library
#include "../I2C/I2C.h"
//Delay Library
#include "../DELAY/DELAY.h"
unsigned char Read_HMC5883L[1];
float HMC5883L_X_Scale=1, HMC5883L_Y_Scale=1, HMC5883L_Z_Scale=1;

void HMC5883L_Init(void){
//	**********Configuration Register A*********** 
i2cReadByte(HMC5883L_I2C, HMC5883L_CONFA, Read_HMC5883L);
// @P11 Select number of samples averaged (8) 0b11 per measurement output.
// Typical Data Output Rate (Hz) NOT USED 0b111
Read_HMC5883L[0] |= ((1<<4)|(1<<3));
Read_HMC5883L[0] &= (((0<<5)&(0<<6)) &(0<<2)); 	
// applying changes
i2cWriteByte(HMC5883L_I2C,HMC5883L_CONFA,Read_HMC5883L[0]);
Delayms(1);
i2cReadByte(HMC5883L_I2C,HMC5883L_CONFA,Read_HMC5883L);
// Normal measurement configuration, Clear CRA7 bits for coorect operation
Read_HMC5883L[0] &= (0<<7) & ((0<<1)&(0<<0));
// Applying changes
i2cWriteByte(HMC5883L_I2C,HMC5883L_CONFA,Read_HMC5883L[0]);
Delayms(1);
// **********Configuration Register B*********** 	
i2cReadByte(HMC5883L_I2C,HMC5883L_CONFB,Read_HMC5883L);
//@P12 Gain Configuration Bits ± 0.88 Ga  1370 LSB/Gauss 
Read_HMC5883L[0] &= ((0<<7)&(0<<6)&(0<<5));
//Applying changes
i2cWriteByte(HMC5883L_I2C,HMC5883L_CONFB,Read_HMC5883L[0]);
Delayms(1);
// ***************Mode Register***************** 
i2cReadByte(HMC5883L_I2C,HMC5883L_MODE,Read_HMC5883L);
//@P13 Single-Measurement Mode 0b01
//Single-Measurement Mode (Default).  When single-measurement mode is selected,
//device performs a single measurement, sets RDY high and returned to idle mode.  
//Mode register returns to idle mode bit values. The measurement remains in the 
//data output register and RDY remains high until the data output register is read 
//or another measurement is performed. 
Read_HMC5883L[0] &= (0<<1)&(0<<2)&(0<<3)&(0<<4)&(0<<5)&(0<<6)&(0<<7);
Read_HMC5883L[0] |= (1<<0);
//Applying changes
i2cWriteByte(HMC5883L_I2C,HMC5883L_MODE,Read_HMC5883L[0]);
Delayms(1);
// **********Check Status Register***************
i2cReadByte(HMC5883L_I2C,HMC5883L_STATUS,Read_HMC5883L);
//Check if DRDY is HIGH
	if (!(Read_HMC5883L[0] & (1<<0))){
		Read_HMC5883L[0]=7;
	};

// CALIBRATION 
//For Calibrating the sensor
int HMC5883L_Data[3], i=0;
float HMC5883L_X, HMC5883L_Y, HMC5883L_Z, HMC5883L_Max_X=0, HMC5883L_Max_Y=0, HMC5883L_Max_Z=0, HMC5883L_Max = 0;
// **********SELECT POSITIVE BIAS FOR CALIBRATION*********** 
i2cReadByte(HMC5883L_I2C,HMC5883L_CONFA,Read_HMC5883L);
//Add first bit in 1 force to Positive Bias for Calibration
i2cWriteByte(HMC5883L_I2C, HMC5883L_CONFA, Read_HMC5883L[0]+HMC5883L_POS_BIAS);
//Read Sample Data in this case 100 data
	for (i=0; i<HMC5883L_Sample ; i++){
		//Read data from HMC5883L
		HMC5883L_Read_RAW(HMC5883L_Data);
		//Casting and divide by pre scale values
		HMC5883L_X = (float) HMC5883L_Data[0]/(HMC5883L_X_Scale);
		HMC5883L_Y = (float) HMC5883L_Data[1]/(HMC5883L_Y_Scale);
		HMC5883L_Z = (float) HMC5883L_Data[2]/(HMC5883L_Z_Scale);
		//Find the maximum value for each axis
			if (HMC5883L_X>HMC5883L_Max_X) HMC5883L_Max_X = HMC5883L_X;
			if (HMC5883L_Y>HMC5883L_Max_Y) HMC5883L_Max_Y = HMC5883L_Y;
			if (HMC5883L_Z>HMC5883L_Max_Z) HMC5883L_Max_Z = HMC5883L_Z;
			//Variable for find the maximum of maximum value for each axis 
				if (HMC5883L_Max_X > HMC5883L_Max) HMC5883L_Max = HMC5883L_Max_X;
				if (HMC5883L_Max_Y > HMC5883L_Max) HMC5883L_Max = HMC5883L_Max_Y;
				if (HMC5883L_Max_Z > HMC5883L_Max) HMC5883L_Max = HMC5883L_Max_Z;
	};
		HMC5883L_X_Scale = HMC5883L_Max/HMC5883L_Max_X;
		HMC5883L_Y_Scale = HMC5883L_Max/HMC5883L_Max_Y;
		HMC5883L_Z_Scale = HMC5883L_Max/HMC5883L_Max_Z;
	// **********SELECT NORMAL OPERATION MODE*********** 
	i2cReadByte(HMC5883L_I2C,HMC5883L_CONFA,Read_HMC5883L);
	Read_HMC5883L[0] &= (0<<0);
	//Add first bit in 1 force to Positive Bias for Calibration
	i2cWriteByte(HMC5883L_I2C, HMC5883L_CONFA, Read_HMC5883L[0]);
};

// ***************************************READ RAW DATA********************************************
unsigned char HMC5883L_Read_RAW(int *data){
unsigned char error= 0, buffer[6];
error = i2cReadArray(HMC5883L_I2C,HMC5883L_XM, buffer,6);
*data++ = (buffer[0]<<8)|buffer[1];
*data++ = (buffer[4]<<8)|buffer[5];
*data++ = (buffer[2]<<8)|buffer[3];
return error;
};

// *************************************PUT IN SINGLE MODE ****************************************
void HMC5883L_Single_Mode(void){
unsigned char Read_HMC5883L;
Read_HMC5883L &= (0<<1);
Read_HMC5883L |= (1<<0);
//Applying changes
i2cWriteByte(HMC5883L_I2C,HMC5883L_MODE, Read_HMC5883L);
};



