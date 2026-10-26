/* wm.x func_00f40750: matched by hand. */
#include "ovl.h"

#include "ovl.h"

typedef struct { s32 id; s32 a; s32 b; f32 val; u8 pad[0x590 - 16]; } S;
void func_00f62c98(f32 *, s32, f32, s32);
void func_001becb8(OvlMtx, f32 *, s32);
extern S D_00F86A40[];

void func_00f40750(s32 i, OvlMtx m) {
    OvlMtx r;
    OvlVec v;
    S *s;
    s = &D_00F86A40[i];
    func_00f62c98(v, 1, s->val, s->id);
    PlatVu0UnitMatrix(m);
    func_001becb8(m, v, 0);
    PlatVu0TransposeMatrix(m, m);
    PlatVu0UnitMatrix(r);
    PlatVu0RotMatrixZ(r, r, 3.1415927f);
    PlatVu0MulMatrix(m, r, m);
}
