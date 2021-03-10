#	int main(void) {
#		char c;
#		do {
#			while( (c = inkey()) == 0 );
#			if( c != '\n' )
#			putChar( c );
#		} while( c != '\n' );
#		return 0;
#	}
#
#	$t0:	c

		.data
		.eqv	inkey,	1
		.text
		.globl main

main:
do:		li	$v0, inkey
		syscall
		beqz	$v0, do
	
		beq	$v0, '\n', while
		move	$a0, $v0
		li	$v0, putChar
		syscall
		
while:	bne	$a0, '\n', do
		
		li	$v0, 0
		jr	$ra