/* gb.x func_00f28090: matched by hand. */
#include "ovl.h"

typedef struct { u64 v[8]; } GbQ8;
typedef struct { u64 v[2]; } GbQ2;
extern GbQ8 D_00F71680;
extern GbQ8 D_00F716C0;
extern GbQ2 D_00F71700;
void *memset(void *, s32, u32);
s32 func_00f27640(s32, u64 **, s32, s32, OvlMtx, s32, f32);
u64 *func_00f3f9d0(u64 *);
u64 *func_00f26500(u64 *);
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);
u64 *func_00f37618(u64 *, f32 (*)[4], GbQ8 *, u64, s32 *, OvlMtx);
u64 *func_00f3f9e8(u64 *);
void func_00f3fe80(s32, u64 *);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0RotMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0TransMatrix(OvlMtx, OvlMtx, f32 *);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void sceVu0ViewScreenMatrix(OvlMtx, f32, f32, f32, f32, f32, f32, f32, f32, f32);

static inline void xyoff(u64 **pp, s32 x, s32 y) {
    u64 *p = func_00f3fa80(*pp);
    u64 *q;
    p[0] = (u64)(x << 4) | ((u64)(y << 4) << 32);
    p[1] = 24;
    q = p + 2;
    q[0] = 13;
    q[1] = 71;
    *pp = q + 2;
    func_00f3fa98(q + 2);
}

s32 func_00f28090(s32 id, u64 **pp, s32 x, s32 y, s32 a4, s32 size, f32 ry0, f32 ry1, f32 f) {
    f32 A[4][4];
    f32 B[4][4];
    GbQ8 c = D_00F71680;
    GbQ8 d = D_00F716C0;
    s32 col[4];
    GbQ2 t = D_00F71700;
    OvlMtx vs;
    OvlMtx m;
    OvlMtx rot;
    OvlMtx unit;
    OvlVec rv;
    OvlVec r2;
    double v;
    u64 *p;
    u64 *q;
    u64 xy;
    s32 h, i, k;
    memset(rv, 0, 16);
    h = size / 2;
    rv[3] = 1.0f;
    A[0][0] = -h;
    A[0][1] = h;
    A[1][0] = 0.0f;
    A[1][1] = h;
    A[2][0] = -h;
    A[2][1] = -h;
    A[3][0] = 0.0f;
    A[3][1] = -h;
    B[0][0] = 0.0f;
    B[0][1] = h;
    B[1][0] = h;
    B[1][1] = h;
    B[2][0] = 0.0f;
    B[2][1] = -h;
    B[3][0] = h;
    B[3][1] = -h;
    for (i = 0; i < 4; i++) {
        A[i][2] = 0.0f;
        A[i][3] = 1.0f;
        B[i][2] = 0.0f;
        B[i][3] = 1.0f;
    }
    sceVu0UnitMatrix(unit);
    r2[0] = 3.141592503f / 8;
    r2[1] = 0.0f;
    r2[2] = 0.0f;
    sceVu0RotMatrix(rot, unit, r2);
    id = func_00f27640(id, pp, a4, 0, rot, 1, f);
    sceVu0ViewScreenMatrix(vs, 512.0f, 1.0f, -1.0f, 2048.0f, 2048.0f, 1.0f, 16777000.0f, 1.0f, 65536.0f);
    *pp = func_00f3f9d0(*pp);

    rv[1] = ry0;
    sceVu0UnitMatrix(m);
    sceVu0RotMatrix(m, m, rv);
    sceVu0TransMatrix(m, m, (f32 *)&t);
    sceVu0MulMatrix(m, vs, m);
    v = ry0 * 2.0f / 3.141592503f * 100.0f;
    if (v < 0.0)
        v = 0.0 - v;
    k = (f32)v;
    col[3] = 128;
    k = 128 - k;
    col[0] = k;
    col[1] = k;
    col[2] = k;
    *pp = func_00f26500(*pp);
    xyoff(pp, 2048 - x, 2048 - y);
    *pp = func_00f37618(*pp, A, &c, 0x620013200ULL, col, m);

    rv[1] = ry1;
    sceVu0UnitMatrix(m);
    sceVu0RotMatrix(m, m, rv);
    sceVu0TransMatrix(m, m, (f32 *)&t);
    sceVu0MulMatrix(m, vs, m);
    v = ry1 * 2.0f / 3.141592503f * 100.0f;
    if (v < 0.0)
        v = 0.0 - v;
    k = (f32)v;
    col[3] = 128;
    k = 128 - k;
    col[0] = k;
    col[1] = k;
    col[2] = k;
    *pp = func_00f37618(*pp, B, &d, 0x620013200ULL, col, m);
    p = func_00f3fa80(*pp);
    p[0] = 0x0000740000007000ULL;
    p[1] = 24;
    q = p + 2;
    q[0] = 0x5000D;
    q[1] = 71;
    *pp = q + 2;
    func_00f3fa98(q + 2);
    func_00f3fe80(id, func_00f3f9e8(*pp));
    return id + 1;
}
