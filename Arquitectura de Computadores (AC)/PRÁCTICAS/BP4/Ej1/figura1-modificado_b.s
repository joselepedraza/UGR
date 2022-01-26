	.file	"figura1-modificado_b.c"
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
	movl	$s+40000, %r14d
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$160056, %rsp
	.cfi_def_cfa_offset 160112
	movq	%rsp, %rsi
	leaq	36(%rsp), %r15
	movq	%fs:40, %rax
	movq	%rax, 160040(%rsp)
	xorl	%eax, %eax
	call	clock_gettime
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L2:
	movl	$s, %eax
	xorl	%r13d, %r13d
	xorl	%r12d, %r12d
	xorl	%ebp, %ebp
	xorl	%ebx, %ebx
	xorl	%edi, %edi
	xorl	%r11d, %r11d
	xorl	%r10d, %r10d
	xorl	%r9d, %r9d
	xorl	%r8d, %r8d
	xorl	%esi, %esi
	.p2align 4,,10
	.p2align 3
.L3:
	movl	(%rax), %ecx
	addq	$40, %rax
	leal	(%rdx,%rcx,2), %ecx
	addl	%ecx, %esi
	movl	-32(%rax), %ecx
	leal	(%rdx,%rcx,2), %ecx
	addl	%ecx, %r8d
	movl	-24(%rax), %ecx
	leal	(%rdx,%rcx,2), %ecx
	addl	%ecx, %r9d
	movl	-16(%rax), %ecx
	leal	(%rdx,%rcx,2), %ecx
	addl	%ecx, %r10d
	movl	-8(%rax), %ecx
	leal	(%rdx,%rcx,2), %ecx
	addl	%ecx, %r11d
	movl	-36(%rax), %ecx
	leal	(%rcx,%rcx,2), %ecx
	subl	%edx, %ecx
	addl	%ecx, %edi
	movl	-28(%rax), %ecx
	leal	(%rcx,%rcx,2), %ecx
	subl	%edx, %ecx
	addl	%ecx, %ebx
	movl	-20(%rax), %ecx
	leal	(%rcx,%rcx,2), %ecx
	subl	%edx, %ecx
	addl	%ecx, %ebp
	movl	-12(%rax), %ecx
	leal	(%rcx,%rcx,2), %ecx
	subl	%edx, %ecx
	addl	%ecx, %r12d
	movl	-4(%rax), %ecx
	leal	(%rcx,%rcx,2), %ecx
	subl	%edx, %ecx
	addl	%ecx, %r13d
	cmpq	%rax, %r14
	jne	.L3
	addl	%r8d, %esi
	addl	%ebx, %edi
	addl	%esi, %r9d
	addl	%edi, %ebp
	addl	%r9d, %r10d
	addl	%ebp, %r12d
	addl	%r10d, %r11d
	addl	%r12d, %r13d
	cmpl	%r13d, %r11d
	jge	.L4
	movl	%r11d, (%r15)
.L5:
	addl	$1, %edx
	addq	$4, %r15
	cmpl	$40001, %edx
	jne	.L2
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	24(%rsp), %rax
	subq	8(%rsp), %rax
	movl	$.LC1, %esi
	pxor	%xmm0, %xmm0
	movl	160028(%rsp), %ecx
	movl	32(%rsp), %edx
	movl	$1, %edi
	cvtsi2sdq	%rax, %xmm0
	movq	16(%rsp), %rax
	subq	(%rsp), %rax
	movapd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	divsd	.LC0(%rip), %xmm1
	cvtsi2sdq	%rax, %xmm0
	movl	$1, %eax
	addsd	%xmm1, %xmm0
	call	__printf_chk
	xorl	%eax, %eax
	movq	160040(%rsp), %rbx
	xorq	%fs:40, %rbx
	jne	.L11
	addq	$160056, %rsp
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
	movl	%r13d, (%r15)
	jmp	.L5
.L11:
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
