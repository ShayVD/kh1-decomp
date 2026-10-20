/* func_00125240: MATCHED (session 22, s22m1), hand. From s20m1's 3w draft (natural body, FP constants pinned: 10000.0f in $f0, -10000.0f in $f2, 1.0f in $f3). New: `f32 *q = &D_002E27A4;` at the top with the store written `*q = x;`. The 27A4 HIGH now gets the low LUID from the declaration (combine folds the LO_SUM into the swc1), independent of where the store sits, so sched1 issues it before the D_004F77E0 HIGH and local-alloc still gives it a0; then pclimb_s15 over the body order (1 -> 0). FLAGGED: three local register variables (without them 8w). */
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
    f32 *q = &D_002E27A4;
    m = -10000.0f;
    p->y = m;
    one = 1.0f;
    p->x = 0.0f;
    p->w = one;
    k = 10000.0f;
    p->z = k;
    x = p->x;
    D_002E2790.x = x;
    D_004F77E0 = x;
    D_002E2790.y = x;
    D_002E2790.z = x;
    y = 53.0f;
    *q = x;
    D_002E2790.w = one;
    func_00124c68(y);
    func_00125000();
    func_0011ef10(0x1adb0, func_00125000);
    func_0011ef10(0x20f58, func_001251a0);
    func_0017f510();
}
