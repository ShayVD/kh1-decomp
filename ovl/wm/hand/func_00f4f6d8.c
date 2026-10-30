/* wm.x func_00f4f6d8: matched by hand. */
#include "ovl.h"

typedef struct {
    u8 pad0[0x48];
    u8 x48[0x10D4 - 0x48];
    s32 rx;
    s32 ry;
} GbMap;
extern GbMap *D_00F9B540;
void func_001bbbd0(OvlMtx, void *);
u64 *func_00f4e0b0(u64 *, s32, s32);
void func_00f4e480(s32, u64 **, s32, f32 *, void *, s32, f32, f32);
u64 *func_00f66ac8(u64 *);
u64 *func_00f66ae0(u64 *);
void func_00f66f78(s32, u64 *);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void sceVu0RotMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0UnitMatrix(OvlMtx);

void func_00f4f6d8(s32 id, u64 **pp, s32 x, s32 y, s32 a4, f32 *scl, s32 flag, f32 ry, f32 f1, f32 s, f32 f3) {
    OvlMtx m;
    OvlMtx base;
    OvlMtx m2;
    OvlMtx m3;
    OvlVec r;
    OvlVec r2;
    OvlVec sv;
    s32 i;
    sceVu0UnitMatrix(base);
    r[0] = D_00F9B540->rx * 3.141592503f * (1.0f / 2048);
    r[1] = D_00F9B540->ry * 3.141592503f * (1.0f / 2048);
    r[2] = 0.0f;
    r[3] = 1.0f;
    sceVu0RotMatrix(m, base, r);
    if (scl == NULL) {
        for (i = 0; i < 3; i++)
            sv[i] = s;
    } else {
        for (i = 0; i < 3; i++)
            sv[i] = s * scl[i];
    }
    r2[0] = 0.0f;
    r2[1] = ry;
    r2[2] = 0.0f;
    r2[3] = 1.0f;
    sceVu0RotMatrix(m2, base, r2);
    sceVu0MulMatrix(m, m, m2);
    if (flag) {
        func_001bbbd0(m3, D_00F9B540->x48);
        sceVu0MulMatrix(m, m, m3);
    }
    *pp = func_00f66ac8(*pp);
    *pp = func_00f4e0b0(*pp, 2048 - x, 2048 - y);
    func_00f66f78(id, func_00f66ae0(*pp));
    func_00f4e480(id + 1, pp, a4, sv, m, 2, f1, f3);
}
