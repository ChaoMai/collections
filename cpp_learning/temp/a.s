	.text
	.file	"a.cc"
	.section	.text.startup,"ax",@progbits
	.align	16, 0x90
	.type	__cxx_global_var_init,@function
__cxx_global_var_init:                  # @__cxx_global_var_init
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
	sub	rsp, 16
	movabs	rdi, _ZStL8__ioinit
	call	_ZNSt8ios_base4InitC1Ev
	movabs	rdi, _ZNSt8ios_base4InitD1Ev
	movabs	rsi, _ZStL8__ioinit
	movabs	rdx, __dso_handle
	call	__cxa_atexit
	mov	dword ptr [rbp - 4], eax # 4-byte Spill
	add	rsp, 16
	pop	rbp
	ret
.Lfunc_end0:
	.size	__cxx_global_var_init, .Lfunc_end0-__cxx_global_var_init
	.cfi_endproc

	.text
	.globl	_Z3pf21FIiE
	.align	16, 0x90
	.type	_Z3pf21FIiE,@function
_Z3pf21FIiE:                            # @_Z3pf21FIiE
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
	sub	rsp, 16
	movabs	rax, _ZSt4cout
	mov	dword ptr [rbp - 8], edi
	mov	esi, dword ptr [rbp - 8]
	mov	rdi, rax
	call	_ZNSolsEi
	movabs	rsi, _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	mov	rdi, rax
	call	_ZNSolsEPFRSoS_E
	mov	qword ptr [rbp - 16], rax # 8-byte Spill
	add	rsp, 16
	pop	rbp
	ret
.Lfunc_end1:
	.size	_Z3pf21FIiE, .Lfunc_end1-_Z3pf21FIiE
	.cfi_endproc

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
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
	sub	rsp, 48
	lea	rdi, [rbp - 8]
	call	_ZN1FIiEC2Ev
	mov	eax, dword ptr [rbp - 8]
	mov	dword ptr [rbp - 16], eax
	mov	edi, dword ptr [rbp - 16]
	call	_Z3pf11FIiE
	mov	eax, dword ptr [rbp - 8]
	mov	dword ptr [rbp - 24], eax
	mov	edi, dword ptr [rbp - 24]
	call	_Z3pf21FIiE
	mov	eax, dword ptr [rbp - 8]
	mov	dword ptr [rbp - 32], eax
	mov	edi, dword ptr [rbp - 32]
	call	_Z3pf3IiEv1FIT_E
	mov	eax, dword ptr [rbp - 8]
	mov	dword ptr [rbp - 40], eax
	mov	edi, dword ptr [rbp - 40]
	call	_Z3pf3IiEv1FIT_E
	xor	eax, eax
	add	rsp, 48
	pop	rbp
	ret
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.cfi_endproc

	.section	.text._ZN1FIiEC2Ev,"axG",@progbits,_ZN1FIiEC2Ev,comdat
	.weak	_ZN1FIiEC2Ev
	.align	16, 0x90
	.type	_ZN1FIiEC2Ev,@function
_ZN1FIiEC2Ev:                           # @_ZN1FIiEC2Ev
	.cfi_startproc
# BB#0:
	push	rbp
.Ltmp9:
	.cfi_def_cfa_offset 16
.Ltmp10:
	.cfi_offset rbp, -16
	mov	rbp, rsp
.Ltmp11:
	.cfi_def_cfa_register rbp
	mov	qword ptr [rbp - 8], rdi
	mov	rdi, qword ptr [rbp - 8]
	mov	dword ptr [rdi], 100
	pop	rbp
	ret
.Lfunc_end3:
	.size	_ZN1FIiEC2Ev, .Lfunc_end3-_ZN1FIiEC2Ev
	.cfi_endproc

	.section	.text._Z3pf3IiEv1FIT_E,"axG",@progbits,_Z3pf3IiEv1FIT_E,comdat
	.weak	_Z3pf3IiEv1FIT_E
	.align	16, 0x90
	.type	_Z3pf3IiEv1FIT_E,@function
_Z3pf3IiEv1FIT_E:                       # @_Z3pf3IiEv1FIT_E
	.cfi_startproc
# BB#0:
	push	rbp
.Ltmp12:
	.cfi_def_cfa_offset 16
.Ltmp13:
	.cfi_offset rbp, -16
	mov	rbp, rsp
.Ltmp14:
	.cfi_def_cfa_register rbp
	sub	rsp, 16
	movabs	rax, _ZSt4cout
	mov	dword ptr [rbp - 8], edi
	mov	esi, dword ptr [rbp - 8]
	mov	rdi, rax
	call	_ZNSolsEi
	movabs	rsi, _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	mov	rdi, rax
	call	_ZNSolsEPFRSoS_E
	mov	qword ptr [rbp - 16], rax # 8-byte Spill
	add	rsp, 16
	pop	rbp
	ret
.Lfunc_end4:
	.size	_Z3pf3IiEv1FIT_E, .Lfunc_end4-_Z3pf3IiEv1FIT_E
	.cfi_endproc

	.section	.text.startup,"ax",@progbits
	.align	16, 0x90
	.type	_GLOBAL__sub_I_a.cc,@function
_GLOBAL__sub_I_a.cc:                    # @_GLOBAL__sub_I_a.cc
	.cfi_startproc
# BB#0:
	push	rbp
.Ltmp15:
	.cfi_def_cfa_offset 16
.Ltmp16:
	.cfi_offset rbp, -16
	mov	rbp, rsp
.Ltmp17:
	.cfi_def_cfa_register rbp
	call	__cxx_global_var_init
	pop	rbp
	ret
.Lfunc_end5:
	.size	_GLOBAL__sub_I_a.cc, .Lfunc_end5-_GLOBAL__sub_I_a.cc
	.cfi_endproc

	.type	_ZStL8__ioinit,@object  # @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.init_array,"aw",@init_array
	.align	8
	.quad	_GLOBAL__sub_I_a.cc

	.ident	"clang version 3.7.1 (tags/RELEASE_371/final)"
	.section	".note.GNU-stack","",@progbits
