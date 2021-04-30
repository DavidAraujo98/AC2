#include<detpic32.h>

int main(void){
	// Potenciometro -> RB4
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4 = 0;
	AD1CON1bits.SSRC = 7;
	
	AD1CON1bits.CLRASAM = 1;
	
	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI = 15;
	
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON = 1; 	
	
	while(1){
		AD1CON1bits.ASAM = 1;
		
		while(IFS1bits.AD1IF == 0);
		
		int *p = (int *)(&ADC1BUF0);
		int i;
		for( i = 0; i < 16; i++ ){
			printInt( p[i*4], 10 | 4 << 16 );
			putChar(' ');
		}
		
		IFS1bits.AD1IF = 0;
		putChar('\n');
	}
	
	return 0;
} 