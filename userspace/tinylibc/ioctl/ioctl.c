#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <syscall.h>

int ioctl(int fd, unsigned long request, ...)
{
   INIT_FDS
   if (!fd_is_valid(fd)) {
      errno = EBADFD;
      return -1;
   }
   va_list vl;
   va_start(vl, request);
   long ret = syscall(SYS_IOCTL, fds[fd]->file, request, &vl);
   va_end(vl);
   return ret;
}