/* wm.x func_00f3c550: matched by hand. */
#include "ovl.h"

s32 func_00f684e8(s32);
u32 func_00f68828(s32);
void func_00f68980(s32, void *);
void func_00f689f0(s32, OvlMtx);
extern OvlMtx D_0107FFE0[];

s32 func_00f3c550(s32 arg0, OvlMtx arg1, u8 *arg2, void *arg3) {
    OvlMtx m;
    s32 i;
    s32 n = 0;
    for (i = 0; i < 256; i++) {
        u32 v = func_00f68828(i);
        s32 t = v & 0xF;
        if (t != 0 && ((v >> 4) & 0xFFFFFF) == arg0) {
            if (t == 2) {
                PlatVu0MulMatrix(m, arg1, D_0107FFE0[func_00f684e8(i)]);
                func_00f689f0(i, m);
                func_00f68980(i, arg3);
            } else {
                func_00f689f0(i, arg1);
                func_00f68980(i, arg3);
            }
            n++;
            arg2[i] = 1;
        }
    }
    return n;
}
