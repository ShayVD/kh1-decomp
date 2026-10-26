/* gb.x func_00f34498: matched by hand. */
#include "ovl.h"

void func_00f33d18(OvlMtx, s32);
s32 func_00f41678(s32, s32, OvlMtx, s32, s32);
void func_00f33da0(s32, s32);
void func_00f418f8(s32, OvlMtx);
void func_00f41948(s32);
void func_00f419b8(s32);
void func_001bfac8(void);
extern s32 D_00F56DE8, D_00F80850;
void func_00f34498(s32 a) {
    OvlMtx m;
    OvlVec v;
    s32 done = 0;
    s32 o;
    f32 k, d, one, lim;
    func_00f33d18(m, a);
    a = 0;
    k = 2000.0f;
    func_00f41678(67, 1, m, 0, D_00F56DE8);
    o = func_00f41678(40, 1, m, 0, D_00F56DE8);
    d = 0.0f;
    func_00f33da0(o, 4);


    {
        while (a < 30 && D_00F80850) {
            func_00f418f8(o, m);
            d += k;
            v[0] = -m[2][0] * k;
            v[1] = -m[2][1] * k;
            v[2] = -m[2][2] * k;
            v[3] = 1.0f;
            PlatVu0TransMatrix(m, m, v);
            if (!done && 40000.0f < d) {
                func_00f419b8(o);
                done = 1;
            }
            func_001bfac8();
            a++;
        }
    }
    if (!done) func_00f41948(o);
}
