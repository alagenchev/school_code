#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int me()
{
    printf("in me\n");
}

int main(int argc, char **argv)
{

    foo();
    me();
}

int bar()
{
    printf("in bar\n");
}
int foo()
{
    int x = 5;
    if(x < 4)
    {
        printf("here\n");
    }
    else
    {
        printf("there\n");
    }
    bar();
}
