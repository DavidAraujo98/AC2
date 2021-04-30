#include<detpic32.h>

void delay(int ms) {
	for(; ms > 0; ms--) {
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}

unsigned char toBcd(unsigned char value)
{
	return ((value / 10) << 4) + (value % 10);
}

void send2displays(unsigned char value){
	static int dis = 0;
	int display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	
	value = toBcd(value);
	
	int dh = value >> 4;
	int dl = value & 0x0F;

	printf("%d", dis);
	
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

	int i = 0, x = 0, fla = 0;
	while(1){
		if(x%20 == 0){
			if(i == 99){ // 0x
				i = 0;
				fla = 1;
			}else{
				i++;
			}
		}
		if(fla == 1){
			int r, y;
			for(r = 0; r < 10; r++){
				for(y = 0; y < 10; y++){
					send2displays((unsigned char)i);
					delay(10);
					send2displays((unsigned char)i);
					delay(10);
				}
				LATB = (0x80FF & LATB);
				delay(100);
			}
			fla = 0;
		}else{
			send2displays((unsigned char)i);
		}
		
		
		x++;
		delay(10);
	}
	return 0;
}
