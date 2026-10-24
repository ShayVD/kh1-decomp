#include "common.h"
#include "platform/math.h"

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
    union { u64 x; struct { u64 b0:5; u64 b5:1; u64 b6:4; u64 b10:1; u64 r:53; } b; struct { s32 lo; struct Actor *hi; } w; } x30;
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
    struct Actor *x90;
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
typedef struct Actor {
    s32 x0; u8 pad4[0x30 - 4]; u8 x30[0x10]; f32 x40; u8 pad44[0x68 - 0x44]; s32 x68; B4Prm *x6c;
    u8 pad70[0x88 - 0x70]; s32 x88; u8 pad8c[0xd0 - 0x8c]; f32 xd0[4][4]; u8 pad110[0x130 - 0x110];
    B4C130 *x130; u8 pad134[0x148 - 0x134]; B4C148 *x148;
    u8 pad14c[0x160 - 0x14c]; union { u64 x; struct { s32 lo; s32 hi; } w; } x160; u8 pad168[0x1cc - 0x168]; u32 x1cc;
    u8 pad1d0[0x1f0 - 0x1d0]; f32 x1f0[3]; f32 x1fc;
    u8 pad200[0x370 - 0x200];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b7:6; u32 b13:1; u32 hi:18; } b; } x370;
    u8 pad378[0x450 - 0x378]; f32 x450[4]; u8 pad460[0x470 - 0x460];
    union { u64 x; struct { struct Actor *lo; u32 hi; } w; } x470;
} B4Ent;

#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002E26A0.h"
extern u32 D_0054F440;
B4P *func_0014a450(void);
s32 func_0013c318(s32);
s32 func_002408d8(s32);
void func_001315c0(void *, s32, f32, void *);
void func_002675a8(void *, void *);

s32 func_00122ff8(B4Ent *);
extern f32 D_002BBDFC;
#include "data/pieces/D_002E27C8.h"

typedef struct {
    union { u64 x; struct { u64 b0:2; u64 b2:2; u64 b4:2; u64 b6:2; u64 b8:24; struct Actor *hi; } b; } f;
    union { u64 x; struct { s32 i; s32 c; } w; struct { u64 lo:32; u64 b32:5; u64 r:27; } b; } x8;
    u8 x10[0x10];
    u8 pad20[0x2c - 0x20];
    void *x2c;
} B4O;
B4O *func_001350d8(B4P *, s32, B4Ent *);
B4O *func_00135070(B4Ent *, s32);
void func_0014ac00(B4P *, s32);
void func_00267560(void *, void *, f32);
void func_001586a8(s32);
void func_00247408(B4Ent *, s32);
void func_0013c548(s32);

s32 func_0014b090(B4P *a, B4P *b) {
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
            func_00267560(o->x10, a->x30.w.hi->x30, -1.0f);
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

extern B4P D_0054C440[];
#include "data/pieces/D_002C5960.h"
void func_0014aab0(B4P *);
void func_0014aaf0(B4P *);
void func_0014a0f0(B4P *);
s32 func_0014bba8(B4P *, s32, s32);

s32 func_0014bdc0(s32 a) {
    s32 i;
    s32 r = 0;
    s32 k;
    B4P *p;
    B4Ent *e;
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
                    func_002675a8(p->x80, p->x70);
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

f32 cosf(f32);
f32 acosf(f32);
f32 func_0014fc68(B4Ent *, B4Ent *, f32 *, f32);
f32 func_0014fab0(B4Ent *, B4Ent *, f32 *, f32);
f32 func_00267390(f32 *, f32 *);
void func_00267370(f32 *, f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
void func_00120cf8(f32 *, f32 (*)[4], f32);
void func_002672f8(f32 *, f32 (*)[4], f32 *);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);

void func_0014fe48(B4Ent *e) {
    f32 v[4];
    f32 ax[4];
    f32 m[4][4];
    f32 d;
    f32 a;
    f32 lim;
    f32 c;
    e->x1cc &= ~0xc;
    if ((s32)(e->x470.x >> 33) & 1) {
        e->x1fc = e->x1fc + e->x450[3] * D_002BBDFC;
        if (1.0f < e->x1fc) {
            e->x1fc = 1.0f;
        } else if (e->x1fc < 0.0f) {
            e->x470.x &= ~(1ULL << 33);
            return;
        }
        e->x1cc |= 4;
        return;
    }
    d = 500.0f;
    if (!func_00122ff8(e->x470.w.lo)) {
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = -1.0f;
        e->x470.x &= ~(1ULL << 32);
    } else {
        c = cosf(((s32)(e->x470.x >> 32) & 1) ? e->x6c->x20 : e->x6c->x1c);
        if (((s32)(e->x370.x >> 37) & 3) == 1) d = func_0014fc68(e, e->x470.w.lo, v, -c);
        else d = func_0014fab0(e, e->x470.w.lo, v, -c);
        if (0.0f < d) {
            e->x470.x |= 1ULL << 32;
        } else {
            e->x470.x &= ~(1ULL << 32);
            v[1] = v[0] = 0.0f;
            v[2] = -1.0f;
        }
    }
    a = acosf(func_00267390(e->x450, v));
    lim = e->x6c->x24 * D_002BBDFC;
    if (lim < a) a = lim;
    func_00267370(ax, e->x450, v);
    func_002673b8(ax, ax);
    func_00120cf8(ax, m, a);
    e->x450[3] = 0.0f;
    func_002672f8(e->x450, m, e->x450);
    func_002673b8(e->x450, e->x450);
    if (e->x450[2] <= -1.0f) return;
    c = -cosf(e->x6c->x28);
    if (e->x450[2] < c) e->x450[3] = (-1.0f - e->x450[2]) / (-1.0f - c);
    else e->x450[3] = 1.0f;
    if (e->x130->x4c == 507) {
        sceVu0CopyMatrix(m, e->xd0);
        func_001315c0(e, 0, 0.5f, m[3]);
        func_002675a8(v, e->x450);
        func_00267560(v, v, d);
        v[3] = 1.0f;
        func_002672f8(e->x1f0, m, v);
        e->x1fc = e->x450[3];
        e->x1cc |= 4;
    } else {
        e->x1cc |= 8;
    }
}
#include "data/pieces/D_002E31B0.h"
f32 D_00551D70 ALIGNED(16);
f32 func_00121b08(f32);

#include "data/types/nostrict_text_00140000_b04.h"
typedef struct { u8 pad[0x3c]; f32 x3c; } B4Ky;
typedef struct { B4Ky *x0; } B4Kyp;
typedef struct { u8 pad[0x10]; B4Kyp *x10; u8 pad14[0x48 - 0x14]; union { u64 x; struct { u8 b0; s8 x49; } c; } x48; } B4Obj;
typedef struct B4Ln { struct B4Ln *x0; B4Obj *x4; } B4Ln;
B4Ln *D_005739F0 ALIGNED(16);
B4Ln D_005736F0[0x60] ALIGNED(16);
void func_00267370(f32 *, f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);

/* needs make: uses rodata */

/* needs make: uses rodata (jump table jtbl_0048E420) */
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
    func_002675a8(p->x80, p->x70);
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
f32 func_00121b08(f32);
#include "data/bss_0054_mixed.h"
#include "data/bss_0057_mixed.h"
#include "data/data_002C.h"
#include "data/data_0030.h"
#include "data/data_0035.h"
#include "data/pieces/D_002BBDFC.h"
