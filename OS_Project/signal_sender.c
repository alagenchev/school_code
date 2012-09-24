#include  <stdio.h>
#include  <sys/types.h>
#include  <signal.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <time.h>

pid_t   receiver_pid;

//long long iterations = 10;
long long iterations[] = {1, 10000, 100000, 1000000, 10000000, 100000000};
//long long current_iteration = 0;
long long current_iteration = 0;
int loop_index = 0;

unsigned long long wall_time;
unsigned long long rdtsc_time;
void  SIGINT_handler_sender(int);   

inline unsigned long long start_timer_sender() 
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return time.tv_sec * 1000000000 + time.tv_nsec;
}

inline unsigned long long stop_timer_sender(unsigned long long start_time, char *label) 
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);

    unsigned long long end_time = time.tv_sec * 1000000000 + time.tv_nsec;
    printf("%s: %.5f sec\n", label, ((float) (end_time - start_time)) / (1000 * 1000 * 1000));
    return end_time - start_time;
}



unsigned long long int rdtsc_sender(void)
{
    unsigned long long int x;
    unsigned a, d;

    __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

    return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}

inline unsigned long long start_rdtsc_timer_sender()
{
    return rdtsc_sender();
}

inline unsigned long long stop_rdtsc_timer_sender(unsigned long long start_time, char* label)
{
    unsigned long long end_time = rdtsc_sender();
    //printf("rtdsc start is %llu, end is %llu\n", start_time, end_time);

    unsigned long long total_time = end_time - start_time;
    printf("RDTSC: %s: %llu \n", label, total_time);
    return total_time;
}
void  start_sender(void)
{
        //shmdt(ShmPTR);                    
        register_handlers_sender();
        get_receiver_id();
        set_sender_id();
        wall_time = start_timer_sender();
        rdtsc_time = start_rdtsc_timer_sender();
        kill(receiver_pid, SIGINT);
        printf("Sent a SIGINT signal from sender\n");
        wait();
}

void get_receiver_id()
{
        key_t MyKey;
        int   ShmID;
        pid_t *ShmPTR;

        MyKey   = ftok(".", 's');        
        ShmID   = shmget(MyKey, sizeof(pid_t), 0666);
        ShmPTR  = (pid_t *) shmat(ShmID, NULL, 0);
        receiver_pid     = *ShmPTR;                
}
void set_sender_id()
{
        key_t MyKey;
        int   ShmID;
        pid_t *ShmPTR;

        MyKey   = ftok(".", 's');        
        ShmID   = shmget(MyKey, sizeof(pid_t), 0666);
        ShmPTR  = (pid_t *) shmat(ShmID, NULL, 0);
        *ShmPTR = getpid();               
}
void wait()
{
        for(int i=0;;i++)
        {
                sleep(1);
        }

}
void register_handlers_sender()
{
	if (signal(SIGINT, SIGINT_handler_sender) == SIG_ERR) {
		printf("SIGINT install error\n");
		exit(1);
	}
}
void  SIGINT_handler_sender(int sig)
{
	current_iteration += 1;
	if(current_iteration < iterations[loop_index])
	{
		kill(receiver_pid, SIGINT);
	}else
	{
		printf("\n\nIterations = %d\n", iterations[loop_index]);
		rdtsc_time = stop_rdtsc_timer_sender(rdtsc_time, "signal exchange");
		stop_timer_sender(wall_time, "signal exchange");
		loop_index += 1;
		if(loop_index < 6)
		{
			current_iteration = 0;
			set_sender_id();
			wall_time = start_timer_sender();
			rdtsc_time = start_rdtsc_timer_sender();
			kill(receiver_pid, SIGINT);
		}else 
		{

			//printf("From SIGINT: just got a %d (SIGINT ^C) signal back from receiver\n", sig);
			signal(sig, SIGINT_handler_sender);

			//printf("About to send a SIGQUIT signal to receiver\n");
			//kill(receiver_pid, SIGINT);
			kill(receiver_pid, SIGQUIT);     
			exit(0);
		}
	}
}
