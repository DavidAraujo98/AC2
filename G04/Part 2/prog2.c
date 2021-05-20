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
	
	int dh = value >> 4;
	int dl = value & 0x0F;
	
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
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;
	
	TRISB = TRISB & 0x80FF;

	int i = 0, x = 0;
	while(1){
		if(x%200 == 0){	// Counting at 5Hz
			if(i == 256){
				i = 0;
			}
			i++;
		}
		send2displays((unsigned char)i);
		
		x++;
		delay(50);	// Refreshing at 20Hz
		
		// PS: It looks really good  with 100Hz (10ms) refresh rate and 50Hz (20) counting
	}
	return 0;
}
