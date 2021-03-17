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
	
delay:	addiu	$sp, $sp, -4
		sw	$ra, 0($sp)
		
		move	$t0, $a0
		
for:	ble	$t0, 0, end
		
		li	$v0, resetTimer			# resetCoreTimer();
		syscall
		
sleep:	li	$v0, readTimer			# while(readCoreTimer() < K);
		blt	$v0, 20000, sleep

		j for
		
end:	lw	$ra, 0($sp)
		addiu	$sp, $sp, -4
		jr	$ra