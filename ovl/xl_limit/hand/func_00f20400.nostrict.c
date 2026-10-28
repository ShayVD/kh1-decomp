/* xl_limit.x func_00f20400: matched by hand. */
#include "ovl.h"

typedef struct { f32 *pos; u8 pad[0xC]; u8 *flag; s32 state; } Res;
typedef struct { union { u64 f; struct { s32 lo, hi; } w; } u; s32 w8; u8 pad[4]; OvlVec pos; } Eff;
typedef struct {
    u8 pad[0x10];
    OvlVec pos;
    OvlVec dir;
    f32 timer;
    f32 turn;
    s32 tgt;
    s32 part;
    Res *res;
    Eff *eff;
    s32 wait;
} Obj;
Res *func_00147c98(s32, s32, s32);
s32 func_001477e0(s32);
Eff *func_0014a4a8(s32, s32, s32);
void func_0014a898(Eff *, f32 *);
void func_00176310(Res *);
s32 func_00122ff8(s32);
f32 func_0012ec60(s32, s32, f32 *);
s32 func_0012ef30(s32, f32 *, f32 *, f32);
void func_00f202d8(Obj *, f32 *, f32);
extern f32 D_002BBDFC;
extern s32 D_002E26A0;
extern s32 D_00F23208;

s32 func_00f20400(Obj *o) {
    OvlVec v;
    s32 t;
    f32 f;

    if (o->res == NULL) {
        o->res = func_00147c98(D_00F23208, 7, 20000);
    }
    if (o->eff == NULL && o->wait-- <= 0) {
        o->eff = func_0014a4a8(D_002E26A0, 0, func_001477e0(15));
        o->eff->u.f |= 0x800000;
        o->eff->u.f |= 0x80;
        o->eff->w8 = D_00F23208;
        func_0014a898(o->eff, o->pos);
    }
    sceVu0CopyVector(o->res->pos, o->pos);
    if (o->eff != NULL && o->eff->u.w.hi != 0) {
        func_00176310(o->res);
        return 4;
    }
    if (func_00122ff8(o->tgt) != 0) {
        func_0012ec60(o->tgt, o->part, v);
    } else {
        t = func_0012ef30(D_002E26A0, o->pos, o->dir, 1000.0f);
        if (t != 0) {
            o->tgt = t;
            o->part = -1;
            func_0012ec60(t, -1, v);
        } else {
            sceVu0CopyVector(v, o->dir);
        }
    }
    sceVu0SubVector(v, v, o->pos);
    sceVu0Normalize(v, v);
    func_00f202d8(o, v, o->turn);
    sceVu0ScaleVector(v, o->dir, D_002BBDFC * 12.0f);
    sceVu0AddVector(o->pos, o->pos, v);
    if (o->eff != NULL) {
        sceVu0CopyVector(o->eff->pos, o->pos);
        o->eff->u.f = (o->eff->u.f & ~0xC) | 4;
    }
    if (o->timer > 0.0f) {
        o->timer -= D_002BBDFC;
        if (o->timer <= 0.0f) {
            *o->res->flag = 1;
        }
    } else if (o->res == NULL || (o->res->state & 3) != 1) {
        return 4;
    }
    return 0;
}
