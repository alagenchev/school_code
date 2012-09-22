#include "timer.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <rdtsc.h>

inline unsigned long long start_timer() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

inline unsigned long long stop_timer(unsigned long long start_time, char *label) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	unsigned long long end_time = tv.tv_sec * 1000000 + tv.tv_usec;
	printf("%s: %.5f sec\n", label, ((float) (end_time - start_time)) / (1000 * 1000));
	return end_time - start_time;
}

inline unsigned long long start_rdtsc_timer()
{
	return rdtsc();
}

inline unsigned long long stop_rdtsc_timer(unsigned long long start_time, char* label)
{
    unsigned long long end_time = rdtsc();
    printf("start is %llu, end is %llu\n", start_time, end_time);

	unsigned long long total_time = end_time - start_time;
	printf("RDTSC: %s: %llu cycles\n", label, total_time);
	return total_time;
}
