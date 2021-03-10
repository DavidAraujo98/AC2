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
		.eqv	getChar, 2
		.eqv	putChar, 3
		.text
		.globl main

main:	li	$v0, getChar
		syscall
		
		beq $v0, '\n', while
		
		move	$a0, $v0
		li	$v0, putChar
		syscall
		
while:	bne	$a0, '\n', main 	
		
		li	$v0, 0			# return 0;
		jr	$ra