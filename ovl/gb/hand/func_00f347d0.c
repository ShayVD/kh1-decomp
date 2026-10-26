/* gb.x func_00f347d0: the twin of wm.x func_00f5b8c8 (tools/ovl/twins.py). */
#include "ovl.h"

void func_001bfac8(void);
void func_00f33d18(void *, s32);
void func_00f33da0(s32, s32);
s32 func_00f41678(s32, s32, void *, s32, s32);
void func_00f418f8(s32, void *);
void func_00f41948(s32);
void func_00f419b8(s32);
s32 func_00f40fc8(s32);
extern s32 D_00F56DE8;
extern s32 D_00F80850;

void func_00f347d0(s32 arg0) {
    f32 m[8][4];
    f32 t[4];
    s32 h;
    f32 k;

    func_00f33d18(m, arg0);
    k = 500.0f;
    h = func_00f41678(37, 1, m, 0, D_00F56DE8);
    func_00f33da0(h, 4);
    for (arg0 = 0; arg0 < 30 && D_00F80850 != 0; arg0++) {
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
        h = func_00f41678(68, 1, m, 0, D_00F56DE8);
        while (func_00f40fc8(h) != 0) {
            func_001bfac8();
        }
    }
}
