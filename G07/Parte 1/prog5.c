#include <detpic32.h>

unsigned int voltage = 0;

void send2displays(unsigned char value){
	static int dis = 0;
	int display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	
	value = ((value / 10) << 4) + (value % 10);
	
	int dh = value >> 4;
	int dl = value & 0x0F;
	
	if(dis == 0){
		LATDbits.LATD6 = 0;
		LATDbits.LATD5 = 1;	// display low active
		LATB = (0x80FF & LATB) | (display7Scodes[dl] << 8);
	}else{
		LATDbits.LATD6 = 1;	// display high active
		LATDbits.LATD5 = 0;
		LATB = (0x80FF & LATB) | (display7Scodes[dh] << 8);
	}
	
	dis = !dis;
}

// Interrupction Handler
void _int_(27) isr_adc(void){

    // calculate buffer average
    int* p = (int*) (&ADC1BUF0);

    int sum = 0;
    int i;
    for(i = 0; i < 8; i++){
        sum += p[i*4];
    }

    int med_voltage = sum / 8;

    voltage = (med_voltage*33 + 511) / 1023;
    
    IFS1bits.AD1IF = 0;             // clear/reset A/D interrupt flag   

}

void _int_(4) isr_T1(void){
    AD1CON1bits.ASAM = 1;
	IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void){
	send2displays(voltage);
	IFS0bits.T3IF = 0;
}


int main(void){
	// Configure display
    TRISB = TRISB & 0x00FF;					// configure RB8-RB14 as outputs         
    TRISD = TRISD & 0xFF9F;					// configure RD5-RD6 as outputs

    // Configure the A/D module and port RB4 as analog input // potenciometro
    TRISBbits.TRISB4 = 1;					// RB4 digital output disconnected
    AD1PCFGbits.PCFG4 = 0;					// RB4 configured as analog input (AN4)
    AD1CON1bits.SSRC = 7;           
    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 7;					// 8 amostras consecutivas

    AD1CHSbits.CH0SA = 4;

    AD1CON1bits.ON = 1;						// Enable A/D converter

    // Configure interrupt system
    IPC6bits.AD1IP = 2;						// configure priority of A/D interrupts to 2

    IEC1bits.AD1IE = 1;
    
    // 2Hz - Timer 1
	T1CONbits.TCKPS = 3 ;
	PR1 = 19530;
	TMR1 = 0;
	IPC1bits.T1IP = 2;
	IEC0bits.T1IE = 1;
	IFS0bits.T1IF = 0;
	
	// 100Hz
	T3CONbits.TCKPS = 7;
	PR3 = 781;
	TMR3 = 0;
	IPC3bits.T3IP = 2;
	IEC0bits.T3IE = 1;
	IFS0bits.T3IF = 0;
	
	EnableInterrupts();
	
	T1CONbits.TON = 1;
    T3CONbits.TON = 1;
    
    IFS0bits.T1IF = 0;
    IFS0bits.T3IF = 0;
    IFS1bits.AD1IF = 0;

    while(1);
    
    return 0;
}

