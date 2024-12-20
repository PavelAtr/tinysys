#include <sys/types.h>

#ifndef _STAT_H
#define _STAT_H

#define S_IFMT     0170000
#define S_IFSOCK   0140000
#define S_IFLNK    0120000
#define S_IFREG    0100000
#define S_IFBLK    0060000
#define S_IFDIR    0040000
#define S_IFCHR    0020000
#define S_IFIFO    0010000

#define S_IRWXU  00700
#define S_IRUSR  00400
#define S_IWUSR  00200
#define S_IXUSR  00100
#define S_IRWXG  00070
#define S_IRGRP  00040
#define S_IWGRP  00020
#define S_IXGRP  00010
#define S_IRWXO  00007
#define S_IROTH  00004
#define S_IWOTH  00002
#define S_IXOTH  00001
#define S_ISUID  04000
#define S_ISGID  02000
#define S_ISVTX  01000

#define S_ISREG(mode) (mode & S_IFREG)
#define S_ISDIR(mode) (mode & S_IFDIR)
#define S_ISLNK(mode) (mode & S_IFLNK)

struct stat {
  mode_t	st_mode;     /* File type and mode */
  uid_t	st_uid;      /* User ID of owner */
  gid_t	st_gid;      /* Group ID of owner */
  size_t	st_size;
  short	st_major;
  short	st_minor;
  dev_t	st_dev;
  long	st_ino;
  time_t      st_atime;
  time_t      st_mtime;
  time_t      st_ctime;
};

int stat(const char* path, struct stat* statbuf);
int lstat(const char* pathname, struct stat* statbuf);
extern mode_t global_mask;
mode_t umask(mode_t mask);
int mknod(const char *pathname, mode_t mode, dev_t dev);
int mkdir(const char *pathname, mode_t mode);
int chmod(const char *pathname, mode_t mode);

#endif
