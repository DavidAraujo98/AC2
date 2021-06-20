#include <detpic32.h>
#include "ConfigUart.c"

void delay(int ms){
	for(; ms > 0; ms--){
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}

void putc(char byte2send) {
	while(U2STAbits.UTXBF == 1);
	U2TXREG = byte2send;
}

char getc(void){
	if(U2STAbits.OERR == 1)
		U2STAbits.OERR = 0;
	
	while(U2STAbits.URXDA == 0);
	
	char c;
	
	if(U2STAbits.FERR || U2STAbits.PERR){
		c = U2RXREG;
		return 0;
	}
	
	return U2RXREG; 
}


int main(void){
	
	ConfigUart(115200, 'N', 1);
	while(1){
		putc(getc());
	}
}
