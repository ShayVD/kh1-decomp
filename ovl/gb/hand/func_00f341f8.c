/* gb.x func_00f341f8: the twin of wm.x func_00f5b2f0 (tools/ovl/twins.py). */
#include "ovl.h"

void func_001bfac8(void);
void func_00f33e18(s32, void *);
void func_00f33da0(s32, s32);
s32 func_00f41678(s32, s32, void *, s32, s32);
void func_00f418f8(s32, void *);
void func_00f41948(s32);
void func_00f419b8(s32);
extern s32 D_00F56DE8;
extern s32 D_00F80850;

void func_00f341f8(s32 arg0) {
    f32 m[4][4];
    f32 t[4];
    s32 h;
    f32 k;
    s32 i;

    func_00f33e18(arg0, m);
    func_00f41678(0x46, 1, m, 0, D_00F56DE8);
    k = 1500.0f;
    h = func_00f41678(0x49, 1, m, 0, D_00F56DE8);
    func_00f33da0(h, 5);
    for (i = 0; i < 1296 && D_00F80850 != 0; i++) {
        func_00f418f8(h, m);
        t[0] = -m[2][0] * k;
        t[1] = -m[2][1] * k;
        t[2] = -m[2][2] * k;
        t[3] = 1.0f;
        PlatVu0TransMatrix(m, m, t);
        func_001bfac8();
    }
    if (D_00F80850 == 0) {
        func_00f41948(h);
    } else {
        func_00f419b8(h);
    }
}
