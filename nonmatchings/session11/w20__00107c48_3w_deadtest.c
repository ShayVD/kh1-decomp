/* 00107c48: 3 LCS words off (right size 232), hand/nostrict, no context. From w13 7w. One `arg = (Ent16 *)i;` copy in block 0 (no arm copies) plus a dead test that keeps the param pseudo i live past the copy: `if ((i << 4) & 8) return 0;` (combine folds it via nonzero_bits, cse cannot). With i still live, combine cannot merge `i = a0; arg = i` (i2 would have to be kept), so i keeps its a0 preference; allocation and the beqz-slot `move a1,a0` are then exact, loop/epilogue exact. Left: block-0 `lui v0 / lw v1` vs original `lui v1 / lw v0`: sched1 places the copy between the lw and the beqz, so the load pseudo lives 2 local-alloc insns, ties the %hi pseudo, and the lower qty (%hi) takes v0. The dead test is a hack (needs a natural use of i that disappears after combine). Copy in the join block instead (no dead test): allocation exact but the move stays in the join (9w). */
#include "common.h"
typedef struct { s32 w0, w4, w8, w12; } Ent16;
typedef struct { s32 a, b; } P8;
extern s32 D_00351BD0;
extern Ent16 *D_00494BA8;
extern s32 D_00494BB0;
extern Ent16 D_00482290[];
extern Ent16 D_0047E250[];
extern P8 D_0047A1D0;

s32 func_00107c48(s32 i) {
    Ent16 *arg;
    Ent16 *base;
    Ent16 *dst;
    u32 tbl;
    Ent16 *q;
    s32 *p;
    s32 *r;
    s32 j;
    s32 n;
    u8 buf[64];

    arg = (Ent16 *)i;
    if ((i << 4) & 8) return 0;
    if (D_00351BD0 != 0) {
        base = D_00482290;
    } else {
        base = D_0047E250;
    }
    i = 0;
    tbl = arg->w4 + (s32)arg;
    n = 0;
    for (; i < D_00494BB0; ) {
        arg = (Ent16 *)(i << 4);
        p = (s32 *)((u32)&D_00494BA8->w12 + (u32)arg);
        i++;
        if (*p != 0) {
            q = (Ent16 *)((u32)(i * 16) + tbl);
            r = &q->w8;
            if (*r != 0) {
                *p = 3;
                base[n].w0 = *r; base[n].w4 = q->w12; n++;
            }
        }
    }

    base[n].w0 = D_0047A1D0.a;
    base[n].w4 = D_0047A1D0.b;
    return n;
}
