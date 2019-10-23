#if !defined(__I2C_H)
#define __I2C_H
#define I2Cspeed 19
#define ACK 	0
#define NACK    1

// --------------- Function Prototypes ---------------------
void 			i2cStart(void);						// Send Start bit
void 			i2cRestart(void);					// Send Restart bit
void 			i2cStop(void);						// Send Stop bit
void 			i2cAck(void);						// Send Acknolegment
void 			i2cNack(void);						// Send Not Acknolegment
unsigned char 	i2cGetAck(void);					// Receive Acknolegment
void 			i2cWrite(unsigned char c);			// Write a byte
unsigned char 	i2cWriteAck(unsigned char c);		// Write a byte, and receive Acknolegment
unsigned char 	i2cRead(void);						// Read a byte
void 			initI2C(void);						// Initialize I2C module
unsigned char i2cWriteByte(unsigned char i2cADD,unsigned char ADD,unsigned char data);
unsigned char i2cReadByte(unsigned char i2cADD,unsigned char ADD,unsigned char *data);
unsigned char i2cReadArray(unsigned char i2cADD,unsigned char ADD,unsigned char *data,unsigned char length);
#endif

