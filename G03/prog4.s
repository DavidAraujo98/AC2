	.data
	
	.equ SFR_BASE_HI, 0xBF88	# 16 MSbits of SFR area
	.equ TRISE, 0x6100			# TRISE address is 0xBF886100
	.equ PORTE, 0x6110			# PORTE address is 0xBF886110
	.equ LATE, 0x6120			# LATE address is 0xBF886120
	
	.equ TRISB, 0x6040
	.equ PORTB, 0x6050
	.equ LATB, 0x6060
	
	.equ resetTimer, 12
	.equ readTime, 11

	.text
	.globl main
		
#	RE0 -> Output	(0)
#	RB0 -> Input	(1)
#	$t0 -> v

main:
	lui		$t1, SFR_BASE_HI
	lw		$t2, TRISE($t1)
	andi	$t2, $t2, 0xFFFE	# bit0 = 0
	sw		$t2, TRISE($t1)
	
	li		$a0, 500
	li		$t0, 0				# v = 0
	
while: 
	sw		$t0, LATE($t1)		# write v to LATE
	xori	$t0, $t0, 1
	jal		delay
	
	j		while

	jr		$ra

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
