	.file	"daxpy.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Falta num\n"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC2:
	.string	"Tiempo(seg): %f\ny[0]=%d, y[N-1]=%d \n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB3:
	.section	.text.startup,"ax",@progbits
.LHOTB3:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB38:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$48, %rsp
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	.cfi_offset 12, -40
	.cfi_offset 3, -48
	movq	%fs:40, %rax
	movq	%rax, -40(%rbp)
	xorl	%eax, %eax
	cmpl	$1, %edi
	jle	.L17
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	movq	%rax, %r14
	movl	%eax, %ecx
	cltq
	leaq	18(,%rax,4), %rax
	shrq	$4, %rax
	salq	$4, %rax
	subq	%rax, %rsp
	movq	%rsp, %r13
	subq	%rax, %rsp
	leaq	3(%rsp), %r12
	shrq	$2, %r12
	testl	%r14d, %r14d
	leaq	0(,%r12,4), %rbx
	jle	.L3
	xorl	%edx, %edx
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L4:
	movl	%eax, 4(%r13,%rdx)
	movl	%eax, 4(%rbx,%rdx)
	addl	$1, %eax
	addq	$4, %rdx
	cmpl	%ecx, %eax
	jle	.L4
	leaq	-80(%rbp), %rsi
	xorl	%edi, %edi
	subl	$1, %r14d
	call	clock_gettime
	movl	%r14d, %esi
	xorl	%edx, %edx
	addq	$1, %rsi
	.p2align 4,,10
	.p2align 3
.L6:
	imull	$47, 4(%r13,%rdx,4), %ecx
	addl	%ecx, 4(%rbx,%rdx,4)
	addq	$1, %rdx
	cmpq	%rdx, %rsi
	jne	.L6
.L7:
	leaq	-64(%rbp), %rsi
	xorl	%edi, %edi
	movslq	%r14d, %r14
	call	clock_gettime
	movq	-56(%rbp), %rax
	subq	-72(%rbp), %rax
	movl	$1, %edi
	pxor	%xmm0, %xmm0
	movl	(%rbx,%r14,4), %ecx
	pxor	%xmm1, %xmm1
	movl	0(,%r12,4), %edx
	movl	$.LC2, %esi
	cvtsi2sdq	%rax, %xmm0
	movq	-64(%rbp), %rax
	subq	-80(%rbp), %rax
	cvtsi2sdq	%rax, %xmm1
	movl	$1, %eax
	divsd	.LC1(%rip), %xmm0
	addsd	%xmm1, %xmm0
	call	__printf_chk
	xorl	%eax, %eax
	movq	-40(%rbp), %rdi
	xorq	%fs:40, %rdi
	jne	.L18
	leaq	-32(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L3:
	.cfi_restore_state
	leaq	-80(%rbp), %rsi
	xorl	%edi, %edi
	subl	$1, %r14d
	call	clock_gettime
	jmp	.L7
.L18:
	call	__stack_chk_fail
.L17:
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
.LCOLDE3:
	.section	.text.startup
.LHOTE3:
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	1104006501
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
