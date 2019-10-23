#include<p33Fxxxx.h>

#include <timer.h>
#include <uart.h>
#include "DELAY/DELAY.h"
#include "UART/UART2.h"
#include "Compiler.h"
#include "HardwareProfile.h"
#include "mpu6050.h"
#include <i2c.h>

void initSystem(void);
void Clock32MHz(void);
void initI2C(void);
void MPU6050_Init(void);
unsigned char MPU6050_Read_RAW(int *data);
unsigned char i2cReadByte(unsigned char i2cADD,unsigned char ADD,unsigned char *data);

// --------------- System ------------------

void initSystem(void){
extern int __C30_UART; __C30_UART = 2; 
Clock32MHz();
AD1PCFGL = 0xffff;
TRISBbits.TRISB2=1;
TRISBbits.TRISB3=0;
initU2();
Delayms(50);
};

void Clock32MHz(void){
CLKDIVbits.DOZE =0;
CLKDIVbits.FRCDIV =0;
CLKDIVbits.PLLPRE =0;
OSCCONbits.COSC=0b010;
OSCCONbits.LPOSCEN=0;
};

unsigned char *DATOS;
unsigned char monda;

int main(void){
initSystem();
initI2C();
MPU6050_Init();
Delayms(5);
StartI2C1();
IdleI2C1();
MasterWriteI2C1(0x68<<1|0);
IdleI2C1();
MasterWriteI2C1(0x41);
IdleI2C1();
StartI2C1();
MasterWriteI2C1(0x68<<1|1);
IdleI2C1();
DATOS=MasterReadI2C1();
NotAckI2C1();
StopI2C1();

            while(1){
                 printf("Medida:");
                 printf("%d \t",*DATOS);
                 //printf(*DATOS);
                 Delayms(1000);
                };
};


