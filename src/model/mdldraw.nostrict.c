/* The model renderer's draw side, without strict aliasing
 * (docs/modules.md "Session 52"): the draw task func_00160370, the per-model
 * draw func_001606d0 (its bucket tables D_0055BE00 / D_0055BEC0 /
 * D_0055C280 are defined here), func_00161a08 (relocate a "MOBJ" model or a
 * "MENV" map environment in place), func_00161de8, func_00162218,
 * func_00162428.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/math.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_003519E0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/types/nostrict_text_00140000_b04.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/types/nostrict_text_00150000_h59.h"
#include "data/pieces/D_00351BC8.h"
#include "data/types/nostrict_text_00150000_h36.h"

/* func_00160370 (from hand/nostrict/text_00140000_b04.c). */
typedef struct { void *x0; void *x4; } B4Pr;
typedef struct { u8 pad[0x3c]; f32 x3c; } B4Ky;
typedef struct { B4Ky *x0; } B4Kyp;
typedef struct { u8 pad[0x10]; B4Kyp *x10; u8 pad14[0x48 - 0x14]; union { u64 x; struct { u8 b0; s8 x49; } c; } x48; } B4Obj;
typedef struct { B4Obj *x0; u32 x4; u8 pad8[0x28 - 8]; s32 x28; } B4Dsl;
typedef struct B4Ln { struct B4Ln *x0; B4Obj *x4; } B4Ln;
typedef struct { s32 x0; s32 x4; s32 x8; s32 xc; s32 x10; B4Pr x14[2][72]; u8 pad494[4]; B4Obj x498[2][78]; B4Dsl x3558[2][480]; } B4Gl;
typedef struct { u8 pad[0x10]; void *x10; s32 x14; } B4Task;
extern B4Gl D_0055C698;
B4Ln *D_005739F0 ALIGNED(16);  /* D_005739F0 and D_005736F0 moved from hand/nostrict/text_00140000_b04.c (session 53) */
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

/* func_001606d0 (from hand/nostrict/text_00160000_s7_w25.c). */
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
s32 D_0055BE00[48] ALIGNED(64);
s32 D_0055BEC0[48][5] ALIGNED(64);
void *D_0055C280[48][5] ALIGNED(64);
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
#define D_0055C698 (*(Gl25 (*)) &D_0055C698)
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
#undef D_0055C698
#undef VU_LOAD_MTX
#undef VU_MUL_MTX
#undef ADD_ATT

/* func_001617c0 (from hand/nostrict/text_00150000_h59.c). */
typedef struct { u8 pad0[8]; s32 x8; u8 padc[0x20 - 0xc]; Mdl59 *x20; u8 pad24[4]; s32 x28; u8 pad2c[4]; s32 x30; } Src17c0;
extern Ent59 D_0056A0F0[96];
void *memset(void *, s32, u32);
void func_001626f0(f32 *, f32 *, f32 *, f32 *);
#define func_00121e28 ((s32 (*)(s32, void *)) func_00121e28)
Ent59 *func_001617c0(Src17c0 *o) {
    s32 i, j;
    Ent59 *e;
    Mdl59 *m;
    for (i = 0; i < 96; i++) {
        if (D_0056A0F0[i].x0 == 0) break;
    }
    e = &D_0056A0F0[i];
    m = o->x20;
    memset(e, 0, sizeof(Ent59));
    e->x170 = m;
    e->x174 = o->x30;
    e->x178 = o->x28;
    e->x17c = o->x8;
    e->x180 = o;
    e->x0 = &e->x170;
    func_00121e28(m->n << 6, &e->x154);
    func_00121e28(m->n << 6, &e->x158);
    func_00121e28(m->n << 6, &e->x150);
    for (i = 0; i < m->n; i++) {
        for (j = 0; j < 3; j++) e->x150[i].m[0][j] = m->src[i].a[j];
        for (j = 0; j < 3; j++) e->x150[i].m[2][j] = m->src[i].b[j];
        for (j = 0; j < 3; j++) e->x150[i].m[3][j] = m->src[i].c[j];
        func_001626f0(e->x150[i].m[0], e->x150[i].m[2], e->x150[i].m[3], e->x158[i].m[0]);
    }
    return e;
}
#undef func_00121e28

/* func_00161a08 (from hand/nostrict/text_00140000_b04.c). */
typedef struct { u32 x0; u32 x4; s32 x8; u32 xc; s32 x10; u32 x14; s32 x18; u32 x1c; s32 x20; u32 x24; s32 x28; s32 x2c; s32 x30; s32 x34; } B4Hd;
typedef struct { u8 pad[3]; u8 x3; s32 x4; s32 x8; s32 xc; } B4Me;
typedef struct { u16 x0; u16 x2; s32 x4; s32 x8; s32 xc; B4Me e[1]; } B4Mt;
typedef struct { u16 x0; u16 x2; u32 x4; s32 x8; s32 xc; } B4Mb;
typedef struct { s32 x0; s32 x4; s32 x8; } B4Mk;
typedef struct { u8 pad[0x14]; s32 x14; u8 pad18[4]; s32 x1c; u8 pad20[4]; s32 x24; s32 x28; u8 pad2c[4]; s32 x30; u8 pad34[4]; s32 x38; B4Mk *x3c; } B4Mo;
extern s32 D_005739F8[];
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

/* func_00161de8 (from hand/nostrict/text_00150000_h59.c). */
typedef struct { void *a, *b; } Pr59;
typedef struct { u8 b[44]; } E44_59;
typedef struct {
    s32 x0, x4, x8, xC, x10;
    Pr59 pr[2][72];
    u8 pad494[0x3558 - 0x494];
    E44_59 e[2][480];
} G698;
typedef struct { u8 pad[0x10]; void *x10; s32 x14; } Tk62;
s32 func_0015eea0();
s32 sceGsSyncPath(s32, s32);
#define D_0055C698 (*(G698 (*)) &D_0055C698)
#define func_001606d0 ((void (*)(void)) func_001606d0)
#define func_0015ee78 ((Tk62 *(*)(s32, void *)) func_0015ee78)
#define func_0015f388 ((s32 (*)(void)) func_0015f388)
void func_00161de8(void) {
    s32 c8 = D_0055C698.x8;
    s32 c4 = D_0055C698.x4;
    s32 cC = D_0055C698.xC;
    s32 i;
    Tk62 *t;
    E44_59 *e;
    Pr59 *p;
    func_001606d0();
    e = &D_0055C698.e[D_0055C698.x0][c8];
    for (i = c8; i < D_0055C698.x8; i++) {
        t = func_0015ee78(0, func_0015ff78);
        t->x10 = e;
        t->x14 = 0;
        e++;
    }
    func_0015ee78(0, func_0015f388);
    func_0015eea0();
    sceGsSyncPath(0, 0);
    p = &D_0055C698.pr[D_0055C698.x0][cC];
    for (i = cC; i < D_0055C698.xC; i++, p++) {
        if (p->a) {
            func_00121eb0(p->a);
            p->a = 0;
        }
        if (p->b) {
            func_00121eb0(p->b);
            p->b = 0;
        }
    }
    D_0055C698.x4 = c4;
    D_0055C698.x8 = c8;
    D_0055C698.xC = cC;
}
#undef D_0055C698
#undef func_001606d0
#undef func_0015ee78
#undef func_0015f388

/* func_00162218 (from hand/nostrict/text_00150000_h36.c). */
void func_002675a8(void *, void *);
typedef struct { u8 pad[0x2C]; u32 x2C; } Bone48;
typedef struct { u8 pad[4]; Bone48 *bones; } SkelHdr;
typedef struct { SkelHdr **skel; u8 pad4[0x14C]; f32 (*m150)[4][4]; f32 (*m154)[4][4]; } SkelObj;
void func_00162848(f32 *, void *, f32 *);
void func_00267e60(f32 *, f32 *, f32 *, f32);
s32 func_00162218(SkelObj *o, s32 idx, f32 *out, f32 t) {
    f32 v[4];
    s32 par = (*o->skel)->bones[idx].x2C & 0x3FF;
    if (par == 0x3FF && t == 1.0f) {
        func_002675a8(out, o->m154[idx][3]);
        return -1;
    }
    func_00162848(v, o->m154[par], o->m150[idx][3]);
    func_00267e60(out, v, o->m154[par][3], t);
    return ((*o->skel)->bones[par].x2C >> 30) & 1 ? -1 : 0;
}

/* func_00162428 (from hand/nostrict/text_00150000_h36.c). */
void func_00266f38(void *, void *);
extern DmaChcr *D_0055C644;
typedef struct { u16 h0; u8 b2; u8 b3; u32 w4; } GifTag8;
extern GifTag8 *volatile D_0055C648;
extern u8 D_00573AC0[];
void func_0015f8c8(void);
void func_00162428(void) {
    __asm__ volatile("sync");
    D_0055C648 = (GifTag8 *)((u32)D_00573AC0 | 0x20000000);
    func_0015f8c8();
    D_0055C648->b3 = 0x70;
    D_0055C648->w4 = 0;
    D_0055C648->h0 = 0;
    __asm__ volatile("sync");
    D_0055C644->mod = 1;
    D_0055C644->asp = 0;
    D_0055C644->tte = 0;
    D_0055C644->tie = 0;
    __asm__ volatile("sync");
    func_00266f38(D_0055C644, D_00573AC0);
}

