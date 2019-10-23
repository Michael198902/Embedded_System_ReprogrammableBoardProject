//-------------- Serial CONFIGURATION --------------------
#define	BRATE		115200
#define U2RxPin _U2RXR = 2				
#define U2TxPin	_RP3R = 5				
//------------- Clock frequency values -------------------
//used for UART and SPI baud rate generation.
#define GetSystemClock()		(20000000ul)			// Hz
#define GetInstructionClock()	(GetSystemClock()/2)	// GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.
#define GetPeripheralClock()	(GetSystemClock()/2)	// GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32. 


