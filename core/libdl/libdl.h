#ifndef _LIBDL_H
#define _LIBDL_H

#include "tinyelf.h"

typedef struct {
   Elf_Ehdr* hdr;
   Elf_Phdr* phdrs;
   Elf_Shdr* shdrs;

   elfrelas** rela;
   elfsyms ** sym;


   Elf_Shdr* dyns;
   Elf_Dyn* dyntab;
   char* dynstr;
   len_t exec_size;
   char* exec;
} elf;

void *dlopen(const char* filename, int flags);
void *dlsym(void* handle, const char* symbol);
int dlclose(void *handle);

typedef struct {
   const char* path;
   elf* dl_elf;
   void* next;
   int_t nlink;
} dl;

#endif
