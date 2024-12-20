#include "loop.h"

len_t loop_read(void* devparam, void* ptr, len_t size)
{
   return sys_fread(((loop*) devparam)->filename, ptr, size,
         ((loop*) devparam)->offset + ((loop*) devparam)->pos);
}

len_t loop_write(void* devparam, const void* ptr, len_t size)
{
   return sys_fwrite(((loop*) devparam)->filename, ptr, size,
         ((loop*) devparam)->offset + ((loop*) devparam)->pos);
}

void loop_seek(void* devparam, len_t offset)
{
   ((loop*) devparam)->pos = offset;
}

errno_t loop_ioctl(void* devparam, ulong_t request, ...)
{
   return 0;
}
