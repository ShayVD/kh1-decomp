/* 0017b4f8: 70w off (356 vs 364 bytes), nostrict. Ours hoists seg base +12; nl via andi not sltu; decrement via v0=i-1 bgezl in orig. */
#include "common.h"
typedef struct { f32 x, y, z, len; } SegB;
typedef struct { s32 n; f32 x4; f32 x8; f32 xc; u8 pad10[4]; f32 x14; s32 flags; u8 pad1c[4]; SegB seg[1]; } PathB;
extern PathB *D_00362438;

s32 func_0017b4f8(s32 *pi, f32 *pt, f32 dt) {
    s32 i = *pi;
    PathB *p = D_00362438;
    s32 changed = 0;
    f32 inv, t, rem;
    s32 nl;
    inv = 1.0f / p->seg[i].len;
    nl = (p->flags & 1) != 0;
    t = *pt + dt * inv;
    if (!(t < 0.0f)) goto pos;
    if (!nl || i != 0) goto neg;
    t = 0.0f;
    i = 0;
    goto store;
neg:
    rem = (t - 0.0f) / inv;
    i--;
    if (i < 0) i = p->n - 1;
    t = 1.0f;
    changed = 1;
    goto again;
pos:
    if (!(1.0f < t)) goto store;
    if (nl && !(i < p->n - 2)) {
        i = p->n - 2;
        t = 1.0f;
        goto store;
    }
    i = (i + 1 < p->n) ? i + 1 : 0;
    rem = (t - 1.0f) / inv;
    changed = 1;
    t = 0.0f;
again:
    inv = 1.0f / p->seg[i].len;
    t += rem * inv;
    if (!(t < 0.0f)) goto pos;
    if (!nl || i != 0) goto neg;
    t = 0.0f;
store:
    *pi = i;
    *pt = t;
    return changed;
}
