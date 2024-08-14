	.file	"t.c"
	.text
	.globl	vetor
	.bss
	.align 32
	.type	vetor, @object
	.size	vetor, 40
vetor:
	.zero	40
	.globl	i
	.data
	.align 4
	.type	i, @object
	.size	i, 4
i:
	.long	1
	.globl	a
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	2
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp
	
	movl	a(%rip), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	vetor(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, i(%rip)
	movl	$0, %eax

	popq	%rbp
	ret
.LFE0:
	.size	main, .-main
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
