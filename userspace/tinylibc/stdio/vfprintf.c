#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int vfprintf(FILE* stream, const char* format, va_list ap)
{
    va_list ap2;
    va_copy(ap2, ap);
    int size = vsnprintf(NULL, MAXSTRING, format, ap);
    char* str = malloc(size);
    size = vsnprintf(str, MAXSTRING, format, ap2);
    size_t ret =  fwrite(str, size, 1, stream);
    free(str);

    return ret;
}