/* 00125240: 6 LCS words off (was 8), hand (strict), no context. FLAGGED dead FP test (if (p[-1].x < -1e4f) y = 0;, y set again before its use; flow2 deletes it). FP registers now all match (x f1, 1e4 f0, -1e4 f2, 1.0 f3: x becomes global, the test load holds f1 locally). Left: D_004F77E0 store is alone after the test, so its lui takes v0 after p dies (original a1, issued early) and the sched2 store order differs. */
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
    p->z = 10000.0f;
    p->y = -10000.0f;
    D_002E2790.x = p->x;
    D_002E2790.w = 1.0f;
    p->w = 1.0f;
    D_002E27A4 = p->x;
    D_002E2790.y = p->x;
    D_002E2790.z = p->x;
    if (p[-1].x < -10000.0f) y = 0; /* dead FP test (flagged): y is set again before use; flow2 deletes it */
    D_004F77E0 = p->x;
    y = 53.0f;
    func_00124c68(y);
    func_00125000();
    func_0011ef10(0x1adb0, func_00125000);
    func_0011ef10(0x20f58, func_001251a0);
    func_0017f510();
}
