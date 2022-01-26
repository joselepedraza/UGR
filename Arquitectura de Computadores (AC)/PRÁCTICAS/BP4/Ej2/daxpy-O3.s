	.file	"daxpy.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Falta num\n"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC4:
	.string	"Tiempo(seg): %f\ny[0]=%d, y[N-1]=%d \n"
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
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	cmpl	$1, %edi
	jle	.L48
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	movq	%rax, %rbx
	cltq
	leaq	18(,%rax,4), %rax
	shrq	$4, %rax
	salq	$4, %rax
	subq	%rax, %rsp
	leaq	3(%rsp), %r13
	subq	%rax, %rsp
	leaq	3(%rsp), %r15
	shrq	$2, %r13
	shrq	$2, %r15
	testl	%ebx, %ebx
	leaq	0(,%r13,4), %rdx
	leaq	0(,%r15,4), %r12
	jle	.L3
	leaq	4(%rdx), %rax
	andl	$15, %eax
	shrq	$2, %rax
	negq	%rax
	andl	$3, %eax
	cmpl	%ebx, %eax
	cmova	%ebx, %eax
	cmpl	$6, %ebx
	cmovbe	%ebx, %eax
	testl	%eax, %eax
	je	.L25
	cmpl	$1, %eax
	movl	$1, 4(,%r13,4)
	movl	$1, 4(,%r15,4)
	je	.L26
	cmpl	$2, %eax
	movl	$2, 8(,%r13,4)
	movl	$2, 8(,%r15,4)
	je	.L27
	cmpl	$3, %eax
	movl	$3, 12(,%r13,4)
	movl	$3, 12(,%r15,4)
	je	.L28
	cmpl	$4, %eax
	movl	$4, 16(,%r13,4)
	movl	$4, 16(,%r15,4)
	je	.L29
	cmpl	$6, %eax
	movl	$5, 20(,%r13,4)
	movl	$5, 20(,%r15,4)
	jne	.L30
	movl	$6, 24(,%r13,4)
	movl	$6, 24(,%r15,4)
	movl	$7, %ecx
.L6:
	cmpl	%eax, %ebx
	je	.L49
.L5:
	movl	%ebx, %r9d
	leal	-1(%rbx), %r14d
	movl	%eax, %edi
	subl	%eax, %r9d
	leal	-4(%r9), %esi
	movl	%r14d, %r11d
	subl	%eax, %r11d
	shrl	$2, %esi
	addl	$1, %esi
	cmpl	$2, %r11d
	leal	0(,%rsi,4), %r10d
	jbe	.L8
	movl	%ecx, -104(%rbp)
	leaq	4(,%rdi,4), %r8
	xorl	%eax, %eax
	movd	-104(%rbp), %xmm3
	xorl	%edi, %edi
	movdqa	.LC2(%rip), %xmm1
	leaq	(%rdx,%r8), %r11
	addq	%r12, %r8
	pshufd	$0, %xmm3, %xmm0
	paddd	.LC1(%rip), %xmm0
.L9:
	movdqa	%xmm0, %xmm2
	addl	$1, %edi
	movaps	%xmm0, (%r11,%rax)
	paddd	%xmm1, %xmm2
	movups	%xmm0, (%r8,%rax)
	addq	$16, %rax
	cmpl	%esi, %edi
	jnb	.L50
	movdqa	%xmm2, %xmm0
	jmp	.L9
.L50:
	addl	%r10d, %ecx
	cmpl	%r10d, %r9d
	je	.L11
.L8:
	movslq	%ecx, %rax
	movl	%ecx, (%rdx,%rax,4)
	movl	%ecx, (%r12,%rax,4)
	leal	1(%rcx), %eax
	cmpl	%eax, %ebx
	jl	.L11
	movslq	%eax, %rsi
	movl	%eax, (%rdx,%rsi,4)
	movl	%eax, (%r12,%rsi,4)
	leal	2(%rcx), %eax
	cmpl	%eax, %ebx
	jl	.L11
	movslq	%eax, %rcx
	movl	%eax, (%rdx,%rcx,4)
	movl	%eax, (%r12,%rcx,4)
.L11:
	leaq	-96(%rbp), %rsi
	xorl	%edi, %edi
	movq	%rdx, -104(%rbp)
	call	clock_gettime
	leaq	4(%r12), %rcx
	movq	-104(%rbp), %rdx
	movq	%rcx, %rax
	andl	$15, %eax
	shrq	$2, %rax
	negq	%rax
	andl	$3, %eax
	cmpl	%ebx, %eax
	cmova	%ebx, %eax
	cmpl	$4, %ebx
	cmovbe	%ebx, %eax
.L17:
	testl	%eax, %eax
	je	.L51
.L23:
	imull	$47, 4(,%r13,4), %esi
	addl	%esi, (%rcx)
	cmpl	$1, %eax
	je	.L33
	imull	$47, 8(,%r13,4), %ecx
	addl	%ecx, 8(%r12)
	cmpl	$2, %eax
	je	.L34
	imull	$47, 12(,%r13,4), %ecx
	addl	%ecx, 12(%r12)
	cmpl	$4, %eax
	jne	.L35
	imull	$47, 16(,%r13,4), %ecx
	addl	%ecx, 16(%r12)
	movl	$5, %ecx
.L19:
	cmpl	%eax, %ebx
	je	.L22
.L18:
	movl	%ebx, %r8d
	movl	%eax, %edi
	subl	%eax, %r8d
	leal	-4(%r8), %esi
	shrl	$2, %esi
	leal	1(%rsi), %r9d
	movl	%r14d, %esi
	subl	%eax, %esi
	cmpl	$2, %esi
	leal	0(,%r9,4), %r10d
	jbe	.L21
	leaq	4(,%rdi,4), %rsi
	xorl	%eax, %eax
	xorl	%edi, %edi
	leaq	(%rdx,%rsi), %r11
	addq	%r12, %rsi
.L13:
	movdqu	(%r11,%rax), %xmm1
	addl	$1, %edi
	movdqa	%xmm1, %xmm2
	pslld	$4, %xmm2
	movdqa	%xmm2, %xmm0
	pslld	$2, %xmm0
	psubd	%xmm2, %xmm0
	psubd	%xmm1, %xmm0
	paddd	(%rsi,%rax), %xmm0
	movaps	%xmm0, (%rsi,%rax)
	addq	$16, %rax
	cmpl	%r9d, %edi
	jb	.L13
	addl	%r10d, %ecx
	cmpl	%r10d, %r8d
	je	.L22
.L21:
	movslq	%ecx, %rax
	imull	$47, (%rdx,%rax,4), %esi
	addl	%esi, (%r12,%rax,4)
	leal	1(%rcx), %eax
	cmpl	%eax, %ebx
	jl	.L22
	cltq
	addl	$2, %ecx
	imull	$47, (%rdx,%rax,4), %esi
	addl	%esi, (%r12,%rax,4)
	cmpl	%ebx, %ecx
	jg	.L22
	movslq	%ecx, %rcx
	imull	$47, (%rdx,%rcx,4), %eax
	addl	%eax, (%r12,%rcx,4)
.L22:
	leaq	-80(%rbp), %rsi
	xorl	%edi, %edi
	movslq	%r14d, %r14
	call	clock_gettime
	movq	-72(%rbp), %rax
	pxor	%xmm0, %xmm0
	subq	-88(%rbp), %rax
	pxor	%xmm1, %xmm1
	movl	0(,%r15,4), %edx
	movl	(%r12,%r14,4), %ecx
	movl	$.LC4, %esi
	movl	$1, %edi
	cvtsi2sdq	%rax, %xmm0
	movq	-80(%rbp), %rax
	subq	-96(%rbp), %rax
	cvtsi2sdq	%rax, %xmm1
	movl	$1, %eax
	divsd	.LC3(%rip), %xmm0
	addsd	%xmm1, %xmm0
	call	__printf_chk
	xorl	%eax, %eax
	movq	-56(%rbp), %rdx
	xorq	%fs:40, %rdx
	jne	.L52
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L51:
	.cfi_restore_state
	movl	$1, %ecx
	jmp	.L18
.L49:
	leaq	-96(%rbp), %rsi
	xorl	%edi, %edi
	movq	%rdx, -104(%rbp)
	leal	-1(%rbx), %r14d
	call	clock_gettime
	leaq	4(%r12), %rcx
	movq	-104(%rbp), %rdx
	movq	%rcx, %rax
	andl	$15, %eax
	shrq	$2, %rax
	negq	%rax
	andl	$3, %eax
	cmpl	%ebx, %eax
	cmova	%ebx, %eax
	cmpl	$4, %ebx
	ja	.L17
	movl	%ebx, %eax
	leal	-1(%rbx), %r14d
	jmp	.L23
.L25:
	movl	$1, %ecx
	jmp	.L5
.L34:
	movl	$3, %ecx
	jmp	.L19
.L35:
	movl	$4, %ecx
	jmp	.L19
.L33:
	movl	$2, %ecx
	jmp	.L19
.L29:
	movl	$5, %ecx
	jmp	.L6
.L30:
	movl	$6, %ecx
	jmp	.L6
.L26:
	movl	$2, %ecx
	jmp	.L6
.L27:
	movl	$3, %ecx
	jmp	.L6
.L28:
	movl	$4, %ecx
	jmp	.L6
.L3:
	leaq	-96(%rbp), %rsi
	xorl	%edi, %edi
	leal	-1(%rbx), %r14d
	call	clock_gettime
	jmp	.L22
.L52:
	call	__stack_chk_fail
.L48:
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
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC1:
	.long	0
	.long	1
	.long	2
	.long	3
	.align 16
.LC2:
	.long	4
	.long	4
	.long	4
	.long	4
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC3:
	.long	0
	.long	1104006501
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
