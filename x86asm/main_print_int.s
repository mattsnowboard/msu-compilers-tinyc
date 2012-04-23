# print an integer
.section .text
.globl _start
_start:
	call main 
	jmp exit
.include "print_int.s"
.globl main
.type main, @function
main:
	pushl %ebp # save frame pointer
	movl %esp, %ebp # set frame pointer
	pushl $-100 # number to print
	call print_int
	movl %ebp, %esp
	popl %ebp 
	ret
.type exit, @function
exit:
	movl $0, %ebx
	movl $1, %eax
	int $0x80
