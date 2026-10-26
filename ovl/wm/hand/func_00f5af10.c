/* wm.x func_00f5af10: matched by hand. */
#include "ovl.h"

void func_001becb8(void *, f32 *, s32);
void func_001bf098(void *, void *);
void func_00f5ae10(void *, s32);
extern f32 D_0108CFD8;
extern f32 D_0108CFF0[2];
extern f32 D_0108D000[4];

void func_00f5af10(s32 arg0, void *arg1) {
    f32 a[4];
    f32 b[4];
    f32 m[4][4];

    func_00f5ae10(m, arg0);
    PlatVu0CopyMatrix(arg1, m);
    PlatVu0CopyVector(a, m[3]);
    a[2] += 100.0f;
    a[0] -= D_0108CFF0[0] - D_0108D000[0];
    a[1] -= D_0108CFF0[1] - D_0108D000[1];
    a[2] -= D_0108CFD8 - D_0108D000[2];
    PlatVu0CopyVector(b, m[2]);
    PlatVu0Normalize(b, b);
    PlatVu0Normalize(a, a);
    PlatVu0AddVector(a, b, a);
    PlatVu0Normalize(a, a);
    a[2] = -a[2];
    a[3] = 1.0f;
    func_001becb8(m, a, 1);
    func_001bf098(arg1, m);
}
