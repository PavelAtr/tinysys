#include <stdio.h>
#include <string.h>

int fputs(const char* s, FILE* stream)
{
   return fwrite(s, strlen(s), 1, stream);
}

int puts(const char* s)
{
   return fputs(s, stdout);
}
