#include <linux/unistd.h>
#include <sys/syscall.h>
#include <time.h>
#define FILE_NAME "foo.txt" 
#define LINK_NAME "bar.txt" 

//function declerations

inline unsigned long long start_timer_kc() 
{
	struct timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	return time.tv_sec * 1000000000 + time.tv_nsec;
}

inline unsigned long long stop_timer_kc(unsigned long long start_time, char *label) 
{
	struct timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);

	unsigned long long end_time = time.tv_sec * 1000000000 + time.tv_nsec;
	printf("%s: %.5f sec\n", label, ((float) (end_time - start_time)) / (1000 * 1000 * 1000));
	return end_time - start_time;
}


unsigned long long int rdtsc_kc(void)
{
	unsigned long long int x;
	unsigned a, d;

	__asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

	return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}

inline unsigned long long start_rdtsc_timer_kc()
{
	return rdtsc_kc();
}

inline unsigned long long stop_rdtsc_timer_kc(unsigned long long start_time, char* label)
{
	unsigned long long end_time = rdtsc_kc();
	//printf("rtdsc start is %llu, end is %llu\n", start_time, end_time);

	unsigned long long total_time = end_time - start_time;
	printf("RDTSC: %s: %llu \n", label, total_time);
	return total_time;
}
int measure_kernel_call()
{
	long jiffies;
	long long iterations[] = {1, 10000, 100000, 1000000, 10000000, 100000000};
    
	/*for (int j=0; j < 6; j++)
	{
		unsigned long long wall_time = start_timer_kc();
		unsigned long long rdtsc_time = start_rdtsc_timer_kc();
		for (int i=0; i<iterations[j];i++)
		{
			jiffies = syscall( SYS_getpid );
		}
		printf("\n\niterations = %d\n", iterations[j]);
		rdtsc_time = stop_rdtsc_timer_kc(rdtsc_time, "pid_sys_call");
		stop_timer_kc(wall_time, "pid_sys_call");
	}*/
	for (int j=0; j < 6; j++)
	{
		unsigned long long wall_time = start_timer_kc();
		unsigned long long rdtsc_time = start_rdtsc_timer_kc();
		for (int i=0; i < iterations[j]; i++)
		{
			syscall(SYS_link, FILE_NAME, LINK_NAME);
			syscall(SYS_unlink, LINK_NAME);
		}
		printf("\n\niterations = %d\n", iterations[j]);
		rdtsc_time = stop_rdtsc_timer_kc(rdtsc_time, "pid_sys_call");
		stop_timer_kc(wall_time, "pid_sys_call");
	}
return 0;
}
