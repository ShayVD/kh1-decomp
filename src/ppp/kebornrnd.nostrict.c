/* The ppp random spawner classes, -fno-strict-aliasing (docs/modules.md
 * "Session 50"): pppKeBornRnd and its numbered variants start an effect
 * (func_00182588) at a random vertex of a mesh (the owner's or a resource's,
 * func_0018d390 ... 0018e0b0 pick the vertex and fill the new instance's
 * position and direction) when a random number passes the key's mask;
 * pppKeMvYpEff moves the owner along y by a speed (func_0018e5a8).
 * kebornrnd.c has the Cons and small frames, kebornrnd.nostrict_nofill.c
 * the point-complete spawner, keborn.nostrict.c a helper.  Types named
 * NAME_xxxxx are one function's own view (tools/shift/s50move/assemble.py).
 * Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_002BBFA0.h"
#include "ppp.h"
#include "data/bss_0061.h"
#include "data/types/nostrict_text_00180000_h40.h"
#include "data/pieces/D_003701F0.h"
#include "data/pieces/D_003701E0.h"
#include "data/pieces/D_003701D0.h"

/* pppKeBornRndFrame (from hand/nostrict/text_s7_w1.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
    s32 unk90, unk94;
} PppMtxOwner;
typedef f32 PppVec4[4] __attribute__((aligned(16)));
extern PppMtxOwner *D_00615E68;
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
void func_001a90f8(void *, void *, void *);
/* ---- func_0018d038 (pppKeBornRndFrame) ---- */
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
    PlatVu0CopyMatrix(mtx, D_00615E68->m);
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
        PlatVu0ApplyMatrix(d0, D_00615E68->m, v);
        p = &vb[vi];
        v[0] = p->x;
        v[1] = p->y;
        v[2] = p->z;
        PlatVu0ApplyMatrix(v, mtx, v);
        func_001a90f8(d1, v, D_00615E68->m[3]);
        if (rnd)
            idx = func_001a8f30() % m->n;
        else if (++idx >= m->n)
            idx = 0;
    }
    *w = idx;
}
#undef PPP_WORK

/* func_0018d390 (from hand/nostrict/text_00180000_h40.c). */
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} PppMtxOwner_8d390;
void func_001a9098(void *, f32 *);
typedef struct {
    s32 frame;
    s16 n;        /* +0x4 */
    s16 pad6;
    f32 speed;    /* +0x8 */
    u8 c;         /* +0xC */
    u8 mask;      /* +0xD */
    u8 b;         /* +0xE */
    u8 padF;
    s32 slot;     /* +0x10 */
    s32 off0;     /* +0x14 */
    s32 off1;     /* +0x18 */
    s32 off2;     /* +0x1C */
} PppBornKey;
#define D_00615E68 ((PppMtxOwner_8d390 *) D_00615E68)
void func_0018d390(void *owner, PppBornKey *key, s16 *pos) {
    PppVec4 v;
    PppSlot *slot = &D_00615E60->slots[key->slot];
    u8 *inst = 0;
    f32 *a, *b;

    if (slot) {
        inst = func_00182588(D_00615E60, slot);
        *(void **) (inst + 4) = owner;
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    v[3] = 1.0f;
    a = (f32 *) (inst + key->off0 + 0xA0);
    b = (f32 *) (inst + key->off2 + 0xA0);
    PlatVu0ApplyMatrix(v, D_00615E68->m[0], v);
    func_001a9098((void *) a, v);
    PlatVu0SubVector(v, v, D_00615E68->m[3]);
    PlatVu0Normalize(v, v);
    PlatVu0ScaleVector(v, v, key->speed);
    func_001a9098((void *) b, v);
}
#undef D_00615E68

/* func_0018d5c0 (from hand/nostrict/text_00180000_h40.c). */
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} PppMtxOwner_8d5c0;
typedef struct {
    s32 frame;
    s16 n;        /* +0x4 */
    u8 c;         /* +0x6 */
    u8 mask;      /* +0x7 */
    u8 b;         /* +0x8 */
    u8 pad9[3];
    s32 slot;     /* +0xC */
    s32 off0;     /* +0x10 */
    s32 off1;     /* +0x14 */
    s32 off2;     /* +0x18 */
} PppBorn3Key;
#define D_00615E68 ((PppMtxOwner_8d5c0 *) D_00615E68)
void func_0018d5c0(void *owner, PppBorn3Key *key, s16 *pos) {
    PppVec4 v;
    PppSlot *slot = &D_00615E60->slots[key->slot];
    u8 *inst = 0;
    f32 *a, *b;

    if (slot) {
        inst = func_00182588(D_00615E60, slot);
        *(void **) (inst + 4) = owner;
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    v[3] = 1.0f;
    a = (f32 *) (inst + key->off0 + 0xA0);
    b = (f32 *) (inst + key->off2 + 0xA0);
    PlatVu0ApplyMatrix(v, D_00615E68->m[0], v);
    func_001a9098((void *) a, v);
    PlatVu0SubVector(v, v, D_00615E68->m[3]);
    PlatVu0Normalize(v, v);
    func_001a9098((void *) b, v);
}
#undef D_00615E68

/* func_0018d7d8 (from hand/nostrict/text_00190000_h63.c). */
typedef struct {
    u8 pad[0x30];
    f32 col[4];     /* +0x30 */
    u8 pad40[0x40];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem_8d7d8;
static inline u8 *inl_spawn_8d7d8(PppSystem_8d7d8 *sys, s32 id, PppObject *o) {
    PppSlot *s = &sys->slots[id];
    u8 *i = 0;

    if (s) {
        i = func_00182588(sys, s);
        *(PppObject **) (i + 4) = o;
    }
    return i;
}
typedef struct {
    s32 frame;
    s32 unk4;
    f32 speed;    /* +0x8 */
    s32 unkC;
    s32 slot;     /* +0x10 */
    s32 off0;     /* +0x14 */
    s32 unk18;
    s32 off2;     /* +0x1C */
    s32 unk20;
    s32 off1;     /* +0x24 */
} PppBorn2Key;
#define D_00615E60 ((PppSystem_8d7d8 *) D_00615E60)
void func_0018d7d8(PppObject *owner, PppBorn2Key *key, s16 *pos) {
    PppVec4 v;
    u8 *inst = inl_spawn_8d7d8(D_00615E60, key->slot, owner);
    f32 *a, *b, *c;

    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    v[3] = 1.0f;
    a = (f32 *) (inst + key->off0 + 0xA0);
    c = (f32 *) (inst + key->off2 + 0xA0);
    b = (f32 *) (inst + key->off1 + 0xA0);
    PlatVu0ApplyMatrix(v, D_00615E68->m[0], v);
    func_001a9098((void *) a, v);
    PlatVu0SubVector(v, v, D_00615E68->m[3]);
    PlatVu0Normalize(v, v);
    func_001a9098((void *) b, v);
    PlatVu0ScaleVector(v, v, key->speed);
    func_001a9098((void *) c, v);
}
#undef D_00615E60

/* pppKeBornRnd4Frame (from hand/nostrict/text_00180000_b07.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 frame;
    s16 n;        /* +0x4 */
    s16 pad6;
    f32 speed;    /* +0x8 */
    u8 c;         /* +0xC */
    u8 mask;      /* +0xD */
    u8 b;         /* +0xE */
    u8 padF;
    s32 slot;     /* +0x10 */
    s32 off0;     /* +0x14 */
    s32 off1;     /* +0x18 */
    s32 off2;     /* +0x1C */
    s32 off3;     /* +0x20 */
    s32 off4;     /* +0x24 */
} PppBorn4Key;
extern s32 D_00616234;
void func_001a5520(PppObject *, PppBorn4Key *, void *, void *, s16, u8, u8);
void pppKeBornRnd4Frame(PppObject *obj, PppBorn4Key *key, PppEntry *e) {
    PppObject **pp = &obj;
    PppVec4 v;
    u16 *w;
    s32 rnd;
    s32 r;
    VtxMap *m;
    VtxS16 *va;
    s32 idx;
    s32 k;

    if (D_00616234 != 0)
        return;
    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL) && key->mask != 0xFF &&
        !((func_001a8f30() >> 8) & key->mask)) {
        if (key->slot == -1 || key->off1 == -1 || key->off3 == -1)
            return;
        func_001a5520(obj, key, func_0018d7d8, PPP_WORK(void, obj, e, 0), key->n, key->b, key->c);
    }
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    r = func_001a8f30();
    if (key->mask == 0xFF)
        return;
    if ((r >> 8) & key->mask)
        return;
    if (key->slot == -1 || key->off1 == -1 || key->off3 == -1)
        return;
    w = PPP_WORK(u16, obj, e, 0);
    m = &D_00615E64->maps[key->n];
    va = ((PppVtxOwner *) D_00615E68)->vtx;
    if (va == 0)
        va = D_00615E64->res[m->slot].vtx;
    rnd = key->b;
    if (rnd)
        idx = r % m->n;
    else
        idx = *w;
    for (k = key->c; k > 0; k--) {
        u8 *inst = inl_spawn(D_00615E60, key->slot, obj);
        s32 vi = m->map[idx];
        u8 *d0 = inst + key->off0 + 0xA0;
        u8 *d2 = inst + key->off2 + 0xA0;
        u8 *d1 = inst + key->off4 + 0xA0;
        VtxS16 *p;

        p = &va[vi];
        v[0] = p->x;
        v[1] = p->y;
        v[2] = p->z;
        v[3] = 1.0f;
        idx++;
        PlatVu0ApplyMatrix(v, D_00615E68->m, v);
        func_001a9098(d0, v);
        PlatVu0SubVector(v, v, D_00615E68->m[3]);
        PlatVu0Normalize(v, v);
        func_001a9098(d1, v);
        PlatVu0ScaleVector(v, v, key->speed);
        func_001a9098(d2, v);
        if (rnd)
            idx = func_001a8f30() % m->n;
        else if (idx >= m->n)
            idx = 0;
    }
    *w = idx;
}
#undef PPP_WORK

/* func_0018dd08 (from hand/nostrict/text_00180000_h40.c). */
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} PppMtxOwner_8dd08;
#define D_00615E68 ((PppMtxOwner_8dd08 *) D_00615E68)
void func_0018dd08(void *owner, PppBornKey *key, s16 *pos) {
    PppVec4 v;
    PppSlot *slot = &D_00615E60->slots[key->slot];
    u8 *inst = 0;
    f32 *a, *b;

    if (slot) {
        inst = func_00182588(D_00615E60, slot);
        *(void **) (inst + 4) = owner;
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    v[3] = 1.0f;
    a = (f32 *) (inst + key->off0 + 0xA0);
    b = (f32 *) (inst + key->off2 + 0xA0);
    PlatVu0ApplyMatrix(v, D_00615E68->m[0], v);
    func_001a9098((void *) a, v);
    PlatVu0SubVector(v, v, D_00615E68->m[3]);
    PlatVu0Normalize(v, v);
    PlatVu0ScaleVector(v, v, key->speed);
    func_001a9098((void *) b, v);
}
#undef D_00615E68

/* func_0018df30 (from hand/nostrict/text_00190000_h63.c). */
double atan(double);
s32 func_0018df30(f32 *v, f32 *out) {
    f32 x = v[0];
    f32 y = v[1];
    f32 r = x * y;

    if (0.0f < r) {
        r = 0.0f;
        if (!(r < x))
            r = -3.1415927f;
        r = r + atan(y / x);
    } else if (r < 0.0f) {
        r = 1.5707963f;
        if (!(0.0f < y))
            r = -1.5707963f;
        r = r - atan(x / y);
    } else if (x != 0.0f) {
        r = 3.1415927f;
        if (0.0f < x)
            r = 0.0f;
    } else {
        if (y == 0.0f)
            return 0;
        r = -1.5707963f;
        if (0.0f < y)
            r = 1.5707963f;
    }
    *out = r;
    return 1;
}

/* func_0018e0b0 (from hand/nostrict/text_00190000_h63.c). */
typedef struct {
    u8 pad[0x30];
    f32 col[4];     /* +0x30 */
    u8 pad40[0x40];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem_8e0b0;
static inline u8 *inl_spawn_8e0b0(PppSystem_8e0b0 *sys, s32 id, PppObject *o) {
    PppSlot *s = &sys->slots[id];
    u8 *i = 0;

    if (s) {
        i = func_00182588(sys, s);
        *(PppObject **) (i + 4) = o;
    }
    return i;
}
f32 func_001a9328(f32);
typedef struct {
    s32 frame;
    s32 unk4, unk8;
    s32 slot;     /* +0xC */
    s32 off0;     /* +0x10 */
    s32 unk14;
    s32 off1;     /* +0x18 */
} PppBorn3Key_8e0b0;
#define D_00615E60 ((PppSystem_8e0b0 *) D_00615E60)
void func_0018e0b0(PppObject *owner, PppBorn3Key_8e0b0 *key, s16 *pos) {
    PppVec4 v;
    f32 ang;
    u8 *inst = inl_spawn_8e0b0(D_00615E60, key->slot, owner);
    s32 *r;
    f32 x, y;

    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    v[3] = 1.0f;
    func_001a9098(inst + key->off0 + 0xA0, v);
    y = v[1];
    x = v[0];
    r = (s32 *) (inst + key->off1 + 0xA0);
    v[1] = x;
    v[0] = -y;
    if (func_0018df30(v, &ang))
        r[2] = ang * 32768.0f / 3.141592654;
    v[0] = func_001a9328(y * y + x * x);
    v[1] = -v[2];
    if (func_0018df30(v, &ang))
        r[0] = ang * 32768.0f / 3.141592654;
    r[1] = 0;
}
#undef D_00615E60

/* func_0018e5a8 (from hand/nostrict/text_00190000_h63.c). */
s32 func_0018e5a8(f32 *v, f32 *out) {
    f32 x = v[0];
    f32 y = v[1];
    f32 r = x * y;

    if (0.0f < r) {
        r = 0.0f;
        if (!(r < x))
            r = -3.1415927f;
        r = r + atan(y / x);
    } else if (r < 0.0f) {
        r = 1.5707963f;
        if (!(0.0f < y))
            r = -1.5707963f;
        r = r - atan(x / y);
    } else if (x != 0.0f) {
        r = 3.1415927f;
        if (0.0f < x)
            r = 0.0f;
    } else {
        if (y == 0.0f)
            return 0;
        r = -1.5707963f;
        if (0.0f < y)
            r = 1.5707963f;
    }
    *out = r;
    return 1;
}

/* pppKeMvYpEffFrame (from hand/nostrict/text_00190000_h63.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    u8 pad[0x30];
    f32 col[4];     /* +0x30 */
    u8 pad40[0x40];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem_8e728;
#define D_00615E60 ((PppSystem_8e728 *) D_00615E60)
void pppKeMvYpEffFrame(PppObject *obj, void *key, PppEntry *e) {
    PppVec4 t;
    f32 ang;
    f32 *v;
    s32 *r;
    f32 y, x;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    v = PPP_WORK(f32, obj, e, 1);
    y = v[1];
    x = v[0];
    if (y == 0.0f && x == 0.0f && v[2] == 0.0f)
        return;
    r = PPP_WORK(s32, obj, e, 0);
    t[1] = x;
    t[0] = -y;
    if (func_0018e5a8(t, &ang))
        r[2] = ang * 32768.0f / 3.141592654;
    t[0] = func_001a9328(y * y + x * x);
    t[1] = -v[2];
    if (func_0018e5a8(t, &ang))
        r[0] = ang * 32768.0f / 3.141592654;
}
#undef D_00615E60
#undef PPP_WORK

