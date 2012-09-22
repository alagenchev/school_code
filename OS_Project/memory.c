#include <unistd.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <timer.h>

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

	unsigned long long wall_time = start_timer();
	unsigned long long rdtsc_time = start_rdtsc_timer();

	for(long i = 0; i < num_pages;i++)
	{
		new_page_address = (ptr_to_use + i * page_size);
		char val = *((char *) new_page_address);
	}

	rdtsc_time = stop_rdtsc_timer(rdtsc_time, "page_alloc");

	stop_timer(wall_time, "page_alloc");

}
