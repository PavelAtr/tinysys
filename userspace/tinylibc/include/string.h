#ifndef _STRING_H
#define _STRING_H
#include <stddef.h>

size_t strlen(const char *s);
char* strstr(const char *haystack, const char *needle);
int strcmp(const char *s1, const char *s2);
char* strcpy(char* dst, const char* src);
char* strdup(const char *s);
void* memcpy(void* dest, const void* src, size_t n);
char* strerror(int errnum);
char* strtok(char* str, const char* delim);
void *memcpy(void* dest, const void* src, size_t n);
void *memset(void* s, int c, size_t n);
char *strcat(char* dst, const char* src);
char *strrchr(const char *s, int c);
#define memmove(dest, src, size) __builtin_memmove(dest, src, size)
char *stpcpy(char* dst, const char* src);
char *strchr(const char *s, int c);

#endif
