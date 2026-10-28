/* xs_dumbo.x func_00f20aa8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad0[0x10]; OvlVec pos; u8 pad20[0xA4]; f32 fc4; u8 padc8[0x30C]; f32 f3d4; } Act;
typedef struct { s32 pad; f32 f4; f32 f8; } Gnd;
typedef struct { s32 f0; f32 f4; s32 f8; f32 fc; } Ctl;
typedef struct { Act *act; s32 id; } Cur;
Gnd *func_0014dab8(Act *);
s32 func_00122ff8(Act *);
void func_0012ec60(Act *, s32, f32 *);
void func_001315c0(Act *, s32, f32 *, f32);
void func_0014d988(Act *, Cur *, Ctl *, f32, f32, f32, f32);
typedef struct { u32 b0 : 5; u32 b5 : 1; u32 rest : 26; } F58;
typedef struct { u32 id : 8; u32 pad : 19; u32 b27 : 1; u32 b28 : 1; u32 rest : 3; } F90;
extern F58 D_002C5958;
extern F90 D_002E3190;
extern Cur D_002E31B0;
f32 fabsf(f32);
extern f32 D_00F3CA8C;
void func_00f20aa8(Act *o, s32 unused, Ctl *c) {
    OvlVec v;
    OvlVec w;
    Gnd *g;
    f32 h;

    g = func_0014dab8(o);
    if (g != NULL)
        h = g->f8 - o->pos[1];
    else
        h = o->f3d4;
    c->f4 = 0.0f;
    if (h < D_00F3CA8C) {
        c->f4 = -0.3f;
    } else {
        if (!(D_002C5958.b5) && (300.0f < h || o->fc4 < 0.866)) {
            c->f4 = 0.3f;
        } else if (D_002E3190.b27) {
            if ((D_002C5958.b5) || h < 275.0f)
                c->f4 = -0.3f;
        } else if (D_002E3190.b28) {
            D_00F3CA8C = 10.0f;
            if (35.0f < h)
                c->f4 = 0.3f;
        }
    }
    if (0.0f < c->fc)
        c->fc = 0.5f;
    if (!func_00122ff8(D_002E31B0.act))
        return;
    if (c->f4 != 0.0f)
        return;
    if (!(35.0f < h))
        return;
    if (!(D_002C5958.b5) && !(h < 275.0f))
        return;
    if (D_002E3190.id == 70) {
        func_0012ec60(D_002E31B0.act, D_002E31B0.id, v);
        func_001315c0(o, 0x8003, w, 0.0f);
        PlatVu0SubVector(v, v, w);
        if (30.0f < fabsf(v[1])) {
            c->f4 = v[1] < -0.3f ? -0.3f : (0.3f < v[1] ? 0.3f : v[1]);
        }
    } else if (0.0f < c->fc) {
        func_0014d988(o, &D_002E31B0, c, 0.5f, 200.0f, 0.8f, 1.0f);
    }
}
