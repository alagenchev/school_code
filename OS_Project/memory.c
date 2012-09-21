#include <unistd.h>
void measure_memory()
{
	long size = sysconf(_SC_PAGESIZE);
	printf("page size is: %ld\n", size);
}
