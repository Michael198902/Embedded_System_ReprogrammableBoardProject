
#define lineU2()		putU2('\r');putU2('\n')

//---------------- Fun��es ---------------------
void initU2(void);	 	// inicializa a porta seria (8n1, UART2)
void putU2(int c);	 	// envia um caracter para a porta
void putsU2(char *s); 	// envia uma string terminada em null
char getU2(void);	 	// espera at� receber um caracter da porta

