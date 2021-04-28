#include<detpic32.h>

int main(void) {
	
	LATB = (LATB & 0x0000);
	TRISB = (TRISB & 0x00FF);	// RD8 a RD15 = 0
	
	LATDbits.LATD5 = 0;
	LATDbits.LATD6 = 1;
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;
	
	while(1) {
		char in = 'a';
		while(!(in >= 'A' && in <= 'G')){
			in = getChar();
			if (in >= 97)
				in -= 32;	// Converts to Uppercase with ASCII
		}
		
		LATB = (LATB & 0x0000);	// Cleans display
		
		int r[7] = {0,0,0,0,0,0,0};
		
		int i;
		for(i = 0; i < 7; i++){
			if((65+i) == in){
				r[i] = 1;
				break;
			}
		}
		
		LATBbits.LATB8 = r[0];
		LATBbits.LATB9 = r[1];
		LATBbits.LATB10 = r[2];
		LATBbits.LATB11 = r[3];
		LATBbits.LATB12 = r[4];
		LATBbits.LATB13 = r[5];
		LATBbits.LATB14 = r[6];
	}
	return 0;
}
