BITS 64

global asm_memcpy

asm_memcpy:
	push rbp
	mov rbp, rsp
	xor rax, rax
	xor rbx, rbx
	dec rax
str_loop:
	inc rax
	cmp rdx, 0
	je epilogue
	mov bl, [rsi+rax]
	mov [rdi+rax], bl
	dec rdx
	jmp str_loop
epilogue:
	mov rax, rdi
	mov rsp, rbp
	pop rbp
	ret
