#include<detpic32.h>

void delay(int ms) {
	for(; ms > 0; ms--) {
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}

void decToBin(int *a, int dec, size){
	for(int i = size -1; i >= 1; i--){
		*(a+i) = dec % 2;
		dec = dec / 2;
	}
	*(a) = dec;
}

int main(void) {
	char a[4];
	int size = 4;
	int count = 0;
	
	LATE = (LATE & 0xFFF0);
	TRISE = (TRISE & 0xFFF0);
	
	while(1) {
		delay(125);
		
		if(count == 15)
			count = 0;
		
		decToBin(a, count, size);
		
		LATCbits.LATE0 = a[0];
		LATCbits.LATE1 = a[1];
		LATCbits.LATE2 = a[2];
		LATCbits.LATE3 = a[3];
		
		count++;
	}
	return 0;
}