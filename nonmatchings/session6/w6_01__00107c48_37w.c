/* func_00107c48: ~37w off (struct diff 11), mode hand/nostrict. Remaining: original increments i in place (addiu a0,a0,1, i lives in a0, arg moved to a1) yet does NOT strength-reduce i*16; here the i=j copy pattern stops SR but leaves a move (and shifts regs). Frame 64 = unused u8 buf[64]. */
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
    for (i = 0; i < D_00494BB0; i = j) {
        p = (s32 *)((u32)&D_00494BA8->w12 + (u32)(i * 16));
        j = i + 1;
        q = (Ent16 *)((u32)(j * 16) + tbl);
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
