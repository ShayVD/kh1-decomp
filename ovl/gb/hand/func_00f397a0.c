/* gb.x func_00f397a0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad0[6]; u16 x6; u16 x8; u16 xa; } GbObj;
typedef struct { f32 v[4][4]; f32 pos[4]; f32 rot[4]; } GbXf;
extern u8 *D_00F56DC0;
extern u8 D_00F56DC8[];
extern GbObj D_00F816D0;
void func_00f33380(s32);
void func_00f23098(s32, s32, f32);
s32 func_001bc4a8(void);
s32 func_001bc4b8(s32);
void func_001ba060(GbObj *, s32);
GbObj *func_001ba9d8(s32);
void func_001bebd0(OvlMtx *, GbXf *, void *);
void func_00f36020(s32, s32, void *, s32, s32, void *, void *);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0TransMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);

void func_00f397a0(s32 a0, s32 x, s32 y, s32 idx, s32 a4, OvlMtx base, s32 flag, f32 f) {
    OvlMtx out[4];
    GbXf xf;
    OvlMtx m;
    OvlVec v;
    GbObj *o;
    if (flag == 0)
        return;
    func_00f33380(flag);
    if (idx < 0)
        return;
    func_00f23098(a0, a4, f);
    if (idx == 0) {
        o = (GbObj *)(D_00F56DC0 + 160);
    } else if (--idx < func_001bc4a8()) {
        func_001ba060(&D_00F816D0, func_001bc4b8(idx));
        o = &D_00F816D0;
    } else {
        o = func_001ba9d8(idx - func_001bc4a8());
    }
    xf.v[0][2] = -4624.0f;
    xf.v[1][0] = 0.0f;
    xf.v[1][1] = 0.0f;
    xf.v[1][2] = 1.0f;
    xf.v[1][3] = 1.0f;
    xf.v[2][0] = 0.0f;
    xf.v[2][1] = 1.0f;
    xf.v[2][2] = 0.0f;
    xf.v[2][3] = 1.0f;
    v[1] = o->x8 * 200.0f * 0.5f;
    v[0] = -(o->x6 * 200.0f) * 0.5f;
    v[2] = -(o->xa * 200.0f) * 0.5f;
    xf.v[3][0] = 0.0f;
    xf.v[3][1] = 0.0f;
    xf.v[3][2] = 0.0f;
    xf.v[3][3] = 1.0f;
    xf.v[0][0] = 0.0f;
    xf.v[0][1] = 0.0f;
    xf.v[0][3] = 1.0f;
    xf.rot[0] = 0.0f;
    xf.rot[1] = 0.0f;
    xf.rot[2] = 0.0f;
    xf.rot[3] = 1.0f;
    v[3] = 1.0f;
    xf.pos[3] = 1.0f;
    xf.pos[0] = 0.0f;
    xf.pos[1] = 0.0f;
    xf.pos[2] = 0.0f;
    sceVu0UnitMatrix(m);
    sceVu0TransMatrix(m, m, v);
    sceVu0MulMatrix(m, base, m);
    func_001bebd0(out, &xf, D_00F56DC0 + 4112);
    sceVu0MulMatrix(out[3], out[3], m);
    func_00f36020(0, 11201, D_00F56DC8, 2048 - x, 2048 - y, out, o);
    func_00f23098(0, 0, 0.0f);
}
