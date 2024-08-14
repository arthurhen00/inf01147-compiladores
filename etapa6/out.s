.LC0:
	.string "%d\n"
.LC1:
	.string "%c\n"
.LC2:
	.string "%f\n"
.LC3:
	.string "%d\n"

	.globl main
main:
	pushq %rbp
	movq %rsp, %rbp

_label1:

	movl _i(%rip), %edx
	movl _10(%rip), %eax
	cmpl %eax, %edx
	setl %al
	movzbl %al, %eax
	movl %eax, _temp0(%rip)

	cmpl $0, _temp0(%rip)
	je _label0

	movl _i(%rip), %esi
	leaq .LC0(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movl 0+_vetor(%rip), %eax
	movl %eax, _temp1(%rip)

	movl _temp1(%rip), %esi
	leaq .LC0(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movl _i(%rip), %edx
	movl _1(%rip), %eax
	addl %edx, %eax
	movl %eax, _temp2(%rip)

	movl _temp2(%rip), %eax
	movl %eax, _i(%rip)

	movl 0+_i(%rip), %eax
	movl %eax, _vetor(%rip)

	jmp _label1

_label0:

	movl 28+_vetor(%rip), %eax
	movl %eax, _temp3(%rip)

	movl _temp3(%rip), %esi
	leaq .LC0(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movl 32+_vetor(%rip), %eax
	movl %eax, _temp4(%rip)

	movl _temp4(%rip), %esi
	leaq .LC0(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movl 36+_vetor(%rip), %eax
	movl %eax, _temp5(%rip)

	movl _temp5(%rip), %esi
	leaq .LC0(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movl 40+_vetor(%rip), %eax
	movl %eax, _temp6(%rip)

	movl _temp6(%rip), %esi
	leaq .LC0(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movl 44+_vetor(%rip), %eax
	movl %eax, _temp7(%rip)

	movl _temp7(%rip), %esi
	leaq .LC0(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	movl 48+_vetor(%rip), %eax
	movl %eax, _temp8(%rip)

	movl _temp8(%rip), %esi
	leaq .LC0(%rip), %rax
	movq %rax, %rdi
	call printf@PLT

	popq %rbp
	ret

	.data
_0:
	.long 0
_1:
	.long 1
_7:
	.long 7
_8:
	.long 8
_9:
	.long 9
_i:
	.long 0
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
_vetor:
	.zero 40
_10:
	.long 10
_11:
	.long 11
_12:
	.long 12
