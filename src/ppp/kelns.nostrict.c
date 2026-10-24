/* The KeLns draw helpers, -fno-strict-aliasing (docs/modules.md "Session 49"),
 * with kelns.c: func_001a5740 draws a shape frame through the VU0 routine
 * func_001b8198 and advances the packet end D_00616224; func_001a57c0 is
 * pppKeLnsLpDraw's (a lens flare's ray: a screen-space matrix and its fade
 * from the angle to the camera); func_001a5ce8 / func_001a60e8 /
 * func_001a62c0 / func_001a6550 are the Clm / Arnd / Crn / Fls draws (a
 * shape scaled by the object's size and alpha, func_001a56a0 stepping its
 * animation).  The flare reading is a guess from the class names.
 * Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"

typedef kh1_s128 u128;
typedef f32 Mtx[4][4] __attribute__((aligned(16)));
typedef f32 Vec[4] __attribute__((aligned(16)));
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
typedef f32 Mtx4[4][4];

f32 func_001a9350(f32 *);
f32 func_001a9388(f32 *);
void func_001a56a0(void *);

extern f32 D_00615FC0[4][4];
extern Mtx D_00616040; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
extern f32 D_00615FF8;
extern f32 D_00575A00; /* src/data/bss_0057.c: u8 D_00575A00[0x10] */
extern s32 D_00616224;

typedef struct {
    u16 unk0;
    u16 flags;
    u8 r, g, b, a;
    s32 w8;
    s16 hC;
    s16 pad;
    s32 w10;
    s32 w14;
    u8 b18;
} P5740;
typedef struct {
    s16 pad[8];
    s16 off;
} E5740;
typedef struct {
    u8 **base;
    u8 *hdr;
    u8 pad8[8];
    P5740 p;
} S5740;
s32 func_001b8198(void *, P5740 *, s32);

void func_001a5740(S5740 *s) {
    u8 **b = s->base;
    E5740 *e;
    e = (E5740 *)(*b + s->hdr[2] * 8);
    s->p.w8 = 0;
    s->p.b18 = 0;
    s->p.w14 = D_00616224;
    s->p.flags |= 0x30;
    s->p.hC = 18;
    D_00616224 = func_001b8198(*b + e->off, &s->p, 0);
}

typedef struct {
    Mtx ma;       /* 0x00 */
    Mtx m;        /* 0x40 */
    f32 off[3];   /* 0x80 */
    u8 pad8c[2];
    u8 b8e;
    u8 b8f;
    Vec v90;      /* 0x90 */
    f32 fa0;
    f32 fa4;
    f32 fa8;
} Obj57c0;

typedef struct {
    Obj57c0 *o;
    f32 *v;
    Mtx *mtx;
} Arg57c0;

void func_001a57c0(Arg57c0 *a) {
    Mtx m0;
    Mtx m1;
    Vec v80;
    Vec v90;
    Vec va0;
    Obj57c0 *o;

    f32 d;

    o = a->o;
    PlatVu0CopyMatrix(m1, *a->mtx);
    if (o->b8f) {
        PlatVu0CopyMatrix(m0, m1);
        m0[3][0] = 0;
        m0[3][1] = 0;
        m0[3][2] = 0;
        PlatVu0ApplyMatrix(v80, m0, a->v);
        PlatVu0ScaleVector(v90, m1[3], -1.0f);
        PlatVu0SubVector(va0, v90, v80);
    } else {
        *(u128 *)v80 = 0;
        *(u128 *)v90 = 0;
        v80[3] = 1.0f;
        v90[3] = 1.0f;
        PlatVu0UnitMatrix(m0);
        m0[3][0] = D_00615FC0[3][0] + o->off[0];
        m0[3][1] = D_00615FC0[3][1] + o->off[1];
        m0[3][2] = D_00615FC0[3][2] + o->off[2];
        PlatVu0MulMatrix(m0, D_00616040, m0);
        PlatVu0ApplyMatrix(v80, m0, v80);
        PlatVu0ScaleVector(v80, v80, 1.0f / v80[3]);
        PlatVu0UnitMatrix(m0);
        PlatVu0CopyVector(m0[3], D_00615FC0[3]);
        PlatVu0MulMatrix(m0, D_00616040, m0);
        PlatVu0ApplyMatrix(v90, m0, v90);
        PlatVu0ScaleVector(v90, v90, 1.0f / v90[3]);
        PlatVu0SubVector(va0, v90, v80);
        va0[2] = 512.0f;
    }
    PlatVu0UnitMatrix(o->ma);
    PlatVu0ApplyMatrix(o->ma[3], m1, a->v);
    if (va0[0] == 0.0f && va0[1] == 0.0f) {
        PlatVu0CopyVector(o->m[3], o->ma[3]);
    } else {
        __asm__ volatile(
        "lqc2 $vf18, 0(%1)\n"
        "vmul.xy $vf26xy, $vf18xy, $vf18xy\n"
        "vaddy.x $vf26x, $vf26x, $vf26y\n"
        "vsqrt Q, $vf26x\n"
        "vsub.zw $vf22zw, $vf0zw, $vf0zw\n"
        "vsub.w $vf21w, $vf0w, $vf0w\n"
        "vsub.xyw $vf20xyw, $vf0xyw, $vf0xyw\n"
        "vaddw.z $vf20z, $vf0z, $vf0w\n"
        "sqc2 $vf20, 32(%0)\n"
        "vwaitq\n"
        "vaddq.x $vf26x, $vf0x, Q\n"
        "vdiv Q, $vf0w, $vf26x\n"
        "lqc2 $vf17, 0(%2)\n"
        "sqc2 $vf17, 48(%0)\n"
        "vwaitq\n"
        "vmulq.xy $vf22xy, $vf18xy, Q\n"
        "sqc2 $vf22, 0(%0)\n"
        "vopmula.xyz ACC, $vf22, $vf20\n"
        "vopmsub.xyz $vf21, $vf20, $vf22\n"
        "sqc2 $vf21, 16(%0)\n"
        : : "r"(o->m), "r"(va0), "r"(o->ma[3]) : "memory");
    }
    if (o->b8f) {
        o->m[3][2] = o->ma[3][2] * 0.001953125f;
    } else {
        o->m[3][2] = (D_00615FC0[3][2] + o->off[2]) * 0.001953125f;
    }
    PlatVu0Normalize(va0, va0);
    o->m[3][0] = va0[0] * o->m[3][2];
    o->m[3][1] = va0[1] * o->m[3][2];
    PlatVu0SubVector(v90, v90, v80);
    d = func_001a9350(v90);
    o->fa4 = func_001a9388(v90);
    PlatVu0Normalize(v80, v90);
    if (o->b8f) {
        v90[0] = 0;
        v90[1] = 0;
        v90[2] = 1.0f;
        v90[0] = (1.0f - (1.0f - PlatVu0InnerProduct(v90, v80)) * 0.5f) / 0.3f;
        o->m[3][3] = v90[0] > 1.0f ? 0.0f : 1.0f - v90[0];
        if (o->v90[3] >= 0.0f) {
            PlatVu0CopyMatrix(m0, m1);
            m0[3][2] = m0[3][1] = m0[3][0] = 0.0f;
            PlatVu0ApplyMatrix(v90, m0, v90);
            v90[0] = (1.0f - PlatVu0InnerProduct(o->v90, v80)) * 0.5f;
            v90[0] = v90[0] / o->v90[3];
            v90[0] = v90[0] > 1.0f ? 0.0f : 1.0f - v90[0];
            o->m[3][3] *= v90[0];
        }
        v80[0] = o->fa8 - (f32)o->b8e;
        if (v80[0] > 0.0f) {
            v80[0] = d / v80[0];
            d = 0.0f;
            if (!(v80[0] >= 1.0f)) d = 1.0f - v80[0];
            o->m[3][3] *= d;
        } else {
            o->m[3][3] = 0.0f;
        }
    } else {
        if (o->fa8 > 0.0f) {
            o->m[3][3] = o->fa4 / o->fa8;
            o->m[3][3] = o->m[3][3] > 1.0f ? 0.0f : 1.0f - o->m[3][3];
        } else {
            o->m[3][3] = 0.0f;
        }
    }
}

typedef struct { u16 time; u8 idx; u8 pad; f32 w; } C5St;
typedef struct {
    u16 unk0;
    u16 flags;
    union { u32 w; struct { u8 r, g, b, a; } c; } col;
    s32 d8;
    s16 dc;
    s16 de;
    void *p10;
    s32 w14;
    u8 b18;
    void *p1C;
    u8 pad20[0x10];
} C5Param;
typedef struct { void *anim; C5St *st; u8 pad8[8]; C5Param p; } C5Draw;
typedef struct {
    PppMtx m;
    u8 pad40[0x30];
    f32 x70, x74, x78, x7c;
    u8 pad80[8];
    f32 x88;
    u8 pad8c[2];
    u8 x8e;
    u8 x8f;
    u8 pad90[0x14];
    f32 xa4;
} C5Src;
typedef struct {
    C5Src *src;
    void *anim;
    u8 n;
    u8 pad9;
    s16 xa;
    s16 xc;
    u8 xe;
    u8 padf;
    C5St st[1];
} C5Obj;
typedef struct { C5Obj *obj; u32 col; PppMtx *m; f32 xc; f32 x10; f32 *x14; } C5Arg;

void func_001a5ce8(C5Arg *a, s32 fl) {
    PppMtx m0;
    PppMtx m1;
    C5Draw d;
    C5Obj *o = a->obj;
    C5Src *s = o->src;
    C5St *st;
    f32 x, y, dx, dy, al, fa, fc, w;
    s32 n;

    if (s == (C5Src *)&D_00575A00)
        return;
    if (!o->anim)
        return;
    if (s->x7c == 0.0f)
        return;
    if (s->x8f) {
        PlatVu0CopyMatrix(m0, (f32 (*)[4])s);
    } else {
        PlatVu0UnitMatrix(m0);
        m0[3][2] = D_00615FF8 + s->x88;
    }
    d.p.col.w = a->col;
    d.anim = o->anim;
    d.p.flags = fl;
    d.p.p10 = m1;
    d.p.p1C = 0;
    d.p.d8 = 0;
    d.p.dc = 0;
    d.p.de = 0;
    if (s->x8f) { y = x = 0.0f; } else { x = D_00615FC0[3][0]; y = D_00615FC0[3][1]; }
    fc = o->xc;
    fa = o->xa;
    al = s->x70;
    x += al * fc;
    dx = al * fa;
    al = s->x74;
    y += al * fc;
    dy = al * fa;
    al = s->xa4;
    al -= s->x8e;
    if (al <= 0.0f) {
        al = 0.0f;
    } else {
        al = al / (a->x10 * s->x78);
        if (al > 1.0f)
            al = 1.0f;
    }
    if (o->xe)
        al = 1.0f - al;
    st = o->st;
    n = o->n;
    al = al * (d.p.col.c.a * s->x7c);
    for (; n > 0; n--) {
        w = st->w;
        d.st = st;
        func_001a56a0(&d);
        st++;
        x += dx * w;
        y += dy * w;
        m0[3][0] = x;
        m0[3][1] = y;
        d.p.col.c.a = al * (w * 0.75 + 0.25);
        w = w * a->xc;
        m0[0][0] = s->m[0][0] * w * a->x14[0];
        m0[1][1] = s->m[1][1] * w * a->x14[1];
        PlatVu0MulMatrix(m1, *a->m, m0);
        func_001a5740((S5740 *)&d);
    }
}

typedef union { u32 w; struct { u8 r, g, b, a; } c; } Rgba;
typedef struct {
    Mtx4 m;
    u8 pad40[0x3c];
    f32 alpha;
    f32 pos[3];
    u8 pad8c[3];
    u8 useMtx;
} DmObj;
typedef struct { DmObj *obj; void *mdl; u8 data[1]; } DmSrc;
typedef struct { DmSrc *src; Rgba col; f32 (*mtx)[4]; f32 scale; f32 *scl; } DmArg;
typedef struct {
    void *mdl;
    void *data;
    u8 pad8[0xa];
    s16 id;
    Rgba col;
    s32 x18, x1c;
    f32 (*mtx)[4];
    u8 pad24[8];
    s32 x2c;
    u8 pad30[0x10];
} DmCtx;

void func_001a60e8(DmArg *a, s32 id) {
    Mtx4 m;
    DmCtx c;
    DmSrc *s = a->src;
    DmObj *o = s->obj;

    if (o == (DmObj *)&D_00575A00)
        return;
    if (s->mdl == NULL)
        return;
    if (o->alpha == 0.0f)
        return;
    if (o->useMtx) {
        PlatVu0CopyMatrix(m, o->m);
    } else {
        PlatVu0UnitMatrix(m);
        m[3][0] = D_00615FC0[3][0] + o->pos[0];
        m[3][1] = D_00615FC0[3][1] + o->pos[1];
        m[3][2] = D_00615FC0[3][2] + o->pos[2];
    }
    m[0][0] *= a->scale;
    m[1][1] *= a->scale;
    PlatVu0ScaleVector(m[0], m[0], a->scl[0]);
    PlatVu0ScaleVector(m[1], m[1], a->scl[1]);
    PlatVu0ScaleVector(m[2], m[2], a->scl[2]);
    PlatVu0MulMatrix(m, a->mtx, m);
    c.col = a->col;
    c.col.c.a = c.col.c.a * o->alpha;
    c.mdl = s->mdl;
    c.data = s->data;
    func_001a56a0(&c);
    c.id = id;
    c.mtx = m;
    c.x2c = 0;
    c.x18 = 0;
    c.x1c = 0;
    func_001a5740((S5740 *)&c);
}

typedef struct { DmSrc *src; Rgba col; f32 (*mtx)[4]; f32 scale; u16 w, h; f32 *scl; } DmArg2;
typedef struct {
    void *mdl;
    void *data;
    u8 pad8[0xa];
    s16 id;
    Rgba col;
    s32 x18;
    s16 x1c, x1e;
    f32 (*mtx)[4];
    u8 pad24[8];
    s32 x2c;
    u8 pad30[0x10];
} DmCtx2;
typedef struct {
    u8 pad0[0x30];
    f32 r3[4], r0[4], r1[4], r2[4];
    u8 pad70[0xc];
    f32 alpha;
    f32 pos[3];
    u8 pad8c[3];
    u8 useMtx;
    u8 pad90[0x14];
    f32 size;
} DmObj2;

void func_001a62c0(DmArg2 *a, s32 id) {
    Mtx4 m;
    DmCtx2 c;
    DmSrc *s = a->src;
    DmObj2 *o = (DmObj2 *)s->obj;
    f32 f, t;

    if (o == (DmObj2 *)&D_00575A00)
        return;
    if (s->mdl == NULL)
        return;
    if (o->alpha == 0.0f)
        return;
    PlatVu0CopyVector(m[0], o->r0);
    PlatVu0CopyVector(m[1], o->r1);
    PlatVu0CopyVector(m[2], o->r2);
    PlatVu0CopyVector(m[3], o->r3);
    f = a->scale * o->size / (f32)a->w;
    PlatVu0ScaleVector(m[0], m[0], -f);
    PlatVu0ScaleVector(m[1], m[1], f);
    if (!o->useMtx) {
        m[3][0] = D_00615FC0[3][0] + o->pos[0];
        m[3][1] = D_00615FC0[3][1] + o->pos[1];
        m[3][2] = D_00615FC0[3][2] + o->pos[2];
    }
    PlatVu0ScaleVector(m[0], m[0], a->scl[0]);
    PlatVu0ScaleVector(m[1], m[1], a->scl[1]);
    PlatVu0ScaleVector(m[2], m[2], a->scl[2]);
    PlatVu0MulMatrix(m, a->mtx, m);
    c.col = a->col;
    f = o->size / (f32)a->h;
    t = 1.0f < f ? 1.0f : f;
    c.col.c.a = c.col.c.a * o->alpha * t;
    c.mdl = s->mdl;
    c.data = s->data;
    func_001a56a0((DmCtx *)&c);
    c.id = id;
    c.mtx = m;
    c.x2c = 0;
    c.x18 = 0;
    c.x1c = 0;
    c.x1e = 0;
    func_001a5740((S5740 *)&c);
}

typedef struct { DmSrc *src; Rgba col; f32 (*mtx)[4]; f32 scale; u16 w; u8 mx, my; f32 *scl; } DmArg3;

void func_001a6550(DmArg3 *a, s32 id) {
    Mtx4 m;
    DmCtx2 c;
    DmSrc *s = a->src;
    DmObj2 *o = (DmObj2 *)s->obj;
    f32 f, r, sc;

    if (o == (DmObj2 *)&D_00575A00)
        return;
    if (s->mdl == NULL)
        return;
    if (o->alpha == 0.0f)
        return;
    r = 0.0f;
    f = o->size / (f32)a->w;
    if (!(1.0f < f))
        r = 1.0f - f;
    if (o->useMtx) {
        PlatVu0CopyMatrix(m, (f32 (*)[4])o);
    } else {
        PlatVu0UnitMatrix(m);
        m[3][0] = D_00615FC0[3][0] + o->pos[0];
        m[3][1] = D_00615FC0[3][1] + o->pos[1];
        m[3][2] = D_00615FC0[3][2] + o->pos[2];
    }
    sc = a->scale;
    m[0][0] = sc;
    switch (a->mx) {
    case 1:
        m[0][0] = sc * r;
        break;
    case 2:
        m[0][0] = f * sc + sc;
        break;
    }
    m[1][1] = sc;
    switch (a->my) {
    case 1:
        m[1][1] = sc * r;
        break;
    case 2:
        m[1][1] = f * sc + sc;
        break;
    }
    PlatVu0ScaleVector(m[0], m[0], a->scl[0]);
    PlatVu0ScaleVector(m[1], m[1], a->scl[1]);
    PlatVu0MulMatrix(m, a->mtx, m);
    c.col = a->col;
    c.col.c.a = c.col.c.a * o->alpha * r;
    c.mdl = s->mdl;
    c.data = s->data;
    func_001a56a0((DmCtx *)&c);
    c.id = id;
    c.mtx = m;
    c.x2c = 0;
    c.x18 = 0;
    c.x1c = 0;
    c.x1e = 0;
    func_001a5740((S5740 *)&c);
}
