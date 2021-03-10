#	int main(void) {
#		int value;
#		while(1){
#			printStr("\nIntroduza um numero (sinal e módulo): ");
#			value = readInt10();
#			printStr("\nValor lido, em base 2: ");
#			printInt(value, 2);
#			printStr("\nValor lido, em base 16: ");
#			printInt(value, 16);
#			printStr("\nValor lido, em base 10 (unsigned): ");
#			printInt(value, 10);
#			printStr("\nValor lido, em base 10 (signed): ");
#			printInt10(value);
#		}
#		return 0;
#	}

		.data
		.eqv	printStr, 8
		.eqv	printInt, 6
		.eqv	printInt10, 7
		.eqv	readInt10, 5
		
str1:	.asciiz	"\nIntroduza um numero (sinal e módulo): "
str2:	.asciiz	"\nValor lido, em base 2: "
str3:	.asciiz	"\nValor lido, em base 16: "
str4:	.asciiz	"\nValor lido, em base 10 (unsigned): "
str5:	.asciiz	"\nValor lido, em base 10 (signed): "
		
		.text
		.globl main
	
main:	
while:	li	$v0, printStr			# printStr("\nIntroduza um numero (sinal e módulo): ");
		la	$a0, str1
		syscall
		
		li	$v0, readInt10			# value = readInt10();
		syscall
		move	$t0, $v0

		li	$v0, printStr			# printStr("\nValor lido, em base 2: ");
		la	$a0, str2
		syscall
		
		li	$v0, printInt			# printInt(value, 2); 
		move	$a0, $t0
		li	$a1, 2
		syscall
		
		li	$v0, printStr			# printStr("\nValor lido, em base 16: ");
		la	$a0, str3
		syscall
		
		li	$v0, printInt			# printInt(value, 16); 
		move	$a0, $t0
		li	$a1, 16
		syscall
		
		li	$v0, printStr			# printStr("\nValor lido, em base 10 (unsigned): ");
		la	$a0, str3
		syscall
		
		li	$v0, printInt			# printInt(value, 10); 
		move	$a0, $t0
		li	$a1, 10
		syscall
		
		li	$v0, printStr			# printStr("\nValor lido, em base 10 (signed): ");
		la	$a0, str4
		syscall
		
		li	$v0, printInt			# printInt(value); 
		move	$a0, $t0
		li	$a1, 10
		syscall
		
		j	while
		
		li	$v0, 0
		jr	$ra
		