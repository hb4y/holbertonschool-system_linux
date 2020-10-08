BITS 64

global asm_strcmp

asm_strcmp:
	push rbp
	mov rbp, rsp
	xor rax, rax
	xor rbx, rbx
	dec rbx
str_loop:
	inc rbx
	mov al, [rdi+rbx]
	sub al, [rsi+rbx]
	cmp al, 0
	jg greater_out
	jl less_out
	cmp byte [rdi+rbx], 0
	je epilogue
	cmp byte [rsi+rbx], 0
	jne str_loop
	jmp epilogue
less_out:
	mov rax, -1
	jmp epilogue
greater_out:
	mov rax, 1
epilogue:
	mov rsp, rbp
	pop rbp
	ret
