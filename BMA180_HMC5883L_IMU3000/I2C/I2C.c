#include "../Compiler.h"
#include "I2C.h"
#include "../HardwareProfile.h"

#define i2cWRITE 0
#define i2cREAD  1

void i2cStart(void){
I2C1CONbits.SEN = 1;
	while(I2C1CONbits.SEN);
};

void i2cRestart(void){
I2C1CONbits.RSEN = 1;
	while(I2C1CONbits.RSEN);
};

void i2cStop(void){
I2C1CONbits.PEN = 1;
	while(I2C1CONbits.PEN);
};

void i2cNack(void){
I2C1CONbits.ACKDT=1;
I2C1CONbits.ACKEN=1;
	while(I2C1CONbits.ACKEN);
I2C1CONbits.ACKDT=0;
};

void i2cAck(void){
I2C1CONbits.ACKDT=0;
I2C1CONbits.ACKEN=1;
	while(I2C1CONbits.ACKEN);   
};

unsigned char i2cGetAck(void){
return (!I2C1STATbits.ACKSTAT);
};

void i2cWrite(unsigned char byte){
I2C1TRN=byte;
	while(I2C1STATbits.TBF);
};

unsigned char i2cWriteAck(unsigned char byte){
I2C1TRN=byte;
	while(I2C1STATbits.TRSTAT==1);
return (!I2C1STATbits.ACKSTAT);
};


unsigned char i2cRead(void){
I2C1CONbits.RCEN=1;
	while(!I2C1STATbits.RBF);
return(I2C1RCV);
};

void initI2C(void){
I2C1CONbits.A10M=0;
I2C1CONbits.SCLREL=0;
I2C1ADD=0;
I2C1MSK=0;
I2C1CONbits.SMEN = 0; 
I2C1BRG = I2Cspeed;
I2C1CONbits.I2CEN = 1;	
};

unsigned char i2cWriteByte(unsigned char i2cADD,unsigned char ADD,unsigned char data){
unsigned char error = 0;
i2cStart();
error += !i2cWriteAck((i2cADD<<1)|i2cWRITE);
error += !i2cWriteAck(ADD);
error += !i2cWriteAck(data);
i2cStop();
return error;
};

unsigned char i2cReadByte(unsigned char i2cADD,unsigned char ADD,unsigned char *data){
unsigned char error = 0;
i2cStart();
error += !i2cWriteAck((i2cADD<<1)|i2cWRITE);
error += !i2cWriteAck(ADD);
i2cStart();
error += !i2cWriteAck((i2cADD<<1)|i2cREAD);
	if(error){
		i2cStop();
		return error;
	};
*data = i2cRead();
i2cNack();
i2cStop();
return error;
};

unsigned char i2cReadArray(unsigned char i2cADD,unsigned char ADD,unsigned char *data,unsigned char length){
unsigned char error = 0;
i2cStart();
error += !i2cWriteAck((i2cADD<<1)|i2cWRITE);
error += !i2cWriteAck(ADD);
i2cStart();
error += !i2cWriteAck((i2cADD<<1)|i2cREAD);
	if(error){
		i2cStop();
		return error;
	};
		while(length-->1){
			*data++ = i2cRead(); 
			i2cAck();
		};
*data = i2cRead(); 
i2cNack();
i2cStop();
return error;
};
