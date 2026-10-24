/* The pppKeTh classes, -fno-strict-aliasing (docs/modules.md "Session 50"):
 * a thread / streamer effect.  pppKeThFrame emits nodes along the owner's
 * direction into the pool of a pppKeThRes (keth*.c's node lists),
 * pppKeThDraw draws them as strips (kethdraw.nostrict.c), pppKeThTp moves
 * them, pppKeThHitBorn starts an effect where a node hits, pppKeThSft shifts
 * their parameters.  kethcls.c has the Cons.  Types named NAME_xxxxx are one
 * function's own view (tools/shift/s50move/assemble.py).  Read from the
 * code, not proved by a boot. */
#include "common.h"
#include "ppp.h"
#include "data/pieces/D_003701F0.h"
#include "data/bss_0061.h"
#include "data/types/nostrict_text_00180000_h40.h"
#include "data/pieces/D_003701E0.h"
#include "data/pieces/D_003701D0.h"

/* pppKeThFrame (from hand/nostrict/text_00180000_c05.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef int u128_8bee0 __attribute__((mode(TI)));
typedef f32 PppVec4[4] __attribute__((aligned(16)));
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
    u8 pad[0x10];
    PppMtx m;
    PppMtx m2;
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;
extern f32 D_00575A00;
typedef struct {
    s32 frame;
    s32 slot;      /* +0x04 */
    s32 off;       /* +0x08 */
    u16 d[16];     /* +0x0C */
    f32 f2C;
    f32 f30, f34, f38, f3C, f40, f44, f48, f4C;
    u16 h50;
    u8 b52, b53;
    u8 pad54;
    u8 b55, b56, b57, b58;
} PppThKey;
typedef struct {
    u8 c0[8];      /* +0x00 */
    u8 pad8[4];
    f32 fC;        /* +0x0C */
    u8 c10[8];     /* +0x10 */
    u8 pad18[4];
    f32 f1C, f20, f24, f28, f2C, f30, f34, f38, f3C; /* +0x1C */
    u8 b40, b41, b42;
    u8 pad43;
} PppThSub;
typedef struct {
    u8 pad0[4];
    u8 flags;      /* +0x04 */
    u8 pad5[0xB];
    PppThSub s;    /* +0x10 */
    u8 pad54[0xC];
    u8 *a;         /* +0x60 */
    void *p;       /* +0x64 */
    f32 f68;       /* +0x68 */
    f32 f6C;       /* +0x6C */
    u16 c[16];     /* +0x70 */
} PppThWork;
typedef struct {
    PppThWork *w;
    void *p;
    PppThSub *s;
    u8 *a;
    f32 *v1;
    f32 *v0;
} PppThArgs;
void sceVu0CopyMatrix(PppMtx, PppMtx);
void func_002672f8(f32 *, PppMtx, f32 *);
void func_002673b8(f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
void func_001a89f0(PppThWork *, u8 *, f32 *, f32 *);
void func_001a8ae8(PppThArgs *);
void pppKeThFrame(PppObject *obj, PppThKey *key, PppEntry *e) {
    PppThWork *w = PPP_WORK(PppThWork, obj, e, 0);
    f32 *pos = PPP_WORK(f32, obj, e, 2);
    PppThSub *s = (PppThSub *) ((u8 *) obj + e->offsets[0] + 0xB0);
    PppMtx m;
    PppVec4 dir;
    PppVec4 org;
    PppThArgs args;
    f32 f;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    sceVu0CopyMatrix(m, D_00615E68->m);
    *(u128_8bee0 *) m[3] = 0;
    m[3][3] = 1.0f;
    func_002672f8(dir, m, pos);
    func_002673b8(dir, dir);
    func_002675a8(org, D_00615E68->m[3]);
    if (obj->frame == key->frame) {
        if (obj->frame == 0) {
            u8 *p;
            u8 *a = PPP_WORK(u8, obj, e, 1);
            if (key->slot != -1)
                p = D_00615E60->slots[key->slot].inst + key->off + 0xA0;
            else
                p = (u8 *) &D_00575A00;
            if (w->p == &D_00575A00)
                return;
            w->p = p;
            w->a = a;
            if (key->b56 == 0)
                w->flags |= 8;
            if (key->b55 != 0)
                w->flags |= 4;
            if (key->b58 != 0)
                w->flags |= 0x10;
            if (key->b57 != 0)
                w->flags |= 0x20;
            func_001a89f0(w, w->a, org, dir);
        }
        w->c[0] += key->d[0];
        w->c[1] += key->d[1];
        w->c[2] += key->d[2];
        w->c[3] += key->d[3];
        w->c[4] += key->d[4];
        w->c[5] += key->d[5];
        w->c[6] += key->d[6];
        w->c[7] += key->d[7];
        w->c[8] += key->d[8];
        w->c[9] += key->d[9];
        w->c[10] += key->d[10];
        w->c[11] += key->d[11];
        w->c[12] += key->d[12];
        w->c[13] += key->d[13];
        w->c[14] += key->d[14];
        w->c[15] += key->d[15];
        w->f68 = key->f2C;
        w->f6C += key->f48;
        s->b42 = w->a[1] + 255;
        s->fC += key->f30;
        s->f30 = key->f38;
        s->f38 = key->f3C;
        s->f3C = key->f40;
        s->f24 += key->f44;
        s->f2C += key->f4C;
        s->f28 = key->h50 * 3.141592654 * 0.01745329252222222;
        s->b40 = key->b52;
        s->b41 = key->b53;
        s->f1C = -(s->fC - s->fC * key->f34) / s->b42;
    }
    f = w->f68 / s->b42;
    s->f20 = f;
    s->f34 = w->f6C / f;
    s->c0[0] = w->c[0] >> 7;
    s->c0[1] = w->c[1] >> 7;
    s->c0[2] = w->c[2] >> 7;
    s->c0[3] = w->c[3] >> 7;
    s->c0[4] = w->c[4] >> 7;
    s->c0[5] = w->c[5] >> 7;
    s->c0[6] = w->c[6] >> 7;
    s->c0[7] = w->c[7] >> 7;
    s->c10[0] = w->c[8] >> 7;
    s->c10[1] = w->c[9] >> 7;
    s->c10[2] = w->c[10] >> 7;
    s->c10[3] = w->c[11] >> 7;
    s->c10[4] = w->c[12] >> 7;
    s->c10[5] = w->c[13] >> 7;
    s->c10[6] = w->c[14] >> 7;
    s->c10[7] = w->c[15] >> 7;
    args.w = w;
    args.s = &w->s;
    args.a = w->a;
    args.p = w->p;
    args.v1 = org;
    args.v0 = dir;
    func_001a8ae8(&args);
}

/* pppKeThDraw (from hand/nostrict/text_00180000_s7_w2.c). */
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
extern u8 D_00616080[];
extern u8 D_00616224[];
void func_001a8c40(ThWork *, void *, f32 *, ThSub *, void *, u64, u64);
/* session 7 w2: pppKeThDraw (0x18c3f8). The mode switch assigns both t1 and t2 in every case (no shared defaults), which stops jump.c hoisting t1 = 66. */
void pppKeThDraw(void *obj, ThKey *k, PppEntry *e) {
    f32 v[2];
    ThWork *w;
    u64 t1;
    u64 t2;
    u8 m;
    w = PPP_WORK(ThWork, obj, e, 0);
    v[0] = D_003701F0[0];
    v[1] = D_003701F0[1];
    m = k->mode;
    switch (m) {
    case 0: t1 = 72; t2 = 0x51801; break;
    case 1: t1 = 66; t2 = 0x51801; break;
    default: t2 = 0x70000; t1 = 0x80000000a8ULL; break;
    }

    func_001a8c40(w, D_00616080, v, &w->s, D_00616224, t1, t2);
}

/* pppKeThCon (from hand/nostrict/text_00180000_s6_11.c). */
void func_001a8d78(ThWork *);
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

/* pppKeThReset (from hand/nostrict/text_00180000_s6_11.c). */
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

/* pppKeThTpFrame (from hand/nostrict/text_00180000_h40.c). */
typedef struct {
    s32 frame;
    f32 c, a, b;  /* +0x4 */
    s32 slot;     /* +0x10 */
    s32 off;      /* +0x14 */
} PppThTpKey;
typedef struct {
    u8 pad[0x10];
    f32 a, b, c;  /* +0x10 */
    f32 *p;       /* +0x1C */
} PppThTpWork;
void func_001a9098(void *, f32 *);
void pppKeThTpFrame(PppObject *obj, PppThTpKey *key, PppEntry *e) {
    PppThTpWork *w = PPP_WORK(PppThTpWork, obj, e, 0);

    if (obj->frame == key->frame) {
        f32 *p;
        w->a = key->a;
        w->c = key->c;
        w->b = key->b;
        if (key->slot != -1)
            p = (f32 *) (D_00615E60->slots[key->slot].inst + key->off + 0xA0);
        else
            p = &D_00575A00;
        w->p = p;
        if (p == &D_00575A00)
            w->p = 0;
    }
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    func_001a9098((void *) w, D_00615E68->m[3]);
}

/* pppKeThHitBornFrame (from hand/nostrict/text_00190000_h63.c). */
typedef struct {
    u8 pad[0x30];
    f32 col[4];     /* +0x30 */
    u8 pad40[0x40];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem_8cad8;
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject_8cad8;
u8 *func_00182588(PppSystem_8cad8 *, PppSlot *);
static inline u8 *inl_spawn(PppSystem_8cad8 *sys, s32 id, PppObject_8cad8 *o) {
    PppSlot *s = &sys->slots[id];
    u8 *i = 0;

    if (s) {
        i = func_00182588(sys, s);
        *(PppObject_8cad8 **) (i + 4) = o;
    }
    return i;
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
#define D_00615E60 ((PppSystem_8cad8 *) D_00615E60)
void pppKeThHitBornFrame(PppObject_8cad8 *obj, PppHitBornKey *key, PppEntry *e) {
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
#undef D_00615E60

/* pppKeThSftFrame (from hand/nostrict/text_00180000_b07.c). */
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

