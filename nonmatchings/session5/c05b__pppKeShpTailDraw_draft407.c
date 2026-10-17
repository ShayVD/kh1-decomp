#define CL_vuCopy  
#define CL_vuSub  
#define CL_vuAdd  
#define CL_vuScale : "$2"
#define CL_vuLen : "$2"
#include "common.h"
#include "ppp.h"
#ifndef CLOB
#define CLOB

#ifndef CL_vuLen
#define CL_vuLen : "$2", "memory"
#endif
#ifndef CL_vuCopy
#define CL_vuCopy : "memory"
#endif
#ifndef CL_vuScale
#define CL_vuScale : "$2", "memory"
#endif
#ifndef CL_vuAdd
#define CL_vuAdd : "memory"
#endif
#ifndef CL_vuSub
#define CL_vuSub : "memory"
#endif
#ifndef CL_vuMulMatrix
#define CL_vuMulMatrix : "memory"
#endif
#ifndef CL_vuApply2
#define CL_vuApply2 : "memory"
#endif
#ifndef CL_vuApply
#define CL_vuApply : "memory"
#endif
#ifndef CL_vuScaleXYZ
#define CL_vuScaleXYZ : "$2", "memory"
#endif
#ifndef CL_vuFtoi0Bytes
#define CL_vuFtoi0Bytes : "$2", "memory"
#endif
#endif
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef int u128 __attribute__((mode(TI)));
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
typedef f32 PppVec4[4] __attribute__((aligned(16)));

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame;
} PppObject;

typedef struct {
    u8 pad[0x10];
    PppMtx m;
    PppMtx m2;
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;

typedef struct {
    s16 off;
    s16 dur;
    s8 flags;
    u8 pad5[3];
} PppShapeFrame;
typedef struct {
    u8 pad0[6];
    s16 n;
    u8 pad8[8];
    PppShapeFrame f[1];
} PppShape;
typedef struct {
    PppShape *shape;
    s32 unk4;
} PppShapeEnt;
typedef struct {
    u8 pad00[0x14];
    PppShapeEnt *shapes;
} DSysS;
extern DSysS *D_00615E64;
extern s32 D_00616224;

typedef struct {
    u16 unk0;
    u16 flags;
    u8 r, g, b, a;
    u16 h8[4];
    void *p10;
    s32 w14;
    u8 b18;
    void *p1C;
    u8 pad20[0x10];
} TailParam;

extern f32 D_003701F0[2];
extern PppMtx D_00615EB0, D_00615FC0, D_00616040;

void sceVu0CopyMatrix(PppMtx, PppMtx);
void sceVu0UnitMatrix(PppMtx);
void func_00267530(f32 *, f32 *, f32 *);
void func_002674b0(f32 *, f32 *, f32);
void func_002675a8(f32 *, f32 *);
f32 func_001a9350(f32 *);
s32 func_001b8198(void *, TailParam *, s32);

static inline void vuFtoi0Bytes(u8 *d, f32 *s) {
    __asm__ volatile(
        "lqc2 $vf31, 0(%1)\n"
        "vftoi0.xyzw $vf31xyzw, $vf31xyzw\n"
        "qmfc2 $2, $vf31\n"
        "sb $2, 0(%0)\n"
        "mtsab $0, 4\n"
        "qfsrv $2, $2, $2\n"
        "sb $2, 1(%0)\n"
        "qfsrv $2, $2, $2\n"
        "sb $2, 2(%0)\n"
        "qfsrv $2, $2, $2\n"
        "sb $2, 3(%0)\n"
        : : "r"(d), "r"(s) CL_vuFtoi0Bytes);
}

static inline void vuScaleXYZ(f32 *d, f32 *s, f32 f) {
    __asm__ volatile(
        "lqc2 $vf31, 0(%1)\n"
        "lqc2 $vf29, 0(%0)\n"
        "mfc1 $2, %2\n"
        "qmtc2 $2, $vf30\n"
        "vmulx.xyz $vf29xyz, $vf31xyz, $vf30x\n"
        "sqc2 $vf29, 0(%0)\n"
        : : "r"(d), "r"(s), "f"(f) CL_vuScaleXYZ);
}

static inline void vuApply(f32 *d, PppMtx m, f32 *v) {
    __asm__ volatile(
        "lqc2 $vf27, 0(%1)\n"
        "lqc2 $vf28, 16(%1)\n"
        "lqc2 $vf29, 32(%1)\n"
        "lqc2 $vf30, 48(%1)\n"
        "lqc2 $vf31, 0(%2)\n"
        "vmulax.xyzw ACCxyzw, $vf27xyzw, $vf31x\n"
        "vmadday.xyzw ACCxyzw, $vf28xyzw, $vf31y\n"
        "vmaddaz.xyzw ACCxyzw, $vf29xyzw, $vf31z\n"
        "vmaddw.xyzw $vf27xyzw, $vf30xyzw, $vf31w\n"
        "sqc2 $vf27, 0(%0)\n"
        : : "r"(d), "r"(m), "r"(v) CL_vuApply);
}

static inline void vuApply2(f32 *d, PppMtx m, f32 *v) {
    __asm__ volatile(
        "lqc2 $vf27, 0(%1)\n"
        "lqc2 $vf28, 16(%1)\n"
        "lqc2 $vf29, 32(%1)\n"
        "lqc2 $vf30, 48(%1)\n"
        "lqc2 $vf31, 0(%2)\n"
        "vmulax.xyzw ACCxyzw, $vf27xyzw, $vf31x\n"
        "vmadday.xyzw ACCxyzw, $vf28xyzw, $vf31y\n"
        "vmaddaz.xyzw ACCxyzw, $vf29xyzw, $vf31z\n"
        "vmaddw.xyzw $vf27xyzw, $vf30xyzw, $vf31w\n"
        "sqc2 $vf27, 0(%0)\n\t"
        : : "r"(d), "r"(m), "r"(v) CL_vuApply2);
}

static inline void vuMulMatrix(PppMtx d, PppMtx a, PppMtx b) {
    __asm__ volatile(
        "lqc2 $vf27, 0(%1)\n"
        "lqc2 $vf28, 16(%1)\n"
        "lqc2 $vf29, 32(%1)\n"
        "lqc2 $vf30, 48(%1)\n"
        "lqc2 $vf31, 0(%2)\n"
        "vmulax.xyzw ACCxyzw, $vf27xyzw, $vf31x\n"
        "vmadday.xyzw ACCxyzw, $vf28xyzw, $vf31y\n"
        "vmaddaz.xyzw ACCxyzw, $vf29xyzw, $vf31z\n"
        "vmaddw.xyzw $vf26xyzw, $vf30xyzw, $vf31w\n"
        "sqc2 $vf26, 0(%0)\n"
        "lqc2 $vf31, 16(%2)\n"
        "vmulax.xyzw ACCxyzw, $vf27xyzw, $vf31x\n"
        "vmadday.xyzw ACCxyzw, $vf28xyzw, $vf31y\n"
        "vmaddaz.xyzw ACCxyzw, $vf29xyzw, $vf31z\n"
        "vmaddw.xyzw $vf26xyzw, $vf30xyzw, $vf31w\n"
        "sqc2 $vf26, 16(%0)\n"
        "lqc2 $vf31, 32(%2)\n"
        "vmulax.xyzw ACCxyzw, $vf27xyzw, $vf31x\n"
        "vmadday.xyzw ACCxyzw, $vf28xyzw, $vf31y\n"
        "vmaddaz.xyzw ACCxyzw, $vf29xyzw, $vf31z\n"
        "vmaddw.xyzw $vf26xyzw, $vf30xyzw, $vf31w\n"
        "sqc2 $vf26, 32(%0)\n"
        "lqc2 $vf31, 48(%2)\n"
        "vmulax.xyzw ACCxyzw, $vf27xyzw, $vf31x\n"
        "vmadday.xyzw ACCxyzw, $vf28xyzw, $vf31y\n"
        "vmaddaz.xyzw ACCxyzw, $vf29xyzw, $vf31z\n"
        "vmaddw.xyzw $vf26xyzw, $vf30xyzw, $vf31w\n"
        "sqc2 $vf26, 48(%0)\n"
        : : "r"(d), "r"(a), "r"(b) CL_vuMulMatrix);
}

static inline void vuSub(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf31, 0(%1)\n"
        "lqc2 $vf30, 0(%2)\n"
        "vsub.xyzw $vf31xyzw, $vf31xyzw, $vf30xyzw\n"
        "sqc2 $vf31, 0(%0)\n"
        : : "r"(d), "r"(a), "r"(b) CL_vuSub);
}

static inline void vuAdd(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf31, 0(%1)\n"
        "lqc2 $vf30, 0(%2)\n"
        "vadd.xyzw $vf31xyzw, $vf31xyzw, $vf30xyzw\n"
        "sqc2 $vf31, 0(%0)\n"
        : : "r"(d), "r"(a), "r"(b) CL_vuAdd);
}

static inline void vuScale(f32 *d, f32 *s, f32 f) {
    __asm__ volatile(
        "lqc2 $vf31, 0(%1)\n"
        "mfc1 $2, %2\n"
        "qmtc2 $2, $vf30\n"
        "vmulx.xyzw $vf31xyzw, $vf31xyzw, $vf30x\n"
        "sqc2 $vf31, 0(%0)\n"
        : : "r"(d), "r"(s), "f"(f) CL_vuScale);
}

static inline void vuCopy(f32 *d, f32 *s) {
    __asm__ volatile(
        "lqc2 $vf31, 0(%1)\n"
        "sqc2 $vf31, 0(%0)\n"
        : : "r"(d), "r"(s) CL_vuCopy);
}

static inline f32 vuLen(f32 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf31, 0(%1)\n"
        "vmul.xyz $vf31xyz, $vf31xyz, $vf31xyz\n"
        "vaddy.x $vf31x, $vf31x, $vf31y\n"
        "vaddz.x $vf31x, $vf31x, $vf31z\n"
        "vsqrt Q, $vf31x\n"
        "vwaitq\n"
        "vaddq.x $vf31x, $vf0x, Q\n"
        "qmfc2 $2, $vf31\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(v) CL_vuLen);
    return r;
}


typedef struct {
    u8 n;          /* +0x0 */
    u8 idx;        /* +0x1 */
    u8 pad2[4];
    u16 frame;     /* +0x6 */
    u8 pad8[8];
    PppVec4 pts[1]; /* +0x10 */
} Tail2Work;

typedef struct {
    s32 frame;
    s32 id;        /* +0x04 */
    u8 pad8[4];
    s16 col[4];    /* +0x0C */
    f32 size2;     /* +0x14 */
    f32 len;       /* +0x18 */
    u16 n;         /* +0x1C */
    u8 local;      /* +0x1E */
    u8 b1F;        /* +0x1F */
    u8 b20;        /* +0x20 */
} TailKey;

typedef struct {
    u8 pad[8];
    u8 c[4];
} TailCol;

typedef struct {
    u16 unk0;
    u16 flags;
    u8 r, g, b, a;
    s32 w8;
    s16 hC, hE;
    void *p10;
    s32 w14;
    u8 b18;
    void *p1C;
    u8 pad20[0x10];
} TailParamA;

s32 func_001b8198();

void pppKeShpTailDraw(PppObject *obj, TailKey *key, PppEntry *e) {
    PppMtx m0;
    PppMtx m1;
    PppVec4 a;
    PppVec4 b;
    PppVec4 f;
    PppVec4 ev;
    PppVec4 c;
    PppVec4 d;
    TailParamA p;
    Tail2Work *w;
    u8 *src;
    PppShapeEnt *s;
    TailCol *col;
    s32 n, idx, last, j, cnt;
    f32 fn, sz, t, step, dt, rem, len, seg;
    f32 *pa, *pe, *pf, (*pm)[4];
    PppVec4 *pts;

    if (key->id == 0xFFFF)
        return;
    pa = a;
    col = PPP_WORK(TailCol, obj, e, 1);
    cnt = key->n - 1;
    fn = cnt;
    c[0] = col->c[0];
    c[1] = col->c[1];
    c[2] = col->c[2];
    c[3] = col->c[3];
    a[0] = key->col[0] >> 7;
    a[1] = key->col[1] >> 7;
    a[2] = key->col[2] >> 7;
    a[3] = key->col[3] >> 7;
    func_00267530(b, c, pa);
    func_002674b0(d, b, fn);
    s = &D_00615E64->shapes[key->id];
    w = PPP_WORK(Tail2Work, obj, e, 0);
    pm = m1;
    p.w8 = 0;
    p.b18 = 0;
    p.p10 = pm;
    p.p1C = 0;
    if (!key->b1F)
        p.flags = 128;
    else
        p.flags = 0;
    if (key->b20 == 1)
        p.flags |= 0x10;
    p.hC = 0;
    p.hE = 0;
    src = (u8 *) s->shape + s->shape->f[w->frame].off;
    sceVu0CopyMatrix(m0, D_00615E68->m);
    vuScaleXYZ(m0[0], m0[0], D_003701F0[0]);
    vuScaleXYZ(m0[1], m0[1], D_003701F0[1]);
    sz = 1.0f;
    sceVu0UnitMatrix(pm);
    t = key->len;
    step = (sz - key->size2) / fn;
    dt = t * step;
    n = cnt;
    if (t == 0.0f)
        n = -1;
    idx = w->idx;
    pts = w->pts;
    last = w->n - 1;
    func_002675a8(pa, pts[idx]);
    func_002675a8(b, pa);
    j = idx + 1;
    rem = t;
    if (idx == last)
        j = 0;
    pe = ev;
    func_002675a8(pe, pts[j]);
    pf = f;
    func_00267530(pf, pe, b);
    len = func_001a9350(pf);
    seg = len;
    for (;;) {
        vuFtoi0Bytes(&p.r, c);
        vuScaleXYZ(pm[0], m0[0], sz);
        vuScaleXYZ(m1[1], m0[1], sz);
        if (key->local)
            vuApply(m1[3], D_00615EB0, pa);
        else
            vuApply2(m1[3], D_00615FC0, pa);
        vuMulMatrix(pm, D_00616040, pm);
        {
            s32 *gp = &D_00616224;
            p.w14 = *gp;
            *gp = func_001b8198(src, &p, s->unk4);
        }
        if (n == 0)
            return;
        vuSub(c, c, d);
        t -= dt;
        if (t <= 0.0f)
            return;
        sz -= step;
        if (t <= len) {
            vuScale(pa, pf, rem / seg);
            vuAdd(pa, b, pa);
        } else {
            do {
                s32 k = j;
                j++;
                if (k == last)
                    j = 0;
                if (j == idx)
                    return;
                vuCopy(b, pe);
                vuCopy(ev, pts[j]);
                pe = ev;
                vuSub(pf, pe, b);
                rem -= seg;
                pf = f;
                seg = vuLen(pf);
                len += seg;
            } while (!(t <= len));
            vuScale(pa, pf, rem / seg);
            vuAdd(pa, b, pa);
        }
        rem += t;
        n--;
        len -= t;
    }
}
