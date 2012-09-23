#include  <stdio.h>
#include  <sys/types.h>
#include  <signal.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>

void  SIGINT_handler_receiver(int);   
void  SIGQUIT_handler_receiver(int); 

int   ShmID;      
pid_t *ShmPTR;    
pid_t sender_pid;

void start_receiver(void)
{
	register_handlers_receiver();
	set_receiver_id();
	for (int i = 0; ; i++)
	{        
		sleep(1);
	}
}
void register_handlers_receiver()
{
	if (signal(SIGINT, SIGINT_handler_receiver) == SIG_ERR) {
		printf("SIGINT install error\n");
		exit(1);
	}
	if (signal(SIGQUIT, SIGQUIT_handler_receiver) == SIG_ERR) {
		printf("SIGQUIT install error\n");
		exit(2);
	}

}
void  SIGINT_handler_receiver(int sig)
{
	signal(sig, SIG_IGN);
	get_sender_id();
	printf("From SIGINT: just got a %d (SIGINT ^C) signal from sender\n", sig);
	signal(sig, SIGINT_handler_receiver);
	printf("Sending interrupt to sender\n");
	kill(sender_pid, SIGINT);
}
void get_sender_id()
{
	key_t MyKey;
	int   ShmID;
	pid_t *ShmPTR;
	char  line[100], c;
	int   i;

	MyKey   = ftok(".", 's');        
	ShmID   = shmget(MyKey, sizeof(pid_t), 0666);
	ShmPTR  = (pid_t *) shmat(ShmID, NULL, 0);
	sender_pid     = *ShmPTR;                
	shmdt(ShmPTR);                    
}
void set_receiver_id()
{
	int   i;
	pid_t pid = getpid();
	key_t MyKey;

	MyKey   = ftok(".", 's');    
	ShmID   = shmget(MyKey, sizeof(pid_t), IPC_CREAT | 0666);
	ShmPTR  = (pid_t *) shmat(ShmID, NULL, 0);
	*ShmPTR = pid;               

}

void  SIGQUIT_handler_receiver(int sig)
{
	signal(sig, SIG_IGN);
	printf("From SIGQUIT: just got a %d (SIGQUIT ^\\) signal"
			" and is about to quit\n", sig);
	shmdt(ShmPTR);
	shmctl(ShmID, IPC_RMID, NULL);

	exit(3);
}
