#include <string.h>

char* temp;
char* rez;
char* copy;

char* strtok(char* str, const char* delim)
{
   if (str) {
      temp = str;
      rez = str;
      copy = str;
   } else {
      rez = temp;
   }
   if (!rez) {
      return NULL;
   }
   temp = strstr(temp, delim);
   if (temp) {
      copy[temp - copy] = '\0';
      temp = temp + strlen(delim);
   }
   return rez;
}