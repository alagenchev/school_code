#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dlfcn.h>
#include "dmtcpaware.h"

extern FILE *freopen (__const char *__restrict __filename, __const char *__restrict __modes, FILE *__restrict __stream) __wur
{
	FILE * return_value;

	pid_t pid; int status;
	puts("OVERSEER: freopen");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(freopen) *old_freopen;
	old_freopen = dlsym(RTLD_NEXT, "freopen");
	return_value = (*old_freopen)(__filename, __modes, __stream);
	return return_value;
}
extern FILE *fopen64 (__const char *__restrict __filename, __const char *__restrict __modes) __wur
{
	FILE * return_value;

	pid_t pid; int status;
	puts("OVERSEER: fopen64");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(fopen64) *old_fopen64;
	old_fopen64 = dlsym(RTLD_NEXT, "fopen64");
	return_value = (*old_fopen64)(__filename, __modes);
	return return_value;
}
extern FILE *freopen64 (__const char *__restrict __filename, __const char *__restrict __modes, FILE *__restrict __stream) __wur
{
	FILE * return_value;

	pid_t pid; int status;
	puts("OVERSEER: freopen64");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(freopen64) *old_freopen64;
	old_freopen64 = dlsym(RTLD_NEXT, "freopen64");
	return_value = (*old_freopen64)(__filename, __modes, __stream);
	return return_value;
}
extern FILE *fdopen (int __fd, __const char *__modes)  __wur
{
	FILE * return_value;

	pid_t pid; int status;
	puts("OVERSEER: fdopen");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(fdopen) *old_fdopen;
	old_fdopen = dlsym(RTLD_NEXT, "fdopen");
	return_value = (*old_fdopen)(__fd, __modes);
	return return_value;
}
extern FILE *fopencookie (void *__restrict __magic_cookie, __const char *__restrict __modes, _IO_cookie_io_functions_t __io_funcs)  __wur
{
	FILE * return_value;

	pid_t pid; int status;
	puts("OVERSEER: fopencookie");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(fopencookie) *old_fopencookie;
	old_fopencookie = dlsym(RTLD_NEXT, "fopencookie");
	return_value = (*old_fopencookie)(__magic_cookie, __modes, __io_funcs);
	return return_value;
}
extern FILE *fmemopen (void *__s, size_t __len, __const char *__modes)  __wur
{
	FILE * return_value;

	pid_t pid; int status;
	puts("OVERSEER: fmemopen");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(fmemopen) *old_fmemopen;
	old_fmemopen = dlsym(RTLD_NEXT, "fmemopen");
	return_value = (*old_fmemopen)(__s, __len, __modes);
	return return_value;
}
extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc)  __wur
{
	FILE * return_value;

	pid_t pid; int status;
	puts("OVERSEER: open_memstream");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(open_memstream) *old_open_memstream;
	old_open_memstream = dlsym(RTLD_NEXT, "open_memstream");
	return_value = (*old_open_memstream)(__bufloc, __sizeloc);
	return return_value;
}
extern int __isoc99_fscanf (FILE *__restrict __stream, __const char *__restrict __format, ...) __wur
{
	int return_value;

	pid_t pid; int status;
	puts("OVERSEER: __isoc99_fscanf");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	va_list args;
	va_start(args, __format);
	return_value = vfscanf(__stream, __format, args);
	va_end(args);
	return return_value;
}
extern int __isoc99_scanf (__const char *__restrict __format, ...) __wur
{
	int return_value;

	pid_t pid; int status;
	puts("OVERSEER: __isoc99_scanf");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	va_list args;
	va_start(args, __format);
	return_value = vscanf(__format, args);
	va_end(args);
	return return_value;
}
extern int __isoc99_sscanf (__const char *__restrict __s, __const char *__restrict __format, ...) 
{
	int return_value;

	pid_t pid; int status;
	puts("OVERSEER: __isoc99_sscanf");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	va_list args;
	va_start(args, __format);
	return_value = vsscanf(__s, __format, args);
	va_end(args);
	return return_value;
}
extern int __isoc99_vfscanf (FILE *__restrict __s, __const char *__restrict __format, _G_va_list __arg) __wur
{
	int return_value;

	pid_t pid; int status;
	puts("OVERSEER: __isoc99_vfscanf");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(__isoc99_vfscanf) *old___isoc99_vfscanf;
	old___isoc99_vfscanf = dlsym(RTLD_NEXT, "__isoc99_vfscanf");
	return_value = (*old___isoc99_vfscanf)(__s, __format, __arg);
	return return_value;
}
extern int __isoc99_vscanf (__const char *__restrict __format, _G_va_list __arg) __wur
{
	int return_value;

	pid_t pid; int status;
	puts("OVERSEER: __isoc99_vscanf");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(__isoc99_vscanf) *old___isoc99_vscanf;
	old___isoc99_vscanf = dlsym(RTLD_NEXT, "__isoc99_vscanf");
	return_value = (*old___isoc99_vscanf)(__format, __arg);
	return return_value;
}
extern int __isoc99_vsscanf (__const char *__restrict __s, __const char *__restrict __format, _G_va_list __arg) 
{
	int return_value;

	pid_t pid; int status;
	puts("OVERSEER: __isoc99_vsscanf");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(__isoc99_vsscanf) *old___isoc99_vsscanf;
	old___isoc99_vsscanf = dlsym(RTLD_NEXT, "__isoc99_vsscanf");
	return_value = (*old___isoc99_vsscanf)(__s, __format, __arg);
	return return_value;
}
extern int fgetc (FILE *__stream)
{
	int return_value;

	pid_t pid; int status;
	puts("OVERSEER: fgetc");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(fgetc) *old_fgetc;
	old_fgetc = dlsym(RTLD_NEXT, "fgetc");
	return_value = (*old_fgetc)(__stream);
	return return_value;
}
extern int getc (FILE *__stream)
{
	int return_value;

	pid_t pid; int status;
	puts("OVERSEER: getc");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(getc) *old_getc;
	old_getc = dlsym(RTLD_NEXT, "getc");
	return_value = (*old_getc)(__stream);
	return return_value;
}
extern int getchar (void)
{
	int return_value;

	pid_t pid; int status;
	puts("OVERSEER: getchar");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(getchar) *old_getchar;
	old_getchar = dlsym(RTLD_NEXT, "getchar");
	return_value = (*old_getchar)();
	return return_value;
}
extern int getc_unlocked (FILE *__stream)
{
	int return_value;

	pid_t pid; int status;
	puts("OVERSEER: getc_unlocked");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(getc_unlocked) *old_getc_unlocked;
	old_getc_unlocked = dlsym(RTLD_NEXT, "getc_unlocked");
	return_value = (*old_getc_unlocked)(__stream);
	return return_value;
}
extern int getchar_unlocked (void)
{
	int return_value;

	pid_t pid; int status;
	puts("OVERSEER: getchar_unlocked");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(getchar_unlocked) *old_getchar_unlocked;
	old_getchar_unlocked = dlsym(RTLD_NEXT, "getchar_unlocked");
	return_value = (*old_getchar_unlocked)();
	return return_value;
}
extern int fgetc_unlocked (FILE *__stream)
{
	int return_value;

	pid_t pid; int status;
	puts("OVERSEER: fgetc_unlocked");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(fgetc_unlocked) *old_fgetc_unlocked;
	old_fgetc_unlocked = dlsym(RTLD_NEXT, "fgetc_unlocked");
	return_value = (*old_fgetc_unlocked)(__stream);
	return return_value;
}
extern int getw (FILE *__stream)
{
	int return_value;

	pid_t pid; int status;
	puts("OVERSEER: getw");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(getw) *old_getw;
	old_getw = dlsym(RTLD_NEXT, "getw");
	return_value = (*old_getw)(__stream);
	return return_value;
}
extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream) __wur
{
	char * return_value;

	pid_t pid; int status;
	puts("OVERSEER: fgets");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(fgets) *old_fgets;
	old_fgets = dlsym(RTLD_NEXT, "fgets");
	return_value = (*old_fgets)(__s, __n, __stream);
	return return_value;
}
extern char *gets (char *__s) __wur
{
	char * return_value;

	pid_t pid; int status;
	puts("OVERSEER: gets");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(gets) *old_gets;
	old_gets = dlsym(RTLD_NEXT, "gets");
	return_value = (*old_gets)(__s);
	return return_value;
}
extern char *fgets_unlocked (char *__restrict __s, int __n, FILE *__restrict __stream) __wur
{
	char * return_value;

	pid_t pid; int status;
	puts("OVERSEER: fgets_unlocked");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(fgets_unlocked) *old_fgets_unlocked;
	old_fgets_unlocked = dlsym(RTLD_NEXT, "fgets_unlocked");
	return_value = (*old_fgets_unlocked)(__s, __n, __stream);
	return return_value;
}
extern _IO_ssize_t __getdelim (char **__restrict __lineptr, size_t *__restrict __n, int __delimiter, FILE *__restrict __stream) __wur
{
	_IO_ssize_t return_value;

	pid_t pid; int status;
	puts("OVERSEER: __getdelim");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(__getdelim) *old___getdelim;
	old___getdelim = dlsym(RTLD_NEXT, "__getdelim");
	return_value = (*old___getdelim)(__lineptr, __n, __delimiter, __stream);
	return return_value;
}
extern _IO_ssize_t getline (char **__restrict __lineptr, size_t *__restrict __n, FILE *__restrict __stream) __wur
{
	_IO_ssize_t return_value;

	pid_t pid; int status;
	puts("OVERSEER: getline");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(getline) *old_getline;
	old_getline = dlsym(RTLD_NEXT, "getline");
	return_value = (*old_getline)(__lineptr, __n, __stream);
	return return_value;
}
extern size_t fread (void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream) __wur
{
	size_t return_value;

	pid_t pid; int status;
	puts("OVERSEER: fread");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(fread) *old_fread;
	old_fread = dlsym(RTLD_NEXT, "fread");
	return_value = (*old_fread)(__ptr, __size, __n, __stream);
	return return_value;
}
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream) __wur
{
	size_t return_value;

	pid_t pid; int status;
	puts("OVERSEER: fread_unlocked");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(fread_unlocked) *old_fread_unlocked;
	old_fread_unlocked = dlsym(RTLD_NEXT, "fread_unlocked");
	return_value = (*old_fread_unlocked)(__ptr, __size, __n, __stream);
	return return_value;
}
extern FILE *popen (__const char *__command, __const char *__modes) __wur
{
	FILE * return_value;

	pid_t pid; int status;
	puts("OVERSEER: popen");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(popen) *old_popen;
	old_popen = dlsym(RTLD_NEXT, "popen");
	return_value = (*old_popen)(__command, __modes);
	return return_value;
}
ssize_t read (int fd, void *buffer, size_t length)
{
	ssize_t return_value;

	pid_t pid; int status;
	puts("OVERSEER: read");
	while(1) {
	pid = fork();
	if(pid != 0) { wait(&status); if(status == 0) exit(0); else puts("OVERSEER: Restarting..."); } else break;
	}

	typeof(read) *old_read;
	old_read = dlsym(RTLD_NEXT, "read");
	return_value = (*old_read)(fd, buffer, length);
	return return_value;
}
