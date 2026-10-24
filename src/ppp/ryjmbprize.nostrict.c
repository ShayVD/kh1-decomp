/* The pppRyjMegaBirthPrize class's draw, -fno-strict-aliasing (docs/modules.md
 * "Session 50"): the prizes (HP / MP balls, munny) dropped in the field.
 * func_0019dac8 collects the live entries of D_0035C710 (flag 0x100 set,
 * 0x200 clear) into D_0061E310 with their squared distance from the camera
 * D_002E2780 and sorts them far to near (func_0019d968, a quicksort);
 * pppRyjMegaBirthPrizeDraw draws each one's shape frame with its type's
 * colour and scale (ten types in the key) and steps its animation.  The Con
 * is in ryjmbprize.c.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "ppp.h"
#include "data/bss_0061.h"
#include "data/types/nostrict_text_00180000_h40.h"
#include "data/pieces/D_002E2780.h"

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

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject;

typedef struct {
    u8 pad[0x10];
    PppMtx m;     /* +0x10 */
    PppMtx m2;    /* +0x50 */
    s32 unk90;    /* +0x90 */
    s32 unk94;    /* +0x94 */
} PppMtxOwner;

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
    u8 pad00[0x14];
    PppShapeEnt *shapes;
} DSysS;

extern s32 D_0061621C;
extern PppSystem *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */
extern s32 D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
extern PppMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
extern s32 D_00616224;
extern PppMtx D_00615EB0; /* src/data/bss_0061.c: u8 D_00615EB0[0x40] */
extern PppMtx D_00616040; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
extern PppLight *D_0061E310[256];

/* func_0019d968's view: the sort key is the entry's fourth word. */
typedef struct {
    f32 x, y, z, w;
} PppSortEnt;

#define D_0061E310 ((PppSortEnt **) D_0061E310)
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
#undef D_0061E310

typedef union {
    f32 f[4];
    u128 q;
} PppQv;


void func_0019dac8(void) {
    PppQv d;
    PppLight *p = D_0035C710;
    s32 i;

    D_0061E710 = 0;
    for (i = 0; i < 256; i++, p++) {
        if (!(p->u.w & 0x100))
            continue;
        if (p->u.w & 0x200)
            continue;
        {
            PlatVu0SubVector(d.f, &D_002E2780.x, p->v);
            PlatVu0MulVector(d.f, d.f, d.f);
            D_0061E310[D_0061E710] = p;
            D_0061E710++;
            p->v[3] = d.f[0] + d.f[1] + d.f[2];
        }
    }
    if (D_0061E710 >= 2)
        func_0019d968(0, D_0061E710 - 1);
    for (i = 0; i < D_0061E710; i++)
        D_0061E310[i]->v[3] = 1.0f;
}

/* pppRyjMegaBirthPrizeDraw's views (from text_00190000_b08.c). */
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
    s32 id;
    u8 r, g, b, a;
    f32 scale;
} PrizeEnt;

typedef struct {
    s32 frame;
    PrizeEnt ent[10];  /* +0x04 */
    u8 pad7C[0];
    u16 speed;         /* +0x7C */
    u8 pad7E[2];
    u8 b80, b81;
} PrizeKey;

typedef struct {
    f32 pos[3];
    f32 dist;   /* +0xC */
    f32 scale;  /* +0x10 */
    f32 alpha;  /* +0x14 */
    union {
        u64 flags;
        struct { u8 type; u8 pad[3]; s16 time; s16 frame; } s;
    } u;        /* +0x18 */
} PrizeObj;

s32 func_001b8198(void *, DShpParam *, s32);

#define D_0061E310 ((PrizeObj **) D_0061E310)
void pppRyjMegaBirthPrizeDraw(PppObject *obj, PrizeKey *key, PppEntry *e) {
    PppMtx m[10];
    DShpParam p;
    PrizeEnt *ents = key->ent;
    s32 i;

    p.flags = 0;
    if (key->b80)
        p.flags = 0x800;
    if (key->b81)
        p.flags |= 0x400;
    p.p1C = 0;
    p.d8 = 0;
    p.b18 = 0;
    p.p10 = D_00615E68->m2;
    for (i = 0; i < 10; i++) {
        PrizeEnt *pe = &ents[i];
        PlatVu0UnitMatrix(m[i]);
        PlatVu0ScaleVector(m[i][0], m[i][0], pe->scale);
        PlatVu0ScaleVector(m[i][1], m[i][1], pe->scale);
        PlatVu0ScaleVector(m[i][2], m[i][2], pe->scale);
    }
    func_0019dac8();
    for (i = 0; i < D_0061E710; i++) {
        PrizeObj *o = D_0061E310[i];
        PrizeEnt *en;
        PppShapeEnt *s;
        PppShape *sh;
        PppShapeFrame *fr;
        u8 *src;
        s32 t;
        f32 al;
        f32 (*mm)[4];
        s32 fi;

        if (o->u.flags & 0x400) {
            o->u.s.time = 0;
            o->u.s.frame = 0;
            o->u.flags &= ~0x400;
        }
        t = o->u.s.type;
        al = o->alpha;
        en = (PrizeEnt *) (t * 12 + (u32) ents);
        fi = o->u.s.frame;
        if (en->id == 0xFFFF)
            continue;
        mm = m[t];
        s = &((DSysS *) D_00615E64)->shapes[en->id];
        p.r = en->r;
        p.g = en->g;
        p.b = en->b;
        p.a = en->a * al;
        sh = s->shape;
        fr = &sh->f[fi];
        src = (u8 *) sh + fr->off;
        PlatVu0CopyMatrix(D_00615E68->m2, mm);
        PlatVu0ApplyMatrix(D_00615E68->m2[3], D_00615EB0, o->pos);
        PlatVu0ScaleVector(D_00615E68->m2[0], D_00615E68->m2[0], o->scale);
        PlatVu0ScaleVector(D_00615E68->m2[1], D_00615E68->m2[1], o->scale);
        PlatVu0ScaleVector(D_00615E68->m2[2], D_00615E68->m2[2], o->scale);
        PlatVu0MulMatrix(D_00615E68->m2, D_00616040, D_00615E68->m2);
        {
            s32 *gp = &D_00616224;
            p.w14 = *gp;
            *gp = func_001b8198(src, &p, s->unk4);
        }
        if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
            continue;
        o->u.s.time += key->speed;
        if (o->u.s.time >= fr->dur) {
            o->u.s.time -= fr->dur;
            o->u.s.frame++;
            if (o->u.s.frame >= sh->n) {
                if (fr->flags & 0x80) {
                    o->u.s.frame = 0;
                    o->u.s.time = 0;
                } else {
                    o->u.s.frame--;
                    o->u.s.time = 0;
                }
            }
        }
    }
}
#undef D_0061E310
