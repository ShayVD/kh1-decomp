/* Round 41 wwm2: score 52 -> 42. The UV word is written with its v (<< 16) half first, ((u64)((v1 << 4) + 16) << 16) | ((u1 << 4) + 16). Found by r41/orsweep.py, which tries every order of the | terms in each packed GS word line. */
/* 53 words / score 52: the prologue and the non-flip branch match. Index D_00F61880[idx] directly per field (no pointer). Writing q[1] before q[0] in the last flip store stops cross-jumping. Left: the flip branch is scheduled differently, starting with v<<4 where we load sp0 first. */
#include "ovl.h"

typedef struct { s32 pad0; s32 u; s32 v; s32 w; s32 h; } GbSprite;
typedef struct { u8 pad0[0x2200]; u64 tex0[1]; } GbTexState;
extern GbSprite D_00F61880[];
extern GbTexState *D_00F56DC0;
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);

u64 *func_00f39bf8(u64 *p, s32 x, s32 y, s32 idx, u64 rgba, s32 flip) {
    s32 x1 = x + D_00F61880[idx].w;
    s32 y1 = y + D_00F61880[idx].h;
    s32 u = D_00F61880[idx].u;
    s32 u1 = u + D_00F61880[idx].w;
    s32 v = D_00F61880[idx].v;
    s32 v1 = v + D_00F61880[idx].h;
    u64 *q = func_00f3fa80(p);
    q[0] = 0x156;
    q[1] = 0;
    q += 2;
    q[0] = D_00F56DC0->tex0[idx];
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
        q[0] = ((u64)((v1 << 4) + 16) << 16) | ((u1 << 4) + 16);
        q[1] = 3;
        q += 2;
        q[1] = 5;
        q[0] = (x << 4) | ((u64)(y1 << 4) << 16) | 0x100000000;
    }
    q += 2;
    func_00f3fa98(q);
    return q;
}
