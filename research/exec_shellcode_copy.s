.global main

.data                          # needs to be writable and executable for testing
main: 

jmp get_address        # get the address of our string

run: 

pop %rdi #put shell in %rdi
# execve(char *filename, char *argv[], char *envp[])
xorq %rax,%rax
addq $59,%rax          # 59 = execve
movq $0x0, 7(%rdi)
xorq %rsi,%rsi         # char *argv[] = null
xorq %rdx,%rdx         # char *envp[] = null

syscall

get_address: 
call run               # push the address of the string onto the stack

shell: 
.ascii "/bin/shN"

