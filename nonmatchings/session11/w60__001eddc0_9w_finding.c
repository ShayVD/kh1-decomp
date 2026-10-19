/* 001eddc0 finding: 9 LCS words (best stays w2's 8), hand strict, no context. FLAGGED dead FP test reading the ch0 conversion var g BEFORE its first set (uninitialised read: g live from entry, so its global-alloc priority drops below a.r): a.r now gets a0 as in the original (the w2 draft's main miss). Left: g then conflicts with the incoming a0/a1 param hard regs and takes a2 (orig a1), so reorg fills bc1f from the fall-through (lbu a1,5(sp)) instead of bc1fl+addu. Same dead test after g's set, at the end, or reading a.r: no gain. */
#include "common.h"
typedef struct { u8 r, g, b, a; } __attribute__((aligned(4))) Col;
Col func_001eddc0(Col a0, Col b0, f32 t) {
    Col c, a, b;
    u8 *pa, *pb, *pc;
    u32 f, g;
    b = b0; a = a0;
    if ((f32)(s32)g < t) pa = 0; /* dead FP test (flagged): g read uninitialised, pa set again before use; flow2 deletes it */
    g = (b.r - a.r) * t;
    c.r = g + a.r;
    pc = &c.r;
    pa = &a.r;
    pb = &b.r;
    f = (b.g - a.g) * t;
    pc[1] = pa[1] + f;
    c.b = pa[2] + (u32)((pb[2] - pa[2]) * t);
    c.a = pa[3] + (u32)((pb[3] - pa[3]) * t);
    return c;
}
