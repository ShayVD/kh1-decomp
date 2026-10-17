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

/* 0xC0-byte records found by index from a header offset. */
typedef struct { u64 a; s32 unk8; u8 pad[0xC0 - 12]; } Blk;
typedef struct { s32 unk0; s32 unk4; s32 off; } Hdr;
extern s32 D_00669A18[8];

void func_0024af40(s32 *idx, Blk *out, Hdr *h) {
    Blk *base = (Blk *)((u8 *)h + h->off);
    for (; *idx != -1; idx++, out++)
        *out = base[*idx];
}

void func_0024afc0(s32 *idx, Blk **out, Hdr *h) {
    Blk *base = (Blk *)((u8 *)h + h->off);
    while (*idx != -1)
        *out++ = &base[*idx++];
}

void func_0024b1f0(void) {
    s32 i;
    for (i = 0; i < 8; i++) D_00669A18[i] = 0;
}
