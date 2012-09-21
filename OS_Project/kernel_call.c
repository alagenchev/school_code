#include <linux/unistd.h>
#include <sys/syscall.h>
#include <timer.h>
#define __NR_getjiffies 320

//function declerations

int measure_kernel_call()
{
        long jiffies;
        long long start_time = start_timer();
        
        for (int i=0; i<10000;i++)
        { 
                jiffies = syscall( SYS_getpid );
        }
        
        stop_timer(start_time, "pid_sys_call");

        return 0;
}
