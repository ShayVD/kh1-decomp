/* 00249718 12w, hand (s6 draft unchanged). Finding (w6 s9, -dS -dl): single block, all local-alloc. Orig regs need qty order 1.0f (f4) > t2 (f5) > t3 (f6): the 1.0f const pseudo must have a SHORT life in sched1 order (const load next to the o->w store, after the s[2] loads), so 2/life beats t3 8/24; sched2 then hoists lui/mtc1 to 0x249730. Ours: sched1 issues the const load (insn 81) at cycle ~1 (ready at 0, free FP slot), life 27. A do{}while(0) before o->w keeps it late in sched1 but also in sched2 (35w). The c[1]/c[2] f0/f2 swap: equal lives, tie by qty birth; the o param copy (insn 4) sits between the c1 and c2 loads in sched1 and lengthens c1. -fno-schedule-insns 37w. */
#include "common.h"
typedef struct { f32 x, y, z, w; } V4f;
typedef struct { f32 c[4]; } Seg;
void func_00249718(V4f *o, Seg *s, f32 t) {
    f32 t2 = t * t;
    f32 t3 = t2 * t;
    o->x = s[0].c[0] * t3 + s[0].c[1] * t2 + s[0].c[2] * t + s[0].c[3];
    o->y = s[1].c[0] * t3 + s[1].c[1] * t2 + s[1].c[2] * t + s[1].c[3];
    o->z = s[2].c[0] * t3 + s[2].c[1] * t2 + s[2].c[2] * t + s[2].c[3];
    o->w = 1.0f;
}
