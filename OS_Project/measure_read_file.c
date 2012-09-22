#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/mman.h> 
#include <time.h>


inline void start_timer_ivan(struct timespect *time) 
{
    clock_gettime(CLOCK_MONOTONIC, time);

}

unsigned long long int rdtsc(void)
{
    unsigned long long int x;
    unsigned a, d;

    __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

    return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
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


    //unsigned long long wall_time = start_timer();
    //unsigned long long rdtsc_time = start_rdtsc_timer();

    while( read(fd, buffer, 255)!=0)
    {
    }

    //rdtsc_time = stop_rdtsc_timer(rdtsc_time, "read_file_hdd");

    //stop_timer(wall_time, "read_file_hdd");

    close(fd);

    system("truncate -s 10M test2.file");
    fd = open("test2.file",O_RDONLY);
    printf("descriptor for mmap read is %d\n", fd);


    /* Get the size of the file. */
    status = fstat (fd, & s);
    size = s.st_size;
    printf("size is %d\n", size);

    mapped = mmap (0, size, PROT_READ, MAP_SHARED, fd, 0);

    if(mapped == MAP_FAILED)
    {
        printf("map failed\n");
        exit(1);
    }

    printf("start again\n");

    //printf("rdtsc: %llu\n",rdtsc());
    struct timespec time;

    //start_timer_ivan(&time);


    //printf("time: sec %ul, nanosec %ld \n", time.tv_sec, time.tv_nsec);
    
    printf("rdtsc: %llu\n",rdtsc());
    unsigned long long rdtsc_time = start_rdtsc_timer();
    for (int i = 0; i < size; i++) 
    {
        char c = mapped[i];
    }
    stop_rdtsc_timer(rdtsc_time, "read_file_hdd");

    //struct timespec end;

    //start_timer_ivan(&end);

    //printf("time: sec %ul, nanosec %ld\n", end.tv_sec, end.tv_nsec);

    printf("rdtsc2: %llu\n",rdtsc());
    close(fd);

    printf("done\n");
}
