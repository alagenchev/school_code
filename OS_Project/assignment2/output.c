#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <dlfcn.h>
#include "dmtcpaware.h"

extern int scanf (__const char *__restrict __format, ...) __wur
{
	int return_value;
	typeof(scanf) *old_scanf;

	if(dmtcpIsEnabled())
	{
		dmtcpCheckpoint();
	}

	va_list args;
	va_end(args);
	old_scanf = dlsym(RTLD_NEXT, "scanf");
	return_value = (*old_scanf)(__format, args,);
	return return_value;
}
