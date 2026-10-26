/* wm.x func_00f4e118: the twin of gb.x func_00f27020 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { u64 a; u64 b; } Q;
extern Q D_00FA5920[];

Q *func_00f4e118(Q *p, s32 x0, s32 y0, s32 x1, s32 y1, s32 z, u64 c)
{
    Q *s = D_00FA5920;
    Q *d = p;
    u32 i;

    for (i = 0; i < 11; i++) {
        *d++ = *s++;
    }
    s = p;
    s[4].a = c;
    s[5].a = (u64)(x0 << 4) | ((u64)(y0 << 4) << 16) | ((u64)(z << 4) << 32);
    s[6].a = (u64)(x1 << 4) | ((u64)(y0 << 4) << 16) | ((u64)(z << 4) << 32);
    s[7].a = (u64)(x1 << 4) | ((u64)(y1 << 4) << 16) | ((u64)(z << 4) << 32);
    s[8].a = (u64)(x0 << 4) | ((u64)(y1 << 4) << 16) | ((u64)(z << 4) << 32);
    s[9].a = (u64)(x0 << 4) | ((u64)(y0 << 4) << 16) | ((u64)(z << 4) << 32);
    return d;
}
