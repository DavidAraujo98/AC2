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

void puts(char *str) {
	// use putc() function to send each charater ('\0' should not
	// be sent)
	int i = 0;
    while(str[i] != '\0'){
        putc(str[i]);
        i++;
    }
}


int main(void){
	
	U2MODEbits.BRGH = UxBRG = ((PBCLK + 8 * baud) / (16 * baud)) – 1;
	U2MODEbits.BRGH = 0;
	U2MODEbits.PDSEL = 0;
	U2MODEbits.STSEL = 0;
	
	U2MODEbits.UTXEN = 1;
	U2MODEbits.URXEN = 1;
	
	U2MODEbits.ON = 1;
	
	TRISBbits.TRISB6 = 0;
	
	// Configure UART2 (115200, N, 8, 1)
	while(1){
		while(U2STAbits.TRMT == 1);
		PORTBbits.RB6 = 1;
		puts("12345");
		PORTBbits.RB6 = 0;
		delay(1000);
	}
}
