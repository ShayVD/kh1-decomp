/* gb.x func_00f34620: matched by hand. */
#include "ovl.h"

void func_00f33d18(OvlMtx, s32);
s32 func_00f41678(s32, s32, OvlMtx, s32, s32);
void func_00f33da0(s32, s32);
void func_00f418f8(s32, OvlMtx);
void func_00f41948(s32);
void func_00f419b8(s32);
s32 func_00f40fc8(s32);
void func_001bfac8(void);
extern s32 D_00F56DE8, D_00F80850;
void func_00f34620(s32 a, s32 b) {
    OvlMtx m;
    OvlMtx r;
    OvlVec v;
    s32 o;
    s32 done;
    f32 ang, k, d, one, lim;
    ang = 0.34906584f;
    if (b) ang = -ang;
    func_00f33d18(m, a);
    k = 2000.0f;
    d = 0.0f;
    one = 1.0f;
    PlatVu0UnitMatrix(r);
    lim = 40000.0f;
    PlatVu0RotMatrixY(r, r, ang);
    done = 0;
    PlatVu0MulMatrix(m, m, r);
    func_00f41678(67, 1, m, 0, D_00F56DE8);
    o = func_00f41678(40, 1, m, 0, D_00F56DE8);
    func_00f33da0(o, 4);
    while (func_00f40fc8(o) && D_00F80850) {
        d += k;
        func_00f418f8(o, m);
        v[0] = -m[2][0] * k;
        v[1] = -m[2][1] * k;
        v[2] = -m[2][2] * k;
        v[3] = one;
        PlatVu0TransMatrix(m, m, v);
        if (!done && lim < d) {
            func_00f419b8(o);
            done = 1;
        }
        func_001bfac8();
    }
    if (!done) func_00f41948(o);
}
