/* 8 words off; hand/nostrict; func_00124c68 takes one f32 (53.0f); reg/block order differences remain (blkperm best) */
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
    p->x = 0.0f;

    D_002E27A4 = p->x;
    D_002E2790.x = p->x;
    p->y = -10000.0f;
    D_004F77E0 = p->x;
    p->z = 10000.0f;
    p->w = 1.0f;
    D_002E2790.y = p->x;
    D_002E2790.z = p->x;
    D_002E2790.w = 1.0f;

    func_00124c68(53.0f);
    func_00125000();
    func_0011ef10(0x1adb0, func_00125000);
    func_0011ef10(0x20f58, func_001251a0);
    func_0017f510();
}
