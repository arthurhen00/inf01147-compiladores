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

	movl _100(%rip), %eax
	movl %eax, _a(%rip)
	movl _101(%rip), %eax
	movl %eax, _b(%rip)
	call funcao
	movl %eax, _temp0(%rip)

	movl _temp0(%rip), %esi
	leaq .LC0(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movl _200(%rip), %eax
	movl %eax, _c(%rip)
	movl _201(%rip), %eax
	movl %eax, _d(%rip)
	call funcao1
	movl %eax, _temp1(%rip)

	movl _temp1(%rip), %esi
	leaq .LC0(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _100.11(%rip), %xmm0
	movss %xmm0, _aF(%rip)
	movss _101.11(%rip), %xmm0
	movss %xmm0, _bF(%rip)
	call funcaoF
	movd %xmm0, %eax
	movl %eax, _temp2(%rip)

	movss	_temp2(%rip), %xmm0
	pxor %xmm1, %xmm1
	cvtss2sd %xmm0, %xmm1
	movq %xmm1, %rax
	movq %rax, %xmm0
	leaq .LC2(%rip), %rax
	movq %rax, %rdi
	movl $1, %eax
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _200.11(%rip), %xmm0
	movss %xmm0, _cF(%rip)
	movss _201.11(%rip), %xmm0
	movss %xmm0, _dF(%rip)
	call funcao1F
	movd %xmm0, %eax
	movl %eax, _temp3(%rip)

	movss	_temp3(%rip), %xmm0
	pxor %xmm1, %xmm1
	cvtss2sd %xmm0, %xmm1
	movq %xmm1, %rax
	movq %rax, %xmm0
	leaq .LC2(%rip), %rax
	movq %rax, %rdi
	movl $1, %eax
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	popq %rbp
	ret

	.globl funcao
funcao:
	pushq %rbp
	movq %rsp, %rbp

	movl _a(%rip), %esi
	leaq .LC0(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movl _b(%rip), %esi
	leaq .LC0(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movl _1000(%rip), %eax

	popq %rbp
	ret

	.globl funcao1
funcao1:
	pushq %rbp
	movq %rsp, %rbp

	movl _c(%rip), %esi
	leaq .LC0(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movl _d(%rip), %esi
	leaq .LC0(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movl _2000(%rip), %eax

	popq %rbp
	ret

	.globl funcaoF
funcaoF:
	pushq %rbp
	movq %rsp, %rbp

	movss	_aF(%rip), %xmm0
	pxor %xmm1, %xmm1
	cvtss2sd %xmm0, %xmm1
	movq %xmm1, %rax
	movq %rax, %xmm0
	leaq .LC2(%rip), %rax
	movq %rax, %rdi
	movl $1, %eax
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss	_bF(%rip), %xmm0
	pxor %xmm1, %xmm1
	cvtss2sd %xmm0, %xmm1
	movq %xmm1, %rax
	movq %rax, %xmm0
	leaq .LC2(%rip), %rax
	movq %rax, %rdi
	movl $1, %eax
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _1000.11(%rip), %xmm0

	popq %rbp
	ret

	.globl funcao1F
funcao1F:
	pushq %rbp
	movq %rsp, %rbp

	movss	_cF(%rip), %xmm0
	pxor %xmm1, %xmm1
	cvtss2sd %xmm0, %xmm1
	movq %xmm1, %rax
	movq %rax, %xmm0
	leaq .LC2(%rip), %rax
	movq %rax, %rdi
	movl $1, %eax
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss	_dF(%rip), %xmm0
	pxor %xmm1, %xmm1
	cvtss2sd %xmm0, %xmm1
	movq %xmm1, %rax
	movq %rax, %xmm0
	leaq .LC2(%rip), %rax
	movq %rax, %rdi
	movl $1, %eax
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _2000.11(%rip), %xmm0

	popq %rbp
	ret

	.data
_349211034:
	.string "\n"
_101.11:
	.long 1120548946
_a:
	.long 0
_b:
	.long 0
_c:
	.long 0
_d:
	.long 0
_aF:
	.long 0
_100.11:
	.long 1120417874
_bF:
	.long 0
_temp0:
	.long 0
_temp1:
	.long 0
_temp2:
	.long 0
_temp3:
	.long 0
_2000:
	.long 2000
_cF:
	.long 0
_dF:
	.long 0
_1000:
	.long 1000
_200:
	.long 200
_201:
	.long 201
_100:
	.long 100
_101:
	.long 101
_201.11:
	.long 1128864809
_2000.11:
	.long 1157235589
_200.11:
	.long 1128799273
_1000.11:
	.long 1148847882
