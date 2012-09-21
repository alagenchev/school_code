#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/mman.h> 

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


	unsigned long long wall_time = start_timer();
	unsigned long long rdtsc_time = start_rdtsc_timer();

	while( read(fd, buffer, 255)!=0)
	{
	}

	rdtsc_time = stop_rdtsc_timer(rdtsc_time, "read_file_hdd");

	stop_timer(wall_time, "read_file_hdd");

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

	wall_time = start_timer();
	rdtsc_time = start_rdtsc_timer();
	rdtsc_time = stop_rdtsc_timer(rdtsc_time, "read_file_mmap");

	stop_timer(wall_time, "read_file_mmap");
	for (int i = 0; i < size; i++) 
	{
		mapped[i];
	}

	close(fd);

	printf("done\n");
}
