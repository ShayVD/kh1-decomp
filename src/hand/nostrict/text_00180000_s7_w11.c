#include "common.h"
#include "ppp.h"
/* kh1-decomp session 7, worker w11: pppKeShpTail2Draw, pppKeShpTail2XDraw, pppKeShpTailDraw,
   pppKeShpTailXDraw, pppStepPrograms (hand/nostrict). */

/* ---- from pppKeShpTail2Draw.c ---- */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef f32 PppVec4[4] __attribute__((aligned(16)));

typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} T2MtxOwner;

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
    u8 local;     /* +0x23 */
    u8 b24;       /* +0x24 */
    u8 b25;       /* +0x25 */
} T2Key;

typedef struct {
    u8 count;     /* +0x0 */
    u8 idx;       /* +0x1 */
    u16 time;     /* +0x2 */
    u16 frame;    /* +0x4 */
    u16 prev;     /* +0x6 */
    u8 pad8[8];
    PppVec4 v[1]; /* +0x10 */
} T2Work;

typedef struct {
    u8 pad[0xB];
    u8 a;
} T2Col;

extern T2Sys *D_00615E64;

extern T2MtxOwner *D_00615E68;

extern s32 D_00616224;

extern f32 D_003701F0[];

extern PppMtx D_00615EB0;

extern PppMtx D_00615FC0;

extern PppMtx D_00616040;

void func_00267530(f32 *, f32 *, f32 *);

void func_002674b0(f32 *, f32 *, f32);

void func_002675a8(f32 *, f32 *);

f32 func_001a9350(f32 *);

void sceVu0CopyMatrix(PppMtx, PppMtx);

void sceVu0UnitMatrix(PppMtx);

s32 func_001b8198(void *, void *, s32);

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

void pppKeShpTail2Draw(void *obj, T2Key *key, PppEntry *e) {
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
    func_00267530(p0, col, pos);
    func_002674b0(dcol, p0, seg);
    w = PPP_WORK(T2Work, obj, e, 0);
    s = &D_00615E64->shapes[key->id];
    p.d8[0] = p.d8[1] = p.d8[2] = p.d8[3] = 0;
    p.b18 = 0;
    p.p10 = m1;
    p.p1C = 0;
    if (!key->b24)
        p.flags = 128;
    else
        p.flags = 0;
    if (key->b25 == 1)
        p.flags |= 0x10;
    {
        T2Shape *sh = s->shape;
        T2Frame *f = sh->f;
        src = (u8 *) sh + f[w->prev].off;
    }
    sceVu0CopyMatrix(m0, D_00615E68->m);
    sceVu0UnitMatrix(m1);
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
    func_002675a8(pos, v[i]);
    func_002675a8(p0, pos);
    if (i++ == last) i = 0;
    func_002675a8(p1, v[i]);
    func_00267530(d, p1, p0);
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

/* ---- from pppKeShpTail2XDraw.c ---- */
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
    func_00267530(p0, col, pos);
    func_002674b0(dcol, p0, seg);
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
    sceVu0CopyMatrix(m0, D_00615E68->m);
    sceVu0UnitMatrix(m1);
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
    func_002675a8(pos, v[i]);
    func_002675a8(p0, pos);
    if (i++ == last) i = 0;
    func_002675a8(p1, v[i]);
    func_00267530(d, p1, p0);
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

/* ---- from pppKeShpTailDraw.c ---- */
#undef V_MULMTX
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
    s32 frame;
    s32 id;       /* +0x4 */
    u8 pad8[4];
    s16 c[4];     /* +0xC */
    f32 size2;    /* +0x14 */
    f32 len;      /* +0x18 */
    u16 n;        /* +0x1C */
    u8 local;     /* +0x1E */
    u8 b24;       /* +0x1F */
    u8 b25;       /* +0x20 */
} T1Key;

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

void pppKeShpTailDraw(void *obj, T1Key *key, PppEntry *e) {
    PppMtx m0;
    PppMtx m1;
    PppVec4 pos;
    PppVec4 p0;
    PppVec4 d;
    PppVec4 p1;
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
    func_00267530(p0, col, pos);
    func_002674b0(dcol, p0, seg);
    w = PPP_WORK(T2Work, obj, e, 0);
    s = &D_00615E64->shapes[key->id];
    p.w8 = 0;
    p.b18 = 0;
    p.p10 = m1;
    p.p1C = 0;
    if (!key->b24)
        p.flags = 128;
    else
        p.flags = 0;
    if (key->b25 == 1)
        p.flags |= 0x10;
    p.dC = 0;
    p.dE = 0;
    {
        T2Shape *sh = s->shape;
        T2Frame *f = sh->f;
        src = (u8 *) sh + f[w->prev].off;
    }
    sceVu0CopyMatrix(m0, D_00615E68->m);
    V_SCALE_XYZ(m0[0], m0[0], D_003701F0[0]);
    V_SCALE_XYZ(m0[1], m0[1], D_003701F0[1]);
    size = 1.0f;
    sceVu0UnitMatrix(m1);
    step = (size - key->size2) / seg;
    len = key->len;
    dl = len * step;
    if (len == 0.0f)
        n = -1;
    last = w->count - 1;
    i = w->idx;
    v = w->v;
    start = i;
    func_002675a8(pos, v[i]);
    func_002675a8(p0, pos);
    if (i++ == last) i = 0;
    func_002675a8(p1, v[i]);
    func_00267530(d, p1, p0);
    t = len;
    rest = func_001a9350(d);
    seg = rest;
    for (;;) {
        V_FTOI_U8(p.col, col);
        V_SCALE_XYZ(m1[0], m0[0], size);
        V_SCALE_XYZ(m1[1], m0[1], size);
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

/* ---- from pppKeShpTailXDraw.c ---- */
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
    func_00267530(p0, col, pos);
    func_002674b0(dcol, p0, seg);
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
    sceVu0CopyMatrix(m0, D_00615E68->m);
    size = 1.0f;
    sceVu0UnitMatrix(m1);
    step = (size - key->size2) / seg;
    len = key->len;
    dl = len * step;
    if (len == 0.0f)
        n = -1;
    last = w->count - 1;
    i = w->idx;
    v = w->v;
    start = i;
    func_002675a8(pos, v[i]);
    func_002675a8(p0, pos);
    if (i++ == last) i = 0;
    func_002675a8(p1, v[i]);
    func_00267530(d, p1, p0);
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

/* ---- from func_001830a0.c ---- */
typedef struct PppObjS PppObjS;

typedef struct {
    PppClass *cls;
    u16 stride;
    u16 pad6;
    void *data;
    s32 *offsets;
} PppEnt;

typedef struct {
    u8 pad00[0x14];
    u32 life;          /* +0x14 */
    s32 start;         /* +0x18 */
    s32 delay;         /* +0x1C */
    s32 dataoff;       /* +0x20 */
    s16 pad24;
    s16 n;             /* +0x26 */
    PppEnt ent[1];     /* +0x28 */
} PppProgS;

struct PppObjS {
    PppObjS *next;     /* +0x00 */
    s32 unk04;
    PppProgS **prog;   /* +0x08 */
    s32 frame;         /* +0x0C */
    u8 pad10[0x8C];
    u8 skip;           /* +0x9C */
    u8 b9D;            /* +0x9D */
    u8 reset;          /* +0x9E */
};

typedef struct {
    PppProgS *prog;    /* +0x0 */
    PppObjS *obj;      /* +0x4 */
    s32 unk8;
    u16 n;             /* +0xC */
    u16 padE;
} PppSlotS;

typedef struct {
    u8 pad00[0x68];
    s32 nslot;         /* +0x68 */
    u8 pad6C[8];
    PppObjS *list;     /* +0x74 */
    u8 pad78[8];
    PppSlotS *slots;   /* +0x80 */
    u8 unk84;
    u8 unk85;          /* +0x85 */
    u8 pad86[0x2A];
    u64 flags;         /* +0xB0 */
} PppSysS;

typedef union {
    void *p;
    s16 h;
} PppDSlot;

typedef void (*PppStepFn)(PppObjS *, void *, PppEnt *);

extern s32 D_0061621C;

extern PppSysS *D_00615E60;

#define D_00615E68 (*(PppObjS **) &D_00615E68)

extern s32 D_00616234[1];

extern PppStepFn D_003701C0[];

void pppResetComponents(PppObjS *);

void pppDesObject(PppObjS *);

static inline void stepObj(PppObjS *o) {
/*D*/
    PppProgS *p;
    PppDSlot *d;
    s32 i;
    PppEnt *e;
/*E*/
    p = *o->prog;
    d = (PppDSlot *) ((u8 *) o + p->dataoff);

    D_00615E68 = o;
    for (i = 0; i < p->n; i++) {
        PppClass *c;
        e = &p->ent[i];
        c = e->cls;
        if (c) {
            void *data = d->p;
            s32 *nx = (s32 *) ((u8 *) data + e->stride);
            PppStepFn fn;
            if (*nx == o->frame) {
                data = nx;
                (d++)->p = data;
            } else
                d++;
            fn = (PppStepFn) c->frame;
            if (fn) {
                s32 found = 0;
                PppStepFn *q;
                for (q = D_003701C0; *q; q++) {
                    if (fn == *q) {
                        found = 1;
                        break;
                    }
                }
                if (!found)
                    fn(o, data, e);
            }
        }
    }
    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        o->frame += 0x1000;
        if (o->frame > 0x6FFFFFFF)
            o->frame = 0x70000000;
    }
}

void pppStepPrograms(PppSysS *sys, s32 draw) {
    s32 i;

    for (i = 0; i < sys->nslot; i++) {
        PppSlotS *sl = &sys->slots[i];
        PppProgS *p = sl->prog;
        s32 k;

        if (sl->n == 0)
            continue;
        for (k = 0; k < p->n; k++) {
            PppEnt *e = &p->ent[k];
            PppObjS *o = sl->obj;
            PppStepFn ffn, dfn;
            s32 n;

            dfn = (PppStepFn) e->cls->draw;
            ffn = (PppStepFn) e->cls->frame;

            if (!dfn)
                continue;
            if (ffn) {
                n = sl->n;
                do {
                    PppObjS *next = o->next;
                    void **d = (void **) ((u8 *) o + p->dataoff + k * 4);
                    if (!o->skip) {
                        void *data = *d;
                        s32 *nx = (s32 *) ((u8 *) data + e->stride);
                        D_00615E68 = o;
                        if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL) && o->reset) {
                            o->frame = 0;
                            o->b9D = 1;
                            pppResetComponents(o);
                            o->reset = 0;
                        }
                        if (*nx == o->frame) {
                            data = nx;
                            *d = data;
                        }
                        ffn(o, data, e);
                        if (draw)
                            dfn(o, data, e);
                    }
                    o = next;
                } while (--n);
            } else {
                n = sl->n;
                do {
                    void **d = (void **) ((u8 *) o + p->dataoff + k * 4);
                    if (!o->skip) {
                        void *data = *d;
                        s32 *nx = (s32 *) ((u8 *) data + e->stride);
                        D_00615E68 = o;
                        if (*nx == o->frame) {
                            data = nx;
                            *d = data;
                        }
                        if (draw)
                            dfn(o, data, e);
                    }
                    o = o->next;
                } while (--n);
            }
        }
        if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
            PppObjS *o = sl->obj;
            s32 n = sl->n;
            do {
                if (!o->skip) {
                    o->frame += 0x1000;
                    if (o->frame > 0x6FFFFFFF)
                        o->frame = 0x70000000;
                } else
                    o->skip = 0;
                o = o->next;
            } while (--n);
        }
    }
    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        u32 acc = 0;
        PppObjS **prev = &sys->list;
        PppObjS *o = *prev;
        PppObjS *next;

        for (; o; o = next) {
            PppProgS *p;
            next = o->next;
            p = *o->prog;

            if (!sys->unk85 && !(o->frame < p->delay) && !(p->start > 0x6FFFFFFF) && !(p->delay > 0x6FFFFFFF)) {
                o->frame = 0;
                o->b9D = 1;
                pppResetComponents(o);
                if (p->start == 0) {
                    D_00616234[0] = 1;
                    stepObj(o);
                    D_00616234[0] = 0;
                    o->reset = 1;
                } else {
                    D_00616234[0] = 1;
                    while (o->frame < p->start)
                        stepObj(o);
                    D_00616234[0] = 0;
                }
            } else {
                acc |= p->life;
                if ((u32) o->frame >= p->life) {
                    *prev = next;
                    pppDesObject(o);
                    continue;
                }
            }
            prev = &o->next;
        }
        if (sys->unk85 && acc == 0x70000000) {
            PppObjS *q = sys->list;
            while (q) {
                PppObjS *nx = q->next;
                pppDesObject(q);
                q = nx;
            }
            sys->list = 0;
        }
    }
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
void func_0019cd90();
void func_001a0778();
PppStepFn D_003701C0[0x4] ALIGNED(16) = {
    (void *)func_0019cd90, (void *)func_001a0778, 0, 0,
};
