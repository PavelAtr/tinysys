#ifndef _LOOP_H
#define _LOOP_H
#include "../../core/include/tinysys.h"

typedef struct {
	const char* filename;
	len_t offset;
	len_t pos;
} loop;

len_t loop_read(void* devparam, void* ptr, len_t size);
len_t loop_write(void* devparam, const void* ptr, len_t size);
void loop_seek(void* devparam, len_t offset);
errno_t loop_ioctl(void* devparam, ulong_t request, ...);

#endif