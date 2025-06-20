#include <syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int mknod(const char *pathname, mode_t mode, dev_t dev)
{
   return (int)asyscall(SYS_MKNOD, fullpath(get_current_dir_name(), pathname), mode & mask(), 0, 0, 0, 0);
}
