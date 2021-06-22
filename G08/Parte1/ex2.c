#include <detpic32.h>

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


int main(void){

	U2MODEbits.BRGH = 0;
	U2BRG = 10;
	
	U2MODEbits.PDSEL = 0;
	U2MODEbits.STSEL = 1;
	
	U2STAbits.UTXEN = 1;
	U2STAbits.URXEN = 1;
	
	U2MODEbits.ON = 1;
	
	// Configure UART2 (115200, N, 8, 1)
	while(1){
		putc('+');
		delay(1000);
	}
}

