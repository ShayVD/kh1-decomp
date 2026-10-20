#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"

void *memset(void *, s32, u32);
void *func_0017f958(void *, s32);
s32 func_0019f1a8(void *, void *);
void func_001a0628(void *, void *, void *);
void func_002673b8(void *, void *);
typedef struct { u8 pad0[2]; s16 dur; s8 flag; u8 pad5[3]; } AnFrm;
typedef struct { u8 pad0[6]; s16 n; u8 pad8[8]; AnFrm fr[1]; } Anim;
typedef struct { Anim *anim; s32 pad; } AnEnt;
typedef f32 Mtx4[4][4];
typedef struct { u32 flags; u8 pad04[0x12]; u16 h16; } DMdl;
typedef struct { u8 pad[0x14]; void *x14; u8 pad18[4]; DMdl *mdl; s32 x20; } Ent24;
typedef struct { u8 pad[0x10]; Mtx4 m; Mtx4 m2; u8 *x90; s32 x94; } PppMtxOwner;
extern PppMtxOwner *D_00615E68;
typedef struct { s16 a; s16 n; u16 *list; } Grp;
typedef struct { u8 pad0[0x10]; Ent24 *x10; AnEnt *anims; Grp *grps; } PppRes;
extern PppRes *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
typedef struct { f32 x, y, z, w; } FV4;
extern FV4 D_003701D0;

typedef struct {
    f32 x, y, z, w;
    void *p10;
    void *p14;
    void *p18;
    s32 n;
} MbmW;

typedef struct {
    u8 pad0[0x1c];
    u16 n;
    u8 pad1e[0xd0 - 0x1e];
    f32 x, y, z;
    u8 paddc[0x101 - 0xdc];
    u8 b101;
    u8 pad102[4];
    u8 b106;
} MbmK;

void pppRyjMegaBirthModelFrame(void *obj, MbmK *k, PppEntry *e) {
    MbmW *w = (MbmW *)((u8 *)obj + e->offsets[2] + 0xA0);
    void *w2 = (u8 *)obj + e->offsets[1] + 0xA0;

    if (w->p10 == NULL) {
        w->n = k->n;
        w->p10 = func_0017f958(D_00615E64, w->n * 0xB0);
        if (w->p10 != NULL)
            memset(w->p10, 0, w->n * 0xB0);
        if (k->b106) {
            w->p14 = func_0017f958(D_00615E64, w->n << 6);
            if (w->p14 != NULL)
                memset(w->p14, 0, w->n << 6);
        }
        if (k->b101) {
            w->p18 = func_0017f958(D_00615E64, w->n << 5);
            if (w->p18 != NULL)
                memset(w->p18, 0, w->n << 5);
        }
        w->x = k->x;
        w->y = k->y;
        w->z = k->z;
        w->w = 0;
        func_002673b8(w, w);
    }
    if (func_0019f1a8(w, k))
        func_001a0628(w, k, w2);
}


typedef struct { u8 pad[0x31]; u8 a, b, c; } UvSrc;

void func_001a1158(UvSrc *s, FV4 *v) {
    f32 u0, u1, a, h, f;
    switch (s->a) {
    case 1: a = 0.49f; break;
    case 2: a = 0.24f; break;
    case 0: default: a = 0.99f; break;
    }
    switch (s->b) {
    case 1: h = 0.49f; break;
    case 2: h = 0.24f; break;
    case 0: default: h = 0.99f; break;
    }
    switch (s->c) {
    case 1: f = 0.25f; break;
    case 2: f = 0.5f; break;
    case 3: f = 0.75f; break;
    case 0: default: f = 0.0f; break;
    }
    u1 = f + a;
    u0 = f + 0.01f;
    v[7].x = u0;
    v[6].x = u0;
    v[1].x = u0;
    v[5].x = u1;
    v[4].x = u1;
    v[3].x = u1;
    v[7].y = h;
    v[5].y = h;
    v[3].y = h;
    v[6].y = 0.01f;
    v[4].y = 0.01f;
    v[2].y = 0.01f;
    v[7].z = 1.0f;
    v[6].z = 1.0f;
    v[5].z = 1.0f;
    v[4].z = 1.0f;
    v[3].z = 1.0f;
    v[2].z = 1.0f;
    v[1].z = 1.0f;
    v[1].y = h;
    v[0].z = 1.0f;
    v[2].x = u1;
    v[0].y = 0.01f;
    v[0].x = u0;
}

typedef struct {
    u8 pad0[0xc];
    f32 intensity;
    FV4 pos;
    FV4 dir;
    FV4 col;
} Light;
typedef struct {
    u8 pad0[4];
    f32 x, y, z;
    f32 f10;
    u8 type, b15, b16, b17;
} LtKey;
typedef struct { u8 pad[8]; u8 r, g, b, a; } LtCol;
Light *func_001226f0(s32, s32, s32);
void func_00267560(void *, void *, f32);

void pppRyjLightFrame(void *obj, LtKey *k, PppEntry *e) {
    Light **w = (Light **)((u8 *)obj + e->offsets[2] + 0xA0);
    Light *l = *w;
    FV4 *p;
    LtCol *c;
    s32 fl = 0;
    if (k->b15) fl |= 1;
    if (k->b16) fl |= 2;
    if (k->b17) fl |= 4;
    if (l == NULL) {
        *w = func_001226f0(k->type, fl, 0);
        if (*w == NULL)
            return;
        l = *w;
    }
    p = (FV4 *)((u8 *)obj + e->offsets[1] + 0xA0);
    c = (LtCol *)((u8 *)obj + e->offsets[0] + 0xA0);
    l->pos.x = p->x + D_003701D0.x;
    l->pos.y = p->y + D_003701D0.y;
    l->pos.z = p->z + D_003701D0.z;
    l->pos.w = 1.0f;
    l->dir.x = k->x;
    l->dir.y = k->y;
    l->dir.z = k->z;
    l->dir.w = 1.0f;
    l->col.x = c->r;
    l->col.y = c->g;
    l->col.z = c->b;
    l->col.w = c->a;
    func_00267560(&l->col, &l->col, 0.00392156851f);
    l->intensity = k->f10;
}

extern FV4 D_00615F70; /* src/data/bss_0061.c: f32 D_00615F70[4] */
void func_00267530(FV4 *, FV4 *, FV4 *);

typedef struct { u8 pad0[0x20]; u16 t; u16 idx; u16 prev; u16 alive; u8 pad28[0x38]; } MbPart;
typedef struct { u8 pad[0x20]; } MbSub;
typedef struct { MbPart *parts; MbSub *subs; s32 n; f32 alpha; u16 timer; u8 active; } MbWork;
typedef struct { u8 pad0[0xe]; u16 n; u8 pad10[0xac - 0x10]; f32 dist; f32 fade; u8 test; u8 padb5; u8 sub; } MbfKey;

s32 func_001a2218(MbWork *, MbfKey *);
void func_001a2d40(MbWork *, MbfKey *, void *);

static inline f32 vlen3_w65(FV4 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vmul.xyz $vf10xyz, $vf10xyz, $vf10xyz\n"
        "vaddx.y $vf10y, $vf10y, $vf10x\n"
        "vaddy.z $vf10z, $vf10z, $vf10y\n"
        "vsqrt Q, $vf10z\n"
        "vwaitq\n"
        "vaddq.x $vf10x, $vf0x, Q\n"
        "qmfc2 $2, $vf10\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(v) : "$2", "memory");
    return r;
}

void pppRyjMegaBirthFilterFrame(void *obj, MbfKey *k, PppEntry *e) {
    MbWork *w = (MbWork *)((u8 *)obj + e->offsets[2] + 0xA0);
    void *w2 = (u8 *)obj + e->offsets[1] + 0xA0;
    FV4 d;
    f32 len, r;

    if (w->parts == NULL) {
        w->n = k->n;
        w->parts = func_0017f958(D_00615E64, w->n * 0x60);
        if (w->parts != NULL)
            memset(w->parts, 0, w->n * 0x60);
        if (k->sub) {
            w->subs = func_0017f958(D_00615E64, w->n << 5);
            if (w->subs != NULL)
                memset(w->subs, 0, w->n << 5);
        }
    }
    if (!func_001a2218(w, k))
        return;
    if (k->test) {
        func_00267530(&d, &D_00615F70, &D_003701D0);
        len = vlen3_w65(&d);
        if (k->dist < len) {
            w->active = 0;
        } else {
            w->active = 1;
            r = k->dist - len;
            if (r < k->fade)
                w->alpha = r / k->fade;
            else
                w->alpha = 1.0f;
        }
    }
    if (w->active)
        func_001a2d40(w, k, w2);
}

typedef struct { MbPart *parts; MbSub *subs; s32 n; f32 alpha; u16 timer; u8 active; } MbmWork;
typedef struct { u8 pad0[0xa]; u16 n; u8 padc[0xe8 - 0xc]; f32 dist; f32 fade; u8 test; u8 padf1; u8 sub; } MbmfKey;
s32 func_001a36f0(MbmWork *, MbmfKey *);
void func_001a47b0(MbmWork *, MbmfKey *, void *);

void pppRyjMegaBirthModelFilterFrame(void *obj, MbmfKey *k, PppEntry *e) {
    MbmWork *w = (MbmWork *)((u8 *)obj + e->offsets[2] + 0xA0);
    void *w2 = (u8 *)obj + e->offsets[1] + 0xA0;
    FV4 d;
    f32 len, r;

    if (w->parts == NULL) {
        w->n = k->n;
        w->parts = func_0017f958(D_00615E64, w->n * 0xA0);
        if (w->parts != NULL)
            memset(w->parts, 0, w->n * 0xA0);
        if (k->sub) {
            w->subs = func_0017f958(D_00615E64, w->n << 5);
            if (w->subs != NULL)
                memset(w->subs, 0, w->n << 5);
        }
    }
    if (!func_001a36f0(w, k))
        return;
    if (k->test) {
        func_00267530(&d, &D_00615F70, &D_003701D0);
        len = vlen3_w65(&d);
        if (k->dist < len) {
            w->active = 0;
        } else {
            w->active = 1;
            r = k->dist - len;
            if (r < k->fade)
                w->alpha = r / k->fade;
            else
                w->alpha = 1.0f;
        }
    }
    if (w->active)
        func_001a47b0(w, k, w2);
}

void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_002678b8(f32 (*)[4], void *, f32 *);

void func_002675a8(f32 *, void *);
void func_002672f8(f32 *, void *, f32 *);
extern u8 D_006161C0[];
extern u8 D_00615EB0[];
extern f32 D_00616040[4][4]; /* src/data/bss_0061.c: u8 D_00616040[0x40] */

typedef struct { u8 pad[0xe0]; f32 mul; f32 add; } RkKey;
typedef struct {
    u8 pad0[0x28];
    union { u64 d; s32 i[2]; } r01;
    s32 r2;
    u8 pad34[0x54 - 0x34];
    f32 scale[3];
} RkObj;

f32 func_001a4a98(void *a0, f32 (*m)[4], RkKey *k, void *a3, RkObj *o) {
    Mtx4 rm;
    f32 rot[3];
    f32 z;
    s32 i;
    sceVu0UnitMatrix(m);
    if (o->r01.d || o->r2) {
        for (i = 0; i < 3; i++)
            rot[i] = (f32)o->r01.i[i] * 3.1415926f * 3.0517578125e-05f;
        func_002678b8(rm, D_006161C0, rot);
        sceVu0MulMatrix(m, m, rm);
    }
    for (i = 0; i < 3; i++)
        func_00267560(m[i], m[i], o->scale[i]);
    func_002675a8(m[3], o);
    func_002672f8(m[3], D_00615EB0, m[3]);
    m[3][1] *= k->mul;
    z = m[3][2];
    m[3][1] += k->add;
    sceVu0MulMatrix(m, D_00616040, m);
    return z;
}

s32 func_001a8f30(void);

void func_001a5520(void *obj, void *key, void (*fn)(void *, void *, void *), u16 *pidx, s16 id, u8 rnd, u8 cnt) {
    Grp *g = &D_00615E64->grps[id];
    u8 *base = D_00615E68->x90;
    s32 idx;

    if (base == NULL)
        base = D_00615E64->x10[g->a].x14;
    if (rnd)
        idx = func_001a8f30() % g->n;
    else
        idx = *pidx;
    for (; cnt != 0; cnt--) {
        fn(obj, key, base + g->list[idx++] * 6);
        if (rnd)
            idx = func_001a8f30() % g->n;
        else if (idx >= g->n)
            idx = 0;
    }
    *pidx = idx;
}

void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
extern Mtx4 D_00615FC0;
extern u8 D_00575A00[];

typedef union { u32 w; struct { u8 r, g, b, a; } c; } Rgba;
typedef struct {
    Mtx4 m;
    u8 pad40[0x3c];
    f32 alpha;
    f32 pos[3];
    u8 pad8c[3];
    u8 useMtx;
} DmObj;
typedef struct { DmObj *obj; void *mdl; u8 data[1]; } DmSrc;
typedef struct { DmSrc *src; Rgba col; f32 (*mtx)[4]; f32 scale; f32 *scl; } DmArg;
typedef struct {
    void *mdl;
    void *data;
    u8 pad8[0xa];
    s16 id;
    Rgba col;
    s32 x18, x1c;
    f32 (*mtx)[4];
    u8 pad24[8];
    s32 x2c;
    u8 pad30[0x10];
} DmCtx;
void func_001a56a0(DmCtx *);
void func_001a5740(DmCtx *);

void func_001a60e8(DmArg *a, s32 id) {
    Mtx4 m;
    DmCtx c;
    DmSrc *s = a->src;
    DmObj *o = s->obj;

    if (o == (DmObj *)D_00575A00)
        return;
    if (s->mdl == NULL)
        return;
    if (o->alpha == 0.0f)
        return;
    if (o->useMtx) {
        sceVu0CopyMatrix(m, o->m);
    } else {
        sceVu0UnitMatrix(m);
        m[3][0] = D_00615FC0[3][0] + o->pos[0];
        m[3][1] = D_00615FC0[3][1] + o->pos[1];
        m[3][2] = D_00615FC0[3][2] + o->pos[2];
    }
    m[0][0] *= a->scale;
    m[1][1] *= a->scale;
    func_00267560(m[0], m[0], a->scl[0]);
    func_00267560(m[1], m[1], a->scl[1]);
    func_00267560(m[2], m[2], a->scl[2]);
    sceVu0MulMatrix(m, a->mtx, m);
    c.col = a->col;
    c.col.c.a = c.col.c.a * o->alpha;
    c.mdl = s->mdl;
    c.data = s->data;
    func_001a56a0(&c);
    c.id = id;
    c.mtx = m;
    c.x2c = 0;
    c.x18 = 0;
    c.x1c = 0;
    func_001a5740(&c);
}

typedef struct { DmSrc *src; Rgba col; f32 (*mtx)[4]; f32 scale; u16 w, h; f32 *scl; } DmArg2;
typedef struct {
    void *mdl;
    void *data;
    u8 pad8[0xa];
    s16 id;
    Rgba col;
    s32 x18;
    s16 x1c, x1e;
    f32 (*mtx)[4];
    u8 pad24[8];
    s32 x2c;
    u8 pad30[0x10];
} DmCtx2;
typedef struct {
    u8 pad0[0x30];
    f32 r3[4], r0[4], r1[4], r2[4];
    u8 pad70[0xc];
    f32 alpha;
    f32 pos[3];
    u8 pad8c[3];
    u8 useMtx;
    u8 pad90[0x14];
    f32 size;
} DmObj2;

void func_001a62c0(DmArg2 *a, s32 id) {
    Mtx4 m;
    DmCtx2 c;
    DmSrc *s = a->src;
    DmObj2 *o = (DmObj2 *)s->obj;
    f32 f, t;

    if (o == (DmObj2 *)D_00575A00)
        return;
    if (s->mdl == NULL)
        return;
    if (o->alpha == 0.0f)
        return;
    func_002675a8(m[0], o->r0);
    func_002675a8(m[1], o->r1);
    func_002675a8(m[2], o->r2);
    func_002675a8(m[3], o->r3);
    f = a->scale * o->size / (f32)a->w;
    func_00267560(m[0], m[0], -f);
    func_00267560(m[1], m[1], f);
    if (!o->useMtx) {
        m[3][0] = D_00615FC0[3][0] + o->pos[0];
        m[3][1] = D_00615FC0[3][1] + o->pos[1];
        m[3][2] = D_00615FC0[3][2] + o->pos[2];
    }
    func_00267560(m[0], m[0], a->scl[0]);
    func_00267560(m[1], m[1], a->scl[1]);
    func_00267560(m[2], m[2], a->scl[2]);
    sceVu0MulMatrix(m, a->mtx, m);
    c.col = a->col;
    f = o->size / (f32)a->h;
    t = 1.0f < f ? 1.0f : f;
    c.col.c.a = c.col.c.a * o->alpha * t;
    c.mdl = s->mdl;
    c.data = s->data;
    func_001a56a0((DmCtx *)&c);
    c.id = id;
    c.mtx = m;
    c.x2c = 0;
    c.x18 = 0;
    c.x1c = 0;
    c.x1e = 0;
    func_001a5740((DmCtx *)&c);
}

typedef struct { DmSrc *src; Rgba col; f32 (*mtx)[4]; f32 scale; u16 w; u8 mx, my; f32 *scl; } DmArg3;

void func_001a6550(DmArg3 *a, s32 id) {
    Mtx4 m;
    DmCtx2 c;
    DmSrc *s = a->src;
    DmObj2 *o = (DmObj2 *)s->obj;
    f32 f, r, sc;

    if (o == (DmObj2 *)D_00575A00)
        return;
    if (s->mdl == NULL)
        return;
    if (o->alpha == 0.0f)
        return;
    r = 0.0f;
    f = o->size / (f32)a->w;
    if (!(1.0f < f))
        r = 1.0f - f;
    if (o->useMtx) {
        sceVu0CopyMatrix(m, (f32 (*)[4])o);
    } else {
        sceVu0UnitMatrix(m);
        m[3][0] = D_00615FC0[3][0] + o->pos[0];
        m[3][1] = D_00615FC0[3][1] + o->pos[1];
        m[3][2] = D_00615FC0[3][2] + o->pos[2];
    }
    sc = a->scale;
    m[0][0] = sc;
    switch (a->mx) {
    case 1:
        m[0][0] = sc * r;
        break;
    case 2:
        m[0][0] = f * sc + sc;
        break;
    }
    m[1][1] = sc;
    switch (a->my) {
    case 1:
        m[1][1] = sc * r;
        break;
    case 2:
        m[1][1] = f * sc + sc;
        break;
    }
    func_00267560(m[0], m[0], a->scl[0]);
    func_00267560(m[1], m[1], a->scl[1]);
    sceVu0MulMatrix(m, a->mtx, m);
    c.col = a->col;
    c.col.c.a = c.col.c.a * o->alpha * r;
    c.mdl = s->mdl;
    c.data = s->data;
    func_001a56a0((DmCtx *)&c);
    c.id = id;
    c.mtx = m;
    c.x2c = 0;
    c.x18 = 0;
    c.x1c = 0;
    c.x1e = 0;
    func_001a5740((DmCtx *)&c);
}

typedef struct { u8 a[0x20]; u8 b[0x10]; } NdSlot;
typedef struct Nd {
    struct Nd *next;
    struct Nd **pprev;
    u8 pad8[0x2c];
    u16 idx;
    u8 pad36[8];
    u16 fl;
    NdSlot sl[1];
} Nd;
typedef struct { Nd *first; u8 fl; } NdHead;
typedef struct { u8 pad[4]; Nd *free; } NdPool;
typedef struct { NdHead *h; void *x4; void *x8; NdPool *pool; void *x10; void *x14; } NdArg;
typedef struct { Mtx4 m; Nd *n; void *x4; NdPool *pool; void *x8; } NdCtx;
void func_001a9098(void *, void *);
void func_001a7c50(NdCtx *);
void func_001a8828(Nd *);

void func_001a8ae8(NdArg *a) {
    NdHead *h = a->h;
    NdCtx c;
    Nd *n, *cur;
    s32 fl = 0;

    if (h->fl & 2) {
        fl = 0x20;
        h->fl &= ~2;
    }
    sceVu0UnitMatrix(c.m);
    c.x4 = a->x4;
    c.pool = a->pool;
    c.x8 = a->x8;
    n = h->first;
    while (n) {
        if (n->fl & 0x200) {
            func_001a9098(n->sl[n->idx].a, a->x10);
            func_001a9098(n->sl[n->idx].b, a->x14);
        }
        if (n->fl & 0x100)
            n->fl |= fl;
        c.n = n;
        func_001a7c50(&c);
        if (n->fl & 0x10) {
            cur = n;
            n = n->next;
            if (cur->next)
                cur->next->pprev = cur->pprev;
            *cur->pprev = cur->next;
            func_001a8828(cur);
            cur->next = a->pool->free;
            a->pool->free = cur;
        } else {
            n = n->next;
        }
    }
}

double atan(double);

s32 func_001a8d88(f32 *v, f32 *out) {
    f32 x = v[0];
    f32 y = v[1];
    f32 r = x * y;

    if (0.0f < r) {
        r = 0.0f;
        if (!(0.0f < x))
            r = -3.1415926f;
        r = r + atan(y / x);
    } else if (r < 0.0f) {
        r = 1.5707963f;
        if (!(0.0f < y))
            r = -1.5707963f;
        r = r - atan(x / y);
    } else if (x != 0.0f) {
        r = 0.0f < x ? 0.0f : 3.1415926f;
    } else {
        if (y == 0.0f)
            return 0;
        r = !(0.0f < y) ? -1.5707963f : 1.5707963f;
    }
    *out = r;
    return 1;
}

typedef struct {
    s32 flags;
    void *p04;
    u16 h08;
    u8 b0A;
    s16 h0C;
    s16 h0E;
    s32 w10;
    s32 w14;
    u8 r, g, b, a;
    s32 w1C;
    void *p20;
    void *p24;
    void *p28;
    void *p2C;
    void *p30;
    s32 w34;
    u8 *w38;
    s32 w3C;
    s32 w40;
    void *p44;
    u8 pad48[0x18];
} DParam;
extern u8 D_00616240[];
extern u8 D_00616140[];
extern u8 D_00616100[];
extern s32 D_00616224;
s32 func_001aaf88(DMdl *, DParam *, s32);

void func_001a9790(s32 id, u16 *col, s32 h, s32 x, s32 y, u8 fl, void *p) {
    Mtx4 m;
    DParam c;
    Ent24 *s;
    DMdl *md;

    if (id == 0xffff)
        return;
    s = &D_00615E64->x10[id];
    md = s->mdl;
    c.flags = 0;
    if (fl & 2) {
        c.flags = 4;
        if (!(md->flags & 1))
            c.flags |= 8;
    } else {
        if (fl & 1)
            c.flags = 128;
        if (!(md->flags & 1))
            c.flags |= 8;
    }
    if (!(md->flags & 2))
        c.flags |= 16;
    if (fl & 4)
        c.flags |= 0x200;
    if (fl & 8)
        c.flags |= 0x100;
    if (fl & 0x10) {
        c.flags |= 0x2000;
        c.p30 = m;
        sceVu0MulMatrix(m, D_00615FC0, D_00615E68->m);
    }
    c.p44 = (fl & 0x20) ? p : 0;
    c.h08 = md->h16;
    c.w1C = 0;
    c.w38 = D_00615E68->x90;
    c.w3C = D_00615E68->x94;
    c.h0C = 0;
    c.p04 = D_00616240;
    c.h0E = h;
    c.w10 = x << 16;
    c.w14 = y << 16;
    c.w40 = 0;
    c.b0A = 0;
    c.r = col[0] >> 7;
    c.g = col[1] >> 7;
    c.b = col[2] >> 7;
    c.a = col[3] >> 7;
    c.p20 = D_00615E68->m2;
    c.p24 = D_00616140;
    c.p28 = D_00616100;
    c.p2C = D_00615E68->m;
    c.w34 = D_00616224;
    D_00616224 = func_001aaf88(md, &c, s->x20);
}
#include "data/bss_0057_mixed.h"
