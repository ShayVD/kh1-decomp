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
    func_002675a8(&D_003701D0, &D_00615EA0);
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
void sceVu0CopyMatrix(void *, void *);
void func_001a90f8(void *, void *, void *);

/* --- pppKeBornRnd4: born-at-random plus spawn at vertices --- */

/* --- pppKeMdlTfdUv / Uv2: scrolled texture page upload, then draw --- */

/* --- pppKeShpTail3Frame --- */

/* --- pppKeShpDttDraw --- */

typedef unsigned int u128 __attribute__((mode(TI)));

static inline void dttSet(f32 *v, f32 x, f32 y, f32 z, f32 w) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

/* --- pppKeTkFadeDraw: build a faded 256-entry CLUT and upload it --- */

/* --- pppDrawMdlTs3Draw --- */
#include "data/data_0037.h"
