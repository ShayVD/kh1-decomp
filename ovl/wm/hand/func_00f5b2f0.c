/* wm.x func_00f5b2f0: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f5af10(s32, void *);
void func_00f5ae98(s32, s32);
s32 func_00f68770(s32, s32, void *, s32, s32);
void func_00f689f0(s32, void *);
void func_00f68a40(s32);
void func_00f68ab0(s32);
extern s32 D_00F9B568;
extern s32 D_0108D010;

void func_00f5b2f0(s32 arg0) {
    f32 m[4][4];
    f32 t[4];
    s32 h;
    f32 k;
    s32 i;

    func_00f5af10(arg0, m);
    func_00f68770(0x46, 1, m, 0, D_00F9B568);
    k = 1500.0f;
    h = func_00f68770(0x49, 1, m, 0, D_00F9B568);
    func_00f5ae98(h, 5);
    for (i = 0; i < 1296 && D_0108D010 != 0; i++) {
        func_00f689f0(h, m);
        t[0] = -m[2][0] * k;
        t[1] = -m[2][1] * k;
        t[2] = -m[2][2] * k;
        t[3] = 1.0f;
        PlatVu0TransMatrix(m, m, t);
        func_001bfac8();
    }
    if (D_0108D010 == 0) {
        func_00f68a40(h);
    } else {
        func_00f68ab0(h);
    }
}
