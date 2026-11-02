/* wm.x func_00f40750: matched by hand. */
#include "ovl.h"

#include "ovl.h"

typedef struct { s32 id; s32 a; s32 b; f32 val; u8 pad[0x590 - 16]; } S;
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
void func_00f62c98(f32 *, s32, f32, s32);
#else
void func_00f62c98(f32 *, s32, s32, f32);
static __inline__ void ee_00f62c98(f32 * x0, s32 x1, f32 x2, s32 x3) { func_00f62c98(x0, x1, x3, x2); }
#undef func_00f62c98
#define func_00f62c98 ee_00f62c98
#endif
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
