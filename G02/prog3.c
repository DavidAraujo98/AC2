#include<detpic32.h>

void delay(int ms);

int main(void){
	int cnt1 = 0;
	int cnt5 = 0;
	int cnt10 = 0;
	
	while(1){
		delay(100);
		
		// 5 Hz
		if(cnt10%2 == 0){ cnt5++; }
		
		// 1 HZ
		if(cnt10%10 == 0){ cnt1++; }
		
		// 10 Hz
		printInt(cnt1, 10 | 5 << 16);
		putChar('\t');
		printInt(cnt5, 10 | 5 << 16);
		putChar('\t');
		printInt(cnt10, 10 | 5 << 16);
		
		cnt10++;
		putChar('\r');
	}
	return 0;	
}


void delay(int ms) {
	for(; ms > 0; ms--) {
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}