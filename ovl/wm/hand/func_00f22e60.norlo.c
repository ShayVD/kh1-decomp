/* wm.x func_00f22e60: matched by hand. */
#include "ovl.h"

s32 func_00f66ac8(s32);
s32 func_00f66ae0(u64 *);
u64 *func_00f66b78(s32);
void func_00f66b90(u64 *);
void func_00f66fe8(s32, s32);
void func_001bfac8(void);
extern u64 **D_00F85160;
extern s32 D_00FBB338;

void func_00f22e60(void) {
    s32 a = 58;
    u64 *p;
    do {
        p = func_00f66b78(func_00f66ac8((s32)*D_00F85160));
        p[0] = 0x0000740000007000LL;
        p[1] = 24;
        p += 2;
        p[0] = 68;
        p[1] = 66;
        p += 2;
        p[0] = 0x30003;
        p[1] = 71;
        p += 2;
        p[0] = 70;
        p[1] = 0;
        p += 2;
        p[0] = ((s64)a << 24) | 0x3F80000000000000LL;
        p[1] = 1;
        p += 2;
        p[0] = 0x174007000LL;
        p[1] = 5;
        p += 2;
        p[0] = 0x18C009000LL;
        p[1] = 5;
        p += 2;
        p[0] = 0x5000D;
        p[1] = 71;
        p += 2;
        p[0] = 68;
        p[1] = 66;
        p += 2;
        func_00f66b90(p);
        func_00f66fe8(0, func_00f66ae0(p));
        {
            u64 **q = D_00F85160;
            if (D_00FBB338 == 0) a -= 12;
            *q = p;
        }
        func_001bfac8();
    } while (D_00FBB338 != 0 || a > 0);
}
