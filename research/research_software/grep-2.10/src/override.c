#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <dlfcn.h>
#include "dmtcpaware.h"


char *strcpy (char *__restrict __dest, __const char *__restrict __src)
{
    //printf("in strcpy\n");
	char* return_value;
	typeof(strcpy) *old_strcpy;

	old_strcpy = dlsym(RTLD_NEXT, "strcpy");
	return_value = (*old_strcpy)(__dest, __src);

	return return_value;
}
__const void *memchr(__const void *__s, int __c, size_t __n)
{
    //printf("in memchr\n");
    typeof(memchr) *old_memchr;

    old_memchr = dlsym(RTLD_NEXT, "memchr");
    return (*old_memchr)(__s, __c, __n);

}

int vfprintf (FILE *__restrict __s, __const char *__restrict __format,_G_va_list __arg)
{
    //printf("in vfprintf\n");
    int return_value;
    typeof(vfprintf) *old_vfprintf;

    old_vfprintf = dlsym(RTLD_NEXT, "vfprintf");
    return_value = (*old_vfprintf)(__s, __format, __arg);

    return return_value;
}


char *fgets(char* str, int num, FILE* stream)
{
	char* return_value;
	typeof(fgets) *old_fgets;

	if(dmtcpIsEnabled()) {
		printf("OVERSEER: Making checkpoint.\n"); 
		dmtcpCheckpoint();
	} else
		printf("OVERSEER: DMTCP not enabled.\n");

	old_fgets = dlsym(RTLD_NEXT, "fgets");
	return_value = (*old_fgets)(str, num, stream);

	return return_value;
}

/*int printf(const char *format)
{
	int return_value;
	typeof(printf) *old_printf;
	return_value = (*old_printf)(format);
	
	return return_value;
}*/

int printf(const char *format, ...)
{
	va_list list;
	char *parg;
	int return_value;
	typeof(printf) *old_printf;

	printf("OVERSEER: Printf with arguments called.\n"); 
	
	va_start(list, format);
	vasprintf(&parg, format, list);
	va_end(list);
	
	old_printf = dlsym(RTLD_NEXT, "printf");
	return_value = (*old_printf)("%s", parg);

	free(parg);
	
	return return_value;
}

ssize_t write(int fd, const void *buf, size_t count)
{
	ssize_t return_value;
	typeof(write) *old_write;
	
	if(fd == 1)
		printf("OVERSEER: A write begins.\n");
	
	old_write = dlsym(RTLD_NEXT, "write");
	return_value = (*old_write)(fd, buf, count);

	if(fd == 1)
		printf("OVERSEER: A write ends.\n");	
	
	return return_value;
}
