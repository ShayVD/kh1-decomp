/* xs_mushu.x func_00f207e8: matched by hand. */
#include "ovl.h"

typedef struct { union { u64 flags; struct { s32 lo, hi; } w; } u; s32 f8; f32 fC; OvlVec pos; } Sub;
typedef struct { f32 *v; } Tgt;
typedef struct { s32 f0; f32 timer; s32 f8; s32 fC; OvlVec pos; OvlVec vel; Tgt *f30; s32 f34; s32 f38; Sub *f3C; } Obj;
void func_00f20778(Obj *);
s32 func_00122ff8(s32);
#ifdef KH1_PS2
void func_0012ec60(s32, s32, f32 *);
#else /* the definition returns f32: an x86 caller that drops it unbalances the x87 stack */
f32 func_0012ec60(s32, s32, f32 *);
#endif
void func_00121860(f32 *, f32 *, f32 *, f32);
extern f32 D_002BBDFC;
void func_00f207e8(Obj *o) {
    OvlVec s;
    OvlVec a;
    OvlVec d;
    OvlVec r;
    if (o->f3C->u.w.hi != 0) {
        func_00f20778(o);
        return;
    }
    o->f3C->u.flags = (o->f3C->u.flags & ~0xC) | 4;
    o->f3C->fC = 40.0f;
    PlatVu0CopyVector(o->f3C->pos, o->pos);
    o->timer -= D_002BBDFC;
    if (o->timer < 0.0f) {
        func_00f20778(o);
        return;
    }
    if (o->f34 != 0) {
        if (func_00122ff8(o->f34)) {
            func_0012ec60(o->f34, o->f38, a);
            PlatVu0SubVector(d, a, o->pos);
            func_00121860(o->vel, d, r, 0.0349065821618f);
            PlatVu0CopyVector(o->vel, r);
        } else {
            o->f34 = 0;
        }
    }
    PlatVu0ScaleVectorXYZ(s, o->vel, D_002BBDFC * 40.0f);
    PlatVu0AddVector(o->pos, o->pos, s);
    PlatVu0CopyVector(o->f30->v, o->pos);
}
