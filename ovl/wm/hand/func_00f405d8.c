/* wm.x func_00f405d8: matched by hand. */
#include "ovl.h"

typedef struct { s32 id; s32 a; s32 b; f32 val; s32 pad2; s32 dir; } Sub;
typedef struct { OvlMtx m0; OvlMtx m1; OvlMtx m2; OvlMtx m3[16]; OvlMtx m4[2]; Sub s; u8 pad2[0x590 - 0x558]; } W;
void func_001becb8(OvlMtx, OvlVec, s32);
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
void func_00f62c98(OvlVec, f32, s32, s32);
#else
void func_00f62c98(OvlVec, s32, s32, f32);
static __inline__ void ee_00f62c98(OvlVec x0, f32 x1, s32 x2, s32 x3) { func_00f62c98(x0, x2, x3, x1); }
#undef func_00f62c98
#define func_00f62c98 ee_00f62c98
#endif
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
void func_00f62ea0(OvlVec, f32, s32);
#else
void func_00f62ea0(f32, OvlVec, s32);
static __inline__ void ee_00f62ea0(OvlVec x0, f32 x1, s32 x2) { func_00f62ea0(x1, x0, x2); }
#undef func_00f62ea0
#define func_00f62ea0 ee_00f62ea0
#endif
extern W D_00F86500[];

void func_00f405d8(s32 arg0, OvlMtx arg1, OvlMtx arg2) {
    OvlMtx m;
    OvlVec v;
    OvlVec r;
    Sub *s; /* built as (i*0x590+0x540) then +base, matching the original association */
    s = (Sub *)(arg0 * 0x590 + 0x540); s = (Sub *)((u8 *)s + (s32)D_00F86500);
    func_00f62ea0(v, s->val, s->id);
    func_00f62c98(r, s->val, 1, s->id);
    PlatVu0UnitMatrix(arg1);
    func_001becb8(arg1, r, 0);
    PlatVu0TransposeMatrix(arg1, arg1);
    PlatVu0UnitMatrix(m);
    if (D_00F86500[arg0].s.dir == 0) {
        PlatVu0RotMatrixZ(m, m, 3.141592503f);
    } else {
        PlatVu0RotMatrixX(m, m, 3.141592503f);
    }
    PlatVu0MulMatrix(arg1, m, arg1);
    PlatVu0CopyMatrix(arg2, arg1);
    v[3] = 1.0f;
    v[0] = -v[0];
    v[1] = -v[1];
    v[2] = -v[2];
    PlatVu0UnitMatrix(m);
    PlatVu0TransMatrix(m, m, v);
    PlatVu0MulMatrix(arg1, arg1, m);
}
