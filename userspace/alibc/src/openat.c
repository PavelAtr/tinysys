#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int openat(int f, const char *pathname, int flags, ...)
{
   INIT_FDS
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   char* dir = fds[f]->file;
   return open(fullpath(dir, pathname), flags);
}
