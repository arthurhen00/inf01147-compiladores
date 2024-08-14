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

	movss _a(%rip), %xmm0
	movss _b(%rip), %xmm1
	comiss %xmm1, %xmm0
	seta %al
	movzbl %al, %eax
	movl %eax, _temp0(%rip)

	movl _temp0(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm0
	movss _a(%rip), %xmm1
	comiss %xmm1, %xmm0
	seta %al
	movzbl %al, %eax
	movl %eax, _temp1(%rip)

	movl _temp1(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm0
	movss _c(%rip), %xmm1
	comiss %xmm1, %xmm0
	seta %al
	movzbl %al, %eax
	movl %eax, _temp2(%rip)

	movl _temp2(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm1
	movss _b(%rip), %xmm0
	comiss %xmm1, %xmm0
	seta %al
	movzbl %al, %eax
	movl %eax, _temp3(%rip)

	movl _temp3(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm1
	movss _a(%rip), %xmm0
	comiss %xmm1, %xmm0
	seta %al
	movzbl %al, %eax
	movl %eax, _temp4(%rip)

	movl _temp4(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm1
	movss _c(%rip), %xmm0
	comiss %xmm1, %xmm0
	seta %al
	movzbl %al, %eax
	movl %eax, _temp5(%rip)

	movl _temp5(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm0
	movss _b(%rip), %xmm1
	comiss %xmm1, %xmm0
	setnb %al
	movzbl %al, %eax
	movl %eax, _temp6(%rip)

	movl _temp6(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm0
	movss _a(%rip), %xmm1
	comiss %xmm1, %xmm0
	setnb %al
	movzbl %al, %eax
	movl %eax, _temp7(%rip)

	movl _temp7(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm0
	movss _c(%rip), %xmm1
	comiss %xmm1, %xmm0
	setnb %al
	movzbl %al, %eax
	movl %eax, _temp8(%rip)

	movl _temp8(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm1
	movss _b(%rip), %xmm0
	comiss %xmm1, %xmm0
	setnb %al
	movzbl %al, %eax
	movl %eax, _temp9(%rip)

	movl _temp9(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm1
	movss _a(%rip), %xmm0
	comiss %xmm1, %xmm0
	setnb %al
	movzbl %al, %eax
	movl %eax, _temp10(%rip)

	movl _temp10(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm1
	movss _c(%rip), %xmm0
	comiss %xmm1, %xmm0
	setnb %al
	movzbl %al, %eax
	movl %eax, _temp11(%rip)

	movl _temp11(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm0
	movss _b(%rip), %xmm1
	ucomiss %xmm1, %xmm0
	setnp %al
	movl $0, %edx
	ucomiss %xmm1, %xmm0
	cmovne %edx, %eax
	movzbl %al, %eax
	movl %eax, _temp12(%rip)

	movl _temp12(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm0
	movss _a(%rip), %xmm1
	ucomiss %xmm1, %xmm0
	setnp %al
	movl $0, %edx
	ucomiss %xmm1, %xmm0
	cmovne %edx, %eax
	movzbl %al, %eax
	movl %eax, _temp13(%rip)

	movl _temp13(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm0
	movss _c(%rip), %xmm1
	ucomiss %xmm1, %xmm0
	setnp %al
	movl $0, %edx
	ucomiss %xmm1, %xmm0
	cmovne %edx, %eax
	movzbl %al, %eax
	movl %eax, _temp14(%rip)

	movl _temp14(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm0
	movss _b(%rip), %xmm1
	ucomiss %xmm1, %xmm0
	setp %al
	movl $1, %edx
	ucomiss %xmm1, %xmm0
	cmovne %edx, %eax
	movzbl %al, %eax
	movl %eax, _temp15(%rip)

	movl _temp15(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm0
	movss _a(%rip), %xmm1
	ucomiss %xmm1, %xmm0
	setp %al
	movl $1, %edx
	ucomiss %xmm1, %xmm0
	cmovne %edx, %eax
	movzbl %al, %eax
	movl %eax, _temp16(%rip)

	movl _temp16(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movss _a(%rip), %xmm0
	movss _c(%rip), %xmm1
	ucomiss %xmm1, %xmm0
	setp %al
	movl $1, %edx
	ucomiss %xmm1, %xmm0
	cmovne %edx, %eax
	movzbl %al, %eax
	movl %eax, _temp17(%rip)

	movl _temp17(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movl _true(%rip), %eax
	cmpl $0, %eax
	sete %al
	movzbl %al, %eax
	movl %eax, _temp18(%rip)

	movl _temp18(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movl _false(%rip), %eax
	cmpl $0, %eax
	sete %al
	movzbl %al, %eax
	movl %eax, _temp19(%rip)

	movl _temp19(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movl _true(%rip), %eax
	cmpl $0, %eax
	sete %al
	movzbl %al, %eax
	movl %eax, _temp20(%rip)

	movl _true(%rip), %eax
	cmpl $0, %eax
	sete %al
	movzbl %al, %eax
	movl %eax, _temp21(%rip)

	movl _temp20(%rip), %eax
	movl _temp21(%rip), %edx
	andl %edx, %eax
	movl %eax, _temp22(%rip)

	movl _temp22(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movl _true(%rip), %eax
	movl _true(%rip), %edx
	andl %edx, %eax
	movl %eax, _temp23(%rip)

	movl _temp23(%rip), %esi
	leaq .LC3(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	leaq _349211034(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	popq %rbp
	ret

	.data
_349211034:
	.string "\n"
_true:
	.long 1
_a:
	.long 1084647014
_b:
	.long 1084437299
_c:
	.long 1084856730
_temp0:
	.long 0
_temp1:
	.long 0
_temp2:
	.long 0
_temp3:
	.long 0
_temp4:
	.long 0
_temp5:
	.long 0
_temp6:
	.long 0
_temp7:
	.long 0
_temp8:
	.long 0
_temp9:
	.long 0
_5.1:
	.long 1084437299
_5.2:
	.long 1084647014
_5.3:
	.long 1084856730
_false:
	.long 0
_temp10:
	.long 0
_temp11:
	.long 0
_temp12:
	.long 0
_temp13:
	.long 0
_temp14:
	.long 0
_temp15:
	.long 0
_temp16:
	.long 0
_temp17:
	.long 0
_temp18:
	.long 0
_temp19:
	.long 0
_temp20:
	.long 0
_temp21:
	.long 0
_temp22:
	.long 0
_temp23:
	.long 0
