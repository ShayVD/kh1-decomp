/* wm.x func_00f42a38: matched by hand. */
#include "ovl.h"

typedef struct { s16 a; s16 b; s32 u; s32 v; s32 w; s32 h; } T42a38;
extern T42a38 D_00F85000[];
extern u64 D_00F87170[];
u64 *func_00f66b78(s32);
void func_00f66b90(u64 *);

u64 *func_00f42a38(s32 x, s32 y, s32 du, s32 dv, s32 w, s32 h, s32 idx, u32 rgba, s32 pk) {
    s32 x0, y0, x1, y1, u0, v0, u1, v1;
    u64 *p;
    u0 = du + D_00F85000[idx].u;
    y0 = y + 1856;
    x0 = x + 1792;
    v0 = dv + D_00F85000[idx].v;
    u1 = u0 + w + 1;
    x1 = x0 + w;
    v1 = v0 + h + 1;
    y1 = y0 + h;
    p = func_00f66b78(pk);
    p[0] = 0;
    p[1] = 20;
    p += 2;
    p[0] = D_00F87170[idx];
    p[1] = 6;
    p += 2;
    p[0] = 342;
    p[1] = 0;
    p += 2;
    p[0] = (u64)rgba | 0x3F80000000000000LL;
    p[1] = 1;
    p += 2;
    p[0] = (s64)(u0 << 4) | ((s64)(v0 << 4) << 16);
    p[1] = 3;
    p += 2;
    p[0] = (s64)(x0 << 4) | ((s64)(y0 << 4) << 16) | ((s64)0x8000 << 17);
    p[1] = 5;
    p += 2;
    p[0] = (s64)(u1 << 4) | ((s64)(v1 << 4) << 16);
    p[1] = 3;
    p += 2;
    p[0] = (s64)(x1 << 4) | ((s64)(y1 << 4) << 16) | ((s64)0x8000 << 17);
    p[1] = 5;
    p += 2;
    func_00f66b90(p);
    return p;
}
