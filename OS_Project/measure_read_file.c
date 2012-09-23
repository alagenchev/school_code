#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/mman.h> 
#include <time.h>


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



unsigned long long int rdtsc(void)
{
    unsigned long long int x;
    unsigned a, d;

    __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

    return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}

inline unsigned long long start_rdtsc_timer_i()
{
    return rdtsc();
}

inline unsigned long long stop_rdtsc_timer_i(unsigned long long start_time, char* label)
{
    unsigned long long end_time = rdtsc();
    printf("rtdsc start is %llu, end is %llu\n", start_time, end_time);

    unsigned long long total_time = end_time - start_time;
    printf("RDTSC: %s: %llu cycles\n", label, total_time);
    return total_time;
}



void measure_read_file()
{

    char buffer[255];
    int fd;
    int status;
    struct stat s;
    size_t size;
    const char* mapped;

    system("truncate -s 10M test.file");
    fd = open("test.file",O_RDONLY);
    printf("descriptor for read is %d\n", fd);


    unsigned long long wall_time = start_timer_i();
    unsigned long long rdtsc_time = start_rdtsc_timer_i();

    while( read(fd, buffer, 255)!=0)
    {
    }

    rdtsc_time = stop_rdtsc_timer_i(rdtsc_time, "read_file_hdd");

    stop_timer_i(wall_time, "read_file_hdd");

    close(fd);

    system("truncate -s 10M test2.file");
    fd = open("test2.file",O_RDONLY);
    //printf("descriptor for mmap read is %d\n", fd);


    /* Get the size of the file. */
    status = fstat (fd, & s);
    size = s.st_size;
    //printf("size is %d\n", size);

    mapped = mmap (0, size, PROT_READ, MAP_SHARED, fd, 0);

    if(mapped == MAP_FAILED)
    {
        printf("map failed\n");
        exit(1);
    }

    printf("start again\n");

    rdtsc_time = start_rdtsc_timer_i();

    wall_time = start_timer_i();

    for (int i = 0; i < size; i++) 
    {
        char c = mapped[i];
    }

    stop_timer_i(wall_time, "read_file_hdd_i");
    stop_rdtsc_timer_i(rdtsc_time, "read_file_hdd");

    //printf("time: sec %ul, nanosec %ld\n", end.tv_sec, end.tv_nsec);

    close(fd);

    printf("done\n");
}
