/* 001eddc0 finding (58 LCS words but a PURE register permutation: every opcode, the bc1fl/bc1f choices and the homing order of the original; best count stays w2__001eddc0_8w.c at 8), hand, no context. One s32 variable f carries a.r, the channel-0 sum, then the channel-1 and channel-2 conversions (orig: all in a0); the channel-0 conversion is a temp (orig a1). Left: global-alloc takes the conv-0 temp (5 refs/7, prio 1.43) before f (15/40, 1.13), and f prefers a2 because the local andi result of c.r = f got a2 (orig a0: local-alloc in the join block gave a.g a0 before the andi). Orig: f a0, conv0 a1, a.g a1, pa a1, pb a2, -256 a2. */
#include "common.h"
typedef struct { u8 r, g, b, a; } __attribute__((aligned(4))) Col;
Col func_001eddc0(Col a0, Col b0, f32 t) {
    Col c, a, b;
    u8 *pa, *pb, *pc;
    s32 f; u32 g;
    b = b0; a = a0;
    f = a.r; f += (u32)((b.r - f) * t); c.r = f;
    pc = &c.r; pa = &a.r; pb = &b.r;
    f = (u32)((b.g - a.g) * t); pc[1] = pa[1] + f;
    f = (u32)((pb[2] - pa[2]) * t); c.b = pa[2] + f;
    c.a = pa[3] + (u32)((pb[3] - pa[3]) * t);
    return c;
}
