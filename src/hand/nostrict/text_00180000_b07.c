/* Hand-matched functions (worker b07). Built without strict aliasing. */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"

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
static inline u8 *inl_spawn(PppSystem *sys, s32 id, void *o) {
    PppSlot *s = &sys->slots[id];
    u8 *i = 0;

    if (s) {
        i = func_00182588(sys, s);
        *(void **) (i + 4) = o;
    }
    return i;
}

extern PppMdlBank *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
extern u8 D_00616240[];
extern u8 D_00616140[];
extern u8 D_00616100[];
extern s32 D_00616224;

/* --- func_00182870: build the object matrix D_00615E70 --- */

typedef struct {
    f32 x, y, z, w;
} V4F __attribute__((aligned(16)));

typedef struct {
    u8 pad0[0x80];
    f32 x80, x84, x88;
    u8 pad8c[4];
    u8 x90[0x10];
    f32 xa0, xa4, xa8;
    u8 padac[0xf9 - 0xac];
    u8 xf9;
    u8 xfa;
    u8 padfb[0x104 - 0xfb];
    s32 x104;
} MOwner;

typedef struct {
    f32 x0, x4, x8;
    u8 padc[4];
    u8 x10[0x10];
    f32 x20, x24, x28;
    u8 pad2c[0x14];
    f32 x40, x44, x48;
    u8 pad4c[0x8c - 0x4c];
    MOwner *own;
    u8 pad90[0xb2 - 0x90];
    u8 xb2;
} MObj;

extern V4F D_00615E70;
V4F D_00615E80 ALIGNED(16);
V4F D_00615E90 ALIGNED(16);
V4F D_00615EA0 ALIGNED(16);
extern V4F D_00615F70; /* src/data/bss_0061.c: f32 D_00615F70[4] */
#include "data/pieces/D_003701F0.h"
#include "data/pieces/D_003701E0.h"
#include "data/pieces/D_003701D0.h"

void func_00183be0(void *, void *);
void func_002675a8(void *, void *);
void func_00121fc4(void *, void *);
f32 atan2f(f32, f32);
f32 asinf(f32);

static inline void vu0ScaleRow2(f32 s, void *row) {
    __asm__ volatile(
        "qmtc2 %1, $vf9\n"
        "lqc2 $vf10, 0(%0)\n"
        "vmulx.xyz $vf10xyz, $vf10xyz, $vf9x\n"
        "sqc2 $vf10, 0(%0)\n"
        : : "r"(row), "r"(s));
}

static inline void setTrans(V4F *m, MObj *o) {
    m[3].x = o->x0;
    m[3].y = o->x4;
    m[3].z = o->x8;
}

static inline void addTrans(V4F *m, V4F *d) {
    m[3].x += d->x;
    m[3].z += d->z;
}

void func_00182870(MObj *o) {
    V4F m[4];
    f32 ang[3];
    s32 i;

    func_00183be0(&D_00615E70, o->x10);
    vu0ScaleRow2(o->x20, &D_00615E70);
    vu0ScaleRow2(o->x24, &D_00615E80);
    vu0ScaleRow2(o->x28, &D_00615E90);
    if (o->own->xf9) {
        vu0ScaleRow2(o->x40, &D_00615E70);
        vu0ScaleRow2(o->x44, &D_00615E80);
        vu0ScaleRow2(o->x48, &D_00615E90);
    }
    setTrans(&D_00615E70, o);
    func_00183be0(m, o->own->x90);
    vu0ScaleRow2(o->own->xa0, &m[0]);
    vu0ScaleRow2(o->own->xa4, &m[1]);
    vu0ScaleRow2(o->own->xa8, &m[2]);
    m[3].x = o->own->x80;
    m[3].y = o->own->x84;
    m[3].z = o->own->x88;
    sceVu0MulMatrix(&D_00615E70, &D_00615E70, m);
    if (o->own->xfa && o->own->x104 >= 0) {
        func_00183be0(m, o->own->x90);
        vu0ScaleRow2(o->own->xa0 * o->x20, &m[0]);
        vu0ScaleRow2(o->own->xa4 * o->x24, &m[1]);
        vu0ScaleRow2(o->own->xa8 * o->x28, &m[2]);
        func_002675a8(&D_00615E70, &m[0]);
        func_002675a8(&(&D_00615E70)[1], &m[1]);
        func_002675a8(&(&D_00615E70)[2], &m[2]);
    }
    if (o->xb2) {
        addTrans(&D_00615E70, &D_00615F70);
    }
    {
        f32 *w;
        i = 0;
        w = &m[0].w;
        for (; i < 3; i++) {
            func_00121fc4(&m[i], &(&D_00615E70)[i]);
            D_003701F0[i] = *w;
            *w = 0.0f;
            w += 4;
        }
    }
    ang[0] = atan2f(-m[1].z, m[0].z);
    ang[1] = asinf(-m[2].z);
    ang[2] = atan2f(m[2].y, m[2].x);
    for (i = 0; i < 3; i++) D_003701E0[i] = ang[i] * 32768.0f / 3.1415926f;
    func_002675a8(((u8 *)&D_003701D0), &D_00615EA0);
}

/* --- pppDrawMdl* draw callbacks: fill a PppMdlDraw for func_001aaf88 --- */
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
    s32 i40;
    void *i44;     /* +0x44 */
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
    u8 f23, f24, f25, f26;
} PppMdlKey;

typedef struct {
    u8 pad[8];
    u8 col[4];
} PppColWork;

s32 func_001aaf88(s32 *, PppMdlDraw *, s32);

void pppDrawMdlLoopZDraw(PppObject *obj, PppMdlKey *key, PppEntry *e) {
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
    d.u = w->a * 65536.0f;
    d.v = w->b * 65536.0f;
    if (key->f26)
        d.i44 = PPP_WORK(u8, obj, e, 3);
    else
        d.i44 = 0;
    d.i1C = 0;
    d.m2 = D_00615E68->m2;
    d.p24 = D_00616140;
    d.p28 = D_00616100;
    d.m = D_00615E68->m;
    d.i34 = D_00616224;
    d.i38 = D_00615E68->unk90;
    d.i3C = D_00615E68->unk94;
    d.i40 = 0;
    d.b4C = 0;
    d.b4D = 0;
    D_00616224 = func_001aaf88(mdl, &d, D_00615E64->res[key->id].arg);
}

/* --- pppKeThSft: per-frame shift of a key work area --- */

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame;   /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;    /* +0x9D */
} PppObjectB;

typedef struct {
    s32 frame;
    u16 h[16];   /* +0x04 */
    f32 v[4];    /* +0x24 */
    u8 b34;      /* +0x34 */
} PppThSftKey;

typedef struct {
    u16 h[16];   /* +0x00 */
    f32 v[4];    /* +0x20 */
} PppThSftWork;

typedef struct {
    u8 pad[0x50];
    u8 b50;      /* +0x50 */
    u8 pad51[0x1B];
    f32 f6C;     /* +0x6C */
    u16 h[16];   /* +0x70 */
} PppThSftDst;

typedef struct {
    u8 pad[0xC];
    f32 f0C;     /* +0x0C */
    u8 pad10[0x14];
    f32 f24;     /* +0x24 */
    u8 pad28[4];
    f32 f2C;     /* +0x2C */
} PppThSftDst2;

void pppKeThSftFrame(PppObjectB *obj, PppThSftKey *key, PppEntry *e) {
    PppThSftWork *w;
    PppThSftDst *d;
    PppThSftDst2 *d2;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w = PPP_WORK(PppThSftWork, obj, e, 0);
    d = PPP_WORK(PppThSftDst, obj, e, 1);
    d2 = (PppThSftDst2 *) ((u8 *) obj + e->offsets[1] + 0xB0);
    if (obj->frame == key->frame) {
        d->b50 = key->b34;
        w->v[2] += key->v[2];
        w->v[0] += key->v[0];
        w->v[1] += key->v[1];
        w->v[3] += key->v[3];
        w->h[0] += key->h[0];
        w->h[1] += key->h[1];
        w->h[2] += key->h[2];
        w->h[3] += key->h[3];
        w->h[4] += key->h[4];
        w->h[5] += key->h[5];
        w->h[6] += key->h[6];
        w->h[7] += key->h[7];
        w->h[8] += key->h[8];
        w->h[9] += key->h[9];
        w->h[10] += key->h[10];
        w->h[11] += key->h[11];
        w->h[12] += key->h[12];
        w->h[13] += key->h[13];
        w->h[14] += key->h[14];
        w->h[15] += key->h[15];
        if (obj->frame == 0 && obj->unk9D == 0)
            return;
    }
    d->f6C += w->v[2];
    d2->f0C += w->v[0];
    d2->f24 += w->v[1];
    d2->f2C += w->v[3];
    d->h[0] += w->h[0];
    d->h[1] += w->h[1];
    d->h[2] += w->h[2];
    d->h[3] += w->h[3];
    d->h[4] += w->h[4];
    d->h[5] += w->h[5];
    d->h[6] += w->h[6];
    d->h[7] += w->h[7];
    d->h[8] += w->h[8];
    d->h[9] += w->h[9];
    d->h[10] += w->h[10];
    d->h[11] += w->h[11];
    d->h[12] += w->h[12];
    d->h[13] += w->h[13];
    d->h[14] += w->h[14];
    d->h[15] += w->h[15];
}

/* --- pppKeBornRnd: spawn instances at vertices of a vertex map --- */
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


/* --- pppKeBornRnd4: born-at-random plus spawn at vertices --- */
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
void func_0018d7d8(void *owner, PppBorn4Key *key, s16 *pos);
void func_001a5520(PppObject *, PppBorn4Key *, void *, void *, s16, u8, u8);
void func_001a9098(void *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);

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
        func_002672f8(v, D_00615E68->m, v);
        func_001a9098(d0, v);
        func_00267530(v, v, D_00615E68->m[3]);
        func_002673b8(v, v);
        func_001a9098(d1, v);
        func_00267560(v, v, key->speed);
        func_001a9098(d2, v);
        if (rnd)
            idx = func_001a8f30() % m->n;
        else if (idx >= m->n)
            idx = 0;
    }
    *w = idx;
}

/* --- pppKeMdlTfdUv / Uv2: scrolled texture page upload, then draw --- */
typedef struct {
    s32 frame;
    s32 id;         /* +0x4 */
    f32 d0[3];      /* +0x8 */
    s32 u, v;       /* +0x14 */
    u8 page;        /* +0x1C */
    u8 pad1D[3];
    f32 d1[3];      /* +0x20 */
    f32 d2[3];      /* +0x2C */
    u8 b38;         /* +0x38 */
} PppTfdUvKey;

s32 sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
void func_001a9460(f32, s32, s32, void *);
void func_001aa6b0(void *, s32, s32, s32);
void func_001a9790(s32, void *, s32, s32, s32, s32, void *);

void pppKeMdlTfdUvDraw(PppObject *obj, PppTfdUvKey *key, PppEntry *e) {
    f32 *w = PPP_WORK(f32, obj, e, 2);
    u32 tex;
    s32 n;
    u8 *p, *q;

    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w[1] += w[2];
        w[5] += w[6];
        w[8] += w[9];
        w[0] += w[1];
        w[4] += w[5];
        w[7] += w[8];
        if (obj->frame == key->frame) {
            w[0] += key->d0[0];
            w[1] += key->d0[1];
            w[2] += key->d0[2];
            w[4] += key->d1[0];
            w[5] += key->d1[1];
            w[6] += key->d1[2];
            w[7] += key->d2[0];
            w[8] += key->d2[1];
            w[9] += key->d2[2];
        }
    }
    if (key->id == 0xFFFF)
        return;
    {
        PppMdlRes *r = &D_00615E64->res[key->id];
        tex = r->tex;
    }
    n = key->page * 4;
    p = (u8 *) D_00616224 + 16;
    sceGsSetDefLoadImage(p, ((tex >> 5) & 0x3FFF) + n, 4, (tex >> 19) & 0xF, 0, 0, 16, 16);
    *(u64 *) (p + 0x50) = 0x0800000000008100ULL;
    q = (u8 *) D_00616224;
    func_001a9460(w[0], key->u, key->v, q + 0x70);
    func_001aa6b0((void *) D_00616224, 263, 0, 0);
    D_00616224 = (s32) (q + 0x1070);
    func_001a9790(key->id, PPP_WORK(void, obj, e, 0), n, w[4], w[7], 1, 0);
}

void pppKeMdlTfdUv2Draw(PppObject *obj, PppTfdUvKey *key, PppEntry *e) {
    f32 *w = PPP_WORK(f32, obj, e, 2);
    u32 tex;
    s32 n;
    u8 *p, *q;

    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w[1] += w[2];
        w[5] += w[6];
        w[8] += w[9];
        w[0] += w[1];
        w[4] += w[5];
        w[7] += w[8];
        if (obj->frame == key->frame) {
            w[0] += key->d0[0];
            w[1] += key->d0[1];
            w[2] += key->d0[2];
            w[4] += key->d1[0];
            w[5] += key->d1[1];
            w[6] += key->d1[2];
            w[7] += key->d2[0];
            w[8] += key->d2[1];
            w[9] += key->d2[2];
        }
    }
    if (key->id == 0xFFFF)
        return;
    {
        PppMdlRes *r = &D_00615E64->res[key->id];
        tex = r->tex;
    }
    n = key->page * 4;
    p = (u8 *) D_00616224 + 16;
    sceGsSetDefLoadImage(p, ((tex >> 5) & 0x3FFF) + n, 4, (tex >> 19) & 0xF, 0, 0, 16, 16);
    *(u64 *) (p + 0x50) = 0x0800000000008100ULL;
    q = (u8 *) D_00616224;
    func_001a9460(w[0], key->u, key->v, q + 0x70);
    func_001aa6b0((void *) D_00616224, 263, 0, 0);
    D_00616224 = (s32) (q + 0x1070);
    func_001a9790(key->id, PPP_WORK(void, obj, e, 0), n, w[4], w[7], key->b38, 0);
}

/* --- pppKeShpTail3Frame --- */
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

/* --- pppKeShpDttDraw --- */
typedef struct {
    s32 frame;
    f32 d[3];     /* +0x4 */
    f32 sx, sy;   /* +0x10 */
    u8 mode;      /* +0x18 */
    u8 flags;     /* +0x19 */
} PppDttKey;

typedef struct {
    PppVec4 v;        /* +0x00 */
    f32 col[4];       /* +0x10 */
    void *p20;        /* +0x20 */
    u8 *p24;          /* +0x24 */
    void *p28;        /* +0x28 */
    s32 x2C;          /* +0x2C */
    PppVec4 pos;      /* +0x30 */
    u64 tag0;         /* +0x40 */
    u64 tag1;         /* +0x48 */
    u64 tag2;         /* +0x50 */
    f32 sx, sy;       /* +0x58 */
} PppDttDraw;

typedef unsigned int u128 __attribute__((mode(TI)));
extern u8 D_00616040[];
extern s32 D_00616228;
void func_001a99e8(PppDttDraw *);
s32 func_001a9c30(PppDttDraw *);
void func_001aa750(void *, u32, s32, s32);

static inline void dttSet(f32 *v, f32 x, f32 y, f32 z, f32 w) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

void pppKeShpDttDraw(PppObject *obj, PppDttKey *key, PppEntry *e) {
    u8 *w2 = PPP_WORK(u8, obj, e, 2);
    f32 *w0 = PPP_WORK(f32, obj, e, 0);
    u8 *w1;
    PppDttDraw d;
    PppSystem **ps = &D_00615E60;

    if (D_0061621C == 0 && !((*ps)->flags & 0xFF0000FF00ULL)) {
        w0[1] += w0[2];
        w0[0] += w0[1];
        if (obj->frame == key->frame) {
            w0[0] += key->d[0];
            w0[1] += key->d[1];
            w0[2] += key->d[2];
        }
    }
    w1 = PPP_WORK(u8, obj, e, 1);
    d.col[0] = w1[8];
    d.col[1] = w1[9];
    d.col[2] = w1[10];
    d.col[3] = w1[11];
    if (key->flags & 2) {
        f32 *w3 = PPP_WORK(f32, obj, e, 3);
        d.v[0] = w3[0];
        d.v[1] = w3[1];
        d.v[2] = 512.0f;
        d.v[3] = 1.0f;
        d.p28 = D_00616040;
    } else {
        *(u128 *) d.v = *(u128 *) (w2 + 48);
        d.p28 = D_00616040;
    }
    d.p20 = D_00616040;
    d.p24 = (u8 *) D_00616224 + 16;
    d.sx = key->sx * D_003701F0[0];
    d.sy = key->sy * D_003701F0[1];
    if (key->mode == 0) {
        d.tag0 = 0x2A8021A00ULL;
        d.tag2 = 0x740000007000ULL;
    } else {
        d.tag0 = 0x2A8020000ULL;
        d.tag2 = 0x720000007000ULL;
    }
    d.tag1 = 0x017F000001FF0000ULL;
    d.pos[0] = d.pos[1] = d.pos[2] = d.pos[3] = 0.0f;
    d.pos[1] = -w0[0];
    func_002672f8(d.pos, w2, d.pos);
    *(s32 *) &d.pos[3] = key->flags;
    func_001a99e8(&d);
    if (func_001a9c30(&d)) {
        if (key->flags & 2)
            func_001aa6b0((void *) D_00616224, (u32) (d.p24 - (u8 *) D_00616224) >> 4, 4, 0);
        else
            func_001aa750((void *) D_00616224, (u32) (d.p24 - (u8 *) D_00616224) >> 4, d.x2C / 0x3000, 0);
        D_00616228 += d.p24 - (u8 *) D_00616224;
        D_00616224 = (s32) d.p24;
    }
}

/* --- pppKeTkFadeDraw: build a faded 256-entry CLUT and upload it --- */
typedef struct {
    s32 frame;
    s32 id;       /* +0x4 */
    f32 d[3];     /* +0x8 */
    u32 col0;     /* +0x14 */
    u32 col1;     /* +0x18 */
} PppTkFadeKey;

typedef struct {
    u8 pad0[0xC];
    s32 lo;       /* +0xC */
    s32 hi;       /* +0x10 */
} TkRes;

typedef struct {
    u32 clut[256];
    s8 tbl[32];
} TkBuf;

extern u128 D_00372770[2];
extern s8 D_00372790[];
void *func_001aa950(s32);
void func_001aa9d0(s32);
void func_00267518(f32 *, f32 *, f32 *);
void func_002674b0(f32 *, f32 *, f32);
void FlushCache(s32);
s32 sceGsExecLoadImage(void *, void *);
s32 sceGsSyncPath(s32, s32);

void pppKeTkFadeDraw(PppObject *obj, PppTkFadeKey *key, PppEntry *e) {
    f32 *w = PPP_WORK(f32, obj, e, 0);
    PppVec4 b;
    PppVec4 a;
    u8 li[96];
    TkBuf *buf;
    u32 *p;
    u32 c0, c1;
    u64 tex;
    s32 n, i;
    f32 sc;

    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w[1] += w[2];
        w[0] += w[1];
        if (obj->frame == key->frame) {
            w[0] += key->d[0];
            w[1] += key->d[1];
            w[2] += key->d[2];
        }
    }
    if (key->id == 0xFFFF)
        return;
    buf = func_001aa950(0x420);
    ((u128 *) buf->tbl)[0] = D_00372770[0];
    ((u128 *) buf->tbl)[1] = D_00372770[1];
    {
        TkRes *r = (TkRes *) &D_00615E64->res[key->id];
        c1 = key->col1;
        tex = ((u64) r->hi << 32) | r->lo;
        c0 = key->col0;
        n = w[0];
    }
    if (n < 0) {
        if (n < -256)
            n = -256;
        n += 256;
        p = &buf->clut[(n & 0xE0) + D_00372790[n & 0x1F]];
        for (i = n; i < 256; i++) {
            *p = c0;
            p += buf->tbl[i & 0x1F];
        }
        i = 0;
        sc = n;
        p = buf->clut;
    } else {
        if (n >= 256)
            n = 255;
        p = buf->clut;
        for (i = 0; i < n; i++) {
            *p = c1;
            p += buf->tbl[i & 0x1F];
        }
        sc = 256.0f - n;
        n = 256;
    }
    a[0] = (s32) (c1 & 0xFF);
    a[1] = (s32) ((c1 >> 8) & 0xFF);
    a[2] = (s32) ((c1 >> 16) & 0xFF);
    a[3] = (s32) (c1 >> 24);
    b[0] = (s32) (c0 & 0xFF);
    b[1] = (s32) ((c0 >> 8) & 0xFF);
    b[2] = (s32) ((c0 >> 16) & 0xFF);
    b[3] = (s32) (c0 >> 24);
    func_00267530(b, b, a);
    func_002674b0(b, b, sc);
    for (; i < n; i++) {
        *p = ((u32) a[3] << 24) | ((u32) a[2] << 16) | ((u32) a[1] << 8) | (u32) a[0];
        func_00267518(a, a, b);
        p += buf->tbl[i & 0x1F];
    }
    sceGsSetDefLoadImage(li, (u16) ((tex >> 37) & 0x3FFF), 4, (u16) ((tex >> 51) & 0xF), 0, 0, 16, 16);
    FlushCache(0);
    sceGsExecLoadImage(li, buf);
    sceGsSyncPath(0, 0);
    func_001aa9d0(0x420);
}

/* --- pppDrawMdlTs3Draw --- */
typedef struct {
    u32 flags;  /* +0x0 */
    u8 pad04[0x12];
    u16 unk16;  /* +0x16 */
} Ts3Mdl;

typedef struct {
    s32 frame;
    s32 slot;     /* +0x4 */
    u8 pad8[0x18];
    u8 flags;     /* +0x20 */
    u8 f21, f22, f23, f24, f25;
} PppTs3Key;

void pppDrawMdlTs3Draw(PppObject *obj, PppTs3Key *key, PppEntry *e) {
    PppMdlDraw p;
    PppMtx mtx;
    PppColWork *w;
    f32 *t = PPP_WORK(f32, obj, e, 2);
    PppMdlRes *s;
    Ts3Mdl *m;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(PppColWork, obj, e, 0);
    p.col[3] = w->col[3];
    if (p.col[3] == 0)
        return;
    s = &D_00615E64->res[key->slot];
    m = (Ts3Mdl *) s->mdl;
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
    if (key->f21)
        p.flags |= 0x200;
    if (key->f23)
        p.flags |= 0x100;
    if (key->f22) {
        p.flags |= 0x2000;
        p.mtx = mtx;
        sceVu0MulMatrix(mtx, D_00615FC0, D_00615E68->m);
    }
    if (key->f24)
        p.i44 = PPP_WORK(u8, obj, e, 3);
    else
        p.i44 = 0;
    p.h08 = m->unk16;
    p.b0A = 0;
    p.i1C = 0;
    p.i38 = D_00615E68->unk90;
    p.i3C = D_00615E68->unk94;
    p.i0C = 0;
    p.p04 = D_00616240;
    p.u = t[0] * 65536.0f;
    p.v = t[3] * 65536.0f;
    p.i40 = 0;
    p.col[0] = w->col[0];
    p.col[1] = w->col[1];
    p.col[2] = w->col[2];
    p.m2 = D_00615E68->m2;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.m = D_00615E68->m;
    p.i34 = D_00616224;
    p.b4D = key->f25;
    p.b4C = 0;
    D_00616224 = func_001aaf88((s32 *) m, &p, s->arg);
}
#include "data/data_0037.h"
