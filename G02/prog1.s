#void main(void) {
#	int counter = 0;
#	while(1) {
#		while(readCoreTimer() < 200000);
#		resetCoreTimer();
#		printInt(++counter, 10 | 4 << 16); // Ver nota1
#		putChar('\r'); // cursor regressa ao início da linha
#	}
#	return 0;
#}
#	$t1:	counter

		.data
		.equ	printInt, 6
		.equ	putChar, 3
		.equ	readTimer, 11
		.equ	resetTimer, 12
		.text
		.globl main
		
main:		li	$a0, 0
while:		li $v0, readTimer
		syscall
	
		blt	$v0, 200000, while
		
		addiu	$a0, $a0, 1		# ++counter
	
		li	$a1, 0x000400A
		li	$v0, printInt
		syscall
	
		li	$v0, putChar
		li	$a0, '\r'
		syscall
		
		li	$v0, resetTimer
		syscall
		
		j while
	
		li $v0, 0
		jr $ra
