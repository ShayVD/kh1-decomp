/* func_001eddc0: MATCHED (session 19, s19m1), hand. From s11w64's 2w draft (nonmatchings/session11/w64__001eddc0_2w.c) WITHOUT its dead tests: with 9 basic blocks sched1 uses one interblock region and the c.r word store lands after the fix in the bc1f slot as in the original, but global-alloc then gave g a0 and a.r a1 (s11w67 diagnosis: g's preference merge). New: a.r loaded into a local register variable `register s32 ar asm("$4")` (the lbu's own result, so cse keeps the pin) and used for both g and c.r. FLAGGED: one register variable. As u32: 416 bytes (the u32 subtract goes through the unsigned float path). */
#include "common.h"
typedef struct { u8 r, g, b, a; } __attribute__((aligned(4))) Col;
Col func_001eddc0(Col a0, Col b0, f32 t) {
    Col c, a, b;
    u8 *pa, *pb, *pc;
    u32 f, g;
    register s32 ar asm("$4");
    b = b0; a = a0;
    ar = a.r;
    g = (b.r - ar) * t;
    c.r = ar + g;
    pc = &c.r; pa = &a.r; pb = &b.r;
    f = (b.g - a.g) * t;
    pc[1] = pa[1] + f;
    c.b = pa[2] + (u32)((pb[2] - pa[2]) * t);
    c.a = pa[3] + (u32)((pb[3] - pa[3]) * t);
    return c;
}
