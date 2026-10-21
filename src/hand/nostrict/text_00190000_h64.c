/* ppp component callbacks around 0x193e00-0x1a0800 (worker 64). This
 * region was built without strict aliasing. */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef int u128 __attribute__((mode(TI)));
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
typedef f32 PppVec4[4] __attribute__((aligned(16)));
typedef struct { f32 x, y, z; } PppFVec;

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
extern PppSystem *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject;

/* The current draw matrices. */
typedef struct {
    u8 pad[0x10];
    PppMtx m;     /* +0x10 */
    PppMtx m2;    /* +0x50 */
    s32 unk90;    /* +0x90 */
    s32 unk94;    /* +0x94 */
} PppMtxOwner;

extern PppMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */

/* Models and shapes. */
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
    u8 pad00[0x10];
    DSlot *slots;        /* +0x10 */
    PppShapeEnt *shapes; /* +0x14 */
} DSys;

extern DSys *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */

/* Parameter block of func_001aaf88 (model draw). */
typedef struct {
    s32 flags;  /* +0x00 */
    void *p04;  /* +0x04 */
    u16 h08;    /* +0x08 */
    u8 b0A;     /* +0x0A */
    s32 w0C;    /* +0x0C */
    union { u64 d; struct { s32 u, v; } s; } t10; /* +0x10 */
    u8 r, g, b, a; /* +0x18 */
    s32 w1C;    /* +0x1C */
    void *p20;  /* +0x20 */
    void *p24;  /* +0x24 */
    void *p28;  /* +0x28 */
    void *p2C;  /* +0x2C */
    void *p30;  /* +0x30 */
    s32 w34;    /* +0x34 */
    s32 w38;    /* +0x38 */
    s32 w3C;    /* +0x3C */
    s32 w40;    /* +0x40 */
    void *p44;  /* +0x44 */
    s32 w48;    /* +0x48 */
    u8 b4C;     /* +0x4C */
    u8 b4D;     /* +0x4D */
    u8 pad4E[0x12];
} DParam;

typedef struct {
    u8 pad[8];
    u8 r, g, b, a; /* +0x8 */
} DColWork;

extern u8 D_00616240[];
extern u8 D_00616140[];
extern u8 D_00616100[];
extern s32 D_00616224;
extern f32 D_00575A00; /* src/data/bss_0057.c: u8 D_00575A00[0x10] */
extern PppMtx D_00615FC0, D_00615E70, D_00615EB0, D_00616000, D_00616040;
#include "data/pieces/D_003701F0.h"
extern f32 D_003701D0[4];
#include "data/pieces/D_003701E0.h"

s32 func_001aaf88(DMdl *, DParam *, s32);
u8 *func_00182588(PppSystem *, PppSlot *);
void func_001a9098(void *, void *);
void func_00267530(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
s32 func_001a8f70(void *);
void func_00267560(f32 *, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_001a90f8(void *, void *, void *);
void func_002672f8(f32 *, PppMtx, f32 *);
void sceVu0MulMatrix(PppMtx, PppMtx, PppMtx);
void func_00183be0(PppMtx, void *);
void func_001a5250(PppMtx, void *);
void func_001a5370(PppMtx, void *);
void func_001a52e0(PppMtx, void *);
void func_001a5400(PppMtx, void *);
void func_001a5490(PppMtx, void *);
void func_00267440(PppMtx, PppMtx);
s32 sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
void func_001a9460(f32, s32, s32, void *);
void func_001aa6b0(void *, s32, s32, s32);
void func_001a9790(s32, void *, s32, s32, s32, s32, void *);

static inline void vu0ScaleRow(f32 *row, f32 s) {
    __asm__ volatile(
        "qmtc2 %1, $vf9\n"
        "lqc2 $vf10, 0(%0)\n"
        "vmulx.xyz $vf10xyz, $vf10xyz, $vf9x\n"
        "sqc2 $vf10, 0(%0)\n"
        : : "r"(row), "r"(s));
}

typedef struct {
    s32 frame;
    s32 slot;  /* +0x4 */
    s32 off;   /* +0x8 */
    u8 c;      /* +0xC */
} PppHitBornKey;

void pppKeHitBornFrame(PppObject *obj, PppHitBornKey *key, PppEntry *e) {
    u8 *f = PPP_WORK(u8, obj, e, 2);
    u8 *w1;
    PppSlot *slot;
    u8 *inst;

    if (*f & 2)
        return;
    if (obj->frame == key->frame) {
        if (key->c)
            *f |= 1;
        else
            *f &= 0xFE;
    }
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w1 = PPP_WORK(u8, obj, e, 1);
    if (!(w1[0x10] & 1))
        return;
    if (key->slot == -1)
        return;
    slot = &D_00615E60->slots[key->slot];
    inst = 0;
    if (slot) {
        inst = func_00182588(D_00615E60, slot);
        *(void **) (inst + 4) = obj;
    }
    {
        u8 fl = *f;
        u8 *w0 = PPP_WORK(u8, obj, e, 0);
        u8 *dst = inst + key->off + 0xA0;
        if (!(fl & 1)) {
            *f = fl | 2;
            func_001a9098(dst, w1);
        } else {
            func_001a9098(dst, w0);
        }
    }
}

typedef struct {
    f32 r;
    f32 *pos;
} PppHitTgt;

typedef struct {
    PppVec4 v;
    u8 flags;       /* +0x10 */
    PppHitTgt *tgt; /* +0x14 */
} PppHitChkWork;

typedef struct {
    PppVec4 a;
    PppVec4 b; /* +0x10 */
    f32 r;     /* +0x20 */
    f32 t;     /* +0x24 */
} PppHitQ;

void pppKeHitChkPxBFrame(PppObject *obj, PppHitBornKey *key, PppEntry *e) {
    PppHitQ q;
    PppVec4 c;
    PppHitChkWork *w = PPP_WORK(PppHitChkWork, obj, e, 2);
    PppHitTgt *t;
    u8 *w1, *w0;
    u8 fl = w->flags;

    if (fl & 1)
        return;
    if (obj->frame == key->frame) {
        if (key->slot != -1)
            w->tgt = (PppHitTgt *) (D_00615E60->slots[key->slot].inst + key->off + 0xA0);
        else
            w->tgt = (PppHitTgt *) &D_00575A00;
        if (key->c)
            w->flags = fl | 2;
        if (obj->frame == 0 && obj->unk9D == 0)
            return;
    }
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    t = w->tgt;
    if (t == (PppHitTgt *) &D_00575A00)
        return;
    w0 = PPP_WORK(u8, obj, e, 0);
    w1 = PPP_WORK(u8, obj, e, 1);
    if (t->r == 0.0f)
        return;
    q.r = t->r;
    func_00267530(q.a, (f32 *) w0, t->pos);
    func_002675a8(q.b, (f32 *) w1);
    if (!func_001a8f70(&q))
        return;
    if (q.t < 0.0f || q.t > 1.0f)
        return;
    w->flags |= 1;
    func_00267560(c, q.b, q.t);
    func_00267518(c, c, q.a);
    func_00267518(w->v, w->tgt->pos, c);
    if (w->flags & 2) {
        func_001a90f8(w1, w, w0);
        obj->frame = 0xFFFF0000;
    }
}

typedef struct {
    s32 frame;
    s32 slot; /* +0x4 */
    u8 flags; /* +0x8 */
    u8 b9, bA;
} DMdl2Key;

void pppDrawMdl2Draw(PppObject *obj, DMdl2Key *key, PppEntry *e) {
    DParam p;
    DColWork *w;
    DSlot *s;
    DMdl *m;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DColWork, obj, e, 0);
    p.a = w->a;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    p.flags = 0;
    if (key->flags & 2) {
        p.flags = 4;
        if (!(m->flags & 1))
            p.flags |= 8;
    } else {
        if (key->flags & 1)
            p.flags = 128;
        if (!(m->flags & 1))
            p.flags |= 8;
    }
    if (!(m->flags & 2))
        p.flags |= 16;
/*P*/
    p.h08 = m->unk16;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.w0C = 0;
    p.p04 = D_00616240;
    p.t10.d = 0;
    p.w40 = 0;
    p.p44 = D_00615E68->m2;
    p.r = w->r;
    p.g = w->g;
    p.b = w->b;
    p.p20 = D_00615E68->m2;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.p2C = D_00615E68->m;
    p.w34 = D_00616224;
    p.b4C = key->b9;
    p.b4D = key->bA;
/*Q*/
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

typedef struct {
    s32 frame;
    s32 slot; /* +0x4 */
    u16 h8;   /* +0x8 */
    u8 flags; /* +0xA */
} DSemi2Key;

void pppDrawMdlSemi2Draw(PppObject *obj, DSemi2Key *key, PppEntry *e) {
    DParam p;
    DColWork *w;
    DSlot *s;
    DMdl *m;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DColWork, obj, e, 0);
    p.a = w->a;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    p.flags = 0;
    if (key->flags & 2) {
        p.flags = 4;
        if (!(m->flags & 1))
            p.flags |= 8;
    } else {
        if (key->flags & 1)
            p.flags = 128;
        if (!(m->flags & 1))
            p.flags |= 8;
    }
    if (!(m->flags & 2))
        p.flags |= 16;
/*P*/
    p.h08 = key->h8;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.w0C = 0;
    p.p04 = D_00616240;
    p.t10.d = 0;
    p.w40 = 0;
    p.p44 = D_00615E68->m2;
    p.r = w->r;
    p.g = w->g;
    p.b = w->b;
    p.p20 = D_00615E68->m2;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.p2C = D_00615E68->m;
    p.w34 = D_00616224;
/*Q*/
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

typedef struct {
    s32 frame;
    s32 slot; /* +0x4 */
    u8 pad8[0x18];
    u8 flags; /* +0x20 */
    u8 b21;
} DTs2Key;

void pppDrawMdlTs2Draw(PppObject *obj, DTs2Key *key, PppEntry *e) {
    DParam p;
    DColWork *w;
    f32 *t = PPP_WORK(f32, obj, e, 2);
    DSlot *s;
    DMdl *m;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DColWork, obj, e, 0);
    p.a = w->a;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    p.flags = 0;
    if (key->flags & 2) {
        p.flags = 4;
        if (!(m->flags & 1))
            p.flags |= 8;
    } else {
        if (key->flags & 1)
            p.flags = 128;
        if (!(m->flags & 1))
            p.flags |= 8;
    }
    if (!(m->flags & 2))
        p.flags |= 16;
/*P*/
    p.h08 = m->unk16;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.w0C = 0;
    p.p04 = D_00616240;
    p.t10.s.u = t[0] * 65536.0f;
    p.t10.s.v = t[3] * 65536.0f;
    p.w40 = 0;
    p.p44 = D_00615E68->m2;
    p.r = w->r;
    p.g = w->g;
    p.b = w->b;
    p.p20 = D_00615E68->m2;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.p2C = D_00615E68->m;
    p.w34 = D_00616224;
    p.b4D = key->b21;
    p.b4C = 0;
/*Q*/
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

typedef struct {
    s32 frame;
    f32 x, y, z;     /* +0x4 */
    f32 sx, sy, sz;  /* +0x10 */
    u8 mode;         /* +0x1C */
} PppZCrctKey;

void pppKeZCrctFrame(PppObject *obj, PppZCrctKey *key, PppEntry *e) {
    PppMtx m;
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[0] + 0xA0);

    func_00267560(m[0], D_00615E68->m[0], key->sx);
    func_00267560(m[1], D_00615E68->m[1], key->sy);
    func_00267560(m[2], D_00615E68->m[2], key->sz);
    func_002675a8(m[3], D_00615E68->m[3]);
    switch (key->mode) {
    case 0:
        m[3][0] += key->x;
        m[3][1] += key->y;
        m[3][2] += key->z;
        sceVu0MulMatrix(m, D_00615FC0, m);
        break;
    case 1:
        sceVu0MulMatrix(m, D_00615FC0, m);
        m[3][0] += key->x;
        m[3][1] += key->y;
        m[3][2] += key->z;
        break;
    case 2:
        sceVu0MulMatrix(m, D_00615E70, m);
        m[3][0] += key->x * D_003701F0[0];
        m[3][1] += key->y * D_003701F0[1];
        m[3][2] += key->z * D_003701F0[2];
        sceVu0MulMatrix(m, D_00615EB0, m);
        break;
    case 3:
        sceVu0MulMatrix(m, D_00616000, m);
        m[3][0] += key->x;
        m[3][1] += key->y;
        m[3][2] += key->z;
        break;
    }
    sceVu0MulMatrix(w, D_00616040, m);
}

void pppKeZCrctShpFrame(PppObject *obj, PppZCrctKey *key, PppEntry *e) {
    PppMtx m;
    PppVec4 v;
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[0] + 0xA0);

    func_00267560(m[0], D_00615E68->m[0], D_003701F0[0]);
    func_00267560(m[1], D_00615E68->m[1], D_003701F0[1]);
    func_00267560(m[2], D_00615E68->m[2], D_003701F0[2]);
    func_002675a8(v, D_00615E68->m[3]);
    v[0] *= key->sx;
    v[1] *= key->sy;
    v[2] *= key->sz;
    switch (key->mode) {
    case 0:
        v[0] += key->x;
        v[1] += key->y;
        v[2] += key->z;
        func_002672f8(m[3], D_00615FC0, v);
        break;
    case 1:
        func_002672f8(m[3], D_00615FC0, v);
        m[3][0] += key->x;
        m[3][1] += key->y;
        m[3][2] += key->z;
        break;
    case 2:
        func_002672f8(m[3], D_00615E70, v);
        m[3][0] += key->x * D_003701F0[0];
        m[3][1] += key->y * D_003701F0[1];
        m[3][2] += key->z * D_003701F0[2];
        func_002672f8(m[3], D_00615EB0, m[3]);
        break;
    }
    sceVu0MulMatrix(w, D_00616040, m);
}

typedef struct {
    s32 frame;
    s32 slot; /* +0x4 */
    u8 flags; /* +0x8 */
    u8 b9, bA, bB, bC, bD, bE;
} DMdl3Key;

void pppDrawMdl3Draw(PppObject *obj, DMdl3Key *key, PppEntry *e) {
    DParam p;
    PppMtx mtx;
    DColWork *w;
    DSlot *s;
    DMdl *m;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DColWork, obj, e, 0);
    p.a = w->a;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    p.flags = 0;
    if (key->flags & 2) {
        p.flags = 4;
        if (!(m->flags & 1))
            p.flags |= 8;
    } else {
        if (key->flags & 1)
            p.flags = 128;
        if (!(m->flags & 1))
            p.flags |= 8;
    }
    if (!(m->flags & 2))
        p.flags |= 16;
    if (key->b9)
        p.flags |= 0x200;
    if (key->bB)
        p.flags |= 0x100;
    if (key->bA) {
        p.flags |= 0x2000;
        p.p30 = mtx;
        sceVu0MulMatrix(mtx, D_00615FC0, D_00615E68->m);
    }
    if (key->bC)
        p.p44 = PPP_WORK(u8, obj, e, 2);
    else
        p.p44 = 0;
/*P*/
    p.h08 = m->unk16;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.w0C = 0;
    p.p04 = D_00616240;
    p.t10.d = 0;
    p.w40 = 0;
    p.p20 = D_00615E68->m2;
    p.r = w->r;
    p.g = w->g;
    p.b = w->b;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.p2C = D_00615E68->m;
    p.w34 = D_00616224;
    p.b4C = key->bD;
    p.b4D = key->bE;
/*Q*/
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

typedef struct {
    s32 frame;
    s32 slot; /* +0x4 */
    u16 h8;   /* +0x8 */
    u8 flags; /* +0xA */
    u8 bB, bC, bD, bE;
} DSemi3Key;

void pppDrawMdlSemi3Draw(PppObject *obj, DSemi3Key *key, PppEntry *e) {
    DParam p;
    PppMtx mtx;
    DColWork *w;
    DSlot *s;
    DMdl *m;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DColWork, obj, e, 0);
    p.a = w->a;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    p.flags = 0;
    if (key->flags & 2) {
        p.flags = 4;
        if (!(m->flags & 1))
            p.flags |= 8;
    } else {
        if (key->flags & 1)
            p.flags = 128;
        if (!(m->flags & 1))
            p.flags |= 8;
    }
    if (!(m->flags & 2))
        p.flags |= 16;
    if (key->bB)
        p.flags |= 0x200;
    if (key->bD)
        p.flags |= 0x100;
    if (key->bC) {
        p.flags |= 0x2000;
        p.p30 = mtx;
        sceVu0MulMatrix(mtx, D_00615FC0, D_00615E68->m);
    }
    if (key->bE)
        p.p44 = PPP_WORK(u8, obj, e, 2);
    else
        p.p44 = 0;
/*P*/
    p.h08 = key->h8;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.w0C = 0;
    p.p04 = D_00616240;
    p.t10.d = 0;
    p.w40 = 0;
    p.r = w->r;
    p.g = w->g;
    p.b = w->b;
    p.p20 = D_00615E68->m2;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.p2C = D_00615E68->m;
    p.w34 = D_00616224;
/*Q*/
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

typedef struct {
    s32 frame;
    s32 id;       /* +0x4 */
    f32 da, db, dc; /* +0x8 */
    s32 u, v;     /* +0x14 */
    u8 page;      /* +0x1C */
    u8 b1D, b1E, b1F, b20, b21;
} PppTfd3Key;

typedef struct {
    f32 a, b, c;
} PppTfd;

void pppKeMdlTfd3Draw(PppObject *obj, PppTfd3Key *key, PppEntry *e) {
    PppTfd *w = PPP_WORK(PppTfd, obj, e, 2);
    u32 tex;
    s32 n;
    u8 *p, *q;

    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w->b += w->c;
        w->a += w->b;
        if (obj->frame == key->frame) {
            w->a += key->da;
            w->b += key->db;
            w->c += key->dc;
        }
    }
    if (key->id == 0xFFFF)
        return;
    {
        DSlot *r = &D_00615E64->slots[key->id];
        tex = r->tex;
    }
    n = key->page * 4;
    p = (u8 *) D_00616224 + 16;
    sceGsSetDefLoadImage(p, ((tex >> 5) & 0x3FFF) + n, 4, (tex >> 19) & 0xF, 0, 0, 16, 16);
    *(u64 *) (p + 0x50) = 0x0800000000008100ULL;
    q = (u8 *) D_00616224;
    func_001a9460(w->a, key->u, key->v, q + 0x70);
    func_001aa6b0((void *) D_00616224, 263, 0, 0);
    D_00616224 = (s32) (q + 0x1070);
    {
        void *w0 = PPP_WORK(void, obj, e, 0);
        void *w3 = PPP_WORK(void, obj, e, 3);
        func_001a9790(key->id, w0, n, 0, 0,
                      key->b1D | key->b1E | key->b20 | key->b1F | key->b21, w3);
    }
}

typedef struct {
    u16 time;   /* +0x0 */
    u16 cur;    /* +0x2 */
    u16 prev;   /* +0x4 */
} PppShapeWork;

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

void pppDrawShapeXDraw(PppObject *obj, DShpXKey *key, PppEntry *e) {
    DShpParam p;
    PppShapeWork *w = PPP_WORK(PppShapeWork, obj, e, 0);
    DColWork *c = PPP_WORK(DColWork, obj, e, 1);
    PppShapeEnt *s;
    PppShape *sh;
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
    { PppShapeFrame *f = &sh->f[w->prev]; src = (u8 *) sh + f->off; }
    p.w14 = D_00616224;
    D_00616224 = func_001b8198(src, &p, s->unk4);
}

void pppRyjMatrixWorldFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMtx m;
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[3] + 0xA0);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_00183be0(D_00615E68->m, r);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
    func_00183be0(m, &D_003701E0);
    m[3][0] = D_003701D0[0];
    m[3][1] = D_003701D0[1];
    m[3][2] = D_003701D0[2];
    func_00267440(m, m);
    sceVu0MulMatrix(D_00615E68->m, D_00615E68->m, w);
    sceVu0MulMatrix(D_00615E68->m, m, D_00615E68->m);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
}

void pppRyjMatrixWorldXZYFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMtx m;
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[3] + 0xA0);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a5250(D_00615E68->m, r);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
    func_001a5250(m, &D_003701E0);
    m[3][0] = D_003701D0[0];
    m[3][1] = D_003701D0[1];
    m[3][2] = D_003701D0[2];
    func_00267440(m, m);
    sceVu0MulMatrix(D_00615E68->m, D_00615E68->m, w);
    sceVu0MulMatrix(D_00615E68->m, m, D_00615E68->m);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
}

void pppRyjMatrixWorldYXZFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMtx m;
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[3] + 0xA0);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a5370(D_00615E68->m, r);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
    func_001a5370(m, &D_003701E0);
    m[3][0] = D_003701D0[0];
    m[3][1] = D_003701D0[1];
    m[3][2] = D_003701D0[2];
    func_00267440(m, m);
    sceVu0MulMatrix(D_00615E68->m, D_00615E68->m, w);
    sceVu0MulMatrix(D_00615E68->m, m, D_00615E68->m);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
}

void pppRyjMatrixWorldYZXFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMtx m;
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[3] + 0xA0);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a52e0(D_00615E68->m, r);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
    func_001a52e0(m, &D_003701E0);
    m[3][0] = D_003701D0[0];
    m[3][1] = D_003701D0[1];
    m[3][2] = D_003701D0[2];
    func_00267440(m, m);
    sceVu0MulMatrix(D_00615E68->m, D_00615E68->m, w);
    sceVu0MulMatrix(D_00615E68->m, m, D_00615E68->m);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
}

void pppRyjMatrixWorldZXYFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMtx m;
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[3] + 0xA0);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a5400(D_00615E68->m, r);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
    func_001a5400(m, &D_003701E0);
    m[3][0] = D_003701D0[0];
    m[3][1] = D_003701D0[1];
    m[3][2] = D_003701D0[2];
    func_00267440(m, m);
    sceVu0MulMatrix(D_00615E68->m, D_00615E68->m, w);
    sceVu0MulMatrix(D_00615E68->m, m, D_00615E68->m);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
}

void pppRyjMatrixWorldZYXFrame(PppObject *obj, void *key, PppEntry *e) {
    PppMtx m;
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    f32 (*w)[4] = (f32 (*)[4]) ((u8 *) obj + e->offsets[3] + 0xA0);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a5490(D_00615E68->m, r);
    D_00615E68->m[3][0] = t->x;
    D_00615E68->m[3][1] = t->y;
    D_00615E68->m[3][2] = t->z;
    func_001a5490(m, &D_003701E0);
    m[3][0] = D_003701D0[0];
    m[3][1] = D_003701D0[1];
    m[3][2] = D_003701D0[2];
    func_00267440(m, m);
    sceVu0MulMatrix(D_00615E68->m, D_00615E68->m, w);
    sceVu0MulMatrix(D_00615E68->m, m, D_00615E68->m);
    vu0ScaleRow(D_00615E68->m[0], s->x);
    vu0ScaleRow(D_00615E68->m[1], s->y);
    vu0ScaleRow(D_00615E68->m[2], s->z);
}

/* Hand-written VU0 routine: the asm body addresses its 16-byte work
 * buffer through $sp. */
extern u128 D_00372710;

void func_001996d0(u128 *a, s32 n, u128 *b) {
    u128 buf[32];
    register u128 *c asm("$2") = &D_00372710;

    __asm__ volatile(
        ".set noreorder\n"
        "addi $9, $5, -1\n"
        "addi $10, $5, -2\n"
        "lqc2 $vf1, 0($2)\n"
        "sqc2 $vf0, 0($6)\n"
        "sll $11, $9, 0x4\n"
        "add $11, $11, $6\n"
        "sqc2 $vf0, 0($11)\n"
        "move $8, $9\n"
        "move $11, $0\n"
        ".Lw64a_1:\n"
        "blez $8, .Lw64a_2\n"
        "addi $8, $8, -1\n"
        "sll $12, $11, 0x4\n"
        "addi $13, $12, 16\n"
        "add $14, $12, $4\n"
        "add $15, $13, $4\n"
        "add $16, $13, $29\n"
        "lqc2 $vf10, 0($14)\n"
        "lqc2 $vf11, 0($15)\n"
        "vsub.xyzw $vf10xyzw, $vf11xyzw, $vf10xyzw\n"
        "sqc2 $vf10, 0($16)\n"
        "b .Lw64a_1\n"
        "addi $11, $11, 1\n"
        ".Lw64a_2:\n"
        "lqc2 $vf10, 32($29)\n"
        "lqc2 $vf11, 16($29)\n"
        "lqc2 $vf12, 0($6)\n"
        "vsub.xyzw $vf10xyzw, $vf10xyzw, $vf11xyzw\n"
        "vsub.xyzw $vf10xyzw, $vf10xyzw, $vf12xyzw\n"
        "sqc2 $vf10, 16($6)\n"
        "vaddx.xyzw $vf11xyzw, $vf0xyzw, $vf1x\n"
        "sqc2 $vf11, 16($29)\n"
        "move $8, $10\n"
        "addi $8, $8, -1\n"
        "addi $11, $0, 1\n"
        ".Lw64a_3:\n"
        "blez $8, .Lw64a_4\n"
        "addi $8, $8, -1\n"
        "sll $12, $11, 0x4\n"
        "addi $13, $12, 16\n"
        "addi $14, $13, 16\n"
        "add $15, $12, $29\n"
        "add $16, $13, $29\n"
        "add $17, $14, $29\n"
        "add $18, $13, $6\n"
        "add $19, $12, $6\n"
        "lqc2 $vf10, 0($15)\n"
        "lqc2 $vf11, 0($16)\n"
        "lqc2 $vf12, 0($17)\n"
        "lqc2 $vf13, 0($19)\n"
        "vdiv Q, $vf0w, $vf10x\n"
        "vwaitq\n"
        "vaddq.x $vf15x, $vf0x, Q\n"
        "vdiv Q, $vf0w, $vf10y\n"
        "vwaitq\n"
        "vaddq.y $vf15y, $vf0y, Q\n"
        "vdiv Q, $vf0w, $vf10z\n"
        "vwaitq\n"
        "vaddq.z $vf15z, $vf0z, Q\n"
        "vsub.xyzw $vf16xyzw, $vf12xyzw, $vf11xyzw\n"
        "vmul.xyzw $vf17xyzw, $vf13xyzw, $vf15xyzw\n"
        "vsub.xyzw $vf17xyzw, $vf16xyzw, $vf17xyzw\n"
        "sqc2 $vf17, 0($18)\n"
        "vmuly.xyzw $vf18xyzw, $vf15xyzw, $vf1y\n"
        "vaddx.xyzw $vf18xyzw, $vf18xyzw, $vf1x\n"
        "sqc2 $vf18, 0($16)\n"
        "b .Lw64a_3\n"
        "addi $11, $11, 1\n"
        ".Lw64a_4:\n"
        "sll $11, $9, 0x4\n"
        "add $11, $11, $6\n"
        "sll $12, $10, 0x4\n"
        "add $12, $12, $6\n"
        "lqc2 $vf10, 0($11)\n"
        "lqc2 $vf11, 0($12)\n"
        "vsub.xyzw $vf11xyzw, $vf11xyzw, $vf10xyzw\n"
        "sqc2 $vf11, 0($12)\n"
        "move $11, $10\n"
        ".Lw64a_5:\n"
        "blezl $11, .Lw64a_6\n"
        "nop\n"
        "sll $12, $11, 0x4\n"
        "addi $13, $12, 16\n"
        "add $15, $12, $29\n"
        "add $16, $12, $6\n"
        "add $17, $13, $6\n"
        "lqc2 $vf10, 0($15)\n"
        "lqc2 $vf11, 0($16)\n"
        "lqc2 $vf12, 0($17)\n"
        "vsub.xyzw $vf11xyzw, $vf11xyzw, $vf12xyzw\n"
        "vdiv Q, $vf11x, $vf10x\n"
        "vwaitq\n"
        "vaddq.x $vf15x, $vf0x, Q\n"
        "vdiv Q, $vf11y, $vf10y\n"
        "vwaitq\n"
        "vaddq.y $vf15y, $vf0y, Q\n"
        "vdiv Q, $vf11z, $vf10z\n"
        "vwaitq\n"
        "vaddq.z $vf15z, $vf0z, Q\n"
        "sqc2 $vf15, 0($16)\n"
        "b .Lw64a_5\n"
        "addi $11, $11, -1\n"
        ".Lw64a_6:\n"
        ".set reorder\n"
        : : "r"(c), "r"(a), "r"(n), "r"(b), "m"(buf[0])
        : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15",
          "$16", "$17", "$18", "$19", "memory");
}

/* Hand-written VU0 routine: the asm body addresses its 16-byte work
 * buffer through $sp. */
extern u128 D_00372730;

void func_0019a828(u128 *a, s32 n, u128 *b) {
    u128 buf[128];
    register u128 *c asm("$2") = &D_00372730;

    __asm__ volatile(
        ".set noreorder\n"
        "addi $9, $5, -1\n"
        "addi $10, $5, -2\n"
        "lqc2 $vf1, 0($2)\n"
        "sqc2 $vf0, 0($6)\n"
        "sll $11, $9, 0x4\n"
        "add $11, $11, $6\n"
        "sqc2 $vf0, 0($11)\n"
        "move $8, $9\n"
        "move $11, $0\n"
        ".Lw64b_1:\n"
        "blez $8, .Lw64b_2\n"
        "addi $8, $8, -1\n"
        "sll $12, $11, 0x4\n"
        "addi $13, $12, 16\n"
        "add $14, $12, $4\n"
        "add $15, $13, $4\n"
        "add $16, $13, $29\n"
        "lqc2 $vf10, 0($14)\n"
        "lqc2 $vf11, 0($15)\n"
        "vsub.xyzw $vf10xyzw, $vf11xyzw, $vf10xyzw\n"
        "sqc2 $vf10, 0($16)\n"
        "b .Lw64b_1\n"
        "addi $11, $11, 1\n"
        ".Lw64b_2:\n"
        "lqc2 $vf10, 32($29)\n"
        "lqc2 $vf11, 16($29)\n"
        "lqc2 $vf12, 0($6)\n"
        "vsub.xyzw $vf10xyzw, $vf10xyzw, $vf11xyzw\n"
        "vsub.xyzw $vf10xyzw, $vf10xyzw, $vf12xyzw\n"
        "sqc2 $vf10, 16($6)\n"
        "vaddx.xyzw $vf11xyzw, $vf0xyzw, $vf1x\n"
        "sqc2 $vf11, 16($29)\n"
        "move $8, $10\n"
        "addi $8, $8, -1\n"
        "addi $11, $0, 1\n"
        ".Lw64b_3:\n"
        "blez $8, .Lw64b_4\n"
        "addi $8, $8, -1\n"
        "sll $12, $11, 0x4\n"
        "addi $13, $12, 16\n"
        "addi $14, $13, 16\n"
        "add $15, $12, $29\n"
        "add $16, $13, $29\n"
        "add $17, $14, $29\n"
        "add $18, $13, $6\n"
        "add $19, $12, $6\n"
        "lqc2 $vf10, 0($15)\n"
        "lqc2 $vf11, 0($16)\n"
        "lqc2 $vf12, 0($17)\n"
        "lqc2 $vf13, 0($19)\n"
        "vdiv Q, $vf0w, $vf10x\n"
        "vwaitq\n"
        "vaddq.x $vf15x, $vf0x, Q\n"
        "vdiv Q, $vf0w, $vf10y\n"
        "vwaitq\n"
        "vaddq.y $vf15y, $vf0y, Q\n"
        "vdiv Q, $vf0w, $vf10z\n"
        "vwaitq\n"
        "vaddq.z $vf15z, $vf0z, Q\n"
        "vsub.xyzw $vf16xyzw, $vf12xyzw, $vf11xyzw\n"
        "vmul.xyzw $vf17xyzw, $vf13xyzw, $vf15xyzw\n"
        "vsub.xyzw $vf17xyzw, $vf16xyzw, $vf17xyzw\n"
        "sqc2 $vf17, 0($18)\n"
        "vmuly.xyzw $vf18xyzw, $vf15xyzw, $vf1y\n"
        "vaddx.xyzw $vf18xyzw, $vf18xyzw, $vf1x\n"
        "sqc2 $vf18, 0($16)\n"
        "b .Lw64b_3\n"
        "addi $11, $11, 1\n"
        ".Lw64b_4:\n"
        "sll $11, $9, 0x4\n"
        "add $11, $11, $6\n"
        "sll $12, $10, 0x4\n"
        "add $12, $12, $6\n"
        "lqc2 $vf10, 0($11)\n"
        "lqc2 $vf11, 0($12)\n"
        "vsub.xyzw $vf11xyzw, $vf11xyzw, $vf10xyzw\n"
        "sqc2 $vf11, 0($12)\n"
        "move $11, $10\n"
        ".Lw64b_5:\n"
        "blezl $11, .Lw64b_6\n"
        "nop\n"
        "sll $12, $11, 0x4\n"
        "addi $13, $12, 16\n"
        "add $15, $12, $29\n"
        "add $16, $12, $6\n"
        "add $17, $13, $6\n"
        "lqc2 $vf10, 0($15)\n"
        "lqc2 $vf11, 0($16)\n"
        "lqc2 $vf12, 0($17)\n"
        "vsub.xyzw $vf11xyzw, $vf11xyzw, $vf12xyzw\n"
        "vdiv Q, $vf11x, $vf10x\n"
        "vwaitq\n"
        "vaddq.x $vf15x, $vf0x, Q\n"
        "vdiv Q, $vf11y, $vf10y\n"
        "vwaitq\n"
        "vaddq.y $vf15y, $vf0y, Q\n"
        "vdiv Q, $vf11z, $vf10z\n"
        "vwaitq\n"
        "vaddq.z $vf15z, $vf0z, Q\n"
        "sqc2 $vf15, 0($16)\n"
        "b .Lw64b_5\n"
        "addi $11, $11, -1\n"
        ".Lw64b_6:\n"
        ".set reorder\n"
        : : "r"(c), "r"(a), "r"(n), "r"(b), "m"(buf[0])
        : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15",
          "$16", "$17", "$18", "$19", "memory");
}

typedef struct {
    f32 x, y, z, w;
} PppSortEnt;

extern PppSortEnt *D_0061E310[]; /* src/data/bss_0061.c: PppLight *D_0061E310[256] */

/* Quicksort of D_0061E310 by ->w, largest first. The second recursive
 * call is a tail call that gcc turns into a jump. */
void func_0019d968(s32 lo, s32 hi) {
    s32 i, j;
    f32 pivot;
    PppSortEnt *t;

    pivot = D_0061E310[(lo + hi) / 2]->w;
    i = lo;
    j = hi;
    for (;;) {
        while (pivot < D_0061E310[i]->w)
            i++;
        while (D_0061E310[j]->w < pivot)
            j--;
        if (i >= j)
            break;
        t = D_0061E310[i];
        D_0061E310[i] = D_0061E310[j];
        D_0061E310[j] = t;
        i++;
        j--;
    }
    if (lo < i - 1)
        func_0019d968(lo, i - 1);
    if (j + 1 < hi)
        func_0019d968(j + 1, hi);
}

/* needs make: uses rodata (switch jump table) */

typedef struct {
    u8 pad[0x20];
    u16 time;   /* +0x20 */
    u16 cur;    /* +0x22 */
    u16 prev;   /* +0x24 */
    u16 live;   /* +0x26 */
    u8 pad28[0x38];
} PppMegaPart; /* 0x60 */

typedef struct {
    s32 frame;
    s32 id;     /* +0x4 */
    u16 speed;  /* +0x8 */
    u8 padA[0x12];
    u16 n;      /* +0x1C */
    u16 max;    /* +0x1E */
    u16 wait;   /* +0x20 */
    u8 pad22[4];
    u8 mode;    /* +0x26 */
    u8 pad27[0x71];
    f32 dir[3]; /* +0x98 */
    u8 padA4[0x25];
    u8 bC9;     /* +0xC9 */
    u8 padCA[2];
    u8 bCC;     /* +0xCC */
} PppMegaKey;

typedef struct { u8 b[0x40]; } PppMegaA;
typedef struct { u8 b[0x20]; } PppMegaB;

typedef struct {
    PppMtx m;           /* +0x00 */
    PppVec4 v;          /* +0x40 */
    PppMegaPart *parts; /* +0x50 */
    PppMegaA *a;        /* +0x54 */
    PppMegaB *b;        /* +0x58 */
    s32 n;              /* +0x5C */
    u16 timer;          /* +0x60 */
} PppMegaObj;

void func_0019cb88(PppMegaObj *obj, PppMegaKey *key, void *e);
void *func_0017f958(DSys *, s32);
void *memset(void *, s32, u32);
void func_002673b8(f32 *, f32 *);
s32 func_0019bb98(PppMegaObj *, PppMegaKey *);
void sceVu0UnitMatrix(PppMtx);
void sceVu0CopyMatrix(PppMtx, PppMtx);
void func_00267e90(f32 *, f32 *, f32);

void pppRyjMegaBirthFrame(PppObject *obj, PppMegaKey *key, PppEntry *e) {
    PppMegaObj *w = PPP_WORK(PppMegaObj, obj, e, 2);
    void *w1 = PPP_WORK(void, obj, e, 1);

    if (w->parts == 0) {
        w->n = key->n;
        w->parts = func_0017f958(D_00615E64, w->n * 96);
        if (w->parts)
            memset(w->parts, 0, w->n * 96);
        if ((u8) (key->bCC - 1) < 2) {
            w->a = func_0017f958(D_00615E64, w->n * 64);
            if (w->a)
                memset(w->a, 0, w->n * 64);
        }
        if (key->bC9) {
            w->b = func_0017f958(D_00615E64, w->n * 32);
            if (w->b)
                memset(w->b, 0, w->n * 32);
        }
        w->v[0] = key->dir[0];
        w->v[1] = key->dir[1];
        w->v[2] = key->dir[2];
        w->v[3] = 0.0f;
        func_002673b8(w->v, w->v);
    }
    if (!func_0019bb98(w, key))
        return;
    switch (key->mode) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
        sceVu0UnitMatrix(w->m);
        func_00267e90(w->m[0], w->m[0], D_003701F0[0]);
        func_00267e90(w->m[1], w->m[1], D_003701F0[1]);
        func_00267e90(w->m[2], w->m[2], D_003701F0[2]);
        func_002675a8(w->m[3], D_003701D0);
        w->m[3][3] = 1.0f;
        break;
    default:
        sceVu0CopyMatrix(w->m, D_00615E70);
        break;
    }
    func_0019cb88(w, key, w1);
}
