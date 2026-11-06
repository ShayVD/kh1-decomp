/* xs_genie.x func_00f20698: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x10]; OvlVec pos; OvlVec f20; } Obj;
s32 func_00f22cb0(void *, f32 *, s32, f32 *, f32);
void func_00f22db8(void *, s32, f32 *);
void func_00147ed8(s32, s32, s32, f32 *);
void func_00121fc4(f32 *, f32 *);
#ifdef KH1_PS2
void func_001376e8(Obj *, f32 *);
#else /* the definition returns f32: an x86 caller that drops it unbalances the x87 stack */
f32 func_001376e8(Obj *, f32 *);
#endif
extern Obj *D_00F22E90;
extern s32 D_00F22E98;
extern s32 D_00FC1710;
extern s32 D_00FC0E48;
void func_00f20698(Obj *o) {
    OvlVec v;
    OvlVec t;
    s32 n;
    f32 s;
    PlatVu0CopyVector(v, o->pos);
    v[1] = 0;
    n = func_00f22cb0(&D_00FC1710, v, 2, t, 50.0f);
    t[1] = D_00F22E90->pos[1] + -100.0f;
    if (n >= 20) {
        func_00f22db8(&D_00FC1710, 1, o->pos);
        o->pos[1] = D_00F22E90->pos[1] + -100.0f;
        func_00147ed8(D_00F22E98, 23, 20000, o->pos);
    } else {
        PlatVu0SubVector(t, t, o->pos);
        func_00121fc4(o->f20, t);
        s = 0.0f;
        if (n >= 2 || !(t[3] < 50.0f)) {
            s = 2.0f;
            if (n >= 4) {
                s = 8.0f;
            }
        }
        o->f20[3] = s;
    }
    if (D_00FC0E48 != 2) {
        PlatVu0SubVector(t, D_00F22E90->pos, o->pos);
        func_001376e8(o, t);
    }
}
