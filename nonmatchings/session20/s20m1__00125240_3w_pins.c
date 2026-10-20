/* 00125240: 3 true DP LCS words off (hand, strict), right size 180. s20m1: NATURAL body (no dead FP test, unlike the session 15 3w draft) plus three FP constant pins: 10000.0f in $f0, -10000.0f in $f2, 1.0f in $f3 (s12w17's 8w natural draft had only x/1e4 swapped f0/f1; pinning k alone gives 5w, all three 4w), then statement order climbed with pclimb_s15 (4 -> 3). Every FP register and every GPR is now the original's (p v0, 2790 v1, 27A4 a0, 77E0 a1). Left (3 words): sched2 issues the 77E0 HIGH (lui a1) before the 27A4 HIGH (lui a0) and the 27A4 store one slot late. The two needs conflict: sched2 breaks the lui tie by sched1 order, so 27A4's HIGH must come first in sched1, but local-alloc then gives 27A4 a1 unless its sched1 life is no longer than 77E0's, and sched1 always puts a memory-unit insn (the 53.0 f12 load or a store) between the two HIGHs while the two stores sit next to each other. FLAGGED (three local register variables). */
#include "common.h"
typedef struct { f32 x, y, z, w; } V4f;
extern V4f D_002E2780;
extern V4f D_002E2790;
extern f32 D_002E27A4;
extern f32 D_004F77E0;
void func_00124c68(f32);
void func_00125000(void);
void func_001251a0(void);
void func_0011ef10(s32, void (*)(void));
void func_0017f510(void);
void func_00125240(void) {
    V4f *p = &D_002E2780;
    f32 y, x;
    register f32 k asm("$f0");
    register f32 m asm("$f2");
    register f32 one asm("$f3");
    p->x = 0.0f;
    m = -10000.0f;
    one = 1.0f;
    x = p->x;
    D_002E2790.x = x;
    D_004F77E0 = x;
    D_002E2790.y = x;
    k = 10000.0f;
    D_002E2790.z = x;
    D_002E27A4 = x;
    p->z = k;
    p->w = one;
    D_002E2790.w = one;
    p->y = m;
    y = 53.0f;
    func_00124c68(y);
    func_00125000();
    func_0011ef10(0x1adb0, func_00125000);
    func_0011ef10(0x20f58, func_001251a0);
    func_0017f510();
}
