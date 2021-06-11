#include <detpic32.h>

void setPWM(unsigned int dutyCycle){
    if(dutyCycle < 100 && dutyCycle > 0){
        OC1RS = (780 * dutyCycle)/100;
    }
}

void delay(int ms){
	for(; ms > 0; ms--){
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}

int main(void){

	TRISB = TRISB | 0x3;

	T2CONbits.TCKPS = 5;
	PR2 = 62499;
	TMR2 = 0;
	T2CONbits.TON = 1;
	OC1CONbits.OCM = 6;
	OC1CONbits.OCTSEL =0;
	OC1RS = 12500;
	OC1CONbits.ON = 1;
	
    int i = 0;

    while(1){

        setPWM(i);

        delay(500);

        if(i == 100){
            i = -10;
        }

        i+=10;
    }
    
    return 0;
}
