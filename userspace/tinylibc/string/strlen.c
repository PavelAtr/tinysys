#include <string.h>

size_t strlen(const char *s)
{
   size_t len;
   for (len = 0; s[len] != '\0'; len++);
   return len;
}
