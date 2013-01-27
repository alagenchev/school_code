.section .data
.section .text
.globl main
main:
    jmp print

message:
    .string "Hello, world!\n"
print:
    
    lea message(%rip), %rsi
    xor %rax,%rax
    xor %rdi, %rdi
    xor %rdx, %rdx

    add $1, %rax
    add $1, %rdi
    add $14, %rdx
    syscall

    xor %rax, %rax
    add $60, %rax
    xor %rdi, %rdi
    syscall

