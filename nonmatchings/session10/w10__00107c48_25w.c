/* 00107c48: LCS 25 (stock best 29), hand/nostrict, no context, no extra flags. New: q/r computed inside 'if (*p != 0)' (the then-block): loop.c's giv for (i+1)*16+tbl is no longer reduced (not every iteration), sched1 still hoists sll/addu above the beqz as in the orig, so the loop body is now instruction-for-instruction the orig without -fno-strength-reduce. Left: register allocation only (global-alloc priority p 1.71 > r 1.5 > q 1.0 > dst .82 > i .55; orig needs i first: i=a0, arg copied to a1 'move a1,a0' in the first beqz slot, frame addiu first, dst 'move a3,t2' in the preheader). continue forms and p/q/r block-local do not change refs. Probe: -fno-rerun-cse-after-loop gives the orig prologue (addiu sp first, move a1,a0 in the beqz slot) but loses the PRE copy move t5,a2 and i stays a3. */
#include "common.h"
typedef struct { s32 w0, w4, w8, w12; } Ent16;
typedef struct { s32 a, b; } P8;
extern s32 D_00351BD0;
extern Ent16 *D_00494BA8;
extern s32 D_00494BB0;
extern Ent16 D_00482290[];
extern Ent16 D_0047E250[];
extern P8 D_0047A1D0;

s32 func_00107c48(Ent16 *arg) {
    Ent16 *base;
    Ent16 *dst;
    u32 tbl;
    Ent16 *q;
    s32 *p;
    s32 *r;
    s32 i, j;
    s32 n;
    u8 buf[64];

    if (D_00351BD0 != 0) {
        base = D_00482290;
    } else {
        base = D_0047E250;
    }
    tbl = arg->w4 + (s32)arg;
    n = 0;
    dst = base;
    for (i = 0; i < D_00494BB0; ) {
        p = (s32 *)((u32)&D_00494BA8->w12 + (u32)(i * 16));
        i++;
        if (*p != 0) {
            q = (Ent16 *)((u32)(i * 16) + tbl);
            r = &q->w8;
            if (*r != 0) {
                *p = 3; n++;
                dst->w0 = *r; dst->w4 = q->w12; dst++;
            }
        }
    }

    base[n].w0 = D_0047A1D0.a;
    base[n].w4 = D_0047A1D0.b;
    return n;
}
