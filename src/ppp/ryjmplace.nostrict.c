/* The pppRyjMegaPlace classes' -fno-strict-aliasing functions
 * (docs/modules.md "Session 50"): func_0019e028 / e108 / e1e8 take a free
 * shape / model / lamp entry of the owner's pool for a pppRyjMegaPlaceShape
 * / Model / Lamp key (its table entry's origin plus the key's offset);
 * func_0019e3f0 draws the shape entries (func_001b8198), func_0019e710 the
 * models (opdma.c's func_001aaf88), func_0019ea58 the lamps (a flickering
 * shape: D_003732D0's sine table).  ryjmplace.c has the classes' Con, Des,
 * frames and the draw that calls these three.  Read from the code, not proved
 * by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "ppp.h"
#include "data/bss_0061.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef int u128 __attribute__((mode(TI)));
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

typedef struct {
    s32 unk0;
    u8 *inst;
    s32 time;
    s32 unkC;
} PppSlot;

typedef struct {
    u8 pad[0x80];
    PppSlot *slots;
    u8 pad84[0x2C];
    u64 flags;
} PppSystem;

extern s32 D_0061621C;
extern PppSystem *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */

typedef struct {
    u32 flags;
    u8 pad04[0x12];
    u16 unk16;
} DMdl;

typedef struct {
    s32 pad0[4];
    u32 tex;
    s32 pad14[2];
    DMdl *mdl;
    s32 unk20;
} DSlot;

typedef struct {
    u8 pad00[0x10];
    DSlot *slots;
    void *shapes;
} DSys;

extern DSys *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
extern s32 D_00616224;
typedef struct {
    u8 pad[0x10];
    PppMtx m;
    PppMtx m2;
    s32 unk90;
    s32 unk94;
} PppMtxOwner;
extern PppMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
typedef struct {
    s32 flags;
    void *p04;
    u16 h08;
    u8 b0A;
    s32 w0C;
    union { u64 d; struct { s32 u, v; } s; } t10;
    u8 r, g, b, a;
    s32 w1C;
    void *p20;
    void *p24;
    void *p28;
    void *p2C;
    void *p30;
    s32 w34;
    s32 w38;
    s32 w3C;
    s32 w40;
    void *p44;
    s32 w48;
    u8 b4C;
    u8 b4D;
    u8 pad4E[0x12];
} DParam;
extern u8 D_00616240[];
s32 func_001aaf88(DMdl *, DParam *, s32);
typedef struct {
    u16 unk0;
    u16 flags;
    u8 r, g, b, a;
    u64 d8;
    void *p10;
    s32 w14;
    u8 b18;
    void *p1C;
    u8 pad20[0x10];
} DShpParam;
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
s32 func_001b8198(void *, DShpParam *, s32);
extern PppMtx D_00616040; /* src/data/bss_0061.c: u8 D_00616040[0x40] */

/* The pools (from text_00180000_h40.c). */
typedef union {
    f32 f[4];
    u128 q;
} PppQv;

/* Effect instance pools: each slot points back at its source and at the
 * model record func_0019dfc8 finds for the source's id. */
typedef struct {
    u8 pad0[0x10];
    PppQv org;   /* +0x10 */
} PppMdlRec;

typedef struct {
    s32 unk0;
    s32 id;       /* +0x4 */
    u8 pad8[0x18];
    f32 ofs[3];   /* +0x20 */
} PppSrcA;

typedef struct {
    s32 unk0;
    s32 id;       /* +0x4 */
    u8 pad8[0x1C];
    f32 ofs[3];   /* +0x24 */
    u8 pad30[0x10];
    u8 a, b, c;   /* +0x40 */
} PppSrcB;

typedef struct {
    f32 pos[4];
    void *src;        /* +0x10 */
    PppMdlRec *rec;   /* +0x14 */
    u8 pad18[8];
} PppSlotA;

typedef struct {
    f32 pos[4];
    void *src;        /* +0x10 */
    PppMdlRec *rec;   /* +0x14 */
    u8 pad18[4];
    u8 a, b;          /* +0x1C */
    s16 c;            /* +0x1E */
    u8 pad20[0x10];
} PppSlotB;

typedef struct {
    u32 n0;
    u32 n1;
    u32 n2;
    PppSlotA *a;  /* +0xC */
    PppSlotA *b;  /* +0x10 */
    PppSlotB *c;  /* +0x14 */
} PppPool;

PppMdlRec *func_0019dfc8(s32);

s32 func_0019e028(PppPool *pool, PppSrcA *src) {
    u32 i;
    PppSlotA *s;

    if (!pool->a)
        return 0;
    for (i = 0; i < pool->n0; i++) {
        s = &pool->a[i];
        if (s->src == 0) {
            s->src = src;
            s->rec = func_0019dfc8(src->id);
            PlatVu0CopyVector(s->pos, s->rec->org.f);
            s->pos[0] += src->ofs[0];
            s->pos[1] += src->ofs[1];
            s->pos[2] += src->ofs[2];
            s->pos[3] = 1.0f;
            break;
        }
    }
    return 1;
}

s32 func_0019e108(PppPool *pool, PppSrcA *src) {
    u32 i;
    PppSlotA *s;

    if (!pool->b)
        return 0;
    for (i = 0; i < pool->n1; i++) {
        s = &pool->b[i];
        if (s->src == 0) {
            s->src = src;
            s->rec = func_0019dfc8(src->id);
            PlatVu0CopyVector(s->pos, s->rec->org.f);
            s->pos[0] += src->ofs[0];
            s->pos[1] += src->ofs[1];
            s->pos[2] += src->ofs[2];
            s->pos[3] = 1.0f;
            break;
        }
    }
    return 1;
}

s32 func_0019e1e8(PppPool *pool, PppSrcB *src) {
    u32 i;
    PppSlotB *s;

    if (!pool->c)
        return 0;
    for (i = 0; i < pool->n2; i++) {
        s = &pool->c[i];
        if (s->src == 0) {
            s->src = src;
            s->rec = func_0019dfc8(src->id);
            s->a = src->a;
            s->b = src->b;
            s->c = 32767 / src->c;
            PlatVu0CopyVector(s->pos, s->rec->org.f);
            s->pos[0] += src->ofs[0];
            s->pos[1] += src->ofs[1];
            s->pos[2] += src->ofs[2];
            s->pos[3] = 1.0f;
            break;
        }
    }
    return 1;
}
typedef struct {
    s32 frame;
    s32 unk4;
    s32 id;        /* +0x08 */
    u16 speed;     /* +0x0C */
    u8 padE[2];
    u8 b10, b11, b12, b13;
    f32 ofs[3];    /* +0x14 */
    u8 pad20[0xC];
    f32 sx, sy, sz; /* +0x2C */
    u8 r, g, b, a; /* +0x38 */
    u8 mode;       /* +0x3C */
} RKey;
typedef struct {
    f32 pos[4];
    RKey *key;     /* +0x10 */
    void *p14;     /* +0x14 */
    u16 time;      /* +0x18 */
    u16 frame;     /* +0x1A */
    u8 pad1C[4];
} RItem;
typedef struct {
    u32 n;
    u8 pad4[8];
    RItem *items;  /* +0x0C */
} RList;
extern PppMtx D_00615EB0;

void func_0019e3f0(RList *l) {
    DShpParam p;
    PppMtx mtx;
    u32 i;

    i = 0;
    p.d8 = 0;
    p.p10 = D_00615E68->m2;
    p.b18 = 0;
    for (; i < l->n; i++) {
        RItem *it = &l->items[i];
        RKey *k = it->key;
        PppShapeEnt *s;
        PppShape *sh;
        PppShapeFrame *fr;
        u8 *src;
        u32 fi;

        if (k == 0 || it->p14 == 0)
            continue;
        if (!k->a)
            continue;
        p.flags = 0;
        if (k->mode == 1)
            p.flags = 16;
        if (k->b10)
            p.flags |= 0x800;
        if (k->b11)
            p.flags |= 0x400;
        fi = it->frame;
        if (k->id == 0xFFFF)
            continue;
        s = &((DSysS *) D_00615E64)->shapes[k->id];
        p.r = k->r;
        p.g = k->g;
        p.b = k->b;
        p.a = k->a;
        sh = s->shape;
        fr = &sh->f[fi];
        src = (u8 *) sh + fr->off;
        p.p1C = 0;
        PlatVu0UnitMatrix(D_00615E68->m2);
        D_00615E68->m2[0][0] = k->sx;
        D_00615E68->m2[1][1] = k->sy;
        D_00615E68->m2[2][2] = k->sz;
        PlatVu0ApplyMatrix(D_00615E68->m2[3], D_00615EB0, it->pos);
        if (k->b13) {
            PlatVu0CopyMatrix(mtx, D_00615E68->m2);
            mtx[3][0] += k->ofs[0];
            mtx[3][1] += k->ofs[1];
            mtx[3][2] += k->ofs[2];
            PlatVu0MulMatrix(mtx, D_00616040, mtx);
            p.p1C = mtx;
        }
        PlatVu0MulMatrix(D_00615E68->m2, D_00616040, D_00615E68->m2);
        {
            s32 *gp = &D_00616224;
            p.w14 = *gp;
            *gp = func_001b8198(src, &p, s->unk4);
        }
        if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
            continue;
        it->time += k->speed;
        if (it->time >= fr->dur) {
            it->time -= fr->dur;
            it->frame++;
            if (it->frame >= sh->n) {
                if (fr->flags & 0x80) {
                    it->frame = 0;
                    it->time = 0;
                } else {
                    it->frame--;
                    it->time = 0;
                }
            }
        }
    }
}

typedef struct {
    s32 frame;
    s32 unk4;
    s32 id;        /* +0x08 */
    u8 flags, bD, bE, bF;
    u8 b10, b11, b12, b13;
    f32 ofs[3];    /* +0x14 */
    u8 pad20[0xC];
    f32 rot[3];    /* +0x2C */
    f32 sx, sy, sz; /* +0x38 */
    u8 r, g, b, a; /* +0x44 */
    u8 b48;        /* +0x48 */
} MKey;
typedef struct {
    f32 pos[4];
    MKey *key;     /* +0x10 */
    void *p14;     /* +0x14 */
    u8 pad18[8];
} MItem;
typedef struct {
    u32 unk0;
    u32 n;         /* +0x04 */
    u8 pad8[8];
    MItem *items;  /* +0x10 */
} MList;
extern PppMtx D_00615EB0, D_00616180;
void func_00183be0(PppMtx, f32 *);

static inline void vu0ScaleRow(f32 *row, f32 s) {
    __asm__ volatile(
        "qmtc2 %1, $vf9\n"
        "lqc2 $vf10, 0(%0)\n"
        "vmulx.xyz $vf10xyz, $vf10xyz, $vf9x\n"
        "sqc2 $vf10, 0(%0)\n"
        : : "r"(row), "r"(s));
}

void func_0019e710(MList *l) {
    PppMtx mtx;
    DParam p;
    u32 i;

    p.p2C = 0;
    p.p28 = 0;
    p.p24 = 0;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.p04 = D_00616240;
    p.w0C = 0;
    p.t10.d = 0;
    p.p20 = D_00615E68->m2;
    p.w40 = 0;

    for (i = 0; i < l->n; i++) {
        MItem *it = &l->items[i];
        MKey *k = it->key;
        DSlot *s;
        DMdl *m;

        if (k == 0 || it->p14 == 0)
            continue;
        if (!k->a)
            continue;
        if (k->id == 0xFFFF)
            continue;
        func_00183be0(D_00615E68->m, k->rot);
        vu0ScaleRow(D_00615E68->m[0], k->sx);
        vu0ScaleRow(D_00615E68->m[1], k->sy);
        vu0ScaleRow(D_00615E68->m[2], k->sz);
        PlatVu0CopyVector(D_00615E68->m[3], it->pos);
        if (k->b11) {
            PlatVu0MulMatrix(mtx, D_00615EB0, D_00615E68->m);
            mtx[3][0] += k->ofs[0];
            mtx[3][1] += k->ofs[1];
            mtx[3][2] += k->ofs[2];
            PlatVu0MulMatrix(mtx, D_00616040, mtx);
            p.p44 = mtx;
        } else {
            p.p44 = 0;
        }
        PlatVu0MulMatrix(D_00615E68->m2, D_00616180, D_00615E68->m);
        s = &D_00615E64->slots[k->id];
        m = s->mdl;
        p.flags = 0;
        if (k->flags & 2) {
            p.flags = 4;
            if (!(m->flags & 1))
                p.flags |= 8;
        } else {
            if (k->flags & 1)
                p.flags = 128;
            if (!(m->flags & 1))
                p.flags |= 8;
        }
        if (!(m->flags & 2))
            p.flags |= 16;
        if (k->bD)
            p.flags |= 0x200;
        if (k->bF)
            p.flags |= 0x100;
        p.h08 = m->unk16;
        p.r = k->r;
        p.g = k->g;
        p.b = k->b;
        p.a = k->a;
        p.b4C = k->b10;
        p.b4D = k->b48;
        p.w34 = D_00616224;
        D_00616224 = func_001aaf88(m, &p, s->unk20);
    }
}

typedef struct {
    s32 frame;
    s32 unk4;
    s32 id;        /* +0x08 */
    u16 speed;     /* +0x0C */
    u8 padE[2];
    u8 b10, b11, b12, b13;
    f32 ofs[3];    /* +0x14 */
    u8 pad20[0x10];
    f32 sx, sy, sz; /* +0x30 */
    u8 r, g, b, a; /* +0x3C */
    u8 b40, b41, b42, b43;
    u8 mode;       /* +0x44 */
} FKey;
typedef struct {
    f32 pos[4];
    FKey *key;     /* +0x10 */
    void *p14;     /* +0x14 */
    u16 time;      /* +0x18 */
    u16 frame;     /* +0x1A */
    u8 c0, c1;     /* +0x1C */
    u16 dec;       /* +0x1E */
    s32 val;       /* +0x20 */
    u8 pad24[0xC];
} FItem;
typedef struct {
    u32 unk0;
    u32 unk4;
    u32 n;         /* +0x08 */
    u8 padC[8];
    FItem *items;  /* +0x14 */
} FList;
extern PppMtx D_00615EB0;
extern f32 D_003732D0[];

void func_0019ea58(FList *l) {
    DShpParam p;
    PppMtx mtx;
    u32 i;
    u32 off;

    i = 0;
    p.d8 = 0;
    p.p10 = D_00615E68->m2;
    p.b18 = 0;
    if (i < l->n) {
    off = 0;
    do {
        FItem *it = (FItem *) ((u8 *) l->items + off);
        FKey *k = it->key;
        PppShapeEnt *s;
        PppShape *sh;
        PppShapeFrame *fr;
        u8 *src;
        u32 fi;
        f32 f;
        s32 a;
        FKey *k1, *k2;

        if (k == 0 || it->p14 == 0)
            continue;
        if (--it->c0 == 255) {
            it->c0 = k->b40;
            if (it->val == 0)
                it->val = 32767;
        }
        if (--it->c1 == 255) {
            it->c1 = k->b41;
            if (it->val == 0)
                it->val = 32767;
        }
        if (it->val != 0) {
            s32 v = it->val - it->dec;
            if (v < 0)
                v = 0;
            it->val = v;
        }
        p.flags = 0;
        if (k->mode == 1)
            p.flags = 16;
        if (k->b10)
            p.flags |= 0x800;
        if (k->b11)
            p.flags |= 0x400;
        fi = it->frame;
        if (k->id == 0xFFFF)
            continue;
        s = &((DSysS *) D_00615E64)->shapes[k->id];
        p.r = k->r;
        p.g = k->g;
        p.b = k->b;
        f = D_003732D0[(it->val & 0xFFFF) >> 4];
        if (f < 0.0f)
            f = -f;
        k1 = k;
        k2 = k;
        a = k->a - (u8) (k->b43 * f);
        if (a < 0)
            a = 0;
        p.a = a;
        sh = s->shape;
        fr = &sh->f[fi];
        src = (u8 *) sh + fr->off;
        p.p1C = 0;
        PlatVu0UnitMatrix(D_00615E68->m2);
        D_00615E68->m2[0][0] = k2->sx;
        D_00615E68->m2[1][1] = k1->sy;
        D_00615E68->m2[2][2] = k1->sz;
        PlatVu0ApplyMatrix(D_00615E68->m2[3], D_00615EB0, it->pos);
        if (k1->b12) {
            PlatVu0CopyMatrix(mtx, D_00615E68->m2);
            mtx[3][0] += k1->ofs[0];
            mtx[3][1] += k1->ofs[1];
            mtx[3][2] += k1->ofs[2];
            PlatVu0MulMatrix(mtx, D_00616040, mtx);
            p.p1C = mtx;
        }
        PlatVu0MulMatrix(D_00615E68->m2, D_00616040, D_00615E68->m2);
        {
            s32 *gp = &D_00616224;
            p.w14 = *gp;
            *gp = func_001b8198(src, &p, s->unk4);
        }
        if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
            continue;
        it->time += k1->speed;
        if (it->time >= fr->dur) {
            it->time -= fr->dur;
            it->frame++;
            if (it->frame >= sh->n) {
                if (fr->flags & 0x80) {
                    it->frame = 0;
                    it->time = 0;
                } else {
                    it->frame--;
                    it->time = 0;
                }
            }
        }
    } while (i++, off += 48, i < l->n);
    }
}
