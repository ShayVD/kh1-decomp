/* wm.x func_00f27d18: matched by hand. */
#include "ovl.h"

extern u64 **D_00F85160;
s32 func_001bb2e0(s32);
u64 *func_00f66ac8(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
s32 func_00f66ae0(u64 *);
void func_00f66fe8(s32, s32);
s32 func_00f24f50(s32);
u64 *func_00f24738(s32, s32, s32, u32, u64 *);
u64 *func_00f23a58(s32, s32, s32, s32, u64 *);
s32 func_001bb1d8(s32);
s32 func_001baf08(s32);
u64 *func_00f24e38(s32, s32, s32, s32, u64 *);
u64 *func_00f23c20(s32, s32, s32, s32, s32, s32, s32, s32, u64 *);

void func_00f27d18(s32 x, s32 y, s32 id) {
    s32 cnt;
    s32 k;
    s32 i;
    s32 xx;
    s32 yy;
    u64 *p;

    cnt = func_001bb2e0(id);
    p = func_00f66b78(func_00f66ac8(*D_00F85160));
    p[0] = 0x131000070LL;
    p[1] = 78;
    p += 2;
    p[0] = 0;
    p[1] = 20;
    p += 2;
    p[0] = 0x50003;
    p[1] = 71;
    p += 2;
    p[0] = 0x0000740000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 68;
    p[1] = 66;
    p += 2;
    func_00f66b90(p);
    k = func_00f24f50(id);
    p = func_00f24738(x - 16, y, 32, 0x80800000, p);
    p = func_00f23a58(x - 16, y, k, 128, p);
    p = func_00f24e38(x + 20, y + 110, func_001baf08(func_001bb1d8(id)), 4, p);
    if (cnt < 4) {
        xx = x + 24;
        yy = y + 128;
        for (i = 0; i < cnt; i++) {
            p = func_00f23c20(xx, yy, 32, 0, 16, 16, 30, 128, p);
            xx += 16;
        }
        for (; i < 3; i++) {
            p = func_00f23c20(xx, yy, 48, 0, 16, 16, 30, 128, p);
            xx += 16;
        }
    } else {
        p = func_00f23c20(x + 40, y + 128, 64, 0, 16, 16, 30, 128, p);
    }
    p = func_00f66b78(p);
    p[0] = 0x5000D;
    p[1] = 71;
    p += 2;
    p[0] = 0x0000740000007000LL;
    p[1] = 24;
    p += 2;
    p[0] = 68;
    p[1] = 66;
    p += 2;
    func_00f66b90(p);
    func_00f66fe8(1, func_00f66ae0(p));
    *D_00F85160 = p;
}
