	.file	"pmm-secuencial-modificado_a.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Falta num\n"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"num debe ser divisible entre 5\n"
	.section	.rodata.str1.1
.LC3:
	.string	"Tiempo: %11.9f\n"
.LC4:
	.string	"A[0][0]: %d, A[n-1][n-1]: %d\n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB5:
	.section	.text.startup,"ax",@progbits
.LHOTB5:
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
	subq	$104, %rsp
	.cfi_def_cfa_offset 160
	movq	%fs:40, %rax
	movq	%rax, 88(%rsp)
	xorl	%eax, %eax
	cmpl	$1, %edi
	jle	.L39
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	movl	$1717986919, %edx
	movq	%rax, %r12
	movl	%eax, %ebp
	imull	%edx
	movl	%edx, %eax
	movl	%r12d, %edx
	sarl	%eax
	sarl	$31, %edx
	subl	%edx, %eax
	leal	(%rax,%rax,4), %eax
	cmpl	%r12d, %eax
	jne	.L40
	movslq	%r12d, %r13
	leaq	0(,%r13,8), %rax
	movq	%rax, %rdi
	movq	%rax, 32(%rsp)
	call	malloc
	testl	%r12d, %r12d
	movq	%rax, %rdi
	movq	%rax, 24(%rsp)
	jle	.L4
	leaq	0(,%r13,4), %rbx
	movq	%rax, %r14
	leal	-1(%r12), %eax
	movq	%rbx, %r15
	movq	%rbx, 40(%rsp)
	leaq	8(,%rax,8), %rbx
	leaq	(%rdi,%rbx), %r13
.L5:
	movq	%r15, %rdi
	addq	$8, %r14
	call	malloc
	movq	%rax, -8(%r14)
	cmpq	%r13, %r14
	jne	.L5
	movq	32(%rsp), %rdi
	call	malloc
	movq	40(%rsp), %r14
	movq	%rax, 16(%rsp)
	movq	%rax, %r13
	addq	%rax, %rbx
.L7:
	movq	%r14, %rdi
	addq	$8, %r13
	call	malloc
	movq	%rax, -8(%r13)
	cmpq	%rbx, %r13
	jne	.L7
	movq	32(%rsp), %rdi
	xorl	%r13d, %r13d
	call	malloc
	movq	40(%rsp), %r14
	movq	%rax, %rbx
.L9:
	movq	%r14, %rdi
	call	malloc
	movq	%rax, (%rbx,%r13,8)
	addq	$1, %r13
	cmpl	%r13d, %ebp
	jg	.L9
	movq	16(%rsp), %r10
	movq	24(%rsp), %r11
	xorl	%r9d, %r9d
	xorl	%r8d, %r8d
.L12:
	movq	(%r10,%r8,8), %rdi
	movq	(%rbx,%r8,8), %rsi
	movl	%r9d, %edx
	movq	(%r11,%r8,8), %rcx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L11:
	movl	%edx, (%rdi,%rax,4)
	movl	%edx, (%rsi,%rax,4)
	addl	$1, %edx
	movl	$0, (%rcx,%rax,4)
	addq	$1, %rax
	cmpl	%eax, %ebp
	jg	.L11
	addq	$1, %r8
	addl	%r12d, %r9d
	cmpl	%r8d, %ebp
	jg	.L12
	leaq	48(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	$0, 8(%rsp)
.L18:
	movq	16(%rsp), %rdi
	movq	8(%rsp), %rax
	xorl	%r13d, %r13d
	movq	(%rdi,%rax,8), %r15
	movq	24(%rsp), %rdi
	movq	(%rdi,%rax,8), %r14
	.p2align 4,,10
	.p2align 3
.L17:
	leaq	0(,%r13,4), %rcx
	movq	%r15, %rdx
	movq	%rbx, %rax
	xorl	%r12d, %r12d
	xorl	%r11d, %r11d
	xorl	%r10d, %r10d
	xorl	%r9d, %r9d
	xorl	%r8d, %r8d
	xorl	%edi, %edi
	.p2align 4,,10
	.p2align 3
.L14:
	movq	(%rax), %rsi
	addl	$5, %edi
	addq	$20, %rdx
	addq	$40, %rax
	movl	(%rsi,%rcx), %esi
	imull	-20(%rdx), %esi
	addl	%esi, %r8d
	movq	-32(%rax), %rsi
	movl	(%rsi,%rcx), %esi
	imull	-16(%rdx), %esi
	addl	%esi, %r9d
	movq	-24(%rax), %rsi
	movl	(%rsi,%rcx), %esi
	imull	-12(%rdx), %esi
	addl	%esi, %r10d
	movq	-16(%rax), %rsi
	movl	(%rsi,%rcx), %esi
	imull	-8(%rdx), %esi
	addl	%esi, %r11d
	movq	-8(%rax), %rsi
	movl	(%rsi,%rcx), %esi
	imull	-4(%rdx), %esi
	addl	%esi, %r12d
	cmpl	%ebp, %edi
	jl	.L14
	addl	%r9d, %r8d
	addl	%r8d, %r10d
	addl	%r10d, %r11d
	addl	%r11d, %r12d
	movl	%r12d, (%r14,%r13,4)
	addq	$1, %r13
	cmpl	%r13d, %ebp
	jg	.L17
	addq	$1, 8(%rsp)
	movq	8(%rsp), %rax
	cmpl	%eax, %ebp
	jg	.L18
.L16:
	leaq	64(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	72(%rsp), %rax
	subq	56(%rsp), %rax
	movl	$.LC3, %esi
	pxor	%xmm0, %xmm0
	movl	$1, %edi
	cvtsi2sdq	%rax, %xmm0
	movq	64(%rsp), %rax
	subq	48(%rsp), %rax
	movapd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	divsd	.LC2(%rip), %xmm1
	cvtsi2sdq	%rax, %xmm0
	movl	$1, %eax
	addsd	%xmm1, %xmm0
	call	__printf_chk
	movq	24(%rsp), %r15
	movq	32(%rsp), %rdi
	movl	$.LC4, %esi
	movq	-8(%r15,%rdi), %rax
	movq	40(%rsp), %rdi
	movl	-4(%rax,%rdi), %ecx
	movq	(%r15), %rax
	movl	$1, %edi
	movl	(%rax), %edx
	xorl	%eax, %eax
	call	__printf_chk
	movq	%r15, %rdi
	call	free
	movq	16(%rsp), %rdi
	call	free
	movq	%rbx, %rdi
	call	free
	xorl	%eax, %eax
	movq	88(%rsp), %rbx
	xorq	%fs:40, %rbx
	jne	.L41
	addq	$104, %rsp
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
.L4:
	.cfi_restore_state
	movq	32(%rsp), %rbx
	movq	%rbx, %rdi
	call	malloc
	movq	%rbx, %rdi
	movq	%rax, 16(%rsp)
	call	malloc
	leaq	48(%rsp), %rsi
	xorl	%edi, %edi
	movq	%rax, %rbx
	call	clock_gettime
	leaq	0(,%r13,4), %rax
	movq	%rax, 40(%rsp)
	jmp	.L16
.L40:
	movq	stderr(%rip), %rcx
	movl	$.LC1, %edi
	movl	$31, %edx
	movl	$1, %esi
	call	fwrite
	orl	$-1, %edi
	call	exit
.L41:
	call	__stack_chk_fail
.L39:
	movq	stderr(%rip), %rcx
	movl	$.LC0, %edi
	movl	$10, %edx
	movl	$1, %esi
	call	fwrite
	orl	$-1, %edi
	call	exit
	.cfi_endproc
.LFE38:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE5:
	.section	.text.startup
.LHOTE5:
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC2:
	.long	0
	.long	1104006501
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
