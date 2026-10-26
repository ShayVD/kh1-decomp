/* gb.x func_00f269f0: matched by hand. */
#include "ovl.h"

typedef struct { u64 a; u64 b; } Q;
extern Q D_00F61020[];

Q *func_00f269f0(Q *p, s32 x0, s32 y0, s32 x1, s32 y1, s32 z, u64 tex)
{
    Q *s = D_00F61020;
    Q *d = p;
    u32 i;

    for (i = 0; i < 8; i++) {
        *d++ = *s++;
    }
    s = p;
    s[4].a = tex;
    s[5].a = (u64)(x0 << 4) | ((u64)(y0 << 4) << 16) | ((u64)(z << 4) << 32);
    s[6].a = (u64)(x1 << 4) | ((u64)(y1 << 4) << 16) | ((u64)(z << 4) << 32);
    return d;
}
