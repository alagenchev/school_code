#include <stdio.h>
#include <sys/types.h>
#include <string.h>
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
                unsigned long long wall_time = start_timer();
                unsigned long long rdtsc_time = start_rdtsc_timer();
                close(fd_child_write[0]);
                close(fd_parent_write[1]);

                /* Send "string" through the output side of pipe */
                write(fd_child_write[1], string, (strlen(string)+1));
                nbytes = read(fd_parent_write[0], readbuffer_child, sizeof(readbuffer_child));
                printf("Received response: %s\n", readbuffer_child);
                rdtsc_time = stop_rdtsc_timer(rdtsc_time, "piping process switch");
                stop_timer(wall_time, "piping process switch");

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
                        write(fd_parent_write, response, strlen(response) + 1);
                }

        }

        return(0);
}
