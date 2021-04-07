	.data
	
	.equ SFR_BASE_HI, 0xBF88	# 16 MSbits of SFR area
	.equ TRISE, 0x6100			# TRISE address is 0xBF886100
	.equ PORTE, 0x6110			# PORTE address is 0xBF886110
	.equ LATE, 0x6120			# LATE address is 0xBF886120
	
	.equ TRISB, 0x6040
	.equ PORTB, 0x6050
	.equ LATB, 0x6060
	
	.text
	.globl main
		
#	RE0 -> Output	(0)
#	RB0 -> Input	(1)

main:
	lui		$t1, SFR_BASE_HI
	lw		$t2, TRISE($t1)
	andi	$t2, $t2, 0xFFF0	# bit0 a bit3 = 0
	sw		$t2, TRISE($t1)

	lw		$t2, TRISB($t1)
	ori		$t2, $t2, 0x000F	# bit0 a bit3 = 1
	sw		$t2, TRISB($t1)
	
while:
	lw		$t2, PORTB($t1)		# Read and clean PORTB register (input)	
	andi	$t2, $t2, 0x000F
	
	xor		$t2, $t2, 0x0009

	lw		$t3, LATE($t1)		# Read and clean LATE register (output)
	andi	$t3, $t2, 0xFFF0

	or		$t3, $t3, $t2		# Combine both registers and write to LATE 
	sw		$t3, LATE($t1)

	j		while