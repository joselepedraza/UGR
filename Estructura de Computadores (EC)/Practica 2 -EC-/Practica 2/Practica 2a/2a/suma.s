suma:
	mov $0, %ebp				# poner los acomuladores a 0
	mov $0, %edi
	mov $0, %esi 				# poner a 0 índice
bucle:
	mov (%ebx,%esi,4), %eax			# mover i-ésimo elemento por la extension de signo se hace en eax
	cltd					# extendemos el signo
	add %eax, %edi
	adc %edx, %ebp
	inc %esi
	cmp %esi,%ecx
	jne bucle
	mov %ebp, %edx
	mov %edi, %eax
	ret
