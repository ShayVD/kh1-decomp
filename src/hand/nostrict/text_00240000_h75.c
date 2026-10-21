#include "common.h"
typedef struct { u64 lo, hi; } QW;
typedef struct { u8 pad[0x44]; s32 unk44; u8 pad48[0xBE - 0x48]; u16 unkBE; } Prof;
typedef struct { u8 pad[0x4C]; u16 unk4C; } C130;
typedef struct { u8 pad[0x6C]; Prof *unk6C; u8 pad70[0x130 - 0x70]; C130 *unk130; } Chr;
typedef struct { s32 v[48]; } __attribute__((aligned(8))) Spr;
typedef struct { u8 pad[0x18]; u64 unk18; } Tex;
typedef struct {
    s32 unk0;
    Chr *unk4;
    u8 pad8[0x48 - 8];
    Spr *unk48;
    Spr *unk4C;
    Spr *unk50;
    u8 pad54[0x70 - 0x54];
    Tex *unk70;
    u8 pad74[0x520 - 0x74];
    u8 unk520[0x780 - 0x520];
    u8 unk780[0x9FC - 0x780];
    s32 unk9FC;
    f32 unkA00;
    f32 unkA04;
    u8 unkA08[0x10];
    s32 unkA18;
    f32 unkA1C;
    u8 padA20[0xA88 - 0xA20];
    f32 *unkA88;
    f32 *unkA8C;
    u8 padA90[0xAA0 - 0xA90];
    u8 unkAA0[0x10];
} Obj;
extern u8 D_00351E10[];
extern QW *D_00651D60;
extern QW *D_00651D64;
extern f32 D_002BBDFC;
void func_0023d528(Obj *, s32 *, s32 *);
QW *func_0023d700(Spr *, Tex *, s32, s32, QW *, f32);
void func_002492d0(void *, f32, f32, f32, f32);
s32 func_002492e8(void *, s32);
QW *func_0023fad0(Obj *, QW *);
void func_00240b68(Obj *);
QW *func_0023ee80(Obj *, QW *);
QW *func_0023dfc0(Obj *, QW *);
QW *func_00240118(Obj *, QW *);
QW *func_002403d0(Obj *, QW *);
QW *func_0023f920(Obj *, QW *);
QW *func_0023f688(Obj *, QW *);
QW *func_0023dfd8(Obj *, QW *);
QW *func_00240ae0(void *, s32, s32, QW *, f32);
QW *func_00237008(s32, u64, QW *);
void func_00236fd8(QW *, QW *);
void func_00237018(void *, s32, s32);

QW *func_0023fb90(Obj *o, QW *r) {
    s32 a[4];
    s32 b[2];
    Spr c;
    s32 n, m, i, k;
    f32 t, w;
    n = o->unk4->unk6C->unkBE;
    if (n > 600) n = 600;
    if (n < 271) return r;
    if (o->unk0 != 0) return r;
    func_0023d528(o, a, b);
    m = n - 270;
    i = m / 30;
    if (i > 0) {
        k = i;
        do {
            k--;
            r = func_0023d700(o->unk50, o->unk70, b[0], b[1], r, o->unkA1C);
            b[0] -= 26;
        } while (k);
    }
    k = m % 30;
    if (k == 0) return r;
    t = (f32)k / 30.0f;
    c = *o->unk50;
    w = c.v[2];
    c.v[2] = w * t;
    c.v[4] = c.v[4] + (c.v[6] - c.v[4]) * t;
    c.v[0] = c.v[0] + (1.0f - t) * w;
    return func_0023d700(&c, o->unk70, b[0], b[1], r, o->unkA1C);
}

QW *func_0023fd58(Obj *o, QW *r) {
    s32 n = o->unk4->unk6C->unkBE;
    f32 a, b;
    s32 p;
    a = n * 0.017453289f;
    if (a > 4.71238803863525390625f) a = 4.71238803863525390625f;
    p = o->unk9FC;
    b = p * 0.017453289f;
    if (b > 4.71238803863525390625f) b = 4.71238803863525390625f;
    if (n < p) {
        o->unkA00 = a;
        o->unkA04 = b;
        func_002492d0(o->unkA08, 128.0f, -12.799999237060546875f, 0.0f, 128.0f);
    } else if (p < n) {
        o->unkA00 = b;
        o->unkA04 = a;
        func_002492d0(o->unkA08, 0.0f, 12.799999237060546875f, 0.0f, 128.0f);
    }
    if (func_002492e8(o->unkA08, D_002BBDFC) == 1) {
        o->unkA00 = o->unkA04;
    }
    r = func_0023fb90(o, func_0023fad0(o, r));
    o->unk9FC = n;
    return r;
}

QW *func_0023ff38(Obj *o, QW *r) {
    s32 a[4];
    s32 b[2];
    Spr c;
    s32 m, i, n, k;
    f32 t;
    if (*o->unkA88 * 0.00017453289547120220959f <= 4.71238803863525390625f) return r;
    func_0023d528(o, a, b);
    m = *o->unkA88 - 27000.0f;
    n = m / 3000;
    for (i = 0; i < n; i++) {
        r = func_0023d700(o->unk48, o->unk70, b[0], b[1], r, o->unkA1C);
        b[0] -= 26;
    }
    k = m % 3000;
    if (k == 0) return r;
    t = (f32)k / 3000.0f;
    b[0] = b[0] + (1.0f - t) * 26.0f;
    c = *o->unk48;
    c.v[2] = c.v[2] * (t + 0.0625f);
    return func_0023d700(&c, o->unk70, b[0], b[1], r, o->unkA1C);
}

QW *func_002401f0(Obj *o, QW *r) {
    s32 a[4];
    s32 b[2];
    Spr c;
    s32 m, i, n, k;
    f32 t;
    if (*o->unkA8C * 0.00017453289547120220959f <= 4.71238803863525390625f) return r;
    func_0023d528(o, a, b);
    m = *o->unkA8C - 27000.0f;
    n = m / 3000;
    for (i = 0; i < n; i++) {
        r = func_0023d700(o->unk4C, o->unk70, b[0], b[1], r, o->unkA1C);
        b[0] -= 26;
    }
    k = m % 3000;
    if (k == 0) return r;
    t = (f32)k / 3000.0f;
    b[0] = b[0] + (1.0f - t) * 26.0f;
    c = *o->unk4C;
    c.v[2] = c.v[2] * (t + 0.0625f);
    return func_0023d700(&c, o->unk70, b[0], b[1], r, o->unkA1C);
}

void func_002410b8(Obj *o) {
    s32 a[4];
    s32 b[2];
    QW **bp = &D_00651D64;
    QW **pp = &D_00651D60;
    QW *q;
    *bp = (QW *)D_00351E10;
    *pp = (QW *)(D_00351E10 + 0x10);
    func_00240b68(o);
    *pp = func_0023ee80(o, *pp);
    *pp = func_0023dfc0(o, *pp);
    (*pp)->lo = 0x1000000000008001;
    (*pp)->hi = 14;
    (*pp)++;
    (*pp)->lo = o->unk70->unk18;
    (*pp)->hi = 6;
    (*pp)++;
    *pp = func_00240118(o, *pp);
    if (o->unkA8C) *pp = func_002403d0(o, *pp);
    q = *pp;
    *pp = q + 1;
    *pp = func_00237008(0x42, 0x8000000048, q + 1);
    func_00236fd8(q, *pp);
    func_0023d528(o, a, b);
    q = func_00240ae0(o->unkAA0, b[0], b[1], *pp, o->unkA1C);
    *pp = q + 1;
    *pp = func_00237008(0x42, 0x8000000044, q + 1);
    func_00236fd8(q, *pp);
    func_00237018(*bp, *pp - *bp, 1);
}

/* func_0023d698 and func_002414a8 (moved here) and func_002410b8 must be defined above func_002416a8 for it to match. */
extern u8 D_00426970[];
extern u8 D_0042B790[];
extern u8 D_004305B0[];
void func_00249a48(void *, s32);

void func_0023d698(s32 a) {
    if (a == 0) {
        func_00249a48(D_00426970, 1);
    } else if (a == 1) {
        func_00249a48(D_0042B790, 1);
    } else {
        func_00249a48(D_004305B0, 1);
    }
}

typedef struct { u8 pad[0xA1C]; f32 unkA1C; f32 unkA20; u8 padA24[0xD00 - 0xA24]; } Slot1C;
extern Slot1C D_00651E70[];

void func_002414a8(s32 i, s32 a) {
    Slot1C *e = &D_00651E70[i];
    switch (a) {
    case 0:
        e->unkA1C = 1.0f;
        e->unkA20 = -0.0999999940395355224609375f;
        break;
    case 1:
        e->unkA20 = 0.0999999940395355224609375f;
        e->unkA1C = 0.0f;
        break;
    case 2:
        e->unkA1C = 1.0f;
        e->unkA20 = 0.0f;
        break;
    case 3:
        e->unkA20 = 0.0f;
        e->unkA1C = 0.0f;
        break;
    }
}

typedef struct { u8 pad[0x6C]; void *unk6C; } OwA;
typedef struct {
    s32 unk0;
    OwA *unk4;
    u8 pad8[0x80 - 8];
    s32 unk80[4];
    u8 pad90[0xA1C - 0x90];
    f32 unkA1C;
    u8 padA20[0xA2C - 0xA20];
    s32 unkA2C;
    u8 padA30[0xA88 - 0xA30];
    f32 *unkA88;
    f32 *unkA8C;
    u8 padA90[0xD00 - 0xA90];
} EntA;
typedef struct {
    s32 used[8];
    EntA ent[5];
    s32 unk4120;
    s32 unk4124;
} G51E50;
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0 - 0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } QA;
extern G51E50 D_00651E50;
QA D_00651C00 ALIGNED(64);
typedef struct { u32 b0:3; u32 b3:1; u32 rest:28; } F2C5958;
extern F2C5958 D_002C5958;
void func_00241560(void);
void func_00241a38(s32);
void func_0023d1a0(void);
void func_00240fa0(EntA *);
void func_002415f0(EntA *);
void func_00249950(f32 *, f32, f32);
void func_00242c08(OwA *, s32, s32 *, f32);
void func_00241260(EntA *);
void func_00249820(s32 *, s32 *);

s32 func_002416a8(void) {
    s32 t[4];
    s32 i;
    f32 a, b;
    EntA *e;
    func_00241560();
    if (D_00651E50.unk4124 == 0 && D_002C5958.b3 == 1) {
        func_002414a8(0, 3);
        func_002414a8(1, 3);
        func_002414a8(2, 3);
    } else if (D_00651E50.unk4124 == 1 && !D_002C5958.b3) {
        func_002414a8(0, 2);
        func_002414a8(1, 2);
        func_002414a8(2, 2);
        func_00241a38(0);
        func_00241a38(1);
        func_00241a38(2);
    }
    D_00651E50.unk4124 = D_002C5958.b3;
    if (D_00651E50.unk4124) {
        func_0023d1a0();
        return 0;
    }
    func_002370c8(&D_00651C00);
    D_00651C00.unkE0 = 5;
    D_00651C00.unk60 = 0x30003;
    func_00237018(&D_00651C00, 22, 1);
    for (i = 0; i < 5; i++) {
        if (D_00651E50.used[i] == 0) continue;
        e = &D_00651E50.ent[i];
        if (e->unk0 == 4) {
            func_0023d698(0);
            func_00240fa0(e);
            func_002415f0(e);
        } else if (e->unk0 == 3) {
            a = *e->unkA88;
            func_00249950(e->unkA88, 0.0f, 65000.0f);
            if (e->unkA8C) {
                b = *e->unkA8C;
                func_00249950(e->unkA8C, 0.0f, 65000.0f);
            }
            func_0023d698(1);
            func_002410b8((Obj *)e);
            func_00242c08(e->unk4, 0, e->unk80, e->unkA1C);
            *e->unkA88 = a;
            if (e->unkA8C) *e->unkA8C = b;
        } else {
            func_0023d698(0);
            func_00241260(e);
            if (e->unk0 == 0) {
                func_00242c08(e->unk4, e->unkA2C, e->unk80, e->unkA1C);
            } else {
                func_00249820(t, e->unk80);
                t[1]--;
                func_00242c08(e->unk4, 0, t, e->unkA1C);
            }
        }
    }
    return 0;
}

typedef struct { s32 x, y, z, w; } V4;
typedef struct { s32 w, h; u8 pad[8]; u8 clut[0x400]; u8 img[1]; } Img;
typedef struct { u8 pad[0x140]; Img *unk140; } ObG;
V4 *func_00122048(s32, s32);
V4 *func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, s32, void *, V4 *);
V4 *func_0011fb38(s32, u64, V4 *);
void func_0011fb78(V4 *, u64, V4 *);
void FlushCache(s32);
s32 func_00266c08(s32);
void func_00266f38(s32, u32);
void sceGsSyncPath(s32, s32);
void func_001220b8(V4 *);

void func_00242ef8(ObG *o, s32 n, s32 a2, s32 *pos, s32 *col) {
    Img *im = o->unk140;
    V4 *buf, *p, *q;
    s32 d;
    if (im == NULL) return;
    q = func_00122048(0, 16);
    buf = q;
    q = func_0011fbb0(0x3C00, 0, 0, 0, 0, 16, 16, 64, im->clut, q);
    q = func_0011fbb0(0x3A00, 4, 19, 0, 0, im->w, im->h, im->w * im->h / 16, im->img, q);
    p = q;
    q++;
    *(u64 *)&q->x = 0x80AB400000008001;
    *(u64 *)&q->z = 0x53531EEE;
    q = func_0011fb38(63, 0, q + 1);
    q = func_0011fb38(6, 0x20078005A1313A00, q);
    q = func_0011fb38(20, 0, q);
    q->x = col[0];
    q->y = col[1];
    q->z = col[2];
    q->w = col[3];
    d = n / 2 * 16;
    q++;
    q->x = 0;
    q->y = 0;
    q++;
    q->x = pos[0] - d;
    q->y = pos[1] - d;
    q->w = 0x8000;
    q->z = 0;
    q++;
    q->x = im->h * 16;
    q->y = im->h * 16;
    q++;
    q->x = pos[0] + d;
    q->y = pos[1] + d;
    q->z = 0;
    q->w = 0;
    func_0011fb78(p, 7, q + 1);
    FlushCache(0);
    func_00266f38(func_00266c08(2), ((u32)buf & 0x0FFFFFFF) | 0x80000000);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}

#include "data/types/nostrict_text_00240000_h75.h"
extern Tbl D_00656510;

typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0 - 0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Pk;
Pk D_006562C0 ALIGNED(64);
extern QW *D_00656420; /* src/data/bss_0065.c: s32 D_00656420 */
QW *D_00656424 ALIGNED(4);
void func_002370c8(void *);
void func_00237018(void *, s32, s32);
void func_00244188(Ent *);

s32 func_00244298(void) {
    s32 i, j, n;
    s32 x;
    s32 left;
    s32 px;
    s32 py;
    Ent *e;
    px = 16;
    py = 16;
    x = 200;
    left = 16;
    D_00656510.frame++;
    func_002370c8(&D_006562C0);
    D_006562C0.unkE0 = 5;
    D_006562C0.unk60 = 0x30003;
    func_00237018(&D_006562C0, 22, 1);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < D_00656510.cnt[i]; j++) {
            e = &D_00656510.e[i][j];
            D_00656424 = (QW *)D_00351E10;
            D_00656420 = (QW *)(D_00351E10 + 0x10);
            if (e->unk0 == 0) continue;
            n = e->unk18;
            if (left < n + 1) {
                px = x + 16;
                x += 200;
                py = 16;
                left = 16;
            }
            left = left - n - 1;
            e->unk14 = py;
            e->unk10 = px;
            py = py + n * 22 + 22;
            func_00244188(e);
            func_00237018(D_00656424, D_00656420 - D_00656424, 1);
        }
    }
    return 0;
}

extern u8 D_00458560[];
extern u8 D_00459C50[];
extern u8 D_00459C68[];
extern u8 D_00459C78[];
extern u8 D_00459C98[];
void *memset(void *, s32, u32);
void func_0024aac8(void *);
void func_0024af40(void *, void *, void *);
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
s32 func_00244298(void);

void func_00244500(void) {
    s32 i, j;
    Ent *e;
    memset(&D_00656510, 0, sizeof(Tbl));
    func_0024aac8(D_00458560);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 5; j++) {
            e = &D_00656510.e[i][j];
            func_0024af40(D_00459C50, e->unk30, D_00458560);
            func_0024af40(D_00459C68, e->unk330, D_00458560);
            func_0024af40(D_00459C78, e->unk4B0, D_00458560);
            func_0024af40(D_00459C98, e->unk930, D_00458560);
        }
    }
    if (func_0011ef38(func_00244298) == 0) func_0011ef10(0x29811, func_00244298);
}

extern QW *D_006691D0; /* src/data/bss_0066.c: Q4 *D_006691D0 */
extern QW *D_006691D4; /* src/data/bss_0066.c: Q4 *D_006691D4 */
typedef struct { s32 v[4]; } C4;
typedef struct { s32 x0, y0, x1, y1, u0, v0, u1, v1; C4 c[4]; u8 pad60[0x40]; u64 unkA0; } Spr2;
extern Spr2 D_006693F0;
extern u64 D_00491820;
extern u64 D_00669490;
typedef struct { u8 pad[0x30]; } Fnt;
extern Fnt D_00431D50[];
typedef struct { s32 unk0; s32 unk4; u8 pad8[0x10]; s32 unk18; } Wk;
typedef struct { u8 pad[4]; Wk *unk4; } Ow;
void func_00247cc8(s32);
void func_002474e8(Spr2 *, Fnt *, s32, s32, f32);
void func_00237018(void *, s32, s32);

void func_00248238(Ow *o) {
    Wk *w = o->unk4;
    s32 i;
    if (w->unk4 == 0 && w->unk18 == 0) return;
    D_006691D4 = (QW *)D_00351E10;
    D_006691D0 = (QW *)(D_00351E10 + 0x10);
    func_00247cc8(w->unk0);
    D_006693F0.x0 = 12;
    D_006693F0.y0 = 15;
    D_006693F0.x1 = 64;
    D_006693F0.y1 = 64;
    D_006693F0.u0 = 0;
    D_006693F0.v0 = 0;
    D_006693F0.u1 = 63;
    D_006693F0.v1 = 63;
    for (i = 0; i < 4; i++) {
        D_006693F0.c[i].v[0] = 128;
        D_006693F0.c[i].v[1] = 128;
        D_006693F0.c[i].v[2] = 128;
        D_006693F0.c[i].v[3] = 128;
    }
    D_00669490 = D_00491820;
    func_002474e8((Spr2 *)((u8 *)&D_00669490 - 0xA0), &D_00431D50[w->unk0], 0, 0, 1.0f);
    func_00237018(D_006691D4, D_006691D0 - D_006691D4, 1);
}

extern u8 D_00669350[];
extern u8 D_004656A0[];
extern u8 D_00465FD0[];
extern u8 D_00466180[];
extern u8 D_004667B0[];
extern u8 D_00466DE0[];
extern u8 D_00467350[];
extern u8 D_00467388[];
extern u8 D_00467398[];
extern u8 D_004673C0[];
extern u8 D_004673E8[];
extern u8 D_00669358[];
extern u8 D_00669388[]; /* src/data/bss_0066.c: s32 D_00669388[2] */
extern u8 D_00669390[]; /* src/data/bss_0066.c: s32 D_00669390[8] */
extern u8 D_006693B0[]; /* src/data/bss_0066.c: s32 D_006693B0[8] */
extern u8 D_006693D0[];
u64 D_006692D8 ALIGNED(8);
u64 D_00669308 ALIGNED(8);
u64 D_00669338 ALIGNED(8);
void *memset(void *, s32, u32);
void func_0024aac8(void *);
void func_0024afc0(void *, void *, void *);
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
void func_00248380(void);

void func_00248400(void) {
    memset(D_00669350, 0, 8);
    func_0024aac8(D_004656A0);
    func_0024aac8(D_00465FD0);
    func_0024aac8(D_00466180);
    func_0024aac8(D_004667B0);
    func_0024aac8(D_00466DE0);
    func_0024afc0(D_00467350, D_00669358, D_004656A0);
    func_0024afc0(D_00467388, D_00669388, D_00465FD0);
    func_0024afc0(D_00467398, D_00669390, D_00466180);
    func_0024afc0(D_004673C0, D_006693B0, D_004667B0);
    func_0024afc0(D_004673E8, D_006693D0, D_00466DE0);
    D_006692D8 = 0x0007400621413600;
    D_00669308 = 0x0207400621413600;
    D_00669338 = 0x0607400621413600;
    if (func_0011ef38(func_00248380) == 0) func_0011ef10(0x28489, func_00248380);
}

/* needs make: uses rodata */
typedef struct { u8 pad[0x130]; C130 *unk130; } Chr2;
extern u8 D_00459CA0[];
extern u8 D_00459CB0[];
extern u8 D_00459CC0[];
extern u8 D_00459CD0[];
extern u8 D_00459CE0[];
extern u8 D_00459CF0[];
extern u8 D_00459D00[];
extern u8 D_00459D10[];
s32 func_0013c318(u16);
s32 func_00147808(s32);

void func_00244670(Chr2 *o, s32 a, s32 b) {
    s32 g = -1;
    s32 k, f, n;
    Ent *e;
    k = func_0013c318(o->unk130->unk4C);
    switch (k) {
    case 0: g = 0; break;
    case 1: g = 1; break;
    case 2: g = 2; break;
    }
    f = a != 0;
    if (b) f++;
    if (D_00656510.stamp[g] != D_00656510.frame) D_00656510.cnt[g] = 0;
    if (D_00656510.cnt[g] == 5) return;
    D_00656510.stamp[g] = D_00656510.frame;
    e = &D_00656510.e[g][D_00656510.cnt[g]];
    D_00656510.cnt[g]++;
    e->unk8 = k;
    e->unk18 = f;
    e->unk1C = a;
    e->unk20 = b;
    e->unk9F0 = 1.0f;
    e->unk0 = 1;
    e->unkC = 0;
    switch (o->unk130->unk4C) {
    case 0: e->unk9F4 = D_00459CA0; e->unk9F8 = D_00459CE0; break;
    case 1: e->unk9F4 = D_00459CB0; e->unk9F8 = D_00459CF0; break;
    case 2: e->unk9F4 = D_00459CC0; e->unk9F8 = D_00459D00; break;
    default: e->unk9F4 = D_00459CD0; e->unk9F8 = D_00459D10; break;
    }
    switch (o->unk130->unk4C) {
    case 0: n = 295; break;
    case 1: n = 296; break;
    case 2: n = 297; break;
    case 3: n = 298; break;
    case 4: n = 299; break;
    case 5: n = 300; break;
    case 6: n = 301; break;
    case 7: n = 302; break;
    case 8: n = 303; break;
    case 9: n = 304; break;
    default: return;
    }
    e->unk24 = func_00147808(n);
}

typedef struct { u32 unk0; s32 unk4; s32 unk8; u8 padC[8]; void *unk14; } St;
extern St D_00662540; /* src/data/bss_0066.c: Hud D_00662540 */
extern u8 D_00662300[];
s32 func_001ef7a0(void);
s32 func_00122ff8(void *);
s32 func_001375d8(void *);
void func_00244b00(void);
void func_00244be0(s32, s32, s32);
s32 func_0024a1c0(void *);
void func_00244d00(s32, s32);

void func_00244f28(void) {
    St *s = &D_00662540;
    s32 b = 0;
    s32 a = 0;
    switch (s->unk0) {
    case 0:
        return;
    case 1:
        s->unk0++;
        a = 1;
        break;
    case 3:
        if (++s->unk8 < 61) break;
    case 2:
        s->unk0++;
        break;
    case 4:
        s->unk0++;
        b = 1;
        s->unk4 = func_001ef7a0();
        break;
    case 5:
        if (func_0024a1c0(D_00662300) & 4) s->unk0++;
        break;
    case 6:
        s->unk0 = 0;
        break;
    }
    if (s->unk14 == NULL) return;
    if (func_00122ff8(s->unk14) == 0) return;
    if (func_001375d8(s->unk14)) {
        func_00244b00();
        return;
    }
    func_00244d00(a, b);
    if (s->unk4 > 99999) s->unk4 = 99999;
    func_00244be0(s->unk4, 25, 238);
}

typedef struct { u8 pad[0x24]; s32 unk24; s32 unk28; s32 unk2C; u8 pad30[0x14]; s32 unk44; s32 unk48; s32 unk4C; s32 unk50; } Clk;
extern void *D_00467408;
s32 sprintf(char *, const char *, ...);
void func_002475d0(s32, s32, s8 *, f32, char *, void *);

void func_00247930(Clk *c) {
    s8 col[16];
    char buf[16];
    s32 x, y;
    col[0] = -27;
    x = c->unk24;
    x = c->unk2C ? x + 103 : x + 93;
    col[1] = 78;
    col[2] = 25;
    y = c->unk28 + 43;
    if (c->unk2C) {
        sprintf(buf, "%02d", c->unk50);
        func_002475d0(x, y, col, 0.7999999523162842f, buf, D_00467408);
        x += 22;
        func_002475d0(x, y, col, 0.7999999523162842f, ":", D_00467408);
        x += 11;
    }
    sprintf(buf, "%02d", c->unk4C);
    func_002475d0(x, y, col, 0.7999999523162842f, buf, D_00467408);
    x += 22;
    func_002475d0(x, y, col, 0.7999999523162842f, "'", D_00467408);
    x += 11;
    sprintf(buf, "%02d", c->unk48);
    func_002475d0(x, y, col, 0.7999999523162842f, buf, D_00467408);
    x += 22;
    func_002475d0(x, y, col, 0.7999999523162842f, "'", D_00467408);
    x += 5;
    func_002475d0(x, y, col, 0.7999999523162842f, "'", D_00467408);
    x += 9;
    sprintf(buf, "%02d", c->unk44);
    func_002475d0(x, y, col, 0.7999999523162842f, buf, D_00467408);
}
#include "data/data_0045.h"
#include "data/data_0046.h"
#include "data/data_0049.h"
#include "data/pieces/D_002BBDFC.h"
