/* 00125240: 8 LCS words off, hand (strict), no context, NATURAL (no dead test). Every insn and every GPR matches the original exactly; the only difference is x (p->x reload, 6 refs) in f0 and 10000.0f in f1 (original: 1e4 f0, x f1). Local-alloc: x pri 5000 (refs 6, life 24) beats 1e4 (2 refs). In any single-block shape the three FP consts take memory-unit slots t1/t3/t5 in sched1 (EE: movsf consts issue on the memory unit), the x load is fixed at t4 (idx 9) and the HIGH/LO ALU partners fill every cycle, so 1e4 life >= 6 (pri <= 3333) and x life <= 24 (pri >= 5000): unreachable without an extra sched1 insn that later vanishes (the flagged dead-test drafts get it from a split second 1.0 pseudo or the test load). Constants as f32 variables set in this order fix the li/mtc1 order; order found by annealing (sa.py). */
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
    f32 y, one, m, k, x;
    p->x = 0.0f;
    one = 1.0f;
    x = p->x;
    D_002E2790.y = x;
    m = -10000.0f;
    D_002E27A4 = x;
    p->y = m;
    k = 10000.0f;
    D_002E2790.z = x;
    p->z = k;
    D_004F77E0 = x;
    p->w = one;
    D_002E2790.x = x;
    D_002E2790.w = one;
    y = 53.0f;
    func_00124c68(y);
    func_00125000();
    func_0011ef10(0x1adb0, func_00125000);
    func_0011ef10(0x20f58, func_001251a0);
    func_0017f510();
}
