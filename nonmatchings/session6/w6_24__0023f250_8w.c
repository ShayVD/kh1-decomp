/* func_0023f250 8w off (nostrict, CONTEXT_ONLY d528 above, jtbl rodata 00491560 for the ctx d528 -> run with wqb03_rr 00491560): in both setup branches orig schedules the cur load/clamp (a3) before max (s6); ours the reverse. Statement/decl order and min-helpers tried. */
#include "common.h"
typedef struct { u64 lo, hi; } QW;
typedef struct { s32 v[48]; } __attribute__((aligned(8))) Spr;
typedef struct { u8 pad[0x18]; u64 unk18; } Tex;
typedef struct { u8 pad[0x3C]; s32 unk3C; s32 unk40; } St6C;
typedef struct { u8 pad[0x6C]; St6C *unk6C; } Ow;
typedef struct { f32 v[4]; } __attribute__((aligned(16))) V4;
typedef struct {
    s32 unk0;
    Ow *unk4;
    u8 pad8[0x48 - 8];
    Spr *unk48;
    u8 pad4c[0x70 - 0x4C];
    Tex *unk70;
    u8 pad74[0x460 - 0x74];
    u8 unk460[0xA1C - 0x460];
    f32 unkA1C;
    u8 padA20[4];
    s32 unkA24;
} Obj;
typedef struct { s32 x0, x4, x8, xc; } S4A20;
extern S4A20 D_00454A20;
typedef struct { s32 x, y, z, w; } T16;
typedef struct { s32 unk0; u8 pad4[0x90]; s32 unk94; u8 pad98[4]; void *unk9C; } Ob9C;
extern T16 D_00454600[];
extern T16 D_00454650[];
extern T16 D_00454680[];
extern T16 D_004546C0[];
extern T16 D_00454700[];
void func_0024ac08(void *, s32 *);
CONTEXT_ONLY void func_0023d528(Obj *ov, s32 *p1, s32 *p2) {
    Ob9C *o = (Ob9C *)ov;
    s32 r[2];
    register T16 *t asm("$5");
    switch (o->unk0) {
    case 0:
        t = D_00454650;
        p1[0] = D_00454600[0].x;
        p1[1] = D_00454600[0].y;
        goto idx;
    case 1:
        p1[0] = D_00454600[1].x;
        p1[1] = D_00454600[1].y;
        p2[0] = D_00454680[0].x;
        p2[1] = D_00454680[0].y;
        break;
    case 2:
        p1[0] = D_00454600[2].x;
        p1[1] = D_00454600[2].y;
        p2[0] = D_004546C0[0].x;
        p2[1] = D_004546C0[0].y;
        break;
    case 3:
        t = D_00454700;
        p1[0] = D_00454600[3].x;
        p1[1] = D_00454600[3].y;
        goto idx;
    case 4:
        t = D_00454650;
        p1[0] = D_00454600[4].x;
        p1[1] = D_00454600[4].y;
    idx:
        p2[0] = t[o->unk94].x;
        p2[1] = t[o->unk94].y;
        break;
    }
    if (o->unk9C != 0) {
        func_0024ac08(o->unk9C, r);
        p2[0] += r[0];
        p2[1] += r[1];
    }
}
QW *func_0023d700(Spr *, Tex *, s32, s32, QW *, f32);
void func_0024a0e0(void *, V4 *);
void func_0024b008(Spr *, V4 *);

QW *func_0023f250(Obj *o, QW *r) {
    s32 a[4];
    s32 b[2];
    Spr c;
    V4 m;
    Spr d;
    s32 base;
    s32 cur, max, step, w, len, i, n, k;
    f32 f, t;
    if (o->unk0 == 4) {
        f = 0.06544983386993408203125f;
        cur = D_00454A20.xc;
        max = D_00454A20.x4;
        step = 8;
        base = 72;
    } else {
        St6C *p = o->unk4->unk6C;
        f = 0.087266445159912109375f;
        step = 6;
        base = 54;
        cur = p->unk40;
        max = p->unk3C;
        if (max > 120) max = 120;
        if (cur > 120) cur = 120;
    }
    if (f * cur <= 4.71238803863525390625f) return r;
    if (o->unk0 == 0 || o->unk0 == 4) w = 26;
    else w = 17;
    if (o->unkA24 == 2) {
        len = cur - base;
        func_0023d528(o, a, b);
        func_0024a0e0(o->unk460, &m);
        n = len / step;
        d = *o->unk48;
        func_0024b008(&d, &m);
        for (i = 0; i < n; i++) {
            r = func_0023d700(&d, o->unk70, b[0], b[1], r, o->unkA1C);
            b[0] -= w;
        }
        k = len % step;
        if (k != 0) {
            t = (f32)k / (f32)step;
            b[0] = b[0] + w * (1.0f - t);
            c = d;
            c.v[2] = c.v[2] * (t + 0.0625f);
            r = func_0023d700(&c, o->unk70, b[0], b[1], r, o->unkA1C);
        }
    }
    if (base >= max) return r;
    {
        len = max - base;
        func_0023d528(o, a, b);
        b[0]--;
        n = len / step;
        for (i = 0; i < n; i++) {
            r = func_0023d700(o->unk48, o->unk70, b[0], b[1], r, o->unkA1C);
            b[0] -= w;
        }
        k = len % step;
        if (k == 0) return r;
        t = (f32)k / (f32)step;
        b[0] = b[0] + w * (1.0f - t);
        c = *o->unk48;
        c.v[2] = c.v[2] * (t + 0.0625f);
        return func_0023d700(&c, o->unk70, b[0], b[1], r, o->unkA1C);
    }
}
