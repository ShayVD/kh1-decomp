/* xs_genie.x func_00f21c08: matched by hand. */
#include "ovl.h"

typedef struct { s32 f0; f32 f4; } A;
typedef struct { A *f0; s32 f4; f32 *f8; } Eff;
typedef struct { u8 pad[0x10]; OvlVec pos; Eff *f20; } Obj;
void func_00249950(f32 *, f32, f32);
extern f32 D_002BBDFC;
extern f32 D_00FC0D98;
s32 func_00f21c08(Obj *o) {
    f32 d;
    o->f20->f0->f4 += D_00FC0D98 / 15.0f * D_002BBDFC;
    if (o->pos[1] < o->f20->f0->f4) {
        o->f20->f0->f4 = o->pos[1];
    }
    d = D_002BBDFC * 0.0666666627f;
    o->f20->f8[0] += d;
    o->f20->f8[1] += d;
    o->f20->f8[2] += d;
    func_00249950(&o->f20->f8[0], 0.0f, 1.0f);
    func_00249950(&o->f20->f8[1], 0.0f, 1.0f);
    func_00249950(&o->f20->f8[2], 0.0f, 1.0f);
    if (o->f20->f8[0] == 1.0f) {
        return 1;
    }
    return 0;
}
