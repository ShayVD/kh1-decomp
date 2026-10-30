/* wm.x func_00f28448: matched by hand. */
#include "ovl.h"

typedef struct { s32 a, b, c, d; } T28;
extern u64 **D_00F85160;
extern s32 D_00F874F8[];
extern s32 D_00FBB33C;
extern s32 D_00FBB340;
extern T28 D_00FBB558;
u64 *func_00f66ac8(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
s32 func_00f66ae0(u64 *);
void func_00f66fe8(s32, s32);
u64 *func_00f241b0(s32, s32, s32, s32, s32, s32, u64 *);
u64 *func_00f23fe8(s32, s32, s32, s32, s32, s32, u64 *);
u64 *func_00f23a58(s32, s32, s32, s32, u64 *);
u64 *func_00f23c20(s32, s32, s32, s32, s32, s32, s32, s32, u64 *);
u64 *func_00f24e38(s32, s32, s32, s32, u64 *);
u64 *func_00f24ac8(s32, s32, s32, s32, u64 *);
u64 *func_00f24c80(s32, s32, s32, s32, u64 *);
u64 *func_001f0868(u64 *, s32, s32, s32, s32, s32, s32, s32);
s32 func_00f26e48(s32 *);
s32 func_001bb2e0(s32);
s32 func_001bb1d8(s32);
s32 func_001baf08(s32);
s32 func_001bb370(void);
s32 func_002193f0(void);
s32 func_00f2b8f0(s32);
s32 func_00f22ac8(void);
f32 cosf(f32);

void func_00f28448(s32 x, s32 y, s32 z, s32 *list) {
    s32 *q;
    u64 *p;
    s32 cnt, n, sum, i, xx, yy, h, a, b, w, k;
    f32 c;
    p = func_00f66b78(func_00f66ac8(*D_00F85160));
    p[0] = 0;
    p[1] = 20;
    yy = (0x740 - y) << 4;
    xx = (0x700 - x) << 4;
    p += 2;
    p[0] = 0x30003;
    p[1] = 71;
    p += 2;
    p[1] = 24;
    p[0] = (u64)xx | ((u64)yy << 32);

    p += 2;
    p[0] = 68;
    p[1] = 66;
    p += 2;
    func_00f66b90(p);
    p = func_00f241b0(0, -5, 512, 50, 8, 128, p);
    p = func_00f23fe8(0, 344, 512, 50, 8, 128, p);
    p = func_00f23a58(16, 8, 2, 128, p);
    if (list != 0) {
        n = 0;
        cnt = func_00f26e48(list);
        sum = 0;
        for (i = 0; list[i] != 0; i++) {
            if (func_001bb2e0(list[i]) >= 4) n++;
            sum += func_001baf08(func_001bb1d8(list[i]));
        }
        xx = 320;
        yy = 8 - z;
        if (func_001bb370()) {
            p = func_00f23c20(xx - D_00F874F8[0xA8], yy, D_00F874F8[0xA8] * func_002193f0(), 0,
                              D_00F874F8[0xA8], D_00F874F8[0xA9], 33, 128, p);
        }
        for (i = 0; i < n; i++) {
            p = func_00f23c20(xx, yy, 64, 0, 16, 16, 30, 128, p);
            xx += 16;
        }
        for (; i < cnt; i++) {
            p = func_00f23c20(xx, yy, 80, 0, 16, 16, 30, 128, p);
            xx += 16;
        }
        yy = 24 - z;
        p = func_00f23a58(320, yy, 11, 128, p);
        p = func_00f24e38(D_00F874F8[0x3A] + 324, yy, sum, 5, p);
        c = cosf((f32)(D_00FBB33C % 24) * 6.28318505f / 24.0f);
        b = c * 4.0f * 16.0f + 0.5f;
        a = c * 16.0f + 16.0f;
        yy = (z + 348) << 4;
        D_00FBB340 = 128 - a;
        p = func_00f24ac8(b + 256, yy, 4, D_00FBB340, p);
        p = func_00f24c80(((496 - D_00F874F8[0x17]) << 4) - b, yy, 4, D_00FBB340, p);
        p = func_00f66b78(p);
        p[0] = 0x017F015D01FF0000LL;
        p[1] = 64;
        p += 2;
        func_00f66b90(p);
        if (D_00FBB558.a) {
            i = D_00FBB558.b;
            w = z + i;
            xx = (512 - D_00F874F8[0x1C]) / 2;
            p = func_00f23a58(xx, w + 352, 5, 128, p);
            p = func_00f23a58(xx + 12, w + 357, 16, 128, p);
            xx = (D_00F874F8[0x53] + 12) / 2 + 256;
            yy = w + 356;
            p = func_001f0868(p, 1, 2, -128, xx, yy, func_00f2b8f0(func_002193f0() + 13), 16);
        }
        if (D_00FBB558.c) {
            i = D_00FBB558.d;
            w = z + i;
            p = func_00f23a58((512 - D_00F874F8[0x1C]) / 2, w + 352, 5, 128, p);
            yy = w + 356;
            p = func_001f0868(p, 1, 2, -128, 256, yy,
                              func_001bb370() ? func_00f2b8f0(25) : func_00f2b8f0(23), 16);
        }
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
    p[0] = 0x017F000001FF0000LL;
    p[1] = 64;
    p += 2;
    p[0] = 0x31000070;
    p[1] = 78;
    p += 2;
    func_00f66b90(p);
    func_00f66fe8(2, func_00f66ae0(p));
    *D_00F85160 = p;
    func_00f22ac8();
    D_00FBB33C++;
}
