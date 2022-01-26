	.file	"figura1-modificado_c.c"
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
	movl	$s+40000, %r13d
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$160056, %rsp
	.cfi_def_cfa_offset 160112
	movq	%rsp, %rsi
	leaq	36(%rsp), %r14
	movq	%fs:40, %rax
	movq	%rax, 160040(%rsp)
	xorl	%eax, %eax
	call	clock_gettime
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L2:
	movl	$s, %eax
	xorl	%r9d, %r9d
	xorl	%r8d, %r8d
	xorl	%edi, %edi
	xorl	%esi, %esi
	xorl	%ecx, %ecx
	xorl	%r12d, %r12d
	xorl	%ebp, %ebp
	xorl	%ebx, %ebx
	xorl	%r11d, %r11d
	xorl	%r10d, %r10d
	.p2align 4,,10
	.p2align 3
.L3:
	movl	(%rax), %r15d
	subl	%edx, %ecx
	subl	%edx, %esi
	addl	4(%rax), %ecx
	addl	12(%rax), %esi
	subl	%edx, %edi
	subl	%edx, %r8d
	addl	20(%rax), %edi
	addl	28(%rax), %r8d
	addl	%edx, %r15d
	subl	%edx, %r9d
	addq	$40, %rax
	addl	%r15d, %r10d
	movl	-32(%rax), %r15d
	addl	-4(%rax), %r9d
	addl	%edx, %r15d
	addl	%r15d, %r11d
	movl	-24(%rax), %r15d
	addl	%edx, %r15d
	addl	%r15d, %ebx
	movl	-16(%rax), %r15d
	addl	%edx, %r15d
	addl	%r15d, %ebp
	movl	-8(%rax), %r15d
	addl	%edx, %r15d
	addl	%r15d, %r12d
	cmpq	%rax, %r13
	jne	.L3
	addl	%esi, %ecx
	leal	(%r10,%r11), %eax
	addl	%ecx, %edi
	addl	%ebx, %eax
	addl	%edi, %r8d
	addl	%ebp, %eax
	addl	%r8d, %r9d
	addl	%r12d, %eax
	leal	(%r9,%r9,2), %ecx
	addl	%eax, %eax
	cmpl	%ecx, %eax
	jge	.L4
	movl	%eax, (%r14)
.L5:
	addl	$1, %edx
	addq	$4, %r14
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
	movl	%ecx, (%r14)
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
