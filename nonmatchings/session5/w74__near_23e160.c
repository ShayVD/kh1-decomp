#include "common.h"
typedef struct { s32 x, y, z, w; } I4b;
I4b *func_0023d208(s32 *, s32 *, I4b *, f32);
s32 func_0023d1e0(f32);

void func_0023e160(s32 *c, s32 *r, s32 *col, I4b *d, f32 a0, f32 a1, f32 al) {
    I4b *h;
    I4b *e;
    s32 i, n, m;
    ((u64 *)d)[0] = 0x1000000000008001ULL;
    ((u64 *)d)[1] = 1;
    d++;
    d->x = col[0];
    d->y = col[1];
    d->z = col[2];
    d->w = (u32)(col[3] * al);
    d++;
    h = d;
    d++;
    d->x = r[0];
    d->y = r[1];
    d->z = 0;
    d->w = 0;
    d = h + 2;
    d->x = c[0];
    d->y = c[1];
    d->z = 0;
    d->w = 0;
    d = func_0023d208(c, r, h + 3, a0);
    i = func_0023d1e0(a0) + 1;
    m = func_0023d1e0(a1);
    for (; i <= m; i++) {
        d = func_0023d208(c, r, d, i * 0.785398081f);
    }
    d = func_0023d208(c, r, d, a1);
    n = (d - h) - 1;
    ((u64 *)h)[1] = 0x53;
    ((u64 *)h)[0] = (n / 2) | 0x8000 | (0x82BBULL << 46);
}
