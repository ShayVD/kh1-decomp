/* The pppKeShpTail2 and pppKeShpTail3 classes' frames and draws,
 * -fno-strict-aliasing (docs/modules.md "Session 50"): a shape animation
 * drawn along a trail of the owner's last n positions (the frame pushes the
 * position into a ring and steps the shape's frames; the draw draws a shape
 * at each kept position with func_001b8198, scaled and faded along the tail;
 * Tail3 adds a wobble and its own colour).  The Cons are in keshptail.c.
 * Types named NAME_xxxxx are one function's own view
 * (tools/shift/s50move/assemble.py).  Read from the code, not proved by a
 * boot. */

/* pppKeShpTail2Frame (from hand/nostrict/text_00190000_h63.c). */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 unk0;
    u8 *inst;   /* +0x4 */
    s32 time;   /* +0x8 */
    s32 unkC;
} PppSlot;
typedef struct {
    u8 pad[0x30];
    f32 col[4];     /* +0x30 */
    u8 pad40[0x40];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem;
extern PppSystem *D_00615E60;
extern s32 D_0061621C;
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;
typedef f32 PppVec4[4] __attribute__((aligned(16)));
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
    s32 unk90, unk94;
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;
void func_001a9098(void *, void *);
void func_002672f8(PppVec4, f32 *, PppVec4);
typedef struct {
    u8 pad[0x10];
    u32 tex;    /* +0x10 */
    u8 pad14[8];
    s32 *mdl;   /* +0x1C */
    s32 arg;    /* +0x20 */
} PppMdlRes; /* 0x24 */
typedef struct {
    u8 pad[0x9D];
    u8 unk9D;  /* +0x9D */
} PppObjectB;
typedef struct {
    s16 unk0;
    s16 len;    /* +0x2 */
    s8 flags;   /* +0x4 */
    u8 pad5[3];
} PppAnimFrame;
typedef struct {
    u8 pad[6];
    s16 n;      /* +0x6 */
    u8 pad8[8];
    PppAnimFrame frames[1]; /* +0x10 */
} PppAnim;
typedef struct {
    PppAnim *anim;
    s32 unk4;
} PppAnimRef;
extern PppMtx D_00615E70;
void func_002675a8(PppVec4, f32 *);
typedef struct {
    u8 pad[0x10];
    PppMdlRes *res; /* +0x10 */
    PppAnimRef *anims; /* +0x14 */
} PppMdlBank;
extern PppMdlBank *D_00615E64;
typedef struct {
    u8 count;     /* +0x0 */
    u8 idx;       /* +0x1 */
    u16 time;     /* +0x2 */
    u16 frame;    /* +0x4 */
    u16 prev;     /* +0x6 */
    u8 pad8[8];
    PppVec4 v[1]; /* +0x10 */
} PppShpTail;
typedef struct {
    s32 frame;
    s32 id;       /* +0x4 */
    u16 speed;    /* +0x8 */
    u8 padA[0x19];
    u8 local2;    /* +0x23 */
} PppShpTail2Key;
void pppKeShpTail2Frame(PppObject *obj, PppShpTail2Key *key, PppEntry *e) {
    PppShpTail *w;
    PppAnim *a;
    PppAnimFrame *f;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w = PPP_WORK(PppShpTail, obj, e, 0);
    if (obj->frame == 0 && ((PppObjectB *) obj)->unk9D == 0) {
        PppVec4 v;
        f32 *p;
        s32 n;

        if (key->local2) {
            func_002672f8(v, D_00615E70[0], D_00615E68->m[3]);
            v[3] = 1.0f;
        } else {
            func_002675a8(v, D_00615E68->m[3]);
            v[3] = 1.0f;
        }
        p = w->v[0];
        for (n = w->count; n > 0; n--) {
            func_002675a8(p, v);
            p += 4;
        }
    }
    if (w->idx == 0)
        w->idx = w->count;
    w->idx--;
    if (key->local2) {
        func_002672f8(w->v[w->idx], D_00615E70[0], D_00615E68->m[3]);
        w->v[w->idx][3] = 1.0f;
    } else {
        func_001a9098(w->v[w->idx], D_00615E68->m[3]);
    }
    {
        PppAnimRef *r = &D_00615E64->anims[key->id];
        a = r->anim;
    }
    f = &a->frames[w->frame];
    w->prev = w->frame;
    w->time += key->speed;
    if (w->time >= f->len) {
        w->time -= f->len;
        w->frame++;
        if (w->frame >= a->n) {
            if (f->flags & 0x80) {
                w->frame = 0;
                w->time = 0;
            } else {
                w->time = 0;
                w->frame--;
            }
        }
    }
}

/* pppKeShpTail2Draw (from hand/nostrict/text_00180000_s7_w11.c). */
#include "data/pieces/D_003701F0.h"
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
extern s32 D_00616224;
extern PppMtx D_00615EB0;
extern PppMtx D_00615FC0;
extern PppMtx D_00616040;
void func_00267530(f32 *, f32 *, f32 *);
void func_002674b0(f32 *, f32 *, f32);
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
#define D_00615E64 ((T2Sys *) D_00615E64)
#define D_00615E68 ((T2MtxOwner *) D_00615E68)
/* kh1-decomp session 7, worker w11: pppKeShpTail2Draw, pppKeShpTail2XDraw, pppKeShpTailDraw,
   pppKeShpTailXDraw, pppStepPrograms (hand/nostrict). */
/* ---- from pppKeShpTail2Draw.c ---- */
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

/* pppKeShpTail3Frame (from hand/nostrict/text_00180000_b07.c). */
#include "data/pieces/D_003701E0.h"
#include "data/pieces/D_003701D0.h"
typedef struct {
    u8 pad[0x80];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem_90e68;
typedef struct {
    f32 x, y, z, w;
} V4F __attribute__((aligned(16)));
typedef struct {
    u16 p0[4], p1[4], v0[4], a0[4], v1[4], a1[4];
} PppTail3;
typedef struct {
    s32 frame;
    u8 pad4[0x1C];
    PppTail3 d;    /* +0x20 */
    u8 local;      /* +0x50 */
} PppTail3Key;
typedef struct {
    PppTail3 h;
    PppVec4 v[28]; /* +0x30 */
    u8 pad1F0[0xA];
    u8 idx;        /* +0x1FA */
} PppTail3Work;
#define D_00615E60 ((PppSystem_90e68 *) D_00615E60)
#define D_00615E70 (*(V4F (*)) &D_00615E70)
/* --- pppKeShpTail3Frame --- */
void pppKeShpTail3Frame(PppObject *obj, PppTail3Key *key, PppEntry *e) {
    PppTail3Work *w;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w = PPP_WORK(PppTail3Work, obj, e, 0);
    if (obj->frame == 0 && ((u8 *) obj)[0x9D] == 0) {
        PppVec4 v;
        f32 *p;
        s32 n;

        if (key->local) {
            func_002672f8(v, &D_00615E70, D_00615E68->m[3]);
            v[3] = 1.0f;
        } else {
            func_002675a8(v, D_00615E68->m[3]);
            v[3] = 1.0f;
        }
        p = w->v[0];
        for (n = 28; n > 0; n--) {
            func_002675a8(p, v);
            p += 4;
        }
    }
    if (w->idx == 0)
        w->idx = 28;
    w->idx--;
    if (key->local) {
        func_002672f8(w->v[w->idx], &D_00615E70, D_00615E68->m[3]);
        w->v[w->idx][3] = 1.0f;
    } else {
        func_002675a8(w->v[w->idx], D_00615E68->m[3]);
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
#undef D_00615E60
#undef D_00615E70

/* pppKeShpTail3Draw (from hand/nostrict/text_00190000_s10_w1.c). */
void *func_001aa950(s32);
void func_001aa9d0(s32);
extern const f32 D_0048FB68;
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
    u8 local;     /* +0x50 */
    u8 b24;       /* +0x51 */
    u8 b25;       /* +0x52 */
} T3Key;
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
void pppKeShpTail3Draw(void *obj, T3Key *key, PppEntry *e) {
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

    inline void t3Init(T3Key *k) {
        f32 o;
        if (k->local) {
            T3CPY(buf->a, D_00615EB0);
        } else {
            T3CPY(buf->a, D_00615FC0);
        }
        o = D_0048FB68;
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
    func_00267530(p0, col, pos);
    func_002674b0(dcol, p0, seg);
    s = &D_00615E64->shapes[key->id];
    p.p10 = buf->out;
    p.d8[0] = p.d8[1] = p.d8[2] = p.d8[3] = 0;
    p.b18 = 0;
    p.p1C = 0;
    if (!key->b24)
        p.flags = 128;
    else
        p.flags = 0;
    if (key->b25 == 1)
        p.flags |= 0x10;
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

