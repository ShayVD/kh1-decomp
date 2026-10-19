/* Hand-matched functions near 0x14D000-0x158000 (worker 9). */
#include "common.h"

typedef struct {
    u8 pad0[0x10];
    f32 x10;
    u8 pad14[0xBD - 0x14];
    s8 xbd;
    u8 padbe[0xC4 - 0xBE];
    f32 xc4;
    u8 padc8[0xCC - 0xC8];
    union { f32 f; s32 i; u8 c; } xcc;
} W9Obj6c;
typedef struct {
    u8 pad0[0x100];
    u64 x100;
    u8 pad108[0x130 - 0x108];
    f32 x130[4];
    s32 x140;
} W9Obj148;
typedef struct {
    u8 pad0[0x1C];
    u8 *x1c;
} W9Obj134;
typedef struct {
    u8 pad0[0x120];
    f32 x120[4];
    u8 pad130[0x134 - 0x130];
    W9Obj134 *x134;
} W9Obj98;
typedef union { f32 f; s32 i; void *p; u8 c; } W9U;
typedef union {
    W9U w[0x20];
    u64 d[0x10];
} W9Obj144;
typedef struct {
    s32 flags;
    s32 x4;
    u8 pad8[0x10 - 8];
    f32 x10[4];
    f32 x20[4];
    f32 x30[4];
    u8 pad40[0x6C - 0x40];
    W9Obj6c *x6c;
    s32 x70;
    u8 pad74[0x8C - 0x74];
    s32 x8c;
    u8 pad90[0x98 - 0x90];
    W9Obj98 *x98;
    u8 pad9c[0xA4 - 0x9C];
    f32 xa4;
    f32 xa8;
    u8 padac[0x120 - 0xAC];
    f32 x120[4];
    u8 pad130[0x144 - 0x130];
    W9Obj144 *x144;
    W9Obj148 *x148;
    u8 pad14c[0x164 - 0x14C];
    W9U x164;
    u8 pad168[0x1CC - 0x168];
    s32 x1cc;
    u8 pad1d0[0x1F0 - 0x1D0];
    f32 x1f0[4];
    u8 pad200[0x370 - 0x200];
    union { u64 x; struct { u64 lo:44; u64 b44:1; u64 hi:19; } b; } x370;
    s32 x378;
    u8 pad37c[0x3B0 - 0x37C];
    f32 x3b0;
    f32 x3b4;
    f32 x3b8;
    f32 x3bc;
    f32 x3c0[4];
    u8 pad3d0[0x45C - 0x3D0];
    f32 x45c;
    u8 pad460[0x470 - 0x460];
    u64 x470;
    u8 pad478[0x490 - 0x478];
    f32 x490[4];
    void *x4a0;
} W9Ent;
typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    u8 padc[0x14];
} W9Tab32;
extern W9Tab32 D_00350D88[];
typedef struct {
    s8 a;
    s8 b;
    u8 pad2[2];
    f32 f4;
    u8 pad8[4];
} W9Tab12;
void func_00267560(void *out, void *in, f32 s);
void func_00130398(W9Ent *e, f32 s, s32 n);
void func_00267518(void *out, void *a, void *b);
void func_00267530(void *out, void *a, void *b);
void func_002675a8(void *dst, void *src);
void func_00121fc4(void *dst, void *src);
f32 func_00120c18(void *v);
typedef struct {
    f32 a;
    f32 b;
    f32 c;
    f32 d;
} W9F4;
extern W9F4 D_00351930[];
typedef struct {
    union {
        s32 w;
        struct { s8 b0; u8 b1; u8 b2; u8 b3; } b;
        struct { u32 lo:16; u32 f16:1; u32 f17:1; u32 f18:1; u32 hi:13; } f;
    } h;
    u8 pad4[0x24 - 4];
    char name[0x20];
    s32 x44;
} W9Blk;
extern W9Blk D_00550400[];
W9Blk D_005512A0[0xc] ALIGNED(32);
extern u8 D_00FE0000[];
extern u8 D_01CE0000[];

s32 func_00137618(void);
s32 func_0014d180(W9Ent *e) {
    s32 r;
    s32 f, g;
    r = func_00137618();
    if (r) {
        f = e->flags;
        g = f & 4;
        if ((f & 0x10000) && e->x3b0 < 15.0f) return 0;
        r = 0;
        if (e->x3b8 == 0.0f || e->x3b8 + 6.0f < e->x3b0) r = g == 0;
    }
    return r;
}

extern u32 D_002C5958;
s32 func_001443a8(W9Ent *e);
s32 func_0014db20(W9Ent *e);
s32 func_0014d330(W9Ent *e, s32 a1) {
    s32 f;
    if (a1 == 0 && func_001443a8(e) == 0) {
        f = e->flags;
        if (!(f & 0x1000)) goto L;
    }
    if ((D_002C5958 >> 5) & 1) {
        if (func_0014db20(e)) {
            e->flags &= ~4;
            return 8;
        }
    }
    return e->x70;
L:
    return (f & 0x2000) ? 6 : 0;
}


extern W9Tab12 D_00350D30[];
extern s32 D_002BC128;
extern s32 D_002BC130;
W9Tab12 *func_0014dab8(void) {
    W9Tab12 *p;
    for (p = D_00350D30; p->a >= 0; p++) {
        if (p->a == D_002BC128 && p->b == D_002BC130) return p;
    }
    return 0;
}

W9Tab12 *func_0014dab8(void);
s32 func_0014db20(W9Ent *e) {
    W9Tab12 *p;
    if (e->x148) {
        p = func_0014dab8();
        if (p && e->x10[1] > p->f4) return 1;
    }
    return 0;
}

void func_0014db78(W9Ent *e, f32 *v) {
    f32 t[4];
    func_00267560(t, v, v[3]);
    func_00267518(t, e->x3c0, t);
    {
        f32 len = func_00120c18(t);
        if (16.0f < len) func_00267560(t, t, 16.0f / len);
    }
    e->x3c0[0] = t[0];
    e->x3c0[2] = t[2];
}

void func_0014dc08(W9Ent *e) {
    e->x6c->xcc.f = 0.06981316208839417f;
    e->x1cc &= ~1;
    func_00267560(e->x3c0, e->x3c0, 0.29999998211860657f);
    if (e->x148) e->x148->x100 &= ~((u64)1 << 34);
}

void func_00147338(s32 a, s32 b);
void func_0014dc90(W9Ent *e) {
    e->x6c->xcc.f = 0.19634954631328583f;
    e->x1cc |= 1;
    func_00147338(17108, e->x4 + 1);
}

void func_0014cc88(W9Ent *e, f32 s);
void func_0014e3a0(W9Ent *e) {
    f32 s = 12.0f;
    func_00267560(e->x3c0, e->x3c0, 0.7f);
    func_0014cc88(e, s);
    func_00130398(e, s, 6);
}

s32 func_0014ee08(f32 *lo, f32 *hi, f32 *box) {
    s32 r = 0;
    if (hi[0] >= box[4] && lo[0] <= box[8] &&
        hi[1] >= box[5] && lo[1] <= box[9] &&
        hi[2] >= box[6] && lo[2] <= box[10]) r = 1;
    return r;
}

void *func_00134928(void *a);
void func_001350d0(void *p);
void func_0014f3d0(void *a) {
    void *p;
    while ((p = func_00134928(a)) != 0) func_001350d0(p);
}

typedef void (*W9Fn)(W9Ent *);
s32 func_0014f658(W9Ent *e, s32 s) {
    s32 old = e->x70;
    if (old != s) {
        e->x378 = old;
        e->x70 = s;
        e->flags |= 0x400;
        if (D_00350D88[old].f8) ((W9Fn)D_00350D88[old].f8)(e);
        if (D_00350D88[s].f4) ((W9Fn)D_00350D88[s].f4)(e);
        return 1;
    }
    return 0;
}

void func_0014f9b0(W9Ent *e, f32 *src, f32 t) {
    func_002675a8(e->x1f0, src);
    if (0.0f < t) {
        e->x1f0[3] = 0.0f;
        e->x45c = 1.0f / t;
    } else {
        e->x45c = 0.0f;
        e->x1f0[3] = 1.0f;
    }
    e->x470 |= (u64)1 << 33;
}

void func_0014fa38(W9Ent *e, f32 t) {
    if ((s32)(e->x470 >> 33) & 1) {
        if (0.0f < t) {
            e->x470 |= (u64)1 << 33;
            e->x45c = -e->x1f0[3] / t;
        } else {
            e->x470 &= ~((u64)1 << 33);
        }
    }
}

void func_00137318(W9Ent *e);
void func_001501c0(W9Ent *e) {
    func_00137318(e);
    e->x144->w[0].i = 4;
    e->x144->w[2].i = 0;
    e->flags |= 0x20;
}

extern f32 D_002C5970;
W9Obj144 *func_0014cb90(W9Ent *e);
void func_0014cce0(W9Ent *e, f32 s);
void func_00150af0(W9Ent *e, f32 *v) {
    func_0014cb90(e)->w[1].f = 4.0f;
    func_0014cce0(e, e->x6c->x10);
    func_002675a8(v, e->x148->x130);
    v[1] = 0.0f;
    func_00121fc4(v, v);
    v[3] *= D_002C5970;
}

void func_00150b70(W9Ent *e) {
    f32 t[4];
    if (e->x98) return;
    func_0014cb90(e)->w[1].f = 4.0f;
    func_002675a8(t, e->x148->x130);
    t[1] = 0.0f;
    func_00267560(e->x3c0, t, D_002C5970);
    func_0014cce0(e, 10.0f);
    e->flags &= ~0x400;
}

void func_0015bad0(W9Obj98 *o, void *ent, f32 *out);
void func_00150c18(W9Ent *e, f32 *out) {
    f32 m[2][4];
    func_0015bad0(e->x98, e->x98->x134->x1c + e->x148->x140 * 20, m[0]);
    func_00267530(out, m[1], e->x10);
    out[1] += 120.0f;
    if (e->x164.i == 191) func_002675a8(e->x148->x130, out);
}

s32 func_0013c9e0(W9Ent *e);
void func_00243630(s32 a, W9Ent *e);
void func_00150d30(W9Ent *e) {
    s32 v = func_0013c9e0(e);
    func_00243630(v == 255 ? 2 : v == 12, e);
}

typedef struct {
    s32 x0;
    s32 x4;
    u8 pad8[0x38];
} W9Slot64;
extern W9Slot64 D_0054F750[];
extern s32 D_0054F740;
extern W9Tab12 *D_0054F950;
void func_00151808(void) {
    s32 i;
    for (i = 7; i >= 0; i--) D_0054F750[i].x4 = 0;
    D_0054F740 = 0;
    D_0054F950 = func_0014dab8();
}

void func_00151860(void);
W9Obj144 *func_00148a40(W9Ent *e, s32 a);
void func_00148068(W9Obj144 *p, f32 t);
void func_00151940(W9Ent *e) {
    W9Obj144 *p;
    if (!e->x4a0) {
        e->x4a0 = func_00151860;
        e->x144 = func_00148a40(e, 0);
    }
    p = e->x144;
    if (p) {
        if ((p->w[5].i & 3) != 1) {
            e->x144 = 0;
        } else if (e->x164.i) {
            func_00148068(p, 20.0f);
            e->x144 = 0;
        }
    }
}

extern W9Ent *D_002E26A0;
void func_0012cc38(s32 a, s32 b);
s32 func_001520e0(W9Ent *e, s32 a1, s32 a2) {
    W9Ent *p = D_002E26A0;
    if (a2 == -1 && e->x70 == 0 && e->x8c == 0 && p->x70 == 28) func_0012cc38(0, 29);
    return 0;
}

extern f32 D_002BBDFC;
void func_00152370(W9Ent *e, f32 *v) {
    if (e->x98) {
        func_00267560(e->x20, v, v[3] * D_002BBDFC);
        func_00267518(e->x98->x120, e->x98->x120, e->x20);
    }
}

f32 fabsf(f32);
s32 func_00152408(W9Ent *e, s32 a1) {
    f32 t[4];
    s32 r = 2;
    if (a1 == 0) {
        func_00267530(t, e->x10, e->x490);
        if (fabsf(t[0] - e->x120[0]) > 0.001f || fabsf(t[1] - e->x120[1]) > 0.001f ||
            fabsf(t[2] - e->x120[2]) > 0.001f) func_00137318(e);
        r = e->x70;
    }
    return r;
}

void func_00152598(W9Ent *e) {
    e->x144->w[17].f = 300.0f;
    e->x144->w[18].i = 0;
    if (!e->x144->w[19].p) e->x144->w[19].p = func_00148a40(e, 3);
}

void func_00176310(void *p);
void func_001525f0(W9Ent *e) {
    void *p;
    e->x144->w[17].i = 0;
    e->xa4 = e->xa8 = 1.0f;
    p = e->x144->w[19].p;
    if (p) {
        func_00176310(p);
        e->x144->w[19].p = 0;
    }
}

void func_00152538(W9Ent *e);
void func_001528f0(W9Ent *e) {
    func_00152538(e);
    e->x144->w[1].i = 4;
    e->x144->w[7].i = 0;
}

void func_00152ba8(W9Ent *e, f32 *v, f32 s);
void func_00152d50(W9Ent *e, s32 i, f32 *v) {
    f32 t[4];
    e->x144->w[8].i = i;
    func_00267560(t, v, D_00351930[i].b);
    t[1] = D_00351930[i].c;
    func_00152ba8(e, t, D_00351930[i].d);
}

void func_00152dc8(W9Ent *e, s32 i) {
    e->x144->w[1].i = 3;
    e->x144->w[8].i = i;
    e->x144->d[0] &= ~2;
    e->x144->w[7].f = D_00351930[i].a;
}

void func_00152880(W9Ent *e);
void func_001531c0(W9Ent *e) {
    e->x144->w[6].f -= D_002BBDFC;
    if (e->x144->w[6].f < 0.0f) func_00152880(e);
}

typedef struct {
    u8 pad0[0x4C];
    u16 x4c;
} W9Obj130;
typedef struct {
    u8 pad0[0x130];
    W9Obj130 *x130;
} W9ObjB4;
typedef struct {
    s32 x0;
    W9ObjB4 *x4;
    union {
        u64 x;
        struct { u32 lo; u32 b0:10; u32 b10:1; u32 hi:21; } b;
    } x8;
} W9Obj;
s32 func_001532c8(W9Obj *o) {
    s32 r = 0;
    if (o->x4 && !o->x4->x130->x4c) r = !o->x8.b.b10;
    return r;
}

s32 func_00153300(W9Ent *e, W9Obj *o) {
    s32 r = 0;
    if ((((s32 *)o)[3] & 0x1f) == 5) {
        if (func_001532c8(o)) r = e->x8c == 0;
    }
    return r;
}

void func_00153b68(W9Ent *e, s32 a1, f32 *v) {
    s32 n;
    if (0.0f < v[3]) {
        v[3] = 3.0f;
        n = 185;
    } else {
        v[3] = 0.0f;
        n = 182;
    }
    func_00130398(e, 8.0f, n);
}

typedef struct {
    u8 pad0[0x30];
    f32 x30;
    f32 x34;
} W9Cfg;
extern W9Cfg *D_00308CDC;
f32 func_001348e0(W9Ent *e, f32 *o);
void func_00267e90(f32 *out, f32 *in, f32 s);
void func_00154258(W9Ent *e, f32 *o, f32 *out) {
    f32 k = e->x6c->xc4;
    f32 s;
    if (func_001348e0(e, o) * D_00308CDC->x30 < D_00308CDC->x34) {
        s = func_001348e0(e, o) * D_00308CDC->x30 * k;
    } else {
        s = D_00308CDC->x34 * k;
    }
    func_00267e90(out, o + 4, s);
}

s32 func_001559a8(u8 *p) {
    s32 i = (p - D_00FE0000) / 0x40000;
    return D_00550400[i].x44;
}

u8 *func_00155a50(void) {
    s32 i;
    for (i = 0; i < 12; i++) {
        D_005512A0[i].h.b.b0 = -1;
        D_005512A0[i].h.w |= 0x20000;
    }
    return D_01CE0000;
}

s32 func_00155a90(void) {
    s32 i;
    for (i = 0; i < 12; i++) {
        if (!(D_005512A0[i].h.w & 0x20000)) return 1;
    }
    return 0;
}

s32 func_00155ad8(s32 i, s32 n) {
    W9Blk *p = &D_00550400[i];
    s32 j;
    for (j = 0; j < n; j++) {
        if (p[j].h.b.b0 != i || p[j].h.b.b1 != n) {
            for (j = 0; j < n; j++) {
                p[j].h.b.b0 = i;
                p[j].h.b.b1 = n;
            }
            return 0;
        }
    }
    return 1;
}

typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xc;
    s32 x10;
    s32 x14;
    s32 x18;
} W9Hdr;
void func_00162058(void *p);
void func_001763f0(void *p);
void func_0015c9f8(void *p);
void func_00155b70(W9Hdr *h) {
    func_00162058((u8 *)h + h->x4);
    if (h->xc - h->x8 > 0) func_001763f0((u8 *)h + h->x8);
    if (h->x18 - h->x14 > 0) func_0015c9f8((u8 *)h + h->x14);
}

void func_00155be0(s32 *h) {
    s32 i;
    func_00162058((u8 *)h + h[1]);
    if (h[4] - h[3] > 0) {
        h = (s32 *)((u8 *)h + h[3]);
        for (i = 0; i < 10; i++) {
            if (h[i + 2] - h[i + 1] > 0) func_00155be0((s32 *)((u8 *)h + h[i + 1]));
        }
    }
}

void func_00155c68(u32 size, s32 a1, u8 *h) {
    W9Blk *q;
    s32 i;
    func_00155b70((W9Hdr *)h);
    i = (h - D_00FE0000) / 0x40000;
    q = &D_00550400[i];
    q->x44 = (s32)(h + ((size + 127) >> 7 << 7));
    q->h.b.b3++;
}

s32 strcmp(const char *, const char *);
s32 func_00155e48(s32 i, s32 n, const char *name) {
    W9Blk *p = &D_00550400[i];
    s32 j;
    if (p->h.b.b0 != i || strcmp(p->name, name)) return 0;
    for (j = 0; j < n; j++) {
        if (p[j].h.b.b0 != i) return 0;
    }
    return 1;
}

typedef struct {
    u8 pad0[8];
    u8 *x8;
    u8 padc[0x55 - 0xC];
    s8 x55;
} W9Obj55;
typedef struct {
    u8 pad0[0x14];
    W9Obj55 *x14;
    s32 x18;
} W9Task;
extern u8 D_0054F970[];
void func_00155ef8(void);
W9Obj55 *func_001320a8(s32 a);
W9Task *func_0011f090(void *q, s32 a, void (*fn)(void));
s32 func_001560f8(s32 a0, s32 a1) {
    W9Obj55 *o = func_001320a8(a0);
    s32 k = o->x55;
    W9Task *t;
    if (k < 0) return 0;
    D_00550400[k].h.b.b3 = 0;
    o->x8 = D_00FE0000 + (k << 18);
    t = func_0011f090(D_0054F970, 0, func_00155ef8);
    t->x14 = o;
    t->x18 = a1;
    return 1;
}

void func_001561b0(void) {
    s32 i;
    for (i = 0; i < 64; i++) {
        D_00550400[i].h.f.f16 = 0;
        D_00550400[i].h.f.f18 = 0;
    }
}

extern u8 *D_00551600;
u8 *func_00156628(s32 n) {
    u8 *p = D_00551600;
    s32 i;
    for (i = 1; *p; i++) {
        if (i == n) return p;
        p = p + p[1] * 96 + 48;
    }
    return 0;
}

f32 func_00267390(f32 *a, f32 *b);
s32 func_001566d8(f32 (*pl)[4], f32 *pt) {
    s32 i;
    f32 *w = &pl[0][3];
    f32 *p = pl[0];
    for (i = 0; i < 6; i++) {
        if (func_00267390(p, pt) - *w < 0.0f) return 0;
        p += 4;
        w += 4;
    }
    return 1;
}

typedef struct {
    s8 b0;
    s8 b1;
    s8 b2;
    s8 b3;
    u8 pad4[0x10];
} W9Tab20;
extern W9Tab20 D_00551670[];
s32 func_00157528(W9Ent *e) {
    W9Tab20 *q = &D_00551670[e->x6c->xbd];
    if (!q->b0) return -1;
    return q->b3;
}

/* needs make: uses rodata */
s32 func_0014f600(W9Ent *e) {
    switch (e->x70) {
    case 2:
    case 11:
    case 16:
    case 17:
    case 19:
    case 20:
    case 22:
        return 1;
    }
    return (D_00350D88[e->x70].f0 & 3) == 1;
}

typedef union { u64 d; s32 w; struct { u32 lo; u32 x:6; u32 kind:4; u32 hi:22; } b; } F8M;
typedef struct { u8 pad[8]; F8M f8; } Msg9;
void func_00147138(W9Ent *, s32);
void func_00153360(W9Ent *, Msg9 *);
void func_001533d0(W9Ent *, Msg9 *);
void func_00145008(W9Ent *, s32);

void func_00153500(W9Ent *a, Msg9 *m) {
    s32 n;
    if (m->f8.b.kind == 1) func_00147138(a, 4);
    switch (m->f8.b.kind) {
    case 2:
        if (a->x144->w[17].f > 0.0f) {
            a->x144->w[1].i = 6;
            return;
        }
        func_00152598(a);
        return;
    case 3:
        a->x144->w[2].i = 0;
        func_001525f0(a);
        return;
    }
    if (func_00153300(a, (W9Obj *)m)) {
        func_00152598(a);
        func_00153360(a, m);
        return;
    } else {
        n = m->f8.w;
        if (n > 0) {
            a->x144->w[2].i += n;
            if (a->x144->w[2].i >= a->x144->w[3].i) {
                func_00145008(a, 0);
                a->x144->w[1].i = 6;
            } else {
                if (func_001532c8((W9Obj *)m)) func_00152598(a);
                func_001533d0(a, m);
            }
        }
    }
}
