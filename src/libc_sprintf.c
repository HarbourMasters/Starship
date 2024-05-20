#include "sys.h"

char D_800C7C80[] = "$Id: sprintf.c,v 1.5 1997/03/19 02:28:53 hayakawa Exp $";

char* proutSprintf(char* dst, const char* fmt, size_t size) {
    return (char*) ((uintptr_t) memcpy(dst, fmt, size) + size);
}

// s32 vsprintf(char* dst, const char* fmt, va_list args) {
//     s32 ret = _Printf((outfun*) proutSprintf, dst, fmt, args);
//
//     if (ret > -1) {
//         dst[ret] = 0;
//     }
//     return ret;
// }
//
// int sprintf(char* s, const char* fmt, ...) {
//     s32 ret;
//     va_list args;
//     va_start(args, fmt);
//
//     ret = _Printf((outfun*) proutSprintf, s, fmt, args);
//
//     if (ret >= 0) {
//         s[ret] = 0;
//     }
//     va_end(args);
//
//     return ret;
// }
