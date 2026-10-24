/* Two texture spots slid over triangle meshes, without strict aliasing
 * (docs/modules.md "Session 51"): func_001752a0 moves spots D_0035C440 /
 * D_0035C460 toward the hit of the view ray on meshes D_0035C424 / D_0035C42C
 * (at most 0.015 per frame) and builds their GS rectangles D_0035C430 /
 * D_0035C450; func_00175600 sends the packet D_0035C4A0 / D_0035C550 and
 * func_00175708 sets everything up from a file.  texspot.c has the two
 * intersection tests.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "platform/gs.h"
#include "platform/dma.h"
#include "data/pieces/D_0035BD40.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_0035C440.h"
#include "data/pieces/D_0035C460.h"
#include "data/pieces/D_002C58B0.h"
#include "data/types/nostrict_text_00170000_h38.h"
#include "data/pieces/D_0035C490.h"

/* func_001752a0 (from hand/nostrict/text_00160000_s6_09.c). */
typedef struct { u64 a, b; } Q16;
extern Q16 D_0035C430;
extern Q16 D_0035C450;
extern s32 D_0035C420;
extern u8 *D_0035C424;
extern s32 D_0035C428;
extern u8 *D_0035C42C;
extern u8 D_0035C470[];
extern u8 D_0035C480[];
typedef struct { u8 pad[0x154]; u8 *x154; } Ob52;
void func_001625c8(void *, void *);
void func_00162848(f32 *, void *, f32 *);
f32 func_00162c20(f32 *);
s32 func_00174fc0(void *, f32 *, u8 *, s32, f32 *, f32);
void func_001752a0(Ob52 *o, f32 *c) {
    f32 m[4][4];
    f32 m2[4][4];
    f32 v[4];
    f32 a[4];
    f32 b[4];
    f32 t[4];
    s32 x, y;
    if (D_0035C420 && D_0035C424 && D_0035C428 && D_0035C42C) {
        PlatVu0CopyMatrix(m, o->x154 + 0xB80);
        func_001625c8(m, m2);
        func_00162848(v, m2, c);
        PlatVu0CopyVector(a, (*(f32 (*)[0x4])&D_002C58B0));
        PlatVu0CopyVector(b, (*(f32 (*)[0x4])&D_002C58B0));
        if (v[1] < 300.0f) v[1] = 300.0f;
        if (func_00174fc0(D_0035C470, v, D_0035C424, D_0035C420, a, c[3])) {
            PlatVu0SubVector(t, a, D_0035C440);
            t[2] = t[3] = 0.0f;
            if (func_00162c20(t) > 0.015f) {
                PlatVu0ScaleVector(t, t, 0.015f);
                PlatVu0AddVector(D_0035C440, D_0035C440, t);
            } else {
                PlatVu0CopyVector(D_0035C440, a);
            }
        }
        x = D_0035C440[0] * 128.0f * 2.0f * 16.0f;
        y = D_0035C440[1] * 128.0f * 2.0f * 16.0f;
        D_0035C430.a = (u64)(x - 512) | ((u64)(y - 512) << 16) | ((u64)0xFFFFFFFE << 32);
        D_0035C430.b = (u64)(x + 512) | ((u64)(y + 512) << 16) | ((u64)0xFFFFFFFE << 32);
        if (func_00174fc0(D_0035C480, v, D_0035C42C, D_0035C428, b, c[3])) {
            PlatVu0SubVector(t, b, D_0035C460);
            t[2] = t[3] = 0.0f;
            if (func_00162c20(t) > 0.015f) {
                PlatVu0ScaleVector(t, t, 0.015f);
                PlatVu0AddVector(D_0035C460, D_0035C460, t);
            } else {
                PlatVu0CopyVector(D_0035C460, b);
            }
        }
        x = D_0035C460[0] * 128.0f * 2.0f * 16.0f;
        y = D_0035C460[1] * 128.0f * 2.0f * 16.0f;
        D_0035C450.a = (u64)(x - 512) | ((u64)(y - 512) << 16) | ((u64)0xFFFFFFFE << 32);
        D_0035C450.b = (u64)(x + 512) | ((u64)(y + 512) << 16) | ((u64)0xFFFFFFFE << 32);
    }
}

/* func_00175600 (from hand/nostrict/text_00170000_h38.c). */
typedef struct { u64 *x0; } P10;
typedef struct Spr {
    u8 pad0[0xa];
    u16 xa;
    u8 padc[4];
    P10 *x10;
} Spr;
typedef struct { s32 a, b; u8 *c; u8 *d; } Hd16;
extern Pkt D_0035C4A0;
extern Pkt D_0035C550;
Hd16 D_005757A0 ALIGNED(16);
void func_0015fa20(void *);
s32 func_00175600(Spr *s) {
    Pkt *p;
    if ((u16)(s->xa - 3) >= 2) return 0;
    PlatDmaSend(PlatDmaGetChan(2), &D_0035C4A0);
    p = (Pkt *)((u32)&D_0035C550 | 0x20000000);
    if (s->xa == 4) {
        p->x68 = D_0035C430.a;
        p->x78 = D_0035C430.b;
    } else {
        p->x68 = D_0035C450.a;
        p->x78 = D_0035C450.b;
    }
    p->xf0 = s->x10->x0[0];
    p->x100 = s->x10->x0[1];
    PlatGsSyncPath(0, 0);
    func_0015fa20(&D_005757A0);
    PlatGsSyncPath(0, 0);
    PlatDmaSend(PlatDmaGetChan(2), &D_0035C550);
    return 0;
}

/* func_00175708 (from hand/nostrict/text_00170000_h38.c). */
typedef struct { s32 a, b, c, d; } V16;
typedef struct Fil {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xc;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1c;
    s32 x20;
} Fil;
typedef struct { s32 x0; s32 x4; s32 x8; s32 xc; } Sub;
V16 D_00575790 ALIGNED(16);
void func_001623f8(void *, s32, V16 *);
void func_00175708(void *a0, Fil *f) {
    Sub *s;
    D_005757A0 = *(Hd16 *)((u8 *)f + f->x8);
    D_005757A0.c = (u8 *)f + f->x10;
    D_005757A0.d = (u8 *)f + f->x18;
    s = (Sub *)((u8 *)f + f->x20);
    D_0035C420 = s->x0;
    D_0035C424 = (u8 *)s + s->x4;
    D_0035C428 = s->x8;
    D_0035C42C = (u8 *)s + s->xc;
    func_001623f8(a0, 16, &D_00575790);
    PlatVu0CopyVector(D_0035C440, &D_0035C490);
    PlatVu0CopyVector(D_0035C460, &D_0035C490);
    D_0035C4A0.x0 = 10;
    D_0035C550.x0 = 16;
    D_0035C550.x4 = 0;
    D_0035C550.x3 = 112;
    D_0035C4A0.x3 = 112;
    D_0035C4A0.x4 = 0;
}

