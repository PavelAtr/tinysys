#include <stdio.h>
#include <unistd.h>

int fgetc(FILE* stream)
{
INIT_afds
   char ret;
   size_t len = fread(&ret, 1, 1, stream);
   if (len == 0) {
      return EOF;
   }
   return ret;
}

int getchar(void)
{
   return fgetc(stdin);
}
