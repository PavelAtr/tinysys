#include "libdl.h"
#include "dlfcn.h"
#include <stddef.h>
#include <string.h>
#define __off_t_defined
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>

void elf_free(elf* e)
{
   if (!e) {
      return;
   }
   if (e->hdr) {
      free(e->hdr);
   }
   if (e->phdrs) {
      free(e->phdrs);
   }
   if (e->shdrs) {
      free(e->shdrs);
   }
   int ndx;
   for (ndx = 0; e->rela[ndx]; ndx++) {
      if (e->rela[ndx]) {
         if (e->rela[ndx]->relas) {
            free(e->rela[ndx]->relas);
         }
         free(e->rela[ndx]);
      }
   }
   for (ndx = 0; e->rela[ndx]; ndx++) {
      if (e->tlsrela[ndx]) {
         if (e->tlsrela[ndx]->relas) {
            free(e->tlsrela[ndx]->relas);
         }
         free(e->tlsrela[ndx]);
      }
   }
   if (e->rela)
      free(e->rela);
   for (ndx = 0; e->sym[ndx]; ndx++) {
      if (e->sym[ndx]) {
         if (e->sym[ndx]->syms) {
            free(e->sym[ndx]->syms);
         }
         if (e->sym[ndx]->symstr) {
            free(e->sym[ndx]->symstr);
         }
         free(e->sym[ndx]);
      }
   }
   if (e->sym)
      free(e->sym);
   if (e->dyntab) {
      free(e->dyntab);
   }
   if (e->dynstr) {
      free(e->dynstr);
   }
   if (e->exec) {
      munmap(e->exec, e->exec_size);
   }
}

int dl_load(dl* buf, const char* file)
{
   printf(MARK "Loading %s ... ", file);
   buf->path = file;
   buf->dl_elf = calloc(1, sizeof(elf));
   buf->dl_elf->hdr = elf_load_hdr(file);
   buf->dl_elf->phdrs = elf_load_phdrs(file, buf->dl_elf->hdr);
   buf->dl_elf->exec_size = elf_load_exec(file, buf->dl_elf->hdr,
         buf->dl_elf->phdrs, NULL, &buf->dl_elf->tls_size);
   buf->dl_elf->exec = mmap(NULL, buf->dl_elf->exec_size,
         PROT_READ | PROT_WRITE | PROT_EXEC,
         MAP_ANONYMOUS|MAP_SHARED, -1, 0);
   memset(buf->dl_elf->exec, 0x0, buf->dl_elf->exec_size);
   elf_load_exec(file, buf->dl_elf->hdr, buf->dl_elf->phdrs, buf->dl_elf->exec, &buf->dl_elf->tls_size);
   buf->dl_elf->shdrs = elf_load_shdrs(file, buf->dl_elf->hdr);
   if (!buf->dl_elf->hdr || !buf->dl_elf->phdrs || !buf->dl_elf->shdrs) {
      goto fail;
   }
   int start_ndx = 0;
   int i;
   int relacnt = elf_count_table(buf->dl_elf->hdr, buf->dl_elf->shdrs, SHT_RELA);
   
   buf->dl_elf->rela = malloc((relacnt + 1) * sizeof(elfrelas*));
   for (i = 0; i < relacnt; i++) {
      buf->dl_elf->rela[i] = malloc(sizeof(elfrelas));
      buf->dl_elf->rela[i]->head = elf_find_table(buf->dl_elf->hdr,
            buf->dl_elf->shdrs, &start_ndx, SHT_RELA);
      buf->dl_elf->rela[i]->relas = elf_load_table(file, buf->dl_elf->hdr,
            buf->dl_elf->rela[i]->head);
      start_ndx++;
   }
   buf->dl_elf->rela[i] = NULL;

   buf->dl_elf->tlsrela = malloc((relacnt + 1) * sizeof(tlsrelas*));   
   for (i = 0; i < relacnt; i++) {
      buf->dl_elf->tlsrela[i] = calloc(1, sizeof(elfrelas));
   }
   buf->dl_elf->tlsrela[i] = NULL;
   
   
   int symcnt = elf_count_table(buf->dl_elf->hdr, buf->dl_elf->shdrs,
         SHT_SYMTAB);
   int dyncnt = elf_count_table(buf->dl_elf->hdr, buf->dl_elf->shdrs,
         SHT_DYNSYM);
   buf->dl_elf->sym = malloc((symcnt + dyncnt + 1) * sizeof(elfsyms*));
   start_ndx = 0;
   for (i = 0; i < symcnt; i++) {
      buf->dl_elf->sym[i] = malloc(sizeof(elfsyms));
      buf->dl_elf->sym[i]->head = elf_find_table(buf->dl_elf->hdr, buf->dl_elf->shdrs,
            &start_ndx, SHT_SYMTAB);
      buf->dl_elf->sym[i]->syms = elf_load_table(file, buf->dl_elf->hdr,
            buf->dl_elf->sym[i]->head);
      buf->dl_elf->sym[i]->symstr = elf_load_strings(file, buf->dl_elf->hdr,
            buf->dl_elf->shdrs, buf->dl_elf->sym[i]->head);
      buf->dl_elf->sym[i]->dynamic = 0;
      start_ndx++;
   }
   start_ndx = 0;
   for (i = i; i < symcnt + dyncnt; i++) {
      buf->dl_elf->sym[i] = malloc(sizeof(elfsyms));
      buf->dl_elf->sym[i]->head = elf_find_table(buf->dl_elf->hdr, buf->dl_elf->shdrs,
            &start_ndx, SHT_DYNSYM);
      buf->dl_elf->sym[i]->syms = elf_load_table(file, buf->dl_elf->hdr,
            buf->dl_elf->sym[i]->head);
      buf->dl_elf->sym[i]->symstr = elf_load_strings(file, buf->dl_elf->hdr,
            buf->dl_elf->shdrs, buf->dl_elf->sym[i]->head);
      buf->dl_elf->sym[i]->dynamic = 1;
      start_ndx++;
   }
   buf->dl_elf->sym[i] = NULL;
   start_ndx = 0;
   buf->dl_elf->dyns = elf_find_table(buf->dl_elf->hdr, buf->dl_elf->shdrs,
         &start_ndx, SHT_DYNAMIC);
   buf->dl_elf->dyntab = elf_load_table(file, buf->dl_elf->hdr, buf->dl_elf->dyns);
   buf->dl_elf->dynstr = elf_load_strings(file, buf->dl_elf->hdr,
         buf->dl_elf->shdrs, buf->dl_elf->dyns);
   printf("%s\n", "OK");
   return 0;
fail:
   elf_free(buf->dl_elf);
   return -1;
}

dlhandle* relascope;
dlhandle* globalscope = NULL;

void* resolve(const char* symname)
{
   return dlsym(relascope, symname);
}

char* ldpath(const char* path, const char* file)
{
   short found = 0;
   size_t pathlen = 0;
   char* system_path = NULL;
   if (path) {
      system_path = strdup(path);
      pathlen = strlen(system_path);
   }
   char* rezult = malloc(pathlen + strlen(file) + 2);
   if (file[0] == '/' || !system_path) {
      strcpy(rezult, file);
      goto end;
   }
   char* dir = strtok(system_path, ":");
   while (dir != NULL) {
      strcpy(rezult, dir);
      strcpy(rezult + strlen(dir), file);
      dir =strtok(NULL, ":");
      struct stat st;
      if (stat(rezult, &st) != -1) {
         found = 1;
         break;
      }
   }
end:
   if (system_path) {
      free(system_path);
   }
   if (found) {
      return rezult;
   } else {
      return NULL;
   }
}

void *dlsym_single(void* hndl, const char* symbol);

void *dlopen(const char* filename, int flags)
{
   dl* prog = calloc(1, sizeof(dl));
   if (dl_load(prog, filename)) {
      goto fail;
   }
   dlhandle* handle = (dlhandle*)namedlist_add(NULL, prog,  prog->path);
   dlhandle* j;
   for (j = handle; j; j = j->next) {
      dl* s = j->obj;
      const char* file;
      int dtneed_ndx = 0;
      printf(MARK "Resolving dependencies of %s\n", s->path);
      while (file = elf_dtneed(s->dl_elf->dyns, s->dl_elf->dyntab,
                  s->dl_elf->dynstr, &dtneed_ndx)) {
		 char* path = ldpath(LD_PATH, file);
		 if (!path) {
            printf(MARK "%s not found in %s\n", file, LD_PATH);
		    goto fail;
	     }	 
         if (namedlist_get((namedlist*)handle, path)) {
    	    printf(MARK "NEEDED %s ALREDY\n", path);			  
            continue;
         }
         dl* lib;
         if ((lib = namedlist_get((namedlist*)globalscope, path)))
         {
			printf(MARK "InCache %s\n", path);			  
	     } else {
            lib = calloc(1,sizeof(dl));
            if (dl_load(lib, path)) {
                goto fail;
            }   
         }
         handle = (dlhandle*)namedlist_add((namedlist*)handle, lib, lib->path);
         lib->nlink++;
      }
   }   
   for (j = handle; j; j = j->next) {
	  dl* s  = j->obj;
	  if (s->status & DL_RELOCATED) {
		  continue;
	  }
      printf(MARK "Relocate %s\n", s->path);
      relascope = j;
      int sym_ndx;
      for (sym_ndx = 0; s->dl_elf->sym[sym_ndx]; sym_ndx++)
         if (s->dl_elf->sym[sym_ndx]->dynamic) {
            break;
         }
      int rela_ndx;
      for (rela_ndx = 0; s->dl_elf->rela[rela_ndx]; rela_ndx++) {
		 int tls_relas_count = 0; 
         elf_relocate(s->dl_elf->hdr, s->dl_elf->rela[rela_ndx]->head,
            s->dl_elf->rela[rela_ndx]->relas, s->dl_elf->sym[sym_ndx]->syms,
            s->dl_elf->sym[sym_ndx]->symstr, &tls_relas_count, s->dl_elf->exec, &resolve);
		 s->dl_elf->tlsrela[rela_ndx]->count = tls_relas_count;
         s->dl_elf->tlsrela[rela_ndx]->relas = elf_copy_tls_rela(s->dl_elf->rela[rela_ndx]->head,
            s->dl_elf->rela[rela_ndx]->relas, tls_relas_count);
      }
      s->status |= DL_RELOCATED;
   }
   for (j = handle; j != NULL; j = j->next) {
	  dl* s  = j->obj;
	  if (s->status & DL_INITED) {
		  continue;
	  }
      printf(MARK "Init %s\n", s->path);
      elf_init(s->dl_elf->exec, s->dl_elf->dyns, s->dl_elf->dyntab);
      void* (*allocate_tls)(size_t) = dlsym_single(j, "allocate_tls");
      if (allocate_tls) {
		  allocate_tls(s->dl_elf->tls_size);
	  }
      s->status |= DL_INITED;
   }
   for (j = handle->next; j != NULL; j = j->next) {
	  dl* s  = j->obj;
	  if (namedlist_get((namedlist*)globalscope, s->path)) {
		  continue;
	  }
      printf(MARK "Add to global scope %s\n", s->path);
      globalscope = (dlhandle*)namedlist_add((namedlist*)globalscope, s, s->path);
   }
   return handle;
fail:
   dlclose(handle);
   return NULL;
}

void *dlsym_single(void* hndl, const char* symbol)
{
   dlhandle* j = hndl;	
   dl* s = j->obj;
   void* sym;
      int sym_ndx;
      for (sym_ndx = 0; s->dl_elf->sym[sym_ndx]; sym_ndx++) {
         sym = elf_symbol(s->dl_elf->sym[sym_ndx]->head,
               s->dl_elf->sym[sym_ndx]->syms, s->dl_elf->sym[sym_ndx]->symstr,
               s->dl_elf->exec, symbol);
         if (sym) {
            return sym;
         }
      }
   return NULL;
}


void *dlsym(void* hndl, const char* symbol)
{
   dl* s;
   void* sym;
   dlhandle* j;
   for (j = hndl; j != NULL; j = j->next) {
	  s = j->obj; 
      int sym_ndx;
      for (sym_ndx = 0; s->dl_elf->sym[sym_ndx]; sym_ndx++) {
         sym = elf_symbol(s->dl_elf->sym[sym_ndx]->head,
               s->dl_elf->sym[sym_ndx]->syms, s->dl_elf->sym[sym_ndx]->symstr,
               s->dl_elf->exec, symbol);
         if (sym) {
            return sym;
         }
      }
   }
   return NULL;
}

int dlclose(void *hndl)
{
   dlhandle* j = hndl; 	
   dl* s = j->obj;
   if (!s) {
      return 0;
   }
   dlhandle* next = j;
   while (next) {
      next = j->next;
      s = j->obj;
      s->nlink--;
      if (s->nlink <= 0) {
         printf(MARK "Dlclose %s\n", s->path);
         elf_fini(s->dl_elf->exec, s->dl_elf->dyns, s->dl_elf->dyntab);
	     elf_free(s->dl_elf);
         free(s->dl_elf);
         free(s);
      }
      j->next = NULL;
      free(j->name);
      free(j);
      j = next;
   }
   return 0;
}

void dltls(void* handle, unsigned long module_id)
{
   dlhandle* j;
   dl* s;
   for (j = handle; j != NULL; j = j->next) {
	  s = j->obj;
      int rela_ndx;
      for (rela_ndx = 0; s->dl_elf->rela[rela_ndx]; rela_ndx++) {
         if (s->dl_elf->tlsrela[rela_ndx]->relas) {
			 int i;
			 for (i = 0; i < s->dl_elf->tlsrela[rela_ndx]->count; i++)
			 {
				 *(Elf_Xword*)(s->dl_elf->exec + s->dl_elf->tlsrela[rela_ndx]->relas[i].r_offset) = module_id;
// MARK ?? QUESTION	 printf(MARK "FOUND  TLS rela in %p %p=%p\n", s->dl_elf->tlsrela[rela_ndx]->relas, &s->dl_elf->tlsrela[rela_ndx]->relas[i], s->dl_elf->tlsrela[rela_ndx]->relas[i].r_offset);
			 }
         }

      }
	   s->dl_elf->tls_index = module_id;
   }
}
