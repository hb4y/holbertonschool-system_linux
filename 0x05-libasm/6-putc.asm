BITS 64

global asm_putc

asm_putc:
	push rbp
	mov rbp, rsp
	xor rax, rax

	mov rax, 1
	push rdi
	mov rdi, 1
	mov rsi, rsp
	mov rdx, 1
	syscall
epilogue:
	mov rsp, rbp
	pop rbp
	ret
