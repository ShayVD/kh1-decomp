#include "common.h"
#include "ppp.h"
/* kh1-decomp session 7, worker w11: pppKeShpTail2Draw, pppKeShpTail2XDraw, pppKeShpTailDraw,
   pppKeShpTailXDraw, pppStepPrograms (hand/nostrict). */

/* ---- from pppKeShpTail2Draw.c ---- */

typedef f32 PppVec4[4] __attribute__((aligned(16)));

typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} T2MtxOwner;

extern T2MtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */

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

static inline void t2Col(f32 *v, u8 *c, f32 a) {
    v[0] = c[0];
    v[1] = c[1];
    v[2] = c[2];
    v[3] = c[3] * a;
}

/* ---- from pppKeShpTail2XDraw.c ---- */

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

/* ---- from pppKeShpTailXDraw.c ---- */

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

extern PppSysS *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */

#define D_00615E68 (*(PppObjS **) &D_00615E68)

extern s32 D_00616234[1]; /* src/data/bss_0061.c: s32 D_00616234 */

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
