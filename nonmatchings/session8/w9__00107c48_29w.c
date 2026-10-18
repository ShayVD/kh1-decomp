/* 00107c48: hand/nostrict, LCS 29 words off (s6 draft: LCS 41, 236 vs 232 bytes; this one is the right size). Plain loop: p = &D_00494BA8[i].w12; i++; q = &tbl[i]. Still off: loop.c strength-reduces i*16 into one pointer (orig recomputes sll a1,i,4 / sll v1,i+1,4 every iteration; -fno-strength-reduce leaves a gcse-PRE copy instead), orig keeps i in a0 with the arg moved to a1 (move a1,a0 at entry), and the frame addiu comes first. */
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
    Ent16 *base, *dst, *tbl, *q;
    s32 *p;
    s32 i, n;
    u8 buf[64];
    if (D_00351BD0 != 0) base = D_00482290; else base = D_0047E250;
    tbl = (Ent16 *)(arg->w4 + (s32)arg);
    n = 0;
    dst = base;
    for (i = 0; i < D_00494BB0; ) {
        p = &D_00494BA8[i].w12;
        i++;
        q = &tbl[i];
        if (*p != 0 && q->w8 != 0) {
            *p = 3; n++;
            dst->w0 = q->w8; dst->w4 = q->w12; dst++;
        }
    }
    base[n].w0 = D_0047A1D0.a;
    base[n].w4 = D_0047A1D0.b;
    return n;
}
