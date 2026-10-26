/* gb.x func_00f340a0: matched by hand. */
#include "ovl.h"

void func_00f33d18(OvlMtx, s32);
s32 func_00f41678(s32, s32, OvlMtx, s32, s32);
void func_00f33da0(s32, s32);
void func_00f418f8(s32, OvlMtx);
void func_00f41948(s32);
void func_00f419b8(s32);
void func_001bfac8(void);
extern s32 D_00F56DE8, D_00F80850;
void func_00f340a0(s32 a) {
    OvlMtx m;
    OvlVec v;
    s32 o;
    f32 k, one;
    func_00f33d18(m, a);
    a = 0;
    k = 1000.0f;
    func_00f41678(69, 1, m, 0, D_00F56DE8);
    o = func_00f41678(72, 1, m, 0, D_00F56DE8);
    func_00f33da0(o, 5);
    if (D_00F80850) {
        one = 1.0f;
        do {
            func_00f418f8(o, m);
            v[0] = -m[2][0] * k;
            v[1] = -m[2][1] * k;
            v[2] = -m[2][2] * k;
            v[3] = one;
            PlatVu0TransMatrix(m, m, v);
            func_001bfac8();
            a++;
        } while (a < 56 && D_00F80850);
    }
    if (D_00F80850 == 0) func_00f41948(o);
    else func_00f419b8(o);
}
