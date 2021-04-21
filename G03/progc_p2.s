	.data
	
	.equ SFR_BASE_HI, 0xBF88	# 16 MSbits of SFR area
	.equ TRISE, 0x6100			# TRISE address is 0xBF886100
	.equ PORTE, 0x6110			# PORTE address is 0xBF886110
	.equ LATE, 0x6120			# LATE address is 0xBF886120
	
	.equ TRISB, 0x6040
	.equ PORTB, 0x6050
	.equ LATB, 0x6060
	
	.equ readTimer, 11
	.equ resetTimer, 12

	.text
	.globl main

main:
	lui		$t1, SFR_BASE_HI
	lw		$t2, TRISE($t1)
	andi	$t2, $t2, 0xFFF0	# RE0-R03 = 0 
	sw		$t2, TRISE($t1)
	
	lui		$t1, SFR_BASE_HI
	lw		$t2, TRISB($t1)
	ori		$t2, $t2, 0x000F	# RB0-RB3 = 1 
	sw		$t2, TRISB($t1)
	
	li		$a0, 250
	li		$t0, 0
	
	lw		$t3, LATE($t1)
	andi	$t3, $t3, 0xFFF0	# Coloca output a 0 (4 leds apagados)
	sw		$t3, LATE($t1)
	
while:
	li		$a0, 500
	jal delay
	
	lw		$t3, LATE($t1)
	
	lw		$t4, PORTB($t1)
	andi	$t4, $t4, 0x0008
	xori	$t4, $t4, 8
	
	addi	$t5, $0, -1
	bne		$t4, 8, cr
	addi	$t5, $0, 1

cr:	
	add		$t3, $t3, $t5
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
