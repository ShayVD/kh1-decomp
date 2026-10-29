/* wm.x func_00f606a0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad0[6]; u16 x6; u16 x8; u16 xa; } GbObj;
typedef struct { f32 v[4][4]; f32 pos[4]; f32 rot[4]; } GbXf;
extern u8 *D_00F9B540;
extern u8 D_00F9B548[];
extern GbObj D_0108DE90;
void func_00f5a478(s32);
void func_00f4a190(s32, s32, f32);
s32 func_001bc4a8(void);
s32 func_001bc4b8(s32);
void func_001ba060(GbObj *, s32);
GbObj *func_001ba9d8(s32);
void func_001bebd0(OvlMtx *, GbXf *, void *);
void func_00f5d118(s32, s32, void *, s32, s32, void *, void *);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0TransMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);

void func_00f606a0(s32 a0, s32 x, s32 y, s32 idx, s32 a4, OvlMtx base, s32 flag, f32 f) {
    OvlMtx out[4];
    GbXf xf;
    OvlMtx m;
    OvlVec v;
    GbObj *o;
    func_00f5a478(flag);
    func_00f4a190(a0, a4, f);
    o = &D_0108DE90;
    func_001ba060(o, idx - 71);
    xf.pos[3] = 1.0f;
    xf.v[0][2] = -4624.0f;
    xf.v[1][0] = 0.0f;
    xf.v[1][1] = 0.0f;
    xf.v[1][2] = 1.0f;
    xf.v[1][3] = 1.0f;
    xf.v[2][0] = 0.0f;
    xf.v[2][1] = 1.0f;
    xf.v[2][2] = 0.0f;
    xf.v[2][3] = 1.0f;
    xf.v[3][0] = 0.0f;
    v[1] = o->x8 * 200.0f * 0.5f;
    v[0] = -(o->x6 * 200.0f) * 0.5f;
    v[2] = -(o->xa * 200.0f) * 0.5f;
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
    xf.pos[0] = 0.0f;
    xf.pos[1] = 0.0f;
    xf.pos[2] = 0.0f;
    xf.pos[3] = 1.0f;
    sceVu0UnitMatrix(m);
    sceVu0TransMatrix(m, m, v);
    sceVu0MulMatrix(m, base, m);
    func_001bebd0(out, &xf, D_00F9B540 + 4112);
    sceVu0MulMatrix(out[3], out[3], m);
    func_00f5d118(0, 11201, D_00F9B548, 2048 - x, 2048 - y, out, o);
    func_00f4a190(0, 0, 0.0f);
}
