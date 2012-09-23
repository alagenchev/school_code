#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

inline unsigned long long start_timer_pipe() 
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return time.tv_sec * 1000000000 + time.tv_nsec;
}

inline unsigned long long stop_timer_pipe(unsigned long long start_time, char *label) 
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);

    unsigned long long end_time = time.tv_sec * 1000000000 + time.tv_nsec;
    printf("%s: %.5f sec\n", label, ((float) (end_time - start_time)) / (1000 * 1000 * 1000));
    return end_time - start_time;
}



unsigned long long int rdtsc_pipe(void)
{
    unsigned long long int x;
    unsigned a, d;

    __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

    return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}

inline unsigned long long start_rdtsc_timer_pipe()
{
    return rdtsc_pipe();
}

inline unsigned long long stop_rdtsc_timer_pipe(unsigned long long start_time, char* label)
{
    unsigned long long end_time = rdtsc_pipe();
    //printf("rtdsc start is %llu, end is %llu\n", start_time, end_time);

    unsigned long long total_time = end_time - start_time;
    printf("RDTSC: %s: %llu \n", label, total_time);
    return total_time;
}

int measure_pipe_communication()
{
        int     fd_child_write[2], fd_parent_write[2], nbytes;
        pid_t   childpid;
        char    string[] = "Hello, world!\n";
        char    readbuffer[80];
        char    readbuffer_child[80];

        pipe(fd_child_write);
        pipe(fd_parent_write);

        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                /* Child process closes up input side of pipe */
                unsigned long long wall_time = start_timer_pipe();
                unsigned long long rdtsc_time = start_rdtsc_timer_pipe();
                close(fd_child_write[0]);
                close(fd_parent_write[1]);

                /* Send "string" through the output side of pipe */
                write(fd_child_write[1], string, (strlen(string)+1));
                nbytes = read(fd_parent_write[0], readbuffer_child, sizeof(readbuffer_child));
                printf("Received response: %s\n", readbuffer_child);
                rdtsc_time = stop_rdtsc_timer_pipe(rdtsc_time, "piping process switch");
                stop_timer_pipe(wall_time, "piping process switch");

                exit(0);
        }
        else
        {
                /* Parent process closes up output side of pipe */
                close(fd_child_write[1]);
                close(fd_parent_write[0]);

                /* Read in a string from the pipe */
                nbytes = read(fd_child_write[0], readbuffer, sizeof(readbuffer));
                printf("Received string: %s", readbuffer);
                if(strcmp(readbuffer, string) == 0)
                {
                        char* response = "got the response\n";
                        printf("Sending response\n");
                        write(fd_parent_write[1], response, strlen(response) + 1);
                }
        }

        return(0);
}
