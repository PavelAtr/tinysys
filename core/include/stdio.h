#ifndef _STDIO_H
#define _STDIO_H

#include <stddef.h>
#include <stdarg.h>
#include <sys/types.h>

typedef struct {
    char* file;
    size_t size;
    size_t pos;
    unsigned char flags;
} FILE;

#define FILE_EOF 0x01
#define FILE_ERROR 0x02
#define FILE_INFINITY 0x04

extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;

#define MAXSTRING (short)-1

FILE* fopen(const char* pathname, const char* mode);
FILE *fdopen(int fd, const char *mode);
size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);
int fclose(FILE *stream);
int fseek(FILE* stream, long offset, int whence);
long ftell(FILE* stream);
void rewind(FILE* stream);
int getc(FILE* stream);
int fputs(const char* s, FILE* stream);
int puts(const char* s);
int putchar(int c);
int fputc(int c, FILE *stream);
#define putc(c, s) fputc(c, s)
int putchar(int c);
int vsnprintf(char* str, size_t size,  const char* format, va_list ap);
int snprintf(char* str, size_t size, const char* format, ...);
void _exit(int status);
int fprintf(FILE* stream, const char* format, ...);
void clearerr(FILE *stream);
int feof(FILE *stream);
int ferror(FILE *stream);
int vfprintf(FILE* stream, const char* format, va_list ap);
int vsprintf(char* str, const char* format, va_list ap);
char *fgets(char* s, int size, FILE* stream);
#define EOF -1

#endif