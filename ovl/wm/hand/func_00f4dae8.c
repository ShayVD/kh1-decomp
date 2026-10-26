/* wm.x func_00f4dae8: matched by hand. */
#include "ovl.h"

typedef struct { u64 a; u64 b; } Qw4d;
extern Qw4d D_00FA57A0[];

Qw4d *func_00f4dae8(Qw4d *p, s32 x0, s32 y0, s32 x1, s32 y1, s32 z, u64 tex)
{
    Qw4d *s = D_00FA57A0;
    Qw4d *d = p;
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
