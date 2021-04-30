#include<detpic32.h>

int main(void){
	int display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

	LATDbits.LATD6 = 0; // display high active
	LATDbits.LATD5 = 1; // display low inactive
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;
	
	TRISB = TRISB & 0x80FF; 
	// configure RB0 to RB3 as inputs
	// configure RB8 to RB14 and RD5 to RD6 as outputs
	// Select display low
	while(1){
		LATB = (0x80FF & LATB) | (display7Scodes[PORTB & 0xF] << 8); 
		// read dip-switch
		// convert to 7 segments code
		// send to display
	}
	return 0;
}
