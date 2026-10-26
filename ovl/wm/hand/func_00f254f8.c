/* wm.x func_00f254f8: matched by hand. */
#include "ovl.h"

void func_00f21f00(void);
s32 func_00f66ac8(void *);
s32 func_00f66ae0(void *);
s64 *func_00f66b78(s32);
void func_00f66b90(void *);
void func_00f670c8(s32);
extern s32 D_00F873F0;
extern s32 D_00FBB450;

s32 func_00f254f8(void) {
    s64 *p;
    s64 t;

    p = func_00f66b78(func_00f66ac8(&D_00FBB450));
    t = ((s64) 0x7400 << 32) | 0x7000;
    p[0] = t;
    p[1] = 24;
    p += 2;
    p[0] = t;
    p[1] = 25;
    p += 2;
    func_00f66b90(p);
    func_00f670c8(func_00f66ae0(p));
    func_00f21f00();
    return (D_00F873F0 != 0) ? 0 : 4;
}
