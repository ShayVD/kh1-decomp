/* The actors: the actor lists (func_001230a0 walks them, NULL starts and
 * ends; func_00122ff8 whether one is live, func_00123488 finds one by id,
 * its kind in the id's byte 2), the player D_002E26A0, small actor tests
 * (func_00123158, func_00123368 ...), an actor's name (func_00122dc8,
 * sprintf), the actor records D_002C64A0 (func_00123810 clears them), the
 * room's actors set up (func_00124218) and placed (func_001238d0,
 * func_00123b40), the reset func_00124b90. Flag mode: nostrict (the other
 * modes are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 54"). */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004E.h"
#include "data/bss_004F.h"
#include "data/types/nostrict_text_00110000_s6_04_p.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002C58B0.h"
#include "data/types/nostrict_text_00110000_s6_04.h"
#include "data/pieces/D_002C5C48.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_002C5910.h"
#include "data/types/nostrict_text_00110000_h53.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00304C70.h"

/* func_00122f58 (from hand/nostrict/text_00110000_s6_04.c). */
typedef struct { u8 pad[0x44]; f32 x44; u8 pad48[0x16]; u8 x5e; u8 x5f; } Sub130;
typedef struct { u8 pad[0x130]; Sub130 *p; } Obj130;
void func_00122f58(Obj130 *o, f32 a, f32 b, f32 c) {
    o->p->x44 = a;
    o->p->x5e = b;
    o->p->x5f = c;
}

/* func_00123368 (from hand/nostrict/text_00110000_s6_04.c). */
typedef struct { u8 pad[6]; volatile u8 x6; } Sub134;
typedef struct { u64 x0; u8 pad8[0x12c]; Sub134 *x134; u8 pad138[0x270]; u32 x3a8; } Ent3a8;
s32 func_00123368(Ent3a8 *e) {
    Sub134 *s = e->x134;
    s32 i;
    if (s == 0 || s->x6 == 0 || ((u8 *)e)[6] == 2 || (e->x0 & 0x8048) != 0x8000) return 0;
    for (i = 0; i < s->x6; i++) {
        if (!(e->x3a8 & (1 << i))) return 1;
    }
    return 0;
}

/* func_00123b40 (from hand/nostrict/text_00110000_h53.c). */
typedef struct {
    u8 pad0[0x1c];
    f32 p[4];
    f32 q[3];
    f32 r[3];
    u8 pad44[0x10];
    s8 x54;
    u8 pad55[3];
    u8 x58;
    u8 pad59;
    u8 x5a;
} Info3b;
typedef struct Actor_23b40 {
    u8 pad0[4];
    s32 x4;
    u8 pad8[0x38];
    f32 x40[3];
    u8 pad4c[0xe4];
    Info3b *info;
} Obj3b;
void func_00113138(V53 *);
void func_00113270(V53 *);
void func_001133a0(V53 *);
void func_00123ab8(s32, f32 *);
void func_0014eab0(Obj3b *, V53 *);
void func_0014eb60(Obj3b *, V53 *);
void func_0014e668(V53 *, s32, V53 *, f32, f32);
float atan2f(float, float);
void func_00123b40(Obj3b *o, V53 *out) {
    Info3b *in = o->info;
    f32 t[3];
    V53 d;
    s32 k;
    switch (in->x54) {
    case 0:
        func_00113138(out);
        return;
    case 1:
        if (D_002E26A0[1] == o) {
            func_00113270(out);
        } else {
            func_001133a0(out);
        }
        return;
    }
    k = ((u8 *)o)[6];
    if (k < 6) {
        if (k >= 4) {
            out->x = in->p[0];
            out->y = in->p[1];
            out->z = in->p[2];
            out->w = 0.0f;
            o->x40[0] = in->q[0];
            o->x40[1] = in->q[1];
            o->x40[2] = in->q[2];
            t[0] = in->r[0];
            t[1] = in->r[1];
            t[2] = in->r[2];
            func_00123ab8(o->x4, t);
            return;
        }
    }
    out->x = in->p[0];
    out->y = in->p[1];
    out->z = in->p[2];
    out->w = in->p[3];
    switch (in->x5a) {
    case 2:
        if (D_002E26A0[0] == 0) return;
        func_0014eab0(o, out);
        PlatVu0SubVector(&d, (V53 *)((u8 *)D_002E26A0[0] + 16), out);
        out->w = atan2f(d.x, d.z);
        break;
    case 3:
        if (D_002E26A0[0] == 0) return;
        func_0014eb60(o, out);
        PlatVu0SubVector(&d, (V53 *)((u8 *)D_002E26A0[0] + 16), out);
        out->w = atan2f(d.x, d.z);
        break;
    case 4:
        PlatVu0CopyVector(&d, out);
        func_0014e668(&d, o->info->x58, out, 0.0f, 500.0f);
        break;
    }
}

/* func_00123d48 (from hand/nostrict/text_00110000_h53.c). */
typedef struct { u8 pad[0x4c]; u16 x4c; } Info3d;
typedef struct { u8 pad[0xbd]; u8 xbd; } Sub3d;
typedef struct { u8 pad[0x154]; s32 x154; u8 pad158[0x28]; } W3d;
typedef struct { u8 pad[0x10]; s32 x10; } R3d;
typedef struct {
    u64 lo : 37;
    u64 k : 2;
    u64 hi : 25;
} F3d;
typedef struct Obj3d {
    u8 pad0[6];
    u8 x6;
    u8 pad7[0x65];
    Sub3d *x6c;
    u8 pad70[0xc0];
    Info3d *info;
    u8 pad134[0x14];
    W3d *x148;
    s32 x14c;
    u8 pad150[0x7c];
    s32 x1cc;
    u8 pad1d0[0x1a0];
    F3d f;
} Obj3d;
W3d D_004F71D0[0x3] ALIGNED(16);  /* moved from hand/nostrict/text_00110000_h53.c (session 54) */
extern s32 D_002BC130;
extern s32 D_002BC128;
extern s32 D_002BC134;
s32 func_001499a0(void);
u32 func_0013c318(u32);
void func_00141e68(Obj3d *);
void func_00153d88(Obj3d *);
void func_001358b8(void *, s32);
void func_00241c60(Obj3d *, u32);
R3d *func_00157818(Obj3d *, s32);
void func_00123d48(Obj3d *o) {
    u32 n, k;
    W3d *w;
    o->x14c = func_001499a0();
    n = func_0013c318(o->info->x4c);
    k = n;
    if (n >= 3) return;
    if (o->x6 != 3) return;
    if ((s32)n > 0) {
        k = (D_002E26A0[1] == 0) ? 1 : 2;
    }
    w = &D_004F71D0[k];
    D_002E26A0[k] = (void *)o; /* o: this file's Obj3d view */
    o->x148 = w;
    w->x154 = 0;
    o->x1cc = 1;
    o->f.k = 1;
    o->x6c->xbd = k;
    func_00141e68(o);
    func_00153d88(o);
    D_00304BE8->x83e |= 1 << o->info->x4c;
    func_001358b8(o, 12);
    func_00241c60(o, n);
    if (D_002BC128 == 16 && ((D_002BC130 == 37 && D_002BC134 == 13 && o->info->x4c == 2) ||
                             (D_002BC128 == 16 && D_002BC130 == 38 && D_002BC134 == 13 && o->info->x4c == 1))) {
        func_00157818(o, 0)->x10 = 0x3000;
    }
}

/* func_00123f28 (from hand/nostrict/text_00110000_h30.c). */
typedef struct { u8 pad0[12]; s32 xC; u8 pad10[60]; u16 x4C; u8 pad4e[6]; s8 kind; u8 pad55[4]; u8 x59; } Info123;
typedef union {
    u64 v;
    struct { u32 lo0; u32 x0 : 1; u32 b33 : 1; u32 x2 : 14; u32 b48 : 1; u32 x17 : 5; u32 b54 : 1; u32 x23 : 9; } b;
    struct { u64 lo : 33; u64 b33 : 1; u64 m : 14; u64 b48 : 1; u64 m2 : 5; u64 b54 : 1; u64 hi : 9; } c;
} ObjFlags;
typedef struct Actor_23f28 {
    u32 x0;
    u8 pad4[300];
    Info123 *info;
    u8 pad134[4];
    s32 x138;
    u8 pad13c[8];
    s32 x144;
    u8 pad148[552];
    ObjFlags fl;
    u8 pad378[40];
    s32 x3a0;
} Obj123;
void func_00170400(Obj123 *);
s32 func_00132008(Obj123 *);
s32 func_0012b888(s32);
void func_0012ba30(s32, Obj123 **, s32);
void func_00123f28(Obj123 *o) {
    Info123 *info = o->info;
    s8 k = info->kind;
    if (k >= 0) {
        switch (k) {
        case 1:
            func_00170400(o);
            break;
        case 6:
            o->x3a0 = func_00132008(o);
            break;
        case 2:
        case 5:
            o->fl.c.b48 = 1;
            break;
        }
    } else {
        o->x138 = info->xC;
        o->fl.c.b48 = 1;
    }
    if (o->fl.b.b48) {
        if (o->x138 == 0) {
            o->fl.c.b48 = 0;
            return;
        }
        o->x144 = func_0012b888(o->x138);
        func_0012ba30(o->x144, &o, 4);
    }
}

/* func_00124060 (from hand/nostrict/text_00110000_h53.c). */
#define FLD(T, p, off) (*(T *)((u8 *)(p) + (off)))
void func_00145240(void *);
void func_00176310(void *);
s32 func_0014f5c8(void *);
void func_0014f658(void *, s32);
void *func_00134928(void *);
void func_001350d0(void *);
void func_00137448(void *);
void func_001238d0(void *, V53 *);
typedef struct { u64 lo : 4; u64 b4 : 1; u64 hi : 59; } F160;
void func_00124060(u8 *o, V53 *pos) {
    void *v;
    if (FLD(u8 *, o, 0x148)) {
        FLD(s32, FLD(u8 *, o, 0x148), 0x90) = 0xffff;
        if (0.0f < FLD(f32, FLD(u8 *, o, 0x148), 0xe0)) {
            FLD(f32, FLD(u8 *, FLD(u8 *, o, 0x134), 0x10), 0xc) = FLD(f32, FLD(u8 *, o, 0x148), 0xe0);
            FLD(f32, FLD(u8 *, o, 0x148), 0xe0) = 0.0f;
        }
        func_00145240(o);
        PlatVu0CopyVector(FLD(u8 *, o, 0x148) + 0x160, &D_002C58B0);
        func_001358b8(o, 12);
    }
    if (FLD(u8 *, o, 0x14c)) {
        if (FLD(void *, FLD(u8 *, o, 0x14c), 0x1c)) {
            func_00176310(FLD(void *, FLD(u8 *, o, 0x14c), 0x1c));
            FLD(void *, FLD(u8 *, o, 0x14c), 0x1c) = 0;
        }
        FLD(s32, FLD(u8 *, o, 0x14c), 0x24) = -1;
    }
    if (!func_0014f5c8(o)) func_0014f658(o, 0);
    FLD(s32, o, 0x388) = 0;
    FLD(f32, o, 0x480) = 1.0f;
    FLD(u32, o, 0) = (FLD(u32, o, 0) & 0x01004083) | 0x8000;
    FLD(s32, o, 0x88) = 0;
    for (; (v = func_00134928(o)) != 0;) func_001350d0(v);
    FLD(F160, o, 0x160).b4 = 0;
    FLD(f32, o, 0x284) = 1.0f;
    FLD(f32, o, 0x458) = -1.0f;
    FLD(s32, o, 0x470) = 0;
    FLD(s32, o, 0x450) = 0;
    FLD(s32, o, 0x454) = 0;
    FLD(s32, o, 0x474) = 0;
    FLD(s32, o, 0x98) = 0;
    func_00137448(o);
    FLD(f32, o, 0x4ac) = 60.0f;
    func_001238d0(o, pos);
    PlatVu0CopyVector(o + 0x3c0, &D_002C58B0);
    PlatVu0CopyVector(o + 0x120, &D_002C58B0);
}

/* func_00124218 (from hand/nostrict/text_00110000_h30.c). */
typedef struct Actor_24218 {
    u32 x0;
    u8 pad4[300];
    Info123 *info;
    u8 pad134[4];
    s32 x138;
    u8 pad13c[8];
    s32 x144;
    u8 pad148[552];
    ObjFlags fl;
    u8 pad378[40];
    s32 x3a0;
} Obj123_24218;
typedef struct {
    u8 pad0[4];
    u32 x4;
    s32 x8;
    u8 pad0c[4];
    f32 x10;
    f32 x14;
    u8 pad18[0x4c - 0x18];
    u16 x4c;
    u8 pad4e[0x54 - 0x4e];
    s8 x54;
    s8 x55;
    s8 x56;
    s8 x57;
    u8 x58;
    u8 x59;
} C01Def;
typedef struct { u8 pad[8]; f32 x8; f32 xc; } C01Pt;
typedef struct { u8 pad[4]; u8 x4; u8 pad5; u8 x6; u8 pad7[5]; f32 xc; C01Pt *x10; } C01Ent4;
typedef struct { u8 pad[0xe0]; s32 xe0; } C01S148;
typedef struct { u8 pad[0xf]; s8 xf; u8 pad10[0xc]; s32 x1c; u8 pad20[4]; s32 x24; } C01S14c;
typedef struct { u8 pad[0xbd]; u8 xbd; } C01Fx;
typedef struct {
    u32 x0;
    union { s32 id; struct { u16 lo; u8 b6; u8 b7; } s; } u4;
    s32 x8;
    s32 xc;
    u8 pad010[0x40 - 0x10];
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4c;
    u8 pad050[0x60 - 0x50];
    f32 x60;
    s32 x64;
    u8 pad068[0x6c - 0x68];
    void *x6c;
    s32 x70;
    u8 pad074[0x7c - 0x74];
    s32 x7c;
    s32 x80;
    u8 pad084[0x8c - 0x84];
    s32 x8c;
    u8 pad090[0x98 - 0x90];
    s32 x98;
    s32 x9c;
    f32 xa0;
    f32 xa4;
    f32 xa8;
    f32 xac;
    s32 xb0;
    u8 pad0b4[0x130 - 0xb4];
    C01Def *x130;
    C01Ent4 *x134;
    u8 pad138[0x13c - 0x138];
    s32 x13c;
    s32 x140;
    s32 x144;
    C01S148 *x148;
    C01S14c *x14c;
    u8 pad150[0x160 - 0x150];
    s32 x160;
    s32 x164;
    u8 pad168[0x1cc - 0x168];
    s32 x1cc;
    s32 x1d0;
    u8 pad1d4[0x1d8 - 0x1d4];
    s32 x1d8;
    u8 pad1dc[0x2c0 - 0x1dc];
    f32 x2c0;
    f32 x2c4;
    u8 pad2c8[0x350 - 0x2c8];
    s32 x350;
    s32 x354;
    s32 x358;
    s32 x35c;
    u8 pad360[0x370 - 0x360];
    union { u64 x; u8 c[8]; u16 h[4]; struct { u64 lo : 40; u64 f40 : 2; u64 m42 : 7; u64 b49 : 1; u64 hi : 14; } b; } u370;
    s32 x378;
    u8 pad37c[0x38c - 0x37c];
    s32 x38c;
    s32 x390;
    u8 pad394[0x398 - 0x394];
    s32 x398;
    u8 x39c;
    u8 x39d;
    u8 x39e;
    u8 pad39f[0x3a0 - 0x39f];
    s32 x3a0;
    s32 x3a4;
    s32 x3a8;
    s32 x3ac;
    u8 pad3b0[0x3e0 - 0x3b0];
    s32 x3e0;
    s32 x3e4;
    s16 x3e8;
    s16 x3ea;
    s32 x3ec;
    u8 pad3f0[0x400 - 0x3f0];
    s32 x400;
    s32 x404;
    s32 x408;
    u8 pad40c[0x410 - 0x40c];
    f32 x410;
    f32 x414;
    u8 pad418[0x440 - 0x418];
    s32 x440;
    u8 pad444[0x448 - 0x444];
    s32 x448;
    u8 pad44c[0x488 - 0x44c];
    s32 x488;
    u8 pad48c[0x4a0 - 0x48c];
    s32 x4a0;
    s32 x4a4;
    s32 x4a8;
    u8 pad4ac[0x4b0 - 0x4ac];
} C01Act;
extern s32 D_00350D7C;
extern s32 D_00350D80;
extern u8 D_00FE0000[];
s32 func_00131f78(s32);
C01Def *func_001320a8(s32);
s32 func_0015aac0(C01Def *);
C01Act *func_00123810(void);
void func_00123030(C01Act *, s32, s32);
C01Fx *func_00141a40(void);
void func_001323a0(C01Act *, s32);
void func_001238c0(C01Act *, f32, f32);
void func_00131438(C01Act *);
void func_00130340(C01Act *, s32, f32);
void func_001371f0(C01Act *);
void func_00138400(C01Act *);
void func_0012ba98(s32);
#define func_00123d48 ((void (*)(C01Act *)) func_00123d48)
#define func_001358b8 ((void (*)(C01Act *, s32)) func_001358b8)
#define func_00123b40 ((void (*)(C01Act *, void *)) func_00123b40)
#define func_00124060 ((void (*)(C01Act *, void *)) func_00124060)
C01Act *func_00124218(u32 id) {
    u8 buf[16];
    C01Def *d;
    C01Act *a;
    C01Ent4 *e;
    u32 f;

    if ((id >> 16 & 0xff) == 11) {
        id = func_00131f78(id & 0xffff);
        if (id == -1) return 0;
    }
    d = func_001320a8(id);
    if (D_00350D7C > 0 && D_00350D7C < D_00350D80 + d->x59) return 0;
    if (d->x54 == 16 && func_0015aac0(d)) return 0;
    D_00350D80 += d->x59;
    a = func_00123810();
    f = a->x0;
    a->u4.id = id;
    a->x130 = d;
    a->x0 = f | 0x8000;
    if (!(d->x4 & 0x100)) a->x0 = f | 0x8003;
    if (d->x4c < 10 && (D_00304BE8->m[d->x4c].sub.w34.h.x36 & 1)) a->x0 |= 0x4000;
    a->u370.x = (a->u370.x & ~(3ULL << 40)) | ((u64)(d->x4 >> 3 & 3) << 40);
    if (a->x130->x4 & 0x80) a->u370.x |= 1ULL << 47;
    a->x144 = 0;
    a->x140 = 0;
    a->x6c = (*(u8 (*)[0xe4])&D_00304C70);
    a->x13c = 0;
    a->x4a8 = 0;
    a->x488 = 0;
    a->xb0 = 0;
    a->x440 = 0;
    a->x448 = 0;
    a->x148 = 0;
    a->x14c = 0;
    a->x398 = 0;
    a->x8c = 0;
    a->x98 = 0;
    a->x4a0 = 0;
    a->x378 = 0;
    a->x70 = 0;
    a->x160 = 0;
    a->x1d8 = 0;
    a->x1cc = 0;
    func_00123030(a, 0, 0);
    a->x7c = 0;
/*P*/
    a->u370.c[3] = 0x80;
    a->u370.c[2] = 0x80;
    a->u370.c[1] = 0x80;
    a->u370.c[0] = 0x80;
    a->x3ea = 82;
    a->x80 = 0;
    a->x8 = 0;
    a->xc = 0;
    a->x3ec = 0;
    a->x3e0 = 0;
    a->x3e8 = 0;
    a->x400 = 0;
    a->x408 = 0;
    a->x3e4 = 0;
    a->x404 = 0;
    a->x134 = 0;
    a->x60 = 1.0f;
    a->x64 = 0;
    a->xac = 1.0f;
    a->xa8 = 1.0f;
    a->xa4 = 1.0f;
    a->xa0 = 1.0f;
    a->x4a4 = 0;
    a->x38c = 0;
    a->x390 = 0;
    a->x39c = 0;
    a->x39d = 0;
    a->x39e = 0;
    a->x3a0 = 0;
    a->u370.x &= ~(3ULL << 37);
/*Q*/
    switch (a->u4.s.b6) {
    case 3:
        a->u370.x |= 1ULL << 42;
        a->u370.x = (a->u370.x & ~(3ULL << 37)) | (2ULL << 37);
        a->x6c = func_00141a40();
        break;
    case 5:
    case 10:
        if (a->x130->x4 & 0x400) a->x39d |= 1;
        if (a->x130->x4 & 0x800) a->x39d |= 2;
        break;
    case 7: {
        C01Fx *fx = func_00141a40();
        a->x6c = fx;
        fx->xbd = 2;
        break;
    }
    }
    if (!d->x8) d->x8 = (s32)D_00FE0000 + (d->x55 << 18);
    func_001323a0(a, d->x8);
    func_00123d48(a);
    if (a->u4.s.b6 == 2) func_001358b8(a, 12);
    func_00123f28((Obj123_24218 *)a);
    if (a->x14c) {
        a->x14c->xf = -1;
        a->x14c->x1c = 0;
        a->x14c->x24 = -1;
    }
    if (a->x148) a->x148->xe0 = 0;
    e = a->x134;
    if (!e || e->xc == 0.0f) {
        func_001238c0(a, d->x14, d->x10);
        e = a->x134;
        if (d->x4 & 0x20) { a->u370.x |= 1ULL << 49; a->u370.x |= 3ULL << 40; }
    }
    a->x3a4 = 0;
    a->x3a8 = 0;
    a->x3ac = 0;
    if (e && e->x6) {
        a->u370.x &= ~(1ULL << 47);
        if (!((s32)(a->u370.x >> 37) & 3)) a->u370.x |= 3ULL << 37;
    }
    if (e && e->x4) {
        a->x2c4 = e->x10->x8;
        a->x2c0 = e->x10->xc;
    } else {
        a->x2c0 = a->x410;
        a->x2c4 = a->x414 * 0.5f;
    }
    a->x9c = 0;
    a->x4c = 1.0f;
    a->x48 = 1.0f;
    a->x44 = 1.0f;
    a->x40 = 1.0f;
    func_00123b40(a, buf);
    a->x350 = 128;
    a->x354 = 128;
    a->x358 = 128;
    a->x35c = 128;
    func_00124060(a, buf);
    if (a->x1d0) {
        func_00131438(a);
        a->x164 = d->x57;
        func_00130340(a, d->x57, 0.0f);
    }
    func_001371f0(a);
    func_00138400(a);
    if ((s32)(a->u370.x >> 48) & 1) func_0012ba98(a->x144);
    a->x0 &= ~0x400;
    return a;
}
#undef func_00123d48
#undef func_001358b8
#undef func_00123b40
#undef func_00124060

/* func_00124920 (from hand/nostrict/text_00110000_h30.c). */
typedef struct Actor_24920 {
    u32 x0;
    u8 pad4[300];
    Info123 *info;
    u8 pad134[4];
    s32 x138;
    u8 pad13c[8];
    s32 x144;
    u8 pad148[552];
    ObjFlags fl;
    u8 pad378[40];
    s32 x3a0;
} Obj123_24920;
void func_00124920(void) {
    s32 i;
    Obj123_24920 *o;
    for (i = 0; i < 10; i++) D_00304BE8->m[i].sub.w34.b.b16 = 0;
    for (i = 0; i < 3; i++) {
        o = D_002E26A0[i];
        if (o && (o->x0 & 0x4000)) D_00304BE8->m[o->info->x4C].sub.w34.b.b16 = 1;
    }
}

/* func_00124a28 (from hand/nostrict/text_00110000_h53.c). */
extern V53 D_002C6490;
void *func_001230a0(void *);
void func_001247e8(void *);
s32 func_001232f0(void *);
void func_00142480(V53 *, V53 *, s32, V53 *);
void func_00131500(void *);
void func_0012b9b0(void *);
#define func_00130340 ((void (*)(void *, s32, f32)) func_00130340)
void func_00124a28(void) {
    u8 *o;
    V53 v;
    for (o = 0; (o = func_001230a0(o)) != 0;) {
        switch (o[6]) {
        case 3:
            if (((s32)(FLD(u64, o, 0x370) >> 48) & 1) && !((s32)(FLD(u64, o, 0x440) >> 32) & 1)) {
                func_001247e8(o);
                break;
            }
            PlatVu0CopyVector(&v, o + 0x10);
            if (!func_0014f5c8(o) && func_001232f0(o)) {
                v.y -= FLD(f32, FLD(u8 *, FLD(u8 *, o, 0x134), 0x10), 8);
                func_00142480(&v, &D_002C6490, 0, &v);
            }
            v.w = FLD(f32, o, 0x3c);
            func_00124060(o, &v);
            func_00131500(o);
            func_00130340(o, 0, 0.0f);
            break;
        case 7:
            func_001247e8(o);
            break;
        }
        if (((s32)(FLD(u64, o, 0x370) >> 48) & 1) && FLD(void *, o, 0x144)) {
            func_0012b9b0(FLD(void *, o, 0x144));
            FLD(void *, o, 0x144) = 0;
        }
    }
}
#undef func_00130340

