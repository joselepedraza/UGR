	.file	"figura1-modificado_a.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"Tiempo(seg): %f\nR[0]=%d, R[39999]=%d \n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB2:
	.section	.text.startup,"ax",@progbits
.LHOTB2:
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
	xorl	%edi, %edi
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movl	$s+40000, %r15d
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movl	$s+40004, %r14d
	subq	$160072, %rsp
	.cfi_def_cfa_offset 160128
	leaq	16(%rsp), %rsi
	movq	%fs:40, %rax
	movq	%rax, 160056(%rsp)
	xorl	%eax, %eax
	call	clock_gettime
	leaq	52(%rsp), %rax
	movq	%rax, 8(%rsp)
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L2:
	movl	$s, %edx
	xorl	%r12d, %r12d
	xorl	%ebp, %ebp
	xorl	%ebx, %ebx
	xorl	%r11d, %r11d
	xorl	%esi, %esi
	.p2align 4,,10
	.p2align 3
.L3:
	movl	(%rdx), %ecx
	addq	$40, %rdx
	leal	(%rax,%rcx,2), %ecx
	addl	%ecx, %esi
	movl	-32(%rdx), %ecx
	leal	(%rax,%rcx,2), %ecx
	addl	%ecx, %r11d
	movl	-24(%rdx), %ecx
	leal	(%rax,%rcx,2), %ecx
	addl	%ecx, %ebx
	movl	-16(%rdx), %ecx
	leal	(%rax,%rcx,2), %ecx
	addl	%ecx, %ebp
	movl	-8(%rdx), %ecx
	leal	(%rax,%rcx,2), %ecx
	addl	%ecx, %r12d
	cmpq	%rdx, %r15
	jne	.L3
	movl	$s+4, %edx
	xorl	%edi, %edi
	xorl	%r8d, %r8d
	xorl	%r9d, %r9d
	xorl	%r10d, %r10d
	xorl	%r13d, %r13d
	.p2align 4,,10
	.p2align 3
.L4:
	movl	(%rdx), %ecx
	addq	$40, %rdx
	leal	(%rcx,%rcx,2), %ecx
	subl	%eax, %ecx
	addl	%ecx, %r13d
	movl	-32(%rdx), %ecx
	leal	(%rcx,%rcx,2), %ecx
	subl	%eax, %ecx
	addl	%ecx, %r10d
	movl	-24(%rdx), %ecx
	leal	(%rcx,%rcx,2), %ecx
	subl	%eax, %ecx
	addl	%ecx, %r9d
	movl	-16(%rdx), %ecx
	leal	(%rcx,%rcx,2), %ecx
	subl	%eax, %ecx
	addl	%ecx, %r8d
	movl	-8(%rdx), %ecx
	leal	(%rcx,%rcx,2), %ecx
	subl	%eax, %ecx
	addl	%ecx, %edi
	cmpq	%rdx, %r14
	jne	.L4
	addl	%r11d, %esi
	addl	%r13d, %r10d
	addl	%esi, %ebx
	addl	%r10d, %r9d
	addl	%ebx, %ebp
	addl	%r9d, %r8d
	addl	%ebp, %r12d
	addl	%r8d, %edi
	cmpl	%edi, %r12d
	jge	.L5
	movq	8(%rsp), %rdi
	movl	%r12d, (%rdi)
.L6:
	addl	$1, %eax
	addq	$4, 8(%rsp)
	cmpl	$40001, %eax
	jne	.L2
	leaq	32(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	40(%rsp), %rax
	subq	24(%rsp), %rax
	movl	$.LC1, %esi
	pxor	%xmm0, %xmm0
	movl	160044(%rsp), %ecx
	movl	48(%rsp), %edx
	movl	$1, %edi
	cvtsi2sdq	%rax, %xmm0
	movq	32(%rsp), %rax
	subq	16(%rsp), %rax
	movapd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	divsd	.LC0(%rip), %xmm1
	cvtsi2sdq	%rax, %xmm0
	movl	$1, %eax
	addsd	%xmm1, %xmm0
	call	__printf_chk
	xorl	%eax, %eax
	movq	160056(%rsp), %rsi
	xorq	%fs:40, %rsi
	jne	.L13
	addq	$160072, %rsp
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
.L5:
	.cfi_restore_state
	movq	8(%rsp), %rbx
	movl	%edi, (%rbx)
	jmp	.L6
.L13:
	call	__stack_chk_fail
	.cfi_endproc
.LFE38:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE2:
	.section	.text.startup
.LHOTE2:
	.comm	s,40000,32
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	1104006501
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
