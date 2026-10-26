/* xs_dumbo.x func_00f20d88: matched by hand. */
#include "ovl.h"

typedef struct { s32 f0; s32 f4; } G;
typedef struct { u8 pad[0x10]; OvlVec pos; OvlVec f20; } Obj;
s32 func_00122ff8(s32);
void func_0012ec60(s32, s32, f32 *);
void func_001376e8(Obj *, f32 *);
extern G D_002E31B0;
void func_00f20d88(Obj *o, f32 *v) {
    OvlVec t;
    if (func_00122ff8(D_002E31B0.f0)) {
        func_0012ec60(D_002E31B0.f0, D_002E31B0.f4, t);
        PlatVu0SubVector(t, t, o->pos);
        func_001376e8(o, t);
    } else if (v[3] > 0.0f) {
        func_001376e8(o, v);
    }
    PlatVu0CopyVector(o->f20, v);
}
