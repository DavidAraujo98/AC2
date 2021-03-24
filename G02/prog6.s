# cnt1:		$t0
# cnt5:		$t1
# cnt10:	$t2
# temp:		$t3
# key:		$t4
# delay:	$t5

		.data
		.equ	readTimer, 11
		.equ	resetTimer, 12
		.equ	putChar, 3
		.equ	printInt, 6
		.equ	inkey, 1
		
str:	.asciiz "Valor do delay (ms): "
		.text
		.globl main

main:	li	$t0, 0
		li	$t1, 0
		li	$t2, 0
		li	$t5, 100
			
while:	move	$a0, $t5
		jal	delay
		
stop:	li	$v0, inkey
		syscall
		beqz	$v0, skp
		move	$t4, $v0
		
skp:	beq	$t4, 'R', resume
		beq	$t4, 'S', stop
		
resume:	bne	$t4, 'S', skA		# if(inkey() != 'S') -> skip to skA
		div	$t5, $t5, 2			# else -> delay / 2 (same as dividing the frequency by half)
		
skA:	bne	$t4, 'R', skB		# if(inkey() != 'N') -> skip to SkB
		mul	$t5, $t5, 2			# else -> delay * 2 (same as doubling the frequency)

skB:	rem	$t3, $t2, 2
		bnez	$t3, sk1		# cnt10 % 2 != 0 -> skip to sk1
		addiu	$t1, $t1, 1		# else -> cnt5++
		
sk1:	rem	$t3, $t2, 10
		bnez	$t3, sk2		# cnt10 % 10 != 0 -> skip to sk2
		addiu	$t0, $t0, 1		# else -> cnt1++

sk2:	li	$a1, 0x000400A
		
		# print 1Hz
		move	$a0, $t0
		li	$v0, printInt
		syscall
		
		# print tab
		li	$a0, '\t'
		li	$v0, putChar
		syscall
		
		# print 5Hz
		move	$a0, $t1
		li	$v0, printInt
		syscall
		
		# print tab
		li	$a0, '\t'
		li	$v0, putChar
		syscall
		
		# print 10Hz
		move	$a0, $t2
		li	$v0, printInt
		syscall
		
		li	$a0, '\r'
		li	$v0, putChar
		syscall
		
		addiu	$t2, $t2, 1		# cont10++
		
		j while
		
ewhile:	jr	$ra

###############

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