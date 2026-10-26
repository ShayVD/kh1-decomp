/* wm.x func_00f41458: matched by hand. */
#include "ovl.h"

#include "ovl.h"

typedef struct { u8 pad[0x58]; f32 h; } Q;
void func_001bf3e8(OvlMtx, f32 *);
void func_001bf710(f32 *, f32 *, f32 *, f32);
void func_001bf888(f32 *, OvlMtx);
void func_001bfac8(void);
Q *func_00f3b4e0(s32);
extern OvlMtx D_00F85200;
extern s32 D_00F9B2C8;

void func_00f41458(void) {
    OvlMtx m0;
    OvlMtx m1;
    OvlMtx u0; /* u0..u2 unused, keep the frame layout */
    OvlVec u1;
    OvlVec u2;
    OvlVec t2;
    OvlVec t1;
    OvlVec rot;
    OvlVec q;
    OvlVec qa;
    OvlVec qb;
    Q *o;
    s32 i;
    f32 t, n;
    PlatVu0CopyMatrix(m0, D_00F85200);
    o = func_00f3b4e0(D_00F9B2C8);
    if (o == 0) return;
    t1[2] = 0.0f;
    t1[0] = 0.0f;
    t1[1] = 0.0f;
    t1[3] = 1.0f;
    t1[2] = -o->h;
    rot[0] = 0.0f;
    rot[1] = 0.0f;
    rot[2] = 0.0f;
    rot[3] = 1.0f;
    t2[3] = 1.0f;
    t2[2] = 6000.0f;
    t2[0] = 0.0f;
    t2[1] = 0.0f;
    PlatVu0UnitMatrix(m1);
    PlatVu0TransMatrix(m1, m1, t1);
    PlatVu0RotMatrix(m1, m1, rot);
    PlatVu0TransMatrix(m1, m1, t2);
    func_001bf888(qa, m0);
    func_001bf888(qb, m1);
    n = 60.0f;
    for (i = 0; i < 60; i++) {
        t = i / n;
        PlatVu0UnitMatrix(D_00F85200);
        func_001bf710(q, qa, qb, t);
        func_001bf3e8(D_00F85200, q);
        D_00F85200[3][0] = (m1[3][0] - m0[3][0]) * i / n + m0[3][0];
        D_00F85200[3][1] = (m1[3][1] - m0[3][1]) * i / n + m0[3][1];
        D_00F85200[3][2] = (m1[3][2] - m0[3][2]) * i / n + m0[3][2];
        func_001bfac8();
    }
    PlatVu0CopyMatrix(D_00F85200, m1);
}
