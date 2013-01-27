#include <stdio.h>

unsigned long find_start()
{
    __asm__("movq %rsp, %rax");
    //retq instruction returns the value that is stored in %rax
}

void main()
{
    printf("%p\n", find_start());
}
