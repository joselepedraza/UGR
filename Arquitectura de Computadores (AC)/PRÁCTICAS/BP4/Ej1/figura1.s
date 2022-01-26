	.file	"figura1.c"
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
	subq	$160056, %rsp
	.cfi_def_cfa_offset 160064
	xorl	%edi, %edi
	movq	%rsp, %rsi
	movq	%fs:40, %rax
	movq	%rax, 160040(%rsp)
	xorl	%eax, %eax
	call	clock_gettime
	movl	s+39992(%rip), %eax
	leaq	36(%rsp), %rdx
	leal	(%rax,%rax), %edi
	movl	s+39996(%rip), %eax
	leal	(%rax,%rax,2), %r8d
	movl	$1, %eax
	jmp	.L2
	.p2align 4,,10
	.p2align 3
.L5:
	addl	$1, %eax
	movl	%esi, (%rdx)
	addq	$4, %rdx
	cmpl	$40001, %eax
	je	.L4
.L2:
	leal	(%rax,%rdi), %esi
	movl	%r8d, %ecx
	subl	%eax, %ecx
	cmpl	%ecx, %esi
	jl	.L5
	addl	$1, %eax
	movl	%ecx, (%rdx)
	addq	$4, %rdx
	cmpl	$40001, %eax
	jne	.L2
.L4:
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	24(%rsp), %rax
	subq	8(%rsp), %rax
	movl	$1, %edi
	pxor	%xmm0, %xmm0
	movl	160028(%rsp), %ecx
	movl	32(%rsp), %edx
	movl	$.LC1, %esi
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
	movq	160040(%rsp), %rdi
	xorq	%fs:40, %rdi
	jne	.L12
	addq	$160056, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L12:
	.cfi_restore_state
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
