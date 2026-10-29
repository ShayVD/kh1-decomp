/* wm.x func_00f32b00: matched by hand. */
#include "ovl.h"

void sceVu0UnitMatrix(OvlMtx);
void sceVu0RotMatrixZ(OvlMtx, OvlMtx, f32);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void sceVu0TransMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0FTOI4Vector(s32 *, OvlVec);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);

u64 *func_00f32b00(u64 *p, u32 col, u64 tex, s32 x, s32 y, s32 w, s32 h, s32 u, f32 ang, f32 sc, s32 v) {
    OvlMtx s;
    OvlMtx m;
    s32 iv[4][4];
    OvlVec t;
    s32 i;
    f32 hw, hh;
    s32 u0, v0, u1, v1;

    t[0] = x;
    t[1] = y;
    t[2] = 0.0f;
    t[3] = 0.0f;
    sceVu0UnitMatrix(m);
    sceVu0UnitMatrix(s);
    sceVu0RotMatrixZ(m, m, ang);
    s[0][0] = sc;
    s[1][1] = sc;
    s[2][2] = sc;
    sceVu0MulMatrix(m, m, s);
    sceVu0TransMatrix(m, m, t);
    hw = w * 0.5f;
    hh = h * 0.5f;
    s[3][0] = hw;
    s[3][1] = hh;
    s[1][0] = hw;
    s[2][1] = hh;
    s[0][0] = -hw;
    s[2][0] = -hw;
    s[0][1] = -hh;
    s[1][1] = -hh;
    for (i = 3; i >= 0; i--) {
        s[3 - i][2] = 0.0f;
        s[3 - i][3] = 1.0f;
    }
    sceVu0MulMatrix(s, m, s);
    for (i = 0; i < 4; i++) {
        sceVu0FTOI4Vector(iv[i], s[i]);
    }
    p = func_00f66b78(p);
    p[0] = 340;
    p[1] = 0;
    p += 2;
    p[0] = (u64)col | 0x3F80000000000000;
    p[1] = 1;
    p += 2;
    p[0] = tex;
    p[1] = 6;
    p += 2;
    u0 = u * 16 + 1;
    v0 = v * 16 + 1;
    u1 = (u + w) * 16 - 1;
    v1 = (v + h) * 16 - 1;
    p[0] = u0 | ((u64)v0 << 16);
    p[1] = 3;
    p += 2;
    p[0] = (u64)iv[0][0] | ((u64)iv[0][1] << 16);
    p[1] = 5;
    p += 2;
    p[0] = u1 | ((u64)v0 << 16);
    p[1] = 3;
    p += 2;
    p[0] = (u64)iv[1][0] | ((u64)iv[1][1] << 16);
    p[1] = 5;
    p += 2;
    p[0] = u0 | ((u64)v1 << 16);
    p[1] = 3;
    p += 2;
    p[0] = (u64)iv[2][0] | ((u64)iv[2][1] << 16);
    p[1] = 5;
    p += 2;
    p[0] = u1 | ((u64)v1 << 16);
    p[1] = 3;
    p += 2;
    p[0] = (u64)iv[3][0] | ((u64)iv[3][1] << 16);
    p[1] = 5;
    p += 2;
    func_00f66b90(p);
    return p;
}
