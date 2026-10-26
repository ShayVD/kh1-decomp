/* xs_dumbo.x func_00f202b8: matched by hand. */
#include "ovl.h"

typedef struct { s32 f0; } Eff;
typedef struct { u8 pad[0x14]; Eff *f14; } Obj;
typedef struct { u8 pad[0x30]; OvlVec v; } Pl;
void func_001315c0(s32, s32, s32, f32);
Eff *func_00147c98(s32, s32, s32);
void func_00147d50(Eff *, f32 *);
void func_00148068(Eff *, f32);
extern s32 D_00F23204;
extern s32 D_00F23208;
extern Pl *D_00F23200;
extern s32 D_00F3C9D8;
s32 func_00f202b8(Obj *o) {
    OvlVec v;
    if (D_00F3C9D8 == 101) {
        return 4;
    }
    if (o->f14 == 0) {
        o->f14 = func_00147c98(D_00F23208, 0, 20000);
    }
    if (D_00F3C9D8 == 3) {
        func_00148068(o->f14, 8.0f);
        return 4;
    }
    PlatVu0CopyVector(v, D_00F23200->v);
    v[3] = 1.0f;
    PlatVu0ScaleVectorXYZ(v, v, -1.0f);
    func_00147d50(o->f14, v);
    func_001315c0(D_00F23204, 4202, o->f14->f0, 0.0f);
    return 0;
}
