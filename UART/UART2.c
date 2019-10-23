
#include "../Compiler.h"
#include "UART2.h"
#include "../HardwareProfile.h"

//-------------- Configuração dos perifericos -------------------
#if defined(U2_INV)
	#define	U_MODE		0x8018	// Enable UART, BREGH=1, 8n1
	#define	U_STA		0x4400	// Ativa transmissão. limpa flags
#else
	#define	U_MODE		0x8008	// Enable UART, BREGH=1, 8n1
	#define	U_STA		0x0400	// Ativa transmissão. limpa flags
#endif


//------------------------ BAUDRATE -----------------------------
#define BAUDRATEREG    (((GetPeripheralClock())-(4*BRATE))/(4*BRATE))
#define BAUD_ACTUAL		((GetPeripheralClock())	/(4*(BAUDRATEREG+1)))

#define BAUD_ERROR              ((BAUD_ACTUAL > BRATE) ? BAUD_ACTUAL-BRATE : BRATE-BAUD_ACTUAL)
#define BAUD_ERROR_PERCENT      ((BAUD_ERROR*100+BRATE/2)/BRATE)

#if (BAUD_ERROR_PERCENT > 3)
    #error UART frequency error is worse than 3%
#elif (BAUD_ERROR_PERCENT > 2)
    #warning UART frequency error is worse than 2%
#endif


//-----------------Public Functions ------------------------------
	
void initU2(void)
{
	char lixo;
	
	_U2RXIE = 0;
	U2BRG = 7;
	U2MODE = U_MODE;	
	U2STA = U_STA;

        RPOR1bits.RP3R = 5;
        RPINR19bits.U2RXR=2;

	U2RxPin;
	U2TxPin;

	while(U2STAbits.URXDA)
		lixo=U2RXREG; 

#ifdef USE_SERIAL_INT
	_U2RXIE = 1;
#endif

} //initU2

void putU2(int c)
{
	while(U2STAbits.UTXBF);	
	U2TXREG = c;	
} //putU2

char getU2(void)
{
	while(!U2STAbits.URXDA); 
	return U2RXREG;		
} //putU2

void putsU2(char *s)
{
	while(*s)	
		putU2(*s++);
	lineU2();
}
