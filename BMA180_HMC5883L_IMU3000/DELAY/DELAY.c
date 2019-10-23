#include <p33FJ128GP802.h>

void Delayms( unsigned count){
T1CONbits.TON = 1;
	while (count--){
		TMR1 = 0;
			while (TMR1<10000);
    };
};

void Delayus( unsigned count){
    T1CONbits.TON = 1;
		while (count--){
			TMR1 = 0;
			while (TMR1<10);
		};
};
