#include "common.h"
#include "data/bss_0051.h"
#include "data/bss_0052.h"

/* shared declarations */
typedef struct S31b0 { s32 f0, f4; } S31b0;
extern S31b0 D_002E31B0;
extern void *D_002E26A0[3];
extern void *D_00524F58[]; /* src/data/bss_0052.c: s32 D_00524F58[0x4] */
extern u32 D_002C5958;
extern u32 D_002E27C8;
extern s32 D_002E31B8;

typedef struct { u8 pad[0x10]; volatile s32 n; } Q14;
typedef struct {
    u8 pad0[4];
    s32 f4;
    s32 f8;
    u8 padc[8];
    u8 f14, f15, f16, f17;
    u8 pad18[0xe0 - 0x18];
    Q14 a;
    u8 pad2[0x150 - 0xf4];
    Q14 b;
} D14;
extern D14 D_002E2FD8;

typedef struct { u8 pad[0x48e]; u8 f48e[3]; u8 pad491[0x844 - 0x491]; s8 f844[3]; } W17;
extern W17 *D_00304BE8;

typedef struct { u8 b0; u8 pad[19]; } T23;
typedef struct { u8 pad[7]; u8 b7; u8 pad8[0x14]; T23 *f1c; } I23;
typedef struct { u8 pad[0x134]; I23 *f134; u8 pad138[0x3ac - 0x138]; u32 f3ac; } E23;

extern s32 func_00122ff8(void *);
extern f32 func_0012ec60(s32, s32, f32 *);
extern void func_00267530(void *, void *, void *);
extern void func_002675a8(void *, void *);
extern void *func_00123158(void *, void *);
extern void func_0012bd98(void *, s32, u32, f32 *);
extern f32 func_00120c88(f32);
extern void func_00121fc4(f32 *, f32 *);
extern void func_0011ef10(s32, void *);
extern f32 func_00121748(f32 *, f32 *);
s32 func_0012ee70(E23 *e, s32 i);

#include "data/types/text_00120000_h31_p.h"
extern A2 D_002C6814[];
extern void *D_002C64A0;
extern void *D_002E26AC;
extern void func_001372a0(void);
extern void func_00138738(void);
extern s32 func_0011ef38(void *);
extern void func_00123790();

void func_00124b90(void) {
    s32 i;
    for (i = 0; i < 96; i++) D_002C6814[i].f0 = 0;
    D_002E26AC = &D_002C64A0;
    for (i = 0; i < 3; i++) D_002E26A0[i] = 0;
    func_001372a0();
    func_00138738();
    if (func_0011ef38(func_00123790) == 0)
        func_0011ef10(0x27cb9, func_00123790);
}

typedef struct { u8 pad[0x70]; s32 f70; u8 pad74[0x3c0 - 0x74]; f32 f3c0[4]; } E2;
typedef struct { u8 pad[0xf0]; f32 ff0; } G1;
extern G1 *D_00308CDC;
extern void func_00130340(E2 *, s32, f32);
extern void func_00130578(E2 *, s32, f32);
extern void func_00267560(f32 *, f32 *, f32);
extern void func_001333e0(E2 *, s32, s32);

void func_00125be8(E2 *e, s32 a1) {
    switch (e->f70) {
    case 2:
        func_00130340(e, 0x100008a, 8.0f);
        func_00130578(e, 0x40000006, 0.0f);
        func_00267560(e->f3c0, e->f3c0, D_00308CDC->ff0);
        break;
    case 8:
        func_00130340(e, 0x100008a, 8.0f);
        func_00130578(e, 0x40000075, 8.0f);
        func_00267560(e->f3c0, e->f3c0, D_00308CDC->ff0);
        break;
    default:
        func_00130340(e, 0x100003d, 8.0f);
        func_00130578(e, 0x40000000, 0.0f);
        break;
    }
    func_001333e0(e, 0, a1);
}

extern float fabsf(float);
typedef struct { u8 pad[0x10]; f32 f10[16]; u8 pad50[0x3c4 - 0x50]; f32 f3c4; } E3;

void func_00125cf0(E3 *e, f32 k, f32 lim) {
    f32 v[4];
    f32 t, r;
    if (func_00122ff8((void *)D_002E31B0.f0) == 0) return;
    func_0012ec60(D_002E31B0.f0, D_002E31B0.f4, v);
    v[1] += 100.0f;
    func_00267530(v, v, e->f10);
    if (fabsf(v[1]) > 50.0f) {
        t = e->f3c4 + v[1] * k;
        if (t < -lim) r = -lim;
        else if (lim < t) r = lim;
        else r = t;
        e->f3c4 = r;
    }
}


#include "data/types/text_00120000_h31.h"
extern A6 D_004F7820[3];
extern B6 D_004F7C10[3];
extern D6 D_004F8270[];
extern u8 D_004F82D0[];
extern void (*D_00351BC8)(s32);
extern void func_001284a0(A6 *, s32);
extern void func_00128738(B6 *, s32);
extern void *func_0011fb38(s32, s32, void *);
extern void func_0011fb48(void *, s32, void *);
extern void func_0011fb78(void *, s32, void *);
extern void func_00267b08(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void func_00128440();

void func_00128b20(void) {
    s32 i;
    u8 *q, *d, *b;
    for (i = 0; i < 3; i++) {
        func_001284a0(&D_004F7820[i], i);
        func_00128738(&D_004F7C10[i], i);
    }
    q = (u8 *)D_004F8270;
    d = q;
    q += 16;
    b = q;
    q = func_0011fb38(0x47, 0x50000, b + 16);
    q = func_0011fb38(0x48, 0x50000, q);
    q = func_0011fb38(0x14, 0x60, q);
    func_0011fb48(b, 1, q);
    func_0011fb78(d, 7, q);
    D_00351BC8(0);
    func_00267b08(D_004F82D0, 32768.0f, 1.0f, 1.0f, 2048.0f, 2048.0f, 1.0f, 65535.0f, 1.0f, 65535.0f);
    func_0011ef10(0x1fbcf, func_00128440);
}

typedef struct { f32 *m; f32 *rot; } R8;
extern f32 D_002C58D0[];
extern void func_002678b8(f32 *, f32 *, f32 *);
extern void func_002672f8(f32 *, f32 *, f32 *);

void func_00129270(R8 *r) {
    f32 v[4];
    f32 m[16];
    s32 i;
    for (i = 0; i < 3; i++) {
        v[i] = func_00120c88(r->rot[i] / 180.0f * 3.1415928f);
    }
    v[3] = 0.0f;
    func_002678b8(m, D_002C58D0, v);
    func_002672f8(r->m, m, r->m);
}

typedef struct { f32 c[4]; s32 f10, f14, f18, f1c; f32 f20; s32 f24; } L9;
extern s32 D_002BC080[4];
extern s32 D_002BC090;
extern s32 D_002BC094;
extern f32 D_002BC098;
extern s32 D_002BC09C;
extern s32 D_002BC0A0;
extern s32 D_002BC0A4;
extern s32 D_002BBE04;

void func_0012b450(L9 **pp) {
    L9 *p = *pp;
    s32 i;
    for (i = 0; i < 4; i++) D_002BC080[i] = p->c[i] * 128.0f;
    D_002BC090 = p->f10;
    D_002BC094 = p->f14;
    D_002BC098 = func_00120c88(p->f20 / 180.0f * 3.1415928f);
    D_002BC09C = p->f24;
    D_002BC0A0 = p->f18;
    D_002BC0A4 = p->f1c;
    D_002BBE04 = 1;
}

typedef struct { u8 pad[0x14]; u8 *f14; } N2;
extern u8 D_00524F20[32];
extern u8 D_00514F20[];
extern N2 *func_0012b7a8();
extern void *memset(void *, s32, u32);

N2 *func_0012b888(void) {
    N2 *n = func_0012b7a8();
    s32 i;
    u8 *p;
    for (i = 0; i < 32; i++) {
        if (D_00524F20[i] == 0) break;
    }
    D_00524F20[i] = 1;
    p = D_00514F20 + i * 2048;
    memset(p, 0, 2048);
    n->f14 = p;
    return n;
}

typedef struct { u32 f0; u8 pad[0x15c - 4]; s32 f15c; u8 pad160[0x324 - 0x160]; f32 f324; u8 pad328[0x39e - 0x328]; u8 f39e; } E10;
extern s32 func_001232f0(E10 *);
extern s32 func_0012bd30(E10 *);
extern void func_00162218(s32, s32, f32 *, f32);

void func_0012c010(E10 *e, s32 bit, s32 b) {
    f32 v[4];
    if (func_001232f0(e) && func_0012bd30(e)) {
        func_00162218(e->f15c, b, v, 1.0f);
        if ((u8)(e->f39e - 10) < 3 && !(e->f0 & 0x400000)) v[1] = e->f324;
        func_0012bd98(e, e->f39e, (1 << (bit % 8)) | (0x80000000 >> (bit / 8)), v);
    }
}

typedef struct { u8 pad[0x50]; f32 f50[4]; u8 pad60[0x10]; s32 f70; u8 pad74[0x2d4 - 0x74]; f32 f2d4; u8 pad2d8[0x39e - 0x2d8]; u8 f39e; } E12;
extern void func_00146c98(E12 *, s32);

void func_0012c698(E12 *e) {
    f32 v[4];
    if ((u8)(e->f39e - 11) < 2) {
        func_002675a8(v, e->f50);
        v[1] = e->f2d4;
        switch (e->f70) {
        case 2: case 3: case 4: case 5:
            func_0012bd98(e, e->f39e, 0x80000008, v);
            func_00146c98(e, 10);
            break;
        case 10:
        case 13:
            func_0012bd98(e, 10, 0x8000008, v);
            break;
        }
    }
}

extern s32 D_002E3160[];
extern volatile u32 D_00524F44; /* src/data/bss_0052.c: u32 D_00524F44 */
extern void func_0012cb40(Q14 *, s32, s32);

static inline s32 add(Q14 *q, s32 x) {
    s32 i = q->n++;
    func_0012cb40(q, i, x);
    return i;
}

void func_0012cb78(s32 v, s32 x) {
    D14 *d = &D_002E2FD8;
    s32 i = add(&d->a, x);
    s32 j = add(&d->b, x);
    D_002E3160[j] = v;
    D_00524F58[i] = (void *)v;
    D_00524F44 |= 0x10;
}

typedef struct { u8 pad[0x370]; u64 f370; } O16;
typedef struct { u8 pad[0x30]; u32 f30; } P16;
typedef struct { u8 pad[0x14c]; P16 *f14c; u8 pad150[0x14]; s32 f164; } E16;
extern s32 D_002BC128;
extern s32 D_002BC130;

void func_0012d068(E16 *e, u32 *fl) {
    D14 *d = &D_002E2FD8;
    s32 v;
    if (D_002BC128 == 6 || (D_002BC128 == 16 && D_002BC130 == 24)) {
        d->f14 = 98;
    } else if (((D_002E27C8 >> 2) & 1) && func_00122ff8((void *)D_002E31B0.f0)
               && ((s32)(((O16 *)D_002E31B0.f0)->f370 >> 37) & 3) == 2 && e->f164 == 110
               && (e->f14c->f30 & ~0x102)) {
        d->f14 = 99;
    } else {
        d->f14 = 1;
    }

    d->f15 = 66;
    d->f16 = 66;
    d->f17 = 66;
    v = ((*fl >> 4) & 1) ? -2 : -1;
    d->f4 = d->f8 = v;
}

extern D17 D_002E30F0;
extern s32 D_00524F50;
extern s32 func_00132fe0(s32);

void func_0012d368(s32 a0, s32 a1, s32 *fl) {
    D17 *d = &D_002E30F0;
    s32 mask = -1;
    s32 i;
    for (i = 0; i < 3; i++) {
        s32 id = D_00304BE8->f844[i];
        if (id == -1) {
            d->f14[i] = 66;
        } else {
            d->f14[i] = id * 3 + func_00132fe0(id) + 6;
            if (fl[id]) mask &= ~(1 << i);
            D_00524F50 = 1;
        }
    }
    d->f4 = d->f8 = mask;
}

typedef struct { u8 pad[0x10]; s32 f10; u8 f14[4]; } D18;
typedef struct { u32 f0; } E18;
extern D18 D_002E30B8;
extern s32 D_002E3138;
extern s32 func_0013daa8(s32);
extern s32 func_0012f040(E18 *, s32);

void func_0012d818(void) {
    s32 i, n, k;
    u8 id;
    E18 *e;
    D18 *d = &D_002E30B8;
    n = 0;
    for (i = 0; i < 3; i++) {
        id = D_00304BE8->f48e[i];
        if (id == 0xff) continue;
        k = func_0013daa8(id);
        if (k < 0) continue;
        e = D_002E26A0[k];
        if (!func_0012f040(e, -1)) continue;
        if (!(e->f0 & 0x8000)) continue;
        d->f14[n] = id + 56;
        D_00524F58[n] = e;
        n++;
    }
    d->f10 = n;
    D_002E3138 = 1;
}

extern volatile s32 D_00524F48; /* src/data/bss_0052.c: s32 D_00524F48 */
extern s32 D_00524F4C;
extern void func_0023b4b8(s32);

s32 func_0012e970(void) {
    s32 ch;
    s32 cur = D_00524F48;
    ch = D_00524F4C;
    ch ^= cur;
    D_00524F4C = cur;
    if (ch & 1) {
        if (cur & 1) {
            func_0023b4b8(3);
            D_00524F48 &= ~4;
        } else {
            func_0023b4b8(2);
            D_00524F48 |= 4;
        }
    } else if (ch & 2) {
        if (cur & 2) {
            if (!(cur & 4)) {
                func_0023b4b8(1);
                D_00524F48 |= 4;
            }
        } else if (cur & 4) {
            func_0023b4b8(0);
            D_00524F48 &= ~4;
        }
    }
    return 0;
}

typedef struct { u16 h0; u16 h2; f32 f4, f8, fc; } P21;
typedef struct { u8 pad[5]; u8 b5; u8 pad6[0xe]; P21 *f14; } I21;
typedef struct { u8 pad[0x10]; f32 f10[12]; f32 f40, f44; u8 pad48[0x134 - 0x48]; I21 *f134; } E21;
extern P21 *func_0015c960(E21 *, s32, s32, s32);
extern void func_001315c0(E21 *, s32, f32 *, f32);

f32 func_0012eba0(E21 *e, s32 a, s32 b, s32 c, f32 *out) {
    P21 *p = func_0015c960(e, a, b, c);
    f32 r;
    if (!p) {
        I21 *i = e->f134;
        if (i && i->b5) p = i->f14;
    }
    if (!p) {
        func_002675a8(out, e->f10);
        r = 0.0f;
    } else {
        func_001315c0(e, p->h2, out, p->f4);
        out[1] -= p->f8 * e->f44;
        r = p->fc * e->f40;
    }
    out[3] = 1.0f;
    return r;
}

typedef struct { u8 pad[0x10]; f32 f10[16]; } E22;

static inline f32 fmx(f32 a, f32 b) { return (b < a) ? a : b; }

f32 func_0012ed88(E22 *e, S31b0 *s, f32 *pos, f32 *out) {
    f32 r = func_0012ec60(s->f0, s->f4, pos);
    f32 y, w;
    func_00267530(out, pos, e->f10);
    if (0.0f < out[1]) {
        y = 0.0f;
        if (0.0f < out[1] - r) y = out[1] - r;
    } else {
        f32 t = out[1] + r;
        y = (t < 0.0f) ? t : 0.0f;
    }
    out[1] = 0.0f;
    func_00121fc4(out, out);
    w = fmx(out[3] - r, 0.0f);
    out[1] = y;
    out[3] = w;
    return w;
}

s32 func_0012ee70(E23 *e, s32 i) {
    I23 *m = e->f134;
    if (i < 0) {
        if (!m || !m->b7) return 0;
        i = 0;
    } else {
        if (!m || !m->b7) return -1;
        i++;
    }
    for (; i < e->f134->b7; i++) {
        if (!(e->f3ac & (1 << i)) && !(e->f134->f1c[i].b0 & 0xf)) return i;
    }
    return -1;
}

typedef struct { u8 pad[0x10]; f32 f10[4]; } T24;
extern f32 func_00120bf8(f32 *);

T24 *func_0012ef30(void *e, f32 *mat, f32 *dir, f32 maxd) {
    T24 *p, *best = 0;
    f32 bd = maxd;
    f32 d;
    f32 v[4];
    for (p = func_00123158(e, 0); p; p = func_00123158(e, p)) {
        func_00267530(v, p->f10, mat);
        d = func_00120bf8(v);
        if (d < maxd) {
            d *= (1.0f - func_00121748(v, dir)) * dir[3] + 1.0f;
            if (best == 0 || d < bd) {
                bd = d;
                best = p;
            }
        }
    }
    return best;
}

typedef struct { f32 a[4]; f32 b[4]; u8 pad[16]; s16 h30; s16 pad2; u8 pad3[12]; } S0f8;
extern s32 func_00119788(void *);
extern s32 func_00119688(void *);
extern void func_00118648(void *);

s32 func_0012f0f8(void *p, void *q, u32 mode) {
    S0f8 s;
    u8 r;
    func_002675a8(s.a, p);
    func_00267530(s.b, q, p);
    r = 0;
    s.a[3] = 1.0f;
    s.b[3] = 1.0f;
    switch (mode) {
    case 0:
        r = func_00119788(&s) < 0;
        break;
    case 1:
        r = func_00119688(&s) < 0;
        break;
    case 2:
        func_00118648(&s);
        if (s.h30 < 0) r = (u32)func_00119688(&s) >> 31;
        break;
    }
    return r;
}

extern P5c0 D_00524F80[];
extern P5c0 *D_00525288; /* src/data/bss_0052.c: s32 D_00525288 */
extern s32 D_0052528C;
extern void func_0012f3d0(P5c0 *);
extern void func_0012f560(P5c0 *);

void func_0012f5c0(P5c0 *e) {
    P5c0 *c = D_00525288;
    if (c - D_00524F80 < D_0052528C - 1) {
        D_00525288 = c + 1;
        *e = c[1];
        return;
    }
    func_0012f3d0(e);
    if (e->a) {
        func_0012f560(e);
        return;
    }
    if (D_00525288 != D_00524F80) {
        D_00525288 = D_00524F80;
        *e = D_00524F80[0];
    }
}

typedef struct { u8 pad[0x70]; s32 f70; } Gb20;
typedef struct { u32 f0; u8 pad[28]; } Tb20;
extern Tb20 D_00350D88[];
extern s32 D_00524F78;
extern s32 D_002E31BC;
extern void func_001337e0(s32, s32, s32);
extern void func_0011d768(s32);
extern void func_00123030(Gb20 *, s32, s32);
extern void func_0017ef40(s32);
extern void func_0012fa98(void);

void func_0012fb20(S31b0 *e, s32 m) {
    switch (m) {
    case 3:
        func_001337e0(3, e->f0, 0);
        if ((D_00350D88[((Gb20 *)D_002E26A0[0])->f70].f0 >> 2) & 1) func_0011d768(68);
        break;
    case 4:
        D_00524F78 = 0;
        break;
    }
    if (D_002E26A0[0]) func_00123030(D_002E26A0[0], e->f0, e->f4);
    if (m >= 3) func_0017ef40(e->f0);
    D_002E31B0 = *e;
    D_002E31B8 = m;
    D_002E31BC = 0;
    func_0012fa98();
}

typedef struct { s32 type; u16 a; u16 b; s32 c; s32 d; } Ec28;
typedef struct { u8 pad0[0x15c]; s32 f15c; u8 pad160[8]; s32 f168; u8 pad16c[0x1d4 - 0x16c]; s32 *f1d4; } Oc28;
extern s32 func_00164f18(s32, s32, Ec28 *, s32);
extern void func_00146ff0(Oc28 *, u16, u16, s32);

void func_00130c28(Oc28 *e) {
    Ec28 buf[8];
    s32 n, j;
    n = func_00164f18(e->f15c, e->f1d4[e->f168], buf, 8);
    for (j = 0; j < n; j++) {
        switch (buf[j].type) {
        case 0:
            if (!((D_002C5958 >> 8) & 1)) func_0012c010((E10 *)e, buf[j].a, buf[j].b);
            break;
        case 1:
            if (!((D_002C5958 >> 10) & 1)) func_00146ff0(e, buf[j].a, buf[j].b, buf[j].c);
            break;
        }
    }
}

typedef struct { u8 pad0[0x164]; s32 f164; s32 f168; u8 pad16c[0x1d4 - 0x16c]; s32 *f1d4; } Od20;
extern f32 func_0013fe10(Od20 *);
extern void func_00167698(s32);

f32 func_00130d20(Od20 *e) {
    f32 t;
    if ((u32)(e->f164 - 21) >= 2) return -1.0f;
    t = func_0013fe10(e);
    func_00167698(e->f1d4[e->f168]);
    if (e->f164 == 21) t = 1.0f - t;
    return (t < 0.0f) ? 0.0f : ((1.0f < t) ? 1.0f : t);
}

typedef struct Ob50 Ob50;
typedef struct { u32 f0; u8 pad4[8]; void (*fc)(Ob50 *); } Sb50;
struct Ob50 { u32 f0; u8 pad4[0x15c]; u64 f160; u8 pad168[0x178 - 0x168]; s32 f178; Sb50 f17c; };
extern s32 func_00131ab0(Ob50 *);
extern void func_00131500(Ob50 *);

void func_00131b50(Ob50 *e) {
    Sb50 *s;
    e->f160 &= ~0x80;
    if (!func_00131ab0(e)) return;
    if (e->f178 <= 0) return;
    s = &e->f17c;
    if (s->f0 & 0x40000000) e->f0 &= ~4;
    if (s->f0 & 0x100000) func_00131500(e);
    if (s->fc) s->fc(e);
    e->f160 |= 0x80;
}

/* needs make: uses rodata */

typedef struct { u8 pad[0x30]; f32 f30[4]; u8 pad40[0x30]; s32 f70; u8 pad74[0x164 - 0x74]; s32 f164; u8 pad168[0x2da - 0x168]; u16 f2da; } E1;
extern u32 D_002E31A8;
extern f32 D_004F7800[];
extern s32 func_00137618(E1 *, s32);
extern void func_00105a30(s32, s32, f32 *);

s32 func_00125a28(s32 a0) {
    E1 *e;
    f32 buf[4];
    if (D_002E31B8 == 3) goto ret0;
    if (D_002C5958 & 0x12000) return 0;
    if ((D_002E31A8 >> 1) & 1) goto ret0;
    e = D_002E26A0[0];
    if (a0 & 1) {
        if (!func_00137618(e, 3)) return 0;
        func_00105a30(-1, e->f2da, buf);
        if (func_00121748(e->f30, buf) > -0.7f) return 0;
        if (func_00121748(D_004F7800, buf) > -0.7f) return 0;
    }
    if (a0 & 2) {
        switch (e->f164) {
        case 3: case 7: case 8:
        ret0:
            return 0;
        case 1: case 2: case 4: case 5: case 6: case 9: case 10: case 11:
            break;
        default:
            return 0;
        }
    }
    if (a0 & 4) {
        if (e->f70) return 0;
    }
    return 1;
}

typedef struct { u8 pad[8]; u32 *f8; } O070;

u32 func_00130070(O070 *o, u32 v, s32 a2, s32 a3) {
    u32 *t;
    u32 w;
    u32 n, r;
    if ((v & 0x20000000) || !(t = o->f8)) return v;
    r = v & 0xffff;
    w = t[r];
    n = w & 0xfff;
    v &= 0xffff0000;
    if (n == 0xfff) return v | 0x200000;
    r = n;
    switch ((w >> 12) & 7) {
    case 1:
        r = n | 0x10000000;
        break;
    case 3:
        if (a2) {
            if (!((D_002C5958 >> 12) & 1) && a3) r = n + 2;
            else r = n + 1;
        }
        break;
    case 0:
        r = n | 0x8000000;
        break;
    case 4:
        if (!((D_002C5958 >> 12) & 1)) {
            if (a3 && a2) r = n + 1;
        }
        break;
    case 2:
        break;
    }
    if ((w >> 15) & 1) v |= 0x4000000;
    return r | v;
}
#include "data/bss_004F_mixed.h"
#include "data/bss_004F_typed.h"
#include "data/data_002B.h"
#include "data/data_002E.h"
#include "data/pieces/D_002BC080.h"
#include "data/pieces/D_002C5958.h"
