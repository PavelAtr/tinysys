#ifndef _ERRNO_H
#define _ERRNO_H

int get_errno(void);
int set_errno(int err);

#define errno get_errno()

#define ESUCCESS 0
#define EPERM 1
#define EACCESS 2
#define ENOENT 3
#define ENOMEM 4
#define EEXIST 5
#define ENOTDIR 6
#define ENOTSUP 7
#define EISDIR 8
#define ESPIPE 9
#define ERANGE 10
#define BADFD 11

#endif
