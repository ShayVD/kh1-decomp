/* 001eddc0 2 LCS words (hand, strict, no context; best was s11w2 8w). FLAGGED dead tests: five integer `if (a.r == k) { pc = 0; pc = pa; } else { same }` tests between the ch0 conversion and the sum add refs to the a.r pseudo (QI subreg compare, li temps) and live length to the conversion g, so global-alloc takes a.r (a0, sum preference) before g: g gets a1 and every register matches. Left: in the join block pb = &b.r (addiu a2,sp,8) issues before or/mul.s and sw v0,0(sp) goes in the bc1f slot in the original; ours has the sw before c.le.s and addiu a2 in the slot. Without the tests (r1 shape) that order was right. */
#include "common.h"
typedef struct { u8 r, g, b, a; } __attribute__((aligned(4))) Col;
Col func_001eddc0(Col a0, Col b0, f32 t) {
    Col c, a, b;
    u8 *pa, *pb, *pc;
    u32 f, g;
    b = b0; a = a0;
    g = (b.r - a.r) * t;
     if (a.r == 0) { pc = 0; pc = pa; } else { pc = 0; pc = pa; } if (a.r == 1) { pc = 0; pc = pa; } else { pc = 0; pc = pa; } if (a.r == 2) { pc = 0; pc = pa; } else { pc = 0; pc = pa; } if (a.r == 3) { pc = 0; pc = pa; } else { pc = 0; pc = pa; } if (a.r == 4) { pc = 0; pc = pa; } else { pc = 0; pc = pa; }
    c.r = a.r + g;
    pc = &c.r; pa = &a.r; pb = &b.r;
    f = (b.g - a.g) * t;
    pc[1] = pa[1] + f;
    c.b = pa[2] + (u32)((pb[2] - pa[2]) * t);
    c.a = pa[3] + (u32)((pb[3] - pa[3]) * t);
    return c;
}
