#include "common.h"
#include "platform/math.h"

typedef f32 M25[4][4] __attribute__((aligned(16)));
typedef struct { u64 a, b; } Q16_25;
typedef struct { u8 b0, b1, b2, b3; } Pt25;
typedef struct { Pt25 p; u8 pad[12]; } PtE25;
typedef struct { f32 a[4], b[4], c[3]; u32 par; } S48_25;
typedef struct { u8 pad[8]; s32 x8; } X8_25;
typedef struct { s16 n; u8 pad2[2]; S48_25 *src; X8_25 *x8; s32 xc; PtE25 parts[1]; } Mdl25;
typedef struct { Mdl25 *x0; s32 x4; Mdl25 *x8; s32 xc; } Hd25;
typedef struct { u8 pad[3]; u8 idx; u8 pad4[4]; } E8_25;
typedef struct { u8 pad[0x10]; s32 x10; u8 pad14[4]; s32 *x18; } Grp25;
typedef struct { u8 a; s8 b; } Ref25;
typedef struct { s32 x0; Ref25 *x4; s32 x8; s32 xc; u32 *x10; } Att25;
typedef struct {
    Hd25 *x0;
    u8 pad4[0xc];
    Grp25 *x10;
    Grp25 *x14;
    Att25 att[5];
    u8 pad7c[0x154 - 0x7c];
    M25 *x154;
} Obj25;
typedef struct { void *x0; f32 *x4; } Pr25;
typedef struct {
    Q16_25 x0;
    Pr25 *x10;
    Mdl25 *x14;
    s32 x18;
    s32 x1c;
    s32 x20, x24, x28, x2c;
    s32 x30, x34, x38, x3c;
    s32 x40, x44;
    union {
        struct { u64 lo : 16; u64 b16 : 1; u64 b17 : 1; u64 rest : 46; } w;
        struct { s8 b0; s8 b8; } c;
        
    } x48;
} DObj25;
typedef struct {
    DObj25 *x0;
    u8 n : 3;
    u8 f : 1;
    u8 g : 4;
    u8 x5;
    s8 x6;
    u8 x7;
    s32 a[4];
    void *b[4];
    s32 x28;
} Dsl25;
typedef struct {
    s32 x0, x4, x8, xc, x10;
    Pr25 pr[2][72];
    u8 pad494[4];
    DObj25 obj[2][78];
    Dsl25 dsl[2][480];
} Gl25;
typedef struct {
    u32 x0;
    s32 x4;
    s32 x8;
    u8 xc, xd, xe, xf;
    u8 x10, x11, x12, x13;
    Mdl25 *x14;
    u8 x18, x19, x1a, x1b;
    u8 x1c, x1d, x1e, x1f;
    s32 x20, x24;
    u32 x28, x2c;
    void (*x30)(void *, f32 *, M25);
    void (*x34)(void *, f32 *);
    Q16_25 x38;
} Prm25;

extern Gl25 D_0055C698;
extern s32 D_0055BE00[48];
extern s32 D_0055BEC0[48][5];
extern void *D_0055C280[48][5];

u32 func_00121e28(u32, void *);
f32 func_00267390(f32 *, f32 *);
void func_002674d0(f32 *, f32 *, f32);
void func_00162c5c(void *, void *, void *);
void sceVu0CopyMatrix(M25, M25);

#define VU_LOAD_MTX(m) \
    __asm__ volatile( \
        "lqc2 $vf13, 0(%0)\n" \
        "lqc2 $vf14, 16(%0)\n" \
        "lqc2 $vf15, 32(%0)\n" \
        "lqc2 $vf16, 48(%0)\n" \
        : : "r"(m) : "memory")

#define VU_MUL_MTX(d, s) \
    __asm__ volatile( \
        "lqc2 $vf8, 0(%1)\n" \
        "lqc2 $vf9, 16(%1)\n" \
        "lqc2 $vf10, 32(%1)\n" \
        "lqc2 $vf11, 48(%1)\n" \
        "vmulax.xyzw ACC, $vf13xyzw, $vf8x\n" \
        "vmadday.xyzw ACC, $vf14xyzw, $vf8y\n" \
        "vmaddaz.xyzw ACC, $vf15xyzw, $vf8z\n" \
        "vmaddw.xyzw $vf8xyzw, $vf16xyzw, $vf8w\n" \
        "vmulax.xyzw ACC, $vf13xyzw, $vf9x\n" \
        "vmadday.xyzw ACC, $vf14xyzw, $vf9y\n" \
        "vmaddaz.xyzw ACC, $vf15xyzw, $vf9z\n" \
        "vmaddw.xyzw $vf9xyzw, $vf16xyzw, $vf9w\n" \
        "vmulax.xyzw ACC, $vf13xyzw, $vf10x\n" \
        "vmadday.xyzw ACC, $vf14xyzw, $vf10y\n" \
        "vmaddaz.xyzw ACC, $vf15xyzw, $vf10z\n" \
        "vmaddw.xyzw $vf10xyzw, $vf16xyzw, $vf10w\n" \
        "vmulax.xyzw ACC, $vf13xyzw, $vf11x\n" \
        "vmadday.xyzw ACC, $vf14xyzw, $vf11y\n" \
        "vmaddaz.xyzw ACC, $vf15xyzw, $vf11z\n" \
        "vmaddw.xyzw $vf11xyzw, $vf16xyzw, $vf11w\n" \
        "sqc2 $vf8, 0(%0)\n" \
        "sqc2 $vf9, 16(%0)\n" \
        "sqc2 $vf10, 32(%0)\n" \
        "sqc2 $vf11, 48(%0)\n" \
        : : "r"(d), "r"(s) : "memory")

#define ADD_ATT(g, at) { \
    Ref25 *r_ = (at).x4; \
    if (r_ && (at).x10 && !(*(at).x10 & 0xf)) { \
        s32 idx_ = ((E8_25 *)(g)->x10)[r_->b].idx; \
        D_0055BEC0[idx_][D_0055BE00[idx_]] = (g)->x18[(*(at).x10 >> 4) & 0xfff]; \
        D_0055C280[idx_][D_0055BE00[idx_]] = &((E8_25 *)(g)->x10)[r_->b]; \
        D_0055BE00[idx_]++; \
    } \
}

DObj25 *func_001606d0(Obj25 *o, M25 m, Prm25 *p, void *arg) {
    M25 mt;
    Pt25 pt;
    M25 buf;
    Hd25 *h;
    Mdl25 *md;
    Pr25 *pr;
    DObj25 *d;
    DObj25 *d2;
    Dsl25 *e;
    M25 *mtx;
    Grp25 *g;
    s32 i, j, cnt, draw, prio;
    f32 l0, l1, l2;
    f32 *fp;

    VU_LOAD_MTX(m);
    h = o->x0;
    {
        Mdl25 *m0;
        s32 k;
        if ((p->x0 & 1) && h->x8) m0 = h->x8;
        else m0 = h->x0;
        cnt = 0;
        for (k = 0; k < m0->xc; k++) {
            if (!(p->x28 & (1 << m0->parts[k].p.b1))) cnt++;
        }
    }
    draw = 0;
    if (cnt) draw = 1;
    if (p->x14) draw |= 2;
    if (!draw) return 0;

    if ((p->x0 & 1) && h->x8) md = h->x8;
    else md = h->x0;
    pr = &D_0055C698.pr[D_0055C698.x0][D_0055C698.xc++];
    for (i = 47; i >= 0; i--) D_0055BE00[i] = 0;
    g = o->x10;
    if (g) {
        for (i = 0; i < 4; i++) {
            ADD_ATT(g, o->att[i]);
        }
    }
    mtx = o->x154;
    d = &D_0055C698.obj[D_0055C698.x0][D_0055C698.x4];
    d->x48.w.b16 = p->x8 > 0;
    d->x48.w.b17 = 0;
    d->x14 = md;
    d->x10 = pr;
    d->x18 = 0;
    pr->x4 = 0;
    d->x30 = p->x10;
    d->x34 = p->x11;
    d->x38 = p->x12;
    d->x3c = p->x13 << 4;
    d->x48.c.b0 = 0;
    d->x1c = h->xc;
    d->x40 = p->x20;
    d->x44 = p->x24;
    d->x0 = p->x38;
    if (p->x0 & 0x100) d->x48.c.b0 = 16;
    else if (p->x0 & 0x200) d->x48.c.b0 = 8;
    if ((p->x0 & 1) && h->x8) d->x48.c.b0 |= 4;
    if (!(d->x48.c.b0 & 4) && p->x4) {
        d->x48.c.b0 |= 1;
        func_00121e28(md->n << 7, &d->x10->x0);
        func_00121e28(64, &d->x10->x4);
        p->x34(arg, d->x10->x4);
        fp = d->x10->x4;
        for (i = 0; i < 16; i++) fp[i] *= 128.0f;
        d->x2c = (u32)d->x10->x4[15];
        for (i = 0; i < md->n; i++) {
            if (i != 0 && !((md->src[i].par >> 30) & 1)) continue;
            {
                M25 *s = (M25 *)((i << 6) + (u32)mtx);
                VU_MUL_MTX((i << 7) + (u32)d->x10->x0, s);
                p->x30(arg, (*s)[3], buf);
                sceVu0CopyMatrix(mt, *s);
                l0 = func_00267390(mt[0], mt[0]);
                l1 = func_00267390(mt[1], mt[1]);
                l2 = func_00267390(mt[2], mt[2]);
                if (l0 > 1.0999999046325684f) func_002674d0(mt[0], mt[0], PlatSqrtf(l0));
                if (l1 > 1.0999999046325684f) { l1 = PlatSqrtf(l1); func_002674d0(mt[1], mt[1], l1); }
                if (l2 > 1.0999999046325684f) { l2 = PlatSqrtf(l2); func_002674d0(mt[2], mt[2], l2); }
                func_00162c5c((u8 *)d->x10->x0 + i * 128 + 64, buf, mt);
            }
        }
    } else {
        func_00121e28(md->n << 6, &d->x10->x0);
        d->x20 = p->xc;
        d->x24 = p->xd;
        d->x28 = p->xe;
        d->x2c = p->xf;
        VU_MUL_MTX(d->x10->x0, mtx[0]);
        for (i = 1; i < md->n; i++) {
            if ((md->src[i].par >> 30) & 1) {
                VU_MUL_MTX((i << 6) + (u32)d->x10->x0, (i << 6) + (u32)mtx);
            }
        }
    }
    if (p->x8 > 0) prio = p->x8;
    else prio = ((s8)p->xf >= 0) ? 70000 : 20000;
    for (i = 0; i < md->xc; i++) {
        pt = md->parts[i].p;
        if (!(p->x28 & (1 << pt.b1))) {
            e = &D_0055C698.dsl[D_0055C698.x0][D_0055C698.x8];
            e->x7 = i * 4 + 1;
            e->x5 = 0;
            e->x0 = d;
            e->g = pt.b2;
            e->x6 = pt.b3;
            e->f = (p->x2c & (1 << pt.b1)) != 0;
            e->n = D_0055BE00[e->x6];
            for (j = 0; j < e->n; j++) {
                e->a[j] = D_0055BEC0[e->x6][j];
                e->b[j] = D_0055C280[e->x6][j];
            }
            e->x28 = prio;
            D_0055C698.x8++;
        }
    }
    if (p->x8 <= 0) prio = 70000;
    for (i = 0; i < md->xc; i++) {
        pt = md->parts[i].p;
        if ((pt.b0 & 1) && !(p->x28 & (1 << pt.b1)) && !(p->x2c & (1 << pt.b1))) {
            e = &D_0055C698.dsl[D_0055C698.x0][D_0055C698.x8];
            e->x5 = 1;
            e->x7 = i * 4 + 1;
            e->x0 = d;
            e->g = pt.b2;
            e->x6 = pt.b3;
            e->f = 0;
            e->n = D_0055BE00[e->x6];
            for (j = 0; j < e->n; j++) {
                e->a[j] = D_0055BEC0[e->x6][j];
                e->b[j] = D_0055C280[e->x6][j];
            }
            e->x28 = prio;
            D_0055C698.x8++;
        }
    }
    D_0055C698.x4++;
    if (p->x14) {
        for (i = 47; i >= 0; i--) D_0055BE00[i] = 0;
        g = o->x14;
        if (g) ADD_ATT(g, o->att[4]);
        d2 = &D_0055C698.obj[D_0055C698.x0][D_0055C698.x4];
        d2->x48.w.b16 = p->x8 > 0;
        d2->x48.w.b17 = 0;
        if (p->x8 > 0) prio = p->x8;
        else prio = ((s8)p->x1b >= 0) ? 70000 : 20000;
        if (p->x0 & 1) d2->x48.c.b0 = 20;
        else if (d->x48.c.b0 & 1) d2->x48.c.b0 = 1;
        else if (p->x0 & 0x100) d2->x48.c.b0 = 16;
        else d2->x48.c.b0 = 0;
        d2->x14 = p->x14;
        d2->x10 = d->x10;
        d2->x18 = md->n - p->x14->n;
        d2->x30 = p->x1c;
        d2->x34 = p->x1d;
        d2->x38 = p->x1e;
        d2->x3c = p->x1f << 4;
        d2->x20 = p->x18;
        d2->x24 = p->x19;
        d2->x28 = p->x1a;
        d2->x2c = p->x1b;
        d2->x0 = p->x38;
        d2->x1c = p->x14->x8->x8;
        d2->x40 = p->x20;
        d2->x44 = p->x24;
        for (i = 0; i < p->x14->xc; i++) {
            { Pt25 *pp = (Pt25 *)((i << 4) + (u32)p->x14 + 16); pt = *pp; }
            e = &D_0055C698.dsl[D_0055C698.x0][D_0055C698.x8];
            e->x7 = i * 4 + 1;
            e->x5 = 0;
            e->x0 = d2;
            e->g = pt.b2;
            e->x6 = pt.b3;
            e->f = 0;
            e->n = D_0055BE00[e->x6];
            for (j = 0; j < e->n; j++) {
                e->a[j] = D_0055BEC0[e->x6][j];
                e->b[j] = D_0055C280[e->x6][j];
            }
            e->x28 = prio;
            D_0055C698.x8++;
        }
        if (p->x8 <= 0) prio = 70000;
        for (i = 0; i < p->x14->xc; i++) {
            { Pt25 *pp = (Pt25 *)((i << 4) + (u32)p->x14 + 16); pt = *pp; }
            if (pt.b0 & 1) {
                e = &D_0055C698.dsl[D_0055C698.x0][D_0055C698.x8];
                e->x7 = i * 4 + 1;
                e->x5 = 1;
                e->x0 = d2;
                e->g = pt.b2;
                e->x6 = pt.b3;
                e->f = 0;
                e->n = D_0055BE00[e->x6];
                for (j = 0; j < e->n; j++) {
                    e->a[j] = D_0055BEC0[e->x6][j];
                    e->b[j] = D_0055C280[e->x6][j];
                }
                e->x28 = prio;
                D_0055C698.x8++;
            }
        }
        D_0055C698.x4++;
    }
    return d;
}
