/* wm.x func_00f25420: matched by hand. */
#include "ovl.h"

s32 func_00f66ac8(void *);
s32 func_00f66ae0(void *);
s64 *func_00f66b78(s32);
void func_00f66b90(void *);
void func_00f670c8(s32);
extern s32 D_00F873F0;
extern s32 D_00FBAA70;
extern s32 D_00FBAA74;
extern s32 D_00FBB350;

s32 func_00f25420(void) {
    s64 *p;
    s64 t;
    s32 x = 0x700 - D_00FBAA70;
    s32 y = 0x740 - D_00FBAA74;

    p = func_00f66b78(func_00f66ac8(&D_00FBB350));
    t = ((s64)(y << 4) << 32) | (x << 4);
    p[1] = 24;
    p[0] = t;
    p += 2;
    p[0] = t;
    p[1] = 25;
    p += 2;
    p[0] = 0x31000070;
    p[1] = 78;
    p += 2;
    func_00f66b90(p);
    func_00f670c8(func_00f66ae0(p));
    return (D_00F873F0 != 0) ? 0 : 4;
}
