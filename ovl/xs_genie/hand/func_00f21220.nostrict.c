/* xs_genie.x func_00f21220: matched by hand. */
#include "ovl.h"

typedef struct { u64 flags; s32 f8; f32 fc; OvlVec pos; } Eff;
typedef struct { f32 *pos; } Tgt;
typedef struct { s32 f0; s32 type; f32 f8; u8 padc[4]; OvlVec v10; OvlVec v20; Tgt *tgt; s32 f34; s32 f38; Eff *eff; } Gs;
Gs *func_00f20f80(void);
s32 func_001477e0(s32);
Eff *func_0014a4a8(void *, s32, s32);
Tgt *func_00147c98(void *, s32, s32);
extern void *D_00F22E90;
extern void *D_00F22E98;
void func_00f21220(s32 type, f32 *a, f32 *b, s32 *pair) {
    Gs *o = func_00f20f80();

    if (o == NULL)
        return;
    o->type = type;
    o->f8 = 90.0f;
    PlatVu0CopyVector(o->v10, b);
    PlatVu0CopyVector(o->v20, a);
    if (pair != NULL) {
        o->f34 = pair[0];
        o->f38 = pair[1];
    } else {
        o->f34 = 0;
        o->f38 = 0;
    }
    switch (type) {
    case 0:
        o->eff = func_0014a4a8(D_00F22E90, 0, func_001477e0(7));
        o->tgt = func_00147c98(D_00F22E98, 1, 20000);
        PlatVu0CopyVector(o->tgt->pos, o->v10);
        break;
    case 1:
        o->eff = func_0014a4a8(D_00F22E90, 0, func_001477e0(6));
        o->tgt = func_00147c98(D_00F22E98, 10, 20000);
        PlatVu0CopyVector(o->tgt->pos, o->v10);
        break;
    case 2:
        o->eff = func_0014a4a8(D_00F22E90, 0, func_001477e0(9));
        o->tgt = func_00147c98(D_00F22E98, 5, 20000);
        PlatVu0CopyVector(o->tgt->pos, o->v10);
        break;
    case 3:
    case 4:
    case 5:
    case 6:
        o->eff = func_0014a4a8(D_00F22E90, 0, func_001477e0(8));
        break;
    }
    o->eff->flags = (o->eff->flags & ~0xC) | 4;
    o->eff->flags |= 0x800000;
    o->eff->flags |= 0x80;
    o->eff->fc = 45.0f;
    o->eff->f8 = (s32)D_00F22E98;
    PlatVu0CopyVector(o->eff->pos, o->v10);
}
