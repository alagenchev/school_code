#include <unistd.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 

inline unsigned long long start_timer_i() 
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return time.tv_sec * 1000000000 + time.tv_nsec;
}

inline unsigned long long stop_timer_i(unsigned long long start_time, char *label) 
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);

    unsigned long long end_time = time.tv_sec * 1000000000 + time.tv_nsec;
    printf("%s: %.5f sec\n", label, ((float) (end_time - start_time)) / (1000 * 1000 * 1000));
    return end_time - start_time;
}



unsigned long long int rdtsc_i(void)
{
    unsigned long long int x;
    unsigned a, d;

    __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

    return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}

inline unsigned long long start_rdtsc_timer_i()
{
    return rdtsc_i();
}

inline unsigned long long stop_rdtsc_timer_i(unsigned long long start_time, char* label)
{
    unsigned long long end_time = rdtsc();
    //printf("rtdsc start is %llu, end is %llu\n", start_time, end_time);

    unsigned long long total_time = end_time - start_time;
    printf("RDTSC: %s: %llu cycles\n", label, total_time);
    return total_time;
}




void measure_memory()
{
	int num_pages = 0;
	long page_size = sysconf(_SC_PAGESIZE);
	void *ptr = NULL;

	void *ptr_to_use = NULL;

	do
	{
		ptr_to_use = ptr;

		ptr = (void *) calloc(num_pages , page_size);
		if(ptr)
		{
			free(ptr_to_use);
		}
		num_pages++;
	}while(ptr);

	num_pages--;

	printf("max pages: %d\n", sysconf(_SC_PHYS_PAGES));

	printf("available pages: %ld, page size is: %ld, for %ld available MB of memory\n", num_pages, page_size, ((num_pages * page_size)/1024)/1024);


	free(ptr_to_use);
	return;

	if(ptr_to_use== NULL)
	{
		printf("mem allocation failed\n");
		exit(1);
	}


	for(long i = 0; i < (num_pages * page_size)/sizeof(char); i ++)
	{
		*((char *)(ptr_to_use + i*sizeof(char))) = ~0;
	}

	void *new_page_address = NULL;

	printf("Trying /proc/sys/vm/drop_caches... (requires Linux 2.6.16+)\n");
	FILE *f = fopen("/proc/sys/vm/drop_caches", "w");
	if (!f)
	{
		printf("Error opening /proc/sys/vm/drop_caches: %s\n");
		return 0;
	}

	if (fprintf(f, "3\n") < 0)
	{
		printf("Error writing to file\n");
		return 0;
	}

	unsigned long long wall_time = start_timer_i();
	unsigned long long rdtsc_time = start_rdtsc_timer_i();

	for(long i = 0; i < num_pages;i++)
	{
		new_page_address = (ptr_to_use + i * page_size);
		char val = *((char *) new_page_address);
	}

	rdtsc_time = stop_rdtsc_timer_i(rdtsc_time, "page_alloc");

	stop_timer_i(wall_time, "page_alloc");

   // free(ptr_to_use);
}
