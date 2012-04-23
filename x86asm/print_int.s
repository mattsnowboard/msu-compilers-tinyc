# print an integer
.section .text
.globl print_int
.type print_int, @function
# print_it(int value) -- print value followed by \n to stdout.
print_int: 
	pushl %ebp 
	movl %esp, %ebp 
	.equ value, 8 # parameter offset
	# initialize local variables:
	.equ base, -4 
        pushl $10 # base = 10
	.equ bufsize, -8
	pushl $1 # bufsize = 1 ('\n')
	.equ negative, -12
	pushl $0 # negative = 0
	# stack: .. value return-addr saved-ebp base bufsize
	pushl $10 # push newline to be printed last
	movl value(%ebp), %eax 
        cmpl $0, %eax
        jge .L1 # if value >= 0
	# value < 0: remember
        movl $1, negative(%ebp)
	negl %eax # value = -value

.L1:
	cdq # setup %edx:%eax for division
        # eax = value/base, edx = value % base
	idivl base(%ebp) 
	# push remainder digit 
	pushl %edx
	addl $48, (%esp) # adding ascii 48
	incl bufsize(%ebp) # ++bufsize
        cmpl $0, %eax
	jne .L1 # loop if value != 0
	# put sign if negative
	cmpl $0, negative(%ebp)
	je .L2
	pushl $45 # '-'
	incl bufsize(%ebp)
.L2:
        # write(2): fd = ebx, buffer start = ecx, buffersize = edx, write comand =  eax = 4
	movl $4, %eax # code for write syscall
	movl $1, %ebx # fd stdout = 1
	movl %esp, %ecx # buffer start = top of stack
        movl $4, %edx # bufsize * 4 bytes
	imul bufsize(%ebp), %edx 
	int $0x80 # syscall
	movl %ebp, %esp
	popl %ebp # restore saved frame pointer 
	ret
