/* 0x00230000-0x0024FFFF game code by hand (batch 74). */
#include "common.h"
#include "data/bss_0064.h"
#include "data/bss_0065.h"

typedef struct { s32 x, y, z, w; } I4b;
typedef struct { u8 pad[0x60]; s32 c[4][4]; I4b p[4]; } Spr6;
s32 func_002388b8(Spr6 *, s32, s32);

typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0-0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q;
extern f32 D_002BBDFC;


typedef union { u64 x; struct { u64 lo:20; u64 b:6; u64 mid:30; u64 c:5; u64 d:3; } f; } Tag;
typedef struct { u64 tag; u64 n0; u64 tag2; u64 n1; I4b uv[4]; s32 c[4][4]; I4b p[4]; } LSpr;
typedef struct { u8 pad[0x18]; u64 tag; } TObj;

void func_0023d7e8(s32 a0, s32 (*pos)[4], s32 (*uv)[4], s32 (*col)[4], TObj *o, s32 buf) {
    LSpr s;
    Tag t;
    s32 i, j;
    t.x = o->tag;
    t.f.c = 0;
    t.f.d = 1;
    t.f.b = 0x13;
    s.tag = t.x;
    s.n0 = 6;
    s.tag2 = o->tag;
    s.n1 = 6;
    s.p[0].x = pos[0][0] * 16 + 0x7000;
    s.p[0].y = pos[0][1] * 16 + 0x7400;
    s.p[0].z = -256;
    s.p[0].w = 0;
    s.p[1].x = pos[1][0] * 16 + 0x7000;
    s.p[1].y = pos[1][1] * 16 + 0x7400;
    s.p[1].z = -256;
    s.p[1].w = 0;
    s.p[2].x = pos[2][0] * 16 + 0x7000;
    s.p[2].y = pos[2][1] * 16 + 0x7400;
    s.p[2].z = -256;
    s.p[2].w = 0;
    s.p[3].x = pos[3][0] * 16 + 0x7000;
    s.p[3].y = pos[3][1] * 16 + 0x7400;
    s.p[3].z = -256;
    s.p[3].w = 0;
    s.uv[0].x = uv[0][0] * 16 + 8;
    s.uv[0].y = uv[0][1] * 16 + 8;
    s.uv[1].x = uv[1][0] * 16 + 8;
    s.uv[1].y = uv[1][1] * 16 + 24;
    s.uv[2].x = uv[2][0] * 16 + 24;
    s.uv[2].y = uv[2][1] * 16 + 8;
    s.uv[3].x = uv[3][0] * 16 + 24;
    s.uv[3].y = uv[3][1] * 16 + 24;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            s.c[i][j] = col[i][j];
        }
    }
    func_002388b8(&s, 1, buf);
}

typedef struct { u8 pad[0x40]; s32 unk40; s32 unk44; s32 unk48; } St6C;
typedef struct { u8 pad[0x6C]; St6C *unk6C; } Ow;
#include "data/types/nostrict_nofill_text_00230000_h74.h"
typedef struct { s32 a, b, c, d; u8 pad[0xC0 - 0x10]; } __attribute__((aligned(8))) Big;
typedef struct {
    s32 unk0;
    Ow *unk4;
    s32 unk8[7];
    s32 unk24;
    s32 unk28[4];
    s32 unk38;
    void *unk3C;
    void *unk40;
    u8 pad44[0x4C - 0x44];
    void *unk4C;
    u8 pad50[0x5C - 0x50];
    Big *unk5C;
    u8 pad60[4];
    Big *unk64;
    u8 pad68[4];
    TObj *unk6C;
    void *unk70;
    u8 pad74[0xC];
    u8 unk80[0x10];
    u8 *unk90;
    u8 pad94[0x9E0 - 0x94];
    s32 unk9E0;
    f32 unk9E4;
    f32 unk9E8;
    u8 unk9EC[0xA18 - 0x9EC];
    s32 unkA18;
    f32 unkA1C;
    u8 padA20[0xA90 - 0xA20];
    f32 *unkA90;
    f32 *unkA94;
} Obj;
typedef struct { s32 unk0, unk4, unk8, unkC; } S16;
extern S16 D_00454A20;
extern Col D_004915A0;
void func_0023d528(Obj *, s32 *, s32 *);
s32 func_0023d700(void *, void *, s32, s32, s32, f32);
s32 func_0023e160(void *, void *, Col *, s32, f32, f32, f32);

s32 func_0023dfd8(Obj *g, s32 buf) {
    s32 p1[4];
    s32 p2[4];
    s32 x, y;
    s32 f1 = 0, f2 = 0;
    f32 a;
    if (g->unk0 == 4) {
        a = D_00454A20.unk0 * 0.52359867095947265625f;
        if (a > 1.57079616f) f1 = 1;
    } else if (g->unk0 == 3) {
        a = g->unk4->unk6C->unk40 * 0.000174532895471f;
        if (a > 1.57079616f) f1 = 1;
    } else {
        a = g->unk4->unk6C->unk48 * 0.52359867095947265625f;
        if (a > 1.57079616f) f1 = 1;
    }
    if (a > 3.1415922641754150391f) f2 = 1;
    if (!f1 && !f2) return buf;
    func_0023d528(g, p1, p2);
    x = p2[0];
    y = p2[1];
    if (f1) buf = func_0023d700(g->unk3C, g->unk6C, x, y, buf, g->unkA1C);
    if (f2) buf = func_0023d700(g->unk40, g->unk6C, x, y, buf, g->unkA1C);
    return buf;
}

s32 func_0023e330(Obj *e, s32 buf) {
    s32 p1[4];
    s32 p2[4];
    Big big;
    Col q = D_004915A0;
    f32 v;
    s32 i, n, t, rem;
    f32 fr;
    v = *e->unkA94 * 0.0001745328918332234025001526f;
    if (v > 4.712388038635254f) v = 4.712388038635254f;
    buf = func_0023e160(e->unk80, e->unk90 + 0x10, &q, buf, 0.0f, v, e->unkA1C);
    v = *e->unkA94 * 0.0001745328918332234025001526f;
    if (v <= 4.712388038635254f) return buf;
    func_0023d528(e, p1, p2);
    t = *e->unkA94 - 27000.0f;
    n = t / 3000;
    for (i = 0; i < n; i++) {
        buf = func_0023d700(e->unk5C, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
        p2[0] -= 26;
    }
    rem = t % 3000;
    if (rem != 0) {
        fr = rem / 3000.0f;
        p2[0] = p2[0] + (1.0f - fr) * 26.0f;
        big = *e->unk5C;
        big.c = big.c * (fr + 0.0625f);
        buf = func_0023d700(&big, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
    } else {
        p2[0] += 26;
    }
    e->unk64->a = 414;
    return func_0023d700(e->unk64, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
}

s32 func_0023f7d8(Obj *e, s32 buf) {
    s32 p1[4]; s32 p2[4]; s32 n, d, i, step; f32 k;
    if (e->unk0 == 4) { d = 1; k = 0.52359867095947265625f; n = D_00454A20.unk0; }
    else { k = 0.52359867095947265625f; d = 1; n = e->unk4->unk6C->unk44; if (n >= 21) n = 20; }
    if (k * n <= 4.712388038635254f) return buf;
    if (e->unk0 == 0 || e->unk0 == 4) step = 26; else step = 17;
    func_0023d528(e, p1, p2);
    p2[0] -= 1;
    n = (n - 9) / d;
    for (i = 0; i < n; i++) { buf = func_0023d700(e->unk4C, e->unk70, p2[0], p2[1], buf, e->unkA1C); p2[0] -= step; }
    return buf;
}

extern f32 D_002BBDFC;
void func_002492d0(void *, f32, f32, f32, f32);
s32 func_002492e8(void *, s32);
s32 func_0023f700(Obj *, s32);
s32 func_0023f920(Obj *e, s32 buf) {
    s32 n; f32 k, a, b, lim;
    if (e->unk0 == 4) { k = 0.52359867095947265625f; n = D_00454A20.unk0; }
    else { k = 0.52359867095947265625f; n = e->unk4->unk6C->unk44; }
    lim = 4.712388038635254f;
    a = k * n; if (lim < a) a = lim;
    b = k * e->unk9E0; if (lim < b) b = lim;
    if (n < e->unk9E0) {
        e->unk9E4 = a; e->unk9E8 = b;
        func_002492d0(e->unk9EC, 128.0f, -12.8f, 0.0f, 128.0f);
    } else if (e->unk9E0 < n) {
        e->unk9E4 = b; e->unk9E8 = a;
        func_002492d0(e->unk9EC, 0.0f, 12.8f, 0.0f, 128.0f);
    }
    if (func_002492e8(e->unk9EC, (s32)D_002BBDFC) == 1) e->unk9E4 = e->unk9E8;
    e->unk9E0 = n;
    if (n == 0) return buf;
    return func_0023f7d8(e, func_0023f700(e, buf));
}

/* needs make: uses rodata (jump table) */
extern s32 D_00454800, D_00454804, D_00454808, D_0045480C;
extern u8 D_00454820[], D_004548A0[], D_00454860[], D_004548E0[];
extern u8 D_00454920[], D_004549A0[], D_00454960[], D_004549E0[];
s32 func_0023da08(Obj *, void *, void *, s32, s32, s32);

s32 func_0023dd48(Obj *g, s32 buf) {
    s32 a, b;
    switch (g->unk0) {
    case 0:
        a = g->unk4->unk6C->unk48 * 30;
        b = g->unk4->unk6C->unk40 * 5;
        if (a >= 271) a = 0;
        if (b >= 271) b = 0;
        if (a != 0 && g->unkA18 != 0) buf = func_0023da08(g, D_00454820, D_004548A0, a, D_00454804, buf);
        if (b != 0) buf = func_0023da08(g, D_00454860, D_004548E0, b, D_00454800, buf);
        break;
    case 1:
    case 2:
        a = g->unk4->unk6C->unk48 * 30;
        b = g->unk4->unk6C->unk40 * 5;
        if (a >= 271) a = 0;
        if (b >= 271) b = 0;
        if (a != 0) buf = func_0023da08(g, D_00454920, D_004549A0, a, D_0045480C, buf);
        if (b != 0) buf = func_0023da08(g, D_00454960, D_004549E0, b, D_00454808, buf);
        break;
    case 3:
        a = 0;
        b = *g->unkA90 / 100.0f;
        if (b >= 271) b = 0;
        if (g->unkA94 != 0) {
            a = *g->unkA94 / 100.0f;
            if (a >= 271) a = 0;
        }
        if (b != 0) buf = func_0023da08(g, D_00454860, D_004548E0, b, D_00454800, buf);
        if (a != 0) buf = func_0023da08(g, D_00454820, D_004548A0, a, D_00454804, buf);
        break;
    case 4:
        a = D_00454A20.unk8 * 30;
        if (a >= 271) a = 0;
        b = D_00454A20.unkC * 3.75f;
        if (b >= 271) b = 0;
        if (b != 0) buf = func_0023da08(g, D_00454860, D_004548E0, b, D_00454800, buf);
        if (a != 0) buf = func_0023da08(g, D_00454820, D_004548A0, a, D_00454804, buf);
        break;
    }
    return buf;
}
#include "data/bss_0064_mixed.h"
#include "data/data_0045.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_004915A0.h"
