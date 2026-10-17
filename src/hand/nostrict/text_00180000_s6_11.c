/* ppp draw/frame callbacks around 0x197000-0x1a1000 (worker b08). This
 * region was built without strict aliasing. */
#include "common.h"
#include "ppp.h"

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
extern PppSystem *D_00615E60;

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame;
    u8 pad10[0x8D];
    u8 unk9D;
} PppObject;

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

extern DSys *D_00615E64;
extern s32 D_00616224;
s32 sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
void func_001a9460(f32, s32, s32, void *);
void func_001aa6b0(void *, s32, s32, s32);
void func_001a9790(s32, void *, s32, s32, s32, s32, void *);
typedef f32 PppVec4[4] __attribute__((aligned(16)));
typedef struct {
    u8 pad[0x10];
    PppMtx m;
    PppMtx m2;
    s32 unk90;
    s32 unk94;
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;
extern PppMtx D_00615E70;
void func_002672f8(f32 *, PppMtx, f32 *);
void func_002675a8(f32 *, f32 *);
void func_001a9098(void *, void *);
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
typedef struct {
    u8 pad[8];
    u8 r, g, b, a;
} DColWork;
extern u8 D_00616240[];
extern u8 D_00616140[];
extern u8 D_00616100[];
extern PppMtx D_00615FC0;
s32 func_001aaf88(DMdl *, DParam *, s32);
void sceVu0MulMatrix(PppMtx, PppMtx, PppMtx);
void sceVu0UnitMatrix(PppMtx);
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


typedef struct { u8 r, g, b, a; } Col;
typedef struct {
    s32 frame;
    s32 id;
    u8 pad8[4];
    u8 bC, bD;
} ShpKey;

typedef struct {
    u8 pad[4];
    u16 idx;
} ShpW0;

typedef struct {
    u8 pad[8];
    Col col;
} ShpW1;

void pppDrawShapeDraw(void *obj, ShpKey *key, PppEntry *e) {
    DShpParam p;
    ShpW0 *w = PPP_WORK(ShpW0, obj, e, 0);
    ShpW1 *c = PPP_WORK(ShpW1, obj, e, 1);
    PppShapeEnt *s;
    PppShape *sh;

    if (key->id == 0xFFFF)
        return;
    s = &((DSysS *) D_00615E64)->shapes[key->id];
    p.d8 = 0;
    p.p10 = D_00615E68->m2;
    p.b18 = 0;
    p.p1C = 0;
    if (!key->bC)
        p.flags = 128;
    else
        p.flags = 0;
    if (key->bD == 1)
        p.flags |= 0x10;
    {
        s32 *g = &D_00616224;
        u8 *src;
        p.r = c->col.r;
        p.g = c->col.g;
        p.b = c->col.b;
        p.a = c->col.a;
        { PppShapeFrame *f; sh = s->shape; f = &sh->f[w->idx]; src = (u8 *) sh + f->off; }
        p.w14 = *g;
        *g = func_001b8198(src, &p, s->unk4);
    }
}

typedef struct {
    u8 pad0[0xC];
    f32 fC;
    u8 pad10[0x14];
    f32 f24;
    u8 pad28[4];
    f32 f2C;
} ThSub;

typedef struct {
    u8 pad0[0x10];
    ThSub s;          /* +0x10 */
    u8 pad[0x6C - 0x10 - sizeof(ThSub)];
    s32 f6C;
    u64 c[4];         /* +0x70 */
} ThWork;

typedef struct {
    u8 pad[0x54];
    u8 mode;
} ThKey;


void func_001a8d78(ThWork *);

typedef struct {
    s32 x0;
    f32 x4, x8;
    f32 xC, x10, x14, x18;
} B030Out;
typedef struct {
    u8 pad[8];
    f32 x8;
    u8 padC[8];
    f32 x14;
} B030In;

void func_0018b030(B030In *a, B030Out *b) {
    f32 z;

    b->x4 = a->x8;
    b->x10 = a->x14;
    z = 0.0f;
    b->x18 = z;
    b->x14 = z;
    b->xC = z;
    b->x8 = z;
    b->x0 = (s32)a;
}

void func_0018b470(B030In *a, B030Out *b) {
    f32 z;

    b->x4 = a->x8;
    b->x10 = a->x14;
    z = 0.0f;
    b->x18 = z;
    b->x14 = z;
    b->xC = z;
    b->x8 = z;
    b->x0 = (s32)a;
}

void pppKeThCon(void *obj, PppEntry *e) {
    ThWork *w = PPP_WORK(ThWork, obj, e, 0);
    ThSub *s = &w->s;

    func_001a8d78(w);
    w->c[0] = 0;
    w->c[1] = 0;
    w->c[2] = 0;
    w->c[3] = 0;
    w->f6C = 0;
    s->fC = 0;
    s->f24 = 0;
    s->f2C = 0;
}

void pppKeThReset(void *obj, PppEntry *e) {
    ThWork *w = PPP_WORK(ThWork, obj, e, 0);
    ThSub *s = &w->s;

    w->c[0] = 0;
    w->c[1] = 0;
    w->c[2] = 0;
    w->c[3] = 0;
    w->f6C = 0;
    s->fC = 0;
    s->f24 = 0;
    s->f2C = 0;
}

typedef struct {
    u8 pad[0x30];
    u8 v30[0x10];
    f32 f40, f44;
    s32 i48;
} A8Obj;
typedef struct {
    A8Obj *o;
    s32 i;
    void *m;
    f32 f44;
    f32 f40;
    void *v;
} A8Arg;
extern u8 D_00616040[];
void func_001a5ce8(A8Arg *, s32);

void func_001931a8(A8Obj *o) {
    A8Arg a;
    a.o = o;
    a.f40 = o->f40;
    a.i = o->i48;
    a.f44 = o->f44;
    a.m = D_00616040;
    a.v = o->v30;
    func_001a5ce8(&a, 0);
}

typedef struct {
    u8 n;          /* +0x0 */
    u8 idx;        /* +0x1 */
    u16 t;         /* +0x2 */
    u16 fr;        /* +0x4 */
    u16 prev;      /* +0x6 */
    u8 pad8[8];
    PppVec4 v[1];  /* +0x10 */
} TailXWork;

typedef struct {
    s32 frame;
    s32 id;        /* +0x4 */
    u16 speed;     /* +0x8 */
    u8 padA[0x17];
    u8 local;      /* +0x21 */
} TailXKey;

void pppKeShpTailXFrame(PppObject *obj, TailXKey *key, PppEntry *e) {
    TailXWork *w;
    PppShape *sh;
    PppShapeFrame *f;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w = PPP_WORK(TailXWork, obj, e, 0);
    if (obj->frame == 0 && obj->unk9D == 0) {
        PppVec4 v;
        f32 *p;
        s32 n;

        if (key->local) {
            func_002672f8(v, D_00615E70, D_00615E68->m[3]);
            v[3] = 1.0f;
        } else {
            func_002675a8(v, D_00615E68->m[3]);
            v[3] = 1.0f;
        }
        p = w->v[0];
        for (n = w->n; n > 0; n--) {
            func_002675a8(p, v);
            p += 4;
        }
    }
    if (w->idx == 0)
        w->idx = w->n;
    w->idx--;
    if (key->local) {
        func_002672f8(w->v[w->idx], D_00615E70, D_00615E68->m[3]);
        w->v[w->idx][3] = 1.0f;
    } else {
        func_001a9098(w->v[w->idx], D_00615E68->m[3]);
    }
    {
        u16 fr;

        { PppShapeEnt *se = &((DSysS *) D_00615E64)->shapes[key->id]; sh = se->shape; }

        fr = w->fr;
        w->prev = fr;
        f = &sh->f[fr];
        w->t += key->speed;
        if (w->t < f->dur)
            return;
        w->t -= f->dur;
        w->fr = fr + 1;
        if (w->fr < sh->n)
            return;
        {
            s32 fl = f->flags;
            w->t = 0;
            if (fl & 0x80)
                w->fr = 0;
            else
                w->fr--;
        }
    }
}

typedef struct {
    u8 n;          /* +0x0 */
    u8 idx;        /* +0x1 */
    u16 t;         /* +0x2 */
    u16 fr;        /* +0x4 */
    u16 prev;      /* +0x6 */
    u8 pad8[8];
    PppVec4 v[1];  /* +0x10 */
} Tail2XWork;

typedef struct {
    s32 frame;
    s32 id;        /* +0x4 */
    u16 speed;     /* +0x8 */
    u8 padA[0x1C];
    u8 local;      /* +0x26 */
} Tail2XKey;

void pppKeShpTail2XFrame(PppObject *obj, Tail2XKey *key, PppEntry *e) {
    Tail2XWork *w;
    PppShape *sh;
    PppShapeFrame *f;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w = PPP_WORK(Tail2XWork, obj, e, 0);
    if (obj->frame == 0 && obj->unk9D == 0) {
        PppVec4 v;
        f32 *p;
        s32 n;

        if (key->local) {
            func_002672f8(v, D_00615E70, D_00615E68->m[3]);
            v[3] = 1.0f;
        } else {
            func_002675a8(v, D_00615E68->m[3]);
            v[3] = 1.0f;
        }
        p = w->v[0];
        for (n = w->n; n > 0; n--) {
            func_002675a8(p, v);
            p += 4;
        }
    }
    if (w->idx == 0)
        w->idx = w->n;
    w->idx--;
    if (key->local) {
        func_002672f8(w->v[w->idx], D_00615E70, D_00615E68->m[3]);
        w->v[w->idx][3] = 1.0f;
    } else {
        func_001a9098(w->v[w->idx], D_00615E68->m[3]);
    }
    {
        u16 fr;

        { PppShapeEnt *se = &((DSysS *) D_00615E64)->shapes[key->id]; sh = se->shape; }

        fr = w->fr;
        w->prev = fr;
        f = &sh->f[fr];
        w->t += key->speed;
        if (w->t < f->dur)
            return;
        w->t -= f->dur;
        w->fr = fr + 1;
        if (w->fr < sh->n)
            return;
        {
            s32 fl = f->flags;
            w->t = 0;
            if (fl & 0x80)
                w->fr = 0;
            else
                w->fr--;
        }
    }
}

typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) SplV4;
extern SplV4 D_00372720;
extern SplV4 D_00372740;

/* VU0 */
void func_00199888(u128 *out, u128 *p, u128 *q, f32 t) {
    s32 i = (s32) t;
    SplV4 *c = &D_00372720;

    p += i;
    q += i;
    c->z = t - (f32) i;
    __asm__ volatile(
        ".set noreorder\n"
        "lqc2 $vf1, 0(%1)\n"
        "lqc2 $vf2, 16(%1)\n"
        "lqc2 $vf3, 0(%2)\n"
        "lqc2 $vf4, 16(%2)\n"
        "lqc2 $vf5, 0(%3)\n"
        "vsub.xyzw $vf10xyzw, $vf4xyzw, $vf3xyzw\n"
        "vmuly.xyzw $vf11xyzw, $vf3xyzw, $vf5y\n"
        "vmulx.xyzw $vf12xyzw, $vf3xyzw, $vf5x\n"
        "vsub.xyzw $vf13xyzw, $vf2xyzw, $vf1xyzw\n"
        "vmulz.xyzw $vf10xyzw, $vf10xyzw, $vf5z\n"
        "vadd.xyzw $vf11xyzw, $vf11xyzw, $vf4xyzw\n"
        "vadd.xyzw $vf10xyzw, $vf10xyzw, $vf12xyzw\n"
        "vsub.xyzw $vf13xyzw, $vf13xyzw, $vf11xyzw\n"
        "vmulz.xyzw $vf10xyzw, $vf10xyzw, $vf5z\n"
        "vadd.xyzw $vf10xyzw, $vf10xyzw, $vf13xyzw\n"
        "vmulz.xyzw $vf10xyzw, $vf10xyzw, $vf5z\n"
        "vadd.xyzw $vf10xyzw, $vf10xyzw, $vf1xyzw\n"
        "sqc2 $vf10, 0(%0)\n"
        ".set reorder\n"
        : : "r"(out), "r"(p), "r"(q), "r"(c) : "memory");
}

/* VU0 */
void func_0019a9e0(u128 *out, u128 *p, u128 *q, f32 t) {
    s32 i = (s32) t;
    SplV4 *c = &D_00372740;

    p += i;
    q += i;
    c->z = t - (f32) i;
    __asm__ volatile(
        ".set noreorder\n"
        "lqc2 $vf1, 0(%1)\n"
        "lqc2 $vf2, 16(%1)\n"
        "lqc2 $vf3, 0(%2)\n"
        "lqc2 $vf4, 16(%2)\n"
        "lqc2 $vf5, 0(%3)\n"
        "vsub.xyzw $vf10xyzw, $vf4xyzw, $vf3xyzw\n"
        "vmuly.xyzw $vf11xyzw, $vf3xyzw, $vf5y\n"
        "vmulx.xyzw $vf12xyzw, $vf3xyzw, $vf5x\n"
        "vsub.xyzw $vf13xyzw, $vf2xyzw, $vf1xyzw\n"
        "vmulz.xyzw $vf10xyzw, $vf10xyzw, $vf5z\n"
        "vadd.xyzw $vf11xyzw, $vf11xyzw, $vf4xyzw\n"
        "vadd.xyzw $vf10xyzw, $vf10xyzw, $vf12xyzw\n"
        "vsub.xyzw $vf13xyzw, $vf13xyzw, $vf11xyzw\n"
        "vmulz.xyzw $vf10xyzw, $vf10xyzw, $vf5z\n"
        "vadd.xyzw $vf10xyzw, $vf10xyzw, $vf13xyzw\n"
        "vmulz.xyzw $vf10xyzw, $vf10xyzw, $vf5z\n"
        "vadd.xyzw $vf10xyzw, $vf10xyzw, $vf1xyzw\n"
        "sqc2 $vf10, 0(%0)\n"
        ".set reorder\n"
        : : "r"(out), "r"(p), "r"(q), "r"(c) : "memory");
}
