#include <unistd.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

void measure_memory()
{
	long size = sysconf(_SC_PAGESIZE);
	printf("page size is: %ld\n", size);
}
