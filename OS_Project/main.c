#include <stdio.h>
#include<stdlib.h>
#include <memory.h>
#include <kernel_call.h>
#include <timer.h>
int main()
{

    measure_read_file();

    return;

    pid_t pid = fork();
    if (pid==0) // start receiver for child
    {
        printf("starting receiver");
        start_receiver();
    }else if (pid<0)
    {
        printf("failed to fork");
        exit(1);
    }else
    {
        sleep(2);
        measure_signalling();
        //	measure_kernel_call();
        //      measure_read_file();
    }
    return 0;
}

void measure_signalling()
{
    start_sender();
}
