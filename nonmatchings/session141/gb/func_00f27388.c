/* 1 word / score 2: only the branch on D_00F61364 before the scale multiply is bnezl here and bnez in the target (same delay-slot copy of addiu s0,sp,32 in both). Tried !x, braces, ?:, swapped if/else on the later test, scale = f()*scale, moving the test, every flag mode. */
#include "ovl.h"

typedef struct { u8 pad0[8]; u8 kind; } GbEnt;
typedef struct { u8 pad0[0x10]; OvlMtx local; OvlMtx view; OvlMtx world; } GbPkt;
typedef struct { u8 pad0[4]; GbPkt *pkt; u8 sub[1]; } GbCtx;
typedef struct { u8 pad0[0x1010]; OvlMtx view; OvlMtx proj; } GbWorld;
extern GbWorld *D_00F56DC0;
extern s32 D_00F61364;
GbEnt *func_001bb658(s32);
s32 func_00f23880(s32);
f32 func_00f27310(s32);
void func_00f36e40(s32, s32, void *);
void func_00f36e98(s32, s32, void *);
void func_00f36d58(void *, s32);
void func_00f36c00(void *, s32);
s32 func_00f25918(s32);
s32 func_00f25978(s32);
GbPkt *func_00f36ee0(void *, GbPkt *, s32, s32, s32, s32);
void func_00f375e8(void *);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void sceVu0RotMatrixX(OvlMtx, OvlMtx, f32);
void sceVu0TransMatrix(OvlMtx, OvlMtx, OvlVec);

s32 func_00f27388(s32 id, GbCtx *c, s32 obj, f32 *pos, OvlMtx m, s32 flags, f32 w, f32 scale) {
    OvlVec v;
    OvlVec tv;
    OvlMtx tr;
    OvlMtx mw;
    OvlMtx mt;
    OvlMtx ms;
    OvlMtx rx;
    OvlMtx pad1;
    OvlMtx pad2;
    OvlMtx sc;
    GbEnt *e;
    f32 (*view)[4];
    s32 i;
    e = func_001bb658(obj);
    sceVu0UnitMatrix(rx);
    sceVu0RotMatrixX(rx, rx, 3.1415927f);
    sceVu0MulMatrix(m, m, rx);
    func_00f23880(e->kind);
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    sceVu0TransMatrix(mt, m, v);
    sceVu0UnitMatrix(ms);
    if (pos != NULL) {
        for (i = 0; i < 3; i++)
            ms[i][i] = pos[i];
    }
    sceVu0MulMatrix(mt, mt, ms);
    view = D_00F56DC0->view;
    sceVu0UnitMatrix(sc);
    if (D_00F61364 == 0)
        scale *= func_00f27310(obj);
    sc[0][0] = scale;
    sc[1][1] = scale;
    sc[2][2] = scale;
    sc[3][3] = scale;
    tv[0] = 0.0f;
    tv[1] = 0.0f;
    tv[2] = 3072.0f;
    tv[3] = 1.0f;
    sceVu0UnitMatrix(tr);
    sceVu0TransMatrix(tr, tr, tv);
    if (D_00F61364 == 0)
        func_00f36e40(id, id, c->sub);
    else
        func_00f36e98(id, id, c->sub);
    id++;
    func_00f36d58(c->sub, flags & 2);
    sceVu0MulMatrix(mw, tr, mt);
    sceVu0MulMatrix(c->pkt->world, view, mw);
    func_00f36c00(c->pkt->local, obj);
    sceVu0MulMatrix(c->pkt->local, c->pkt->local, sc);
    c->pkt->local[3][3] = w;
    sceVu0MulMatrix(c->pkt->view, view + 4, m);
    c->pkt = func_00f36ee0(c->sub, c->pkt, e->kind + 1, 0, func_00f25918(obj), func_00f25978(obj));
    func_00f375e8(c->sub);
    return id;
}
