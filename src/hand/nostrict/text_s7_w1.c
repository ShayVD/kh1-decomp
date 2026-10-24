#include "common.h"

/* ---- func_00135bb0 ---- */
typedef union { u64 x; struct { u32 lo; u32 x32:13; u32 b45:1; u32 x46:3; u32 b49:1; u32 hi:14; } b; } F370e;
typedef struct { u8 p0[0x40]; f32 sx, sy, sz; u8 p4c[4]; f32 f50[4]; u8 p60[0xd0-0x60]; f32 fd0[4][4]; u8 p110[0x370-0x110]; F370e f370; } Ob9;
#include "data/pieces/D_002BBFA0.h"
extern void func_00135b88(Ob9 *, void *);
extern void sceVu0CopyMatrix(void *, void *);
extern void func_002675a8(f32 *, f32 *);
extern void sceVu0MulMatrix(void *, void *, void *);
extern s32 func_0012f040(Ob9 *, s32);
extern void func_0012ec88(Ob9 *, f32 *);
extern s32 func_0024edf0(f32 (*)[4], void *);
void func_00135a68(void *, f32, f32);
CONTEXT_ONLY void func_00135b88(Ob9 *o, void *b) { func_00135a68(b, *(f32 *)((u8 *)o + 0x410), *(f32 *)((u8 *)o + 0x414)); }
s32 func_00135bb0(Ob9 *o) {
    f32 m[4][4];
    f32 v[4];
    u8 buf[128];
    if (o->f370.b.b45 && o->sx * o->sy * o->sz == 0.0f) return 0;
    if (o->f370.b.b49) goto r1;
    func_00135b88(o, buf);
    sceVu0CopyMatrix(m, o->fd0);
    func_002675a8(m[3], o->f50);
    m[3][3] = 1.0f;
    sceVu0MulMatrix(m, D_002BBFA0, m);
    if (func_0012f040(o, -1)) {
        func_0012ec88(o, v);
        if (func_0024edf0(m, buf) == 0) goto r1;
        return 0;
    }
    if (func_0024edf0(m, buf) == 0) goto r1;
    return 0;
r1:
    return 1;
}

/* ---- func_0018d038 (pppKeBornRndFrame) ---- */
/* Hand-matched functions (worker b07). Built without strict aliasing. */
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

extern PppMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
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
extern PppSystem *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */

u8 *func_00182588(PppSystem *, PppSlot *);

/* Start an instance of program slot `id` owned by `o`. */

extern PppMdlBank *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */

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
        else if (++idx >= m->n)
            idx = 0;
    }
    *w = idx;
}
