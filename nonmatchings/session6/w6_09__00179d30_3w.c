/* 3w off (nostrict): sched order of li.s 40.0 (f3) vs move a1,sp before first bc1f */
#include "common.h"
typedef struct { f32 x, y, z, w; } V4_9d;
typedef struct { u8 pad[0x10]; V4_9d pos; } Act9d;
extern Act9d *D_00575894;
extern V4_9d D_005758D0;
extern V4_9d D_005758E0;
extern f32 D_002E27A0;
extern f32 D_00362520;
extern f32 D_002BBDFC;
void func_001315c0(Act9d *, s32, V4_9d *, f32);
void func_00267530(V4_9d *, V4_9d *, V4_9d *);
f32 func_00121840(V4_9d *, V4_9d *);
void func_002674f0(V4_9d *, V4_9d *, V4_9d *, f32);

void func_00179d30(void) {
    V4_9d a, b, c;
    f32 z, lim, ang, af;
    z = 0.0f;
    func_001315c0(D_00575894, 0x8003, &a, z);
    lim = D_002E27A0;
    lim *= 3.14159251f;
    lim /= 180.0f;
    func_00267530(&b, &D_005758E0, &D_005758D0);
    func_00267530(&c, &D_00575894->pos, &D_005758D0);
    ang = func_00121840(&b, &c);
    af = fabsf(ang);
    lim *= 0.5f;
    if (lim < af) {
        D_00362520 += D_002BBDFC;
        if (40.0f < D_00362520) D_00362520 = 40.0f;
    } else if (af < lim * 0.7999999523162842f) {
        D_00362520 -= D_002BBDFC + D_002BBDFC;
        if (D_00362520 < z) D_00362520 = z;
    }
    if (0.0f < D_00362520) func_002674f0(&D_005758E0, &a, &D_005758E0, D_00362520 / 40.0f * 0.7999999523162842f);
}
