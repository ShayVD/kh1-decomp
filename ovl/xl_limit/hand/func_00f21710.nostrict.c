/* xl_limit.x func_00f21710: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[8]; s32 f8; } Sub2;
typedef struct { u8 pad[0x2C]; Sub2 *f2c; } Sub;
typedef struct { u8 pad[0x14C]; Sub *f14c; } Obj;
typedef struct { u8 pad[0xC]; void *fn; } Res;
s32 func_00130340(Obj *, s32, f32);
Res *func_00130578(Obj *, s32, f32);
s16 *func_0013dc10(Obj *, s32);
void func_00f216f8(void);
extern s32 D_00F23208;
extern s32 D_00F23E0C;

void func_00f21710(Obj *o, f32 f) {
    s16 *p = func_0013dc10(o, D_00F23E0C + 27);
    *(u64 *)o->f14c->f2c |= 0x800000;
    func_00130340(o, *p | 0x01000000, f);
    func_00130578(o, 0x40000000, 0.0f)->fn = func_00f216f8;
    if (++D_00F23E0C == 7) {
        o->f14c->f2c->f8 = D_00F23208;
    }
}
