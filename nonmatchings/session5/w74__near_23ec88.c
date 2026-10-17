#include "common.h"
typedef struct { s32 r, g, b, a; } __attribute__((aligned(16))) Col;
typedef struct { s32 a, b, c, d; u8 pad[0xC0 - 0x10]; } __attribute__((aligned(8))) Big;
typedef struct { u8 pad[0x40]; s32 unk40; u8 pad44[4]; s32 unk48; } St6C;
typedef struct { u8 pad[0x6C]; St6C *unk6C; } Ow;
typedef struct {
    s32 unk0;
    Ow *unk4;
    u8 pad8[0x5C - 8];
    Big *unk5C;
    u8 pad60[4];
    Big *unk64;
    u8 pad68[4];
    s32 unk6C;
    u8 pad70[0x10];
    u8 unk80[0x10];
    u8 *unk90;
    u8 pad94[0xA18 - 0x94];
    s32 unkA18;
    f32 unkA1C;
} Obj;
typedef struct { s32 unk0, unk4, unk8, unkC; } S16;
extern S16 D_00454A20;
extern Col D_004915D0;
s32 func_0023e160(void *, void *, Col *, s32, f32, f32, f32);
void func_0023d528(Obj *, s32 *, s32 *);
s32 func_0023d700(Big *, s32, s32, s32, s32, f32);

s32 func_0023ec88(Obj *e, s32 buf) {
    Col q = D_004915D0;
    s32 p1[4];
    s32 p2[4];
    s32 n, d, i, step;
    f32 k, v, w;
    if (e->unk0 == 4) {
        k = 0.52359867095947265625f;
        n = D_00454A20.unk8;
        d = 1;
    } else {
        k = 0.52359867095947265625f;
        d = 1;
        n = e->unk4->unk6C->unk48;
        if (n >= 21) n = 20;
    }
    if (e->unkA18 == 0) return buf;
    k *= n;
    v = k;
    w = k;
    if (v > 4.712388038635254f) v = 4.712388038635254f;
    buf = func_0023e160(e->unk80, e->unk90 + 0x10, &q, buf, 0.0f, v, e->unkA1C);
    if (w <= 4.712388038635254f) return buf;
    if (e->unk0 == 0 || e->unk0 == 4) step = 26;
    else step = 17;
    func_0023d528(e, p1, p2);
    p2[0] -= 1;
    n = (n - 9) / d;
    for (i = 0; i < n; i++) {
        buf = func_0023d700(e->unk5C, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
        p2[0] -= step;
    }
    if (e->unk0 == 0 || e->unk0 == 4) e->unk64->a = 440;
    else e->unk64->a = 397;
    return func_0023d700(e->unk64, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
}
