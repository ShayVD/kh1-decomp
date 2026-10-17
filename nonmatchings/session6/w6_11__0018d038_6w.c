/* pppKeBornRndFrame 0018d038, nostrict: 6 words off. Only the inl_spawn result register in the loop (ours t0, orig a3): sched1 issues i=0 early so it conflicts with a3. Same family issue as func_0018e348. */
/* Hand-matched functions (worker b07). Built without strict aliasing. */
#include "common.h"
#include "ppp.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

void sceVu0MulMatrix(void *, void *, void *);

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;

typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
    s32 unk90, unk94;
} PppMtxOwner;

typedef f32 PppVec4[4] __attribute__((aligned(16)));

extern PppMtxOwner *D_00615E68;
extern PppMtx D_00615FC0;

typedef struct {
    s32 init;
    f32 a, da, dda;  /* +0x4 */
    f32 b, db, ddb;  /* +0x10 */
} PppMdlLoop;

typedef struct {
    s16 x, y, z;
} VtxS16;

typedef struct {
    s16 slot;  /* +0x0 */
    s16 n;     /* +0x2 */
    u16 *map;  /* +0x4 */
} VtxMap;

typedef struct {
    u8 pad[0x10];
    u32 tex;      /* +0x10 */
    VtxS16 *vtx;  /* +0x14 */
    s32 pad18;
    s32 *mdl;     /* +0x1C */
    s32 arg;      /* +0x20 */
} PppMdlRes; /* 0x24 */

typedef struct {
    u8 pad[0x10];
    PppMdlRes *res; /* +0x10 */
    void *p14;
    VtxMap *maps;   /* +0x18 */
} PppMdlBank;

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
extern PppSystem *D_00615E60;

u8 *func_00182588(PppSystem *, PppSlot *);

/* Start an instance of program slot `id` owned by `o`. */

extern PppMdlBank *D_00615E64;

static inline u8 *inl_spawn(PppSystem *sys, s32 id, void *o) {
    PppSlot *s = &sys->slots[id];
    u8 *i = 0;

    if (s) {
        i = func_00182588(sys, s);
        *(void **) (i + 4) = o;
    }
    return i;
}

typedef struct {
    s32 frame;
    s16 map0;     /* +0x4 */
    s16 map1;     /* +0x6 */
    u8 count;     /* +0x8 */
    u8 mask;      /* +0x9 */
    u8 rnd;       /* +0xA */
    u8 padB;
    s32 slot;     /* +0xC */
    s32 off0;     /* +0x10 */
    s32 off1;     /* +0x14 */
    s32 off2;     /* +0x18 */
} PppBornRndKey;

typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
    VtxS16 *vtx; /* +0x90 */
} PppVtxOwner;

s32 func_001a8f30(void);
void sceVu0CopyMatrix(void *, void *);
void func_002672f8(void *, void *, void *);
void func_001a90f8(void *, void *, void *);

void pppKeBornRndFrame(PppObject *obj, PppBornRndKey *key, PppEntry *e) {
    PppObject **pp = &obj;
    PppMtx mtx;
    PppVec4 v;
    u16 *w;
    VtxS16 *vb;
    s32 rnd;
    s32 r;
    VtxMap *m, *m1;
    VtxS16 *va;
    s32 idx;
    s32 k;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    r = func_001a8f30();
    if (key->mask == 0xFF)
        return;
    if ((r >> 8) & key->mask)
        return;
    if (key->slot == -1 || key->off1 == -1)
        return;
    m1 = (VtxMap *) ((u32) key->map1 * 8 + (u32) D_00615E64->maps);
    m = &D_00615E64->maps[key->map0];

    w = PPP_WORK(u16, obj, e, 0);
    vb = D_00615E64->res[m1->slot].vtx;
    va = ((PppVtxOwner *) D_00615E68)->vtx;
    if (m->n != m1->n)
        return;
    if (va == 0)
        va = D_00615E64->res[m->slot].vtx;
    rnd = key->rnd;
    v[3] = 1.0f;
    sceVu0CopyMatrix(mtx, D_00615E68->m);
    if (rnd)
        idx = r % m->n;
    else
        idx = *w;
    for (k = key->count; k > 0; k--) {
        s32 vi = m->map[idx];
        u8 *inst;
        u8 *d0, *d1;
        VtxS16 *p;

        idx++;
        inst = inl_spawn(D_00615E60, key->slot, obj);
        d0 = inst + key->off0 + 0xA0;
        d1 = inst + key->off2 + 0xA0;
        p = &va[vi];
        v[0] = p->x;
        v[1] = p->y;
        v[2] = p->z;
        func_002672f8(d0, D_00615E68->m, v);
        p = &vb[vi];
        v[0] = p->x;
        v[1] = p->y;
        v[2] = p->z;
        func_002672f8(v, mtx, v);
        func_001a90f8(d1, v, D_00615E68->m[3]);
        if (rnd)
            idx = func_001a8f30() % m->n;
        else if (idx >= m->n)
            idx = 0;
    }
    *w = idx;
}
