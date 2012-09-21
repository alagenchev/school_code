#include <linux/unistd.h>
#include <sys/syscall.h>
#include <timer.h>
#define __NR_getjiffies 320

//function declerations

int measure_kernel_call()
{
        long jiffies;
        unsigned long long wall_time = start_timer();
        unsigned long long rdtsc_time = start_rdtsc_timer();
        
        for (int i=0; i<100000;i++)
        { 
                jiffies = syscall( SYS_getpid );
        }
        
        rdtsc_time = stop_rdtsc_timer(rdtsc_time, "pid_sys_call");

        stop_timer(wall_time, "pid_sys_call");

        return 0;
}
