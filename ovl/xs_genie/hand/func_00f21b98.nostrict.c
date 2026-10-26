/* xs_genie.x func_00f21b98: matched by hand. */
#include "ovl.h"

typedef struct { s32 f0; f32 f4; } A;
typedef struct { s32 x, y, z; } B;
typedef struct { A *f0; s32 f4; B *f8; } Eff;
typedef struct { u8 pad[0x10]; OvlVec pos; Eff *f20; } Obj;
Eff *func_00147ed8(s32, s32, s32, f32 *);
extern s32 D_00F22E98;
extern f32 D_00FC0D98;
void func_00f21b98(Obj *o) {
    Eff *e = func_00147ed8(D_00F22E98, 18, 20000, o->pos);
    e->f0->f4 -= D_00FC0D98;
    e->f8->x = 0;
    e->f8->y = 0;
    e->f8->z = 0;
    o->f20 = e;
}
