/* ppp component callbacks around 0x18a000-0x194000, by hand (worker 63).
 * This region was built without strict aliasing. */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef unsigned int u128 __attribute__((mode(TI)));

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

extern PppSystem *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */
extern f32 D_00575A00; /* src/data/bss_0057.c: u8 D_00575A00[0x10] */
extern s32 D_0061621C;
extern s32 D_00616234;

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;

typedef f32 PppVec4[4] __attribute__((aligned(16)));

f32 fmodf(f32, f32);

typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
    s32 unk90, unk94;
} PppMtxOwner;

extern PppMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
extern PppMtx D_00615FC0;
void sceVu0MulMatrix(PppMtx, PppMtx, PppMtx);

typedef struct {
    s32 frame;
    s32 unk4, unk8;
    f32 da, dda;   /* +0xC */
    s32 unk14;
    f32 db, ddb;   /* +0x18 */
} PppMdlLoopKey;

typedef struct {
    s32 init;
    f32 a, da, dda;  /* +0x4 */
    f32 b, db, ddb;  /* +0x10 */
} PppMdlLoop;

u8 *func_00182588(PppSystem *, PppSlot *);

/* Start an instance of program slot `id` owned by `o`. */
static inline u8 *inl_spawn(PppSystem *sys, s32 id, PppObject *o) {
    PppSlot *s = &sys->slots[id];
    u8 *i = 0;

    if (s) {
        i = func_00182588(sys, s);
        *(PppObject **) (i + 4) = o;
    }
    return i;
}

typedef struct {
    u8 pad[0x10];
    u32 tex;    /* +0x10 */
    u8 pad14[8];
    s32 *mdl;   /* +0x1C */
    s32 arg;    /* +0x20 */
} PppMdlRes; /* 0x24 */

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

typedef struct {
    u8 pad[0x10];
    PppMdlRes *res; /* +0x10 */
    PppAnimRef *anims; /* +0x14 */
} PppMdlBank;

extern PppMdlBank *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
extern u8 D_00616240[];
extern u8 D_00616140[];
extern u8 D_00616100[];
extern s32 D_00616224;

typedef struct {
    s32 frame;
    s32 unk4;
    u8 col[4];     /* +0x8 */
    f32 f0C;       /* +0xC */
    u16 h10, h12;  /* +0x10 */
    u16 h14;       /* +0x14 */
} PppLnsClmKey;

typedef struct {
    s32 frame;
    s32 slot0, off0;
    s32 slot1, off1;
    f32 mass;  /* +0x14 */
} PppWfaccKey;

typedef struct {
    f32 x, y, z;
    f32 range;  /* +0xC */
    f32 unk10;
    f32 min;    /* +0x14 */
    f32 force;  /* +0x18 */
} PppWfacc;

f32 func_00267390(PppWfacc *, f32 *);

static inline f32 vu0Normalize(f32 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vadd.xyz $vf8xyz, $vf0xyz, $vf10xyz\n"
        "vmul.xyz $vf10xyz, $vf10xyz, $vf10xyz\n"
        "vmove.xyz $vf9xyz, $vf10xyz\n"
        "vaddx.y $vf9y, $vf9y, $vf9x\n"
        "vaddy.z $vf9z, $vf9z, $vf9y\n"
        "vsqrt Q, $vf9z\n"
        "vwaitq\n"
        "vaddq.x $vf10x, $vf0x, Q\n"
        "qmfc2 %0, $vf10\n"
        "vdiv Q, $vf0w, $vf10x\n"
        "vwaitq\n"
        "vmulq.xyz $vf9xyz, $vf8xyz, Q\n"
        "sqc2 $vf9, 0(%1)\n"
        : "=r"(r) : "r"(v) : "memory");
    return r;
}

void pppEiWfaccFrame(PppObject *obj, PppWfaccKey *key, PppEntry *e) {
    PppVec4 v;
    f32 *p = PPP_WORK(f32, obj, e, 0);
    PppWfacc *a;
    f32 *b;
    f32 len, d, k;
    f32 *w;

    if (key->slot0 != -1)
        a = (PppWfacc *) (D_00615E60->slots[key->slot0].inst + key->off0 + 0xA0);
    else
        a = (PppWfacc *) &D_00575A00;
    if (key->slot1 != -1)
        b = (f32 *) (D_00615E60->slots[key->slot1].inst + key->off1 + 0xA0);
    else
        b = &D_00575A00;
    v[0] = p[0] - b[0];
    v[1] = p[1] - b[1];
    v[2] = p[2] - b[2];
    len = vu0Normalize(v);
    if (len < a->range) {
        d = func_00267390(a, v);
        if (a->min < d) {
            k = a->force * ((d - a->min) / (1.0f - a->min)) * ((a->range - len) / a->range) / key->mass;
            w = PPP_WORK(f32, obj, e, 1);
            w[0] += v[0] * k;
            w[1] += v[1] * k;
            w[2] += v[2] * k;
        }
    }
}

void func_0018b030(PppMdlLoopKey *, PppMdlLoop *);

void pppDrawMdlLoopFrame(PppObject *obj, PppMdlLoopKey *key, PppEntry *e) {
    PppMdlLoop *w = PPP_WORK(PppMdlLoop, obj, e, 2);

    if (w->init == 0)
        func_0018b030(key, w);
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame == obj->frame) {
        w->da += key->da;
        w->dda += key->dda;
        w->db += key->db;
        w->ddb += key->ddb;
    }
    if (D_00616234 != 0)
        return;
    w->da += w->dda;
    w->db += w->ddb;
    w->a += w->da;
    w->b += w->db;
    w->a = fmodf(w->a, 32768.0f);
    w->b = fmodf(w->b, 32768.0f);
}

typedef struct {
    u32 flags;     /* +0x00 */
    void *p04;     /* +0x04 */
    u16 h08;       /* +0x08 */
    u8 b0A;
    s32 i0C;       /* +0x0C */
    s32 u, v;      /* +0x10 */
    u8 col[4];     /* +0x18 */
    s32 i1C;       /* +0x1C */
    void *m2;      /* +0x20 */
    void *p24;
    void *p28;
    void *m;       /* +0x2C */
    void *mtx;     /* +0x30 */
    s32 i34;
    s32 i38, i3C;  /* +0x38 */
    s32 i40, i44;  /* +0x40 */
    s32 i48;
    u8 b4C, b4D;   /* +0x4C */
    u8 pad4E[0x12];
} PppMdlDraw;

typedef struct {
    s32 frame;
    s32 id;      /* +0x4 */
    u8 pad8[0x18];
    union { u8 b; u16 h; } tex; /* +0x20 */
    u8 mode;     /* +0x22 */
    u8 f23, f24, f25;
} PppMdlKey;

typedef struct {
    u8 pad[8];
    u8 col[4];
} PppColWork;

s32 func_001aaf88(s32 *, PppMdlDraw *, s32);

void pppDrawMdlLoopDraw(PppObject *obj, PppMdlKey *key, PppEntry *e) {
    PppMdlDraw d;
    PppMtx mtx;
    PppMdlLoop *w = PPP_WORK(PppMdlLoop, obj, e, 2);
    PppColWork *c;
    s32 *mdl;

    if (key->id == 0xFFFF)
        return;
    c = PPP_WORK(PppColWork, obj, e, 0);
    mdl = D_00615E64->res[key->id].mdl;
    d.col[0] = c->col[0];
    d.col[1] = c->col[1];
    d.col[3] = c->col[3];
    d.col[2] = c->col[2];
    if (d.col[3] == 0)
        return;
    d.flags = 0;
    if (key->mode & 2)
        d.flags = 4;
    else if (key->mode & 1)
        d.flags = 0x80;
    if (!(*mdl & 1))
        d.flags |= 8;
    if (!(*mdl & 2))
        d.flags |= 0x10;
    if (key->f23)
        d.flags |= 0x200;
    if (key->f24)
        d.flags |= 0x100;
    if (key->f25) {
        d.flags = (d.flags & ~0x10) | 0x2000;
        d.mtx = mtx;
        sceVu0MulMatrix(mtx, D_00615FC0, D_00615E68->m);
    } else {
        d.mtx = 0;
    }
    d.p04 = D_00616240;
    if (key->tex.b == 0xFF)
        d.h08 = ((u16 *) mdl)[11];
    else
        d.h08 = key->tex.h;
    d.b0A = 0;
    d.i0C = 0;
    d.i1C = 0;
    d.u = w->a * 65536.0f;
    d.v = w->b * 65536.0f;
    d.m2 = D_00615E68->m2;
    d.p24 = D_00616140;
    d.p28 = D_00616100;
    d.m = D_00615E68->m;
    d.i34 = D_00616224;
    d.i44 = 0;
    d.i38 = D_00615E68->unk90;
    d.i3C = D_00615E68->unk94;
    d.i40 = 0;
    d.b4C = 0;
    d.b4D = 0;
    D_00616224 = func_001aaf88(mdl, &d, D_00615E64->res[key->id].arg);
}

void func_0018b470(PppMdlLoopKey *, PppMdlLoop *);

void pppDrawMdlLoopZFrame(PppObject *obj, PppMdlLoopKey *key, PppEntry *e) {
    PppMdlLoop *w = PPP_WORK(PppMdlLoop, obj, e, 2);

    if (w->init == 0)
        func_0018b470(key, w);
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->frame == obj->frame) {
        w->da += key->da;
        w->dda += key->dda;
        w->db += key->db;
        w->ddb += key->ddb;
    }
    if (D_00616234 != 0)
        return;
    w->da += w->dda;
    w->db += w->ddb;
    w->a += w->da;
    w->b += w->db;
    w->a = fmodf(w->a, 32768.0f);
    w->b = fmodf(w->b, 32768.0f);
}

void func_00192708(PppObject *, PppLnsClmKey *, PppEntry *);

void func_00192708(PppObject *, PppLnsClmKey *, PppEntry *);

/* needs make: uses rodata */
