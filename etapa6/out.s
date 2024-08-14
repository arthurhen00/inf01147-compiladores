.LC0:
	.string "%d"
.LC1:
	.string "%c"
.LC2:
	.string "%f"
.LC3:
	.string "%d"

	.globl main
main:
	pushq %rbp
	movq %rsp, %rbp

	leaq _3411610111511610134(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _3411610111511610134(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _3411610111511610134(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _3411610111511610134(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _3411610111511610134(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	popq %rbp
	ret

	.data
_3411610111511610134:
	.string "teste"
