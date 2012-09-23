#include  <stdio.h>
#include  <sys/types.h>
#include  <signal.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <timer.h>

pid_t   receiver_pid;
unsigned long long wall_time;
unsigned long long rdtsc_time;
void  SIGINT_handler_sender(int);   

void  start_sender(void)
{
        //shmdt(ShmPTR);                    
        register_handlers_sender();
        get_receiver_id();
        set_sender_id();
        wall_time = start_timer();
        rdtsc_time = start_rdtsc_timer();
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
        rdtsc_time = stop_rdtsc_timer(rdtsc_time, "signal exchange");
        stop_timer(wall_time, "signal exchange");
	
        signal(sig, SIG_IGN);
	printf("From SIGINT: just got a %d (SIGINT ^C) signal back from receiver\n", sig);
	signal(sig, SIGINT_handler_sender);
	kill(receiver_pid, SIGINT);

        printf("About to send a SIGQUIT signal to receiver\n");
        kill(receiver_pid, SIGQUIT);     
        exit(0);
}
