/* The functions of src/text/textwin.c that need nostrict
 * (docs/modules.md "Session 37"): func_001f4570 (the anchor x, by
 * alignment +0xac) and the window frames, each built as a GIF packet and
 * sent through path 2: func_001f4778 (kind 1) and func_001f4d10 (kind 2)
 * draw the gradient body, func_001f54f8 / func_001f5988 the title bar
 * (+0x88 bit 1), func_001f52e8 a flat box (kind 3).  The colours are the
 * window's +0x68 or entry D_003F1A68 of D_003E8E30 (12 words each); with
 * bit 0 of +0x48 every vertex is scaled by +0x74 / +0x78 around the anchor
 * (func_001f4570, func_001f45e0).  func_001f4778 and func_001f4d10 need
 * func_001f4570 defined above them. */
#include "common.h"
#include "platform/gs.h"
#include "platform/dma.h"
#include "text/textwin.h"
#include "data/pieces/D_003F1A70.h"
#include "data/pieces/D_003E8E30.h"
#include "data/pieces/D_003F27D0.h"

typedef Q_3f1a70 Q;
/* one flat sprite: tag, a+d, prim, rgba, two corners */
typedef struct { u64 tag, ad; u64 d2, d3; u64 d4, d5; s32 x0, y0, z0, w0; s32 x1, y1, z1, w1; } Pk;
/* one Gouraud vertex: rgba, q, xyz */
typedef struct { u64 rgba, q; s32 x, y, z, f; } V3;
typedef struct { u64 h[6]; V3 v[10]; } Pk3;
typedef struct { u64 h[6]; V3 v[12]; } Pk4;

extern s32 D_003F1A68;

Q *func_00122048(s32, s32);
u32 func_001edd88(s32, s32);
s32 func_001f45e0(TextWin *);
void func_001220b8(void *);

/* rodata: jump table */
s32 func_001f4570(TextWin *o) {
    switch (o->xac) {
    case 0:
    case 1:
    case 2:
    default:
        return o->xb0 + o->xb8 / 2;
    case 3:
    case 5:
    case 7:
        return o->xb0;
    case 4:
    case 6:
    case 8:
        return o->xb0 + o->xb8 - 16;
    }
}

/* func_001f4778: per-vertex transform; shared coordinates copied from the
 * vertex already transformed (cse turns the reloads into register copies) */
void func_001f4778(TextWin *o) {
    u64 *buf;
    Pk4 *s;
    void *u;
    u32 *t;
    u32 a;
    s32 bx, by, w, h, cx, cy;
    f32 fx, fy, sx, sy;
    s32 X, X128, Xw, X32, X160, Xw32, Y, Y128, Yh, Y32, Y160, Yh32;
    PlatDmaSend(PlatDmaGetChan(2), &D_003F1A70);
    if (o->x88 & 0x10) {
        PlatDmaSend(PlatDmaGetChan(2), D_003F27D0);
    }
    buf = (u64 *)func_00122048(1024, 128);
    s = (Pk4 *)(buf + 2);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    s->h[0] = 0x1026400000008001;
    s->h[1] = 14;
    s->h[2] = 68;
    s->h[3] = 66;
    s->h[4] = 0x200000000000800c;
    s->h[5] = 78;
    a = o->x90 << 24;
    t = o->x68;
    bx = o->xb0;
    by = o->xb4;
    w = o->xb8;
    h = o->xba;
    if (t == 0) t = ((u32 (*)[12])&D_003E8E30)[D_003F1A68];
    s->v[0].rgba = t[0] | a; s->v[0].q = 1; s->v[0].x = bx; s->v[0].y = by + 128; s->v[0].z = 0x100000; s->v[0].f = 0;
    s->v[1].rgba = t[2] | a; s->v[1].q = 1; s->v[1].x = bx; s->v[1].y = by + h; s->v[1].z = 0x100000; s->v[1].f = 0;
    s->v[2].rgba = t[0] | a; s->v[2].q = 1; s->v[2].x = bx + 128; s->v[2].y = by; s->v[2].z = 0x100000; s->v[2].f = 0;
    s->v[3].rgba = t[2] | a; s->v[3].q = 1; s->v[3].x = bx + 128; s->v[3].y = by + h; s->v[3].z = 0x100000; s->v[3].f = 0;
    s->v[4].rgba = t[1] | a; s->v[4].q = 1; s->v[4].x = bx + w; s->v[4].y = by; s->v[4].z = 0x100000; s->v[4].f = 0;
    s->v[5].rgba = t[3] | a; s->v[5].q = 1; s->v[5].x = bx + w; s->v[5].y = by + h; s->v[5].z = 0x100000; s->v[5].f = 0;
    s->v[6].rgba = t[4] | a; s->v[6].q = 1; s->v[6].x = bx + 32; s->v[6].y = by + 160; s->v[6].z = 0x100000; s->v[6].f = 0x8000;
    s->v[7].rgba = t[6] | a; s->v[7].q = 1; s->v[7].x = bx + 32; s->v[7].y = by + h - 32; s->v[7].z = 0x100000; s->v[7].f = 0x8000;
    s->v[8].rgba = t[4] | a; s->v[8].q = 1; s->v[8].x = bx + 160; s->v[8].y = by + 32; s->v[8].z = 0x100000; s->v[8].f = 0;
    s->v[9].rgba = t[6] | a; s->v[9].q = 1; s->v[9].x = bx + 160; s->v[9].y = by + h - 32; s->v[9].z = 0x100000; s->v[9].f = 0;
    s->v[10].rgba = t[5] | a; s->v[10].q = 1; s->v[10].x = bx + w - 32; s->v[10].y = by + 32; s->v[10].z = 0x100000; s->v[10].f = 0;
    s->v[11].rgba = t[7] | a; s->v[11].q = 1; s->v[11].x = bx + w - 32; s->v[11].y = by + h - 32; s->v[11].z = 0x100000; s->v[11].f = 0;
    if (o->u48.w.lo & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
        fx = cx;
        fy = cy;
#define TX(k) s->v[k].x = fx + (f32)(s->v[k].x - cx) * sx
#define TY(k) s->v[k].y = fy + (f32)(s->v[k].y - cy) * sy
        TX(0); TY(0);
        s->v[1].x = s->v[0].x; TY(1);
        TX(2); TY(2);
        s->v[3].x = s->v[2].x; s->v[3].y = s->v[1].y;
        TX(4); s->v[4].y = s->v[2].y;
        s->v[5].x = s->v[4].x; s->v[5].y = s->v[1].y;
        TX(6); TY(6);
        s->v[7].x = s->v[6].x; TY(7);
        TX(8); TY(8);
        s->v[9].x = s->v[8].x; s->v[9].y = s->v[7].y;
        TX(10); s->v[10].y = s->v[8].y;
        s->v[11].x = s->v[10].x; s->v[11].y = s->v[7].y;
    }
    buf[0] = (((s32)(s + 1) - (s32)buf) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), u);
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
}

void func_001f4d10(TextWin *o) {
    u64 *buf;
    Pk4 *s;
    void *u;
    u32 *t;
    u32 a;
    s32 bx, by, w, h, cx, cy;
    f32 fx, fy, sx, sy;
    s32 X, Xw128, Xw, X32, Xw160, Xw32, Y, Y128, Yh, Y32, Y160, Yh32;
    PlatDmaSend(PlatDmaGetChan(2), &D_003F1A70);
    if (o->x88 & 0x10) {
        PlatDmaSend(PlatDmaGetChan(2), D_003F27D0);
    }
    buf = (u64 *)func_00122048(1024, 128);
    s = (Pk4 *)(buf + 2);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    s->h[0] = 0x1026400000008001;
    s->h[1] = 14;
    s->h[2] = 68;
    s->h[3] = 66;
    s->h[4] = 0x200000000000800c;
    s->h[5] = 78;
    a = o->x90 << 24;
    t = o->x68;
    bx = o->xb0;
    by = o->xb4;
    w = o->xb8;
    h = o->xba;
    if (t == 0) t = ((u32 (*)[12])&D_003E8E30)[D_003F1A68];
    s->v[0].rgba = t[0] | a; s->v[0].q = 1; s->v[0].x = bx;
        s->v[0].y = by; s->v[0].z = 0x100000; s->v[0].f = 0;
    s->v[1].rgba = t[2] | a; s->v[1].q = 1; s->v[1].x = bx; s->v[1].y = by + h; s->v[1].z = 0x100000; s->v[1].f = 0;
    s->v[2].rgba = t[1] | a; s->v[2].q = 1; s->v[2].x = bx + w - 128; s->v[2].y = by; s->v[2].z = 0x100000; s->v[2].f = 0;
    s->v[3].rgba = t[3] | a; s->v[3].q = 1; s->v[3].x = bx + w - 128; s->v[3].y = by + h; s->v[3].z = 0x100000; s->v[3].f = 0;
    s->v[4].rgba = t[1] | a; s->v[4].q = 1; s->v[4].x = bx + w; s->v[4].y = by + 128; s->v[4].z = 0x100000; s->v[4].f = 0;
    s->v[5].rgba = t[3] | a; s->v[5].q = 1; s->v[5].x = bx + w; s->v[5].y = by + h; s->v[5].z = 0x100000; s->v[5].f = 0;
    s->v[6].rgba = t[4] | a; s->v[6].q = 1; s->v[6].x = bx + 32; s->v[6].y = by + 32; s->v[6].z = 0x100000; s->v[6].f = 0x8000;
    s->v[7].rgba = t[6] | a; s->v[7].q = 1; s->v[7].x = bx + 32; s->v[7].y = by + h - 32; s->v[7].z = 0x100000; s->v[7].f = 0x8000;
    s->v[8].rgba = t[5] | a; s->v[8].q = 1; s->v[8].x = bx + w - 160; s->v[8].y = by + 32; s->v[8].z = 0x100000; s->v[8].f = 0;
    s->v[9].rgba = t[7] | a; s->v[9].q = 1; s->v[9].x = bx + w - 160; s->v[9].y = by + h - 32; s->v[9].z = 0x100000; s->v[9].f = 0;
    s->v[10].rgba = t[5] | a; s->v[10].q = 1; s->v[10].x = bx + w - 32; s->v[10].y = by + 160; s->v[10].z = 0x100000; s->v[10].f = 0;
    s->v[11].rgba = t[7] | a; s->v[11].q = 1; s->v[11].x = bx + w - 32; s->v[11].y = by + h - 32; s->v[11].z = 0x100000; s->v[11].f = 0;
    if (o->u48.w.lo & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
        fx = cx;
        fy = cy;
        X = fx + (f32)(s->v[0].x - cx) * sx;
        Y = fy + (f32)(s->v[0].y - cy) * sy;
        Yh = fy + (f32)(s->v[1].y - cy) * sy;
        Xw128 = fx + (f32)(s->v[2].x - cx) * sx;
        Xw = fx + (f32)(s->v[4].x - cx) * sx;
        Y128 = fy + (f32)(s->v[4].y - cy) * sy;
        X32 = fx + (f32)(s->v[6].x - cx) * sx;
        Y32 = fy + (f32)(s->v[6].y - cy) * sy;
        Yh32 = fy + (f32)(s->v[7].y - cy) * sy;
        s->v[0].x = X;
        s->v[0].y = Y;
        s->v[1].y = Yh;
        s->v[2].x = Xw128;
        Xw160 = fx + (f32)(s->v[8].x - cx) * sx;
        s->v[3].y = Yh;
        s->v[4].y = Y128;
        s->v[4].x = Xw;
        s->v[5].x = Xw;
        Xw32 = fx + (f32)(s->v[10].x - cx) * sx;
        s->v[6].x = X32;
        s->v[1].x = X;
        s->v[6].y = Y32;
        s->v[7].x = X32;
        s->v[8].x = Xw160;
        s->v[3].x = Xw128;
        s->v[5].y = Yh;
        s->v[8].y = Y32;
        s->v[2].y = Y;
        s->v[9].x = Xw160;
        s->v[7].y = Yh32;
        s->v[9].y = Yh32;
        s->v[10].x = Xw32;
        Y160 = fy + (f32)(s->v[10].y - cy) * sy;
        s->v[10].y = Y160;
        s->v[11].x = Xw32;
        s->v[11].y = Yh32;
    }
    buf[0] = (((s32)(s + 1) - (s32)buf) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), u);
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
}

void func_001f52e8(TextWin *o) {
    Q *buf; Pk *p; void *ub; s32 a, b, x, y; f32 fa, fb, sx, sy, t0, t1, t2, t3;
    PlatDmaSend(PlatDmaGetChan(2), &D_003F1A70);
    buf = func_00122048(1024, 128); p = (Pk *)(buf + 1);
    ub = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p->tag = 0x4023400000008001; p->ad = 0x44ee; p->d2 = 68; p->d3 = 66;
    p->d4 = func_001edd88(o->x6c, o->x90); p->d5 = 1;
    p->x0 = x = o->xb0; p->y0 = y = o->xb4; p->z0 = 0x100000; p->w0 = 0;
    p->x1 = x + o->xb8 * 16; p->y1 = y + o->xba * 16; p->z1 = 0x100000; p->w1 = 0;
    if (o->u48.w.lo & 1) {
        a = func_001f4570(o); b = func_001f45e0(o);
        sx = o->x74; sy = o->x78; fa = a; fb = b;
        t0 = fa + (p->x0 - a) * sx; t1 = fb + (p->y0 - b) * sy; t2 = fa + (p->x1 - a) * sx;
        p->x0 = t0; p->y0 = t1; t3 = fb + (p->y1 - b) * sy; p->y1 = t3; p->x1 = t2;
    }
    buf->a = ((Q *)(p + 1) - buf - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), ub); PlatGsSyncPath(0, 0); func_001220b8(buf);
}

void func_001f54f8(TextWin *o) {
    u64 *buf;
    Pk3 *s;
    void *u;
    u32 *t;
    u32 a;
    s32 bx, by, w, cx, cy;
    f32 fx, fy, sx, sy;
    s32 X32, X160, Xw, Y32, Y160, Y352, Y384;
    PlatDmaSend(PlatDmaGetChan(2), &D_003F1A70);
    if (o->x88 & 0x10) {
        PlatDmaSend(PlatDmaGetChan(2), D_003F27D0);
    }
    buf = (u64 *)func_00122048(1024, 128);
    s = (Pk3 *)(buf + 2);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    s->h[0] = 0x1026400000008001;
    s->h[1] = 14;
    s->h[2] = 68;
    s->h[3] = 66;
    s->h[4] = 0x200000000000800a;
    s->h[5] = 78;
    a = o->x90 << 24;
    t = o->x68;
    bx = o->xb0;
    by = o->xb4;
    w = o->xb8;
    if (t == 0) t = ((u32 (*)[12])&D_003E8E30)[D_003F1A68];
    s->v[0].rgba = t[8] | a; s->v[0].q = 1; s->v[0].x = bx + 32; s->v[0].y = by + 160; s->v[0].z = 0x100000; s->v[0].f = 0x8000;
    s->v[1].rgba = t[10] | a; s->v[1].q = 1; s->v[1].x = bx + 32; s->v[1].y = by + 352; s->v[1].z = 0x100000; s->v[1].f = 0x8000;
    s->v[2].rgba = t[8] | a; s->v[2].q = 1; s->v[2].x = bx + 160; s->v[2].y = by + 32; s->v[2].z = 0x100000; s->v[2].f = 0;
    s->v[3].rgba = t[10] | a; s->v[3].q = 1; s->v[3].x = bx + 160; s->v[3].y = by + 352; s->v[3].z = 0x100000; s->v[3].f = 0;
    s->v[4].rgba = t[9] | a; s->v[4].q = 1; s->v[4].x = bx + w - 32; s->v[4].y = by + 32; s->v[4].z = 0x100000; s->v[4].f = 0;
    s->v[5].rgba = t[11] | a; s->v[5].q = 1; s->v[5].x = bx + w - 32; s->v[5].y = by + 352; s->v[5].z = 0x100000; s->v[5].f = 0;
    s->v[6].rgba = t[0] | a; s->v[6].q = 1; s->v[6].x = bx + 32; s->v[6].y = by + 352; s->v[6].z = 0x100000; s->v[6].f = 0x8000;
    s->v[7].rgba = t[0] | a; s->v[7].q = 1; s->v[7].x = bx + 32; s->v[7].y = by + 384; s->v[7].z = 0x100000; s->v[7].f = 0x8000;
    s->v[8].rgba = t[1] | a; s->v[8].q = 1; s->v[8].x = bx + w - 32; s->v[8].y = by + 352; s->v[8].z = 0x100000; s->v[8].f = 0;
    s->v[9].rgba = t[1] | a; s->v[9].q = 1; s->v[9].x = bx + w - 32; s->v[9].y = by + 384; s->v[9].z = 0x100000; s->v[9].f = 0;
    if (o->u48.w.lo & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
        fx = cx;
        fy = cy;
        X32 = fx + (f32)(s->v[0].x - cx) * sx;
        Y352 = fy + (f32)(s->v[1].y - cy) * sy;
        X160 = fx + (f32)(s->v[2].x - cx) * sx;
        Y32 = fy + (f32)(s->v[2].y - cy) * sy;
        Xw = fx + (f32)(s->v[4].x - cx) * sx;
        Y160 = fy + (f32)(s->v[0].y - cy) * sy;
        Y384 = fy + (f32)(s->v[7].y - cy) * sy;
        s->v[0].x = X32; s->v[0].y = Y160;
        s->v[1].x = X32; s->v[1].y = Y352;
        s->v[2].x = X160; s->v[2].y = Y32;
        s->v[3].x = X160; s->v[3].y = Y352;
        s->v[4].x = Xw; s->v[4].y = Y32;
        s->v[5].x = Xw; s->v[5].y = Y352;
        s->v[6].x = X32; s->v[6].y = Y352;
        s->v[7].x = X32; s->v[7].y = Y384;
        s->v[8].x = Xw; s->v[8].y = Y352;
        s->v[9].x = Xw; s->v[9].y = Y384;
    }
    buf[0] = (((s32)(s + 1) - (s32)buf) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), u);
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
}

void func_001f5988(TextWin *o) {
    u64 *buf;
    Pk3 *s;
    void *u;
    u32 *t;
    u32 a;
    s32 bx, by, w, cx, cy;
    f32 fx, fy, sx, sy;
    s32 X32, X160, Xw, Y32, Y160, Y352, Y384;
    PlatDmaSend(PlatDmaGetChan(2), &D_003F1A70);
    if (o->x88 & 0x10) {
        PlatDmaSend(PlatDmaGetChan(2), D_003F27D0);
    }
    buf = (u64 *)func_00122048(1024, 128);
    s = (Pk3 *)(buf + 2);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    s->h[0] = 0x1026400000008001;
    s->h[1] = 14;
    s->h[2] = 68;
    s->h[3] = 66;
    s->h[4] = 0x200000000000800a;
    s->h[5] = 78;
    a = o->x90 << 24;
    t = o->x68;
    bx = o->xb0;
    by = o->xb4;
    w = o->xb8;
    if (t == 0) t = ((u32 (*)[12])&D_003E8E30)[D_003F1A68];
    s->v[0].rgba = t[8] | a; s->v[0].q = 1; s->v[0].x = bx + 32; s->v[0].y = by + 32; s->v[0].z = 0x100000; s->v[0].f = 0x8000;
    s->v[1].rgba = t[10] | a; s->v[1].q = 1; s->v[1].x = bx + 32; s->v[1].y = by + 352; s->v[1].z = 0x100000; s->v[1].f = 0x8000;
    s->v[2].rgba = t[8] | a; s->v[2].q = 1; s->v[2].x = bx + w - 160; s->v[2].y = by + 32; s->v[2].z = 0x100000; s->v[2].f = 0;
    s->v[3].rgba = t[10] | a; s->v[3].q = 1; s->v[3].x = bx + w - 160; s->v[3].y = by + 352; s->v[3].z = 0x100000; s->v[3].f = 0;
    s->v[4].rgba = t[9] | a; s->v[4].q = 1; s->v[4].x = bx + w - 160; s->v[4].y = by + 160; s->v[4].z = 0x100000; s->v[4].f = 0;
    s->v[5].rgba = t[11] | a; s->v[5].q = 1; s->v[5].x = bx + w - 160; s->v[5].y = by + 352; s->v[5].z = 0x100000; s->v[5].f = 0;
    s->v[6].rgba = t[0] | a; s->v[6].q = 1; s->v[6].x = bx + 32; s->v[6].y = by + 352; s->v[6].z = 0x100000; s->v[6].f = 0x8000;
    s->v[7].rgba = t[0] | a; s->v[7].q = 1; s->v[7].x = bx + 32; s->v[7].y = by + 384; s->v[7].z = 0x100000; s->v[7].f = 0x8000;
    s->v[8].rgba = t[1] | a; s->v[8].q = 1; s->v[8].x = bx + w - 160; s->v[8].y = by + 352; s->v[8].z = 0x100000; s->v[8].f = 0;
    s->v[9].rgba = t[1] | a; s->v[9].q = 1; s->v[9].x = bx + w - 160; s->v[9].y = by + 384; s->v[9].z = 0x100000; s->v[9].f = 0;
    if (o->u48.w.lo & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
        fx = cx;
        fy = cy;
/*P*/
        X32 = fx + (f32)(s->v[0].x - cx) * sx;
        Y32 = fy + (f32)(s->v[0].y - cy) * sy;
        Y352 = fy + (f32)(s->v[1].y - cy) * sy;
        X160 = fx + (f32)(s->v[2].x - cx) * sx;
        Xw = fx + (f32)(s->v[4].x - cx) * sx;
        Y160 = fy + (f32)(s->v[4].y - cy) * sy;
        Y384 = fy + (f32)(s->v[7].y - cy) * sy;
/*Q*/
        s->v[0].x = X32; s->v[0].y = Y32;
        s->v[1].x = X32; s->v[1].y = Y352;
        s->v[2].x = X160; s->v[2].y = Y32;
        s->v[3].x = X160; s->v[3].y = Y352;
        s->v[4].x = Xw; s->v[4].y = Y160;
        s->v[5].x = Xw; s->v[5].y = Y352;
        s->v[6].x = X32; s->v[6].y = Y352;
        s->v[7].x = X32; s->v[7].y = Y384;
        s->v[8].x = Xw; s->v[8].y = Y352;
        s->v[9].x = Xw; s->v[9].y = Y384;
    }
    buf[0] = (((s32)(s + 1) - (s32)buf) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), u);
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
}
