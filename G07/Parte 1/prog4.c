#include <detpic32.h>

int main(void){

	// 2Hz
	T1CONbits.TCKPS = 3;
	PR1 = 39062;
	TMR1 = 0;
	IPC1bits.T1IP = 2;
	IEC0bits.T1IE = 1;
	IFS0bits.T1IF = 0;
	
	// 10Hz
	T3CONbits.TCKPS = 5;
	PR3 = 62499;
	TMR3 = 0;
	IPC3bits.T3IP = 2;
	IEC0bits.T3IE = 1;
	IFS0bits.T3IF = 0;
	
	EnableInterrupts();
	
	T1CONbits.TON = 1;
	T3CONbits.TON = 1;
	
	while(1);
	
	return 0;
}

void _int_(4) isr_T1(void){
	putChar('1');
	IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void){
	putChar('3');
	IFS0bits.T3IF = 0;
}
