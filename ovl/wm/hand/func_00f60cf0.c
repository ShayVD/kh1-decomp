/* wm.x func_00f60cf0: matched by hand. */
#include "ovl.h"

typedef struct { s32 pad0; s32 u; s32 v; s32 w; s32 h; } GbSprite;
typedef struct { u8 pad0[0x2200]; u64 tex0[1]; } GbTexState;
extern GbSprite D_00FA6000[];
extern GbTexState *D_00F9B540;
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);

u64 *func_00f60cf0(u64 *p, s32 x, s32 y, s32 idx, u64 rgba, s32 flip) {
    s32 x1 = x + D_00FA6000[idx].w;
    s32 y1 = y + D_00FA6000[idx].h;
    s32 u = D_00FA6000[idx].u;
    s32 u1 = u + D_00FA6000[idx].w;
    s32 v = D_00FA6000[idx].v;
    s32 v1 = v + D_00FA6000[idx].h;
    u64 *q = func_00f66b78(p);
    q[0] = 0x156;
    q[1] = 0;
    q += 2;
    q[0] = D_00F9B540->tex0[idx];
    q[1] = 6;
    q += 2;
    q[0] = rgba;
    q[1] = 1;
    q += 2;
    if (flip == 0) {
        q[0] = (u << 4) | ((u64)(v << 4) << 16);
        q[1] = 3;
        q += 2;
        q[0] = (x << 4) | ((u64)(y << 4) << 16) | 0x100000000;
        q[1] = 5;
        q += 2;
        q[0] = ((u1 << 4) + 16) | ((u64)((v1 << 4) + 16) << 16);
        q[1] = 3;
        q += 2;
        q[0] = (x1 << 4) | ((u64)(y1 << 4) << 16) | 0x100000000;
        q[1] = 5;
    } else {
        q[0] = (u << 4) | ((u64)(v << 4) << 16);
        q[1] = 3;
        q += 2;
        q[0] = (x1 << 4) | ((u64)(y << 4) << 16) | 0x100000000;
        q[1] = 5;
        q += 2;
        q[0] = (u1 << 4) | ((u64)((v1 << 4) + 16) << 16);
        q[1] = 3;
        q += 2;
        q[1] = 5;
        q[0] = (x << 4) | ((u64)(y1 << 4) << 16) | 0x100000000;
    }
    q += 2;
    func_00f66b90(q);
    return q;
}
