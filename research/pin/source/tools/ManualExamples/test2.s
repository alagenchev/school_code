.section .data
output:
.ascii "This is a test message.\n"
output_end:
.equ len, output_end - output
.section .text
.globl main
main:
movq $1, %rax
movq $1, %rdi
movq $output, %rsi
movq $len, %rdx
syscall

