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
	unsigned long long total_time = rdtsc() - start_time;
	printf("RDTSC: %s: %.5f cycles\n", label, ((float) total_time));
	return total_time;
}
