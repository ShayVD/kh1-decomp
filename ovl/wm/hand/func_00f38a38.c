/* wm.x func_00f38a38: matched by hand. */
#include "ovl.h"

extern s32 D_00F87058;
void func_00f37ea0(s32, OvlMtx);
s32 func_00f68770(s32, s32, OvlMtx, s32, s32);
s32 func_00f680c0(s32);
s32 func_00f361d8(void);
void func_00f689f0(s32, OvlMtx);
s32 func_00f3d850(OvlVec, OvlVec, OvlMtx, OvlVec);
s32 func_00f31118(s32, s32, s32);
void func_00f68508(s32, s32, OvlVec, s32, s32, s32);
void func_001bfac8(void);

void func_00f38a38(f32 arg0, f32 arg1) {
    OvlMtx m;
    OvlVec a;
    OvlVec b;
    OvlVec c;
    s32 h;
    a[0] = 0.0f;
    a[1] = -arg0 * 0.5f;
    a[2] = 0.0f;
    a[3] = 1.0f;
    b[0] = arg1 * 0.5f;
    b[1] = arg0 * 0.5f;
    b[2] = arg1 * 0.5f;
    b[3] = 1.0f;
    func_00f37ea0(3, m);
    h = func_00f68770(2, 1, m, 0, D_00F87058);
    while (func_00f680c0(h) && func_00f361d8()) {
        func_00f37ea0(3, m);
        func_00f689f0(h, m);
        if (func_00f3d850(a, b, m, c) && func_00f31118(2, 1, 0)) {
            func_00f68508(4, 1, c, 0, 0, D_00F87058);
            return;
        }
        func_001bfac8();
    }
}
