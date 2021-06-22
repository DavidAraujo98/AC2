#include<detpic32.h>

void delay(int ms) {
	for(; ms > 0; ms--) {
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}

void send2displays(unsigned char value){
	static int dis = 0;
	int display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	
	int dh = (value / 10) << 4;
	int dl = value % 10;
	
	if(dis == 0){
		LATDbits.LATD6 = 0;
		LATDbits.LATD5 = 1;	// display low active
		LATB = (0x80FF & LATB) | (display7Scodes[dl] << 8);
		dis = 1;
	}else{
		LATDbits.LATD6 = 1;	// display high active
		LATDbits.LATD5 = 0;
		LATB = (0x80FF & LATB) | (display7Scodes[dh] << 8);
		dis = 0;
	}
}

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
	
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;
	
	TRISB = TRISB & 0x80FF;
	
	int *p = (int *)(&ADC1BUF0);
	int y = 0;
	int VAL_AD = 0;
	int V = 0;
	while(1){
		if(y++ % 25 == 0){
			AD1CON1bits.ASAM = 1;
			
			while(IFS1bits.AD1IF == 0);
			
			VAL_AD = 0;
			int i;
			for( i = 0; i < 4; i++ ){
				VAL_AD += p[i*4];
			}
			VAL_AD = VAL_AD / 4;
			
			V=(VAL_AD*33+511)/1023;
			
			printInt(V,10);
			putChar('\n');

			IFS1bits.AD1IF = 0;
		}
		send2displays(V);
		delay(10);
	}
	
	return 0;
}
