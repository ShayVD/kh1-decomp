/* wm.x func_00f407f8: matched by hand. */
#include "ovl.h"

typedef struct { s32 id; s32 a; s32 b; f32 val; s32 pad2; s32 dir; } Sub;
typedef struct { OvlMtx m0; OvlMtx m1; OvlMtx m2; OvlMtx m3[16]; OvlMtx m4[2]; Sub s; u8 pad2[0x590 - 0x558]; } W;
typedef struct { f32 f0; u8 kind; u8 pad[3]; f32 tx; f32 ty; f32 tz; f32 rx; f32 ry; f32 rz; u16 snd; } K;
void func_001becb8(OvlMtx, OvlVec, s32);
K *func_00f62b98(s32, s32);
void func_00f62c78(s32, s32);
void func_00f62c98(OvlVec, f32, s32, s32);
void func_00f62ea0(OvlVec, f32, s32);
extern W *D_00F864C0;

void func_00f407f8(OvlMtx arg0, OvlMtx arg1, s32 arg2) {
    OvlVec v;
    OvlVec r;
    OvlMtx m;
    OvlMtx t;
    OvlMtx n;
    s32 id;
    K *k;
    s32 kd;
    id = D_00F864C0->s.id;
    k = func_00f62b98(arg2, id);
    func_00f62c78(k->snd, id);
    func_00f62ea0(v, k->f0, id);
    func_00f62c98(r, k->f0, 1, id);
    PlatVu0UnitMatrix(m);
    PlatVu0TransMatrix(m, m, v);
    func_001becb8(n, r, 1);
    if (D_00F864C0->s.dir != 0) {
        PlatVu0UnitMatrix(t);
        PlatVu0RotMatrixY(t, t, 3.141592503f);
        PlatVu0MulMatrix(n, n, t);
    }
    PlatVu0MulMatrix(m, m, n);
    PlatVu0MulMatrix(m, D_00F864C0->m0, m);
    PlatVu0MulMatrix(n, D_00F864C0->m1, n);
    kd = k->kind;
    if (kd < 4) if (kd >= 2) { /* nested so gcc does not fold it into one range test */
        PlatVu0UnitMatrix(t);
        PlatVu0RotMatrixX(t, t, k->rx);
        PlatVu0RotMatrixY(t, t, k->ry);
        PlatVu0RotMatrixZ(t, t, k->rz);
        PlatVu0MulMatrix(n, n, t);
        v[0] = k->tx;
        v[1] = k->ty;
        v[2] = k->tz;
        v[3] = 1.0f;
        PlatVu0TransMatrix(t, t, v);
        PlatVu0MulMatrix(m, m, t);
    }
    PlatVu0CopyMatrix(arg0, m);
    if (arg1 != 0) {
        PlatVu0CopyMatrix(arg1, n);
    }
}
