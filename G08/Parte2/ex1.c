#include <detpic32.h>
#include "ConfigUart.c"

void putc(char byte2send) {
	while(U2STAbits.UTXBF == 1);
	U2TXREG = byte2send;
}

void _int_(32) isr_uart2(void){
	if(IFS0bits.U2RXIF == 1){
        putc(U1RXREG);
        IFS0bits.U2RXIF = 0;     // clear Uart1 Interrupt flag
    }
}

int main(void){
	configUart(115200, 'N', 1);
	EnableInterrupts();
	while(1);
}
