/* 001eddc0 hand, 13w (session-7 draft 27w, same as its -fno-sched-interblock result), same size. Fixed: one function-level 'u32 f' takes the r and g conversions (f = (b.r - a.r) * t; c.r = f + a.r; ... f = (b.g - a.g) * t; pc[1] = pa[1] + f;). Left: f (10 refs/17 insns, global-alloc first) takes a0 and a.r a1; orig has a.r a0 / conv a1 (so bc1fl, sw a1 before sw a0, b.r loaded first), then the pb = sp+8 placement. Grid of all 256 f/inline x operand-order combos: 13 is the floor. */
#include "common.h"
typedef struct { u8 r, g, b, a; } __attribute__((aligned(4))) Col;

Col func_001eddc0(Col a, Col b, f32 t) {
    Col c;
    u8 *pa, *pb, *pc;
    u32 f;
    f = (b.r - a.r) * t;
    c.r = f + a.r;
    pc = &c.r; pa = &a.r; pb = &b.r;
    f = (b.g - a.g) * t;
    pc[1] = pa[1] + f;
    c.b = pa[2] + (u32)((pb[2] - pa[2]) * t);
    c.a = pa[3] + (u32)((pb[3] - pa[3]) * t);
    return c;
}
