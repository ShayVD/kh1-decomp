/* pppKeShpTail3XDraw (00197cf8), hand/nostrict. ARTIFICIAL SHAPE (flagged): the `move a3,sp; lw 288(a3)` reads come from an inline helper that takes the frame as a struct overlay, t3Init((T3Loc *) m0, key), where T3Loc mirrors the local layout (m0 at sp+0 ... buf at sp+288). A real locals struct would round to 304 bytes and move the spill slots. The if/else copy lives in the helper (the a3 copy is set before the branch, used after the join where CSE cannot fold it). T3CPY must not be do { } while (0): its NOTE_INSN_LOOP_BEG blocks sched1. */
#include "common.h"
#include "ppp.h"

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


typedef unsigned int T3Q __attribute__((mode(TI)));

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

typedef struct {
    f32 m0[4][4];
    f32 m1[4][4];
    f32 pos[4];
    f32 p0[4];
    f32 d[4];
    f32 p1[4];
    f32 tmp[4];
    f32 col[4];
    f32 dcol[4];
    T2Param p;
    T3Buf *buf;
} T3Loc;

static inline void t3Init(T3Loc *l, T3XKey *key) {
    f32 o;
    if (key->local) {
        T3CPY(l->buf->a, D_00615EB0);
    } else {
        T3CPY(l->buf->a, D_00615FC0);
    }
    o = D_0048FB6C;
    T3CPY(l->buf->b, D_00616040);
    l->buf->out[0][3] = o;
    l->buf->out[1][3] = o;
    V3_SCALE2(l->buf, D_00615E68->m, D_003701F0);
}

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
    T3Buf *volatile buf;
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
    func_00267530(p0, col, pos);
    func_002674b0(dcol, p0, seg);
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
    last = 27;
    func_002675a8(pos, v[i]);
    func_002675a8(p0, pos);
    if (i++ == last) i = 0;
    func_002675a8(p1, v[i]);
    func_00267530(d, p1, p0);
    t = len;
    rest = func_001a9350(d);
    seg = rest;
    base = w->t;
    rnd = w->seed;
    dur = sh->f[0].dur;
    nfr = sh->nfr;
    t3Init((T3Loc *) m0, key);
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
