#include<stdio.h>
#include "dmtcpaware.h"

int main()
{
    if(dmtcpIsEnabled())
    {
        printf("app dmtcp is enabled\n");
    }

    printf("hello world from application\n");
}
