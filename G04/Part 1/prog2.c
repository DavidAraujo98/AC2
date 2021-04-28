#include<detpic32.h>

void delay(int ms) {
	for(; ms > 0; ms--) {
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}

void decToBin(int *a, int dec, int size){
	int i;
	for(i = size-1; i >= 1; i--){
		*(a+i) = dec % 2;
		dec = dec / 2;
	}
	*(a) = dec;
}

int main(void) {
	int a[4];
	int size = 4;
	int count = 0;
	
	LATE = (LATE & 0xFFF0);
	TRISE = (TRISE & 0xFFF0);
	
	while(1) {
		delay(250);
		
		if(count == 15)
			count = 0;
		
		decToBin(a, count, size);
		
		LATEbits.LATE0 = a[0];
		LATEbits.LATE1 = a[1];
		LATEbits.LATE2 = a[2];
		LATEbits.LATE3 = a[3];
		
		count++;
	}
	return 0;
}
