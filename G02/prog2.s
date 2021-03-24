		.data
		
		.equ	readTimer, 11
		.equ	resetTimer, 12
		.equ	readInt10, 5
		.equ	printStr, 8
		
str:	.asciiz "Valor do delay (ms): "
		.text
		.globl main
		
main:	la	$a0, str
		li 	$v0, printStr		# printStr("Valor do delay (ms): ")
		syscall
		
		li 	$v0, readInt10
		syscall					# readInt10()
		move	$a0, $v0
		
		jal delay				# delay()
		
		jr	$ra
		
		
#void delay(int ms) {
#	for(; ms > 0; ms--) {
#		resetCoreTimer();
#		while(readCoreTimer() < K);
#	}
#}		
	
delay:	
for:	blez	$a0, end
		
		li	$v0, resetTimer			# resetCoreTimer();
		syscall
		
sleep:	li	$v0, readTimer			# while(readCoreTimer() < K);
		syscall
		blt	$v0, 20000, sleep

		addi	$a0, $a0, -1 
		j for
		
end:	jr	$ra