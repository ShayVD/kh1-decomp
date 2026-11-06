/* xs_genie.x func_00f20fe8: matched by hand. */
#include "ovl.h"

typedef struct { union { u64 flags; struct { u32 lo; s32 hi; } w; } u; s32 f8; f32 fc; OvlVec pos; } Eff;
typedef struct { f32 *pos; } Tgt;
typedef struct { s32 f0; s32 type; f32 f8; u8 padc[4]; OvlVec v10; OvlVec v20; Tgt *tgt; void *act; s32 id; Eff *eff; } Gs;
void func_00f20fc0(Gs *);
s32 func_00122ff8(void *);
#ifdef KH1_PS2
void func_0012ec60(void *, s32, f32 *);
#else /* the definition returns f32: an x86 caller that drops it unbalances the x87 stack */
f32 func_0012ec60(void *, s32, f32 *);
#endif
void func_00121860(f32 *, f32 *, f32 *, f32);
extern f32 D_002BBDFC;
void func_00f20fe8(Gs *o) {
    OvlVec d;
    OvlVec t;
    OvlVec e;
    OvlVec r;

    if (o->eff->u.w.hi != 0) {
        func_00f20fc0(o);
        return;
    }
    o->eff->u.flags = (o->eff->u.flags & ~0xC) | 4;
    o->eff->fc = 45.0f;
    PlatVu0CopyVector(o->eff->pos, o->v10);
    o->f8 -= D_002BBDFC;
    if (o->f8 < 0.0f) {
        func_00f20fc0(o);
        return;
    }
    if (o->act != NULL) {
        if (func_00122ff8(o->act)) {
            func_0012ec60(o->act, o->id, t);
            PlatVu0SubVector(e, t, o->v10);
            func_00121860(o->v20, e, r, 0.0698131695f);
            PlatVu0CopyVector(o->v20, r);
        } else {
            o->act = NULL;
        }
    }
    switch (o->type) {
    case 3:
        PlatVu0ScaleVectorXYZ(d, o->v20, 75.999993f);
        break;
    case 4:
        PlatVu0ScaleVectorXYZ(d, o->v20, 71.999993f);
        break;
    case 5:
        PlatVu0ScaleVectorXYZ(d, o->v20, 67.999993f);
        break;
    case 6:
        PlatVu0ScaleVectorXYZ(d, o->v20, 63.9999962f);
        break;
    default:
        PlatVu0ScaleVectorXYZ(d, o->v20, 80.0f);
        break;
    }
    PlatVu0AddVector(o->v10, o->v10, d);
    if (o->tgt != NULL)
        PlatVu0CopyVector(o->tgt->pos, o->v10);
}
