	.file	"pmm-secuencial-modificado_b.c"
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
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	cmpl	$1, %edi
	jle	.L38
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	movl	$1717986919, %edx
	movq	%rax, %rbx
	movq	%rax, 8(%rsp)
	movl	%eax, %r13d
	imull	%edx
	movl	%edx, %eax
	movl	%ebx, %edx
	sarl	%eax
	sarl	$31, %edx
	subl	%edx, %eax
	leal	(%rax,%rax,4), %eax
	cmpl	%ebx, %eax
	jne	.L39
	movq	8(%rsp), %r15
	movslq	%r15d, %rbx
	leaq	0(,%rbx,8), %rax
	movq	%rax, %rdi
	movq	%rax, (%rsp)
	call	malloc
	testl	%r15d, %r15d
	movq	%rax, %rbp
	movq	%r15, %rax
	jle	.L4
	subl	$1, %eax
	salq	$2, %rbx
	movq	%rbp, %r15
	leaq	8(,%rax,8), %r14
	leaq	0(%rbp,%r14), %r12
.L5:
	movq	%rbx, %rdi
	addq	$8, %r15
	call	malloc
	movq	%rax, -8(%r15)
	cmpq	%r12, %r15
	jne	.L5
	movq	(%rsp), %rdi
	call	malloc
	movq	%rax, %r12
	movq	%rax, %r15
	addq	%rax, %r14
.L7:
	movq	%rbx, %rdi
	addq	$8, %r15
	call	malloc
	movq	%rax, -8(%r15)
	cmpq	%r14, %r15
	jne	.L7
	movq	(%rsp), %rdi
	xorl	%r15d, %r15d
	call	malloc
	movq	%rax, %r14
.L9:
	movq	%rbx, %rdi
	call	malloc
	movq	%rax, (%r14,%r15,8)
	addq	$1, %r15
	cmpl	%r15d, %r13d
	jg	.L9
	movl	8(%rsp), %r15d
	xorl	%r10d, %r10d
	xorl	%r9d, %r9d
.L12:
	movq	(%r12,%r9,8), %rdi
	movq	(%r14,%r9,8), %rsi
	movl	%r10d, %edx
	movq	0(%rbp,%r9,8), %rcx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L11:
	movl	%edx, (%rdi,%rax,4)
	movl	%edx, (%rsi,%rax,4)
	addl	$1, %edx
	movl	$0, (%rcx,%rax,4)
	addq	$1, %rax
	cmpl	%eax, %r13d
	jg	.L11
	addq	$1, %r9
	addl	%r15d, %r10d
	cmpl	%r9d, %r13d
	jg	.L12
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	xorl	%r11d, %r11d
.L18:
	movq	0(%rbp,%r11,8), %rdx
	movq	(%r12,%r11,8), %r10
	xorl	%r9d, %r9d
	.p2align 4,,10
	.p2align 3
.L17:
	movl	(%r10,%r9,4), %edi
	movq	(%r14,%r9,8), %rsi
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L14:
	movl	(%rsi,%rax,4), %ecx
	imull	%edi, %ecx
	addl	%ecx, (%rdx,%rax,4)
	addq	$1, %rax
	cmpl	%eax, %r13d
	jg	.L14
	addq	$1, %r9
	cmpl	%r9d, %r13d
	jg	.L17
	addq	$1, %r11
	cmpl	%r11d, %r13d
	jg	.L18
.L16:
	leaq	32(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	40(%rsp), %rax
	subq	24(%rsp), %rax
	movl	$.LC3, %esi
	pxor	%xmm0, %xmm0
	movl	$1, %edi
	cvtsi2sdq	%rax, %xmm0
	movq	32(%rsp), %rax
	subq	16(%rsp), %rax
	movapd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	divsd	.LC2(%rip), %xmm1
	cvtsi2sdq	%rax, %xmm0
	movl	$1, %eax
	addsd	%xmm1, %xmm0
	call	__printf_chk
	movq	(%rsp), %rax
	movl	$.LC4, %esi
	movl	$1, %edi
	movq	-8(%rbp,%rax), %rax
	movl	-4(%rax,%rbx), %ecx
	movq	0(%rbp), %rax
	movl	(%rax), %edx
	xorl	%eax, %eax
	call	__printf_chk
	movq	%rbp, %rdi
	call	free
	movq	%r12, %rdi
	call	free
	movq	%r14, %rdi
	call	free
	xorl	%eax, %eax
	movq	56(%rsp), %rbx
	xorq	%fs:40, %rbx
	jne	.L40
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
.L4:
	.cfi_restore_state
	movq	(%rsp), %r15
	salq	$2, %rbx
	movq	%r15, %rdi
	call	malloc
	movq	%r15, %rdi
	movq	%rax, %r12
	call	malloc
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	movq	%rax, %r14
	call	clock_gettime
	jmp	.L16
.L39:
	movq	stderr(%rip), %rcx
	movl	$.LC1, %edi
	movl	$31, %edx
	movl	$1, %esi
	call	fwrite
	orl	$-1, %edi
	call	exit
.L40:
	call	__stack_chk_fail
.L38:
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
