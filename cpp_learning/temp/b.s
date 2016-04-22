	.text
	.file	"b.cc"
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	push	rbp
.Ltmp0:
	.cfi_def_cfa_offset 16
.Ltmp1:
	.cfi_offset rbp, -16
	mov	rbp, rsp
.Ltmp2:
	.cfi_def_cfa_register rbp
	sub	rsp, 288
	lea	rsi, [rbp - 224]
	lea	rdi, [rbp - 48]
	call	_Z4fobjIPiET_S1_S1_
	lea	rdi, [rbp - 48]
	lea	rsi, [rbp - 272]
	mov	qword ptr [rbp - 280], rax # 8-byte Spill
	call	_Z5fref2IA10_iERT_RKS1_S4_
	xor	ecx, ecx
	mov	qword ptr [rbp - 288], rax # 8-byte Spill
	mov	eax, ecx
	add	rsp, 288
	pop	rbp
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc

	.section	.text._Z4fobjIPiET_S1_S1_,"axG",@progbits,_Z4fobjIPiET_S1_S1_,comdat
	.weak	_Z4fobjIPiET_S1_S1_
	.align	16, 0x90
	.type	_Z4fobjIPiET_S1_S1_,@function
_Z4fobjIPiET_S1_S1_:                    # @_Z4fobjIPiET_S1_S1_
	.cfi_startproc
# BB#0:
	push	rbp
.Ltmp3:
	.cfi_def_cfa_offset 16
.Ltmp4:
	.cfi_offset rbp, -16
	mov	rbp, rsp
.Ltmp5:
	.cfi_def_cfa_register rbp
	mov	qword ptr [rbp - 16], rdi
	mov	qword ptr [rbp - 24], rsi
	ud2
.Lfunc_end1:
	.size	_Z4fobjIPiET_S1_S1_, .Lfunc_end1-_Z4fobjIPiET_S1_S1_
	.cfi_endproc

	.section	.text._Z5fref2IA10_iERT_RKS1_S4_,"axG",@progbits,_Z5fref2IA10_iERT_RKS1_S4_,comdat
	.weak	_Z5fref2IA10_iERT_RKS1_S4_
	.align	16, 0x90
	.type	_Z5fref2IA10_iERT_RKS1_S4_,@function
_Z5fref2IA10_iERT_RKS1_S4_:             # @_Z5fref2IA10_iERT_RKS1_S4_
	.cfi_startproc
# BB#0:
	push	rbp
.Ltmp6:
	.cfi_def_cfa_offset 16
.Ltmp7:
	.cfi_offset rbp, -16
	mov	rbp, rsp
.Ltmp8:
	.cfi_def_cfa_register rbp
	mov	qword ptr [rbp - 16], rdi
	mov	qword ptr [rbp - 24], rsi
	ud2
.Lfunc_end2:
	.size	_Z5fref2IA10_iERT_RKS1_S4_, .Lfunc_end2-_Z5fref2IA10_iERT_RKS1_S4_
	.cfi_endproc


	.ident	"clang version 3.7.1 (tags/RELEASE_371/final)"
	.section	".note.GNU-stack","",@progbits
