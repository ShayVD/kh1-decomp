/* xs_dumbo.x func_00f20e38: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x20]; OvlVec f20; u8 pad2[0x390]; OvlVec f3C0; } Obj;
void func_00121fc4(f32 *, f32 *);
f32 powf(f32, f32);
extern f32 D_002BBDFC;
void func_00f20e38(Obj *o, f32 *v) {
    if (o->f20[3] > 0.0f) {
        PlatVu0ScaleVector(v, o->f20, o->f20[3] * D_002BBDFC);
        PlatVu0AddVector(v, o->f3C0, v);
        v[1] = 0.0f;
        func_00121fc4(v, v);
        if (v[3] > 6.0f) {
            v[3] = 6.0f;
        }
    } else {
        PlatVu0CopyVector(v, o->f3C0);
        v[1] = 0.0f;
        func_00121fc4(v, v);
        v[3] -= D_002BBDFC * 0.5f;
        if (v[3] < 0.0f) {
            v[3] = 0.0f;
        }
    }
    PlatVu0ScaleVector(v, v, v[3]);
    if (o->f20[1] == 0.0f) {
        v[1] = o->f3C0[1] * powf(0.79999997f, D_002BBDFC);
    } else {
        v[1] = o->f3C0[1] + o->f20[1] * D_002BBDFC;
        if (v[1] < -4.0f) {
            v[1] = -4.0f;
        } else if (v[1] > 4.0f) {
            v[1] = 4.0f;
        }
    }
    PlatVu0CopyVector(o->f3C0, v);
    PlatVu0ScaleVector(v, v, D_002BBDFC);
}
