#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dlfcn.h>
#include "dmtcpaware.h"

char *fgets(char* str, int num, FILE* stream)
{
	char* return_value;
        typeof(fgets) *old_fgets;

	if(dmtcpIsEnabled()) {
		printf("OVERSEER: Making checkpoint.\n"); 
		dmtcpCheckpoint();
	} else
		printf("OVERSEER: DMTCP not enabled.\n");

        // get a pointer to the function "printf"
        old_fgets = dlsym(RTLD_NEXT, "fgets");
        return_value = (*old_fgets)(str, num, stream); // and we call the function with previous arguments

        return return_value;
}
