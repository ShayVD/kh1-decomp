#include "common.h"
typedef struct { u64 d[24]; } Blk;
typedef struct {
    s32 a, b, n;
    Blk *p6, *p7, *p9, *p10, *p11, *p12, *p13, *p14, *p15, *p16, *p17;
} Out;
void func_0023aed0(s32 mode, Out *o, s32 *idx, Blk *tbl, s32 a, s32 b, Blk *p6, Blk *p7,
                   s32 n, Blk *p9, Blk *p10, Blk *p11, Blk *p12, Blk *p13, Blk *p14,
                   Blk *p15, Blk *p16, Blk *p17)
{
    s32 i;
    *p10 = tbl[*idx++];
    *p11 = tbl[*idx++];
    for (i = 0; i < n; i++) p9[i] = tbl[*idx];
    idx++;
    *p6 = tbl[*idx++];
    for (i = 0; i < 4; i++) p12[i] = tbl[*idx++];
    *p7 = tbl[*idx++];
    switch (mode) {
    case 0:
        for (i = 0; i < 3; i++) p13[i] = tbl[*idx++];
        break;
    case 1: case 2: case 3: case 4:
        if (mode == 1) {
            for (i = 0; i < 2; i++) p13[i] = tbl[*idx++];
        } else if (mode != 4) {
            *p13 = tbl[*idx++];
        }
        *p16 = tbl[*idx++];
        for (i = 0; i < n; i++) p15[i] = tbl[*idx];
        idx++;
        *p14 = tbl[*idx++];
        for (i = 0; i < 4; i++) p17[i] = tbl[*idx++];
        break;
    }
    o->a = a;
    o->b = b;
    o->p6 = p6;
    o->p7 = p7;
    o->n = n;
    o->p9 = p9;
    o->p10 = p10;
    o->p11 = p11;
    o->p12 = p12;
    o->p13 = p13;
    o->p14 = p14;
    o->p15 = p15;
    o->p16 = p16;
    o->p17 = p17;
}
