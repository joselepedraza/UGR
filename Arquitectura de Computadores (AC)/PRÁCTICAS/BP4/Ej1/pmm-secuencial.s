	.file	"pmm-secuencial.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Falta num\n"
.LC2:
	.string	"Tiempo: %11.9f\n"
.LC3:
	.string	"A[0][0]: %d, A[n-1][n-1]: %d\n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB4:
	.section	.text.startup,"ax",@progbits
.LHOTB4:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB38:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	cmpl	$1, %edi
	jle	.L37
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	movslq	%eax, %rbx
	movq	%rax, %r15
	movq	%rax, 8(%rsp)
	movl	%eax, %r13d
	leaq	0(,%rbx,8), %rax
	movq	%rax, %rdi
	movq	%rax, (%rsp)
	call	malloc
	testl	%r15d, %r15d
	movq	%rax, %r12
	movq	%r15, %rax
	jle	.L3
	subl	$1, %eax
	salq	$2, %rbx
	movq	%r12, %r15
	leaq	8(,%rax,8), %r14
	leaq	(%r12,%r14), %rbp
.L4:
	movq	%rbx, %rdi
	addq	$8, %r15
	call	malloc
	movq	%rax, -8(%r15)
	cmpq	%rbp, %r15
	jne	.L4
	movq	(%rsp), %rdi
	call	malloc
	movq	%rax, %rbp
	movq	%rax, %r15
	addq	%rax, %r14
.L6:
	movq	%rbx, %rdi
	addq	$8, %r15
	call	malloc
	movq	%rax, -8(%r15)
	cmpq	%r14, %r15
	jne	.L6
	movq	(%rsp), %rdi
	xorl	%r15d, %r15d
	call	malloc
	movq	%rax, %r14
.L8:
	movq	%rbx, %rdi
	call	malloc
	movq	%rax, (%r14,%r15,8)
	addq	$1, %r15
	cmpl	%r15d, %r13d
	jg	.L8
	movl	8(%rsp), %r15d
	xorl	%r9d, %r9d
	xorl	%edi, %edi
.L11:
	movq	0(%rbp,%rdi,8), %rsi
	movq	(%r14,%rdi,8), %rcx
	movl	%r9d, %edx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L10:
	movl	%edx, (%rsi,%rax,4)
	movl	%edx, (%rcx,%rax,4)
	addq	$1, %rax
	addl	$1, %edx
	cmpl	%eax, %r13d
	jg	.L10
	addq	$1, %rdi
	addl	%r15d, %r9d
	cmpl	%edi, %r13d
	jg	.L11
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	xorl	%r11d, %r11d
.L16:
	movq	(%r12,%r11,8), %r10
	movq	0(%rbp,%r11,8), %rdi
	xorl	%r9d, %r9d
	.p2align 4,,10
	.p2align 3
.L14:
	leaq	0(,%r9,4), %rsi
	xorl	%eax, %eax
	xorl	%ecx, %ecx
	.p2align 4,,10
	.p2align 3
.L13:
	movq	(%r14,%rax,8), %rdx
	movl	(%rdx,%rsi), %edx
	imull	(%rdi,%rax,4), %edx
	addq	$1, %rax
	addl	%edx, %ecx
	cmpl	%eax, %r13d
	jg	.L13
	movl	%ecx, (%r10,%r9,4)
	addq	$1, %r9
	cmpl	%r9d, %r13d
	jg	.L14
	addq	$1, %r11
	cmpl	%r11d, %r13d
	jg	.L16
.L15:
	leaq	32(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	40(%rsp), %rax
	subq	24(%rsp), %rax
	movl	$.LC2, %esi
	pxor	%xmm0, %xmm0
	movl	$1, %edi
	cvtsi2sdq	%rax, %xmm0
	movq	32(%rsp), %rax
	subq	16(%rsp), %rax
	movapd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	divsd	.LC1(%rip), %xmm1
	cvtsi2sdq	%rax, %xmm0
	movl	$1, %eax
	addsd	%xmm1, %xmm0
	call	__printf_chk
	movq	(%rsp), %rax
	movl	$.LC3, %esi
	movl	$1, %edi
	movq	-8(%r12,%rax), %rax
	movl	-4(%rax,%rbx), %ecx
	movq	(%r12), %rax
	movl	(%rax), %edx
	xorl	%eax, %eax
	call	__printf_chk
	movq	%r12, %rdi
	call	free
	movq	%rbp, %rdi
	call	free
	movq	%r14, %rdi
	call	free
	xorl	%eax, %eax
	movq	56(%rsp), %rbx
	xorq	%fs:40, %rbx
	jne	.L38
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L3:
	.cfi_restore_state
	movq	(%rsp), %r15
	salq	$2, %rbx
	movq	%r15, %rdi
	call	malloc
	movq	%r15, %rdi
	movq	%rax, %rbp
	call	malloc
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	movq	%rax, %r14
	call	clock_gettime
	jmp	.L15
.L37:
	movq	stderr(%rip), %rcx
	movl	$.LC0, %edi
	movl	$10, %edx
	movl	$1, %esi
	call	fwrite
	orl	$-1, %edi
	call	exit
.L38:
	call	__stack_chk_fail
	.cfi_endproc
.LFE38:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE4:
	.section	.text.startup
.LHOTE4:
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	1104006501
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
