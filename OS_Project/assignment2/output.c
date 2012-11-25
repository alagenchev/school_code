#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <dlfcn.h>
#include "dmtcpaware.h"



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
/*
extern FILE *fopen (__const char *__restrict __filename, __const char *__restrict __modes) __wur
{
	FILE * return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}



	typeof(fopen) *old_fopen;
	old_fopen = dlsym(RTLD_NEXT, "fopen");
	return_value = (*old_fopen)(__filename, __modes);
	return return_value;
}
*/
/*
extern FILE *freopen (__const char *__restrict __filename, __const char *__restrict __modes, FILE *__restrict __stream) __wur
{
	FILE * return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}



	typeof(freopen) *old_freopen;
	old_freopen = dlsym(RTLD_NEXT, "freopen");
	return_value = (*old_freopen)(__filename, __modes, __stream);
	return return_value;
}

extern FILE *fopen64 (__const char *__restrict __filename, __const char *__restrict __modes) __wur
{
	FILE * return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}



	typeof(fopen64) *old_fopen64;
	old_fopen64 = dlsym(RTLD_NEXT, "fopen64");
	return_value = (*old_fopen64)(__filename, __modes);
	return return_value;
}

extern FILE *freopen64 (__const char *__restrict __filename, __const char *__restrict __modes, FILE *__restrict __stream) __wur
{
	FILE * return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}



	typeof(freopen64) *old_freopen64;
	old_freopen64 = dlsym(RTLD_NEXT, "freopen64");
	return_value = (*old_freopen64)(__filename, __modes, __stream);
	return return_value;
}
extern FILE *fdopen (int __fd, __const char *__modes)  __wur
{
	FILE * return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}



	typeof(fdopen) *old_fdopen;
	old_fdopen = dlsym(RTLD_NEXT, "fdopen");
	return_value = (*old_fdopen)(__fd, __modes);
	return return_value;
}
*/

extern FILE *fopencookie (void *__restrict __magic_cookie, __const char *__restrict __modes, _IO_cookie_io_functions_t __io_funcs)  __wur
{
	FILE * return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}



	typeof(fopencookie) *old_fopencookie;
	old_fopencookie = dlsym(RTLD_NEXT, "fopencookie");
	return_value = (*old_fopencookie)(__magic_cookie, __modes, __io_funcs);
	return return_value;
}
/*
extern FILE *fmemopen (void *__s, size_t __len, __const char *__modes)  __wur
{
	FILE * return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: fmemopen\n");
	fclose(fp);

	typeof(fmemopen) *old_fmemopen;
	old_fmemopen = dlsym(RTLD_NEXT, "fmemopen");
	return_value = (*old_fmemopen)(__s, __len, __modes);
	return return_value;
}
*/
extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc)  __wur
{
	FILE * return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: open_memstream\n");
	fclose(fp);

	typeof(open_memstream) *old_open_memstream;
	old_open_memstream = dlsym(RTLD_NEXT, "open_memstream");
	return_value = (*old_open_memstream)(__bufloc, __sizeloc);
	return return_value;
}

/*
extern int __isoc99_fscanf (FILE *__restrict __stream, __const char *__restrict __format, ...) __wur
{
	int return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: __isoc99_fscanf\n");
	fclose(fp);

	va_list args;
	va_start(args, __format);
	return_value = vfscanf(__stream, __format, args);
	va_end(args);
	return return_value;
}
*/
extern int __isoc99_scanf (__const char *__restrict __format, ...) __wur
{
	int return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: __isoc99_scanf\n");
	fclose(fp);

	va_list args;
	va_start(args, __format);
	return_value = vscanf(__format, args);
	va_end(args);
	return return_value;
}
extern int __isoc99_sscanf (__const char *__restrict __s, __const char *__restrict __format, ...) 
{
	int return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: __isoc99_sscanf\n");
	fclose(fp);

	va_list args;
	va_start(args, __format);
	return_value = vsscanf(__s, __format, args);
	va_end(args);
	return return_value;
}
extern int __isoc99_vfscanf (FILE *__restrict __s, __const char *__restrict __format, _G_va_list __arg) __wur
{
	int return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: __isoc99_vfscanf\n");
	fclose(fp);

	typeof(__isoc99_vfscanf) *old___isoc99_vfscanf;
	old___isoc99_vfscanf = dlsym(RTLD_NEXT, "__isoc99_vfscanf");
	return_value = (*old___isoc99_vfscanf)(__s, __format, __arg);
	return return_value;
}
extern int __isoc99_vscanf (__const char *__restrict __format, _G_va_list __arg) __wur
{
	int return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: __isoc99_vscanf\n");
	fclose(fp);

	typeof(__isoc99_vscanf) *old___isoc99_vscanf;
	old___isoc99_vscanf = dlsym(RTLD_NEXT, "__isoc99_vscanf");
	return_value = (*old___isoc99_vscanf)(__format, __arg);
	return return_value;
}
extern int __isoc99_vsscanf (__const char *__restrict __s, __const char *__restrict __format, _G_va_list __arg) 
{
	int return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: __isoc99_vsscanf\n");
	fclose(fp);

	typeof(__isoc99_vsscanf) *old___isoc99_vsscanf;
	old___isoc99_vsscanf = dlsym(RTLD_NEXT, "__isoc99_vsscanf");
	return_value = (*old___isoc99_vsscanf)(__s, __format, __arg);
	return return_value;
}
/*
extern int fgetc (FILE *__stream)
{
	int return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: fgetc\n");
	fclose(fp);

	typeof(fgetc) *old_fgetc;
	old_fgetc = dlsym(RTLD_NEXT, "fgetc");
	return_value = (*old_fgetc)(__stream);
	return return_value;
}
*/
extern int getc (FILE *__stream)
{
	int return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: getc\n");
	fclose(fp);

	typeof(getc) *old_getc;
	old_getc = dlsym(RTLD_NEXT, "getc");
	return_value = (*old_getc)(__stream);
	return return_value;
}
extern int getchar (void)
{
	int return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: getchar\n");
	fclose(fp);

	typeof(getchar) *old_getchar;
	old_getchar = dlsym(RTLD_NEXT, "getchar");
	return_value = (*old_getchar)();
	return return_value;
}

extern int getc_unlocked (FILE *__stream)
{
	int return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: getc_unlocked\n");
	fclose(fp);

	typeof(getc_unlocked) *old_getc_unlocked;
	old_getc_unlocked = dlsym(RTLD_NEXT, "getc_unlocked");
	return_value = (*old_getc_unlocked)(__stream);
	return return_value;
}
extern int getchar_unlocked (void)
{
	int return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: getchar_unlocked\n");
	fclose(fp);

	typeof(getchar_unlocked) *old_getchar_unlocked;
	old_getchar_unlocked = dlsym(RTLD_NEXT, "getchar_unlocked");
	return_value = (*old_getchar_unlocked)();
	return return_value;
}
/*
extern int fgetc_unlocked (FILE *__stream)
{
	int return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: fgetc_unlocked\n");
	fclose(fp);

	typeof(fgetc_unlocked) *old_fgetc_unlocked;
	old_fgetc_unlocked = dlsym(RTLD_NEXT, "fgetc_unlocked");
	return_value = (*old_fgetc_unlocked)(__stream);
	return return_value;
}*/
extern int getw (FILE *__stream)
{
	int return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: getw\n");
	fclose(fp);

	typeof(getw) *old_getw;
	old_getw = dlsym(RTLD_NEXT, "getw");
	return_value = (*old_getw)(__stream);
	return return_value;
}
/*
extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream) __wur
{
	char * return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: fgets\n");
	fclose(fp);

	typeof(fgets) *old_fgets;
	old_fgets = dlsym(RTLD_NEXT, "fgets");
	return_value = (*old_fgets)(__s, __n, __stream);
	return return_value;
}
*/
extern char *gets (char *__s) __wur
{
	char * return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: gets\n");
	fclose(fp);

	typeof(gets) *old_gets;
	old_gets = dlsym(RTLD_NEXT, "gets");
	return_value = (*old_gets)(__s);
	return return_value;
}
/*
extern char *fgets_unlocked (char *__restrict __s, int __n, FILE *__restrict __stream) __wur
{
	char * return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: fgets_unlocked\n");
	fclose(fp);

	typeof(fgets_unlocked) *old_fgets_unlocked;
	old_fgets_unlocked = dlsym(RTLD_NEXT, "fgets_unlocked");
	return_value = (*old_fgets_unlocked)(__s, __n, __stream);
	return return_value;
}
*/
extern _IO_ssize_t __getdelim (char **__restrict __lineptr, size_t *__restrict __n, int __delimiter, FILE *__restrict __stream) __wur
{
	_IO_ssize_t return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: __getdelim\n");
	fclose(fp);

	typeof(__getdelim) *old___getdelim;
	old___getdelim = dlsym(RTLD_NEXT, "__getdelim");
	return_value = (*old___getdelim)(__lineptr, __n, __delimiter, __stream);
	return return_value;
}
/*
extern _IO_ssize_t getdelim (char **__restrict __lineptr, size_t *__restrict __n, int __delimiter, FILE *__restrict __stream) __wur
{
	_IO_ssize_t return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: getdelim\n");
	fclose(fp);

	typeof(getdelim) *old_getdelim;
	old_getdelim = dlsym(RTLD_NEXT, "getdelim");
	return_value = (*old_getdelim)(__lineptr, __n, __delimiter, __stream);
	return return_value;
}
*/

extern _IO_ssize_t getline (char **__restrict __lineptr, size_t *__restrict __n, FILE *__restrict __stream) __wur
{
	_IO_ssize_t return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: getline\n");
	fclose(fp);

	typeof(getline) *old_getline;
	old_getline = dlsym(RTLD_NEXT, "getline");
	return_value = (*old_getline)(__lineptr, __n, __stream);
	return return_value;
}

/*
extern size_t fread (void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream) __wur
{
	size_t return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: fread\n");
	fclose(fp);

	typeof(fread) *old_fread;
	old_fread = dlsym(RTLD_NEXT, "fread");
	return_value = (*old_fread)(__ptr, __size, __n, __stream);
	return return_value;
}
*/
/*
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream) __wur
{
	size_t return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: fread_unlocked\n");
	fclose(fp);

	typeof(fread_unlocked) *old_fread_unlocked;
	old_fread_unlocked = dlsym(RTLD_NEXT, "fread_unlocked");
	return_value = (*old_fread_unlocked)(__ptr, __size, __n, __stream);
	return return_value;
}
*/
extern FILE *popen (__const char *__command, __const char *__modes) __wur
{
	FILE * return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}


	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: popen\n");
	fclose(fp);

	typeof(popen) *old_popen;
	old_popen = dlsym(RTLD_NEXT, "popen");
	return_value = (*old_popen)(__command, __modes);
	return return_value;
}
/*
ssize_t read (int fd, void *buffer, size_t length)
{
	ssize_t return_value;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}

	FILE *fp;
	fp=fopen("trace.txt","a");
	fprintf(fp,"REPLACED: read\n");
	fclose(fp);
	typeof(read) *old_read;
	old_read = dlsym(RTLD_NEXT, "read");
	return_value = (*old_read)(fd, buffer, length);
	return return_value;
}
*/
