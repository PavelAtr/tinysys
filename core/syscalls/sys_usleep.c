#include <tinysys.h>

#ifndef UEFI

#include <unistd.h>

#endif

int sys_usleep(long_t usec)
{
	sys_printf("USLEEP\n");
	switch_context;
    return  0;
}