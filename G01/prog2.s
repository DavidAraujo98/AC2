#	int main(void) {
#		char c;
#		do {
#			c = getChar();
#			if( c != '\n' )
#			putChar( c );
#		} while( c != '\n' );
#		return 0;
#	} 
#
#	$t0:	c

		.data
		.equ	getChar, 2
		.equ	putChar, 3
		.text
		.globl main

main:	li	$v0, getChar
		syscall
		
		move $a0, $v0
		beq $a0, '\n', while
		
		li	$v0, putChar
		syscall
		
while:	bne	$a0, '\n', main 	
		
		li	$v0, 0			# return 0;
		jr	$ra