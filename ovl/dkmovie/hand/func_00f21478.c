/* dkmovie.x func_00f21478: matched by hand. */
#include "ovl.h"

typedef struct { s8 lo : 7; u8 flag : 1; } Cd;
void func_00f213f0(s16 *, s32, s32);

void func_00f21478(u8 *src, s16 *dst, s32 n, s32 arg3, s32 arg4) {
    s16 prev;
    s32 i;
    s32 k;
    s16 v;

    prev = 0;
    i = 0;
    k = 0;
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
        dst[k++] = v;
        prev = v;
    }
    func_00f213f0(dst, arg3, arg4);
}
