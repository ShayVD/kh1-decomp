/* func_0023f0d8. Its callee func_0023e160 takes its three floats before the
 * Col pointer: the other prototype order schedules the argument moves
 * differently. */
#include "common.h"
#include "data/types/nostrict_text_00230000_c2.h"
typedef struct { u8 pad[0x3C]; s32 unk3C; s32 unk40; } St6C;
typedef struct { u8 pad[0x6C]; St6C *unk6C; } Ow;
typedef struct {
    s32 unk0;
    Ow *unk4;
    u8 pad8[0x80 - 8];
    u8 unk80[0x10];
    u8 *unk90;
    u8 pad94[0x460 - 0x94];
    u8 unk460[0xA1C - 0x460];
    f32 unkA1C;
    u8 padA20[4];
    s32 unkA24;
} Obj;
typedef struct { s32 unk0, unk4, unk8, unkC; } S16;
extern S16 D_00454A20;
extern Col D_004915E0;
s32 func_0023e160(void *, void *, f32, f32, f32, Col *, s32);
void func_0024a0e0(void *, Col *);

s32 func_0023f0d8(Obj *e, s32 buf) {
    Col q = D_004915E0;
    Col c;
    s32 a, b;
    f32 k, v;
    if (e->unk0 == 4) {
        k = 0.06544983386993408203125f;
        b = D_00454A20.unk4;
        a = D_00454A20.unkC;
    } else {
        k = 0.087266445159912109375f;
        b = e->unk4->unk6C->unk3C;
        a = e->unk4->unk6C->unk40;
        if (a >= 121) a = 120;
        if (b >= 121) b = 120;
    }
    if (e->unkA24 == 2) {
        func_0024a0e0(e->unk460, &c);
        v = k * a;
        if (v > 4.712388038635254f) v = 4.712388038635254f;
        buf = func_0023e160(e->unk80, e->unk90 + 0x20, 0.0f, v, e->unkA1C, &c, buf);
    }
    v = k * b;
    if (v > 4.712388038635254f) v = 4.712388038635254f;
    return func_0023e160(e->unk80, e->unk90 + 0x20, 0.0f, v, e->unkA1C, &q, buf);
}
#include "data/pieces/D_004915E0.h"
