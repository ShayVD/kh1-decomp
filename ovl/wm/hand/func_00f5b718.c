/* wm.x func_00f5b718: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f5ae10(void *, s32);
void func_00f5ae98(s32, s32);
s32 func_00f680c0(s32);
s32 func_00f68770(s32, s32, void *, s32, s32);
void func_00f689f0(s32, void *);
void func_00f68a40(s32);
void func_00f68ab0(s32);
extern s32 D_00F9B568;
extern s32 D_0108D010;

void func_00f5b718(s32 arg0, s32 arg1) {
    f32 m[4][4];
    f32 r[4][4];
    f32 t[4];
    s32 h;
    s32 done;
    f32 a;
    f32 k;
    f32 d;

    a = 0.349065810442f;
    if (arg1 != 0) {
        a = -a;
    }
    func_00f5ae10(m, arg0);
    k = 2000.0f;
    d = 0.0f;
    PlatVu0UnitMatrix(r);
    PlatVu0RotMatrixY(r, r, a);
    done = 0;
    PlatVu0MulMatrix(m, m, r);
    func_00f68770(67, 1, m, 0, D_00F9B568);
    h = func_00f68770(40, 1, m, 0, D_00F9B568);
    func_00f5ae98(h, 4);
    while (func_00f680c0(h) != 0 && D_0108D010 != 0) {
        d += k;
        func_00f689f0(h, m);
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
