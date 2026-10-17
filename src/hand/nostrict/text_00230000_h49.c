/* 0x00230000-0x0024FFFF game code by hand (batch 49), built without strict aliasing. */
#include "common.h"
typedef struct { s32 r, g, b, a; } __attribute__((aligned(16))) Col;
extern Col D_004915F0;
typedef struct {
    u8 pad0[0x80];
    u8 unk80[0x10];
    u8 *unk90;
    u8 pad94[0x9E4 - 0x94];
    f32 unk9E4;
    f32 unk9E8;
    f32 unk9EC;
    f32 unk9F0;
    u8 pad9F4[0xA1C - 0x9F4];
    f32 unkA1C;
} Obj;
s32 func_0023e160(void *, void *, Col *, s32, f32, f32, f32);

s32 func_0023f700(Obj *o, s32 a1) {
    Col c = D_004915F0;
    s32 v;
    a1 = func_0023e160(o->unk80, o->unk90 + 0x30, &c, a1, 0.0f, o->unk9E4, o->unkA1C);
    if (o->unk9F0 != 0.0f) {
        v = o->unk9EC;
        c.a = 128;
        c.b = v;
        c.g = v;
        c.r = v;
        a1 = func_0023e160(o->unk80, o->unk90 + 0x30, &c, a1, o->unk9E4, o->unk9E8, o->unkA1C);
    }
    return a1;
}
