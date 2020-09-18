BITS 64

global asm_strlen

asm_strlen:
	push rbp				;prologue
	mov rbp, rsp
	xor rax, rax			;set rax to 0
	dec rax					;dec rax by 1
str_loop:					;loop tag
	inc rax					;inc rax by 1
	cmp byte [rdi+rax], 0	;check if null byte
	jne str_loop			;if not loop
	mov rsp, rbp			;epilogue
	pop rbp
	ret
