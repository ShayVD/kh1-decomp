/* wm.x func_00f39058: matched by hand. */
#include "ovl.h"

#include "ovl.h"

void func_001bfac8(void);
f32 func_00f2bed0(s32);
s32 func_00f31118(s32, s32, s32);
s32 func_00f361d8(void);
void func_00f3b118(s32, s32, s32, s32, OvlMtx, f32 *);
s32 func_00f3d758(f32 *, f32);
s32 func_00f680c0(s32);
s32 func_00f68770(s32, s32, OvlMtx, s32, s32);
void func_00f68a40(s32);
extern s32 D_00F87058;
extern s32 D_00FCE38C;

void func_00f39058(OvlMtx arg0, OvlVec arg1, s32 n) {
    OvlMtx m;
    s32 i, h, hit;
    hit = 0;
    PlatVu0UnitMatrix(m);
    PlatVu0CopyVector(m[3], arg0[3]);
    PlatVu0TransMatrix(m, m, arg1);
    m[0][0] = 4.0f;
    m[1][1] = 4.0f;
    m[2][2] = 4.0f;
    for (i = 0; i < n && func_00f361d8() != 0; i++) {
        if (func_00f3d758(m[3], 300.0f) != 0 && func_00f31118(3, 1, 0) != 0) {
            hit = 1;
            break;
        }
        m[3][2] -= func_00f2bed0(-1) * 100.0f;
        func_00f3b118(0, 2, 0x40000000, D_00FCE38C, m, 0);
        func_001bfac8();
    }
    if (func_00f361d8() != 0) {
        h = func_00f68770(9, 1, m, 0, D_00F87058);
        if (h >= 0) {
            while (func_00f680c0(h) != 0) {
                if (hit == 0 && func_00f3d758(m[3], 600.0f) != 0 && func_00f31118(3, 1, 0) != 0) break;
                func_001bfac8();
            }
            func_00f68a40(h);
        }
    }
}
