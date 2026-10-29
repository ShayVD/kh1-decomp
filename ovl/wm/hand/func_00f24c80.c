/* wm.x func_00f24c80: matched by hand. */
#include "ovl.h"

typedef struct { s16 a; s16 b; s32 u; s32 v; s32 w; s32 h; } T24c80;
extern T24c80 *D_00FBAA60;
extern u64 *D_00FBAA64;
u64 *func_00f66b78(s32);
void func_00f66b90(u64 *);

u64 *func_00f24c80(s32 x, s32 y, s32 idx, s32 alpha, s32 pk) {
    s32 x0, y0, x1, y1, u0, v0, u1, v1;
    u64 *p;
    s32 w, h;
    w = (D_00FBAA60[idx].w - 1) << 4;
    h = D_00FBAA60[idx].h << 4;
    y0 = y + (1856 << 4);
    u1 = D_00FBAA60[idx].u << 4;
    u0 = u1 + w;
    v0 = D_00FBAA60[idx].v << 4;
    v1 = v0 + h;
    y1 = y0 + h;
    x0 = x + (1792 << 4);
    x1 = x0 + w;
    p = func_00f66b78(pk);
    p[0] = 0;
    p[1] = 20;
    p += 2;
    p[0] = D_00FBAA64[idx];
    p[1] = 6;
    p += 2;
    p[0] = 342;
    p[1] = 0;
    p += 2;
    p[0] = ((s64)alpha << 24) | 0x3F80000000808080LL;
    p[1] = 1;
    p += 2;
    p[0] = (s64)u0 | ((s64)v0 << 16);
    p[1] = 3;
    p += 2;
    p[0] = (s64)x0 | ((s64)y0 << 16) | ((s64)0x8000 << 17);
    p[1] = 5;
    p += 2;
    p[0] = (s64)u1 | ((s64)v1 << 16);
    p[1] = 3;
    p += 2;
    p[0] = (s64)x1 | ((s64)y1 << 16) | ((s64)0x8000 << 17);
    p[1] = 5;
    p += 2;
    func_00f66b90(p);
    return p;
}
