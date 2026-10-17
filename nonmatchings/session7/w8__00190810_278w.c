/* func_00190810 (pppKeShpTail2Draw), hand/nostrict: 1564 vs 1572 bytes, sequence-diff 83 insns (checkfile 278 words, shifted). C + inline asm macros (V_* below: lqc2/sqc2/qmtc2 helpers as #define, not static inline - inline functions get cross-jumped/merged, orig keeps both copies). Found: variable reuse (len holds the alpha first, seg holds (f32)n first), 'if (i++ == last) i = 0', V_LEN as a statement expression, if/else with the interpolation tail written twice. Still off: register allocation - orig n in s4 and start/last spilled (280/284), p1/d addresses in s5/s6 re-set inside the loop (move s5,a0 / move s6,v1); ours spills n. The 2 missing words are probably the loop-head alignment nops at 0x190af4 and 0x190d0c. Flag sweep: nothing. */
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
s32 func_001b8198(void *, T2Param *, s32);

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
        : : "r"(out), "r"(m), "r"(v) : "memory")

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
        : : "r"(out), "r"(a), "r"(b) : "memory")

#define V_SUB(out, a, b) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "lqc2 $vf30, 0(%2)\n" \
        "vsub.xyzw $vf31xyzw, $vf31xyzw, $vf30xyzw\n" \
        "sqc2 $vf31, 0(%0)\n" \
        : : "r"(out), "r"(a), "r"(b) : "memory")

#define V_ADD(out, a, b) \
    __asm__ volatile( \
        "lqc2 $vf31, 0(%1)\n" \
        "lqc2 $vf30, 0(%2)\n" \
        "vadd.xyzw $vf31xyzw, $vf31xyzw, $vf30xyzw\n" \
        "sqc2 $vf31, 0(%0)\n" \
        : : "r"(out), "r"(a), "r"(b) : "memory")

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
        : : "r"(dst), "r"(src) : "memory")

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
    s32 last;
    s32 n;
    s32 start;
    f32 size;
    PppVec4 *v;
/*E*/

    f32 *Pp1 = p1;
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
        src = (u8 *) sh + sh->f[w->prev].off;
    }
    sceVu0CopyMatrix(m0, D_00615E68->m);
    sceVu0UnitMatrix(m1);
    size = key->size;
    len = key->len;
    step = (size - key->size2) / seg;
    dl = len * (step / size);
    if (len == 0.0f)
        n = -1;
    start = w->idx;
    v = w->v;
    i = start;
    last = w->count - 1;
    func_002675a8(pos, v[i]);
    func_002675a8(p0, pos);
    if (i++ == last) i = 0;
    func_002675a8(Pp1, v[i]);
    func_00267530(d, Pp1, p0);
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
        } else {
            do {
                if (i++ == last) i = 0;
                if (i == start)
                    return;
                V_COPY(p0, Pp1);
                V_COPY(Pp1, v[i]);
                V_SUB(d, Pp1, p0);
                t -= seg;
                seg = V_LEN(d);
                rest += seg;
            } while (!(len <= rest));
            V_SCALE(pos, d, t / seg);
            V_ADD(pos, p0, pos);
            t += len;
        }
        n--;
        rest -= len;
    }
}
