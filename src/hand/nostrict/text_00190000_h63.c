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
double atan(double);

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
void func_001a9098(void *, void *);

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

void func_002672f8(PppVec4, f32 *, PppVec4);
void func_00267530(f32 *, f32 *, f32 *);
void func_002673b8(PppVec4, PppVec4);
void func_00267560(f32 *, PppVec4, f32);
f32 func_001a9328(f32);

typedef struct {
    u8 pad[0x10];
    u32 tex;    /* +0x10 */
    u8 pad14[8];
    s32 *mdl;   /* +0x1C */
    s32 arg;    /* +0x20 */
} PppMdlRes; /* 0x24 */

typedef struct {
    u8 pad[0x9D];
    u8 unk9D;  /* +0x9D */
} PppObjectB;

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


extern PppMtx D_00615E70;
void func_002675a8(PppVec4, f32 *);

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


extern u8 D_00616040[];
extern u8 D_003701F0[];

typedef struct {
    void *work;    /* +0x00 */
    u8 col[4];     /* +0x04 */
    void *p08;     /* +0x08 */
    f32 f0C;       /* +0x0C */
    void *p10;     /* +0x10 */
} PppLnsDraw;

typedef struct {
    s32 frame;
    s32 unk4;
    u8 col[4];     /* +0x8 */
    f32 f0C;       /* +0xC */
} PppLnsKey;


typedef struct {
    void *work;    /* +0x00 */
    u8 col[4];     /* +0x04 */
    void *p08;     /* +0x08 */
    f32 f0C;       /* +0x0C */
    f32 f10;       /* +0x10 */
    void *p14;     /* +0x14 */
} PppLnsClmDraw;

typedef struct {
    s32 frame;
    s32 unk4;
    u8 col[4];     /* +0x8 */
    f32 f0C;       /* +0xC */
    u16 h10, h12;  /* +0x10 */
    u16 h14;       /* +0x14 */
} PppLnsClmKey;


typedef struct {
    void *work;    /* +0x00 */
    u8 col[4];     /* +0x04 */
    void *p08;     /* +0x08 */
    f32 f0C;       /* +0x0C */
    u16 h10, h12;  /* +0x10 */
    void *p14;     /* +0x14 */
} PppLnsCrnDraw;


f32 func_001a9350(PppVec4);
void func_001a9110(void *, void *, PppVec4);

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

typedef struct {
    s32 frame;
    s32 slot;    /* +0x4 */
    s32 off;     /* +0x8 */
    u8 on;       /* +0xC */
} PppHitBornKey;

typedef struct { u8 m[0x30]; } PppJoint;

typedef struct PppHitNode {
    struct PppHitNode *next;  /* +0x00 */
    u8 pad04[0x32];
    u8 joint;                 /* +0x36 */
    u8 pad37;
    union { u64 x; u16 h[4]; } flags;                  /* +0x38 */
    PppJoint joints[1];       /* +0x40 */
} PppHitNode;


void pppKeThHitBornFrame(PppObject *obj, PppHitBornKey *key, PppEntry *e) {
    u8 *w = PPP_WORK(u8, obj, e, 1);
    PppHitNode *n;
    u8 *inst;

    if (obj->frame == key->frame) {
        if (key->on)
            *w |= 2;
        else
            *w &= ~2;
    }
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->slot == -1)
        return;
    n = *PPP_WORK(PppHitNode *, obj, e, 0);
    if (*w & 2) {
        for (; n; n = n->next) {
            if (n->flags.h[3] & 0x800) {
                inst = inl_spawn(D_00615E60, key->slot, obj);
                func_001a9098(inst + key->off + 0xA0, &n->joints[n->joint]);
            }
        }
    } else {
        for (; n; n = n->next) {
            if ((n->flags.x & 0x0840000000000000ULL) == 0x0800000000000000ULL) {
                inst = inl_spawn(D_00615E60, key->slot, obj);
                func_001a9098(inst + key->off + 0xA0, &n->joints[n->joint]);
            }
        }
    }
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

void func_0018d7d8(PppObject *owner, PppBorn2Key *key, s16 *pos) {
    PppVec4 v;
    u8 *inst = inl_spawn(D_00615E60, key->slot, owner);
    f32 *a, *b, *c;

    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    v[3] = 1.0f;
    a = (f32 *) (inst + key->off0 + 0xA0);
    c = (f32 *) (inst + key->off2 + 0xA0);
    b = (f32 *) (inst + key->off1 + 0xA0);
    func_002672f8(v, D_00615E68->m[0], v);
    func_001a9098((void *) a, v);
    func_00267530(v, v, D_00615E68->m[3]);
    func_002673b8(v, v);
    func_001a9098((void *) b, v);
    func_00267560(v, v, key->speed);
    func_001a9098((void *) c, v);
}


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

typedef struct {
    s32 frame;
    s32 id;       /* +0x4 */
    f32 da, db, dc; /* +0x8 */
    s32 u, v;     /* +0x14 */
    u8 page;      /* +0x1C */
    u8 mode;      /* +0x1D */
} PppTfdKey;

typedef struct {
    f32 a, b, c;
} PppTfd;

s32 sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
void func_001a9460(f32, s32, s32, void *);
void func_001aa6b0(void *, s32, s32, s32);
void func_001a9790(s32, void *, s32, s32, s32, s32, s32);

void pppKeMdlTfdDraw(PppObject *obj, PppTfdKey *key, PppEntry *e) {
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
        PppMdlRes *r = &D_00615E64->res[key->id];
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
    func_001a9790(key->id, PPP_WORK(void, obj, e, 0), n, 0, 0, 1, 0);
}

void pppKeMdlTfd2Draw(PppObject *obj, PppTfdKey *key, PppEntry *e) {
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
        PppMdlRes *r = &D_00615E64->res[key->id];
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
    func_001a9790(key->id, PPP_WORK(void, obj, e, 0), n, 0, 0, key->mode, 0);
}

typedef struct {
    s32 frame;
    s32 id;       /* +0x4 */
    u16 speed;    /* +0x8 */
    u8 padA[0x14];
    u8 local;     /* +0x1E */
} PppShpTailKey;

typedef struct {
    u8 count;     /* +0x0 */
    u8 idx;       /* +0x1 */
    u16 time;     /* +0x2 */
    u16 frame;    /* +0x4 */
    u16 prev;     /* +0x6 */
    u8 pad8[8];
    PppVec4 v[1]; /* +0x10 */
} PppShpTail;

void pppKeShpTailFrame(PppObject *obj, PppShpTailKey *key, PppEntry *e) {
    PppShpTail *w;
    PppAnim *a;
    PppAnimFrame *f;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w = PPP_WORK(PppShpTail, obj, e, 0);
    if (obj->frame == 0 && ((PppObjectB *) obj)->unk9D == 0) {
        PppVec4 v;
        f32 *p;
        s32 n;

        if (key->local) {
            func_002672f8(v, D_00615E70[0], D_00615E68->m[3]);
            v[3] = 1.0f;
        } else {
            func_002675a8(v, D_00615E68->m[3]);
            v[3] = 1.0f;
        }
        p = w->v[0];
        for (n = w->count; n > 0; n--) {
            func_002675a8(p, v);
            p += 4;
        }
    }
    if (w->idx == 0)
        w->idx = w->count;
    w->idx--;
    if (key->local) {
        func_002672f8(w->v[w->idx], D_00615E70[0], D_00615E68->m[3]);
        w->v[w->idx][3] = 1.0f;
    } else {
        func_001a9098(w->v[w->idx], D_00615E68->m[3]);
    }
    {
        PppAnimRef *r = &D_00615E64->anims[key->id];
        a = r->anim;
    }
    w->time += key->speed;
    f = &a->frames[w->frame];
    if (w->time >= f->len) {
        w->time -= f->len;
        w->frame++;
        if (w->frame >= a->n) {
            if (f->flags & 0x80) {
                w->frame = 0;
                w->time = 0;
            } else {
                w->time = 0;
                w->frame--;
            }
        }
    }
}

typedef struct {
    s32 frame;
    s32 id;       /* +0x4 */
    u16 speed;    /* +0x8 */
    u8 padA[0x19];
    u8 local2;    /* +0x23 */
} PppShpTail2Key;

void pppKeShpTail2Frame(PppObject *obj, PppShpTail2Key *key, PppEntry *e) {
    PppShpTail *w;
    PppAnim *a;
    PppAnimFrame *f;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w = PPP_WORK(PppShpTail, obj, e, 0);
    if (obj->frame == 0 && ((PppObjectB *) obj)->unk9D == 0) {
        PppVec4 v;
        f32 *p;
        s32 n;

        if (key->local2) {
            func_002672f8(v, D_00615E70[0], D_00615E68->m[3]);
            v[3] = 1.0f;
        } else {
            func_002675a8(v, D_00615E68->m[3]);
            v[3] = 1.0f;
        }
        p = w->v[0];
        for (n = w->count; n > 0; n--) {
            func_002675a8(p, v);
            p += 4;
        }
    }
    if (w->idx == 0)
        w->idx = w->count;
    w->idx--;
    if (key->local2) {
        func_002672f8(w->v[w->idx], D_00615E70[0], D_00615E68->m[3]);
        w->v[w->idx][3] = 1.0f;
    } else {
        func_001a9098(w->v[w->idx], D_00615E68->m[3]);
    }
    {
        PppAnimRef *r = &D_00615E64->anims[key->id];
        a = r->anim;
    }
    f = &a->frames[w->frame];
    w->prev = w->frame;
    w->time += key->speed;
    if (w->time >= f->len) {
        w->time -= f->len;
        w->frame++;
        if (w->frame >= a->n) {
            if (f->flags & 0x80) {
                w->frame = 0;
                w->time = 0;
            } else {
                w->time = 0;
                w->frame--;
            }
        }
    }
}

void func_00191fc8(PppObject *, PppLnsKey *, PppEntry *);
void func_001a60e8(PppLnsDraw *, s32);

void pppKeLnsArndDraw(PppObject *obj, PppLnsKey *key, PppEntry *e) {
    PppLnsDraw d;

    func_00191fc8(obj, key, e);
    d.col[0] = key->col[0] * D_00615E60->col[0];
    d.col[1] = key->col[1] * D_00615E60->col[1];
    d.col[2] = key->col[2] * D_00615E60->col[2];
    d.col[3] = key->col[3] * D_00615E60->col[3];
    d.p08 = D_00616040;
    d.p10 = D_003701F0;
    d.f0C = key->f0C;
    d.work = PPP_WORK(void, obj, e, 0);
    func_001a60e8(&d, 0);
}

void func_00192208(PppObject *, PppLnsClmKey *, PppEntry *);
void func_001a5ce8(PppLnsClmDraw *, s32);

void pppKeLnsClmDraw(PppObject *obj, PppLnsClmKey *key, PppEntry *e) {
    PppLnsClmDraw d;

    func_00192208(obj, key, e);
    d.f10 = key->h14;
    d.col[0] = key->col[0] * D_00615E60->col[0];
    d.col[1] = key->col[1] * D_00615E60->col[1];
    d.col[2] = key->col[2] * D_00615E60->col[2];
    d.col[3] = key->col[3] * D_00615E60->col[3];
    d.p08 = D_00616040;
    d.f0C = key->f0C;
    d.work = PPP_WORK(void, obj, e, 0);
    d.p14 = D_003701F0;
    func_001a5ce8(&d, 0);
}

void func_001924a8(PppObject *, PppLnsClmKey *, PppEntry *);
void func_001a62c0(PppLnsCrnDraw *, s32);

void pppKeLnsCrnDraw(PppObject *obj, PppLnsClmKey *key, PppEntry *e) {
    PppLnsCrnDraw d;

    func_001924a8(obj, key, e);
    d.col[0] = key->col[0] * D_00615E60->col[0];
    d.col[1] = key->col[1] * D_00615E60->col[1];
    d.col[2] = key->col[2] * D_00615E60->col[2];
    d.col[3] = key->col[3] * D_00615E60->col[3];
    d.p08 = D_00616040;
    d.h10 = key->h10;
    d.h12 = key->h12;
    d.f0C = key->f0C;
    d.work = PPP_WORK(void, obj, e, 0);
    d.p14 = D_003701F0;
    func_001a62c0(&d, 0);
}

void func_00192708(PppObject *, PppLnsClmKey *, PppEntry *);
void func_001a6550(PppLnsCrnDraw *, s32);

void pppKeLnsFlsDraw(PppObject *obj, PppLnsClmKey *key, PppEntry *e) {
    PppLnsCrnDraw d;

    func_00192708(obj, key, e);
    d.col[0] = key->col[0] * D_00615E60->col[0];
    d.col[1] = key->col[1] * D_00615E60->col[1];
    d.col[2] = key->col[2] * D_00615E60->col[2];
    d.col[3] = key->col[3] * D_00615E60->col[3];
    d.p08 = D_00616040;
    d.f0C = key->f0C;
    d.h10 = key->h10;
    d.h12 = key->h12;
    d.work = PPP_WORK(void, obj, e, 0);
    d.p14 = D_003701F0;
    func_001a6550(&d, 0);
}

typedef struct {
    u8 pad[0x10];
    PppVec4 v;     /* +0x10 */
    f32 f20;       /* +0x20 */
    u8 col[4];     /* +0x24 */
} PppLnsArndT;

void func_00192f78(PppLnsArndT *, s32, s32);

void pppKeLnsArndTDraw(PppObject *obj, PppLnsKey *key, PppEntry *e) {
    PppLnsArndT *w = PPP_WORK(PppLnsArndT, obj, e, 0);

    func_00191fc8(obj, key, e);
    if (key->frame == obj->frame)
        w->f20 = key->f0C;
    w->col[0] = key->col[0] * D_00615E60->col[0];
    w->col[1] = key->col[1] * D_00615E60->col[1];
    w->col[2] = key->col[2] * D_00615E60->col[2];
    w->col[3] = key->col[3] * D_00615E60->col[3];
    func_002675a8(w->v, (f32 *) D_003701F0);
    func_00192f78(w, 0, 0);
}

typedef struct {
    u8 pad[0x30];
    PppVec4 v;     /* +0x30 */
    f32 f40;       /* +0x40 */
    f32 f44;       /* +0x44 */
    u8 col[4];     /* +0x48 */
} PppLnsClmT;

void func_001931a8(PppLnsClmT *, s32, s32);

void pppKeLnsClmTDraw(PppObject *obj, PppLnsClmKey *key, PppEntry *e) {
    PppLnsClmT *w = PPP_WORK(PppLnsClmT, obj, e, 0);

    func_00192208(obj, key, e);
    if (key->frame == obj->frame) {
        w->f44 = key->f0C;
        w->f40 = key->h14;
    }
    w->col[0] = key->col[0] * D_00615E60->col[0];
    w->col[1] = key->col[1] * D_00615E60->col[1];
    w->col[2] = key->col[2] * D_00615E60->col[2];
    w->col[3] = key->col[3] * D_00615E60->col[3];
    func_002675a8(w->v, (f32 *) D_003701F0);
    func_001931a8(w, 0, 0);
}

typedef struct {
    u8 pad[0x10];
    PppVec4 v;     /* +0x10 */
    f32 f20;       /* +0x20 */
    u8 col[4];     /* +0x24 */
    f32 f28, f2C;  /* +0x28 */
} PppLnsCrnT;

void func_00193408(PppLnsCrnT *, s32, s32);

void pppKeLnsCrnTDraw(PppObject *obj, PppLnsClmKey *key, PppEntry *e) {
    PppLnsCrnT *w = PPP_WORK(PppLnsCrnT, obj, e, 0);

    func_001924a8(obj, key, e);
    if (key->frame == obj->frame) {
        w->f20 = key->f0C;
        w->f28 = key->h10;
        w->f2C = key->h12;
    }
    w->col[0] = key->col[0] * D_00615E60->col[0];
    w->col[1] = key->col[1] * D_00615E60->col[1];
    w->col[2] = key->col[2] * D_00615E60->col[2];
    w->col[3] = key->col[3] * D_00615E60->col[3];
    func_002675a8(w->v, (f32 *) D_003701F0);
    func_00193408(w, 0, 0);
}

typedef struct {
    u8 pad[0x10];
    PppVec4 v;     /* +0x10 */
    f32 f20;       /* +0x20 */
    u8 col[4];     /* +0x24 */
    f32 f28;       /* +0x28 */
    u16 h2C;       /* +0x2C */
} PppLnsFlsT;

void func_00192708(PppObject *, PppLnsClmKey *, PppEntry *);
void func_001936c0(PppLnsFlsT *, s32, s32);

void pppKeLnsFlsTDraw(PppObject *obj, PppLnsClmKey *key, PppEntry *e) {
    PppLnsFlsT *w = PPP_WORK(PppLnsFlsT, obj, e, 0);

    func_00192708(obj, key, e);
    if (key->frame == obj->frame) {
        w->f20 = key->f0C;
        w->f28 = key->h10;
        w->h2C = key->h12;
    }
    w->col[0] = key->col[0] * D_00615E60->col[0];
    w->col[1] = key->col[1] * D_00615E60->col[1];
    w->col[2] = key->col[2] * D_00615E60->col[2];
    w->col[3] = key->col[3] * D_00615E60->col[3];
    func_002675a8(w->v, (f32 *) D_003701F0);
    func_001936c0(w, 0, 0);
}

typedef struct {
    s32 frame;
    f32 rate;     /* +0x4 */
    s32 slot;     /* +0x8 */
    s32 off;      /* +0xC */
} PppHmgKey;

typedef struct {
    f32 rate;
    f32 *target;  /* +0x4 */
} PppHmg;

typedef union {
    PppVec4 f;
    u64 d[2];
} PppV4U;

void func_00267518(PppVec4, PppVec4, PppVec4);
void func_002674f0(PppVec4, PppVec4, PppVec4, f32);
s32 func_001a8f30(void);

void pppKeHmgEffFrame(PppObject *obj, PppHmgKey *key, PppEntry *e) {
    PppVec4 a;
    PppV4U c;
    PppVec4 b;
    PppHmg *w = PPP_WORK(PppHmg, obj, e, 2);
    f32 *p, *q;
    f32 len;

    if (obj->frame == key->frame) {
        w->rate = key->rate;
        if (key->slot != -1)
            p = (f32 *) (D_00615E60->slots[key->slot].inst + key->off + 0xA0);
        else
            p = &D_00575A00;
        w->target = p;
        if (obj->frame == 0 && ((PppObjectB *) obj)->unk9D == 0)
            return;
    }
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (w->target == &D_00575A00)
        return;
    q = PPP_WORK(f32, obj, e, 1);
    func_00267530(a, w->target, PPP_WORK(f32, obj, e, 0));
    func_002673b8(a, a);
    func_002675a8(b, q);
    len = func_001a9350(b);
    func_002673b8(b, b);
    func_00267518(c.f, b, a);
    if (c.d[0] == 0 && c.d[1] == 0)
        a[func_001a8f30() % 3] += 0.05f;
    func_002674f0(a, a, b, w->rate);
    func_002673b8(a, a);
    func_00267560(a, a, len);
    func_001a9098(q, a);
}

typedef struct {
    s32 frame;
    s32 slot;     /* +0x4 */
    s32 off;      /* +0x8 */
} PppGrvKey;

typedef struct {
    f32 range;    /* +0x0 */
    f32 force;    /* +0x4 */
    f32 *pos;     /* +0x8 */
} PppGrvSrc;

void pppKeGrvEffFrame(PppObject *obj, PppGrvKey *key, PppEntry *e) {
    PppVec4 a;
    PppGrvSrc **w = PPP_WORK(PppGrvSrc *, obj, e, 2);
    PppGrvSrc *t;
    f32 *q;
    f32 len;

    if (obj->frame == key->frame) {
        PppGrvSrc *p;

        if (key->slot != -1)
            p = (PppGrvSrc *) (D_00615E60->slots[key->slot].inst + key->off + 0xA0);
        else
            p = (PppGrvSrc *) &D_00575A00;
        *w = p;
        if (obj->frame == 0 && ((PppObjectB *) obj)->unk9D == 0)
            return;
    }
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    t = *w;
    if (t == (PppGrvSrc *) &D_00575A00)
        return;
    q = PPP_WORK(f32, obj, e, 1);
    func_00267530(a, t->pos, PPP_WORK(f32, obj, e, 0));
    len = func_001a9350(a);
    func_002673b8(a, a);
    if (len < t->range) {
        func_00267560(a, a, (1.0f - len / t->range) * t->force);
        func_001a9110(q, q, a);
    }
}

/* needs make: uses rodata */

typedef struct {
    s32 frame;
    s32 unk4, unk8;
    s32 slot;     /* +0xC */
    s32 off0;     /* +0x10 */
    s32 unk14;
    s32 off1;     /* +0x18 */
} PppBorn3Key;



void func_0018e0b0(PppObject *owner, PppBorn3Key *key, s16 *pos) {
    PppVec4 v;
    f32 ang;
    u8 *inst = inl_spawn(D_00615E60, key->slot, owner);
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
