#include "common.h"

/* ---- b860 ---- */
#include "data/types/nostrict_text_00170000_s6_10.h"
typedef struct { f32 x, y, z, len; } Seg;
#include "data/pieces/D_00362438.h"
typedef Path_362438 Path;
typedef struct { u8 pad0[0x30]; V4 x30; } ActB;
extern V4 D_00575970;
extern V4 D_003626A0;
extern V4 D_005758D0;
extern ActB *D_00575894;
void func_00267530(V4 *, V4 *, V4 *);
void func_002673b8(V4 *, V4 *);
f32 func_00267390(V4 *, V4 *);
f32 func_00120c18(V4 *);
f32 func_00120bf8(V4 *);

/* rodata */
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

/* ---- ba80 ---- */
#define D_00362438 D_00362438_ba80
#define D_00575940 D_00575940_ba80
#define Path Path_ba80
#define func_0017b250 func_0017b250_ba80
#define func_0017b308 func_0017b308_ba80
#define func_0017b4f8 func_0017b4f8_ba80
#define func_0017b668 func_0017b668_ba80
#define func_0017b860 func_0017b860_ba80
typedef struct Path {
    s32 n; f32 x4; f32 x8; f32 xc; u8 pad10[4]; f32 x14; s32 flags; u8 pad1c[4]; Seg seg[1];
} Path;
typedef struct Cam {
    V4 x0; V4 x10; V4 x20; V4 x30;
    s32 x40; s32 x44; f32 x48; f32 x4c; f32 x50; f32 x54; f32 x58; f32 x5c; f32 x60;
    u8 x64; u8 x65; u8 x66;
} Cam;
extern Path *D_00362438 __asm__("D_00362438");
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
    Path *path = D_00362438;
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
#undef Path
#undef func_0017b250
#undef func_0017b308
#undef func_0017b4f8
#undef func_0017b668
#undef func_0017b860

/* ---- c8e8x ---- */
#define D_00362438 D_00362438_c8e8x
#define D_005758D0 D_005758D0_c8e8x
#define D_005758E0 D_005758E0_c8e8x
#define D_00575940 D_00575940_c8e8x
#define Path Path_c8e8x
#define func_0017b250 func_0017b250_c8e8x
#define func_0017b308 func_0017b308_c8e8x
#define func_0017b4f8 func_0017b4f8_c8e8x
#define func_0017b668 func_0017b668_c8e8x
#define func_0017b860 func_0017b860_c8e8x
#define func_002675a8 func_002675a8_c8e8x
typedef struct Path {
    s32 n; f32 x4; f32 x8; f32 xc; u8 pad10[4]; f32 x14; s32 flags; u8 pad1c[4]; Seg seg[1];
} Path;
extern Path *D_00362438 __asm__("D_00362438");
extern Cam D_00575940 __asm__("D_00575940");
extern V4 D_005758D0 __asm__("D_005758D0");
extern V4 D_005758E0 __asm__("D_005758E0");
void func_0017b308(void *, Seg *, s32, s32, s32) __asm__("func_0017b308");
void func_0017b250(void *, void *, f32) __asm__("func_0017b250");
s32 func_0017b4f8(s32 *, f32 *, f32) __asm__("func_0017b4f8");
s32 func_0017b860(s32, V4 *, f32 *, s32 *) __asm__("func_0017b860");
f32 func_0017b668(s32, s32, f32, f32) __asm__("func_0017b668");
void func_002675a8(void *, void *) __asm__("func_002675a8");

void func_0017c8e8(void) {
    f32 m[4][4];
    Path *path = D_00362438;
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
#undef Path
#undef func_0017b250
#undef func_0017b308
#undef func_0017b4f8
#undef func_0017b668
#undef func_0017b860
#undef func_002675a8

/* ---- c9a8 ---- */
#define D_00362438 D_00362438_c9a8
#define D_005758E0 D_005758E0_c9a8
#define D_00575940 D_00575940_c9a8
#define D_00575970 D_00575970_c9a8
#define Path Path_c9a8
#define func_00120bf8 func_00120bf8_c9a8
#define func_0017b250 func_0017b250_c9a8
#define func_0017b308 func_0017b308_c9a8
#define func_0017ba80 func_0017ba80_c9a8
#define func_0017bc90 func_0017bc90_c9a8
#define func_0017c7f0 func_0017c7f0_c9a8
#define func_00267518 func_00267518_c9a8
#define func_00267530 func_00267530_c9a8
#define func_00267560 func_00267560_c9a8
typedef struct Path {
    s32 n; f32 x4; f32 x8; f32 xc; u8 pad10[4]; f32 x14; s32 flags; u8 pad1c[4]; Seg seg[1];
} Path;
extern Path *D_00362438 __asm__("D_00362438");
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
    Path *path = D_00362438;

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
#undef Path
#undef func_00120bf8
#undef func_0017b250
#undef func_0017b308
#undef func_0017ba80
#undef func_0017bc90
#undef func_0017c7f0
#undef func_00267518
#undef func_00267530
#undef func_00267560

/* ---- e768 ---- */
#define D_00575894 D_00575894_e768
extern s32 D_00362420;
extern void *D_00575894 __asm__("D_00575894");
CONTEXT_ONLY s32 func_0017dc40(void) { return 0; }
s32 func_001773b0(void);
void func_00176f08(s32, f32);

void func_0017e768(void) {
    s32 *p = &D_00362420;
    if (*p == 0) return;
    *p = 0;
    if (D_00575894 == 0) return;
    if (func_0017dc40()) return;
    if (func_001773b0()) {
        func_00176f08(1, 30.0f);
        return;
    }
}
#undef D_00575894

/* ---- f510 ---- */
#define D_00575894 D_00575894_f510
extern void *D_00575894 __asm__("D_00575894");
extern s32 D_002E27A8;
extern s32 D_005758C4; /* src/data/bss_0057.c: f32 D_005758C4 */
#include "data/pieces/D_00362424.h"
#include "data/pieces/D_0036244C.h"
#include "data/pieces/D_00362454.h"
void func_0017ecf8(void);
s32 func_0011ef10(s32, void *);
void func_0017f150(void);
void func_0017f1a0(void);
void func_0017db68(void);
void func_0017eb20(void);

void func_0017f510(void) {
    D_00575894 = 0;
    func_0011ef10(100000, func_0017ecf8);
    D_002E27A8 = 0;
    D_005758C4 = 0;
    func_0017f150();
    func_0017f1a0();
    func_0017db68();
    D_00362424 = 0;
    D_0036244C = 0;
    D_00362454 = 0;
    func_0017eb20();
}
#undef D_00575894

/* ---- f580 ---- */
extern s32 D_00362704;
extern s32 D_00362708;
extern s32 D_0036270C;
#include "data/pieces/D_00362710.h"
extern f32 D_00362714;
extern f32 D_00362718;
extern f32 D_0036271C;
extern f32 D_00362720;
extern f32 D_00362724;
extern f32 D_002BBDFC;
void func_0010ffb8(void *, void *);

void func_0017f580(f32 t, f32 a, f32 b, f32 c, s32 flag) {
    s32 *p = &D_00362704;
    if (*p == 0) func_0010ffb8(&D_00362708, &D_0036270C);
    *p = 1;
    D_00362710 = t + D_002BBDFC;
    D_00362718 = b;
    D_0036271C = c;
    if (flag) {
        D_00362720 = b / t;
        D_00362724 = c / t;
    } else {
        D_00362720 = 0.0f;
        D_00362724 = 0.0f;
    }
    D_00362714 = a;
}

/* ---- fb98 ---- */
#include "data/pieces/D_00364130.h"
typedef Sub80_364130 Sub80;
typedef E0C0_364130 E0C0;

void func_0011d3c8(s32, s32, s32);
void func_00182788(E0C0 *);
void func_001827f0(E0C0 *);

void func_0017fb98(s32 key) {
    s32 i;
    s32 off;
    E0C0 *t;
    Sub80 *s;
    off = 0;
    t = D_00364130.e0C0;
    i = 0;
    s = &t->s;
    for (; i < 256; i++) {
        if ((s->flags & 1) && s->key == key) {
            E0C0 *e;
            if (s->p8c->xfc) func_0011d3c8(s->p8c->xfc, s->xa8, 60);
            e = (E0C0 *)(off + (u32)t);
            func_00182788(e);
            func_001827f0(e);
            return;
        }
        s = (Sub80 *)((u8 *)s + sizeof(E0C0));
        off += sizeof(E0C0);
    }
}

/* ---- fcd8 ---- */
void func_0011d3c8(s32, s32, s32);
void func_00182788(E0C0 *);
void func_00182840(E0C0 *);

void func_0017fcd8(s32 key) {
    s32 i;
    s32 off;
    E0C0 *t;
    Sub80 *s;
    off = 0;
    t = D_00364130.e0C0;
    i = 0;
    s = &t->s;
    for (; i < 256; i++) {
        if ((s->flags & 1) && s->key == key) {
            E0C0 *e;
            if (s->p8c->xfc) func_0011d3c8(s->p8c->xfc, s->xa8, 60);
            e = (E0C0 *)(off + (u32)t);
            func_00182788(e);
            func_00182840(e);
            return;
        }
        s = (Sub80 *)((u8 *)s + sizeof(E0C0));
        off += sizeof(E0C0);
    }
}

/* ---- fd88 ---- */
void func_0011d3c8(s32, s32, s32);
void func_00182788(E0C0 *);
void func_001827f0(E0C0 *);

void func_0017fd88(s32 lo, s32 n) {
    s32 i;
    s32 off = 0;
    E0C0 *t = D_00364130.e0C0;
    Sub80 *s = &t->s;
    for (i = 0; i < 256; i++) {
        if (s->flags & 1) {
            s32 d = s->x88 - lo;
            if (d >= 0 && d < n) {
                E0C0 *e;
                if (s->p8c->xfc) func_0011d3c8(s->p8c->xfc, s->xa8, 60);
                e = (E0C0 *)(off + (u32)t);
                func_00182788(e);
                func_001827f0(e);
            }
        }
        s = (Sub80 *)((u8 *)s + sizeof(E0C0));
        off += sizeof(E0C0);
    }
}

/* ---- fe60 ---- */
void func_0011d3c8(s32, s32, s32);
void func_00182788(E0C0 *);
void func_00182840(E0C0 *);

void func_0017fe60(s32 lo, s32 n) {
    s32 i;
    s32 off = 0;
    E0C0 *t = D_00364130.e0C0;
    Sub80 *s = &t->s;
    for (i = 0; i < 256; i++) {
        if (s->flags & 1) {
            s32 d = s->x88 - lo;
            if (d >= 0 && d < n) {
                E0C0 *e;
                if (s->p8c->xfc) func_0011d3c8(s->p8c->xfc, s->xa8, 60);
                e = (E0C0 *)(off + (u32)t);
                func_00182788(e);
                func_00182840(e);
            }
        }
        s = (Sub80 *)((u8 *)s + sizeof(E0C0));
        off += sizeof(E0C0);
    }
}

/* ---- ff38 ---- */
#define D_00364130 D_00364130_ff38
#define E0C0 E0C0_ff38
typedef struct E0C0 {
    u8 pad0[0x86];
    u16 flags;
    u8 pad88[0xb1 - 0x88];
    u8 xb1;
    u8 padb2[5];
    u8 xb7;
    u8 padb8[0xc0 - 0xb8];
} E0C0;
extern E0C0 D_00364130[256] __asm__("D_00364130");

void func_0017ff38(s32 on) {
    s32 i;
    for (i = 0; i < 256; i++) {
        if (D_00364130[i].flags & 1) {
            if (on) {
                D_00364130[i].xb7 = 1;
                D_00364130[i].xb1 |= 0x80;
            } else {
                D_00364130[i].xb7 = 0;
                D_00364130[i].xb1 &= 0x7f;
            }
        }
    }
}
#undef D_00364130
#undef E0C0

/* ---- 0878 ---- */
typedef struct { void *p; s32 x4; } E8;
extern E8 D_00363930[];

/* ---- 09b8 ---- */
typedef struct { u16 a; u16 b; void *p; } E8b;
extern E8b D_00363D30[];

/* ---- 2058 ---- */
#define D_00362730 D_00362730_2058
#define D_00363930 D_00363930_2058
#define D_00363D30 D_00363D30_2058
#define D_00364130 D_00364130_2058
#define D_00595E40 D_00595E40_2058
#define D_00615E40 D_00615E40_2058
#define D_00615E64 D_00615E64_2058
#define D_006161C0 D_006161C0_2058
#define D_00616200 D_00616200_2058
#define D_0061621C D_0061621C_2058
#define D_00616220 D_00616220_2058
#define E0C0 E0C0_2058
#define func_0017f910 func_0017f910_2058
#define func_0017f9a8 func_0017f9a8_2058
#define func_00183a00 func_00183a00_2058
typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct { u8 pad[0x10]; void *x10; void *x14; void *x18; } Pmgr;
typedef struct E0C0 {
    u8 pad0[0x86];
    u16 flags;
    u8 pad88[0xc0 - 0x88];
} E0C0;
extern Pmgr D_00615E40 __asm__("D_00615E40");
extern u8 D_00595E40[] __asm__("D_00595E40");
extern s32 D_0061621C __asm__("D_0061621C");
extern Pmgr *D_00615E64 __asm__("D_00615E64");
extern u8 D_00362730[] __asm__("D_00362730");
extern u8 D_00363930[] __asm__("D_00363930");
extern u8 D_00363D30[] __asm__("D_00363D30");
extern E0C0 D_00364130[256] __asm__("D_00364130");
extern s32 D_00616220 __asm__("D_00616220");
extern V4 D_006161C0[4] __asm__("D_006161C0");
extern V4 D_00616200 __asm__("D_00616200");
void func_0017f9a8(void) __asm__("func_0017f9a8");
void func_00183a00(void *, void *, s32) __asm__("func_00183a00");
void func_0017f910(s32, s32) __asm__("func_0017f910");
#undef D_00362730
#undef D_00363930
#undef D_00363D30
#undef D_00364130
#undef D_00595E40
#undef D_00615E40
#undef D_00615E64
#undef D_006161C0
#undef D_00616200
#undef D_0061621C
#undef D_00616220
#undef E0C0
#undef func_0017f910
#undef func_0017f9a8
#undef func_00183a00

/* ---- 3a48 ---- */

#include "data/bss_0061_mixed.h"
#include "data/bss_0061_typed.h"
#include "data/data_002E.h"
#include "data/data_0036.h"
#include "data/pieces/D_00362690_2.h"
#include "data/pieces/D_002BBDFC.h"
