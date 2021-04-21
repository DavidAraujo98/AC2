	.data
	
	.equ SFR_BASE_HI, 0xBF88	# 16 MSbits of SFR area
	.equ TRISE, 0x6100			# TRISE address is 0xBF886100
	.equ PORTE, 0x6110			# PORTE address is 0xBF886110
	.equ LATE, 0x6120			# LATE address is 0xBF886120

	.equ readTimer, 11
	.equ resetTimer, 12

	.text
	.globl main

main:
	lui		$t1, SFR_BASE_HI
	lw		$t2, TRISE($t1)
	andi	$t2, $t2, 0xFFF0	# RE0-R03 = 0 
	sw		$t2, TRISE($t1)
	
	li		$a0, 200
	li		$t0, 0
	
	lw		$t3, LATE($t1)
	andi	$t3, $t3, 0xFFF0	# Coloca output a 0 (4 leds apagados)
	sw		$t3, LATE($t1)
	
while:
	li		$a0, 200
	jal delay

	lw		$t3, LATE($t1)
	nor		$t0, $t3, $0		# negates every bit

	srl		$t0, $t0, 4			# moves negated bit 4 to first position 
	andi	$t0, $t0, 0x0001	# cleans value, leaving only the bit 1
	
	sll		$t3, $t3, 1			# shifs left one position the previous value
	or		$t3, $t3, $t0		# OR operation only changes the 0 from the sll, if previous bit 4 was a 0
	
	sw		$t3, LATE($t1)

	j 		while
	
	jr		$ra

delay:	
for:	
	blez	$a0, end
		
	li	$v0, resetTimer			# resetCoreTimer();
	syscall
		
sleep:	
	li	$v0, readTimer			# while(readCoreTimer() < K);
	syscall
	blt	$v0, 20000, sleep

	addi	$a0, $a0, -1 
	j for
		
end:
	jr	$ra
