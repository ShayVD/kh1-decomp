/* func_00107c48: 23 words (LCS) in hand/nostrict_nogcse with KH1_EXTRA_CCFLAGS=-fno-strength-reduce (best stock draft: session8 w9 29w in hand/nostrict). New finding: under -fno-gcse -fno-strength-reduce the loop body is instruction-for-instruction the original (sll i*16 / addiu i / sll (i+1)*16 recomputed each pass, r = &q->w8 in its own reg, li 3 / &D_00494BB0 / &D_00494BA8 hoisted by loop.c), so the original loop was neither strength-reduced nor PRE'd. Left: register allocation only: original allocates i before r/p/q (i=a0, arg copied to a1, r=a2, dst=a3 'move a3,t2' in the preheader); ours allocates r,p,q,dst first (global-alloc priority r 1.71 > p 1.5 > q 1.09 > dst 0.82 > i 0.55), giving i=a3, dst=a2, arg stays in a0; frame addiu also moves. The original's order would follow if p/q/r were block-local (local-alloc) pseudos. No mode has -fno-strength-reduce. */
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
        q = (Ent16 *)((u32)(i * 16) + tbl);
        r = &q->w8;
        if (*p != 0 && *r != 0) {
            *p = 3; n++;
            dst->w0 = *r; dst->w4 = q->w12; dst++;
        }
    }

    base[n].w0 = D_0047A1D0.a;
    base[n].w4 = D_0047A1D0.b;
    return n;
}
