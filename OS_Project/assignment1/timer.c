#include "timer.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <rdtsc.h>
#include <time.h>

inline unsigned long long start_timer() 
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return time.tv_sec * 1000 * 1000 * 1000 + time.tv_nsec;
}

inline unsigned long long stop_timer(unsigned long long start_time, char *label) 
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);

    unsigned long long end_time = time.tv_sec * 1000 * 1000 * 1000 + time.tv_nsec;
    printf("%s: %.5f sec\n", label, ((float) (end_time - start_time)) / (1000 * 1000 * 1000));
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
