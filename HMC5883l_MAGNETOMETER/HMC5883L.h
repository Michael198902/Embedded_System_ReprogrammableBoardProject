#if !defined(HMC5883L_H)
#define HMC5883L_H

#define	HMC5883L_I2C	0x1E

//HMC5843L register map
#define HMC5883L_CONFA 	0x00
#define HMC5883L_CONFB 	0x01	
#define HMC5883L_MODE 	0x02
#define HMC5883L_XM 	0x03

#define HMC5883L_STATUS	0x09
//For calibrating HMC5883L
#define	HMC5883L_POS_BIAS	1

//For Calibration HMC5883L
#define	HMC5883L_Sample	100

//Function Prototype 
	void HMC5883L_Init(void);
	unsigned char HMC5883L_Read_RAW(int *data);
	void HMC5883L_Single_Mode(void);
	//void HMC5883L_Calibration(float *HMC5883L_X_Scale, float *HMC5883L_Y_Scale, float *HMC5883L_Z_Scale);
#endif



