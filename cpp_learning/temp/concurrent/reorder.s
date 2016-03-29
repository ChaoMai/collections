	.text
	.file	"reorder.cc"
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	mov	eax, dword ptr [rip + B]
	inc	eax
	mov	dword ptr [rip + A], eax
	mov	dword ptr [rip + B], 1
	xor	eax, eax
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc

	.type	A,@object               # @A
	.bss
	.globl	A
	.align	4
A:
	.long	0                       # 0x0
	.size	A, 4

	.type	B,@object               # @B
	.globl	B
	.align	4
B:
	.long	0                       # 0x0
	.size	B, 4


	.ident	"clang version 3.7.1 (tags/RELEASE_371/final)"
	.section	".note.GNU-stack","",@progbits
