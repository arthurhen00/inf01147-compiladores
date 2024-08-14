.LC0:
	.string "%d"
.LC1:
	.string "%c"
.LC2:
	.string "%f"
.LC3:
	.string "%d"

	.globl funcao
funcao:
	pushq %rbp
	movq %rsp, %rbp

	movss _99.999(%rip), %xmm0

	popq %rbp
	ret

	.globl main
main:
	pushq %rbp
	movq %rsp, %rbp

	call funcao
	movd %xmm0, %eax
	movl %eax, _temp0(%rip)

	movl _temp0(%rip), %eax
	movl %eax, _res(%rip)

	call funcao
	movd %xmm0, %eax
	movl %eax, _temp1(%rip)

	movss	_temp1(%rip), %xmm0
	pxor %xmm1, %xmm1
	cvtss2sd %xmm0, %xmm1
	movq %xmm1, %rax
	movq %rax, %xmm0
	leaq .LC2(%rip), %rax
	movq %rax, %rdi
	movl $1, %eax
	call printf@PLT

	popq %rbp
	ret

	.data
_99.999:
	.long 1120403325
_11.11:
	.long 1093780111
_temp0:
	.long 0
_temp1:
	.long 0
_res:
	.long 1093780111
