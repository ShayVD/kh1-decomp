/* 00125240: 5 LCS words off (11 pos; was 6, w60), hand (strict), no context. FLAGGED dead FP test with a dead read in the else arm: `if (p[-1].x < -10000.0f) y = 0; else y = D_004F77E0;` (y is set again before use). gcse PRE puts the D_004F77E0 HIGH in both arms, so life1 keeps the branch; ce removes it, so sched1/local-alloc see one block (REG_N_REFS is recounted after ce: the test adds no refs). Its only effect is the cse1 split: the two 1.0f stores get separate pseudos. FP registers now match except that the second 1.0 (p->w) gets f4 and reload_cse turns it into mov.s f4,f3 (+1 word). Left: that mov.s, lui a0/a1 order, the 1e4 store (8(v0)) issues before the -1e4 store. */
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
    f32 y;
    p->x = 0.0f;
    D_002E2790.x = p->x;
    D_002E2790.y = p->x;
    D_002E2790.z = p->x;
    D_002E2790.w = 1.0f;
    p->y = -10000.0f;
    if (p[-1].x < -10000.0f) y = 0; else y = D_004F77E0;
    D_004F77E0 = p->x;
    p->w = 1.0f;
    p->z = 10000.0f;
    D_002E27A4 = p->x;
    y = 53.0f;
    func_00124c68(y);
    func_00125000();
    func_0011ef10(0x1adb0, func_00125000);
    func_0011ef10(0x20f58, func_001251a0);
    func_0017f510();
}
