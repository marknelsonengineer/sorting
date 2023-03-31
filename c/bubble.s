	.file	"bubble.c"
	.intel_syntax noprefix
	.text
	.globl	bubbleSortAsm
	.type	bubbleSortAsm, @function
bubbleSortAsm:
.LFB6:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR -8[rbp], rdi
	mov	QWORD PTR -16[rbp], rsi
	mov	rax, QWORD PTR -8[rbp]
	mov	rdx, QWORD PTR -16[rbp]
#APP
# 10 "bubble.c" 1
	mov r9, rdx 
	dec r9     
	outerLoop:  
	dec r9        
	jnz outerLoop 
	
# 0 "" 2
#NO_APP
	nop
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	bubbleSortAsm, .-bubbleSortAsm
	.globl	bubbleSort
	.type	bubbleSort, @function
bubbleSort:
.LFB7:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR -40[rbp], rdi
	mov	QWORD PTR -48[rbp], rsi
	mov	QWORD PTR -24[rbp], 0
	jmp	.L3
.L7:
	mov	QWORD PTR -16[rbp], 0
	jmp	.L4
.L6:
	mov	rax, QWORD PTR -16[rbp]
	lea	rdx, 0[0+rax*8]
	mov	rax, QWORD PTR -40[rbp]
	add	rax, rdx
	mov	rax, QWORD PTR [rax]
	mov	rdx, QWORD PTR -16[rbp]
	add	rdx, 1
	lea	rcx, 0[0+rdx*8]
	mov	rdx, QWORD PTR -40[rbp]
	add	rdx, rcx
	mov	rdx, QWORD PTR [rdx]
	cmp	rdx, rax
	jnb	.L5
	mov	rax, QWORD PTR -16[rbp]
	lea	rdx, 0[0+rax*8]
	mov	rax, QWORD PTR -40[rbp]
	add	rax, rdx
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR -8[rbp], rax
	mov	rax, QWORD PTR -16[rbp]
	add	rax, 1
	lea	rdx, 0[0+rax*8]
	mov	rax, QWORD PTR -40[rbp]
	add	rax, rdx
	mov	rdx, QWORD PTR -16[rbp]
	lea	rcx, 0[0+rdx*8]
	mov	rdx, QWORD PTR -40[rbp]
	add	rdx, rcx
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR [rdx], rax
	mov	rax, QWORD PTR -16[rbp]
	add	rax, 1
	lea	rdx, 0[0+rax*8]
	mov	rax, QWORD PTR -40[rbp]
	add	rdx, rax
	mov	rax, QWORD PTR -8[rbp]
	mov	QWORD PTR [rdx], rax
.L5:
	add	QWORD PTR -16[rbp], 1
.L4:
	mov	rax, QWORD PTR -48[rbp]
	sub	rax, QWORD PTR -24[rbp]
	sub	rax, 1
	cmp	QWORD PTR -16[rbp], rax
	jb	.L6
	add	QWORD PTR -24[rbp], 1
.L3:
	mov	rax, QWORD PTR -48[rbp]
	sub	rax, 1
	cmp	QWORD PTR -24[rbp], rax
	jb	.L7
	nop
	nop
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	bubbleSort, .-bubbleSort
	.section	.rodata
	.align 8
.LC1:
	.string	"%zu: bubbleSort took about %.5f seconds\n"
	.text
	.globl	doRun
	.type	doRun, @function
doRun:
.LFB8:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 88
	.cfi_offset 3, -24
	mov	QWORD PTR -88[rbp], rdi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -24[rbp], rax
	xor	eax, eax
	mov	rax, QWORD PTR -88[rbp]
	mov	esi, 8
	mov	rdi, rax
	call	calloc@PLT
	mov	QWORD PTR -72[rbp], rax
	mov	QWORD PTR -64[rbp], 0
	mov	QWORD PTR -56[rbp], 0
	mov	QWORD PTR -48[rbp], 0
	mov	QWORD PTR -40[rbp], 0
	mov	QWORD PTR -80[rbp], 0
	jmp	.L9
.L10:
	call	rand@PLT
	cdqe
	sal	rax, 32
	mov	rbx, rax
	call	rand@PLT
	movsx	rdx, eax
	mov	rax, QWORD PTR -80[rbp]
	lea	rcx, 0[0+rax*8]
	mov	rax, QWORD PTR -72[rbp]
	add	rax, rcx
	add	rdx, rbx
	mov	QWORD PTR [rax], rdx
	add	QWORD PTR -80[rbp], 1
.L9:
	mov	rax, QWORD PTR -80[rbp]
	cmp	rax, QWORD PTR -88[rbp]
	jb	.L10
	lea	rax, -64[rbp]
	mov	rsi, rax
	mov	edi, 1
	call	clock_gettime@PLT
	mov	rdx, QWORD PTR -88[rbp]
	mov	rax, QWORD PTR -72[rbp]
	mov	rsi, rdx
	mov	rdi, rax
	call	bubbleSortAsm
	mov	rdx, QWORD PTR -88[rbp]
	mov	rax, QWORD PTR -72[rbp]
	mov	rsi, rdx
	mov	rdi, rax
	call	bubbleSort
	lea	rax, -48[rbp]
	mov	rsi, rax
	mov	edi, 1
	call	clock_gettime@PLT
	mov	rax, QWORD PTR -48[rbp]
	pxor	xmm1, xmm1
	cvtsi2sd	xmm1, rax
	mov	rax, QWORD PTR -40[rbp]
	pxor	xmm2, xmm2
	cvtsi2sd	xmm2, rax
	movsd	xmm0, QWORD PTR .LC0[rip]
	mulsd	xmm0, xmm2
	addsd	xmm0, xmm1
	mov	rax, QWORD PTR -64[rbp]
	pxor	xmm2, xmm2
	cvtsi2sd	xmm2, rax
	mov	rax, QWORD PTR -56[rbp]
	pxor	xmm3, xmm3
	cvtsi2sd	xmm3, rax
	movsd	xmm1, QWORD PTR .LC0[rip]
	mulsd	xmm1, xmm3
	addsd	xmm1, xmm2
	subsd	xmm0, xmm1
	movq	rdx, xmm0
	mov	rax, QWORD PTR -88[rbp]
	movq	xmm0, rdx
	mov	rsi, rax
	lea	rax, .LC1[rip]
	mov	rdi, rax
	mov	eax, 1
	call	printf@PLT
	mov	rax, QWORD PTR -72[rbp]
	mov	rdi, rax
	call	free@PLT
	nop
	mov	rax, QWORD PTR -24[rbp]
	sub	rax, QWORD PTR fs:40
	je	.L11
	call	__stack_chk_fail@PLT
.L11:
	mov	rbx, QWORD PTR -8[rbp]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	doRun, .-doRun
	.section	.rodata
.LC2:
	.string	"Bubble Sort"
	.text
	.globl	main
	.type	main, @function
main:
.LFB9:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	lea	rax, .LC2[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	QWORD PTR -8[rbp], 0
	jmp	.L13
.L14:
	mov	rax, QWORD PTR -8[rbp]
	mov	edx, 1
	mov	ecx, eax
	sal	edx, cl
	mov	eax, edx
	cdqe
	mov	rdi, rax
	call	doRun
	add	QWORD PTR -8[rbp], 1
.L13:
	cmp	QWORD PTR -8[rbp], 9
	jbe	.L14
	mov	eax, 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	-400107883
	.long	1041313291
	.ident	"GCC: (GNU) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
