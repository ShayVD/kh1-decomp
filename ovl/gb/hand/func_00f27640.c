/* gb.x func_00f27640: matched by hand. */
#include "ovl.h"

typedef struct { u64 *p; u8 *w; u8 x8[1]; } GbCtx;
typedef struct { u8 pad[8]; u8 x8; } GbMdl;
typedef struct { u8 pad[24]; f32 x24; } GbMdlInfo;
typedef struct { s16 a, b; s32 c, d, e, f; } GbTexDef2;
extern u8 *D_00F56DC0;
extern GbTexDef2 D_00F61880;
GbMdl *func_001bb658(s32);
GbMdlInfo *func_00f23880(s32);
f32 func_00f27310(s32);
u64 *func_00f3f9d0(u64 *);
u64 *func_00f26520(u64 *, s32, s32, s32, s32);
u64 *func_00f26ca8(u64 *, s32, s32, s32, s32, s32, s32, s32, u64, u64);
u64 *func_00f26688(u64 *, s32, s32, s32, s32, s32, s32);
u64 *func_00f3f9e8(u64 *);
void func_00f3fe80(s32, u64 *);
void func_00f36e40(s32, s32, void *);
void func_00f36d58(void *, s32);
void func_00f36c00(void *, s32);
s32 func_00f25918(s32);
s32 func_00f25978(s32);
u8 *func_00f36ee0(void *, u8 *, s32, s32, s32, s32);
void func_00f375e8(void *);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0RotMatrixX(OvlMtx, OvlMtx, f32);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void sceVu0TransMatrix(OvlMtx, OvlMtx, f32 *);

s32 func_00f27640(s32 id, GbCtx *cx, s32 k, f32 *scl, f32 (*mtx)[4], s32 flag, f32 s) {
    OvlVec tr;
    OvlVec tr2;
    OvlMtx mt;
    OvlMtx mm;
    OvlMtx mw;
    OvlMtx ms;
    OvlMtx mr;
    OvlMtx mc;
    f32 (*gm)[4];
    GbMdl *e;
    GbMdlInfo *t;
    u8 *g;
    f32 z;
    s32 i, a, b;
    e = func_001bb658(k);
    sceVu0UnitMatrix(mr);
    sceVu0RotMatrixX(mr, mr, 3.141592503f);
    sceVu0MulMatrix(mtx, mtx, mr);
    t = func_00f23880(e->x8);
    tr[0] = 0.0f;
    tr[1] = 0.0f;
    tr[2] = 0.0f;
    sceVu0TransMatrix(mw, mtx, tr);
    sceVu0UnitMatrix(mc);
    if (scl != NULL) {
        for (i = 0; i < 3; i++)
            mc[i][i] = scl[i];
    }
    sceVu0MulMatrix(mw, mw, mc);
    if (flag) {
        z = t->x24;
        z *= 8.0f;
    } else {
        z = 3072.0f;
    }
    g = D_00F56DC0;
    sceVu0UnitMatrix(ms);
    s *= func_00f27310(k);
    gm = (f32 (*)[4])(g + 4112);
    tr2[0] = 0.0f;
    tr2[2] = z;
    tr2[3] = 1.0f;
    ms[0][0] = s;
    ms[1][1] = s;
    ms[2][2] = s;
    ms[3][3] = s;
    tr2[1] = 0.0f;
    sceVu0UnitMatrix(mt);
    sceVu0TransMatrix(mt, mt, tr2);
    cx->p = func_00f3f9d0(cx->p);
    cx->p = func_00f26520(cx->p, 400, 256, 256, 1);
    if (flag) {
        cx->p = func_00f26ca8(cx->p, 1920, 1920, 0, D_00F61880.c, D_00F61880.d, D_00F61880.e, D_00F61880.f, 0x3F80000080808080ULL, *(u64 *)(D_00F56DC0 + 8704));
        cx->p = func_00f26688(cx->p, 400, 256, 0, 0, 0, 255);
    }
    func_00f3fe80(id++, func_00f3f9e8(cx->p));
    func_00f36e40(id, id, cx->x8);
    id++;
    func_00f36d58(cx->x8, 0);
    sceVu0MulMatrix(mm, mt, mw);
    sceVu0MulMatrix((f32 (*)[4])(cx->w + 144), gm, mm);
    func_00f36c00(cx->w + 16, k);
    sceVu0MulMatrix((f32 (*)[4])(cx->w + 16), (f32 (*)[4])(cx->w + 16), ms);
    sceVu0MulMatrix((f32 (*)[4])(cx->w + 80), (f32 (*)[4])(g + 4176), mtx);
    a = func_00f25918(k);
    b = func_00f25978(k);
    cx->w = func_00f36ee0(cx->x8, cx->w, e->x8 + 1, 0, a, b);
    func_00f375e8(cx->x8);
    return id;
}
