/* 001eddc0: hand 27w (same size); with -fno-sched-interblock 13w: orig spills b (sw a1,8) before a, loads b.r first, a.r in a0/conv in a1 (bc1fl in first conv), addiu a1,sp,4 placement. Manual if/else conversions and inline helpers worse. */
#include "common.h"
typedef struct { u8 r, g, b, a; } __attribute__((aligned(4))) Col;

Col func_001eddc0(Col a, Col b, f32 t) {
    Col c;
    u8 *pa, *pb, *pc;
    c.r = (u32)((b.r - a.r) * t) + a.r;
    pc = &c.r; pa = &a.r; pb = &b.r;
    pc[1] = pa[1] + (u32)((b.g - a.g) * t);
    c.b = pa[2] + (u32)((pb[2] - pa[2]) * t);
    c.a = pa[3] + (u32)((pb[3] - pa[3]) * t);
    return c;
}
