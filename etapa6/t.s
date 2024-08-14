	.file	"t.c"
	.text
	.globl	funcao
	.type	funcao, @function
funcao:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	.LC0(%rip), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	funcao, .-funcao
	.globl	res
	.bss
	.align 4
	.type	res, @object
	.size	res, 4
res:
	.zero	4
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	pushq	%rbp
	movq	%rsp, %rbp
	
	movl	$0, %eax
	call	funcao
	movd	%xmm0, %eax
	movl	%eax, res(%rip)
	movl	$0, %eax

	popq	%rbp
	ret
.LFE1:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	1148845916
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
