#include <detpic32.h>

volatile int voltage = 0;
volatile int voltMin = 0;
volatile int voltMax = 0;

void send2displays(unsigned char value){
    static const char display7Scodes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
    static char display_flag = 0;

    unsigned char digit_low = value % 10;
    unsigned char digit_high = (int) (value/10);

    if(display_flag){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | display7Scodes[digit_low] << 8;
    }else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | display7Scodes[digit_high] << 8;
    }
    display_flag = !display_flag;
}

void setPWM(unsigned int dutyCycle){
    if(dutyCycle <= 100 && dutyCycle >= 0){
        OC1RS = (780 * dutyCycle)/100;       // OC1RS = PRx * dutyCicle / 100 
    }
}

void configureAll(){

    T1CONbits.TCKPS = 3;
    PR1 = 19530;
    TMR1 = 0;
    T1CONbits.TON = 1;          

    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;

	T2CONbits.TCKPS = 7;
    PR1 = 780;
    TMR1 = 0;
    T1CONbits.TON = 1;          

    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;

    T3CONbits.TCKPS = 7;
    PR3 = 780;
    TMR3 = 0;
    T3CONbits.TON = 1;

    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;

    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;           

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 7;

    AD1CHSbits.CH0SA = 4;

    AD1CON1bits.ON = 1;

    IPC6bits.AD1IP = 2;

    IEC1bits.AD1IE = 1;

    TRISB = TRISB & 0x00FF;                  
    TRISD = TRISD & 0xFF9F;

    TRISB = TRISB | 0x3;


    T2CONbits.TCKPS = 7;
    PR2 = 780;
    TMR2 = 0;
    T2CONbits.TON = 1;

    OC1CONbits.OCM = 6;
    OC1CONbits.OCTSEL = 0
    OC1RS = 12500;
    OC1CONbits.ON = 1;
}

// isr for timer 1 - 4 Hz, conversion frequecy
void _int_(4) isr_T1(void){
    AD1CON1bits.ASAM = 1;
    IFS0bits.T1IF = 0;
}

// isr for timer 3 - 100 Hz, display refresh time
void _int_(12) isr_T3(void){
	static int counter = 0;
	counter++;
	
	if(counter == 100){
		char dec = 0 | (voltage / 10);
		putc(dec);
		dec = 0 | (voltage % 10);
		putc(dec);
		counter = 0;
	}
	
    send2displays(voltage);
    IFS0bits.T3IF = 0;
}

void _int_(32) isr_uart2(void){
	if(IFS0bits.U1EIF == 1){
		if(U2STAbits.OERR == 1){
			U2STAbits.OERR = 0;
		}else{
			char c = U2RXREG;
		}
	}
	
	if(IFS0bits.U2RXIF == 1 && U2RXREG == 'L'){
		int x = 0 | (voltMin / 10);
		putc(x);
		x = 0 | (voltMin % 10);
		putc(x);
		
		putc('\n');
		
		x = 0 | (voltMax / 10);
		putc(x);
		x = 0 | (voltMax % 10);
		putc(x);
		
    }
	IFS0bits.U2RXIF = 0;
}

void _int_(27) isr_adc(void){

    int* p = (int*) (&ADC1BUF0);

    int sum = 0;
    int i = 0;
	voltMin = p[0];
	voltMax = p[0];
    for(; i < 8; i++){
        sum = sum + p[i*4];
		
		int temp = (p[i*4]*33 + 511) / 1023;
		
		if(temp > voltMax)
			voltMax = temp
		
		if(temp < voltMin)
			voltMin = temp;
    }

    int med_voltage = sum/8;

    voltage = (med_voltage*33 + 511) / 1023;
    
    IFS1bits.AD1IF = 0;
}

void putc(char byte2send) {
	while(U2STAbits.UTXBF == 1);
	U2TXREG = byte2send;
}

int main(void){          
    configureAll();        
    
    IFS1bits.AD1IF = 0;
    IFS0bits.T3IF = 0;
    IFS0bits.T1IF = 0;

    EnableInterrupts();

    int dutyCycle;
    int portVal;

    while(1){
        portVal = PORTB & 0x3;

        switch(portVal){
        case 0:
            IEC0bits.T1IE = 1;
            setPWM(0);
            break;

        case 1:
            IEC0bits.T1IE = 0;
            setPWM(100);
            break;
        
        default:
            IEC0bits.T1IE = 1;
            dutyCycle = voltage * 3;
            setPWM(dutyCycle);
            break;
        }
    }

    return 0;       
}