/* wm.x func_00f4eaa0: matched by hand. */
#include "ovl.h"

typedef struct {
    u8 pad0[0x10D4];
    s32 rx;
    s32 ry;
} GbMap;
extern GbMap *D_00F9B540;
/* A GIF A+D qword; the pointer member puts it in an alias set with u64 *, which keeps the first *pp store (a struct of two u64 lets flow delete it). */
typedef union { struct { u64 data, addr; }; u64 *ptr; } GbQw;
void func_00f4e480(s32, u64 **, s32, s32, void *, s32, f32, f32);
u64 *func_00f66ac8(u64 *);
u64 *func_00f66ae0(u64 *);
void func_00f66f78(s32, u64 *);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void sceVu0RotMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0UnitMatrix(OvlMtx);

void func_00f4eaa0(s32 id, u64 **pp, s32 x, s32 y, s32 a4, s32 a5, OvlMtx *base, f32 f0, f32 f1) {
    OvlMtx m;
    OvlVec r;
    u64 *p;
    GbQw *q;
    f32 ax = D_00F9B540->rx * 3.141592503f * (1.0f / 2048);
    f32 ay = D_00F9B540->ry * 3.141592503f * (1.0f / 2048);
    r[0] = ax;
    r[1] = ay;
    r[2] = 0.0f;
    r[3] = 1.0f;
    sceVu0UnitMatrix(m);
    sceVu0RotMatrix(m, m, r);
    if (base != NULL)
        sceVu0MulMatrix(m, m, *base);
    p = func_00f66ac8(*pp);
    *pp = p;
    q = (GbQw *)p;
    q->data = 0x1000000000008001;
    q->addr = 14;
    q++;
    q->addr = 0x18;
    q->data = (s64)(0x8000 - x) | ((s64)(0x8000 - y) << 32);
    q++;
    *pp = (u64 *)q;
    func_00f66f78(id, func_00f66ae0((u64 *)q));
    func_00f4e480(id + 1, pp, a4, a5, m, 0, f0, f1);
}
