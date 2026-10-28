/* xl_limit.x func_00f202d8: matched by hand. */
#include "ovl.h"

void func_00120cf8(void *, void *, f32);
f32 func_00121840(void *, void *);
extern f32 D_002BBDFC;
typedef struct { u8 pad[0x20]; OvlVec v; } Obj;

void func_00f202d8(Obj *arg0, f32 *arg1, f32 t) {
    OvlVec axis;
    OvlMtx m;
    f32 ang;
    f32 lim;

    if (t > 0.0f) {
        sceVu0OuterProduct(axis, arg0->v, arg1);
        sceVu0Normalize(axis, axis);
        sceVu0InterVector(arg1, axis, arg1, t);
        sceVu0Normalize(arg1, arg1);
    }
    ang = func_00121840(arg0->v, arg1);
    lim = D_002BBDFC * 0.087266453f;
    if (lim < ang) {
        ang = lim;
    } else if (ang < -lim) {
        ang = -lim;
    }
    sceVu0OuterProduct(axis, arg0->v, arg1);
    sceVu0Normalize(axis, axis);
    func_00120cf8(axis, m, ang);
    arg0->v[3] = 0;
    sceVu0ApplyMatrix(arg0->v, m, arg0->v);
}
