/* wm.x func_00f3de48: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[12]; u8 r[4]; u8 pad2[3]; u8 id; } T;
s32 rand(void);
void func_001bf048(OvlMtx, OvlMtx);
s32 func_001ba3f0(s32);
s32 func_00f2c0c0(s32);
s32 func_001ba458(s32);
void func_00f3dd60(s32, OvlVec);
extern OvlMtx *D_00F864C0;

void func_00f3de48(f32 *pos, T *t) {
    OvlMtx m;
    OvlVec v;
    s32 id = -1;
    s32 any = 0;
    s32 k, p;
    f32 f;
    pos[0] -= (*D_00F864C0)[3][0];
    pos[1] -= (*D_00F864C0)[3][1];
    pos[2] -= (*D_00F864C0)[3][2];
    func_001bf048(m, *D_00F864C0);
    PlatVu0TransposeMatrix(m, m);
    PlatVu0ApplyMatrix(v, m, pos);
    k = t->id;
    if (k < 71 || k >= 119 || func_001ba3f0(k) + func_00f2c0c0(k) < func_001ba458(k)) any = 1;
    if (any) {
        f = rand();
        f = f / 2147483520.0f;
        p = f * 100.0f;
        if (p >= 0 && p < 10) id = t->id;
    }
    if (id < 0) {
        f = rand();
        f = f / 2147483520.0f;
        p = f * 100.0f;
        if (p < 40) id = t->r[0];
        else if (p < 70) id = t->r[1];
        else if (p < 90) id = t->r[2];
        else id = t->r[3];
    }
    if (id > 0 && id != 0xFF) func_00f3dd60(id, v);
}
