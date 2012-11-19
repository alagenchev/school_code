
#include "apue.h"
#include<sys/wait.h>


int main()
{
    pid_t pid;
    int status;

    printf("parent is %d\n",getpid());

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)              /* child */
        printf("in child %d\n", getpid());

    if(wait(&status)!= pid)
        ;

    printf("enter input for %d\n", getpid());
    int i;
    scanf("%d",&i);
    printf("output for %d is %d\n", getpid(), i);
    printf("done from %d\n", getpid());
}
