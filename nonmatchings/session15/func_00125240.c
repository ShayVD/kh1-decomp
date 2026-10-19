/* 00125240: 3 LCS words off (true LCS, orig-unmatched 3), hand (strict), no context, RIGHT SIZE 180. FLAGGED: dead no-else FP test `if (p[-1].w < p[-1].x) y = 0;` (y set again before use; flow2 deletes it) with only the D_004F77E0 store after it (statement order found by random search, tools/matching/srch125_s15.py). Was 5w (s12w3, wrong size 184). Every FP register right (x global f1, 1e4 f0, -1e4 f2, 1.0 f3), no mov.s. Left: the D_004F77E0 HIGH is local to the post-test block, so it takes v0 after p dies and issues late (original lui a1 at 0x38, store at 0x60, 8(v1) .z store in the jal slot). */
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
void func_00125240(void) {
    V4f *p = &D_002E2780;
    f32 y;
    p->x = 0.0f;
    p->w = 1.0f;
    D_002E2790.w = 1.0f;
    D_002E27A4 = p->x;
    D_002E2790.x = p->x;
    p->y = -10000.0f;
    D_002E2790.y = p->x;
    p->z = 10000.0f;
    D_002E2790.z = p->x;
    if (p[-1].w < p[-1].x) y = 0;
    D_004F77E0 = p->x;
    y = 53.0f;
    func_00124c68(y);
    func_00125000();
    func_0011ef10(0x1adb0, func_00125000);
    func_0011ef10(0x20f58, func_001251a0);
    func_0017f510();
}
