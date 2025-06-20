//
// scanf.c
//
// Formatted input
//
// Copyright (C) 2011 Michael Ringgaard. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. Neither the name of the project nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
//

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int _input(FILE *stream, const unsigned char *format, va_list arglist);

int fscanf(FILE *stream, const char *fmt, ...)
{
   int rc;
   va_list args;
   va_start(args, fmt);
   rc = _input(stream, fmt, args);
   return rc;
}

int vfscanf(FILE *stream, const char *fmt, va_list args)
{
   return _input(stream, fmt, args);
}

int scanf(const char *fmt, ...)
{
   int rc;
   va_list args;
   va_start(args, fmt);
   rc = _input(stdin, fmt, args);
   return rc;
}

int vscanf(const char *fmt, va_list args)
{
   return _input(stdin, fmt, args);
}

int sscanf(const char *buffer, const char *fmt, ...)
{
   int rc;
   va_list args;
   amemfile str;
   va_start(args, fmt);
   str.membuf = (char *) buffer;
   str.size = strlen(buffer);
   rc = _input((FILE*)&str, fmt, args);
   return rc;
}

int vsscanf(const char *buffer, const char *fmt, va_list args)
{
   int rc;
   amemfile str;
   str.membuf = (char *) buffer;
   str.size = strlen(buffer);
   rc = _input((FILE*)&str, fmt, args);
   return rc;
}

