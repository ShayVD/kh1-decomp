/* 0x00230000-0x0024FFFF game code by hand (batch 26), built without
 * strict aliasing. */
#include "common.h"

typedef struct { s32 r, g, b, a; } __attribute__((aligned(16))) Col;
typedef struct {
    u8 pad0[0x80];
    u8 unk80[0x10];
    u8 *unk90;
    u8 pad94[0xA1C - 0x94];
    f32 unkA1C;
    u8 padA20[0xA88 - 0xA20];
    f32 *unkA88;
    f32 *unkA8C;
} Obj;
extern Col D_00491610;
extern Col D_00491620;
void func_0023e160(void *, void *, Col *, s32, f32, f32, f32);

void func_0023feb8(Obj *e, s32 b) {
    Col q = D_00491610;
    f32 *p = e->unkA88;
    f32 v = *p * 0.0001745328918332234025001526f;
    if (v > 4.712388038635254f) v = 4.712388038635254f;
    func_0023e160(e->unk80, e->unk90 + 0x20, &q, b, 0.0f, v, e->unkA1C);
}

void func_00240170(Obj *e, s32 b) {
    Col q = D_00491620;
    f32 *p = e->unkA8C;
    f32 v = *p * 0.0001745328918332234025001526f;
    if (v > 4.712388038635254f) v = 4.712388038635254f;
    func_0023e160(e->unk80, e->unk90 + 0x30, &q, b, 0.0f, v, e->unkA1C);
}
