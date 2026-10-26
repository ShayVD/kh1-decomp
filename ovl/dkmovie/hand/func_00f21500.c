/* dkmovie.x func_00f21500: matched by hand. */
#include "ovl.h"

typedef struct { s8 lo : 7; u8 flag : 1; } Cd;
void func_0024b138(u8 *, void *);
void func_00f213f0(s16 *, s32, u8 *);

void func_00f21500(void *src, s16 *dst, s32 n, s32 arg3, u8 *work) {
    u8 *buf = work + 0x24D00;
    s32 i;
    s16 prev;
    s32 k;

    func_0024b138(buf, src);
    prev = 0;
    i = 0;
    k = 0;
    while (i < n) {
        Cd *c = (Cd *)(buf + i);
        s16 v;
        if (c->flag) {
            v = c->lo;
            i += 1;
        } else {
            v = c->lo << 8;
            v |= buf[i + 1];
            i += 2;
        }
        v = v + prev;
        dst[k++] = v;
        prev = v;
    }
    func_00f213f0(dst, arg3, work);
}
