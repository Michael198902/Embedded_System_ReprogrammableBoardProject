#include<p33Fxxxx.h>

void Delayms( unsigned count){
T1CONbits.TON = 1;
	while (count--){
		TMR1 = 0;
			while (TMR1<8000);
    };
};

void Delayus( unsigned count){
    T1CONbits.TON = 1;
		while (count--){
			TMR1 = 0;
			while (TMR1<80);
		};
};
