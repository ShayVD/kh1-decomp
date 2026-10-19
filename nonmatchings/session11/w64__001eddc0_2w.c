/* 001eddc0 2 LCS words (hand, strict, no context), FLAGGED dead tests; same code as nonmatchings/session11/w64__001eddc0_2w.c, NEW DIAGNOSIS (s11w67). The 2 words are not a sched2 order problem: sched2 order (and, addiu a2, or, mul.s, sw, c.le.s, trunc/mfc1, bc1f) is already the original one. In ours the fix_truncsfsi in the join block (insn 225) gets its SI clobber scratch = v0 from reload (v0 is free there because the c.r store issues before the fix in sched1), and that v0 clobber stops dbr from moving `sw v0,0(sp)` into the bc1f slot, so it takes `addiu a2,sp,8` instead. In the original v0 (the or result) must be live across the fix, i.e. sched1 issued the store after the fix: that happens only with one interblock sched1 region (whole function <= 10 basic blocks: haifa too_large is bbs > 10 or insns > 100; base shape has 9, any dead test adds 2). With 9 blocks a.r (3 refs/14) cannot beat g (5/7) in global-alloc, and g also prefers a0: expand_preferences merges the add dest (sum, local a0, which has an allocno) into g because g dies in the add, so prune_preferences never puts a0 in g regs_someone_prefers. Needs a.r with ~8 refs and <= 1 extra block, or a sum that is not a0-allocated at expand_preferences time. */
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
