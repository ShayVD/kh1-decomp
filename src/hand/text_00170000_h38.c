/* Hand-matched functions, 0x001743b0..0x001803f0 (worker 38).
 * The ones that need -fno-strict-aliasing are in nostrict/text_00170000_h38.c. */
#include "common.h"

typedef int u128 __attribute__((mode(TI)));
typedef struct { f32 x, y, z; } V3;
typedef struct { f32 x, y, z, w; } V4;
typedef union { V4 v; u128 q; } V4A;

/* --- actor state handlers (Wk = owner, Ob = actor) --- */
typedef struct Prm {
    s32 x0;         /* 0x00 */
    u8 pad4[0x10];
    f32 x14;        /* 0x14 */
    f32 x18;        /* 0x18 */
    f32 x1c;        /* 0x1C */
    f32 x20;        /* 0x20 */
} Prm;
typedef struct { u8 pad[0xc]; Prm *xc; } P160;
typedef struct { u8 pad[0x50]; f32 x50; } P40;

typedef struct Ob {
    u8 pad0[0x38];
    u64 flags;      /* 0x38 */
    P40 *x40;       /* 0x40 */
    u8 pad44[4];
    s32 x48;        /* 0x48 */
    s32 x4c;        /* 0x4C */
    u8 pad50[0x68 - 0x50];
    f32 x68;        /* 0x68 */
    u8 pad6c[0x160 - 0x6c];
    P160 *x160;     /* 0x160 */
    s32 x164;       /* 0x164: sub-state */
} Ob;

typedef struct Wk {
    u8 pad0[0x144];
    Ob *x144;       /* 0x144 */
} Wk;

/* the object D_00575894 points to */
typedef struct Actor {
    u8 pad0[0x3c];
    f32 x3c;        /* 0x3C */
    u8 pad40[0x30];
    s32 x70;        /* 0x70: state */
    u8 pad74[0xd0 - 0x74];
    V4 xd0;         /* 0xD0 */
} Actor;

/* camera path (D_00362438 points to one) */
typedef struct { f32 x, y, z, len; } Seg;
typedef struct Path {
    s32 n;          /* 0x00 */
    u8 pad4[4];
    f32 x8;         /* 0x08 */
    u8 padc[8];
    f32 x14;        /* 0x14 */
    s32 flags;      /* 0x18 */
    u8 pad1c[4];
    Seg seg[1];     /* 0x20 */
} Path;

/* camera state at D_00575940 */
typedef struct Cam {
    V4 x0;          /* 0x00 */
    V4 x10;         /* 0x10 */
    V4 x20;
    V4 x30;         /* 0x30 */
    s32 x40;        /* 0x40 */
    s32 x44;
    f32 x48;        /* 0x48 */
    f32 x4c;
    f32 x50;        /* 0x50 */
    f32 x54;        /* 0x54 */
    u8 pad58[4];
    f32 x5c;        /* 0x5C */
    u8 pad60[4];
    u8 x64;         /* 0x64 */
    u8 x65;         /* 0x65 */
    u8 x66;         /* 0x66 (D_005759A6) */
} Cam;

typedef struct { s32 x0; f32 x4; u8 pad8[8]; V4 x10; } S920;
typedef struct { u32 x0; u32 x4; } Pad;

extern Actor *D_00575894; /* src/data/bss_0057.c: void *D_00575894 */
extern s32 D_00575890;
extern f32 D_005758C4;
extern V4 D_005758D0; /* src/data/bss_0057.c: f32 D_005758D0[4] */
extern V4 D_005758E0; /* src/data/bss_0057.c: f32 D_005758E0[4] */
f32 D_0057590C ALIGNED(4);
extern S920 D_00575920;
extern Cam D_00575940;
u8 D_005759A6 ALIGNED(2);
extern V4 D_00575970;
extern f32 D_002BBDFC;
extern Pad D_002C5BB0;
extern u64 D_002C5BB8;
extern u8 D_002C58D0[];
extern V4 D_002E2780;
extern V4 D_002E2790;
extern s32 D_002E27A8;
extern void *D_00362434;
extern Path *D_00362438;
extern void *D_0036243C;
extern void *D_0036244C;
extern Path *D_00362450;
extern void *D_00362454;
extern V4 D_00362580;
extern V4 D_00362590;
extern f32 D_003623F4;
extern f32 D_003623F8;
extern f32 D_003624B8;
extern V4 D_00362620;
extern V4 D_00362630;
extern V4 D_00362680;
extern f32 D_00362684;
extern u8 D_0035C2B0[];
extern u8 D_0035C410[];

s32 func_00171a88(Wk *, Ob *, s32);
f32 func_00171aa8(f32, f32);
s32 func_00171ae8(Wk *, Ob *);
s16 *func_00171b80(Wk *, Ob *, s32);
void func_00170f90(void);
void func_00170fa8(Wk *, Ob *, void *, void *, f32);
void func_00148a40(Wk *, s32);
s32 func_0016b670(Wk *, Ob *, s32, s32);
s32 func_0016c480(Wk *, Ob *, s32, s32);
s32 func_0016c650(Wk *, Ob *, s32, s32);
s32 func_0016cb98(Wk *, Ob *, s32, s32);
s32 func_0016d040(Wk *, Ob *, s32, s32);
s32 func_0016d2d0(Wk *, Ob *, s32, s32);
s32 func_0016d768(Wk *, Ob *, s32, s32);
f32 func_00162950(V3 *, void *);
void func_0011d768(s32);
f32 func_00120bf8(V4 *);
f32 func_00120c88(f32);
void func_00121fc4(V4 *, V4 *);
f32 func_00124d28(V4 *, V4 *);
s32 func_001375d8(Actor *);
void func_00176f08(s32, f32);
s32 func_00177258(Actor *);
s32 func_00177608(V4 *, V4 *, V4 *);
void func_0017b4f8(s32 *, f32 *, f32);
s32 func_0017b7e8(void);
void func_0017c4c8(void);
void func_0017c550(void);
void func_0017d570(s32);
void func_00182870(void);
void func_002672f8(V4 *, void *, V4 *);
void func_00267370(V4A *, V4A *, V4A *);
void func_002673b8(V4A *, V4A *);
void func_00267518(V4 *, V4 *, V4 *);
void func_00267530(V4 *, V4 *, V4 *);
void func_00267560(V4 *, V4 *, f32);
void func_002675a8(V4 *, V4 *);
void func_00267810(V4 *, void *, f32);
void sceVu0MulMatrix(V4A *, V4A *, V4A *);
s32 *func_001803b8(void *);
s32 *func_001803c0(s32 *, s32);

s32 func_001743b0(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 39)) return 0;
        if (!((s32)(o->flags >> 2) & 1)) return 0;
        return func_0016b670(w, o, a2, 1);
    case 2:
        func_00148a40(w, 0);
        func_0016b670(w, o, a2, 2);
        func_00170fa8(w, o, func_00170f90, D_0035C2B0, 30.0f);
        return 1;
    }
    return 1;
}

s32 func_001744b8(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 40)) return 0;
        return func_0016c480(w, o, a2, 1);
    case 2:
        func_0016c480(w, o, a2, a3);
        return 1;
    }
    return 1;
}

s32 func_00174570(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 41)) return 0;
        return func_0016c650(w, o, a2, 1);
    case 2:
        func_0016c650(w, o, a2, a3);
        return 1;
    }
    return 1;
}

s32 func_00174628(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 42)) return 0;
        return func_0016cb98(w, o, a2, 1);
    case 2:
        func_0016cb98(w, o, a2, a3);
        return 1;
    }
    return 1;
}

s32 func_001746e0(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 43)) return 0;
        return func_0016d040(w, o, a2, 1);
    case 2:
        func_0016d040(w, o, a2, a3);
        return 1;
    }
    return 1;
}

s32 func_00174968(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 45)) return 0;
        return func_0016d2d0(w, o, a2, 1);
    case 2:
        func_0016d2d0(w, o, a2, a3);
        return 1;
    }
    return 1;
}

s32 func_00174a20(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 46)) return 0;
        return func_0016d768(w, o, a2, 1);
    case 2:
        func_0016d768(w, o, a2, a3);
        return 1;
    }
    return 1;
}

void func_00174ad8(Wk *w) {
    Ob *o = w->x144;
    Prm *q;
    if ((s32)(o->flags >> 17) & 1) {
        o->flags &= ~0x20000ULL;
        return;
    }
    q = o->x160->xc;
    o->x68 = func_00171aa8(q->x14, q->x18);
    o->x4c = *func_00171b80(w, o, q->x0);
    if (func_00171ae8(w, o)) o->x40->x50 = q->x1c;
    o->x164 = 1;
}

s32 func_00174db0(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 47)) return 0;
        if (!((s32)(o->flags >> 2) & 1)) return 0;
        return func_0016b670(w, o, a2, 1);
    case 2:
        func_00148a40(w, 0);
        func_0016b670(w, o, a2, 2);
        func_00170fa8(w, o, func_00170f90, D_0035C410, 30.0f);
        return 1;
    }
    return 1;
}

s32 func_00174eb8(Wk *w, Ob *o, s32 a2, s32 a3) {
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 48)) return 0;
        if (!((s32)(o->flags >> 2) & 1)) return 0;
        return func_0016b670(w, o, a2, 1);
    case 2:
        func_00148a40(w, 0);
        func_0016b670(w, o, a2, 2);
        func_00170fa8(w, o, func_00170f90, D_0035C410, 30.0f);
        return 1;
    }
    return 1;
}

/* intersection of segment a-b with a plane; out gets w = 1 */
s32 func_00175820(V3 *a, V3 *b, void *pl, V4 *out) {
    f32 da = func_00162950(a, pl);
    f32 db = func_00162950(b, pl);
    f32 t;
    if (fabsf(da - db) < 1.17549449095213395e-38f) return 0;
    t = -da / (db - da);
    out->x = (b->x - a->x) * t + a->x;
    out->y = (b->y - a->y) * t + a->y;
    out->z = (b->z - a->z) * t + a->z;
    out->w = 1.0f;
    return 1;
}

s32 func_00177168(void) {
    switch (D_00575894->x70) {
    case 0: return D_003623F4 > 1.0f;
    case 8: return D_003623F4 > 7.0f;
    case 24: return D_003623F4 > 7.0f;
    default: return D_003623F4 > 0.1f;
    }
}

void func_00178e10(void) {
    if (func_001375d8(D_00575894)) return;
    if (0.0f < D_005758C4) return;
    if (0.0f < D_0057590C) return;
    if (D_002C5BB0.x4 & 0x1000)
        D_00362680.y = func_00120c88(D_00362680.y + D_002BBDFC * 0.034906583f);
    if (D_002C5BB0.x4 & 0x2000)
        D_00362680.y = func_00120c88(D_00362680.y - D_002BBDFC * 0.034906583f);
}

void func_0017a6c0(void) {
    V4 t;
    s32 *f = &D_00575890;
    Actor **pa;
    if (*f & 2) *f &= ~2;
    pa = &D_00575894;
    func_002672f8(&D_005758E0, &(*pa)->xd0, &D_00362590);
    func_002672f8(&D_005758D0, &(*pa)->xd0, &D_00362580);
    if (func_00177608(&t, &D_005758E0, &D_005758D0)) func_002675a8(&D_005758D0, &t);
    D_00362684 = func_00124d28(&D_005758D0, &D_005758E0);
    if (!func_00177258(*pa)) func_00176f08(1, 30.0f);
}

/* cubic Bezier through the 4 control points m[0..3] */
void func_0017b250(f32 *out, f32 (*m)[4], f32 t) {
    f32 b[4];
    f32 s = 1.0f - t;
    s32 i;
    b[0] = s * s * s;
    b[1] = t * 3.0f * (s * s);
    b[2] = t * t * 3.0f * s;
    b[3] = t * t * t;
    for (i = 0; i < 3; i++) {
        out[i] = m[0][i] * b[0] + m[1][i] * b[1] + m[2][i] * b[2] + m[3][i] * b[3];
    }
    out[3] = 1.0f;
}

void func_0017b740(V4 *out, V4 *in) {
    V4 d;
    Path *p = D_00362438;
    func_00267530(&d, &D_00575970, in);
    d.y = 0.0f;
    func_00121fc4(&d, &d);
    if (p->x8 < d.w) {
        func_00267560(&d, &d, d.w - p->x8);
        func_00267518(out, in, &d);
    } else {
        func_002675a8(out, in);
    }
}

void func_0017bfe8(void) {
    V4 t;
    Cam *c2;
    f32 dt = D_002BBDFC;
    Cam *c = &D_00575940;
    f32 max = D_00362438->x14 * dt;
    f32 s, d;
    f32 k = 100.0f;
    if (c->x64) {
        dt += dt;
        max += max;
    }
    c->x54 += dt;
    c->x54 = (c->x54 < 0.0f) ? 0.0f : ((max < c->x54) ? max : c->x54);
    s = D_00575940.x54;
    func_00267530(&t, &D_00575940.x0, &D_00575940.x10);
    d = func_00120bf8(&t);
    if (d < 5.0f) d = 0.0f;
    d = (d < 0.0f) ? 0.0f : ((k < d) ? 100.0f : d);
    s *= d / k;
    if (!func_0017b7e8()) s = 0.0f;
    c2 = &D_00575940;
    func_0017b4f8(&c2->x40, &c2->x48, s * c2->x50);
}

void func_0017c7f0(void) {
    Path *p = D_00362438;
    Cam *c;
    if (p->flags & 4) {
        if (D_002C5BB8 & 0x3000) {
            D_005759A6 = 0;
            func_0011d768(4);
        }
        return;
    }
    c = &D_00575940;
    if (0.0f < c->x5c) {
        c->x5c -= D_002BBDFC;
        return;
    }
    if (func_001375d8(D_00575894)) return;
    if (c->x65) return;
    if (D_00575920.x0 && !(p->flags & 0x10)) return;
    func_0017c4c8();
    func_0017c550();
}

s32 func_0017dc40(void) {
    void **a = &D_0036244C;
    void *v = *a;
    if (v != 0 || D_00362450 != 0) {
        D_00362434 = v;
        D_00362438 = D_00362450;
        D_0036243C = D_00362454;
        func_00176f08(9, 0.0f);
        *a = 0;
        D_00362450 = 0;
        D_00362454 = 0;
        return 1;
    }
    *a = 0;
    D_00362450 = 0;
    D_00362454 = 0;
    return 0;
}

void func_0017ec00(void) {
    V4 m[4];
    V4 v;
    Actor **pa = &D_00575894;
    if (!*pa) return;
    func_002672f8(&D_005758E0, &(*pa)->xd0, &D_00362630);
    D_00362684 = func_00120c88((*pa)->x3c + 3.1415928f);
    func_00267810(m, D_002C58D0, D_00362684);
    func_002672f8(&v, m, &D_00362620);
    func_00267518(&D_005758D0, &D_005758E0, &v);
    func_002675a8(&D_002E2780, &D_005758D0);
    func_002675a8(&D_002E2790, &D_005758E0);
    func_00176f08(1, 30.0f);
    D_005758C4 = 0.0f;
}

void func_0017ef40(s32 a) {
    S920 *s = &D_00575920;
    s32 m = D_002E27A8;
    s->x0 = a;
    if (m != 9) {
        if (m != 3) {
            func_002675a8(&s->x10, &D_005758E0);
            func_00176f08(3, 60.0f);
            return;
        }
        func_002675a8(&s->x10, &D_005758E0);
        s->x4 = 60.0f;
        return;
    }
    func_002675a8(&s->x10, &D_005758E0);
    func_0017d570(a);
}

/* --- shift packed 14-bit x / 14-bit y coordinates of every entry --- */
typedef struct { s16 off; u8 pad[6]; } TEnt;
typedef struct Hdr {
    u8 pad0[6];
    s16 n;          /* 0x06 */
    u8 pad8[8];
    TEnt tbl[1];    /* 0x10 */
} Hdr;
typedef struct Ref { u16 x0; u16 x2; u16 x4; } Ref;
typedef struct Ent {
    u8 pad0[0x10];
    union { u16 h; u32 w; } x10;
    u32 x14;
} Ent;

void func_00180180(Hdr *h, Ref *r, s16 dx, s16 dy) {
    s16 ox = 0, oy = 0;
    s32 n;
    TEnt *t;
    if (dx == 0 && dy == 0) return;
    if (dx) ox = dx - r->x2;
    if (dy) oy = dy - r->x4;
    n = h->n;
    for (t = h->tbl; n > 0; n--, t++) {
        Ent *e = (Ent *)((u8 *)h + t->off);
        if (dx && ox) {
            s32 v = e->x10.h & 0x3fff;
            if (v >= 0x3800) e->x10.w = (e->x10.w & 0xffffc000) + (v + ox);
        }
        if (dy && oy) {
            u32 w = e->x14;
            s32 v = (w & 0x7ffe0) >> 5;
            if (v >= 0x3d40) e->x14 = (w & 0xfff8001f) + ((v + oy) << 5);
        }
    }
}

typedef struct Obj {
    u8 pad0[0x8c];
    s32 x8c;    /* 0x8C */
    u8 pad90;
    u8 x91;     /* 0x91 */
    u8 x92;     /* 0x92 */
} Obj;

void func_001803f0(void *a0, s32 id, s32 *out, Obj *o) {
    s32 *p = func_001803b8(a0);
    s32 n, i;
    *out = 0;
    n = *p++;
    for (i = 0; i < n; i++, p++) {
        if (id == i) {
            s32 v = *p;
            o->x8c = v;
            *out = v + 272;
        }
    }
    p = func_001803c0(p, 4);
    if (p[0] != -1) {
        s32 y = (p[1] - 0x3781) / 128;
        s32 x = (p[3] - 0x3d21) / 32;
        o->x91 = y;
        o->x92 = x;
    } else {
        o->x91 = 0;
        o->x92 = 0;
    }
}
#include "data/data_002E.h"
#include "data/data_0036.h"
