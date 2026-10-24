/* The gauges (include/hud/gauge.h, docs/modules.md "Session 47"): the parts
 * built with no delay-slot fill.  func_0023cfe8 sets up the world map's
 * parts from the sprite file (kind 1, 2 or 3: tt_gaugeWorldmap's mode),
 * func_0023d490 picks the player's frame size (0, 1, 2) from the maxima
 * (the world map's from its own numbers), func_0023d700 draws one sprite
 * moved by (x, y) with its alpha scaled, through D_00651D70. */
#include "common.h"
#include "hud/gauge.h"
#include "data/types/nofill_text_00230000_h49.h" /* Pkt */
#include "data/data_0045.h"
#include "data/pieces/D_00454A20.h"

void func_0024aa48(UiSpr *, Pkt *, Tex_4268b0 *);
QW *func_002388b8(Pkt *, s32, QW *);
void func_0024afc0(void *, void *, s32);

void func_0023cfe8(u8 *o, s32 k, s32 a) {
    switch (k) {
    case 0:
        break;
    case 1:
        func_0024afc0(D_00454558, o, a);
        func_0024afc0(D_004545F8, o + 0x14, a);
        break;
    case 2:
        func_0024afc0(D_004545B0, o + 0x18, a);
        func_0024afc0(D_004545E0, o + 0x28, a);
        func_0024afc0(D_004545C8, o + 0x3C, a);
        break;
    case 3:
        func_0024afc0(D_00454558, o, a);
        func_0024afc0(D_004545F8, o + 0x14, a);
        func_0024afc0(D_00454570, o + 0x18, a);
        func_0024afc0(D_00454580, o + 0x28, a);
        func_0024afc0(D_00454598, o + 0x3C, a);
        break;
    }
}

s32 func_0023d490(Gauge *a) {
    s32 r;
    if (a->unk0 == 4) {
        s32 x = D_00454A20.unk8;
        s32 y = D_00454A20.unkC;
        r = 0;
        if (y >= 25) r = 1;
        if (x >= 4) r = 1;
        if (y >= 49) r = 2;
        if (x >= 7) r = 2;
        return r;
    }
    if (a->unk0 == 3) return 2;
    {
        GStat *s = a->unk4->unk6C;
        s32 h = s->unk40;
        s32 w;
        if (h >= 37) return 2;
        w = s->unk48;
        if (w >= 7) return 2;
        if (h >= 19) return 1;
        if (w >= 4) return 1;
        return 0;
    }
}

Pkt D_00651D70 ALIGNED(16);

QW *func_0023d700(UiSpr *a0, Tex_4268b0 *a1, s32 x, s32 y, QW *q, f32 s) {
    s32 i;
    s32 *p;
    s32 dx, dy;
    func_0024aa48(a0, &D_00651D70, a1);
    dx = x * 16;
    dy = y * 16;
    p = &D_00651D70.p[0].y;
    for (i = 0; i < 4; i++) {
        p[-1] += dx;
        *p += dy;
        p += 4;
    }
    for (i = 0; i < 4; i++) {
        D_00651D70.c[i].w = D_00651D70.c[i].w * s;
    }
    return func_002388b8(&D_00651D70, 1, q);
}
