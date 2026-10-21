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
    union { u64 x; struct { u64 b0:5; u64 b5:1; u64 b6:4; u64 b10:1; u64 r:53; } b; struct { s32 lo; struct B4Ent *hi; } w; } x30;
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
    struct B4Ent *x90;
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
typedef struct B4Ent {
    s32 x0; u8 pad4[0x30 - 4]; u8 x30[0x10]; f32 x40; u8 pad44[0x68 - 0x44]; s32 x68; B4Prm *x6c;
    u8 pad70[0x88 - 0x70]; s32 x88; u8 pad8c[0xd0 - 0x8c]; f32 xd0[4][4]; u8 pad110[0x130 - 0x110];
    B4C130 *x130; u8 pad134[0x148 - 0x134]; B4C148 *x148;
    u8 pad14c[0x160 - 0x14c]; union { u64 x; struct { s32 lo; s32 hi; } w; } x160; u8 pad168[0x1cc - 0x168]; u32 x1cc;
    u8 pad1d0[0x1f0 - 0x1d0]; f32 x1f0[3]; f32 x1fc;
    u8 pad200[0x370 - 0x200];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b7:6; u32 b13:1; u32 hi:18; } b; } x370;
    u8 pad378[0x450 - 0x378]; f32 x450[4]; u8 pad460[0x470 - 0x460];
    union { u64 x; struct { struct B4Ent *lo; u32 hi; } w; } x470;
} B4Ent;

typedef struct { u8 pad[0xfe]; u8 xfe; } B4G;
extern B4G *D_00308CDC;
extern B4Ent *D_002E26A0;
extern u32 D_0054F440;
B4P *func_0014a450(void);
s32 func_0013c318(s32);
s32 func_002408d8(s32);
void func_001315c0(void *, s32, f32, void *);
void func_002675a8(void *, void *);

s32 func_00122ff8(B4Ent *);
extern f32 D_002BBDFC;
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E27C8.h"

typedef struct {
    union { u64 x; struct { u64 b0:2; u64 b2:2; u64 b4:2; u64 b6:2; u64 b8:24; struct B4Ent *hi; } b; } f;
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
            n = ((D_002E27C8 >> 19) & 7) * n + n;
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
            if (!(D_002C5960 & 1)) p->f.b.b2 = 0;
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

typedef struct { u8 pad0[0x20]; f32 x20[4]; u8 pad30[0x164 - 0x30]; s32 x164; } B4A81;
extern f32 D_002C58A0[];
extern s32 D_002BC0F0[];
#include "data/pieces/D_003519E0.h"
s32 func_00137618(B4A81 *);
void func_00130340(B4A81 *, s32, f32);
void func_00130578(B4A81 *, s32, f32);
s32 func_0014efe0(B4A81 *, s32);

void func_001581d8(B4A81 *e, f32 *v) {
    f32 f;
    s32 i;
    s32 a;
    s32 b;
    if (func_00137618(e)) {
        if (0.7999999523162842f < v[0]) {
            v[0] = 1.0f;
            v[3] = 0.5f;
            v[1] = 0.0f;
            v[2] = 0.0f;
            switch (e->x164) {
            case 0:
                f = v[1];
                func_00130340(e, 202, f);
                func_00130578(e, 203, f);
                break;
            case 206:
                f = v[1];
                func_00130340(e, 207, f);
                func_00130578(e, 0, f);
                break;
            }
        } else if (v[0] < -0.7999999523162842f) {
            v[0] = -1.0f;
            v[3] = 0.5f;
            v[1] = 0.0f;
            v[2] = 0.0f;
            switch (e->x164) {
            case 0:
                f = v[1];
                func_00130340(e, 205, f);
                func_00130578(e, 206, f);
                break;
            case 203:
                f = v[1];
                func_00130340(e, 204, f);
                func_00130578(e, 0, f);
                break;
            }
        } else {
            func_002675a8(v, D_002C58B0);
            switch (e->x164) {
            case 203:
                f = 0.0f;
                func_00130340(e, 204, f);
                func_00130578(e, 0, f);
                break;
            case 206:
                f = 0.0f;
                func_00130340(e, 207, f);
                func_00130578(e, 0, f);
                break;
            }
        }
        switch (e->x164) {
        case 0:
        case 202:
        case 204:
        case 205:
        case 207:
            v[3] *= 0.7f;
            break;
        }
    } else {
        func_002675a8(v, D_002C58A0);
        switch (e->x164) {
        case 209:
            v[0] = 1.0f;
            v[3] = 2.0f;
            break;
        case 210:
            v[0] = -1.0f;
            v[3] = 2.0f;
            break;
        }
    }
    func_002675a8(e->x20, v);
    if (func_0014efe0(e, 1)) {
        for (i = 0; i < 3; i++) {
            if (D_002BC0F0[i + 4] < D_003519E0[i + 4]) D_002BC0F0[i + 4]++;
            else if (D_003519E0[i + 4] < D_002BC0F0[i + 4]) D_002BC0F0[i + 4]--;
        }
    }
}

typedef struct { u8 pad[4]; f32 x4; f32 x8; } B4P9;
typedef struct {
    u32 x0; u8 pad4[0x20 - 4]; f32 x20[4]; f32 x30[4]; u8 pad40[0x6c - 0x40]; B4P9 *x6c;
    u8 pad70[0x88 - 0x70]; s32 x88; u8 pad8c[0x164 - 0x8c]; s32 x164; u8 pad168[0x178 - 0x168]; s32 x178;
    u8 pad17c[0x1cc - 0x17c]; u32 x1cc; u8 pad1d0[0x370 - 0x1d0];
    union { u64 x; struct { u64 lo:50; u64 b50:1; u64 r:13; } b; } x370;
    u8 pad378[0x39e - 0x378]; u8 x39e; u8 pad39f[0x440 - 0x39f]; u64 x440;
} B4E9;
extern u32 D_002C5958;
extern s32 D_002C5C54;
void func_001376e8(B4E9 *, f32 *);
void func_00130398(B4E9 *, s32, f32);
s32 func_00131b08(B4E9 *);
void func_00146c98(B4E9 *, s32);
s32 func_00130010(B4E9 *);
void func_0012bd98(B4E9 *, s32, s32, f32 *);

void func_00159f78(B4E9 *e, f32 *v, s32 n) {
    f32 tmp[4];
    u32 *p;
    s32 k;
    if (v[0] == 0.0f && v[1] == 0.0f && v[2] == 0.0f) goto zero;
    func_001376e8(e, v);
    func_002675a8(e->x20, v);
    if (e->x0 & 4) return;
    if ((s32)(e->x440 >> 33) & 1) return;
    if (v[3] == 0.0f) {
        if (e->x1cc & 0x100000) return;
        p = &D_002C5958;
        if (((s32)(e->x370.x >> 50) & 1) != (*p & 1)) {
            if ((*p & 1) || (e->x164 == 0 && func_00131b08(e))) {
                e->x370.b.b50 = *p & 1;
                func_00130398(e, n, 16.0f);
                return;
            }
        }
        if (e->x178) return;
        if ((e->x164 == n + 1 || e->x164 == n + 2) && !D_002C5C54) func_00146c98(e, 8);
        func_00130398(e, n, 10.0f);
    } else {
        e->x370.b.b50 = D_002C5958 & 1;
        if (e->x88 & 0x80) v[3] = e->x20[3] = e->x6c->x4;
        k = (v[3] < e->x6c->x8) ? n + 1 : n + 2;
        if (e->x164 == n && !func_00130010(e)) {
            func_001315c0(e, 41, 1.0f, tmp);
            func_0012bd98(e, e->x39e, 0x80000002, tmp);
            func_001315c0(e, 40, 1.0f, tmp);
            func_0012bd98(e, e->x39e, 0x80000002, tmp);
        }
        func_00130398(e, k, 8.0f);
    }
    return;
zero:
    func_002675a8(e->x20, e->x30);
    e->x20[3] = 0.0f;
}

typedef struct { u8 pad[0x20]; f32 x20; f32 x24; f32 x28; u8 pad2c[0x3b0 - 0x2c]; f32 x3b0; } B4E5;
typedef struct { s32 a; s32 b; } B4Pair;
extern u32 D_002E3190;
f32 D_00551D70 ALIGNED(16);
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_002E31B0.h"
void func_0014f658(B4E5 *, s32);
f32 func_0012ec60(s32, s32, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
f32 func_00121748(f32 *, f32 *);
f32 func_00120c18(f32 *);
f32 func_00121b08(f32);

void func_0015e178(B4E5 *e, s32 unused, f32 *v) {
    f32 a[4];
    f32 b[4];
    f32 d;
    f32 t;
    if (0.0f < v[3]) {
        if (v[3] < 0.7999999523162842f) v[3] = 4.0f;
        else v[3] = 8.0f;
    }
    if (v[0] == 0.0f && v[2] == 0.0f) {
        v[0] = e->x20;
        v[2] = e->x28;
    }
    if ((D_002E3190 >> 27) & 1) v[1] = -8.0f;
    else if ((D_002E3190 >> 28) & 1) v[1] = 8.0f;
    else v[1] = 0.0f;
    if ((D_002E27C8 >> 6) & 1) {
        if (D_002E3190 & 0x18000000) {
            if (0.0f < D_00551D70 && D_00551D70 < 16.0f) func_0014f658(e, 25);
            else D_00551D70 = 16.0f;
        } else if (0.0f < D_00551D70) {
            D_00551D70 -= D_002BBDFC;
        }
    }
    if (D_002E31B8 >= 3 && 0.0f < v[3] && v[1] == 0.0f) {
        d = func_0012ec60((*(B4Pair *)&D_002E31B0).a, (*(B4Pair *)&D_002E31B0).b, a);
        func_001315c0(e, 0x8003, 0.0f, b);
        func_00267530(a, a, b);
        if (0.5f < func_00121748(a, v)) {
            t = (func_00120c18(a) - d - 200.0f) * 0.7999999523162842f;
            if (0.0f < t) {
                v[1] = a[1] / t * v[3];
                if (8.0f < v[1]) v[1] = 8.0f;
                else if (v[1] < -8.0f) v[1] = -8.0f;
            }
        }
    }
    e->x3b0 = func_00121b08(e->x3b0);
}

#include "data/types/nostrict_text_00140000_b04.h"
typedef struct { u16 x0; u8 x2; u8 x3; u16 x4; u16 x6; s32 x8; } B4Tx;
typedef struct { u8 pad[0xc]; s32 xc; } B4Tc;
typedef struct { u8 pad[0xd]; u8 xd; u8 pade[2]; B4Tx *x10; B4Tc *x14; } B4Rec;
typedef struct {
    u64 x0; u64 x8; u8 pad10[4]; u32 x14; u8 pad18[0x2c - 0x18]; u8 x2c; u8 pad2d[3]; u32 x30; u32 x34; u32 x38;
    u8 pad3c[4]; s32 x40;
} B4Src;
typedef union { struct { u8 pad[0x10]; B4Tx *x10[1]; } a; struct { u8 pad[0x14]; B4Tc *x14[1]; } b; } B4Tbl;
typedef struct { B4Src *x0; u8 pad4; s8 x5; s8 x6; u8 x7; } B4Drw;
typedef struct { u8 pad[0x40]; u64 x40; u8 pad48[0x60 - 0x48]; u64 x60; u8 pad68[8]; u64 x70; u8 pad78[8]; u64 x80; u8 pad88[8]; u64 x90; u8 pad98[8]; u64 xa0; u8 pada8[8]; u64 xb0; } B4Gs;
typedef struct { u16 x0; u8 x2; u8 x3; u16 x4; u16 x6; u16 x8; s16 xa; s32 xc; B4Drw *x10; } B4Rq;
extern B4Pk *D_0055C648;
extern u8 D_00573E40[];
extern B4Rq D_0055C680;

void func_0015f488(B4Drw *a) {
    u32 tbl;
    B4Tx *t;
    B4Tc *c;
    B4Gs *q;
    B4Rec *r;
    u8 k;
    tbl = a->x0->x14;
    r = (B4Rec *)(a->x7 * 4 + tbl);
    c = ((B4Tbl *)tbl)->b.x14[a->x7];
    t = r->x10;
    D_0055C648->x3 = 16;
    D_0055C648->x4 = 0;
    D_0055C648->x0 = 6;
    D_0055C648->x20 = (u64)0x9b80 << 33;
    D_0055C648->x30 = 0;
    D_0055C648->x40 = ((u64)16 << 32) | 16;
    D_0055C648->x60.b.lo = 64;
    D_0055C648->x73 = 48;
    D_0055C648->x74 = c->xc;
    D_0055C648->x70 = 64;
    D_0055C648++;
    D_0055C648->x3 = 16;
    D_0055C648->x4 = 0;
    D_0055C648->x0 = 6;
    D_0055C648->x20 = (u64)0x13043600 << 32;
    D_0055C648->x60.b.lo = t->x0;
    D_0055C648->x30 = 0;
    D_0055C648->x40 = t->x4 | ((u64)t->x6 << 32);
    D_0055C648->x73 = 48;
    D_0055C648->x74 = t->x8;
    D_0055C648->x70 = t->x0;
    D_0055C648++;
    D_0055C648->x3 = 96;
    D_0055C648->x4 = 0;
    D_0055C648->x0 = 0;
    q = (B4Gs *)((u32)D_00573E40 | 0x20000000);
    q->x40 = ((u64)t->x2 << 26) | ((u64)t->x3 << 30) | 0x2006E00401313600ULL;
    k = a->x0->x2c;
    if (a->x5) {
        q->x60 = ((u64)k << 4) | 0x50005;
        q->x70 = ((u64)128 << 32) | 0x44;
        q->x80 = a->x0->x0 | ((u64)1 << 32);
    } else {
        if (k > 120) k = 120;
        q->x70 = ((u64)128 << 32) | 0x44;
        q->x60 = ((u64)k << 4) | 0x5800b;
        q->x80 = a->x0->x0;
        q->x90 = a->x0->x30 | ((u64)a->x0->x34 << 8) | ((u64)a->x0->x38 << 16);
    }
    q->xa0 = a->x0->x8;
    q->xb0 = 5;
    __asm__ volatile("sync");
    if (a->x0->x40) {
        D_0055C680.x0 = 0x3600;
        D_0055C680.x2 = 4;
        D_0055C680.x3 = 19;
        D_0055C680.x4 = t->x4;
        D_0055C680.x6 = t->x6;
        D_0055C680.x8 = 0x3700;
        D_0055C680.xa = ((B4Rec *)(a->x7 * 4 + tbl))->xd;
        D_0055C680.xc = a->x6;
        D_0055C680.x10 = a;
    }
}

typedef struct { void *x0; void *x4; } B4Pr;
typedef struct { u8 pad[0x3c]; f32 x3c; } B4Ky;
typedef struct { B4Ky *x0; } B4Kyp;
typedef struct { u8 pad[0x10]; B4Kyp *x10; u8 pad14[0x48 - 0x14]; union { u64 x; struct { u8 b0; s8 x49; } c; } x48; } B4Obj;
typedef struct { B4Obj *x0; u32 x4; u8 pad8[0x28 - 8]; s32 x28; } B4Dsl;
typedef struct B4Ln { struct B4Ln *x0; B4Obj *x4; } B4Ln;
typedef struct { s32 x0; s32 x4; s32 x8; s32 xc; s32 x10; B4Pr x14[2][72]; u8 pad494[4]; B4Obj x498[2][78]; B4Dsl x3558[2][480]; } B4Gl;
typedef struct { u8 pad[0x10]; void *x10; s32 x14; } B4Task;
extern B4Gl D_0055C698; /* src/data/bss_0055.c: u8 D_0055C698[0xda58] */
B4Ln *D_005739F0 ALIGNED(16);
B4Ln D_005736F0[0x60] ALIGNED(16);
void func_00121eb0(void *);
B4Task *func_0015ed80(s32, void *);
B4Task *func_0015ee78(s32, void *);
s32 func_0015f388();
s32 func_0015ff78();

s32 func_00160370(void) {
    s32 i;
    B4Pr *p;
    B4Obj *o;
    B4Ln *n;
    B4Ln *prev;
    B4Ln *q;
    B4Dsl *e;
    B4Task *t;
    s32 v;
    s32 w;
    B4Ln *h;
    s32 c;

    p = D_0055C698.x14[D_0055C698.x0 ^ 1];
    for (i = 0; i < D_0055C698.x10; i++, p++) {
        if (p->x0) {
            func_00121eb0(p->x0);
            p->x0 = 0;
        }
        if (p->x4) {
            func_00121eb0(p->x4);
            p->x4 = 0;
        }
    }
    o = D_0055C698.x498[D_0055C698.x0];
    D_005739F0 = 0;
    for (i = 0; i < D_0055C698.x4; i++, o++) {
        n = &D_005736F0[i];
        n->x0 = 0;
        n->x4 = o;
        prev = 0;
        q = D_005739F0;
        while (q && !(q->x4->x10->x0->x3c < o->x10->x0->x3c)) {
            prev = q;
            q = prev->x0;
        }
        if (!prev) {
            h = D_005739F0;
            D_005739F0 = n;
            n->x0 = h;
        } else {
            n->x0 = prev->x0;
            prev->x0 = n;
        }
    }
    i = 0;
    n = D_005739F0;
    while (n) {
        n->x4->x48.c.x49 = i++;
        n = n->x0;
    }
    e = D_0055C698.x3558[D_0055C698.x0];
    for (i = 0; i < D_0055C698.x8; i++, e++) {
        v = e->x28;
        if ((u32)(v - 59500) >= 1000 && !(e->x0->x48.x & 0x10000)) {
            w = v + e->x0->x48.c.x49;
            e->x28 = w;
            if (v + 499 < w) {
                e->x28 = v + 499;
            } else if (w < v - 500) {
                e->x28 = v - 500;
            }
        }
        if ((e->x4 & 8) || (e->x0->x48.x & 0x20000)) {
            t = func_0015ee78(e->x28, func_0015ff78);
        } else {
            t = func_0015ed80(e->x28, func_0015ff78);
        }
        t->x10 = e;
        t->x14 = 0;
    }
    func_0015ed80(0x5013, func_0015f388);
    func_0015ed80(0x11363, func_0015f388);
    func_0015ee78(0x7fffffff, func_0015f388);
    c = D_0055C698.xc;
    D_0055C698.x0 ^= 1;
    D_0055C698.x10 = c;
    D_0055C698.xc = D_0055C698.x8 = D_0055C698.x4 = 0;
    return 0;
}

f32 func_00162c20(f32 *);
void func_00267370(f32 *, f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
void func_00162c5c(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_00267768(f32 (*)[4], f32 (*)[4], f32);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);

void func_00162d00(f32 *tgt, s32 flip, f32 (*m0)[4], f32 (*m1)[4], f32 *pole, f32 l1, f32 l2, f32 rot, f32 rot2) {
    f32 d[4];
    f32 u[4];
    f32 w[4];
    f32 p[4];
    f32 m[4][4];
    f32 r[4][4];
    f32 n[4][4];
    f32 dist;
    f32 c;
    f32 s;
    f32 x;
    f32 y;
    f32 t;

    p[0] = m0[3][0];
    p[1] = m0[3][1];
    p[2] = m0[3][2];
    d[0] = tgt[0] - p[0];
    d[1] = tgt[1] - p[1];
    d[2] = tgt[2] - p[2];
    dist = func_00162c20(d);
    if (pole) {
        u[0] = pole[0] - p[0];
        u[1] = pole[1] - p[1];
        u[2] = pole[2] - p[2];
        func_00162c20(u);
        func_00267370(w, d, u);
        func_00162c20(w);
        func_00267370(u, w, d);
        func_00162c20(u);
    } else {
        u[0] = -d[1];
        u[1] = d[0];
        u[2] = 0.0f;
        func_00162c20(u);
        func_00267370(w, d, u);
        func_002673b8(w, w);
    }
    m[0][3] = 0.0f;
    m[0][0] = d[0];
    m[0][1] = d[1];
    m[0][2] = d[2];
    m[1][0] = u[0];
    m[1][1] = u[1];
    m[1][2] = u[2];
    m[1][3] = 0.0f;
    m[2][0] = w[0];
    m[2][1] = w[1];
    m[2][2] = w[2];
    m[2][3] = 0.0f;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
    if (rot != 0.0f) {
        sceVu0UnitMatrix(r);
        func_00267768(r, r, rot);
        func_00162c5c(m, m, r);
    }
    if (!m1) {
        sceVu0CopyMatrix(m0, m);
        m0[3][0] = p[0];
        m0[3][1] = p[1];
        m0[3][2] = p[2];
        return;
    }
    c = (dist * dist - l1 * l1 - l2 * l2) / ((l1 + l1) * l2);
    if (c > 1.0f) {
        c = 1.0f;
    } else if (c < -1.0f) {
        c = -1.0f;
    }
    t = 1.0f - c * c;
    if (t < 0.0f) t = 0.0f;
    if (flip) {
        s = -PlatSqrtf(t);
    } else {
        s = PlatSqrtf(t);
    }
    m1[0][2] = 0.0f;
    m1[0][0] = c;
    m1[1][0] = -s;
    m1[0][1] = s;
    m1[0][3] = 0.0f;
    m1[1][1] = c;
    m1[1][2] = 0.0f;
    m1[1][3] = 0.0f;
    m1[2][0] = 0.0f;
    m1[2][1] = 0.0f;
    m1[2][2] = 1.0f;
    m1[2][3] = 0.0f;
    m1[3][0] = l1;
    m1[3][1] = 0.0f;
    m1[3][2] = 0.0f;
    m1[3][3] = 1.0f;
    if (rot2 != 0.0f) {
        sceVu0UnitMatrix(r);
        func_00267768(r, r, rot2);
        func_00162c5c(m1, m1, r);
    }
    y = -(l2 * s) * dist;
    x = (l1 + l2 * c) * dist;
    dist = PlatSqrtf(x * x + y * y);
    y = y / dist;
    x = x / dist;
    n[0][0] = x;
    n[0][1] = y;
    n[0][2] = 0.0f;
    n[0][3] = 0.0f;
    n[1][0] = -y;
    n[1][1] = x;
    n[1][2] = 0.0f;
    n[1][3] = 0.0f;
    n[2][0] = 0.0f;
    n[2][1] = 0.0f;
    n[2][2] = 1.0f;
    n[2][3] = 0.0f;
    n[3][0] = 0.0f;
    n[3][1] = 0.0f;
    n[3][2] = 0.0f;
    n[3][3] = 1.0f;
    func_00162c5c(m0, m, n);
    m0[3][0] = p[0];
    m0[3][1] = p[1];
    m0[3][2] = p[2];
}

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
            if (t >= 0 && func_002408d8(t)) p->x2c = p->x2c + D_00308CDC->xfe;
        }
        break;
    case 1: p->x2c = e->x6c->x48; break;
    case 2: p->x2c = 0; break;
    case 3: p->x2c = e->x6c->x48 * 2; break;
    case 4: p->x2c = e->x6c->x48 * 3; break;
    case 5: p->x2c = e->x6c->x48 * 5; break;
    case 6: p->x2c = D_002E26A0->x6c->x4c; break;
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

typedef struct { u32 x0; u32 *x4; u8 pad8[4]; f32 xc; f32 x10[4]; f32 x20; f32 x24; u8 pad28[4]; f32 x2c; u8 pad30[4]; s32 x34; } B4W51;
typedef struct {
    u32 x0; u8 pad4[0xc]; f32 x10[4]; f32 x20[4]; u8 pad30[0xc]; f32 x3c; f32 x40; f32 x44; f32 x48;
    u8 pad4c[0x144 - 0x4c]; B4W51 *x144;
} B4A51;
extern f32 D_00306840;
f32 sinf(f32);
f32 func_00121b08(f32);
f32 func_00120c88(f32);
void func_001247e8(B4A51 *);
void func_00137688(B4A51 *, f32);
s32 func_00150ec8(B4A51 *);
void func_00151010(B4A51 *);
void func_00151148(B4A51 *);
void func_00151208(B4A51 *);
void func_00267518(f32 *, f32 *, f32 *);

void func_00151268(B4A51 *e) {
    f32 v[4];
    f32 u[4];
    f32 k;
    B4W51 *w = e->x144;
    if (!w) return;
    func_001315c0(D_002E26A0, 0x8003, 0.0f, v);
    if (w->x24 < 1.0f) {
        w->x24 += 0.09999999590218067169189453125f;
        if (1.0f < w->x24) w->x24 = 1.0f;
    }
    w->x2c = func_00121b08(w->x2c);
    e->x40 = e->x48 = e->x44 = w->x20;
    e->x44 *= w->x24;
    switch (w->x0) {
    case 0:
        if (func_00150ec8(e)) break;
        switch (w->x34) {
        case 0: func_00151010(e); break;
        case 1: func_00151148(e); break;
        }
        func_00151208(e);
        break;
    case 1:
        func_00150ec8(e);
        break;
    case 2:
        w->xc -= D_002BBDFC;
        if (!(0.0f < w->xc)) {
            func_001247e8(e);
            e->x144 = 0;
            w->x4 = 0;
            return;
        }
        k = w->xc / 30.0f;
        k = 1.0f - sinf((1.0f - k) * 3.1415928f * 0.5f);
        func_00267560(u, w->x10, k);
        u[1] -= sinf(k * 3.1415928f) * 50.0f;
        func_00137688(e, func_00120c88(e->x3c + (1.0f - k) * 0.52359874546527862548828125f));
        func_00267518(e->x10, v, u);
        if (k < 1.0f) e->x40 = e->x44 = e->x48 = w->x20 * k;
        func_002675a8(e->x20, D_002C58B0);
        break;
    case 3:
        w->xc -= 1.0f;
        if (w->xc <= 0.0f) {
            e->x0 &= ~3;
        } else {
            k = w->xc / D_00306840;
            e->x40 = e->x44 = e->x48 = w->x20 * k;
        }
        func_002675a8(e->x20, D_002C58B0);
        break;
    case 4:
        e->x0 |= 3;
        w->xc -= 1.0f;
        if (w->xc <= 0.0f) {
            k = 1.0f;
            *w->x4 &= ~0x30;
            func_002675a8(e->x20, w->x10);
            w->x0 = 0;
        } else {
            k = 1.0f - w->xc / D_00306840;
            func_002675a8(e->x20, D_002C58B0);
        }
        e->x40 = e->x44 = e->x48 = w->x20 * k;
        break;
    }
}

typedef struct { u32 dir:1; u32 b1:1; u32 mod:2; u32 asp:2; u32 tte:1; u32 tie:1; u32 rest:24; } B4Chcr;
typedef struct { u8 pad[0x18]; s32 x18; } B4Rec2;
typedef struct { u32 x0; } B4X10;
typedef struct {
    u64 x0; u64 x8; B4X10 *x10; u32 x14; s32 x18; u8 pad1c[0x40 - 0x1c]; s32 (*x40)(B4Rq *, s32); s32 x44; s8 x48;
} B4Src2;
typedef struct { B4Src2 *x0; u8 x4; s8 x5; s8 x6; u8 x7; } B4Drw2;
typedef struct { u8 pad[0x10]; B4Drw2 *x10; u32 x14; } B4Dm;
typedef struct { u16 x0; u8 x2; u8 x3; s32 x4; u8 pad8[0x170 - 8]; u64 x170; u8 pad178[8]; u64 x180; } B4Gp;
extern B4Chcr *D_0055C644; /* src/data/bss_0055.c: DmaChcr *D_0055C644 */
extern B4Chcr *D_0055C640; /* src/data/bss_0055.c: DmaChcr *D_0055C640 */
extern u8 D_00351C40[];
extern u8 D_00573AC0[];
void func_0015f798(B4Dm *);
void func_0015fc00(B4Dm *);
s32 func_0015fd20(s32, u32, s32, u64, s32);
void func_00266f38(B4Chcr *, void *);
void func_0015f8c8(B4Drw2 *, s32);

#define CALLFD() do { B4Drw2 *t_ = d->x10; B4Src2 *u_ = t_->x0; func_0015fd20(((B4Rec2 *)(t_->x7 * 4 + u_->x14))->x18, u_->x10->x0, u_->x48, (u64)t_->x4 >> 4, u_->x18); } while (0)
s32 func_0015ff78(B4Dm *d) {
    B4Drw2 *s;
    B4Drw2 *t;
    B4Gp *g;
    s32 r;
    u32 tb;
    u64 a;
    u64 b;
    u32 x;
    u32 st;
    __asm__ volatile("sync");
    r = 2;
    s = d->x10;
    switch (st = d->x14) {
    case 0:
        func_0015f798(d);
        d->x14 = 1; st = 1;
        break;
    case 1:
        func_0015fc00(d);
        if (!(s->x0->x48 & 4)) {
            d->x14 = 2; st = 2;
            break;
        }
        CALLFD();
        d->x14 = st = 4;
        break;
    case 2:
        if (*(u32 *)&s->x4 & 8) {
            b = s->x0->x0;
            a = s->x0->x8;
            __asm__ volatile("sync");
            g = (B4Gp *)((u32)D_00351C40 | 0x20000000);
            g->x180 = a;
            g->x3 = 112;
            g->x0 = 24;
            g->x170 = b;
            g->x4 = 0;
            __asm__ volatile("sync");
            D_0055C644->mod = 1;
            D_0055C644->asp = 0;
            D_0055C644->tte = 0;
            D_0055C644->tie = 0;
            __asm__ volatile("sync");
            func_00266f38(D_0055C644, D_00351C40);
        } else {
            D_0055C648 = (B4Pk *)((u32)D_00573AC0 | 0x20000000);
            func_0015f488((B4Drw *)s);
            func_0015f8c8(s, 0);
            D_0055C648->x3 = 96;
            D_0055C648->x4 = 0;
            D_0055C648->x0 = 0;
            __asm__ volatile("sync");
            D_0055C644->mod = 1;
            D_0055C644->asp = 0;
            D_0055C644->tte = 0;
            D_0055C644->tie = 0;
            __asm__ volatile("sync");
            func_00266f38(D_0055C644, D_00573E40);
        }
        CALLFD();
        if (s->x0->x40) { d->x14 = 3; st = 3; }
        else { d->x14 = 4; st = 4; }
        break;
    case 3:
        r = s->x0->x40(&D_0055C680, s->x0->x44);
        d->x14 = 4; st = 4;
        break;
    case 4:
        tb = s->x0->x14;
        D_0055C640->dir = 1;
        D_0055C640->mod = 1;
        D_0055C640->asp = 0;
        D_0055C640->tte = 1;
        D_0055C640->tie = 0;
        __asm__ volatile("sync");
        func_00266f38(D_0055C640, (void *)((B4Rec2 *)(((u8 *)s)[7] * 4 + tb))->x18);
        d->x14 = 5; st = 5;
        break;
    case 5:
        do {
            do {
                x = *(volatile u32 *)0x10003c00 & 0x1f000003;
            } while (x);
            __asm__ volatile("cfc2 %0, $vi29" : "=r"(x));
        } while (x & 0x100);
        r = 0;
        d->x14 = 6; st = 6;
        break;
    }
    return st != 5 ? r | 0x20 : r;
}

typedef struct { u32 x0; u32 x4; s32 x8; u32 xc; s32 x10; u32 x14; s32 x18; u32 x1c; s32 x20; u32 x24; s32 x28; s32 x2c; s32 x30; s32 x34; } B4Hd;
typedef struct { u8 pad[3]; u8 x3; s32 x4; s32 x8; s32 xc; } B4Me;
typedef struct { u16 x0; u16 x2; s32 x4; s32 x8; s32 xc; B4Me e[1]; } B4Mt;
typedef struct { u16 x0; u16 x2; u32 x4; s32 x8; s32 xc; } B4Mb;
typedef struct { s32 x0; s32 x4; s32 x8; } B4Mk;
typedef struct { u8 pad[0x14]; s32 x14; u8 pad18[4]; s32 x1c; u8 pad20[4]; s32 x24; s32 x28; u8 pad2c[4]; s32 x30; u8 pad34[4]; s32 x38; B4Mk *x3c; } B4Mo;
extern s32 D_005739F8[];
#include "data/pieces/D_00351BC8.h"
void FlushCache(s32);
s32 printf(const char *, ...);
void func_001680d8(B4Hd *);
s32 func_001681b8(B4Hd *, u32);
void func_00175708(B4Hd *, s32);

void func_00161a08(B4Hd *h) {
    B4Mt *t;
    B4Mt *t2;
    B4Mb *b;
    u8 *c;
    u8 *m;
    s32 *o;
    s32 *p;
    B4Mo *q;
    B4Mk *k;
    s32 i;
    u32 j;
    s32 r;
    u8 v;
    u8 *a;
    u8 *a2;
    s32 *pp;
    s32 *pq;
    s32 *pr;

    t2 = 0;
    b = 0;
    c = 0;
    t = 0;
    m = 0;
    FlushCache(0);
    o = D_005739F8;
    switch (h->x0) {
    case 0x4a424f4d:
        t = (B4Mt *)((u8 *)h + h->x20);
        t->x4 = (s32)t + t->x4;
        t->x8 = (s32)t + t->x8;
        if (h->x2c) {
            t2 = (B4Mt *)((u8 *)h + h->x28);
        }
        goto common;
    case 0x564e454d:
        t = (B4Mt *)((u8 *)h + h->x20);
        t->x4 = 0;
        t->x8 = (s32)h;
    common:
        b = (B4Mb *)((u8 *)h + h->x8);
        c = (u8 *)h + h->x10;
        m = (u8 *)h + h->x18;
        break;
    case 0x4e544d4d:
        break;
    case 0x41584554:
        printf("*** TEXTURE ANIM ***\n");
        break;
    }
    func_001680d8(h);
    if (h->x0 == 0x41584554) return;
    a = c;
    if (t) {
        for (i = 0; i < t->xc; i++) {
            pp = &t->e[i].xc;
            *pp = (s32)t + *pp;
        }
        for (i = 0; i < t->xc; i++) {
            pq = &t->e[i].x8;
            v = ((u8 *)pq)[-4];
            ((u8 *)pq)[-5] = v;
            pq[-1] = (s32)&b[v];
            *pq = (s32)&b[*pq];
        }
        for (j = 0; j < h->xc >> 4; j++) {
            b[j].x8 = (s32)a;
            a += b[j].x0 * 16;
        }
        a2 = m;
        for (j = 0; j < h->xc >> 4; j++) {
            b[j].xc = (s32)a2;
            a2 += 1024;
        }
        *(s32 *)&t->e[t->xc] = func_001681b8(h, 0x454e4f42);
    }
    if (t2) {
        t2->x0 = t->x0;
        t2->x4 = t->x4;
        t2->x8 = t->x8;
        for (i = 0; i < t2->xc; i++) {
            pr = &t2->e[i].xc;
            pr[-2] = 0;
            pr[-1] = 0;
            *pr = (s32)t2 + *pr;
        }
    }
    if (h->x34) {
        o = (s32 *)((u8 *)h + h->x30);
        for (p = o; *p != -1; p++) {
            q = (B4Mo *)((u8 *)o + *p);
            *p = (s32)q;
            q->x14 = (s32)q + q->x14;
            q->x1c = (s32)q + q->x1c;
            q->x24 = (s32)q + q->x24;
            q->x28 = (s32)q + q->x28;
            q->x30 = (s32)q + q->x30;
            q->x38 = (s32)q + q->x38;
            q->x3c = (B4Mk *)((s32)q + (s32)q->x3c);
            for (k = q->x3c; k->x0 != -1; k++) {
                k->x8 = (s32)q + k->x8;
            }
        }
        *p = 0;
    }
    h->x8 = (s32)b;
    h->x10 = (s32)c;
    h->x18 = (s32)m;
    h->x20 = (s32)t;
    h->x28 = (s32)t2;
    h->x30 = (s32)o;
    r = func_001681b8(h, 0x4c535255);
    if (r) func_00175708(h, r);
    D_00351BC8(0);
}
#include "data/bss_0054_mixed.h"
#include "data/bss_0057_mixed.h"
#include "data/data_002C.h"
#include "data/data_0030.h"
#include "data/data_0035.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDFC.h"
