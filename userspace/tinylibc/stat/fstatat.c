#include <syscall.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int fstatat(int f, const char* pathname,
                struct stat* statbuf, int flags)
{
   if (!fd_is_valid(f) || !fds[f].stream->file) {
      errno = BADFD;
      return -1;
   }
   char* dir = fds[f].stream->file;
   const char* file = pathname;
   if (pathname == NULL || flags & AT_EMPTY_PATH)
   {
      file = NULL;
   }
   if (flags & AT_FDCWD)
   {
      dir = get_current_dir_name();
   }
   return syscall(SYS_FSTAT, fullpath(dir, file), statbuf);
}