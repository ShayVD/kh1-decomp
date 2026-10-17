#include "common.h"
#include "ppp.h"

void *memset(void *, s32, u32);
void *func_0017f958(void *, s32);
s32 func_0019f1a8(void *, void *);
void func_001a0628(void *, void *, void *);
void func_002673b8(void *, void *);
typedef struct { u8 pad0[2]; s16 dur; s8 flag; u8 pad5[3]; } AnFrm;
typedef struct { u8 pad0[6]; s16 n; u8 pad8[8]; AnFrm fr[1]; } Anim;
typedef struct { Anim *anim; s32 pad; } AnEnt;
typedef struct { u8 pad0[0x14]; AnEnt *anims; } PppRes;
extern PppRes *D_00615E64;
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
void func_00267560(FV4 *, FV4 *, f32);

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

extern FV4 D_00615F70;
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
