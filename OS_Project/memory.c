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
	printf("%s, %.10f\n", label, ((float) (end_time - start_time)) / (1000 * 1000 * 1000));
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
	unsigned long long end_time = rdtsc_i();
	//printf("rtdsc start is %llu, end is %llu\n", start_time, end_time);

	unsigned long long total_time = end_time - start_time;
	printf("RDTSC, %s, %llu\n", label, total_time);
	return total_time;
}




void measure_memory()
{
	long long iterations[] = {1, 2,100, 200, 300, 400};
	int num_pages = 0;
	long page_size = sysconf(_SC_PAGESIZE);
	void *ptr = NULL;

	void *ptr_to_use = NULL;


	//	printf("max pages: %d\n", sysconf(_SC_PHYS_PAGES));

	//	printf("available pages: %ld, page size is: %ld, for %ld available MB of memory\n", num_pages, page_size, ((num_pages * page_size)/1024)/1024);
	unsigned long long wall_time = start_timer_i();
		unsigned long long rdtsc_time = start_rdtsc_timer_i();


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
		rdtsc_time = stop_rdtsc_timer_i(rdtsc_time, "page_alloc");
		stop_timer_i(wall_time, "page_alloc");


		num_pages--;


		if(ptr_to_use== NULL)
		{
			printf("mem allocation failed\n");
			exit(1);
		}


		long upper = (num_pages * page_size)/sizeof(char*);


	wall_time = start_timer_i();
	 rdtsc_time = start_rdtsc_timer_i();



			for(long i = 0; i < upper ; i ++)
			{
				*((char *)(ptr_to_use + i*sizeof(char*))) = ~0;
			}
		//printf("\n\nIterations = %d\n", iterations[i]);

		rdtsc_time = stop_rdtsc_timer_i(rdtsc_time, "page_access");
		stop_timer_i(wall_time, "page_access");

		free(ptr_to_use);


	/*
	   for(long i = 0; i < upper ; i ++)
	   {
	   printf("i: %d, val: %d\n", i, *((char *)(ptr_to_use + i*sizeof(char*))) & 1);
	   }
	 */

}
