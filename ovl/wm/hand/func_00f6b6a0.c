/* wm.x func_00f6b6a0: matched by hand. */
#include "ovl.h"

typedef struct {
    s8 b0;
    s8 b1;
    s8 b2;
    s8 b3;
    s8 b4;
    s8 b5;
    s8 pad6[2];
    s16 h8;
    s16 ha;
    s16 hc;
    s16 pade;
    s32 w10;
    f32 f14;
    f32 f18;
    f32 f1c;
    f32 f20;
    u8 pad24[8];
    f32 f2c;
    f32 f30;
    u8 pad34[4];
    s8 b38;
    s8 b39;
    s8 b3a;
    s8 b3b;
} Obj;
Obj *func_00f6a480(void);
void func_00f6b5b0(Obj *, f32, f32);

Obj *func_00f6b6a0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 x, s32 y, s32 z, s32 a8, s32 aa, s32 a38, s32 a39, s32 a3a, s32 a3b, s32 p, s32 q) {
    Obj *o = func_00f6a480();
    o->b0 = arg0;
    o->b1 = arg1;
    o->b2 = arg2;
    o->hc = arg3;
    o->b3 = arg4;
    o->b5 = arg5;
    o->w10 = arg6;
    o->b4 = arg7;
    o->f14 = o->f1c = x;
    o->f18 = o->f20 = y;
    o->f2c = o->f30 = z;
    o->h8 = a8;
    o->ha = aa;
    o->b38 = a38;
    o->b39 = a39;
    o->b3a = a3a;
    o->b3b = a3b;
    func_00f6b5b0(o, p, q);
    return o;
}
