/* xs_genie.x func_00f209e8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x10]; OvlVec pos; u8 pad2[0x1C]; f32 f3C; u8 pad3[0x58]; s32 f98; u8 pad4[0xB4]; f32 f150; u8 pad5[0x34C]; void (*f4A0)(); } Obj;
typedef struct { u8 pad[0x320]; OvlVec v; } Pl;
f32 func_001216d8(f32, f32, f32);
s32 func_00130340(Obj *, s32, f32);
void func_00135800(Obj *, f32, f32);
void func_00137308(Obj *, Pl *);
void func_00137318(Obj *);
void func_00137688(Obj *, f32);
void func_00147ed8(s32, s32, s32, f32 *);
void func_00157910(Obj *, s32, s32);
void func_00f20638(void);
void func_00f20670();
CONTEXT_ONLY void func_00f20698(Obj *o) {}
void func_00f20830(Obj *);
void func_00f22bb8(void *, f32 *, f32);
extern Pl *D_00F22E90;
extern s32 D_00F22E98;
extern s32 D_00FC0E48;
extern s32 D_00FC1710;
void func_00f209e8(Obj *o) {
    OvlVec v;
    if (o->f4A0 == 0) {
        func_00137308(o, D_00F22E90);
        o->f4A0 = func_00f20670;
    }
    PlatVu0CopyVector(v, D_00F22E90->v);
    v[1] = 0;
    func_00f22bb8(&D_00FC1710, v, 30.0f);
    switch (D_00FC0E48) {
    case 0:
    case 1:
        func_00f20698(o);
        break;
    case 2:
        func_00f20698(o);
        func_00f20830(o);
        break;
    case 100:
        if (o->f98 != 0) {
            func_00157910(o, 1, 3);
            func_00130340(o, 203, 0.0f);
            func_00147ed8(D_00F22E98, 23, 20000, o->pos);
            func_00f20638();
            func_00135800(o, 0.0f, 30.0f);
            func_00137318(o);
        }
        break;
    case 101:
        func_00137318(o);
        break;
    }
    func_00137688(o, func_001216d8(o->f3C, o->f150, 0.104719760269f));
}
