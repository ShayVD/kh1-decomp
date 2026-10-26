/* wm.x func_00f5b590: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f5ae10(void *, s32);
void func_00f5ae98(s32, s32);
s32 func_00f68770(s32, s32, void *, s32, s32);
void func_00f689f0(s32, void *);
void func_00f68a40(s32);
void func_00f68ab0(s32);
extern s32 D_00F9B568;
extern s32 D_0108D010;

void func_00f5b590(s32 arg0) {
    f32 m[4][4];
    f32 t[4];
    s32 h;
    s32 done = 0;
    f32 k;
    f32 d;

    func_00f5ae10(m, arg0);
    k = 2000.0f;
    func_00f68770(67, 1, m, 0, D_00F9B568);
    h = func_00f68770(40, 1, m, 0, D_00F9B568);
    d = 0.0f;
    func_00f5ae98(h, 4);
    for (arg0 = 0; arg0 < 30 && D_0108D010 != 0; arg0++) {
        func_00f689f0(h, m);
        d += k;
        t[0] = -m[2][0] * k;
        t[1] = -m[2][1] * k;
        t[2] = -m[2][2] * k;
        t[3] = 1.0f;
        PlatVu0TransMatrix(m, m, t);
        if (done == 0 && d > 40000.0f) {
            func_00f68ab0(h);
            done = 1;
        }
        func_001bfac8();
    }
    if (done == 0) {
        func_00f68a40(h);
    }
}
