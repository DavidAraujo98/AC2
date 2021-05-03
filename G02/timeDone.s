	.data
	
	.equ readCoreTimer, 11
	.equ resetCoreTimer, 12
	
	.text
	.globl timeDone

#	$t1 -> retValue
#	$t2 -> curCount
#	$t4 -> ms * 20000
#	$t3 -> 20000

timeDone:
	li	$t1, 0
	
	blez	$a1, else
	li	$v0, resetCoreTimer
	syscall
	
else:
	li	$t2, readCoreTimer
	syscall
	
	li	$t3, 20000
	mul	$t4, $a0, $t3		# $t4 = ms * 20000
		
	ble	$t2, $t3, eif
	div $t1, $t2, $t3
	
eif:
	move $v0, $t1