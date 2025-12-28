#ifndef _XSTDIO_H
#define _XSTDIO_H
#include <libultraship.h>
#include <stdio.h>

#ifdef __OpenBSD__
#include <stdarg.h> /* va_list */
#endif

#define FLAGS_SPACE 1
#define FLAGS_PLUS 2
#define FLAGS_MINUS 4
#define FLAGS_HASH 8
#define FLAGS_ZERO 16
typedef char *outfun(char*,const char*,size_t);

int _Printf(outfun prout, char *arg, const char *fmt, va_list args);
void _Litob(_Pft *args, char type);
void _Ldtob(_Pft* px, char code);

#endif
