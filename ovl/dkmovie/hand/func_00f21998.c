/* dkmovie.x func_00f21998: matched by hand. */
#include "ovl.h"

typedef struct { s8 lo : 7; u8 flag : 1; } Cd;

void func_00f21998(u8 *src, s16 *dst, s32 n) {
    s16 prev;
    s32 i;
    s16 v;

    prev = *src++;
    prev |= *src++ << 8;
    i = 0;
    while (i < n) {
        Cd *c = (Cd *)&src[i];
        if (c->flag) {
            v = c->lo;
            i += 1;
        } else {
            v = c->lo << 8;
            v |= src[i + 1];
            i += 2;
        }
        v = v + prev;
        *dst++ = v;
        prev = v;
    }
}
