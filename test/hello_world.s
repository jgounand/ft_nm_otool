extern printf

global	_main

segment .text

_main:
	mov rax, writeSyscall
	mov rdi, 1
	mov rsi, helloString
	mov rdx, helloString.len
	syscall

	mov rax, 50
	ret

segment .data

writeSyscall:	equ 0x2000004

rturn:			equ	50
helloString:	db	"Hello World", 0xa
	.len:		equ	$ - helloString
