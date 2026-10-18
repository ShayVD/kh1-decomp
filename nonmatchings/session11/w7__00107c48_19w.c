/* 00107c48: 19w LCS (posoff 23), hand/nostrict (same in hand, hand/nostrict_nofill), no context, no flags (was 25 stock / 23 with flags). New: the parameter is an s32 reused as the loop counter (`s32 func_00107c48(s32 i) { Ent16 *arg = (Ent16 *)i; ... for (i = 0; ...)`): gives the orig prologue copy `move a1,a0` in the first beqz slot (arg copy in a1) and frees the frame/branch layout. Left: i (the param pseudo, pref a0) gets a2 because local-alloc puts the loop's i*16 temp in a0 (v0/v1 taken by the D_00494BA8 chain and (i+1)*16), so i conflicts with a0 and p takes a0; the orig has the i*16 temp in a1, i.e. a0 blocked at local-alloc time. */
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
    Ent16 *arg = (Ent16 *)i;
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
