/* xl_limit.x func_00f206e8: matched by hand. */
#include "ovl.h"

typedef struct { s32 tgt; s32 part; } Tgt;
typedef struct {
    u8 pad[0x10];
    OvlVec pos;
    OvlVec dir;
    f32 timer;
    f32 turn;
    Tgt t;
    void *res;
    void *eff;
    s32 wait;
} Obj;
typedef struct { u8 pad[0xD0]; OvlMtx m; } Chr;
void func_0011efa8(void *, void *, s32, s32);
void func_0011ef10(s32, s32 (*)());
Obj *func_0011f090(void *, s32, s32 (*)());
void func_001315c0(Chr *, s32, f32 *, f32);
f32 func_00176850(void);
f32 sinf(f32);
f32 cosf(f32);
s32 func_00f20690();
s32 func_00f20400();
extern OvlMtx D_002C58D0;
extern u8 D_00F23490[];
extern u8 D_00F234A0[];

void func_00f206e8(Chr *c, Tgt *tg, s32 n) {
    OvlVec pos;
    OvlVec v;
    OvlMtx rot;
    s32 i;
    Obj *o;

    func_0011efa8(D_00F23490, D_00F234A0, 80, 30);
    func_0011ef10(0x21728, func_00f20690);
    func_001315c0(c, 48, pos, 1.0f);
    v[0] = 0.0f;
    v[1] = -sinf(1.5707962f);
    v[2] = -cosf(1.5707962f);
    v[3] = 0.0f;
    sceVu0RotMatrixZ(rot, D_002C58D0, 6.2831855f / n);
    for (i = 0; i < n; i++) {
        o = func_0011f090(D_00F23490, 0, func_00f20400);
        sceVu0CopyVector(o->pos, pos);
        sceVu0ApplyMatrix(o->dir, c->m, v);
        sceVu0ApplyMatrix(v, rot, v);
        o->timer = func_00176850() * 60.0f + 180.0f;
        o->t = *tg;
        o->res = 0;
        o->turn = func_00176850() * 0.39999998f + 0.39999998f;
        o->eff = 0;
        o->wait = i % 8;
    }
}
