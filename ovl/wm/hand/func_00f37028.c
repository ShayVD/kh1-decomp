/* wm.x func_00f37028: matched by hand. */
#include "ovl.h"

typedef struct { s32 id; s32 a; s32 b; f32 val; s32 pad2; s32 dir; } Sub;
typedef struct { OvlMtx m0; OvlMtx m1; OvlMtx m2; OvlMtx m3[16]; OvlMtx m4[2]; Sub s; u8 pad2[0x590 - 0x558]; } W;
typedef struct { f32 f0; u8 kind; u8 pad[3]; f32 tx; f32 ty; f32 tz; f32 rx; f32 ry; f32 rz; u16 snd; } K;
void func_00f62ea0(OvlVec, f32, s32);
extern W *D_00F864C0;

void func_00f37028(OvlMtx arg0, K *k) {
    OvlVec v;
    OvlMtx r;
    OvlMtx m;
    func_00f62ea0(v, k->f0, D_00F864C0->s.id);
    PlatVu0UnitMatrix(m);
    PlatVu0TransMatrix(m, m, v);
    PlatVu0MulMatrix(m, D_00F864C0->m0, m);
    PlatVu0UnitMatrix(r);
    PlatVu0RotMatrixX(r, r, -k->rx);
    PlatVu0RotMatrixY(r, r, -k->ry);
    PlatVu0RotMatrixZ(r, r, k->rz);
    v[0] = k->tx + m[3][0];
    v[1] = m[3][1] - k->ty;
    v[2] = m[3][2] - k->tz;
    v[3] = 1.0f;
    PlatVu0TransMatrix(arg0, r, v);
    PlatVu0UnitMatrix(m);
    PlatVu0RotMatrixY(m, m, 3.141592503f);
    PlatVu0MulMatrix(arg0, arg0, m);
}
