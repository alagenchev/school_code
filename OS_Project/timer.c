#include "timer.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
long long start_timer() {
                struct timeval tv;
                gettimeofday(&tv, NULL);
                return tv.tv_sec * 1000000 + tv.tv_usec;
}

long long stop_timer(long long start_time, char *label) {
                struct timeval tv;
                gettimeofday(&tv, NULL);
                long long end_time = tv.tv_sec * 1000000 + tv.tv_usec;
                printf("%s: %.5f sec\n", label, ((float) (end_time - start_time)) / (1000 * 1000));
                return end_time - start_time;
}

