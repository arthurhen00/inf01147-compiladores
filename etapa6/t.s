	.file	"t.c"
	.text
	.globl	funcao
	.type	funcao, @function
funcao:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp

	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	movl	80(%rbp), %eax

	popq	%rbp
	ret
.LFE0:
	.size	funcao, .-funcao
	.globl	entrada1
	.data
	.align 4
	.type	entrada1, @object
	.size	entrada1, 4
entrada1:
	.long	10
	.globl	entrada2
	.align 4
	.type	entrada2, @object
	.size	entrada2, 4
entrada2:
	.long	20
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	pushq	%rbp
	movq	%rsp, %rbp

	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$24, %rsp
	movl	entrada1(%rip), %r14d
	movl	entrada1(%rip), %r13d
	movl	entrada1(%rip), %r12d
	movl	entrada1(%rip), %ebx
	movl	entrada2(%rip), %r11d
	movl	entrada2(%rip), %r10d
	movl	entrada2(%rip), %r9d
	movl	entrada2(%rip), %r8d
	movl	entrada2(%rip), %edi
	movl	entrada2(%rip), %eax
	movl	%eax, -52(%rbp)
	movl	entrada2(%rip), %r15d
	movl	entrada2(%rip), %ecx
	movl	entrada2(%rip), %edx
	movl	entrada2(%rip), %esi
	movl	entrada1(%rip), %eax
	pushq	$9
	pushq	$8
	pushq	$7
	pushq	$6
	pushq	$5
	pushq	$4
	pushq	$3
	pushq	$2
	pushq	$1
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	pushq	%r11
	pushq	%r10
	pushq	%r9
	pushq	%r8
	pushq	%rdi
	movl	-52(%rbp), %r9d
	movl	%r15d, %r8d
	movl	%eax, %edi
	call	funcao
	addq	$144, %rsp
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15

	popq	%rbp
	ret
.LFE1:
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
