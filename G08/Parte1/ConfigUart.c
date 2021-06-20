#include <detpic32.h>

int ConfigUart(unsigned int baud, char parity, unsigned int stopbits){

	if(baud < 600 || baud > 115200)
		baud = 115200;
	
	U2MODEbits.BRGH = ((PBCLK + 8 * baud) / (16 * baud)) - 1;

	if(parity == 'E'){
		U2MODEbits.PDSEL = 1;
	}else if(parity == 'O'){
		U2MODEbits.PDSEL = 0x10;
	}else{
		U2MODEbits.PDSEL = 0;
	}
	
	U2MODEbits.STSEL = stopbits - 1;
	
	U2STAbits.UTXEN = 1;
	U2STAbits.URXEN = 1;
	
	U2MODEbits.ON = 1;
	
	return 0;
}
