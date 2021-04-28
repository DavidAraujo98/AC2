#include<detpic32.h>

void delay(int ms) {
	for(; ms > 0; ms--) {
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}

int main(void){
	
	// from 0 to F
	int display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

	LATDbits.LATD6 = 1; // display high active
	LATDbits.LATD5 = 0; // display low inactive
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;
	
	LATB = (LATB & 0x0000);
	TRISB = (TRISB & 0x00FF);
	
	int i = 0;
	while(1){
		if(i == 16){
			i = 0;
		}
		LATB = display7Scodes[i] << 8;
		i++;
		delay(500);
	}
	return 0;
}

