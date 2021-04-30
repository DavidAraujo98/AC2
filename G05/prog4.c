#include<detpic32.h>

int main(void){
	// Potenciometro -> RB4
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4 = 0;
	AD1CON1bits.SSRC = 7;
	
	AD1CON1bits.CLRASAM = 1;
	
	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI = 3;
	
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON = 1; 	
	
	int *p = (int *)(&ADC1BUF0);
	int i;
	int VAL_AD = 0;
	
	while(1){
		AD1CON1bits.ASAM = 1;
		
		while(IFS1bits.AD1IF == 0);
		
		VAL_AD = 0;
		for( i = 0; i < 4; i++ ){
			VAL_AD += p[i*4];
		}
		VAL_AD = VAL_AD / 4;
		
		int V=(VAL_AD*33+511)/1023;
		
		printInt(V,10);

		IFS1bits.AD1IF = 0;
		
		putChar('\n');
	}
	
	return 0;
} 