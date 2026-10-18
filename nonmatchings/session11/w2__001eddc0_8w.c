/* 001eddc0 8w LCS (hand, strict; was 9). New: param copies 'Col a0, Col b0' + locals 'b = b0; a = a0;' (b first) give the original's homing order (sw a1,8(sp) before sw a0,4(sp)) and b.r loaded first. Left: conv f (refs 10, prio 1.76) still beats a.r for a0 (orig a.r a0, conv a1 -> bc1fl + addu a0,a0,a1), and the addiu a2,sp,8 / sw v0,0(sp) placement. */
#include "common.h"
typedef struct { u8 r, g, b, a; } __attribute__((aligned(4))) Col;
Col func_001eddc0(Col a0, Col b0, f32 t) {
    Col c, a, b;
    u8 *pa, *pb, *pc;
    u32 f;
    b = b0; a = a0;
    f = (b.r - a.r) * t;
    c.r = f + a.r;
    pc = &c.r; pa = &a.r; pb = &b.r;
    f = (b.g - a.g) * t;
    pc[1] = pa[1] + f;
    c.b = pa[2] + (u32)((pb[2] - pa[2]) * t);
    c.a = pa[3] + (u32)((pb[3] - pa[3]) * t);
    return c;
}
