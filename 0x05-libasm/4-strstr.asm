BITS 64

global asm_strstr

asm_strstr:
	push rbp
	mov rbp, rsp
	xor rax, rax
	cmp BYTE [rsi], 0
	mov rax, rdi
	je epilogue
	xor rax, rax
	xor rbx, rbx
	xor rcx, rcx
str_loop:
	mov cl, [rdi]
	cmp cl, [rsi+rbx]
	jne not_same
	cmp rbx, 0
	je set_rax
needle_chk:
	cmp BYTE [rsi+rbx+1], 0
	je epilogue
	inc rbx
continue:
	inc rdi
	cmp BYTE [rdi], 0
	jne str_loop
	mov rax, 0
epilogue:
	mov rsp, rbp
	pop rbp
	ret
set_rax:
	mov rax, rdi
	jmp needle_chk
not_same:
	mov rbx, 0
	jmp continue
