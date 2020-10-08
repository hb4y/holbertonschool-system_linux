BITS 64

global asm_strchr

asm_strchr:
	push rbp		;prologue
	mov rbp, rsp
	xor rax, rax		;set rax to 0
	dec rax			;dec rax by 1
str_loop:			;loop tag
	inc rax			;inc rax by 1
	cmp BYTE [rdi+rax], sil
	je store
	cmp BYTE [rdi+rax], 0	;check if null byte
	jne str_loop		;if not loop
	jmp null_ret
store:
	add rdi, rax
	mov rax, rdi
epilogue:
	mov rsp, rbp		;epilogue
	pop rbp
	ret
null_ret:
	mov rax, 0
	jmp epilogue
