/* wm.x func_00f3cdd0: matched by hand. */
#include "ovl.h"

/* wm.x func_00f3cdd0: matched by hand. The CONTEXT_ONLY func_00f3caf0 makes the calls nothrow (plain bnez, li v0,1 in the slot); it is declared (f32 *, f32, f32 *, f32) and called (p, r, v, 0.0f) like func_00f3e5d0 does, which gives the a0/f12/a1/f13 setup order; m[3][0..2] cleared in order. */
#include "ovl.h"
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
CONTEXT_ONLY s32 func_00f3caf0(f32 *a0, f32 a1, f32 *a2, f32 a3) { return 0; }
#else /* a CONTEXT_ONLY copy is a weak definition off the EE: its order would be the calls' */
s32 func_00f3caf0(f32 *, f32 *, f32, f32);
static __inline__ s32 ee_00f3caf0(f32 *x0, f32 x1, f32 *x2, f32 x3) { return func_00f3caf0(x0, x2, x1, x3); }
#undef func_00f3caf0
#define func_00f3caf0 ee_00f3caf0
#endif
void sceVu0ApplyMatrix(f32 *, f32 (*)[4], f32 *);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
void sceVu0TransposeMatrix(f32 (*)[4], f32 (*)[4]);

s32 func_00f3cdd0(f32 *p, f32 *c, f32 *a, f32 *b, f32 (*mtx)[4], f32 r)
{
    f32 m[4][4];
    f32 v[4];
    f32 u[4];

    v[0] = c[0] + a[0];
    v[3] = 1.0f;
    v[1] = c[1] + a[1];
    v[2] = c[2] + a[2];
    if (func_00f3caf0(p, r, v, 0.0f)) return 1;
    v[0] = c[0] - b[0];
    v[1] = c[1] + a[1];
    v[2] = c[2] + a[2];
    if (func_00f3caf0(p, r, v, 0.0f)) return 1;
    v[0] = c[0] + a[0];
    v[1] = c[1] - b[1];
    v[2] = c[2] + a[2];
    if (func_00f3caf0(p, r, v, 0.0f)) return 1;
    v[0] = c[0] - b[0];
    v[1] = c[1] - b[1];
    v[2] = c[2] + a[2];
    if (func_00f3caf0(p, r, v, 0.0f)) return 1;
    v[0] = c[0] + a[0];
    v[1] = c[1] + a[1];
    v[2] = c[2] - b[2];
    if (func_00f3caf0(p, r, v, 0.0f)) return 1;
    v[0] = c[0] - b[0];
    v[1] = c[1] + a[1];
    v[2] = c[2] - b[2];
    if (func_00f3caf0(p, r, v, 0.0f)) return 1;
    v[0] = c[0] + a[0];
    v[1] = c[1] - b[1];
    v[2] = c[2] - b[2];
    if (func_00f3caf0(p, r, v, 0.0f)) return 1;
    v[0] = c[0] - b[0];
    v[1] = c[1] - b[1];
    v[2] = c[2] - b[2];
    if (func_00f3caf0(p, r, v, 0.0f)) return 1;
    sceVu0CopyMatrix(m, mtx);
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    sceVu0TransposeMatrix(m, m);
    v[0] = p[0] - c[0];
    v[1] = p[1] - c[1];
    v[2] = p[2] - c[2];
    v[3] = 1.0f;
    sceVu0ApplyMatrix(v, m, v);
    if (-b[0] < v[0] && v[0] < a[0] && -b[1] < v[1] && v[1] < a[1] && -b[2] < v[2] && v[2] < a[2]) return 1;
    if (-(b[0] + r) < v[0] && v[0] < a[0] + r && -b[1] < v[1] && v[1] < a[1] && -b[2] < v[2] && v[2] < a[2]) return 1;
    if (-b[0] < v[0] && v[0] < a[0] && -(b[1] + r) < v[1] && v[1] < a[1] + r && -b[2] < v[2] && v[2] < a[2]) return 1;
    if (-b[0] < v[0] && v[0] < a[0] && -b[1] < v[1] && v[1] < a[1] && -(b[2] + r) < v[2] && v[2] < a[2] + r) return 1;
    return 0;
}
