/* 00107c48: 7 LCS words (posoff 55, size 240 vs 232), hand/nostrict, no context, no flags (was 19). New: (1) p's i*16 temp held in a GLOBAL user variable (the dead arg reused: `arg = (Ent16 *)(i << 4); p = (s32 *)((u32)&D_00494BA8->w12 + (u32)arg);`), so local-alloc no longer puts it in a0; i keeps the param pseudo's a0 preference, p gets a1, and the operand order is (plus v0 arg) (writing the temp into p itself makes expand_binop swap to (plus p v0)); (2) base[n].w0/.w4 with n++ (loop.c giv) instead of a dst pointer: gives the original's `move a3,t2` in the loop preheader. The loop and epilogue are exact. Left: the `arg = (Ent16 *)i` copy sits in both if/else arms (the original has ONE copy in block 0, in the beqz slot); in block 0 combine merges `i = a0; arg = i` into `arg = a0` (i's entry value dies at the copy) and i loses its a0 preference. Needs a block-0 copy that combine leaves alone. */
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

    if (D_00351BD0 != 0) {
        arg = (Ent16 *)i;
        base = D_00482290;
    } else {
        arg = (Ent16 *)i;
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
