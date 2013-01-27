.section .data
.section .text
.globl main
main:
    jmp get_address    # jump down and do a call to get the address
 
run:

    pop %rsi             # pop the message address into rsi
    xor %rax, %rax       # zero the registers
    xor %rdi, %rdi
    xor %rdx, %rdx
 
    # sys_write(stdout, message, length)
    add    $1, %rax      # sys_write
    add    $1, %rdi      # stdout
    add    $14, %rdx     # message string length
    syscall
 
    # sys_exit(return_code)
    xor %rax, %rax
    add    $60, %rax     # sys_exit
    xor %rdi, %rdi        # return 0 (success)
    syscall
 
get_address:
    call run            # put address of our message onto the stack
 
message:
    .string "Hello, world!\n"

