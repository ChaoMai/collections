	.text
	.file	"acquire_release2.cc"
	.globl	_Z2f1v
	.align	16, 0x90
	.type	_Z2f1v,@function
_Z2f1v:                                 # @_Z2f1v
	.cfi_startproc
# BB#0:
	xor	eax, eax
	.align	16, 0x90
.LBB0_1:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_3 Depth 2
	mov	ecx, dword ptr [rip + flag]
	test	ecx, ecx
	jne	.LBB0_1
# BB#2:                                 # %.outer
                                        #   in Loop: Header=BB0_1 Depth=1
	mov	ecx, 1
	xchg	dword ptr [rip + flag], ecx
	inc	dword ptr [rip + sharedValue]
	xor	ecx, ecx
	xchg	dword ptr [rip + flag], ecx
	.align	16, 0x90
.LBB0_3:                                #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	mov	ecx, dword ptr [rip + flag]
	test	ecx, ecx
	jne	.LBB0_3
# BB#4:                                 # %.outer.1
                                        #   in Loop: Header=BB0_1 Depth=1
	mov	ecx, 1
	xchg	dword ptr [rip + flag], ecx
	inc	dword ptr [rip + sharedValue]
	xor	ecx, ecx
	xchg	dword ptr [rip + flag], ecx
	add	eax, 2
	cmp	eax, 10000000
	jl	.LBB0_1
# BB#5:                                 # %.split
	ret
.Lfunc_end0:
	.size	_Z2f1v, .Lfunc_end0-_Z2f1v
	.cfi_endproc

	.globl	_Z2f2v
	.align	16, 0x90
	.type	_Z2f2v,@function
_Z2f2v:                                 # @_Z2f2v
	.cfi_startproc
# BB#0:
	xor	edx, edx
	mov	ecx, dword ptr [rip + sharedValue]
	mov	esi, 1
	.align	16, 0x90
.LBB1_1:                                # %_ZNSt13__atomic_baseIiE23compare_exchange_strongERiiSt12memory_order.exit
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_3 Depth 2
	xor	eax, eax
	lock
	cmpxchg	dword ptr [rip + flag], esi
	jne	.LBB1_1
# BB#2:                                 # %.outer
                                        #   in Loop: Header=BB1_1 Depth=1
	mov	dword ptr [rip + flag], 0
	.align	16, 0x90
.LBB1_3:                                # %_ZNSt13__atomic_baseIiE23compare_exchange_strongERiiSt12memory_order.exit.1
                                        #   Parent Loop BB1_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	xor	eax, eax
	lock
	cmpxchg	dword ptr [rip + flag], esi
	jne	.LBB1_3
# BB#4:                                 # %.outer.1
                                        #   in Loop: Header=BB1_1 Depth=1
	add	ecx, 2
	mov	dword ptr [rip + flag], 0
	add	edx, 2
	cmp	edx, 10000000
	jl	.LBB1_1
# BB#5:                                 # %.split
	mov	dword ptr [rip + sharedValue], ecx
	ret
.Lfunc_end1:
	.size	_Z2f2v, .Lfunc_end1-_Z2f2v
	.cfi_endproc

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
.Lfunc_begin0:
	.cfi_startproc
	.cfi_personality 3, __gxx_personality_v0
	.cfi_lsda 3, .Lexception0
# BB#0:
	push	rbp
.Ltmp16:
	.cfi_def_cfa_offset 16
	push	r15
.Ltmp17:
	.cfi_def_cfa_offset 24
	push	r14
.Ltmp18:
	.cfi_def_cfa_offset 32
	push	r12
.Ltmp19:
	.cfi_def_cfa_offset 40
	push	rbx
.Ltmp20:
	.cfi_def_cfa_offset 48
	sub	rsp, 16
.Ltmp21:
	.cfi_def_cfa_offset 64
.Ltmp22:
	.cfi_offset rbx, -48
.Ltmp23:
	.cfi_offset r12, -40
.Ltmp24:
	.cfi_offset r14, -32
.Ltmp25:
	.cfi_offset r15, -24
.Ltmp26:
	.cfi_offset rbp, -16
	xor	r12d, r12d
	lea	r14, [rsp + 8]
	mov	ebp, 1
	.align	16, 0x90
.LBB2_1:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB2_2 Depth 2
                                        #       Child Loop BB2_4 Depth 3
                                        #       Child Loop BB2_6 Depth 3
                                        #       Child Loop BB2_8 Depth 3
	mov	esi, _Z2f2v
	mov	rdi, r14
	call	_ZNSt6threadC2IRFvvEJEEEOT_DpOT0_
	mov	ecx, dword ptr [rip + sharedValue]
	xor	edx, edx
	.align	16, 0x90
.LBB2_2:                                # %_ZNSt13__atomic_baseIiE23compare_exchange_strongERiiSt12memory_order.exit.i
                                        #   Parent Loop BB2_1 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB2_4 Depth 3
                                        #       Child Loop BB2_6 Depth 3
                                        #       Child Loop BB2_8 Depth 3
	xor	eax, eax
	lock
	cmpxchg	dword ptr [rip + flag], ebp
	jne	.LBB2_2
# BB#3:                                 # %.outer.i
                                        #   in Loop: Header=BB2_2 Depth=2
	mov	dword ptr [rip + flag], 0
	.align	16, 0x90
.LBB2_4:                                # %_ZNSt13__atomic_baseIiE23compare_exchange_strongERiiSt12memory_order.exit.i.1
                                        #   Parent Loop BB2_1 Depth=1
                                        #     Parent Loop BB2_2 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	xor	eax, eax
	lock
	cmpxchg	dword ptr [rip + flag], ebp
	jne	.LBB2_4
# BB#5:                                 # %.outer.i.1
                                        #   in Loop: Header=BB2_2 Depth=2
	mov	dword ptr [rip + flag], 0
	.align	16, 0x90
.LBB2_6:                                # %_ZNSt13__atomic_baseIiE23compare_exchange_strongERiiSt12memory_order.exit.i.2
                                        #   Parent Loop BB2_1 Depth=1
                                        #     Parent Loop BB2_2 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	xor	eax, eax
	lock
	cmpxchg	dword ptr [rip + flag], ebp
	jne	.LBB2_6
# BB#7:                                 # %.outer.i.2
                                        #   in Loop: Header=BB2_2 Depth=2
	mov	dword ptr [rip + flag], 0
	.align	16, 0x90
.LBB2_8:                                # %_ZNSt13__atomic_baseIiE23compare_exchange_strongERiiSt12memory_order.exit.i.3
                                        #   Parent Loop BB2_1 Depth=1
                                        #     Parent Loop BB2_2 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	xor	eax, eax
	lock
	cmpxchg	dword ptr [rip + flag], ebp
	jne	.LBB2_8
# BB#9:                                 # %.outer.i.3
                                        #   in Loop: Header=BB2_2 Depth=2
	mov	dword ptr [rip + flag], 0
	add	edx, 4
	cmp	edx, 10000000
	jne	.LBB2_2
# BB#10:                                # %_Z2f2v.exit
                                        #   in Loop: Header=BB2_1 Depth=1
	add	ecx, 10000000
	mov	dword ptr [rip + sharedValue], ecx
.Ltmp0:
	mov	rdi, r14
	call	_ZNSt6thread4joinEv
.Ltmp1:
# BB#11:                                #   in Loop: Header=BB2_1 Depth=1
	mov	esi, dword ptr [rip + sharedValue]
.Ltmp2:
	mov	edi, _ZSt4cout
	call	_ZNSolsEi
	mov	r15, rax
.Ltmp3:
# BB#12:                                #   in Loop: Header=BB2_1 Depth=1
	mov	rax, qword ptr [r15]
	mov	rax, qword ptr [rax - 24]
	mov	rbx, qword ptr [r15 + rax + 240]
	test	rbx, rbx
	je	.LBB2_13
.LBB2_14:                               # %.noexc5
                                        #   in Loop: Header=BB2_1 Depth=1
	cmp	byte ptr [rbx + 56], 0
	je	.LBB2_16
# BB#15:                                #   in Loop: Header=BB2_1 Depth=1
	mov	al, byte ptr [rbx + 67]
	jmp	.LBB2_18
	.align	16, 0x90
.LBB2_16:                               #   in Loop: Header=BB2_1 Depth=1
.Ltmp4:
	mov	rdi, rbx
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
.Ltmp5:
# BB#17:                                # %.noexc7
                                        #   in Loop: Header=BB2_1 Depth=1
	mov	rax, qword ptr [rbx]
	mov	rax, qword ptr [rax + 48]
.Ltmp6:
	mov	esi, 10
	mov	rdi, rbx
	call	rax
.Ltmp7:
.LBB2_18:                               # %.noexc
                                        #   in Loop: Header=BB2_1 Depth=1
.Ltmp8:
	movsx	esi, al
	mov	rdi, r15
	call	_ZNSo3putEc
.Ltmp9:
# BB#19:                                # %.noexc1
                                        #   in Loop: Header=BB2_1 Depth=1
.Ltmp10:
	mov	rdi, rax
	call	_ZNSo5flushEv
.Ltmp11:
# BB#20:                                # %_ZNSolsEPFRSoS_E.exit
                                        #   in Loop: Header=BB2_1 Depth=1
	mov	dword ptr [rip + sharedValue], 0
	cmp	qword ptr [rsp + 8], 0
	jne	.LBB2_27
# BB#21:                                # %_ZNSt6threadD2Ev.exit4
                                        #   in Loop: Header=BB2_1 Depth=1
	inc	r12d
	cmp	r12d, 10000
	jl	.LBB2_1
	jmp	.LBB2_22
.LBB2_13:                               #   in Loop: Header=BB2_1 Depth=1
.Ltmp13:
	call	_ZSt16__throw_bad_castv
.Ltmp14:
	jmp	.LBB2_14
.LBB2_24:                               # %.loopexit.split-lp
.Ltmp15:
	jmp	.LBB2_25
.LBB2_22:
	xor	eax, eax
	add	rsp, 16
	pop	rbx
	pop	r12
	pop	r14
	pop	r15
	pop	rbp
	ret
.LBB2_23:                               # %.loopexit
.Ltmp12:
.LBB2_25:
	cmp	qword ptr [rsp + 8], 0
	jne	.LBB2_27
# BB#26:                                # %_ZNSt6threadD2Ev.exit
	mov	rdi, rax
	call	_Unwind_Resume
.LBB2_27:
	call	_ZSt9terminatev
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.cfi_endproc
	.section	.gcc_except_table,"a",@progbits
	.align	4
GCC_except_table2:
.Lexception0:
	.byte	255                     # @LPStart Encoding = omit
	.byte	3                       # @TType Encoding = udata4
	.asciz	"\266\200\200"          # @TType base offset
	.byte	3                       # Call site Encoding = udata4
	.byte	52                      # Call site table length
	.long	.Lfunc_begin0-.Lfunc_begin0 # >> Call Site 1 <<
	.long	.Ltmp0-.Lfunc_begin0    #   Call between .Lfunc_begin0 and .Ltmp0
	.long	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.long	.Ltmp0-.Lfunc_begin0    # >> Call Site 2 <<
	.long	.Ltmp11-.Ltmp0          #   Call between .Ltmp0 and .Ltmp11
	.long	.Ltmp12-.Lfunc_begin0   #     jumps to .Ltmp12
	.byte	0                       #   On action: cleanup
	.long	.Ltmp13-.Lfunc_begin0   # >> Call Site 3 <<
	.long	.Ltmp14-.Ltmp13         #   Call between .Ltmp13 and .Ltmp14
	.long	.Ltmp15-.Lfunc_begin0   #     jumps to .Ltmp15
	.byte	0                       #   On action: cleanup
	.long	.Ltmp14-.Lfunc_begin0   # >> Call Site 4 <<
	.long	.Lfunc_end2-.Ltmp14     #   Call between .Ltmp14 and .Lfunc_end2
	.long	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.align	4

	.section	.text._ZNSt6threadC2IRFvvEJEEEOT_DpOT0_,"axG",@progbits,_ZNSt6threadC2IRFvvEJEEEOT_DpOT0_,comdat
	.weak	_ZNSt6threadC2IRFvvEJEEEOT_DpOT0_
	.align	16, 0x90
	.type	_ZNSt6threadC2IRFvvEJEEEOT_DpOT0_,@function
_ZNSt6threadC2IRFvvEJEEEOT_DpOT0_:      # @_ZNSt6threadC2IRFvvEJEEEOT_DpOT0_
.Lfunc_begin1:
	.cfi_startproc
	.cfi_personality 3, __gxx_personality_v0
	.cfi_lsda 3, .Lexception1
# BB#0:
	push	r14
.Ltmp30:
	.cfi_def_cfa_offset 16
	push	rbx
.Ltmp31:
	.cfi_def_cfa_offset 24
	sub	rsp, 24
.Ltmp32:
	.cfi_def_cfa_offset 48
.Ltmp33:
	.cfi_offset rbx, -24
.Ltmp34:
	.cfi_offset r14, -16
	mov	r14, rsi
	mov	rbx, rdi
	mov	qword ptr [rbx], 0
	mov	edi, 48
	call	_Znwm
	mov	dword ptr [rax + 8], 1
	mov	dword ptr [rax + 12], 1
	mov	qword ptr [rax], _ZTVSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE+16
	lea	rcx, [rax + 16]
	xorps	xmm0, xmm0
	movups	xmmword ptr [rax + 24], xmm0
	mov	qword ptr [rax + 16], _ZTVNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE+16
	mov	qword ptr [rax + 40], r14
	test	rax, rax
	cmove	rcx, rax
	mov	qword ptr [rsp + 8], rcx
	mov	qword ptr [rsp + 16], rax
.Ltmp27:
	lea	rsi, [rsp + 8]
	mov	edx, pthread_create
	mov	rdi, rbx
	call	_ZNSt6thread15_M_start_threadESt10shared_ptrINS_10_Impl_baseEEPFvvE
.Ltmp28:
# BB#1:
	mov	rbx, qword ptr [rsp + 16]
	test	rbx, rbx
	je	.LBB3_11
# BB#2:
	lea	rax, [rbx + 8]
	mov	ecx, __pthread_key_create
	test	rcx, rcx
	je	.LBB3_4
# BB#3:
	mov	ecx, -1
	lock
	xadd	dword ptr [rax], ecx
	jmp	.LBB3_5
.LBB3_4:
	mov	ecx, dword ptr [rax]
	lea	edx, [rcx - 1]
	mov	dword ptr [rax], edx
.LBB3_5:                                # %_ZN9__gnu_cxxL27__exchange_and_add_dispatchEPii.exit.i.i.i.6
	cmp	ecx, 1
	jne	.LBB3_11
# BB#6:
	mov	rax, qword ptr [rbx]
	mov	rdi, rbx
	call	qword ptr [rax + 16]
	lea	rax, [rbx + 12]
	mov	ecx, __pthread_key_create
	test	rcx, rcx
	je	.LBB3_8
# BB#7:
	mov	ecx, -1
	lock
	xadd	dword ptr [rax], ecx
	jmp	.LBB3_9
.LBB3_8:
	mov	ecx, dword ptr [rax]
	lea	edx, [rcx - 1]
	mov	dword ptr [rax], edx
.LBB3_9:                                # %_ZN9__gnu_cxxL27__exchange_and_add_dispatchEPii.exit2.i.i.i.8
	cmp	ecx, 1
	jne	.LBB3_11
# BB#10:
	mov	rax, qword ptr [rbx]
	mov	rdi, rbx
	call	qword ptr [rax + 24]
.LBB3_11:                               # %_ZNSt12__shared_ptrINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEELN9__gnu_cxx12_Lock_policyE2EED2Ev.exit14
	add	rsp, 24
	pop	rbx
	pop	r14
	ret
.LBB3_12:
.Ltmp29:
	mov	r14, rax
	mov	rbx, qword ptr [rsp + 16]
	test	rbx, rbx
	je	.LBB3_22
# BB#13:
	lea	rax, [rbx + 8]
	mov	ecx, __pthread_key_create
	test	rcx, rcx
	je	.LBB3_15
# BB#14:
	mov	ecx, -1
	lock
	xadd	dword ptr [rax], ecx
	jmp	.LBB3_16
.LBB3_15:
	mov	ecx, dword ptr [rax]
	lea	edx, [rcx - 1]
	mov	dword ptr [rax], edx
.LBB3_16:                               # %_ZN9__gnu_cxxL27__exchange_and_add_dispatchEPii.exit.i.i.i.2
	cmp	ecx, 1
	jne	.LBB3_22
# BB#17:
	mov	rax, qword ptr [rbx]
	mov	rdi, rbx
	call	qword ptr [rax + 16]
	lea	rax, [rbx + 12]
	mov	ecx, __pthread_key_create
	test	rcx, rcx
	je	.LBB3_19
# BB#18:
	mov	ecx, -1
	lock
	xadd	dword ptr [rax], ecx
	jmp	.LBB3_20
.LBB3_19:
	mov	ecx, dword ptr [rax]
	lea	edx, [rcx - 1]
	mov	dword ptr [rax], edx
.LBB3_20:                               # %_ZN9__gnu_cxxL27__exchange_and_add_dispatchEPii.exit2.i.i.i.4
	cmp	ecx, 1
	jne	.LBB3_22
# BB#21:
	mov	rax, qword ptr [rbx]
	mov	rdi, rbx
	call	qword ptr [rax + 24]
.LBB3_22:                               # %_ZNSt12__shared_ptrINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEELN9__gnu_cxx12_Lock_policyE2EED2Ev.exit
	mov	rdi, r14
	call	_Unwind_Resume
.Lfunc_end3:
	.size	_ZNSt6threadC2IRFvvEJEEEOT_DpOT0_, .Lfunc_end3-_ZNSt6threadC2IRFvvEJEEEOT_DpOT0_
	.cfi_endproc
	.section	.gcc_except_table,"a",@progbits
	.align	4
GCC_except_table3:
.Lexception1:
	.byte	255                     # @LPStart Encoding = omit
	.byte	3                       # @TType Encoding = udata4
	.byte	41                      # @TType base offset
	.byte	3                       # Call site Encoding = udata4
	.byte	39                      # Call site table length
	.long	.Lfunc_begin1-.Lfunc_begin1 # >> Call Site 1 <<
	.long	.Ltmp27-.Lfunc_begin1   #   Call between .Lfunc_begin1 and .Ltmp27
	.long	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.long	.Ltmp27-.Lfunc_begin1   # >> Call Site 2 <<
	.long	.Ltmp28-.Ltmp27         #   Call between .Ltmp27 and .Ltmp28
	.long	.Ltmp29-.Lfunc_begin1   #     jumps to .Ltmp29
	.byte	0                       #   On action: cleanup
	.long	.Ltmp28-.Lfunc_begin1   # >> Call Site 3 <<
	.long	.Lfunc_end3-.Ltmp28     #   Call between .Ltmp28 and .Lfunc_end3
	.long	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.align	4

	.section	.text._ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED2Ev,"axG",@progbits,_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED2Ev,comdat
	.weak	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED2Ev
	.align	16, 0x90
	.type	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED2Ev,@function
_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED2Ev: # @_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED2Ev
	.cfi_startproc
# BB#0:
	ret
.Lfunc_end4:
	.size	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED2Ev, .Lfunc_end4-_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED2Ev
	.cfi_endproc

	.section	.text._ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED0Ev,"axG",@progbits,_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED0Ev,comdat
	.weak	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED0Ev
	.align	16, 0x90
	.type	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED0Ev,@function
_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED0Ev: # @_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED0Ev
	.cfi_startproc
# BB#0:
	jmp	_ZdlPv                  # TAILCALL
.Lfunc_end5:
	.size	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED0Ev, .Lfunc_end5-_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED0Ev
	.cfi_endproc

	.section	.text._ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv,"axG",@progbits,_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv,comdat
	.weak	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv
	.align	16, 0x90
	.type	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv,@function
_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv: # @_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv
	.cfi_startproc
# BB#0:
	mov	rax, qword ptr [rdi + 16]
	add	rdi, 16
	jmp	qword ptr [rax]         # TAILCALL
.Lfunc_end6:
	.size	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv, .Lfunc_end6-_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv
	.cfi_endproc

	.section	.text._ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv,"axG",@progbits,_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv,comdat
	.weak	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv
	.align	16, 0x90
	.type	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv,@function
_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv: # @_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv
	.cfi_startproc
# BB#0:
	test	rdi, rdi
	je	.LBB7_1
# BB#2:
	jmp	_ZdlPv                  # TAILCALL
.LBB7_1:                                # %_ZNSt15__allocated_ptrISaISt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS8_ELN9__gnu_cxx12_Lock_policyE2EEEED2Ev.exit
	ret
.Lfunc_end7:
	.size	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv, .Lfunc_end7-_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv
	.cfi_endproc

	.section	.text._ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info,"axG",@progbits,_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info,comdat
	.weak	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info
	.align	16, 0x90
	.type	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info,@function
_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info: # @_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info
	.cfi_startproc
# BB#0:
	push	rbx
.Ltmp35:
	.cfi_def_cfa_offset 16
.Ltmp36:
	.cfi_offset rbx, -16
	mov	rbx, rdi
	mov	rdi, qword ptr [rsi + 8]
	mov	eax, _ZTSSt19_Sp_make_shared_tag
	cmp	rdi, rax
	je	.LBB8_3
# BB#1:
	movzx	ecx, byte ptr [rdi]
	xor	eax, eax
	cmp	ecx, 42
	je	.LBB8_4
# BB#2:                                 # %_ZNKSt9type_infoeqERKS_.exit
	mov	esi, _ZTSSt19_Sp_make_shared_tag
	call	strcmp
	mov	ecx, eax
	xor	eax, eax
	test	ecx, ecx
	jne	.LBB8_4
.LBB8_3:                                # %_ZNKSt9type_infoeqERKS_.exit.thread
	add	rbx, 16
	mov	rax, rbx
.LBB8_4:                                # %_ZNKSt9type_infoeqERKS_.exit.thread1
	pop	rbx
	ret
.Lfunc_end8:
	.size	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info, .Lfunc_end8-_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info
	.cfi_endproc

	.section	.text._ZNSt6thread10_Impl_baseD2Ev,"axG",@progbits,_ZNSt6thread10_Impl_baseD2Ev,comdat
	.weak	_ZNSt6thread10_Impl_baseD2Ev
	.align	16, 0x90
	.type	_ZNSt6thread10_Impl_baseD2Ev,@function
_ZNSt6thread10_Impl_baseD2Ev:           # @_ZNSt6thread10_Impl_baseD2Ev
	.cfi_startproc
# BB#0:
	push	rbx
.Ltmp37:
	.cfi_def_cfa_offset 16
.Ltmp38:
	.cfi_offset rbx, -16
	mov	qword ptr [rdi], _ZTVNSt6thread10_Impl_baseE+16
	mov	rbx, qword ptr [rdi + 16]
	test	rbx, rbx
	je	.LBB9_9
# BB#1:
	lea	rax, [rbx + 8]
	mov	ecx, __pthread_key_create
	test	rcx, rcx
	je	.LBB9_3
# BB#2:
	mov	ecx, -1
	lock
	xadd	dword ptr [rax], ecx
	jmp	.LBB9_4
.LBB9_3:
	mov	ecx, dword ptr [rax]
	lea	edx, [rcx - 1]
	mov	dword ptr [rax], edx
.LBB9_4:                                # %_ZN9__gnu_cxxL27__exchange_and_add_dispatchEPii.exit.i.i.i
	cmp	ecx, 1
	jne	.LBB9_9
# BB#5:
	mov	rax, qword ptr [rbx]
	mov	rdi, rbx
	call	qword ptr [rax + 16]
	lea	rax, [rbx + 12]
	mov	ecx, __pthread_key_create
	test	rcx, rcx
	je	.LBB9_7
# BB#6:
	mov	ecx, -1
	lock
	xadd	dword ptr [rax], ecx
	jmp	.LBB9_8
.LBB9_7:
	mov	ecx, dword ptr [rax]
	lea	edx, [rcx - 1]
	mov	dword ptr [rax], edx
.LBB9_8:                                # %_ZN9__gnu_cxxL27__exchange_and_add_dispatchEPii.exit2.i.i.i
	cmp	ecx, 1
	jne	.LBB9_9
# BB#10:
	mov	rax, qword ptr [rbx]
	mov	rdi, rbx
	pop	rbx
	jmp	qword ptr [rax + 24]    # TAILCALL
.LBB9_9:                                # %_ZNSt12__shared_ptrINSt6thread10_Impl_baseELN9__gnu_cxx12_Lock_policyE2EED2Ev.exit
	pop	rbx
	ret
.Lfunc_end9:
	.size	_ZNSt6thread10_Impl_baseD2Ev, .Lfunc_end9-_ZNSt6thread10_Impl_baseD2Ev
	.cfi_endproc

	.section	.text._ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEED0Ev,"axG",@progbits,_ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEED0Ev,comdat
	.weak	_ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEED0Ev
	.align	16, 0x90
	.type	_ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEED0Ev,@function
_ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEED0Ev: # @_ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEED0Ev
	.cfi_startproc
# BB#0:
	push	r14
.Ltmp39:
	.cfi_def_cfa_offset 16
	push	rbx
.Ltmp40:
	.cfi_def_cfa_offset 24
	push	rax
.Ltmp41:
	.cfi_def_cfa_offset 32
.Ltmp42:
	.cfi_offset rbx, -24
.Ltmp43:
	.cfi_offset r14, -16
	mov	r14, rdi
	mov	qword ptr [r14], _ZTVNSt6thread10_Impl_baseE+16
	mov	rbx, qword ptr [r14 + 16]
	test	rbx, rbx
	je	.LBB10_10
# BB#1:
	lea	rax, [rbx + 8]
	mov	ecx, __pthread_key_create
	test	rcx, rcx
	je	.LBB10_3
# BB#2:
	mov	ecx, -1
	lock
	xadd	dword ptr [rax], ecx
	jmp	.LBB10_4
.LBB10_3:
	mov	ecx, dword ptr [rax]
	lea	edx, [rcx - 1]
	mov	dword ptr [rax], edx
.LBB10_4:                               # %_ZN9__gnu_cxxL27__exchange_and_add_dispatchEPii.exit.i.i.i.i
	cmp	ecx, 1
	jne	.LBB10_10
# BB#5:
	mov	rax, qword ptr [rbx]
	mov	rdi, rbx
	call	qword ptr [rax + 16]
	lea	rax, [rbx + 12]
	mov	ecx, __pthread_key_create
	test	rcx, rcx
	je	.LBB10_7
# BB#6:
	mov	ecx, -1
	lock
	xadd	dword ptr [rax], ecx
	jmp	.LBB10_8
.LBB10_7:
	mov	ecx, dword ptr [rax]
	lea	edx, [rcx - 1]
	mov	dword ptr [rax], edx
.LBB10_8:                               # %_ZN9__gnu_cxxL27__exchange_and_add_dispatchEPii.exit2.i.i.i.i
	cmp	ecx, 1
	jne	.LBB10_10
# BB#9:
	mov	rax, qword ptr [rbx]
	mov	rdi, rbx
	call	qword ptr [rax + 24]
.LBB10_10:                              # %_ZNSt6thread10_Impl_baseD2Ev.exit
	mov	rdi, r14
	add	rsp, 8
	pop	rbx
	pop	r14
	jmp	_ZdlPv                  # TAILCALL
.Lfunc_end10:
	.size	_ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEED0Ev, .Lfunc_end10-_ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEED0Ev
	.cfi_endproc

	.section	.text._ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEE6_M_runEv,"axG",@progbits,_ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEE6_M_runEv,comdat
	.weak	_ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEE6_M_runEv
	.align	16, 0x90
	.type	_ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEE6_M_runEv,@function
_ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEE6_M_runEv: # @_ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEE6_M_runEv
	.cfi_startproc
# BB#0:
	jmp	qword ptr [rdi + 24]    # TAILCALL
.Lfunc_end11:
	.size	_ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEE6_M_runEv, .Lfunc_end11-_ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEE6_M_runEv
	.cfi_endproc

	.section	.text._ZNSt6thread10_Impl_baseD0Ev,"axG",@progbits,_ZNSt6thread10_Impl_baseD0Ev,comdat
	.weak	_ZNSt6thread10_Impl_baseD0Ev
	.align	16, 0x90
	.type	_ZNSt6thread10_Impl_baseD0Ev,@function
_ZNSt6thread10_Impl_baseD0Ev:           # @_ZNSt6thread10_Impl_baseD0Ev
	.cfi_startproc
# BB#0:
	push	r14
.Ltmp44:
	.cfi_def_cfa_offset 16
	push	rbx
.Ltmp45:
	.cfi_def_cfa_offset 24
	push	rax
.Ltmp46:
	.cfi_def_cfa_offset 32
.Ltmp47:
	.cfi_offset rbx, -24
.Ltmp48:
	.cfi_offset r14, -16
	mov	r14, rdi
	mov	qword ptr [r14], _ZTVNSt6thread10_Impl_baseE+16
	mov	rbx, qword ptr [r14 + 16]
	test	rbx, rbx
	je	.LBB12_10
# BB#1:
	lea	rax, [rbx + 8]
	mov	ecx, __pthread_key_create
	test	rcx, rcx
	je	.LBB12_3
# BB#2:
	mov	ecx, -1
	lock
	xadd	dword ptr [rax], ecx
	jmp	.LBB12_4
.LBB12_3:
	mov	ecx, dword ptr [rax]
	lea	edx, [rcx - 1]
	mov	dword ptr [rax], edx
.LBB12_4:                               # %_ZN9__gnu_cxxL27__exchange_and_add_dispatchEPii.exit.i.i.i.i
	cmp	ecx, 1
	jne	.LBB12_10
# BB#5:
	mov	rax, qword ptr [rbx]
	mov	rdi, rbx
	call	qword ptr [rax + 16]
	lea	rax, [rbx + 12]
	mov	ecx, __pthread_key_create
	test	rcx, rcx
	je	.LBB12_7
# BB#6:
	mov	ecx, -1
	lock
	xadd	dword ptr [rax], ecx
	jmp	.LBB12_8
.LBB12_7:
	mov	ecx, dword ptr [rax]
	lea	edx, [rcx - 1]
	mov	dword ptr [rax], edx
.LBB12_8:                               # %_ZN9__gnu_cxxL27__exchange_and_add_dispatchEPii.exit2.i.i.i.i
	cmp	ecx, 1
	jne	.LBB12_10
# BB#9:
	mov	rax, qword ptr [rbx]
	mov	rdi, rbx
	call	qword ptr [rax + 24]
.LBB12_10:                              # %_ZNSt6thread10_Impl_baseD2Ev.exit
	mov	rdi, r14
	add	rsp, 8
	pop	rbx
	pop	r14
	jmp	_ZdlPv                  # TAILCALL
.Lfunc_end12:
	.size	_ZNSt6thread10_Impl_baseD0Ev, .Lfunc_end12-_ZNSt6thread10_Impl_baseD0Ev
	.cfi_endproc

	.section	.text.startup,"ax",@progbits
	.align	16, 0x90
	.type	_GLOBAL__sub_I_acquire_release2.cc,@function
_GLOBAL__sub_I_acquire_release2.cc:     # @_GLOBAL__sub_I_acquire_release2.cc
	.cfi_startproc
# BB#0:
	push	rax
.Ltmp49:
	.cfi_def_cfa_offset 16
	mov	edi, _ZStL8__ioinit
	call	_ZNSt8ios_base4InitC1Ev
	mov	edi, _ZNSt8ios_base4InitD1Ev
	mov	esi, _ZStL8__ioinit
	mov	edx, __dso_handle
	pop	rax
	jmp	__cxa_atexit            # TAILCALL
.Lfunc_end13:
	.size	_GLOBAL__sub_I_acquire_release2.cc, .Lfunc_end13-_GLOBAL__sub_I_acquire_release2.cc
	.cfi_endproc

	.type	_ZStL8__ioinit,@object  # @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.type	sharedValue,@object     # @sharedValue
	.bss
	.globl	sharedValue
	.align	4
sharedValue:
	.long	0                       # 0x0
	.size	sharedValue, 4

	.type	flag,@object            # @flag
	.globl	flag
	.align	4
flag:
	.zero	4
	.size	flag, 4

	.type	_ZTSSt19_Sp_make_shared_tag,@object # @_ZTSSt19_Sp_make_shared_tag
	.section	.rodata._ZTSSt19_Sp_make_shared_tag,"aG",@progbits,_ZTSSt19_Sp_make_shared_tag,comdat
	.weak	_ZTSSt19_Sp_make_shared_tag
	.align	16
_ZTSSt19_Sp_make_shared_tag:
	.asciz	"St19_Sp_make_shared_tag"
	.size	_ZTSSt19_Sp_make_shared_tag, 24

	.type	_ZTVSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE,@object # @_ZTVSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE
	.section	.rodata._ZTVSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE,"aG",@progbits,_ZTVSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE,comdat
	.weak	_ZTVSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE
	.align	8
_ZTVSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE:
	.quad	0
	.quad	_ZTISt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE
	.quad	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED2Ev
	.quad	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EED0Ev
	.quad	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv
	.quad	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv
	.quad	_ZNSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info
	.size	_ZTVSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE, 56

	.type	_ZTSSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE,@object # @_ZTSSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE
	.section	.rodata._ZTSSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE,"aG",@progbits,_ZTSSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE,comdat
	.weak	_ZTSSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE
	.align	16
_ZTSSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE:
	.asciz	"St23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE"
	.size	_ZTSSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE, 111

	.type	_ZTSSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE,@object # @_ZTSSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE
	.section	.rodata._ZTSSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE,"aG",@progbits,_ZTSSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE,comdat
	.weak	_ZTSSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE
	.align	16
_ZTSSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE:
	.asciz	"St16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE"
	.size	_ZTSSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE, 52

	.type	_ZTSSt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE,@object # @_ZTSSt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE
	.section	.rodata._ZTSSt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE,"aG",@progbits,_ZTSSt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE,comdat
	.weak	_ZTSSt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE
	.align	16
_ZTSSt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE:
	.asciz	"St11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE"
	.size	_ZTSSt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE, 47

	.type	_ZTISt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE,@object # @_ZTISt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE
	.section	.rodata._ZTISt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE,"aG",@progbits,_ZTISt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE,comdat
	.weak	_ZTISt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE
	.align	8
_ZTISt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSSt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE
	.size	_ZTISt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE, 16

	.type	_ZTISt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE,@object # @_ZTISt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE
	.section	.rodata._ZTISt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE,"aG",@progbits,_ZTISt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE,comdat
	.weak	_ZTISt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE
	.align	16
_ZTISt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE
	.quad	_ZTISt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE
	.size	_ZTISt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE, 24

	.type	_ZTISt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE,@object # @_ZTISt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE
	.section	.rodata._ZTISt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE,"aG",@progbits,_ZTISt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE,comdat
	.weak	_ZTISt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE
	.align	16
_ZTISt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSSt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE
	.quad	_ZTISt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE
	.size	_ZTISt23_Sp_counted_ptr_inplaceINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEESaIS7_ELN9__gnu_cxx12_Lock_policyE2EE, 24

	.type	_ZTVNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE,@object # @_ZTVNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE
	.section	.rodata._ZTVNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE,"aG",@progbits,_ZTVNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE,comdat
	.weak	_ZTVNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE
	.align	8
_ZTVNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE:
	.quad	0
	.quad	_ZTINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE
	.quad	_ZNSt6thread10_Impl_baseD2Ev
	.quad	_ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEED0Ev
	.quad	_ZNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEE6_M_runEv
	.size	_ZTVNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE, 40

	.type	_ZTSNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE,@object # @_ZTSNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE
	.section	.rodata._ZTSNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE,"aG",@progbits,_ZTSNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE,comdat
	.weak	_ZTSNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE
	.align	16
_ZTSNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE:
	.asciz	"NSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE"
	.size	_ZTSNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE, 46

	.type	_ZTSNSt6thread10_Impl_baseE,@object # @_ZTSNSt6thread10_Impl_baseE
	.section	.rodata._ZTSNSt6thread10_Impl_baseE,"aG",@progbits,_ZTSNSt6thread10_Impl_baseE,comdat
	.weak	_ZTSNSt6thread10_Impl_baseE
	.align	16
_ZTSNSt6thread10_Impl_baseE:
	.asciz	"NSt6thread10_Impl_baseE"
	.size	_ZTSNSt6thread10_Impl_baseE, 24

	.type	_ZTINSt6thread10_Impl_baseE,@object # @_ZTINSt6thread10_Impl_baseE
	.section	.rodata._ZTINSt6thread10_Impl_baseE,"aG",@progbits,_ZTINSt6thread10_Impl_baseE,comdat
	.weak	_ZTINSt6thread10_Impl_baseE
	.align	8
_ZTINSt6thread10_Impl_baseE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSNSt6thread10_Impl_baseE
	.size	_ZTINSt6thread10_Impl_baseE, 16

	.type	_ZTINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE,@object # @_ZTINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE
	.section	.rodata._ZTINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE,"aG",@progbits,_ZTINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE,comdat
	.weak	_ZTINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE
	.align	16
_ZTINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSNSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE
	.quad	_ZTINSt6thread10_Impl_baseE
	.size	_ZTINSt6thread5_ImplISt12_Bind_simpleIFPFvvEvEEEE, 24

	.type	_ZTVNSt6thread10_Impl_baseE,@object # @_ZTVNSt6thread10_Impl_baseE
	.section	.rodata._ZTVNSt6thread10_Impl_baseE,"aG",@progbits,_ZTVNSt6thread10_Impl_baseE,comdat
	.weak	_ZTVNSt6thread10_Impl_baseE
	.align	8
_ZTVNSt6thread10_Impl_baseE:
	.quad	0
	.quad	_ZTINSt6thread10_Impl_baseE
	.quad	_ZNSt6thread10_Impl_baseD2Ev
	.quad	_ZNSt6thread10_Impl_baseD0Ev
	.quad	__cxa_pure_virtual
	.size	_ZTVNSt6thread10_Impl_baseE, 40

	.section	.init_array,"aw",@init_array
	.align	8
	.quad	_GLOBAL__sub_I_acquire_release2.cc
	.weak	__pthread_key_create

	.ident	"clang version 3.7.1 (tags/RELEASE_371/final)"
	.section	".note.GNU-stack","",@progbits
