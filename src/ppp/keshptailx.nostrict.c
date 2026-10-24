/* The pppDrawShapeX and pppKeShpTailX / Tail2X / Tail3X classes,
 * -fno-strict-aliasing (docs/modules.md "Session 50"): a shape animation
 * drawn at the owner's position (DrawShapeX) or along a trail of its last n
 * positions (the KeShpTail "X" variants of keshptail*.c's classes: the frame
 * pushes the current position, local or world, into a ring and steps the
 * shape's frames; the draw draws a shape at each kept position with
 * func_001b8198, scaled and faded along the tail; Tail3X adds a wobble from
 * its random phase).  Types named NAME_xxxxx are one function's own view of a
 * type the others declare differently (tools/shift/s50move/assemble.py).
 * Each section names the file its code came from.  Read from the code, not
 * proved by a boot. */

/* pppDrawShapeXFrame (from hand/nostrict/text_00180000_h40.c). */
#include "common.h"
#include "platform/vu.h"
#include "ppp.h"
#include "data/bss_0061.h"
#include "data/types/nostrict_text_00180000_h40.h"
#include "data/pieces/D_003701F0.h"
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 unk0;
    u8 *inst;   /* +0x4 */
    s32 time;   /* +0x8 */
    s32 unkC;
} PppSlot;
typedef struct {
    u8 pad[0x80];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem;
extern s32 D_0061621C;
extern PppSystem *D_00615E60;
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject;
typedef struct {
    s16 unk0;
    s16 dur;   /* +0x2 */
    s8 flags;  /* +0x4 */
    u8 pad5[3];
} PppShapeFrame;
typedef struct {
    u8 pad0[6];
    s16 n;                  /* +0x6 */
    u8 pad8[8];
    PppShapeFrame f[1];     /* +0x10 */
} PppShape;
typedef struct {
    PppShape *shape;
    s32 unk4;
} PppShapeEnt;
typedef struct {
    u8 pad[0x14];
    PppShapeEnt *shapes; /* +0x14 */
} PppRes;
extern PppRes *D_00615E64;
typedef struct {
    s32 frame;
    s32 id;     /* +0x4 */
    u16 speed;  /* +0x8 */
} PppShapeKey;
typedef struct {
    u16 time;   /* +0x0 */
    u16 cur;    /* +0x2 */
    u16 prev;   /* +0x4 */
} PppShapeWork;
void pppDrawShapeXFrame(PppObject *obj, PppShapeKey *key, PppEntry *e) {
    PppShapeWork *w;
    PppShape *s;
    PppShapeFrame *f;
    u16 cur, t;
    s8 fl;
    s32 id, off;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w = PPP_WORK(PppShapeWork, obj, e, 0);
    id = key->id;
    off = id * 8;
    if (id == 0xFFFF)
        return;
    s = *(PppShape **) ((u8 *) D_00615E64->shapes + off);
    f = &s->f[w->prev];
    w->prev = w->cur;
    w->time += key->speed;
    if (w->time < f->dur)
        return;
    w->time -= f->dur;
    w->cur++;
    if (w->cur < s->n)
        return;
    fl = f->flags;
    w->time = 0;
    if (fl & 0x80)
        w->cur = 0;
    else
        w->cur--;
}

/* pppDrawShapeXDraw (from hand/nostrict/text_00190000_h64.c). */
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
typedef struct {
    u8 pad[0x10];
    PppMtx m;     /* +0x10 */
    PppMtx m2;    /* +0x50 */
    s32 unk90;    /* +0x90 */
    s32 unk94;    /* +0x94 */
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;
typedef struct {
    u32 flags;  /* +0x0 */
    u8 pad04[0x12];
    u16 unk16;  /* +0x16 */
} DMdl;
typedef struct {
    s32 pad0[4];
    u32 tex;    /* +0x10 */
    s32 pad14[2];
    DMdl *mdl;  /* +0x1C */
    s32 unk20;  /* +0x20 */
} DSlot; /* 0x24 */
typedef struct {
    s16 off;   /* +0x0 */
    s16 dur;   /* +0x2 */
    s8 flags;  /* +0x4 */
    u8 pad5[3];
} PppShapeFrame_965a8;
typedef struct {
    u8 pad0[6];
    s16 n;                  /* +0x6 */
    u8 pad8[8];
    PppShapeFrame_965a8 f[1];     /* +0x10 */
} PppShape_965a8;
typedef struct {
    PppShape_965a8 *shape;
    s32 unk4;
} PppShapeEnt_965a8;
typedef struct {
    u8 pad00[0x10];
    DSlot *slots;        /* +0x10 */
    PppShapeEnt_965a8 *shapes; /* +0x14 */
} DSys;
typedef struct {
    u8 pad[8];
    u8 r, g, b, a; /* +0x8 */
} DColWork;
extern s32 D_00616224;
typedef struct {
    u16 unk0;
    u16 flags;     /* +0x2 */
    u8 r, g, b, a; /* +0x4 */
    u64 d8;        /* +0x8 */
    void *p10;     /* +0x10 */
    s32 w14;       /* +0x14 */
    u8 b18;        /* +0x18 */
    void *p1C;     /* +0x1C */
    u8 pad20[0x10];
} DShpParam;
typedef struct {
    s32 frame;
    s32 id;    /* +0x4 */
    u8 pad8[4];
    u8 bC, bD, bE, bF, b10;
} DShpXKey;
s32 func_001b8198(void *, DShpParam *, s32);
#define D_00615E64 ((DSys *) D_00615E64)
void pppDrawShapeXDraw(PppObject *obj, DShpXKey *key, PppEntry *e) {
    DShpParam p;
    PppShapeWork *w = PPP_WORK(PppShapeWork, obj, e, 0);
    DColWork *c = PPP_WORK(DColWork, obj, e, 1);
    PppShapeEnt_965a8 *s;
    PppShape_965a8 *sh;
    u8 *src;

    if (key->id == 0xFFFF)
        return;
    s = &D_00615E64->shapes[key->id];
    if (!key->bF)
        p.flags = 128;
    else
        p.flags = 0;
    if (key->b10 == 1)
        p.flags |= 0x10;
    if (key->bC)
        p.flags |= 0x800;
    if (key->bD)
        p.flags |= 0x400;
    if (key->bE)
        p.p1C = PPP_WORK(u8, obj, e, 3);
    else
        p.p1C = 0;
/*P*/
    p.p10 = D_00615E68->m2;
    p.r = c->r;
    p.g = c->g;
    p.b = c->b;
    p.a = c->a;
    p.d8 = 0;
    p.b18 = 0;
/*Q*/
    sh = s->shape;
    { PppShapeFrame_965a8 *f = &sh->f[w->prev]; src = (u8 *) sh + f->off; }
    p.w14 = D_00616224;
    D_00616224 = func_001b8198(src, &p, s->unk4);
}
#undef D_00615E64

/* pppKeShpTailXFrame (from hand/nostrict/text_00180000_s6_11.c). */
typedef struct {
    u8 pad00[0x10];
    DSlot *slots;
    void *shapes;
} DSys_966f8;
typedef f32 PppVec4[4] __attribute__((aligned(16)));
extern PppMtx D_00615E70;
void func_001a9098(void *, void *);
typedef struct {
    s16 off;
    s16 dur;
    s8 flags;
    u8 pad5[3];
} PppShapeFrame_966f8;
typedef struct {
    u8 pad0[6];
    s16 n;
    u8 pad8[8];
    PppShapeFrame_966f8 f[1];
} PppShape_966f8;
typedef struct {
    PppShape_966f8 *shape;
    s32 unk4;
} PppShapeEnt_966f8;
typedef struct {
    u8 pad00[0x14];
    PppShapeEnt_966f8 *shapes;
} DSysS;
typedef struct {
    u8 n;          /* +0x0 */
    u8 idx;        /* +0x1 */
    u16 t;         /* +0x2 */
    u16 fr;        /* +0x4 */
    u16 prev;      /* +0x6 */
    u8 pad8[8];
    PppVec4 v[1];  /* +0x10 */
} TailXWork;
typedef struct {
    s32 frame;
    s32 id;        /* +0x4 */
    u16 speed;     /* +0x8 */
    u8 padA[0x17];
    u8 local;      /* +0x21 */
} TailXKey;
#define D_00615E64 ((DSys_966f8 *) D_00615E64)
void pppKeShpTailXFrame(PppObject *obj, TailXKey *key, PppEntry *e) {
    TailXWork *w;
    PppShape_966f8 *sh;
    PppShapeFrame_966f8 *f;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w = PPP_WORK(TailXWork, obj, e, 0);
    if (obj->frame == 0 && obj->unk9D == 0) {
        PppVec4 v;
        f32 *p;
        s32 n;

        if (key->local) {
            PlatVu0ApplyMatrix(v, D_00615E70, D_00615E68->m[3]);
            v[3] = 1.0f;
        } else {
            PlatVu0CopyVector(v, D_00615E68->m[3]);
            v[3] = 1.0f;
        }
        p = w->v[0];
        for (n = w->n; n > 0; n--) {
            PlatVu0CopyVector(p, v);
            p += 4;
        }
    }
    if (w->idx == 0)
        w->idx = w->n;
    w->idx--;
    if (key->local) {
        PlatVu0ApplyMatrix(w->v[w->idx], D_00615E70, D_00615E68->m[3]);
        w->v[w->idx][3] = 1.0f;
    } else {
        func_001a9098(w->v[w->idx], D_00615E68->m[3]);
    }
    {
        u16 fr;

        { PppShapeEnt_966f8 *se = &((DSysS *) D_00615E64)->shapes[key->id]; sh = se->shape; }

        fr = w->fr;
        w->prev = fr;
        f = &sh->f[fr];
        w->t += key->speed;
        if (w->t < f->dur)
            return;
        w->t -= f->dur;
        w->fr = fr + 1;
        if (w->fr < sh->n)
            return;
        {
            s32 fl = f->flags;
            w->t = 0;
            if (fl & 0x80)
                w->fr = 0;
            else
                w->fr--;
        }
    }
}
#undef D_00615E64

/* pppKeShpTailXDraw (from hand/nostrict/text_00180000_s7_w11.c). */
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} T2MtxOwner;
typedef struct {
    s16 off;
    s16 dur;
    s8 flags;
    u8 pad5[3];
} T2Frame;
typedef struct {
    u8 pad0[0x10];
    T2Frame f[1];
} T2Shape;
typedef struct {
    T2Shape *shape;
    s32 unk4;
} T2ShapeEnt;
typedef struct {
    u8 pad00[0x14];
    T2ShapeEnt *shapes;
} T2Sys;
typedef struct {
    u8 count;     /* +0x0 */
    u8 idx;       /* +0x1 */
    u16 time;     /* +0x2 */
    u16 frame;    /* +0x4 */
    u16 prev;     /* +0x6 */
    u8 pad8[8];
    PppVec4 v[1]; /* +0x10 */
} T2Work;
extern PppMtx D_00615EB0;
extern PppMtx D_00615FC0;
extern PppMtx D_00616040;
f32 func_001a9350(f32 *);
#define V_FTOI_U8(dst, src) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "vftoi0.xyzw $vf31xyzw, $vf31xyzw\n" \
        "qmfc2 $2, $vf31\n" \
        "sb $2, 0(%0)\n" \
        "mtsab $0, 4\n" \
        "qfsrv $2, $2, $2\n" \
        "sb $2, 1(%0)\n" \
        "qfsrv $2, $2, $2\n" \
        "sb $2, 2(%0)\n" \
        "qfsrv $2, $2, $2\n" \
        "sb $2, 3(%0)\n" \
        : : "r"(dst), "r"(src) : "$2", "memory")
#define V_SCALE_XYZ(dst, src, s) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "lqc2 $vf29, 0(%0)\n" \
        "mfc1 $2, %2\n" \
        "qmtc2 $2, $vf30\n" \
        "vmulx.xyz $vf29xyz, $vf31xyz, $vf30x\n" \
        "sqc2 $vf29, 0(%0)\n" \
        : : "r"(dst), "r"(src), "f"(s) : "$2", "memory")
#define V_APPLY(out, m, v) \
    __asm__ volatile( \
        "lqc2 $vf27, 0(%1)\n" \
        "lqc2 $vf28, 16(%1)\n" \
        "lqc2 $vf29, 32(%1)\n" \
        "lqc2 $vf30, 48(%1)\n" \
        "lqc2 $vf31, 0(%2)\n" \
        "vmulax.xyzw ACC, $vf27xyzw, $vf31x\n" \
        "vmadday.xyzw ACC, $vf28xyzw, $vf31y\n" \
        "vmaddaz.xyzw ACC, $vf29xyzw, $vf31z\n" \
        "vmaddw.xyzw $vf27xyzw, $vf30xyzw, $vf31w\n" \
        "sqc2 $vf27, 0(%0)\n" \
        : : "r"(out), "r"(m), "r"(v))
#define V_SUB(out, a, b) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "lqc2 $vf30, 0(%2)\n" \
        "vsub.xyzw $vf31xyzw, $vf31xyzw, $vf30xyzw\n" \
        "sqc2 $vf31, 0(%0)\n" \
        : : "r"(out), "r"(a), "r"(b))
#define V_ADD(out, a, b) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "lqc2 $vf30, 0(%2)\n" \
        "vadd.xyzw $vf31xyzw, $vf31xyzw, $vf30xyzw\n" \
        "sqc2 $vf31, 0(%0)\n" \
        : : "r"(out), "r"(a), "r"(b))
#define V_SCALE(out, v, s) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "mfc1 $2, %2\n" \
        "qmtc2 $2, $vf30\n" \
        "vmulx.xyzw $vf31xyzw, $vf31xyzw, $vf30x\n" \
        "sqc2 $vf31, 0(%0)\n" \
        : : "r"(out), "r"(v), "f"(s) : "$2", "memory")
#define V_COPY(dst, src) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "sqc2 $vf31, 0(%0)\n" \
        : : "r"(dst), "r"(src))
#define V_LEN(v) ({ f32 _r; \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "vmul.xyz $vf31xyz, $vf31xyz, $vf31xyz\n" \
        "vaddy.x $vf31x, $vf31x, $vf31y\n" \
        "vaddz.x $vf31x, $vf31x, $vf31z\n" \
        "vsqrt Q, $vf31x\n" \
        "vwaitq\n" \
        "vaddq.x $vf31x, $vf0x, Q\n" \
        "qmfc2 $2, $vf31\n" \
        "mtc1 $2, %0\n" \
        : "=f"(_r) : "r"(v) : "$2", "memory"); _r; })
#define _V_MULMTX(out, a, b) \
    __asm__ volatile( \
        "lqc2 $vf27, 0(%1)\n" \
        "lqc2 $vf28, 16(%1)\n" \
        "lqc2 $vf29, 32(%1)\n" \
        "lqc2 $vf30, 48(%1)\n" \
        "lqc2 $vf31, 0(%2)\n" \
        "vmulax.xyzw ACC, $vf27xyzw, $vf31x\n" \
        "vmadday.xyzw ACC, $vf28xyzw, $vf31y\n" \
        "vmaddaz.xyzw ACC, $vf29xyzw, $vf31z\n" \
        "vmaddw.xyzw $vf26xyzw, $vf30xyzw, $vf31w\n" \
        "sqc2 $vf26, 0(%0)\n" \
        "lqc2 $vf31, 16(%2)\n" \
        "vmulax.xyzw ACC, $vf27xyzw, $vf31x\n" \
        "vmadday.xyzw ACC, $vf28xyzw, $vf31y\n" \
        "vmaddaz.xyzw ACC, $vf29xyzw, $vf31z\n" \
        "vmaddw.xyzw $vf26xyzw, $vf30xyzw, $vf31w\n" \
        "sqc2 $vf26, 16(%0)\n" \
        "lqc2 $vf31, 32(%2)\n" \
        "vmulax.xyzw ACC, $vf27xyzw, $vf31x\n" \
        "vmadday.xyzw ACC, $vf28xyzw, $vf31y\n" \
        "vmaddaz.xyzw ACC, $vf29xyzw, $vf31z\n" \
        "vmaddw.xyzw $vf26xyzw, $vf30xyzw, $vf31w\n" \
        "sqc2 $vf26, 32(%0)\n" \
        "lqc2 $vf31, 48(%2)\n" \
        "vmulax.xyzw ACC, $vf27xyzw, $vf31x\n" \
        "vmadday.xyzw ACC, $vf28xyzw, $vf31y\n" \
        "vmaddaz.xyzw ACC, $vf29xyzw, $vf31z\n" \
        "vmaddw.xyzw $vf26xyzw, $vf30xyzw, $vf31w\n" \
        "sqc2 $vf26, 48(%0)\n" \
        : : "r"(out), "r"(a), "r"(b))
typedef struct {
    u16 unk0;
    u16 flags;
    u8 col[4];
    s32 w8;
    s16 dC;
    s16 dE;
    void *p10;
    s32 w14;
    u8 b18;
    void *p1C;
    u8 pad20[0x10];
} T1Param;
typedef struct {
    u8 pad[8];
    u8 c[4];
} T1Col;
static inline void V_MULMTX(void *out, void *a, void *b) { _V_MULMTX(out, a, b); }
static inline void t1Col(f32 *v, u8 r, u8 g, u8 b, u8 a) {
    v[0] = r;
    v[1] = g;
    v[2] = b;
    v[3] = a;
}
static inline void t1Pos(f32 *v, s16 *c) {
    v[0] = c[0] >> 7;
    v[1] = c[1] >> 7;
    v[2] = c[2] >> 7;
    v[3] = c[3] >> 7;
}
typedef struct {
    s32 frame;
    s32 id;       /* +0x4 */
    u8 pad8[4];
    s16 c[4];     /* +0xC */
    f32 size2;    /* +0x14 */
    f32 len;      /* +0x18 */
    u16 n;        /* +0x1C */
    u8 f800;      /* +0x1E */
    u8 f400;      /* +0x1F */
    u8 work3;     /* +0x20 */
    u8 local;     /* +0x21 */
    u8 b24;       /* +0x22 */
    u8 b25;       /* +0x23 */
} T1XKey;
#define D_00615E64 ((T2Sys *) D_00615E64)
#define D_00615E68 ((T2MtxOwner *) D_00615E68)
/* kh1-decomp session 7, worker w11: pppKeShpTail2Draw, pppKeShpTail2XDraw, pppKeShpTailDraw,
   pppKeShpTailXDraw, pppStepPrograms (hand/nostrict). */
/* ---- from pppKeShpTailXDraw.c ---- */
void pppKeShpTailXDraw(void *obj, T1XKey *key, PppEntry *e) {
    PppMtx m0;
    PppMtx m1;
    PppVec4 pos;
    PppVec4 p0;
    PppVec4 d;
    PppVec4 p1;
    PppVec4 unused;
    PppVec4 col;
    PppVec4 dcol;
    T1Param p;
    s32 i;
    f32 len;
    PppVec4 *v;
    void *src;
    f32 t;
    T2Work *w;
    f32 step;
    f32 rest;
    f32 dl;
    T2ShapeEnt *s;
    f32 seg;
    s32 start;
    s32 last;
    s32 n;
    f32 size;

    if (key->id == 0xFFFF)
        return;
    n = key->n - 1;
    seg = n;
    {
        T1Col *c = PPP_WORK(T1Col, obj, e, 1);
        t1Col(col, c->c[0], c->c[1], c->c[2], c->c[3]);
    }
    t1Pos(pos, key->c);
    PlatVu0SubVector(p0, col, pos);
    PlatVu0DivVector(dcol, p0, seg);
    w = PPP_WORK(T2Work, obj, e, 0);
    s = &D_00615E64->shapes[key->id];
    p.w8 = 0;
    p.b18 = 0;
    p.p10 = m1;
    if (!key->b24)
        p.flags = 128;
    else
        p.flags = 0;
    if (key->b25 == 1)
        p.flags |= 0x10;
    if (key->f800)
        p.flags |= 0x800;
    if (key->f400)
        p.flags |= 0x400;
    if (key->work3)
        p.p1C = PPP_WORK(void, obj, e, 3);
    else
        p.p1C = 0;
    p.dC = 0;
    p.dE = 0;
    {
        T2Shape *sh = s->shape;
        T2Frame *f = sh->f;
        src = (u8 *) sh + f[w->prev].off;
    }
    PlatVu0CopyMatrix(m0, D_00615E68->m);
    size = 1.0f;
    PlatVu0UnitMatrix(m1);
    step = (size - key->size2) / seg;
    len = key->len;
    dl = len * step;
    if (len == 0.0f)
        n = -1;
    last = w->count - 1;
    i = w->idx;
    v = w->v;
    start = i;
    PlatVu0CopyVector(pos, v[i]);
    PlatVu0CopyVector(p0, pos);
    if (i++ == last) i = 0;
    PlatVu0CopyVector(p1, v[i]);
    PlatVu0SubVector(d, p1, p0);
    t = len;
    rest = func_001a9350(d);
    seg = rest;
    for (;;) {
        V_FTOI_U8(p.col, col);
        V_SCALE_XYZ(m1[0], m0[0], size * D_003701F0[0]);
        V_SCALE_XYZ(m1[1], m0[1], size * D_003701F0[1]);
        if (key->local)
            V_APPLY(m1[3], D_00615EB0, pos);
        else
            V_APPLY(m1[3], D_00615FC0, pos);
        V_MULMTX(m1, D_00616040, m1);
        {
            s32 *g = &D_00616224;
            p.w14 = *g;
            *g = func_001b8198(src, &p, s->unk4);
        }
        if (n == 0)
            return;
        V_SUB(col, col, dcol);
        len -= dl;
        size -= step;
        if (len <= 0.0f)
            return;
        if (len <= rest) {
            V_SCALE(pos, d, t / seg);
            V_ADD(pos, p0, pos);
            t += len;
            n--;
            rest -= len;
        } else {
        more:
            if (i++ == last) i = 0;
            if (i == start)
                return;
            V_COPY(p0, p1);
            V_COPY(p1, (f32 *) (i * 16 + (s32) v));
            V_SUB(d, p1, p0);
            t -= seg;
            seg = V_LEN(d);
            rest += seg;
            if (!(len <= rest))
                goto more;
            V_SCALE(pos, d, t / seg);
            V_ADD(pos, p0, pos);
            t += len;
            n--;
            rest -= len;
        }
    }
}
#undef D_00615E64
#undef D_00615E68
#undef V_FTOI_U8
#undef V_SCALE_XYZ
#undef V_APPLY
#undef V_SUB
#undef V_ADD
#undef V_SCALE
#undef V_COPY
#undef V_LEN
#undef _V_MULMTX

/* pppKeShpTail2XFrame (from hand/nostrict/text_00180000_s6_11.c). */
typedef struct {
    u8 pad00[0x10];
    DSlot *slots;
    void *shapes;
} DSys_97040;
typedef struct {
    s16 off;
    s16 dur;
    s8 flags;
    u8 pad5[3];
} PppShapeFrame_97040;
typedef struct {
    u8 pad0[6];
    s16 n;
    u8 pad8[8];
    PppShapeFrame_97040 f[1];
} PppShape_97040;
typedef struct {
    PppShape_97040 *shape;
    s32 unk4;
} PppShapeEnt_97040;
typedef struct {
    u8 pad00[0x14];
    PppShapeEnt_97040 *shapes;
} DSysS_97040;
typedef struct {
    u8 n;          /* +0x0 */
    u8 idx;        /* +0x1 */
    u16 t;         /* +0x2 */
    u16 fr;        /* +0x4 */
    u16 prev;      /* +0x6 */
    u8 pad8[8];
    PppVec4 v[1];  /* +0x10 */
} Tail2XWork;
typedef struct {
    s32 frame;
    s32 id;        /* +0x4 */
    u16 speed;     /* +0x8 */
    u8 padA[0x1C];
    u8 local;      /* +0x26 */
} Tail2XKey;
#define D_00615E64 ((DSys_97040 *) D_00615E64)
void pppKeShpTail2XFrame(PppObject *obj, Tail2XKey *key, PppEntry *e) {
    Tail2XWork *w;
    PppShape_97040 *sh;
    PppShapeFrame_97040 *f;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w = PPP_WORK(Tail2XWork, obj, e, 0);
    if (obj->frame == 0 && obj->unk9D == 0) {
        PppVec4 v;
        f32 *p;
        s32 n;

        if (key->local) {
            PlatVu0ApplyMatrix(v, D_00615E70, D_00615E68->m[3]);
            v[3] = 1.0f;
        } else {
            PlatVu0CopyVector(v, D_00615E68->m[3]);
            v[3] = 1.0f;
        }
        p = w->v[0];
        for (n = w->n; n > 0; n--) {
            PlatVu0CopyVector(p, v);
            p += 4;
        }
    }
    if (w->idx == 0)
        w->idx = w->n;
    w->idx--;
    if (key->local) {
        PlatVu0ApplyMatrix(w->v[w->idx], D_00615E70, D_00615E68->m[3]);
        w->v[w->idx][3] = 1.0f;
    } else {
        func_001a9098(w->v[w->idx], D_00615E68->m[3]);
    }
    {
        u16 fr;

        { PppShapeEnt_97040 *se = &((DSysS_97040 *) D_00615E64)->shapes[key->id]; sh = se->shape; }

        fr = w->fr;
        w->prev = fr;
        f = &sh->f[fr];
        w->t += key->speed;
        if (w->t < f->dur)
            return;
        w->t -= f->dur;
        w->fr = fr + 1;
        if (w->fr < sh->n)
            return;
        {
            s32 fl = f->flags;
            w->t = 0;
            if (fl & 0x80)
                w->fr = 0;
            else
                w->fr--;
        }
    }
}
#undef D_00615E64

/* pppKeShpTail2XDraw (from hand/nostrict/text_00180000_s7_w11.c). */
typedef struct {
    u16 unk0;
    u16 flags;
    u8 col[4];
    s16 d8[4];
    void *p10;
    s32 w14;
    u8 b18;
    void *p1C;
    u8 pad20[0x10];
} T2Param;
typedef struct {
    u8 pad[0xB];
    u8 a;
} T2Col;
#define V_FTOI_U8(dst, src) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "vftoi0.xyzw $vf31xyzw, $vf31xyzw\n" \
        "qmfc2 $2, $vf31\n" \
        "sb $2, 0(%0)\n" \
        "mtsab $0, 4\n" \
        "qfsrv $2, $2, $2\n" \
        "sb $2, 1(%0)\n" \
        "qfsrv $2, $2, $2\n" \
        "sb $2, 2(%0)\n" \
        "qfsrv $2, $2, $2\n" \
        "sb $2, 3(%0)\n" \
        : : "r"(dst), "r"(src) : "$2", "memory")
#define V_SCALE_XYZ(dst, src, s) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "lqc2 $vf29, 0(%0)\n" \
        "mfc1 $2, %2\n" \
        "qmtc2 $2, $vf30\n" \
        "vmulx.xyz $vf29xyz, $vf31xyz, $vf30x\n" \
        "sqc2 $vf29, 0(%0)\n" \
        : : "r"(dst), "r"(src), "f"(s) : "$2", "memory")
#define V_APPLY(out, m, v) \
    __asm__ volatile( \
        "lqc2 $vf27, 0(%1)\n" \
        "lqc2 $vf28, 16(%1)\n" \
        "lqc2 $vf29, 32(%1)\n" \
        "lqc2 $vf30, 48(%1)\n" \
        "lqc2 $vf31, 0(%2)\n" \
        "vmulax.xyzw ACC, $vf27xyzw, $vf31x\n" \
        "vmadday.xyzw ACC, $vf28xyzw, $vf31y\n" \
        "vmaddaz.xyzw ACC, $vf29xyzw, $vf31z\n" \
        "vmaddw.xyzw $vf27xyzw, $vf30xyzw, $vf31w\n" \
        "sqc2 $vf27, 0(%0)\n" \
        : : "r"(out), "r"(m), "r"(v))
#define V_MULMTX(out, a, b) \
    __asm__ volatile( \
        "lqc2 $vf27, 0(%1)\n" \
        "lqc2 $vf28, 16(%1)\n" \
        "lqc2 $vf29, 32(%1)\n" \
        "lqc2 $vf30, 48(%1)\n" \
        "lqc2 $vf31, 0(%2)\n" \
        "vmulax.xyzw ACC, $vf27xyzw, $vf31x\n" \
        "vmadday.xyzw ACC, $vf28xyzw, $vf31y\n" \
        "vmaddaz.xyzw ACC, $vf29xyzw, $vf31z\n" \
        "vmaddw.xyzw $vf26xyzw, $vf30xyzw, $vf31w\n" \
        "sqc2 $vf26, 0(%0)\n" \
        "lqc2 $vf31, 16(%2)\n" \
        "vmulax.xyzw ACC, $vf27xyzw, $vf31x\n" \
        "vmadday.xyzw ACC, $vf28xyzw, $vf31y\n" \
        "vmaddaz.xyzw ACC, $vf29xyzw, $vf31z\n" \
        "vmaddw.xyzw $vf26xyzw, $vf30xyzw, $vf31w\n" \
        "sqc2 $vf26, 16(%0)\n" \
        "lqc2 $vf31, 32(%2)\n" \
        "vmulax.xyzw ACC, $vf27xyzw, $vf31x\n" \
        "vmadday.xyzw ACC, $vf28xyzw, $vf31y\n" \
        "vmaddaz.xyzw ACC, $vf29xyzw, $vf31z\n" \
        "vmaddw.xyzw $vf26xyzw, $vf30xyzw, $vf31w\n" \
        "sqc2 $vf26, 32(%0)\n" \
        "lqc2 $vf31, 48(%2)\n" \
        "vmulax.xyzw ACC, $vf27xyzw, $vf31x\n" \
        "vmadday.xyzw ACC, $vf28xyzw, $vf31y\n" \
        "vmaddaz.xyzw ACC, $vf29xyzw, $vf31z\n" \
        "vmaddw.xyzw $vf26xyzw, $vf30xyzw, $vf31w\n" \
        "sqc2 $vf26, 48(%0)\n" \
        : : "r"(out), "r"(a), "r"(b))
#define V_SUB(out, a, b) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "lqc2 $vf30, 0(%2)\n" \
        "vsub.xyzw $vf31xyzw, $vf31xyzw, $vf30xyzw\n" \
        "sqc2 $vf31, 0(%0)\n" \
        : : "r"(out), "r"(a), "r"(b))
#define V_ADD(out, a, b) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "lqc2 $vf30, 0(%2)\n" \
        "vadd.xyzw $vf31xyzw, $vf31xyzw, $vf30xyzw\n" \
        "sqc2 $vf31, 0(%0)\n" \
        : : "r"(out), "r"(a), "r"(b))
#define V_SCALE(out, v, s) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "mfc1 $2, %2\n" \
        "qmtc2 $2, $vf30\n" \
        "vmulx.xyzw $vf31xyzw, $vf31xyzw, $vf30x\n" \
        "sqc2 $vf31, 0(%0)\n" \
        : : "r"(out), "r"(v), "f"(s) : "$2", "memory")
#define V_COPY(dst, src) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "sqc2 $vf31, 0(%0)\n" \
        : : "r"(dst), "r"(src))
#define V_LEN(v) ({ f32 _r; \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "vmul.xyz $vf31xyz, $vf31xyz, $vf31xyz\n" \
        "vaddy.x $vf31x, $vf31x, $vf31y\n" \
        "vaddz.x $vf31x, $vf31x, $vf31z\n" \
        "vsqrt Q, $vf31x\n" \
        "vwaitq\n" \
        "vaddq.x $vf31x, $vf0x, Q\n" \
        "qmfc2 $2, $vf31\n" \
        "mtc1 $2, %0\n" \
        : "=f"(_r) : "r"(v) : "$2", "memory"); _r; })
static inline void t2Col(f32 *v, u8 *c, f32 a) {
    v[0] = c[0];
    v[1] = c[1];
    v[2] = c[2];
    v[3] = c[3] * a;
}
typedef struct {
    s32 frame;
    s32 id;       /* +0x4 */
    u8 pad8[4];
    f32 size;     /* +0xC */
    f32 size2;    /* +0x10 */
    u8 c0[4];     /* +0x14 */
    u8 c1[4];     /* +0x18 */
    f32 len;      /* +0x1C */
    u16 n;        /* +0x20 */
    u8 draw;      /* +0x22 */
    u8 f800;      /* +0x23 */
    u8 f400;      /* +0x24 */
    u8 work3;     /* +0x25 */
    u8 local;     /* +0x26 */
    u8 b24;       /* +0x27 */
    u8 b25;       /* +0x28 */
} T2XKey;
#define D_00615E64 ((T2Sys *) D_00615E64)
#define D_00615E68 ((T2MtxOwner *) D_00615E68)
/* kh1-decomp session 7, worker w11: pppKeShpTail2Draw, pppKeShpTail2XDraw, pppKeShpTailDraw,
   pppKeShpTailXDraw, pppStepPrograms (hand/nostrict). */
/* ---- from pppKeShpTail2XDraw.c ---- */
void pppKeShpTail2XDraw(void *obj, T2XKey *key, PppEntry *e) {
    PppMtx m0;
    PppMtx m1;
    PppVec4 pos;
    PppVec4 p0;
    PppVec4 d;
    PppVec4 p1;
    PppVec4 col;
    PppVec4 dcol;
    T2Param p;
/*D*/
    s32 i;
    f32 len;
    void *src;
    f32 t;
    T2Work *w;
    f32 step;
    f32 a;
    f32 rest;
    f32 dl;
    T2ShapeEnt *s;
    f32 seg;
    s32 start;
    s32 last;
    s32 n;
    f32 size;
    PppVec4 *v;
/*E*/

    if (key->id == 0xFFFF)
        return;
    len = PPP_WORK(T2Col, obj, e, 1)->a * 0.0078125f;
    n = key->n - 1;
    seg = n;
    t2Col(col, key->c0, len);
    t2Col(pos, key->c1, len);
    PlatVu0SubVector(p0, col, pos);
    PlatVu0DivVector(dcol, p0, seg);
    w = PPP_WORK(T2Work, obj, e, 0);
    s = &D_00615E64->shapes[key->id];
    p.d8[0] = p.d8[1] = p.d8[2] = p.d8[3] = 0;
    p.b18 = 0;
    p.p10 = m1;
    if (!key->b24)
        p.flags = 128;
    else
        p.flags = 0;
    if (key->b25 == 1)
        p.flags |= 0x10;
    if (key->f800)
        p.flags |= 0x800;
    if (key->f400)
        p.flags |= 0x400;
    if (key->work3)
        p.p1C = PPP_WORK(void, obj, e, 3);
    else
        p.p1C = 0;
    {
        T2Shape *sh = s->shape;
        T2Frame *f = sh->f;
        src = (u8 *) sh + f[w->prev].off;
    }
    PlatVu0CopyMatrix(m0, D_00615E68->m);
    PlatVu0UnitMatrix(m1);
    size = key->size;
    len = key->len;
    step = (size - key->size2) / seg;
    dl = len * (step / size);
    if (len == 0.0f)
        n = -1;
    i = w->idx;
    v = w->v;
    start = i;
    last = w->count - 1;
    PlatVu0CopyVector(pos, v[i]);
    PlatVu0CopyVector(p0, pos);
    if (i++ == last) i = 0;
    PlatVu0CopyVector(p1, v[i]);
    PlatVu0SubVector(d, p1, p0);
    t = len;
    rest = func_001a9350(d);
    seg = rest;
    if (!key->draw)
        goto skip;
    for (;;) {
        V_FTOI_U8(p.col, col);
        V_SCALE_XYZ(m1[0], m0[0], size * D_003701F0[0]);
        V_SCALE_XYZ(m1[1], m0[1], size * D_003701F0[1]);
        if (key->local)
            V_APPLY(m1[3], D_00615EB0, pos);
        else
            V_APPLY(m1[3], D_00615FC0, pos);
        V_MULMTX(m1, D_00616040, m1);
        p.w14 = D_00616224;
        D_00616224 = func_001b8198(src, &p, s->unk4);
    skip:
        if (n == 0)
            return;
        V_SUB(col, col, dcol);
        len -= dl;
        size -= step;
        if (len <= 0.0f)
            return;
        if (len <= rest) {
            V_SCALE(pos, d, t / seg);
            V_ADD(pos, p0, pos);
            t += len;
            n--;
        } else {
        more:
            if (i++ == last) i = 0;
            if (i == start)
                return;
            V_COPY(p0, p1);
            V_COPY(p1, (f32 *) (i * 16 + (s32) v));
            V_SUB(d, p1, p0);
            t -= seg;
            seg = V_LEN(d);
            rest += seg;
            if (!(len <= rest))
                goto more;
            V_SCALE(pos, d, t / seg);
            V_ADD(pos, p0, pos);
            t += len;
            n--;
        }
        rest -= len;
    }
}
#undef D_00615E64
#undef D_00615E68
#undef V_FTOI_U8
#undef V_SCALE_XYZ
#undef V_APPLY
#undef V_MULMTX
#undef V_SUB
#undef V_ADD
#undef V_SCALE
#undef V_COPY
#undef V_LEN

/* pppKeShpTail3XFrame (from hand/nostrict/text_00190000_b08.c). */
typedef struct {
    u16 p0[4], p1[4], v0[4], a0[4], v1[4], a1[4];
} PppTail3X;
typedef struct {
    s32 frame;
    s32 id;
    u8 pad8[0x18];
    PppTail3X d;
    u8 pad50[3];
    u8 local;
} PppTail3XKey;
typedef struct {
    PppTail3X h;
    PppVec4 v[28];
    u8 padF0[0xA];
    u8 idx;
} PppTail3XWork;
void pppKeShpTail3XFrame(PppObject *obj, PppTail3XKey *key, PppEntry *e) {
    PppTail3XWork *w;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w = PPP_WORK(PppTail3XWork, obj, e, 0);
    if (obj->frame == 0 && obj->unk9D == 0) {
        PppVec4 v;
        f32 *p;
        s32 n;

        if (key->local) {
            PlatVu0ApplyMatrix(v, D_00615E70, D_00615E68->m[3]);
            v[3] = 1.0f;
        } else {
            PlatVu0CopyVector(v, D_00615E68->m[3]);
            v[3] = 1.0f;
        }
        p = w->v[0];
        for (n = 28; n > 0; n--) {
            PlatVu0CopyVector(p, v);
            p += 4;
        }
    }
    if (w->idx == 0)
        w->idx = 28;
    w->idx--;
    if (key->local) {
        PlatVu0ApplyMatrix(w->v[w->idx], D_00615E70, D_00615E68->m[3]);
        w->v[w->idx][3] = 1.0f;
    } else {
        PlatVu0CopyVector(w->v[w->idx], D_00615E68->m[3]);
    }
    w->h.v0[0] += w->h.a0[0]; w->h.p0[0] += w->h.v0[0];
    w->h.v0[1] += w->h.a0[1]; w->h.p0[1] += w->h.v0[1];
    w->h.v0[2] += w->h.a0[2]; w->h.p0[2] += w->h.v0[2];
    w->h.v0[3] += w->h.a0[3]; w->h.p0[3] += w->h.v0[3];
    w->h.v1[0] += w->h.a1[0]; w->h.p1[0] += w->h.v1[0];
    w->h.v1[1] += w->h.a1[1]; w->h.p1[1] += w->h.v1[1];
    w->h.v1[2] += w->h.a1[2]; w->h.p1[2] += w->h.v1[2];
    w->h.v1[3] += w->h.a1[3]; w->h.p1[3] += w->h.v1[3];
    if (obj->frame == key->frame) {
        w->h.p0[0] += key->d.p0[0];
        w->h.p0[1] += key->d.p0[1];
        w->h.p0[2] += key->d.p0[2];
        w->h.p0[3] += key->d.p0[3];
        w->h.v0[0] += key->d.v0[0];
        w->h.v0[1] += key->d.v0[1];
        w->h.v0[2] += key->d.v0[2];
        w->h.v0[3] += key->d.v0[3];
        w->h.a0[0] += key->d.a0[0];
        w->h.a0[1] += key->d.a0[1];
        w->h.a0[2] += key->d.a0[2];
        w->h.a0[3] += key->d.a0[3];
        w->h.p1[0] += key->d.p1[0];
        w->h.p1[1] += key->d.p1[1];
        w->h.p1[2] += key->d.p1[2];
        w->h.p1[3] += key->d.p1[3];
        w->h.v1[0] += key->d.v1[0];
        w->h.v1[1] += key->d.v1[1];
        w->h.v1[2] += key->d.v1[2];
        w->h.v1[3] += key->d.v1[3];
        w->h.a1[0] += key->d.a1[0];
        w->h.a1[1] += key->d.a1[1];
        w->h.a1[2] += key->d.a1[2];
        w->h.a1[3] += key->d.a1[3];
    }
}

/* pppKeShpTail3XDraw (from hand/nostrict/text_00190000_s10_w1.c). */
void *func_001aa950(s32);
void func_001aa9d0(s32);
extern f32 D_0048FB6C;
extern f32 D_003732D0[];
#define V_FTOI_U8(dst, src) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "vftoi0.xyzw $vf31xyzw, $vf31xyzw\n" \
        "qmfc2 $2, $vf31\n" \
        "sb $2, 0(%0)\n" \
        "mtsab $0, 4\n" \
        "qfsrv $2, $2, $2\n" \
        "sb $2, 1(%0)\n" \
        "qfsrv $2, $2, $2\n" \
        "sb $2, 2(%0)\n" \
        "qfsrv $2, $2, $2\n" \
        "sb $2, 3(%0)\n" \
        : : "r"(dst), "r"(src) : "$2")
#define V_SUB(out, a, b) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "lqc2 $vf30, 0(%2)\n" \
        "vsub.xyzw $vf31xyzw, $vf31xyzw, $vf30xyzw\n" \
        "sqc2 $vf31, 0(%0)\n" \
        : : "r"(out), "r"(a), "r"(b))
typedef kh1_u128 T3Q;
typedef struct {
    s32 frame;
    s32 id;       /* +0x4 */
    s32 tstep;    /* +0x8 */
    f32 size;     /* +0xC */
    f32 size2;    /* +0x10 */
    f32 rs;       /* +0x14 */
    f32 len;      /* +0x18 */
    u8 n;         /* +0x1C */
    u8 draw;      /* +0x1D */
    u16 rot;      /* +0x1E */
    u8 pad20[0x30];
    u8 f800;      /* +0x50 */
    u8 f400;      /* +0x51 */
    u8 work3;     /* +0x52 */
    u8 local;     /* +0x53 */
    u8 b24;       /* +0x54 */
    u8 b25;       /* +0x55 */
} T3XKey;
typedef struct {
    s16 c0[4];    /* +0x0 */
    s16 c1[4];    /* +0x8 */
    u8 pad10[0x20];
    PppVec4 v[28]; /* +0x30 */
    u32 t;        /* +0x1F0 */
    u8 pad1F4[4];
    u16 seed;     /* +0x1F8 */
    u8 idx;       /* +0x1FA */
} T3Work;
typedef struct {
    T3Q a[4];     /* +0x0 */
    T3Q b[4];     /* +0x40 */
    PppVec4 r0;   /* +0x80 */
    PppVec4 r1;   /* +0x90 */
    u8 padA0[0x20];
    PppMtx out;   /* +0xC0 */
    PppVec4 s[3]; /* +0x100 */
    u8 pad130[0x50];
} T3Buf;
typedef struct {
    u8 pad0[6];
    s16 nfr;      /* +0x6 */
    u8 pad8[8];
    T2Frame f[1]; /* +0x10 */
} T3Shape;
#define V3_SCALE2(out, m, s) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%2)\n" \
        "lqc2 $vf30, 0(%1)\n" \
        "lqc2 $vf29, 16(%1)\n" \
        "vmulx.xyz $vf28xyz, $vf30xyz, $vf31x\n" \
        "vmuly.xyz $vf27xyz, $vf29xyz, $vf31y\n" \
        "sqc2 $vf28, 128(%0)\n" \
        "sqc2 $vf27, 144(%0)\n" \
        : : "r"(out), "r"(m), "r"(s))
#define V3_LOAD(b) \
    __asm__ volatile( \
        "lqc2 $vf10, 0(%0)\n" \
        "lqc2 $vf11, 16(%0)\n" \
        "lqc2 $vf12, 32(%0)\n" \
        "lqc2 $vf13, 48(%0)\n" \
        "lqc2 $vf14, 64(%0)\n" \
        "lqc2 $vf15, 80(%0)\n" \
        "lqc2 $vf16, 96(%0)\n" \
        "lqc2 $vf17, 112(%0)\n" \
        "lqc2 $vf6, 128(%0)\n" \
        "lqc2 $vf7, 144(%0)\n" \
        "lqc2 $vf26, 256(%0)\n" \
        "lqc2 $vf27, 272(%0)\n" \
        "lqc2 $vf28, 288(%0)\n" \
        : : "r"(b))
#define V3_INIT(pos, p0, d, p1) \
    __asm__ volatile( \
        "lqc2 $vf29, 0(%0)\n" \
        "lqc2 $vf28, 0(%1)\n" \
        "lqc2 $vf27, 0(%2)\n" \
        "lqc2 $vf26, 0(%3)\n" \
        "vsub.xyzw $vf2xyzw, $vf2xyzw, $vf2xyzw\n" \
        "vsub.xyzw $vf3xyzw, $vf3xyzw, $vf3xyzw\n" \
        "vsub.xyzw $vf4xyzw, $vf4xyzw, $vf4xyzw\n" \
        "vsub.xyzw $vf5xyzw, $vf5xyzw, $vf5xyzw\n" \
        : : "r"(pos), "r"(p0), "r"(d), "r"(p1))
#define V3_SIZE(t) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%0)\n" \
        "vmulx.xyz $vf2xyz, $vf6xyz, $vf31x\n" \
        "vmulx.xyz $vf3xyz, $vf7xyz, $vf31x\n" \
        "vmulax.xyzw ACC, $vf10xyzw, $vf29x\n" \
        "vmadday.xyzw ACC, $vf11xyzw, $vf29y\n" \
        "vmaddaz.xyzw ACC, $vf12xyzw, $vf29z\n" \
        "vmaddw.xyzw $vf5xyzw, $vf13xyzw, $vf0w\n" \
        : : "r"(t))
#define V3_ROT(t) \
    __asm__ volatile( \
        "lqc2 $vf22, 0(%0)\n" \
        "vmove.xyzw $vf23xyzw, $vf2xyzw\n" \
        "vmulay.xyzw ACC, $vf2xyzw, $vf22y\n" \
        "vmaddx.xyzw $vf2xyzw, $vf3xyzw, $vf22x\n" \
        "vmulay.xyzw ACC, $vf3xyzw, $vf22y\n" \
        "vmsubx.xyzw $vf3xyzw, $vf23xyzw, $vf22x\n" \
        : : "r"(t))
#define V3_XF1(r) \
        "vmulax.xyzw ACC, $vf14xyzw, $vf" #r "x\n" \
        "vmadday.xyzw ACC, $vf15xyzw, $vf" #r "y\n" \
        "vmaddaz.xyzw ACC, $vf16xyzw, $vf" #r "z\n" \
        "vmaddw.xyzw $vf" #r "xyzw, $vf17xyzw, $vf" #r "w\n"
#define V3_XFORM() __asm__ volatile(V3_XF1(2) V3_XF1(3) V3_XF1(4) V3_XF1(5))
#define V3_SAVE(b) \
    __asm__ volatile( \
        "sqc2 $vf2, 192(%0)\n" \
        "sqc2 $vf3, 208(%0)\n" \
        "sqc2 $vf4, 224(%0)\n" \
        "sqc2 $vf5, 240(%0)\n" \
        "sqc2 $vf26, 256(%0)\n" \
        "sqc2 $vf27, 272(%0)\n" \
        "sqc2 $vf28, 288(%0)\n" \
        : : "r"(b))
#define V3_POS(t) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%0)\n" \
        "vmulx.xyzw $vf29xyzw, $vf27xyzw, $vf31x\n" \
        "vadd.xyzw $vf29xyzw, $vf28xyzw, $vf29xyzw\n" \
        : : "r"(t))
#define V3_NEXT(v) \
    __asm__ volatile( \
        "vmove.xyzw $vf28xyzw, $vf26xyzw\n" \
        "lqc2 $vf26, 0(%0)\n" \
        "vsub.xyzw $vf27xyzw, $vf26xyzw, $vf28xyzw\n" \
        : : "r"(v))
#define V3_LEN(t) \
    __asm__ volatile( \
        "vmul.xyz $vf31xyz, $vf27xyz, $vf27xyz\n" \
        "vaddy.x $vf30x, $vf31x, $vf31y\n" \
        "vaddz.x $vf31x, $vf30x, $vf31z\n" \
        "vsqrt Q, $vf31x\n" \
        "vwaitq\n" \
        "vaddq.x $vf31x, $vf0x, Q\n" \
        "sqc2 $vf31, 0(%0)\n" \
        : : "r"(t))
#define T3CPY(d, s) \
    (d)[0] = ((T3Q *) (s))[0]; \
    (d)[1] = ((T3Q *) (s))[1]; \
    (d)[2] = ((T3Q *) (s))[2]; \
    (d)[3] = ((T3Q *) (s))[3]
static inline void t3Col(f32 *v, s16 *c, f32 a) {
    v[0] = c[0] >> 7;
    v[1] = c[1] >> 7;
    v[2] = c[2] >> 7;
    v[3] = (c[3] >> 7) * a;
}
#define D_00615E64 ((T2Sys *) D_00615E64)
#define D_00615E68 ((T2MtxOwner *) D_00615E68)
/* kh1-decomp session 10, worker w1: pppKeShpTail3Draw (00191248) and
   pppKeShpTail3XDraw (00197cf8), hand/nostrict.
   The `move a3,sp; lw 288(a3)` reads are a GNU C nested function t3Init
   (inline, declared inside each draw function) that reads the enclosing
   function's `buf` through its static chain: inlined, the chain is the frame
   pointer copied to a pseudo before the key->local if/else, and the copy is
   still used after the join (CSE does not fold it back). Referencing buf from
   the nested function also keeps buf in the frame at sp+288 (the
   reloads after each store come from -fno-strict-aliasing). No volatile,
   no struct overlay. T3CPY must not be do { } while (0): its
   NOTE_INSN_LOOP_BEG blocks sched1. */
void pppKeShpTail3XDraw(void *obj, T3XKey *key, PppEntry *e) {
    PppMtx m0;
    PppMtx m1;
    PppVec4 pos;
    PppVec4 p0;
    PppVec4 d;
    PppVec4 p1;
    PppVec4 tmp;
    PppVec4 col;
    PppVec4 dcol;
    T2Param p;
    T3Buf *buf;
/*D*/
    s32 i;
    f32 len;
    void *src;
    f32 t;
    T3Work *w;
    f32 step;
    f32 rest;
    f32 dl;
    T3Shape *sh;
    T2ShapeEnt *s;
    f32 seg;
    s32 start;
    u32 base;
    s32 dur;
    u32 rnd;
    s32 nfr;
    s32 n;
    f32 size;
    f32 r;
    s32 off;
    s32 last;
    PppVec4 *v;
/*E*/

    inline void t3Init(T3XKey *k) {
        f32 o;
        if (k->local) {
            T3CPY(buf->a, D_00615EB0);
        } else {
            T3CPY(buf->a, D_00615FC0);
        }
        o = D_0048FB6C;
        T3CPY(buf->b, D_00616040);
        buf->out[0][3] = o;
        buf->out[1][3] = o;
        V3_SCALE2(buf, D_00615E68->m, D_003701F0);
    }

    if (key->id == 0xFFFF)
        return;
    off = e->offsets[0];
    w = (T3Work *) ((u8 *) obj + off + 0xA0);
    buf = func_001aa950(384);
    len = PPP_WORK(T2Col, obj, e, 1)->a * 0.0078125f;
    t3Col(col, w->c0, len);
    t3Col(pos, w->c1, len);
    n = key->n - 1;
    seg = n;
    PlatVu0SubVector(p0, col, pos);
    PlatVu0DivVector(dcol, p0, seg);
    s = &D_00615E64->shapes[key->id];
    p.p10 = buf->out;
    p.d8[0] = p.d8[1] = p.d8[2] = p.d8[3] = 0;
    p.b18 = 0;
    if (!key->b24)
        p.flags = 128;
    else
        p.flags = 0;
    if (key->b25 == 1)
        p.flags |= 0x10;
    if (key->f800)
        p.flags |= 0x800;
    if (key->f400)
        p.flags |= 0x400;
    if (key->work3)
        p.p1C = PPP_WORK(void, obj, e, 3);
    else
        p.p1C = 0;
    sh = (T3Shape *) s->shape;
    PlatVu0CopyMatrix(m0, D_00615E68->m);
    PlatVu0UnitMatrix(m1);
    size = key->size;
    len = key->len;
    step = (size - key->size2) / seg;
    dl = len * (step / size);
    if (len == 0.0f)
        n = -1;
    i = w->idx;
    v = w->v;
    start = i;
    last = 27;
    PlatVu0CopyVector(pos, v[i]);
    PlatVu0CopyVector(p0, pos);
    if (i++ == last) i = 0;
    PlatVu0CopyVector(p1, v[i]);
    PlatVu0SubVector(d, p1, p0);
    t = len;
    rest = func_001a9350(d);
    seg = rest;
    base = w->t;
    rnd = w->seed;
    dur = sh->f[0].dur;
    nfr = sh->nfr;
    t3Init(key);
    V3_LOAD(buf);
    V3_INIT(pos, p0, d, p1);
    if (!key->draw)
        goto skip;
    {
    loop:
        rnd = (rnd * 2061 + 7) & 0xFFFF;
        r = rnd / 65535.0f;
        src = (u8 *) sh + sh->f[((base + rnd) / dur) % nfr].off;
        V_FTOI_U8(p.col, col);
        r = 1.0f - r * key->rs;
        tmp[0] = size * r;
        V3_SIZE(tmp);
        if (key->rot) {
            tmp[0] = D_003732D0[rnd >> 4];
            tmp[1] = D_003732D0[((rnd + 0x4000) >> 4) & 0xFFF];
            V3_ROT(tmp);
        }
        V3_XFORM();
        p.w14 = D_00616224;
        V3_SAVE(buf);
        {
            s32 *g = &D_00616224;
            *g = func_001b8198(src, &p, s->unk4);
        }
        V3_LOAD(buf);
    skip:
        if (n == 0)
            goto end;
        V_SUB(col, col, dcol);
        len -= dl;
        size -= step;
        if (len <= 0.0f)
            goto end;
        if (len <= rest) {
            tmp[0] = t / seg;
            V3_POS(tmp);
            t += len;
            n--;
        } else {
        more:
            if (i++ == last) i = 0;
            if (i == start)
                goto end;
            V3_NEXT(v[i]);
            t -= seg;
            V3_LEN(tmp);
            seg = tmp[0];
            rest += seg;
            if (!(len <= rest))
                goto more;
            tmp[0] = t / seg;
            V3_POS(tmp);
            t += len;
            n--;
        }
        rest -= len;
        goto loop;
    }
end:
    w->t += key->tstep;
    func_001aa9d0(384);
}
#undef D_00615E64
#undef D_00615E68
#undef V_FTOI_U8
#undef V_SUB
#undef V3_SCALE2
#undef V3_LOAD
#undef V3_INIT
#undef V3_SIZE
#undef V3_ROT
#undef V3_XF1
#undef V3_XFORM
#undef V3_SAVE
#undef V3_POS
#undef V3_NEXT
#undef V3_LEN
#undef T3CPY

#include "data/pieces/D_003701D0.h"
#include "data/pieces/D_003727B0.h"
#include "data/types/nostrict_text_00180000_s6_11.h"
#include "data/data_0037.h"
#include "data/data_0048.h"
