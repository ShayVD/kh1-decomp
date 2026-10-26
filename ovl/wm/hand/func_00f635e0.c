/* wm.x func_00f635e0: matched by hand. */
#include "ovl.h"

u64 *func_001f0798(u64 *, s32, s32, s32, s32, s8 *, s32);
u64 *func_00f66ac8(u64 *);
s32 func_00f66ae0(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
void func_00f66f78(s32, s32);
s8 *func_00f632d0(s32);
extern u64 **D_00FA66D8;
extern s32 D_00FA66DC;

void func_00f635e0(s32 x, s32 y, s32 id) {
    u64 *p;
    s8 *s;
    s8 buf[3];

    p = func_00f66b78(func_00f66ac8(*D_00FA66D8));
    p[0] = (u64)(0x700 << 4) | ((u64)(0x740 << 4) << 32);
    p[1] = 0x18;
    p += 2;
    func_00f66b90(p);
    s = func_00f632d0(id);
    while (*s != 0) {
        buf[0] = s[0];
        buf[1] = s[1];
        buf[2] = 0;
        s += 2;
        p = func_001f0798(p, 1, 0x80808080, x, y, buf, D_00FA66DC);
        x += D_00FA66DC;
    }
    func_00f66f78(0x9C40, func_00f66ae0(p));
    *D_00FA66D8 = p;
}
