/* 001eddc0 hand: 75w off (size 384 vs 380). Shape right: c.r stored via lw/and/or/sw (c pseudo then forced to stack, slots c=0,a=4,b=8), later bytes sb. Off: orig stores c.g.. direct to sp (we use pc reg), orig reads diff of g direct but add of g via &a reg; bc1fl vs bc1f in byte r. */
#include "common.h"
typedef struct { u8 r, g, b, a; } __attribute__((aligned(4))) Col;

Col func_001eddc0(Col a, Col b, f32 t) {
    Col c;
    u8 *pa, *pb, *pc;
    c.r = a.r + (u32)((b.r - a.r) * t);
    pc = &c.r; pa = &a.r; pb = &b.r;
    pc[1] = pa[1] + (u32)((pb[1] - pa[1]) * t);
    pc[2] = pa[2] + (u32)((pb[2] - pa[2]) * t);
    pc[3] = pa[3] + (u32)((pb[3] - pa[3]) * t);
    return c;
}
