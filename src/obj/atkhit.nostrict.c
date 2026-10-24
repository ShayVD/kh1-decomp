/* Attack hits: the 64 hit records D_0054C440 (func_0014a450 takes one,
 * func_0014a4a8 fills one from an attack definition, func_0014bdc0 updates
 * them all) and their mask D_0054F440, the hit timers (func_0014a0f0), a
 * follow offset (func_0014a238). Flag mode: nostrict (the other modes are in
 * the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_0035C710.h"
#include "data/bss_0053.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_00304DB0.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_003044A0.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E26A0.h"
#include "platform/math.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002E31B0.h"
#include "data/types/nostrict_text_00140000_b04.h"
#include "data/bss_0054.h"
#include "data/types/nostrict_text_00140000_h57.h"
#include "data/types/nostrict_text_00140000_h57_p.h"

/* func_0014a1b0 (from hand/nostrict/text_00140000_h56.c). */
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x1c]; f32 ang; } Tg3c;
typedef struct {
    u64 d0;
    s32 w8;
    u8 padc[4];
    f32 pos[4];
    u8 pad20[0x10];
    union { u64 d; struct { u32 lo; Tg3c *tg; } s; } u30;
    u8 pad38[0x54 - 0x38];
    u32 w54;
    u8 pad58[4];
    s32 w5c;
    u8 pad60[0x70 - 0x60];
    f32 v70[4];
    u8 pad80[0x9c - 0x80];
    u32 w9c;
    u8 padA0[0xa8 - 0xa0];
    s8 ba8;
    s8 ba9;
    s8 baa;
} Hm;
s32 func_00147ed8(s32, s32, s32, f32 *);
typedef struct { u8 pad[0x28]; s32 x28; } W8Z5c;
typedef struct { u8 pad[8]; s32 x8; u8 padc[0x5c - 0xc]; W8Z5c *x5c; } W8Z;
s32 func_00176578(s32, s32, s32, s32);
void *func_0014a1b0(Hm *m, s32 b, f32 *c) {
    W8Z *z = (W8Z *)m;
    s32 r;
    s32 res;
    if (!z->x8) return 0;
    if (z->x5c->x28 < 0) return 0;
    r = func_00176578(z->x8, b != 4 ? b : 2, 1 << z->x5c->x28, 0);
    res = 0;
    if (r >= 0) res = func_00147ed8(z->x8, r, -10000, c);
    return (void *)res;
}

/* func_0014a4a8 (from hand/nostrict/text_00140000_b04.c). */
typedef struct {
    union {
        u64 x;
        struct { u64 b0:2; u64 b2:2; u64 b4:2; u64 b6:3; u64 b9:1; u64 b10:1; u64 f11:1; u64 b12:2; u64 b14:1; u64 b15:1; u64 b16:1; u64 b17:3; u64 b20:1; u64 b21:1; u64 b22:2; u64 b24:1; u64 r:39; } b;
        struct { u32 lo; u32 hi; } w;
    } f;
    s32 x8;
    f32 xc;
    u8 pad10[0x20 - 0x10];
    s32 x20;
    f32 x24;
    f32 x28;
    s32 x2c;
    union { u64 x; struct { u64 b0:5; u64 b5:1; u64 b6:4; u64 b10:1; u64 r:53; } b; struct { s32 lo; struct Actor_4a4a8 *hi; } w; } x30;
    s32 x38_;
    f32 x3c;
    u8 pad40[0x50 - 0x40];
    f32 x50;
    u32 x54;
    s32 x58;
    void *x5c;
    s32 x60;
    s32 x64;
    u8 pad68[0x70 - 0x68];
    u8 x70[0x10];
    u8 x80[0x10];
    struct Actor_4a4a8 *x90;
    f32 x94;
    s32 x98;
    s32 x9c;
    s32 xa0;
    f32 xa4;
    u8 pada8[4];
    f32 xac;
    s32 xb0;
    s32 xb4;
    s32 xb8;
    u8 xbc[4];
} B4P;
typedef struct {
    u32 x0; u32 x4; u32 x8; u8 padc[4]; s32 x10; u8 pad14[4]; s32 x18; s32 x1c;
    u8 pad20[0x34 - 0x20]; u32 x34; s32 x38; s32 x3c;
    u8 pad40[0x54 - 0x40]; f32 x54; f32 x58; f32 x5c; u8 pad60[8]; f32 x68;
} B4D;
typedef struct { u8 pad[0x1c]; f32 x1c; f32 x20; f32 x24; f32 x28; u8 pad2c[0x48 - 0x2c]; s32 x48; s32 x4c; u8 pad50[0x68 - 0x50]; s32 x68; u8 pad6c[0xd4 - 0x6c]; f32 xd4; u8 padd8[4]; f32 xdc; } B4Prm;
typedef struct { u8 pad[0x48]; s16 x48; s16 x4a; u16 x4c; } B4C130;
typedef struct { u8 pad[0x170]; union { u64 x; struct { u32 lo; u32 b0:5; u32 b5:1; u32 r:26; } b; } x170; } B4C148;
typedef struct Actor_4a4a8 {
    s32 x0; u8 pad4[0x30 - 4]; u8 x30[0x10]; f32 x40; u8 pad44[0x68 - 0x44]; s32 x68; B4Prm *x6c;
    u8 pad70[0x88 - 0x70]; s32 x88; u8 pad8c[0xd0 - 0x8c]; f32 xd0[4][4]; u8 pad110[0x130 - 0x110];
    B4C130 *x130; u8 pad134[0x148 - 0x134]; B4C148 *x148;
    u8 pad14c[0x160 - 0x14c]; union { u64 x; struct { s32 lo; s32 hi; } w; } x160; u8 pad168[0x1cc - 0x168]; u32 x1cc;
    u8 pad1d0[0x1f0 - 0x1d0]; f32 x1f0[3]; f32 x1fc;
    u8 pad200[0x370 - 0x200];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b7:6; u32 b13:1; u32 hi:18; } b; } x370;
    u8 pad378[0x450 - 0x378]; f32 x450[4]; u8 pad460[0x470 - 0x460];
    union { u64 x; struct { struct Actor_4a4a8 *lo; u32 hi; } w; } x470;
} B4Ent;
extern u32 D_0054F440;
B4P *func_0014a450(void);
s32 func_0013c318(s32);
s32 func_002408d8(s32);
void func_001315c0(void *, s32, f32, void *);
extern B4Ent *D_002E26A0_4a4a8[3] __asm__("D_002E26A0");
#define D_002E26A0 D_002E26A0_4a4a8
B4P *func_0014a4a8(B4Ent *e, u32 m, B4D *d) {
    B4P *p = func_0014a450();
    s32 t;
    p->f.w.hi = 0;
    p->f.b.b4 = d->x34;
    p->f.b.b12 = (s32)(e->x370.x >> 37) & 3;
    p->f.b.b14 = 1;
    p->f.b.b10 = 0;
    p->f.b.b2 = 0;
    if (d->x38 & 0x10000) p->f.b.b20 = 1;
    p->f.b.b17 = d->x38 & 7;
    p->x64 = d->x3c;
    p->x54 = m;
    *(volatile u32 *)&D_0054F440 |= m;
    p->x90 = e;
    p->x30.w.hi = e;
    p->x8 = e->x68;
    p->x58 = 0xfff;
    switch (d->x0) {
    case 0:
        p->x2c = e->x6c->x4c;
        if (e->x148 && e->x148->x170.b.b5) {
            t = func_0013c318(e->x130->x4c);
            if (t >= 0 && func_002408d8(t)) p->x2c = p->x2c + (*(Cfg_308cdc **)&D_00308CDC)->xfe;
        }
        break;
    case 1: p->x2c = e->x6c->x48; break;
    case 2: p->x2c = 0; break;
    case 3: p->x2c = e->x6c->x48 * 2; break;
    case 4: p->x2c = e->x6c->x48 * 3; break;
    case 5: p->x2c = e->x6c->x48 * 5; break;
    case 6: p->x2c = D_002E26A0[0]->x6c->x4c; break;
    }
    p->x30.b.b0 = d->x8;
    p->x30.b.b6 = d->x4;
    p->x30.b.b5 = 0;
    if (d->x10 >= 0) {
        p->f.b.b0 = 1;
        p->f.b.b2 = 2;
        p->x30.b.b10 = 0;
        p->x20 = d->x10;
        p->x24 = d->x54;
        p->x28 = d->x58;
        if (e->x370.b.b13) p->xc = d->x5c * e->x40;
        else p->xc = d->x5c;
    } else {
        p->f.b.b0 = 0;
        p->f.b.b2 = 0;
        p->x30.b.b10 = 1;
        p->xc = p->x3c = d->x5c;
    }
    p->x5c = d;
    p->x60 = 0;
    p->xa0 = 0;
    p->x38_ = 0;
    func_001315c0(e, 0x8003, 0.0f, p->x70);
    PlatVu0CopyVector(p->x80, p->x70);
    p->f.b.b16 = 1;
    p->x94 = (f32)d->x18 * 0.0500000007f * e->x6c->xd4;
    p->x98 = d->x1c;
    p->x9c = 0;
    p->x50 = 0.0f;
    p->xa4 = 0.0f;
    p->xac = e->x6c->xdc;
    if (0.0f < d->x68) {
        s32 n = (s32)((f32)e->x6c->x68 * d->x68);
        p->xb0 = n < 1 ? 1 : n;
    } else {
        p->xb0 = 0;
    }
    p->xb8 = 0;
    p->xb4 = 0;
    return p;
}
#undef D_002E26A0

/* func_0014a908 (from hand/nostrict/text_00140000_h34.c). */
typedef struct { u8 pad[0x20]; f32 x20; u8 pad24[8]; f32 x2c; u8 x30; u8 x31; s8 x32; u8 x33; } W34Prm;
typedef struct { u8 pad[0x14]; s32 x14; W34Prm *x18; u8 pad1c[0x14]; s32 x30; } W34Eff;
typedef struct { u8 pad[0x40]; f32 x40; u8 pad44[0x14c - 0x44]; W34Eff *x14c; } W34EObj;
typedef struct { u8 pad[8]; s32 x8; f32 xc; u8 pad10[0x10]; s32 x20; f32 x24; f32 x28; u8 pad2c[0x60 - 0x2c]; s32 *x60; s32 x64; u8 pad68[0x94 - 0x68]; f32 x94; s32 x98; } W34Prt;
#define func_0014a4a8 ((void *(*)()) func_0014a4a8)
W34Prt *func_0014a908(W34EObj *o, u32 m, B4D *d) {
    W34Prt *r = func_0014a4a8(o, m, d);
    if (o->x14c) {
        if (r->x20 == 48) {
            W34Prm *p = o->x14c->x18;
            r->xc += p->x20 * o->x40;
            r->x24 *= p->x2c;
            r->x28 *= p->x2c;
            r->x64 += p->x33;
            if (r->x64 >= 100) r->x64 = 99;
            else if (r->x64 <= 0) r->x64 = 1;
            r->x94 *= p->x31 * 0.0499999970197677612304688f;
            r->x98 += p->x32;
        }
        r->x8 = o->x14c->x14;
        r->x60 = &o->x14c->x30;
        o->x14c->x30 = 0;
    }
    return r;
}
#undef func_0014a4a8

/* func_0014ac50 (from hand/nostrict/text_00140000_h56.c). */
void func_00121fc4(f32 *, f32 *);
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x10]; f32 v30[4]; } Hs;
f32 sinf(f32);
f32 atan2f(f32, f32);
f32 cosf(f32);
f32 func_00120c88(f32);
void func_0014ac50(Hm *o, Hs *s, f32 *out) {
    f32 a;

    if ((s32)(o->d0 >> 6) & 1) {
        PlatVu0SubVector(out, s->pos, o->pos);
        out[1] = 0.0f;
        func_00121fc4(out, out);
        if (out[3] == 0.0f) {
            PlatVu0SubVector(out, (*(f32 (*)[0x4])&D_002C58A0), s->v30);
        }
    } else if (((s32)(o->u30.d >> 10) & 1) || !o->u30.s.tg) {
        PlatVu0SubVector(out, o->pos, o->v70);
        out[1] = 0.0f;
        PlatVu0Normalize(out, out);
    } else {
        PlatVu0SubVector(out, s->pos, o->u30.s.tg->pos);
        out[1] = 0.0f;
        a = func_00120c88(atan2f(out[0], out[2]) - o->u30.s.tg->ang);
        if (a > 0.7853982f) {
            a = 0.7853982f;
        } else if (a < -0.7853982f) {
            a = -0.7853982f;
        }
        a = func_00120c88(o->u30.s.tg->ang + a);
        out[0] = sinf(a);
        out[2] = cosf(a);
    }
    out[3] = 1.0f;
}

/* func_0014ade0 (from hand/nostrict/text_00140000_h56.c). */
typedef struct {
    u32 flags;
    s32 w4;
    u8 pad8[0x50 - 8];
    f32 v50[4];
    u8 pad60[0x9c - 0x60];
    u32 w9c;
    u8 padA0[0x370 - 0xa0];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 hi:25; } b; } u370;
    u8 pad378[0x39e - 0x378];
    u8 b39e;
} Pf;
void func_00146fb8(Pf *, s32, s32);
typedef struct {
    u64 d0;
    union { u64 x; struct { u32 lo; u32 b0:5; u32 f37:1; u32 rest:26; } b; } d8;
    f32 v10[4];
    s32 w20;
} Hr;
typedef struct { u8 pad[0xc]; Hm *m; f32 pos[4]; } Hx;
typedef struct { u8 pad[4]; Hs *s; s32 w8; u8 padc[4]; f32 pos[4]; } Hy;
Hr *func_001354b8(Hm *, Hs *);
void func_0014ac00(Hm *, s32);
void func_0014a238(f32 *, f32 *, f32 *);
void func_00134870(Hs *, Hr *, f32 *);
void func_00147d50(void *, f32 *);
void func_0012bd00(void *, Hs *);
void func_0014ade0(Hx *x, Hy *y) {
    f32 t[4];
    Hm *m = x->m;
    Hr *r;
    void *q;
    s32 k;
    s32 v;

    r = func_001354b8(m, y->s);
    if (!r) return;
    k = 4;
    if (*(u32 *)y->s & 0x1000080) {
        v = m->ba8;
    } else {
        k = 64;
        if (r->d8.b.f37) {
            v = m->baa;
        } else {
            v = m->ba8;
            k = 1;
        }
    }
    func_0014ac00(m, k);
    r->w20 = y->w8;
    func_0014ac50(m, y->s, r->v10);
    func_0014a238(x->pos, y->pos, t);
    func_00134870(y->s, r, t);
    if ((s32)(r->d0 >> 4) & 1) return;
    if (!m->w8) return;
    q = func_0014a1b0(m, k, t);
    if (q) {
        func_00147d50(q, r->v10);
        func_0012bd00(q, y->s);
    }
    if (((s32)(m->d0 >> 22) & 1) && v >= 0) {
        func_00146fb8((Pf *)m->u30.s.tg, 0, v);
    }
}

/* func_0014b090 (from hand/nostrict/text_00140000_b04.c). */
typedef struct {
    union {
        u64 x;
        struct { u64 b0:2; u64 b2:2; u64 b4:2; u64 b6:3; u64 b9:1; u64 b10:1; u64 f11:1; u64 b12:2; u64 b14:1; u64 b15:1; u64 b16:1; u64 b17:3; u64 b20:1; u64 b21:1; u64 b22:2; u64 b24:1; u64 r:39; } b;
        struct { u32 lo; u32 hi; } w;
    } f;
    s32 x8;
    f32 xc;
    u8 pad10[0x20 - 0x10];
    s32 x20;
    f32 x24;
    f32 x28;
    s32 x2c;
    union { u64 x; struct { u64 b0:5; u64 b5:1; u64 b6:4; u64 b10:1; u64 r:53; } b; struct { s32 lo; struct Actor_4b090 *hi; } w; } x30;
    s32 x38_;
    f32 x3c;
    u8 pad40[0x50 - 0x40];
    f32 x50;
    u32 x54;
    s32 x58;
    void *x5c;
    s32 x60;
    s32 x64;
    u8 pad68[0x70 - 0x68];
    u8 x70[0x10];
    u8 x80[0x10];
    struct Actor_4b090 *x90;
    f32 x94;
    s32 x98;
    s32 x9c;
    s32 xa0;
    f32 xa4;
    u8 pada8[4];
    f32 xac;
    s32 xb0;
    s32 xb4;
    s32 xb8;
    u8 xbc[4];
} B4P_4b090;
typedef struct Actor_4b090 {
    s32 x0; u8 pad4[0x30 - 4]; u8 x30[0x10]; f32 x40; u8 pad44[0x68 - 0x44]; s32 x68; B4Prm *x6c;
    u8 pad70[0x88 - 0x70]; s32 x88; u8 pad8c[0xd0 - 0x8c]; f32 xd0[4][4]; u8 pad110[0x130 - 0x110];
    B4C130 *x130; u8 pad134[0x148 - 0x134]; B4C148 *x148;
    u8 pad14c[0x160 - 0x14c]; union { u64 x; struct { s32 lo; s32 hi; } w; } x160; u8 pad168[0x1cc - 0x168]; u32 x1cc;
    u8 pad1d0[0x1f0 - 0x1d0]; f32 x1f0[3]; f32 x1fc;
    u8 pad200[0x370 - 0x200];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b7:6; u32 b13:1; u32 hi:18; } b; } x370;
    u8 pad378[0x450 - 0x378]; f32 x450[4]; u8 pad460[0x470 - 0x460];
    union { u64 x; struct { struct Actor_4b090 *lo; u32 hi; } w; } x470;
} B4Ent_4b090;
s32 func_00122ff8(B4Ent_4b090 *);
typedef struct {
    union { u64 x; struct { u64 b0:2; u64 b2:2; u64 b4:2; u64 b6:2; u64 b8:24; struct Actor_4b090 *hi; } b; } f;
    union { u64 x; struct { s32 i; s32 c; } w; struct { u64 lo:32; u64 b32:5; u64 r:27; } b; } x8;
    u8 x10[0x10];
    u8 pad20[0x2c - 0x20];
    void *x2c;
} B4O;
B4O *func_001350d8(B4P_4b090 *, s32, B4Ent_4b090 *);
B4O *func_00135070(B4Ent_4b090 *, s32);
void func_001586a8(s32);
void func_00247408(B4Ent_4b090 *, s32);
void func_0013c548(s32);
#define func_0014ac00 ((void (*)(B4P_4b090 *, s32)) func_0014ac00)
s32 func_0014b090(B4P_4b090 *a, B4P_4b090 *b) {
    s32 d;
    s32 r;
    s32 k;
    s32 n;
    B4O *o;
    if (a->f.w.hi & 0x30) return 0;
    if (a->x64 >= 98 && b->x64 >= 98) return 0;
    if (b->x64 == 0) return 0;
    a->x9c |= b->x54;
    b->x9c |= a->x54;
    if (a->x64 == 100) return 16;
    if (func_00122ff8(a->x30.w.hi) && (a->x30.w.hi->x88 & 1)) return 0;
    d = a->x64 - b->x64;
    if (d > 0) {
        k = (s32)(a->f.x >> 17) & 7;
        if (k == 1 || k == 3 || k == 4) {
            r = 16;
            o = func_001350d8(b, 0, a->x30.w.hi);
            o->f.x |= 32;
            func_0014ac00(a, 16);
            goto out;
        }
    }
    if (a->x64 >= 98) {
        if (func_00122ff8(b->x30.w.hi) && (b->x30.w.hi->x88 & 1)) return 0;
        return 16;
    }
    if (!((s32)(a->x30.x >> 10) & 1)) {
        o = func_00135070(a->x30.w.hi, 0);
        if (o) {
            o->x8.w.i = d;
            o->f.b.b2 = (s32)(b->f.x >> 12) & 3;
            o->f.b.hi = b->x30.w.hi;
            o->x2c = a->x5c;
            o->x8.w.c = b->x30.w.lo;
            PlatVu0ScaleVector(o->x10, a->x30.w.hi->x30, -1.0f);
            if (d >= -40) o->x8.b.b32 = 6;
            else o->x8.b.b32 = 7;
        }
    } else {
        if (((s32)(a->f.x >> 12) & 3) == 1) a->f.b.b12 = 2;
        else a->f.b.b12 = 1;
        a->f.b.b24 = 1;
        a->x30.w.hi = b->x30.w.hi;
    }
    r = 16;
    if (d < -40) r = 32;
    func_0014ac00(a, r);
    if (b->x30.w.hi && b->x30.w.hi->x130->x4c == 0 && ((s32)(b->x30.x >> 6) & 0xf) == 1) {
        func_001586a8(10);
        n = a->xb0;
        if (n > 0) {
            n = (((*(u32 *)&D_002E27C8) >> 19) & 7) * n + n;
            func_00247408(b->x30.w.hi, n);
            func_0013c548(n);
        }
    }
out:
    return r;
}
#undef func_0014ac00

/* func_0014b3e0 (from hand/nostrict/text_00140000_h56.c). */
typedef struct { u8 pad[0x3e0]; u32 w3e0; } Hp;
typedef struct { s32 w0; Hp *p4; u8 pad8[4]; Hm *m; f32 v10[4]; f32 v20[4]; } Hz;
s32 func_0014af60(Hm *, Hm *);
s32 func_0014a330(Hm *, s32, f32 *, f32 *);
#define func_0014b090 ((s32 (*)(Hm *, Hm *)) func_0014b090)
void func_0014b3e0(Hz *x, Hz *y) {
    f32 t[4];
    Hm *m1 = x->m;
    Hm *m2 = y->m;
    s32 a, b, ra, rb;

    if (!func_0014af60(m1, m2)) return;
    if (!func_0014af60(m2, m1)) return;
    a = func_0014b090(m1, m2);
    rb = 0;
    ra = 0;
    if (a > 0) ra = func_0014a330(m1, a, x->v10, y->v10);
    b = func_0014b090(m2, m1);
    if (b > 0) rb = func_0014a330(m2, b, y->v10, x->v10);
    if (a <= 0 && b <= 0) return;
    if (a == 0) {
        func_0014ac00(m1, b);
    } else if (b == 0) {
        func_0014ac00(m2, a);
    }
    if (ra || rb) return;
    PlatVu0InterVector(t, x->v20, y->v20, 0.5f);
    func_00147ed8(D_00350CE0, (a | b) < 32 ? 10 : 11, 20000, t);
}
#undef func_0014b090

/* func_0014b768 (from hand/nostrict/text_00140000_s6_07.c). */
typedef struct {
    union {
        u64 x;
        struct { u32 lo; u32 hi; } w;
    } f;
    u8 pad8[0x10 - 0x8];
    f32 x10[4];
    u8 pad20[0x30 - 0x20];
    union { u64 x; struct { s32 lo; s32 hi; } w; } x30;
    u8 pad38[0x5c - 0x38];
    s32 x5c;
    u8 pad60[0xa9 - 0x60];
    s8 xa9;
} B7P;
typedef struct {
    union { u64 x; struct { u32 lo; s32 hi; } w; } f;
    union { u64 x; struct { s32 i; s32 c; } w; struct { u64 lo:32; u64 b32:5; u64 r:27; } b; } x8;
    u8 x10[0x10];
    u8 pad20[0x2c - 0x20];
    s32 x2c;
} B7O;
typedef struct { f32 p[4]; f32 d[4]; f32 hit[4]; s16 x30; s32 x34; } B7Q;
void func_00118628(B7Q *, s32);
s32 func_00105b68(s32, s32);
void func_00105a30(s32, s32, f32 *);
void func_0014aaf0(B7P *);
#define func_00146fb8 ((void (*)(s32, s32, s32)) func_00146fb8)
#define func_0014a1b0 ((void *(*)(B7P *, s32, f32 *)) func_0014a1b0)
#define func_0014ac00 ((void (*)(B7P *, s32)) func_0014ac00)
#define func_00135070 ((B7O *(*)(s32, s32)) func_00135070)
B7P *func_0014b768(B7P *a, f32 *p0, f32 *p1) {
    B7Q q;
    f32 v[4];
    s32 k;
    s32 r;
    void *h;
    B7O *o;

    PlatVu0CopyVector(q.p, p0);
    PlatVu0SubVector(q.d, p1, p0);
    func_00118628(&q, ((s32)(a->x30.x >> 10) & 1) ? 2 : 1);
    if (q.x30 >= 0) {
        r = func_00105b68(q.x34, q.x30);
        switch (r) { case 0: k = 0x100; break; case 5: k = 8; break; default: k = 2; break; }
        if ((k & 0x102) && ((s32)(a->f.x >> 22) & 1)) {
            func_00146fb8(a->x30.w.hi, 0, a->xa9);
        }
        h = func_0014a1b0(a, k, q.hit);
        if (h) {
            func_00105a30(q.x34, q.x30, v);
            PlatVu0SubVector(v, (*(f32 (*)[0x4])&D_002C58A0), v);
            func_00147d50(h, v);
        }
        func_0014ac00(a, k);
        if ((s32)(a->f.x >> 26) & 1) {
            PlatVu0CopyVector(a->x10, q.hit);
        }
        if (!((s32)(a->x30.x >> 10) & 1) && !(k & 8) && a->x30.w.hi) {
            o = func_00135070(a->x30.w.hi, 0);
            if (o) {
                o->x8.w.i = -20;
                o->x8.b.b32 = 6;
                o->x2c = a->x5c;
                o->f.w.hi = 0;
            }
            func_0014aaf0(a);
            a = 0;
        }
    }
    return a;
}
#undef func_00146fb8
#undef func_0014a1b0
#undef func_0014ac00
#undef func_00135070

/* func_0014b9e0 (from hand/nostrict/text_00130000_s6_na_2.c). */
typedef struct {
    union { u64 flags; s32 w; } u;
    u8 pad8[4];
    f32 f0c;
    f32 v10[4];
    s32 i20;
    f32 f24;
    f32 f28;
    u8 pad2c[0x34-0x2c];
    s32 i34;
    u8 pad38[0x3c-0x38];
    f32 f3c;
    f32 v40[4];
    u8 pad50[0x54-0x50];
    s32 i54;
    u8 pad58[0x70-0x58];
    f32 v70[4];
    f32 v80[4];
    s32 i90;
} Src57;
typedef struct { s32 kind; s32 a4; s32 a8; Src57 *src; s32 a10; f32 f14; f32 f18; s32 pad1c; f32 v[4]; } Ent57;
void func_0014b550(Ent57 *, Ent57 *, s32);
s32 func_0014b9e0(Src57 *s, f32 *a, f32 *b, f32 f0, f32 f1, Ent57 *tbl, s32 n) {
    f32 p[4];
    f32 zero;
    f32 d[4];
    f32 len;
    s32 cnt;
    Ent57 *e;

    len = (f0 + f1) * 0.5f;
    if ((s32)(s->u.flags >> 27) & 1) len += len;
    if (len == 0.0f) return 0;
    e = &tbl[n];
    PlatVu0SubVector(d, b, a);
    func_00121fc4(d, d);
    cnt = 0;
    PlatVu0ScaleVectorXYZ(d, d, len);
    zero = 0.0f;
    PlatVu0CopyVector(p, a);
    f1 = (f1 - f0) / (d[3] / len);
    do {
        e->kind = (s32)(s->u.flags >> 12) & 3;
        e->a4 = s->i34;
        e->a8 = s->i54;
        e->src = s;
        e->a10 = 1;
        PlatVu0CopyVector(e->v, p);
        e->f14 = e->f18 = f0;
        f0 += f1;
        func_0014b550(e, tbl, n);
        if (n + cnt < 254) {
            e++;
            cnt++;
        }
        PlatVu0AddVector(p, p, d);
        d[3] -= len;
    } while (zero < d[3]);
    return cnt;
}

/* func_0014bdc0 (from hand/nostrict/text_00140000_b04.c). */
typedef struct {
    union {
        u64 x;
        struct { u64 b0:2; u64 b2:2; u64 b4:2; u64 b6:3; u64 b9:1; u64 b10:1; u64 f11:1; u64 b12:2; u64 b14:1; u64 b15:1; u64 b16:1; u64 b17:3; u64 b20:1; u64 b21:1; u64 b22:2; u64 b24:1; u64 r:39; } b;
        struct { u32 lo; u32 hi; } w;
    } f;
    s32 x8;
    f32 xc;
    u8 pad10[0x20 - 0x10];
    s32 x20;
    f32 x24;
    f32 x28;
    s32 x2c;
    union { u64 x; struct { u64 b0:5; u64 b5:1; u64 b6:4; u64 b10:1; u64 r:53; } b; struct { s32 lo; struct Actor_4bdc0 *hi; } w; } x30;
    s32 x38_;
    f32 x3c;
    u8 pad40[0x50 - 0x40];
    f32 x50;
    u32 x54;
    s32 x58;
    void *x5c;
    s32 x60;
    s32 x64;
    u8 pad68[0x70 - 0x68];
    u8 x70[0x10];
    u8 x80[0x10];
    struct Actor_4bdc0 *x90;
    f32 x94;
    s32 x98;
    s32 x9c;
    s32 xa0;
    f32 xa4;
    u8 pada8[4];
    f32 xac;
    s32 xb0;
    s32 xb4;
    s32 xb8;
    u8 xbc[4];
} B4P_4bdc0;
typedef struct Actor_4bdc0 {
    s32 x0; u8 pad4[0x30 - 4]; u8 x30[0x10]; f32 x40; u8 pad44[0x68 - 0x44]; s32 x68; B4Prm *x6c;
    u8 pad70[0x88 - 0x70]; s32 x88; u8 pad8c[0xd0 - 0x8c]; f32 xd0[4][4]; u8 pad110[0x130 - 0x110];
    B4C130 *x130; u8 pad134[0x148 - 0x134]; B4C148 *x148;
    u8 pad14c[0x160 - 0x14c]; union { u64 x; struct { s32 lo; s32 hi; } w; } x160; u8 pad168[0x1cc - 0x168]; u32 x1cc;
    u8 pad1d0[0x1f0 - 0x1d0]; f32 x1f0[3]; f32 x1fc;
    u8 pad200[0x370 - 0x200];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b7:6; u32 b13:1; u32 hi:18; } b; } x370;
    u8 pad378[0x450 - 0x378]; f32 x450[4]; u8 pad460[0x470 - 0x460];
    union { u64 x; struct { struct Actor_4bdc0 *lo; u32 hi; } w; } x470;
} B4Ent_4bdc0;
extern B4P D_0054C440[];
void func_0014aab0(B4P_4bdc0 *);
void func_0014a0f0(B4P_4bdc0 *);
s32 func_0014bba8(B4P_4bdc0 *, s32, s32);
#define func_00122ff8 ((s32 (*)(B4Ent_4bdc0 *)) func_00122ff8)
extern B4P_4bdc0 D_0054C440_0014bdc0[] __asm__("D_0054C440");
#define D_0054C440 D_0054C440_0014bdc0
#define func_0014aaf0 ((void (*)(B4P_4bdc0 *)) func_0014aaf0)
s32 func_0014bdc0(s32 a) {
    s32 i;
    s32 r = 0;
    s32 k;
    B4P_4bdc0 *p;
    B4Ent_4bdc0 *e;
    for (i = 0; i < 64; i++) {
        p = &D_0054C440[i];
        p->f.b.b15 = 0;
        if (!((s32)(p->f.x >> 11) & 1)) continue;
        if (((s32)(p->f.x >> 21) & 1)) func_0014aab0(p);
        if (((s32)(p->f.x >> 2) & 3) == 0) {
            func_0014aaf0(p);
            continue;
        }
        if (!func_00122ff8(p->x30.w.hi)) p->x30.w.hi = 0;
        if (!((s32)(p->x30.x >> 10) & 1)) {
            if (!func_00122ff8(p->x90)) {
                func_0014aab0(p);
                continue;
            }
            if (!(p->x90->x0 & 0x8000)) continue;
        }
        if (((s32)(p->f.x >> 24) & 1)) continue;
        p->f.w.hi = 0;
        if (p->x90 && (p->x90->x88 & 1) && !((s32)(p->x30.x >> 10) & 1)) {
            k = ((s32)(p->f.x >> 17) & 7);
            if (k != 1 && k != 2 && k != 4) continue;
        }
        if (((s32)(p->f.x >> 10) & 1)) continue;
        switch (((s32)(p->f.x >> 2) & 3)) {
        case 1:
            if (!((*(u32 *)&D_002C5960) & 1)) p->f.b.b2 = 0;
            break;
        case 2:
            if (p->x58 == 0xfff) {
                p->x58 = p->x30.w.hi->x160.w.hi;
                p = 0;
            } else {
                e = p->x30.w.hi;
                if (p->x58 != e->x160.w.hi || ((s32)(e->x160.x >> 8) & 1)) {
                    func_0014aaf0(p);
                    p = 0;
                } else if (!(e->x1cc & (0x10000 << ((s32)(p->f.x >> 4) & 3)))) {
                    p = 0;
                } else if (!(p->f.x & 0x10200)) {
                    func_001315c0(e, 0x8003, 0.0f, p->x70);
                    PlatVu0CopyVector(p->x80, p->x70);
                    p->f.b.b16 = 1;
                }
            }
            if (p == 0) continue;
            func_0014a0f0(p);
            break;
        case 3:
            if (((s32)(p->f.x >> 9) & 1)) {
                p->f.b.b16 = 0;
                p->f.b.b9 = 0;
            }
            func_0014a0f0(p);
            break;
        }
        if (p) {
            r = func_0014bba8(p, a, r);
            p->f.b.b15 = 1;
        }
    }
    return r;
}
#undef func_00122ff8
#undef D_0054C440
#undef func_0014aaf0

/* func_0014c130 (from hand/nostrict/text_00140000_h57.c). */
typedef struct {
    union { u64 flags; s32 w; } u;
    u8 pad8[4];
    f32 f0c;
    f32 v10[4];
    s32 i20;
    f32 f24;
    f32 f28;
    u8 pad2c[0x34-0x2c];
    s32 i34;
    u8 pad38[0x3c-0x38];
    f32 f3c;
    f32 v40[4];
    u8 pad50[0x54-0x50];
    s32 i54;
    u8 pad58[0x70-0x58];
    f32 v70[4];
    f32 v80[4];
    s32 i90;
    u8 pad94[0x9c-0x94];
    s32 i9c;
    u8 pada0[0xc0-0xa0];
} Src57_c130;
typedef struct { s32 kind; s32 a4; s32 a8; s32 src; s32 a10; f32 f14; f32 f18; s32 pad1c; f32 v[4]; } Ent57_c130;
typedef struct { u8 x[20]; } Col57_c130;
typedef struct { u8 pad0[6]; u8 n; u8 pad7[0x18-7]; Col57_c130 *cols; } ColSet57_c130;
typedef struct {
    u8 pad0[0x134];
    ColSet57_c130 *cs;
    u8 pad138[0x370-0x138];
    u64 f370;
    u8 pad378[0x3a8-0x378];
    u32 mask;
    u8 pad3ac[0x3e0-0x3ac];
    s32 f3e0;
} Chr57_c130;
extern u32 D_002C5958;
Ent57_c130 *func_00121e28(s32, s32);
void func_00121ee0(Ent57_c130 *);
Chr57_c130 *func_001230a0(Chr57_c130 *);
s32 func_00123368(Chr57_c130 *);
void func_0015bad0(Chr57_c130 *, Col57_c130 *, void *);
extern Src57_c130 D_0054C440_0014c130[64] __asm__("D_0054C440");
#define D_0054C440 D_0054C440_0014c130
extern s32 D_0054F440_0014c130 __asm__("D_0054F440");
#define D_0054F440 D_0054F440_0014c130
#define func_0014bdc0 ((s32 (*)(Ent57_c130 *)) func_0014bdc0)
#define func_0014b550 ((void (*)(Ent57_c130 *, Ent57_c130 *, s32)) func_0014b550)
s32 func_0014c130(void) {
    Ent57_c130 *tbl;
    s32 cnt;
    Ent57_c130 *e;
    Chr57_c130 *p;
    Chr57_c130 *q;
    Src57_c130 *s;
    Col57_c130 *c;
    s32 i;

    if ((D_002C5958 >> 14) & 1) return 0;
    tbl = func_00121e28(0x3000, 0);
    cnt = func_0014bdc0(tbl);
    e = &tbl[cnt];
    e->a10 = 1;
    e->src = 0;
    for (q = 0; (p = func_001230a0(q)) != 0; q = p) {
        if (!func_00123368(p)) continue;
        e->kind = (s32)(p->f370 >> 37) & 3;
        e->a4 = (s32)p;
        c = p->cs->cols;
        for (i = 0; i < p->cs->n; i++, c++) {
            if (!(p->mask & (1 << i))) {
                func_0015bad0(p, c, &e->a10);
                e->a8 = c->x[0];
                func_0014b550(e, tbl, cnt);
            }
        }
    }
    func_00121ee0(tbl);
    s = D_0054C440;
    for (i = 0; i < 64; i++, s++) {
        if ((s32)(s->u.flags >> 15) & 1) {
            PlatVu0CopyVector(s->v70, s->v10);
            PlatVu0CopyVector(s->v80, s->v40);
            s->u.flags |= 0x10000;
        } else {
            s->u.flags &= ~0x10000;
        }
        s->i9c &= D_0054F440;
    }
    p = 0;
    while ((p = func_001230a0(p)) != 0) {
        p->f3e0 &= D_0054F440;
    }
    return (s32)p;
}
#undef D_0054C440
#undef D_0054F440
#undef func_0014bdc0
#undef func_0014b550

