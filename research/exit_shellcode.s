.section .data
.section .bss

.section .text

.globl main
main:

mov $60, %rax
mov $999, %rdi
syscall

