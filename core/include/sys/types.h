#ifndef _TYPES_H
#define _TYPES_H

typedef unsigned int uid_t;
typedef unsigned int gid_t;
typedef unsigned int mode_t;

#ifdef UEFI
typedef unsigned long long size_t;
typedef unsigned long long off_t;
typedef long long ssize_t;
typedef unsigned long long time_t;
#else
typedef unsigned long size_t;
typedef long  off_t;
typedef long ssize_t;
typedef long time_t;
#endif
typedef int pid_t;
typedef unsigned long dev_t;


typedef long long long_t;
typedef unsigned long long ulong_t;
typedef unsigned long long addr_t;
typedef unsigned int len_t;
typedef unsigned int counter_t;
typedef int int_t;
typedef int errno_t;
typedef unsigned char bool_t;
typedef unsigned int u_int32_t;
typedef int int32_t;


#endif
