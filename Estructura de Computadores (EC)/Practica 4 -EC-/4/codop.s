# codop.s

.text
_start: .globl _start

	inc %eax
	int $0x80
	jmp .
	leave
	nop
	ret
	xor $0, %ebx
	xor $1, %eax
	xor %eax, %eax
