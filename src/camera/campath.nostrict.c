/* The field camera's path mode, without strict aliasing (docs/modules.md
 * "Session 51"): the Bezier control points of a path segment
 * (func_0017b308), the step along the path (func_0017b4f8), the nearest point
 * of the path to the player (func_0017b860, func_0017ba80) and the path
 * camera's position and target updates (func_0017bc90 ... func_0017cf08).
 * campath.c has the rest.  Read from the code, not proved by a boot. */
#include "common.h"
#include "data/pieces/D_0035BD40.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_0035C440.h"
#include "data/pieces/D_0035C460.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_00362438.h"
#include "data/types/nostrict_text_00170000_s6_10.h"
#include "data/types/nostrict_text_00170000_b06.h"
#include "data/types/nostrict_text_00170000_b06_p.h"
#include "data/pieces/D_002E31B0.h"
#include "data/types/nostrict_text_00170000_b06_p2.h"
#include "data/pieces/D_00362430.h"
#include "data/pieces/D_00362434.h"
#include "data/pieces/D_0036243C.h"
#include "data/pieces/D_00362424.h"
#include "data/pieces/D_002C5960.h"

/* func_0017b308 (from hand/nostrict/text_00160000_s6_09.c). */
void func_002675a8(void *, void *);
void func_00267530(void *, void *, void *);
void func_00267518(void *, void *, void *);
void func_00267560(void *, void *, f32);
void func_002673b8(void *, void *);
typedef struct { f32 x, y, z, w; } V4_7b308;
f32 func_00120bf8(V4_7b308 *);
void func_0017b308(V4_7b308 *out, V4_7b308 *seg, s32 n, s32 i, s32 loop) {
    V4_7b308 a, b;
    s32 nx, nn, pv;
    nx = (i + 1 < n) ? i + 1 : 0;
    nn = (nx + 1 < n) ? nx + 1 : 0;
    pv = i - 1; if (pv < 0) pv = n - 1;
    func_002675a8(&out[0], &seg[i]);
    func_002675a8(&out[3], &seg[nx]);
    if (i == 0 && loop) {
        func_002675a8(&out[1], &out[0]);
    } else {
        func_00267530(&a, &seg[nx], &seg[pv]);
        func_002673b8(&a, &a);
        func_00267530(&b, &seg[nx], &seg[i]);
        func_00267560(&a, &a, func_00120bf8(&b) * 0.3f);
        func_00267518(&out[1], &out[0], &a);
    }
    if (i == n - 2 && loop) {
        func_002675a8(&out[2], &out[3]);
    } else {
        func_00267530(&a, &seg[nn], &seg[i]);
        func_002673b8(&a, &a);
        func_00267530(&b, &seg[nn], &seg[nx]);
        func_00267560(&a, &a, func_00120bf8(&b) * 0.3f);
        func_00267530(&out[2], &out[3], &a);
    }
}

/* func_0017b4f8 (from hand/nostrict/text_s7_w27.c). */
typedef struct { f32 len, x, y, z; } SegL;
/* func_0017b4f8: MATCH hand/nostrict */
s32 func_0017b4f8(s32 *pi, f32 *pt, f32 dt) {
    s32 i = *pi;
    Path_362438 *p = D_00362438;
    s32 changed = 0;
    f32 inv, t, rem;
    s32 nl;
    inv = 1.0f / ((SegL *)((u8 *)p + 0x2c))[i].len;
    { s32 f = p->x18 & 1; nl = f != 0; }
    t = *pt;
    t += dt * inv;
    if (!(t < 0.0f)) goto pos;
    if (!nl || i != 0) goto neg;
    t = 0.0f;
    i = 0;
    goto store;
neg:
    rem = (t - 0.0f) / inv;
    { s32 j = i - 1; if (j < 0) j = p->n - 1; i = j; }
    t = 1.0f;
    changed = 1;
    goto again;
pos:
    if (!(1.0f < t)) goto store;
    if (nl && !(i < p->n - 2)) {
        i = p->n - 2;
        t = 1.0f;
        goto store;
    }
    i = (i + 1 < p->n) ? i + 1 : 0;
    rem = (t - 1.0f) / inv;
    changed = 1;
    t = 0.0f;
again:
    inv = 1.0f / ((SegL *)((u8 *)p + 0x2c))[i].len;
    t += rem * inv;
    if (!(t < 0.0f)) goto pos;
    if (!nl || i != 0) goto neg;
    t = 0.0f;
store:
    *pi = i;
    *pt = t;
    return changed;
}

/* func_0017b860 (from hand/nostrict/text_00170000_s6_10.c). */
typedef Path_362438 Path;
typedef struct { u8 pad0[0x30]; V4 x30; } ActB;
extern V4 D_00575970;
extern V4 D_003626A0;
extern V4 D_005758D0;
extern ActB *D_00575894;
f32 func_00267390(V4 *, V4 *);
f32 func_00120c18(V4 *);
s32 func_0017b860(s32 mode, V4 *pos, f32 *out, s32 *first) {
    V4 t;
    V4 a;
    V4 b;
    f32 d;
    f32 r;
    Path *p = D_00362438;

    switch (mode) {
    default:
    case 0:
        func_00267530(&t, &D_00575970, pos);
        d = func_00120c18(&t);
        if (d < p->xc) {
            r = p->xc - d;
        } else {
            r = 0.0f;
            if (p->x10 < d) r = d - p->x10;
        }
        if (*first) {
            *out = r;
            *first = 0;
            return 1;
        }
        if (r < *out) {
            *out = r;
            return 1;
        }
        goto r0;
    case 1:
        func_00267530(&a, &D_003626A0, &D_00575970);
        func_002673b8(&a, &a);
        func_00267530(&b, pos, &D_00575970);
        func_002673b8(&b, &b);
        d = func_00267390(&a, &b);
        if (*first) {
            *out = d;
            *first = 0;
            return 1;
        }
        if (d < *out) {
            *out = d;
            return 1;
        }
        goto r0;
    case 2:
        func_00267530(&t, &D_005758D0, pos);
        d = func_00120bf8(&t);
        if (*first) {
            *out = d;
            *first = 0;
            return 1;
        }
        if (d < *out) {
            *out = d;
            return 1;
        }
        goto r0;
    case 3:
        func_00267530(&t, &D_005758D0, pos);
        d = func_00120bf8(&t);
        if (*first) {
            *out = d;
            *first = 0;
            return 1;
        }
        if (*out < d) {
            *out = d;
            return 1;
        }
        goto r0;
    case 4:
        func_00267530(&b, pos, &D_00575970);
        func_002673b8(&b, &b);
        d = func_00267390(&D_00575894->x30, &b);
        if (*first) {
            *out = d;
            *first = 0;
            return 1;
        }
        if (d < *out) {
            *out = d;
            return 1;
        }
        goto r0;
    }
r0:
    return 0;
}

/* func_0017ba80 (from hand/nostrict/text_00170000_s6_10.c). */
typedef struct { f32 x, y, z, len; } Seg;
#define D_00362438 D_00362438_ba80
#define D_00575940 D_00575940_ba80
#define Path_7ba80 Path_ba80
#define func_0017b250 func_0017b250_ba80
#define func_0017b308 func_0017b308_ba80
#define func_0017b4f8 func_0017b4f8_ba80
#define func_0017b668 func_0017b668_ba80
#define func_0017b860 func_0017b860_ba80
typedef struct Path_7ba80 {
    s32 n; f32 x4; f32 x8; f32 xc; u8 pad10[4]; f32 x14; s32 flags; u8 pad1c[4]; Seg seg[1];
} Path_7ba80;
typedef struct Cam {
    V4 x0; V4 x10; V4 x20; V4 x30;
    s32 x40; s32 x44; f32 x48; f32 x4c; f32 x50; f32 x54; f32 x58; f32 x5c; f32 x60;
    u8 x64; u8 x65; u8 x66;
} Cam;
extern Path_7ba80 *D_00362438 __asm__("D_00362438");
extern Cam D_00575940 __asm__("D_00575940");
void func_0017b308(void *, Seg *, s32, s32, s32) __asm__("func_0017b308");
void func_0017b250(void *, void *, f32) __asm__("func_0017b250");
s32 func_0017b860(s32, V4 *, f32 *, s32 *) __asm__("func_0017b860");
s32 func_0017b4f8(s32 *, f32 *, f32) __asm__("func_0017b4f8");
f32 func_0017b668(s32, s32, f32, f32) __asm__("func_0017b668");
void func_0017ba80(s32 a0) {
    f32 m[4][4];
    V4 p;
    f32 d;
    s32 f;
    s32 idx;
    f32 t;
    Path_7ba80 *path = D_00362438;
    s32 loop;
    f32 acc;
    f32 bt;
    s32 bi;
    Cam *c;

/*P*/
    f = 1;
    loop = 0; if (path->flags & 1) loop = 1;
    d = bt = 0.0f;
    idx = 0;
    t = bt;
    bi = -1;
/*Q*/
    func_0017b308(m, path->seg, path->n, 0, loop);
    for (acc = bt; acc < path->x4; acc += 10.0f) {
        func_0017b250(&p, m, t);
        if (func_0017b860(a0, &p, &d, &f)) {
            bi = idx;
            bt = t;
        }
        if (func_0017b4f8(&idx, &t, 10.0f)) func_0017b308(m, path->seg, path->n, idx, loop);
    }
    func_0017b308(m, path->seg, path->n, bi, loop);
    func_0017b250(&D_00575940.x10, m, bt);
    c = &D_00575940;
    c->x44 = bi;
    c->x4c = bt;
    c->x50 = 1.0f;
    if (!loop) {
        if (bi == c->x40) {
            if (bt < c->x48) c->x50 = -1.0f;
        } else if (func_0017b668(c->x40, bi, c->x48, bt) > path->x4 * 0.5f) {
            c->x50 = -1.0f;
        }
    } else {
        if (bi == c->x40) {
            if (bt < c->x48) c->x50 = -1.0f;
        } else if (bi < c->x40) {
            c->x50 = -1.0f;
        }
    }
}
#undef D_00362438
#undef D_00575940
#undef Path_7ba80
#undef func_0017b250
#undef func_0017b308
#undef func_0017b4f8
#undef func_0017b668
#undef func_0017b860

/* func_0017bc90 (from hand/nostrict/text_00170000_b06.c). */
extern Cam D_00575940;
void func_0017b250(void *, void *, f32);
extern f32 D_002BBDFC;
/* ---- func_0017bc90 ---- */
void func_0017bc90(s32 a0) {
    f32 m[4][4];
    V4 p;
    f32 d;
    s32 f;
    s32 idx;
    f32 t;
    Path *path = D_00362438;
    s32 loop;
    f32 dir;
    f32 bt;
    s32 bi;
    f32 i;

    loop = 0;
    if (path->x18 & 1) loop = 1;
    if (D_00575940.x60 <= 0.0f) {
        dir = 0.0f;
        f = 1;
        func_0017b308(m, path->seg, path->n, D_00575940.x40, loop);
        func_0017b250(&p, m, D_00575940.x48);
        func_0017b860(a0, &p, &d, &f);
        idx = D_00575940.x40;
        t = D_00575940.x48;
        func_0017b308(m, path->seg, path->n, idx, loop);
        if (func_0017b4f8(&idx, &t, 10.0f)) func_0017b308(m, path->seg, path->n, idx, loop);
        func_0017b250(&p, m, t);
        if (func_0017b860(a0, &p, &d, &f)) {
            D_00575940.x60 = 20.0f;
            dir = 1.0f;
        }
        idx = D_00575940.x40;
        t = D_00575940.x48;
        func_0017b308(m, path->seg, path->n, idx, loop);
        if (func_0017b4f8(&idx, &t, -10.0f)) func_0017b308(m, path->seg, path->n, idx, loop);
        func_0017b250(&p, m, t);
        if (func_0017b860(a0, &p, &d, &f)) {
            D_00575940.x60 = 20.0f;
            dir = -1.0f;
        }
        if (dir == 0.0f) return;
    } else {
        dir = D_00575940.x50;
        D_00575940.x60 -= D_002BBDFC;
    }
    bt = 0.0f;
    f = 1;
    t = D_00575940.x48;
    d = 0.0f;
    idx = D_00575940.x40;
    func_0017b308(m, path->seg, path->n, idx, loop);
    bi = -1;
    for (i = 0.0f; i < 100.0f; i += 1.0f) {
        func_0017b250(&p, m, t);
        if (func_0017b860(a0, &p, &d, &f)) {
            bi = idx;
            bt = t;
        }
        if (func_0017b4f8(&idx, &t, dir)) func_0017b308(m, path->seg, path->n, idx, loop);
    }
    func_0017b308(m, path->seg, path->n, bi, loop);
    func_0017b250(&D_00575940.x10, m, bt);
    D_00575940.x44 = bi;
    D_00575940.x4c = bt;
    D_00575940.x50 = dir;
}

/* func_0017c190 (from hand/nostrict/text_00170000_b06.c). */
typedef struct {
    s32 x0; u8 pad4[0x10 - 4]; V4 x10; u8 pad20[0x10]; f32 x30[3]; f32 x3c; u8 pad40[0x64 - 0x40]; f32 x64;
    u8 pad68[0x70 - 0x68]; s32 x70; u8 pad74[0xd0 - 0x74]; f32 xd0[4][4];
} ActB_7c190;
f32 func_00120c88(f32);
f32 func_00124d28(V4 *, V4 *);
f32 fabsf(f32);
V4 D_00575860 ALIGNED(16);
extern f32 D_003625E4;
f32 func_0017c110(s32, f32);
#define D_00575894 ((ActB_7c190 *) D_00575894)
s32 func_0017c190(void) {
    f32 m[4][4];
    V4 p;
    s32 idx;
    f32 t;
    Path *path = D_00362438;
    s32 loop;
    f32 base, a, d, c, k, s, t0;
    s32 i0;

    loop = 0;
    if (path->x18 & 1) loop = 1;
    base = func_00124d28(&D_005758D0, &D_00575940.x30);
    a = base;
    if (D_00575940.x66 == 2) {
        func_002675a8(&D_00575860, D_00575894->x30);
        D_00575860.y = 0.0f;
        func_002673b8(&D_00575860, &D_00575860);
        D_00575940.x66 = 3;
        D_003625E4 = 0.0f;
    }
    func_00267530(&p, &D_005758D0, &D_00575940.x30);
    p.y = 0.0f;
    func_002673b8(&p, &p);
    d = func_00267390(&p, &D_00575860);
    k = (-1.0f - (d < -1.0f ? -1.0f : (-0.9f < d ? -0.9f : d))) / -0.1f;
    if (k < 0.1f) return 0;
    s = k * 0.1221730355f;
    idx = D_00575940.x40;
    t = D_00575940.x48;
    func_0017b308(m, path->seg, path->n, idx, loop);
    while (fabsf(func_00120c88(a - base)) < s * D_002BBDFC) {
        t0 = t;
        i0 = idx;
        func_0017b250(&p, m, t0);
        a = func_00124d28(&p, &D_00575940.x30);
        D_003625E4 += 10.0f;
        if (func_0017b4f8(&idx, &t, D_00575940.x50 * 10.0f)) func_0017b308(m, path->seg, path->n, idx, loop);
        if (i0 == idx && t == t0) return 0;
    }
    if (!(func_0017c110(idx, t) > 150.0f)) return 0;
    D_00575940.x40 = idx;
    D_00575940.x44 = idx;
    D_00575940.x48 = t;
    D_00575940.x4c = t;
    func_0017b308(m, path->seg, path->n, idx, loop);
    func_0017b250(&D_00575940.x10, m, t);
    if (path->x4 < D_003625E4) return 0;
    return 1;
}
#undef D_00575894

/* func_0017c550 (from hand/nostrict/text_00170000_b06.c). */
typedef struct { u32 x0, x4; u64 x8; u8 pad10[0x44 - 0x10]; f32 x44; } PadB;
extern PadB D_002C5BB0;
/* ---- func_0017c550 ---- */
void func_0017c550(void) {
    f32 m[4][4];
    V4 p;
    struct { s32 idx; f32 t; } q;
/*P*/
    Path *path = D_00362438;
    s32 loop;
    u64 k;
    f32 dir;
    f32 base;
    f32 a;
    f32 d0;
    f32 d;
    f32 t0;
    s32 i0;
/*Q*/

    if (D_00575940.x66 == 3) return;
    loop = 0;
    if (path->x18 & 1) loop = 1;
    k = *(u64 *)&D_002C5BB0 & 0x300000000000ULL;
    dir = 0.0f;
    if (k == 0x100000000000ULL) {
        dir = 1.0f;
        D_00575940.x66 = 1;
    } else if (k == 0x200000000000ULL) {
        dir = -1.0f;
        D_00575940.x66 = 1;
    } else {
        D_00575940.x66 = 0;
    }
    if (D_00575940.x66 != 1) return;
    a = func_00124d28(&D_005758D0, &D_00575940.x30);
    base = a;
    q.idx = D_00575940.x40;
    q.t = D_00575940.x48;
    func_0017b308(m, path->seg, path->n, q.idx, loop);
    d0 = func_0017c110(q.idx, q.t);
    while (fabsf(func_00120c88(a - base)) < D_002BBDFC * 0.01745329099f) {
        t0 = q.t;
        i0 = q.idx;
        func_0017b250(&p, m, t0);
        a = func_00124d28(&p, &D_00575940.x30);
        if (func_0017b4f8(&q.idx, &q.t, dir * 10.0f)) func_0017b308(m, path->seg, path->n, q.idx, loop);
        if (i0 == q.idx && q.t == t0) break;
    }
    d = func_0017c110(q.idx, q.t);
    if (d > 150.0f || (d < 150.0f && d0 < d)) {
        D_00575940.x40 = q.idx;
        D_00575940.x44 = q.idx;
        D_00575940.x48 = q.t;
        D_00575940.x4c = q.t;
        func_0017b308(m, path->seg, path->n, q.idx, loop);
        func_0017b250(&D_00575940.x10, m, q.t);
    } else {
        D_00575940.x5c = 30.0f;
    }
}

/* func_0017c8e8 (from hand/nostrict/text_00170000_s6_10.c). */
#define D_00362438 D_00362438_c8e8x
#define D_005758D0 D_005758D0_c8e8x
#define D_005758E0 D_005758E0_c8e8x
#define D_00575940 D_00575940_c8e8x
#define Path_7c8e8 Path_c8e8x
#define func_0017b250 func_0017b250_c8e8x
#define func_0017b308 func_0017b308_c8e8x
#define func_002675a8 func_002675a8_c8e8x
typedef struct Path_7c8e8 {
    s32 n; f32 x4; f32 x8; f32 xc; u8 pad10[4]; f32 x14; s32 flags; u8 pad1c[4]; Seg seg[1];
} Path_7c8e8;
extern Path_7c8e8 *D_00362438 __asm__("D_00362438");
extern Cam D_00575940 __asm__("D_00575940");
extern V4 D_005758D0 __asm__("D_005758D0");
extern V4 D_005758E0 __asm__("D_005758E0");
void func_0017b308(void *, Seg *, s32, s32, s32) __asm__("func_0017b308");
void func_0017b250(void *, void *, f32) __asm__("func_0017b250");
void func_002675a8(void *, void *) __asm__("func_002675a8");
void func_0017c8e8(void) {
    f32 m[4][4];
    Path_7c8e8 *path = D_00362438;
    if (path->flags & 8) {
        D_00575940.x40 = 0;
        D_00575940.x48 = 0.0f;
    } else {
        func_0017ba80(0);
        D_00575940.x40 = D_00575940.x44;
        D_00575940.x48 = D_00575940.x4c;
    }
    func_0017b308(m, path->seg, path->n, D_00575940.x40, path->flags & 1);
    func_0017b250(&D_00575940, m, D_00575940.x48);
    func_002675a8(&D_005758D0, &D_00575940);
    func_002675a8(&D_005758E0, &D_00575940.x30);
    D_00575940.x66 = 0;
}
#undef D_00362438
#undef D_005758D0
#undef D_005758E0
#undef D_00575940
#undef Path_7c8e8
#undef func_0017b250
#undef func_0017b308
#undef func_002675a8

/* func_0017c9a8 (from hand/nostrict/text_00170000_s6_10.c). */
#define D_00362438 D_00362438_c9a8
#define D_005758E0 D_005758E0_c9a8
#define D_00575940 D_00575940_c9a8
#define D_00575970 D_00575970_c9a8
#define Path_7c9a8 Path_c9a8
#define func_00120bf8 func_00120bf8_c9a8
#define func_0017b250 func_0017b250_c9a8
#define func_0017b308 func_0017b308_c9a8
#define func_0017ba80 func_0017ba80_c9a8
#define func_0017bc90 func_0017bc90_c9a8
#define func_0017c7f0 func_0017c7f0_c9a8
#define func_00267518 func_00267518_c9a8
#define func_00267530 func_00267530_c9a8
#define func_00267560 func_00267560_c9a8
typedef struct Path_7c9a8 {
    s32 n; f32 x4; f32 x8; f32 xc; u8 pad10[4]; f32 x14; s32 flags; u8 pad1c[4]; Seg seg[1];
} Path_7c9a8;
extern Path_7c9a8 *D_00362438 __asm__("D_00362438");
extern Cam D_00575940 __asm__("D_00575940");
extern V4 D_00575970 __asm__("D_00575970");
extern V4 D_005758E0 __asm__("D_005758E0");
void func_0017b308(void *, Seg *, s32, s32, s32) __asm__("func_0017b308");
void func_0017b250(void *, void *, f32) __asm__("func_0017b250");
void func_0017ba80(s32) __asm__("func_0017ba80");
void func_0017bc90(s32) __asm__("func_0017bc90");
CONTEXT_ONLY void func_0017bfe8(void) { }
void func_0017c7f0(void) __asm__("func_0017c7f0");
void func_00267530(V4 *, V4 *, V4 *) __asm__("func_00267530");
f32 func_00120bf8(V4 *) __asm__("func_00120bf8");
void func_00267560(V4 *, V4 *, f32) __asm__("func_00267560");
void func_00267518(V4 *, V4 *, V4 *) __asm__("func_00267518");
void func_0017c9a8(void) {
    f32 m[4][4];
    V4 v;
    f32 d;
    Path_7c9a8 *path = D_00362438;

    if (!D_00575940.x66) {
        if (D_00575940.x58 > 100.0f) {
            if (!(*(u64 *)&D_00575940.x60 & 0xFFFF00000000)) func_0017bc90(0);
        } else {
            if (!(*(u64 *)&D_00575940.x60 & 0xFFFF00000000)) {
                func_0017ba80(0);
                D_00575940.x64 = 1;
            }
        }
        if (D_00575940.x64) {
            func_00267530(&v, &D_00575940, &D_00575940.x10);
            if (func_00120bf8(&v) < 50.0f) D_00575940.x64 = 0;
        }
        func_0017bfe8();
    }
    func_0017c7f0();
    func_00267530(&v, &D_00575970, &D_005758E0);
    d = func_00120bf8(&v) < 0.0f ? 0.0f : (200.0f < func_00120bf8(&v) ? 200.0f : func_00120bf8(&v));
    d /= 200.0f;
    func_00267560(&v, &v, d * 0.3f);
    func_00267518(&D_005758E0, &D_005758E0, &v);
    func_0017b308(m, path->seg, path->n, D_00575940.x40, path->flags & 1);
    func_0017b250(&D_00575940, m, D_00575940.x48);
}
#undef D_00362438
#undef D_005758E0
#undef D_00575940
#undef D_00575970
#undef Path_7c9a8
#undef func_00120bf8
#undef func_0017b250
#undef func_0017b308
#undef func_0017ba80
#undef func_0017bc90
#undef func_0017c7f0
#undef func_00267518
#undef func_00267530
#undef func_00267560

/* func_0017cb88 (from hand/nostrict/text_00170000_b06.c). */
/* ---- func_0017cb88 ---- */
void func_0017cb88(void) {
    f32 m[4][4];
    V4 p;
    f32 d;
    s32 f;
    s32 idx;
    f32 t;
    Path *path = D_00362438;
    s32 loop;
    f32 dir;
    f32 bt;
    s32 bi;
    f32 i;

    loop = 0;
    if (path->x18 & 1) loop = 1;
    if (D_00575940.x60 <= 0.0f) {
        dir = 0.0f;
        f = 1;
        func_0017b308(m, path->seg, path->n, D_00575940.x40, loop);
        func_0017b250(&p, m, D_00575940.x48);
        func_0017b860(1, &p, &d, &f);
        idx = D_00575940.x40;
        t = D_00575940.x48;
        func_0017b308(m, path->seg, path->n, idx, loop);
        if (func_0017b4f8(&idx, &t, 10.0f)) func_0017b308(m, path->seg, path->n, idx, loop);
        func_0017b250(&p, m, t);
        if (func_0017b860(1, &p, &d, &f)) {
            D_00575940.x60 = 20.0f;
            dir = 1.0f;
        }
        idx = D_00575940.x40;
        t = D_00575940.x48;
        func_0017b308(m, path->seg, path->n, idx, loop);
        if (func_0017b4f8(&idx, &t, -10.0f)) func_0017b308(m, path->seg, path->n, idx, loop);
        func_0017b250(&p, m, t);
        if (func_0017b860(1, &p, &d, &f)) {
            D_00575940.x60 = 20.0f;
            dir = -1.0f;
        }
        if (dir == 0.0f) return;
    } else {
        dir = D_00575940.x50;
        D_00575940.x60 -= D_002BBDFC;
    }
    bt = 0.0f;
    d = 0.0f;
    idx = D_00575940.x40;
    t = D_00575940.x48;
    f = 1;
    func_0017b308(m, path->seg, path->n, idx, loop);
    bi = -1;
    for (i = 0.0f; i < path->x4; i += 10.0f) {
        func_0017b250(&p, m, t);
        if (func_0017b860(1, &p, &d, &f)) {
            bi = idx;
            bt = t;
            if (d < -0.5f) break;
        }
        func_00267530(&p, &D_00575940.x30, &p);
        if (func_00120c18(&p) < path->xc) break;
        if (func_0017b4f8(&idx, &t, dir * 10.0f)) func_0017b308(m, path->seg, path->n, idx, loop);
    }
    func_0017b308(m, path->seg, path->n, bi, loop);
    func_0017b250(&D_00575940.x10, m, bt);
    D_00575940.x44 = bi;
    D_00575940.x4c = bt;
    D_00575940.x50 = dir;
}

/* func_0017cf08 (from hand/nostrict/text_00170000_b06.c). */
extern V4 D_005758E0;
extern S690 D_00362690;
f32 func_0012eca8(void *, void *);
f32 func_00121840(void *, void *);
void func_002674f0(void *, void *, void *, f32);
/* defined above it in its old file (b06) */
CONTEXT_ONLY s32 func_001770b8(void) { return 0; }
void func_0017cf08(void) {
    f32 m[4][4];
    V4 v;
    V4 v2;
    V4 v3;
    Path *path = D_00362438;
    f32 r, ang, k;

    r = func_0012eca8((*(u8 (*)[0x8])&D_002E31B0), &D_00362690);
    func_00267530(&v, &D_00362690, &D_00575940.x30);
    func_002673b8(&v, &v);
    func_00267560(&v, &v, r + 100.0f);
    func_00267518(&D_00362690.b, &v, &D_00362690);
    func_00267530(&v2, &D_005758E0, &D_005758D0);
    func_00267530(&v3, &D_00575940.x30, &D_005758D0);
    ang = func_00121840(&v2, &v3) * 180.0f / 3.141592562f;
    k = (ang < 0.0f ? 0.0f : (21.19999743f < ang ? 21.19999743f : ang)) / 21.19999743f * 0.5f + 0.5f;
    func_002674f0(&v, &D_00575940.x30, &D_00362690.b, k);
    func_00267530(&v, &v, &D_005758E0);
    func_00267560(&v, &v, D_002BBDFC * 0.04999999795f);
    func_00267518(&D_005758E0, &D_005758E0, &v);
    if (D_00575940.x58 < 250.0f && func_001770b8()) D_00362690.mode = 2;
    else if (400.0f < D_00575940.x58 && func_001770b8()) D_00362690.mode = 1;
    if (!D_00575940.x65) {
        if (D_00362690.mode == 1) func_0017cb88();
        else func_0017bc90(0);
    }
    D_00575940.x66 = 0;
    func_0017bfe8();
    func_0017b308(m, path->seg, path->n, D_00575940.x40, path->x18 & 1);
    func_0017b250(&D_00575940, m, D_00575940.x48);
}

