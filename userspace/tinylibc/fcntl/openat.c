#include <syscall.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int openat(int f, const char *pathname, int flags, ...)
{
   if (!fd_is_valid(f) || !fds[f].stream->file) {
      errno = EBADFD;
      return -1;
   }
   char* dir = fds[f].stream->file;
   const char* file = pathname;
   return open(fullpath(dir, file), flags);
}