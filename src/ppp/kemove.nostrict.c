/* The ppp motion classes' frames, -fno-strict-aliasing (docs/modules.md
 * "Session 50"): pppKeHmgEff steers the owner towards a target (another
 * instance's work area, or D_00575A00) at a rate; pppKeGrvEff pulls it
 * towards a pppKeGrvTgt; pppKeHitBorn starts an effect (func_00182588) when
 * its flag says it was hit; pppKeHitChkPxB tests the owner against a
 * target's sphere (pppmath.c's ray / sphere helpers) and sets the hit flags.
 * kemove.c has the Cons and the small classes.  Types named NAME_xxxxx are
 * one function's own view (tools/shift/s50move/assemble.py).  Read from the
 * code, not proved by a boot. */

/* pppKeHmgEffFrame (from hand/nostrict/text_00190000_h63.c). */
#include "common.h"
#include "platform/vu.h"
#include "ppp.h"
#include "data/bss_0061.h"
#include "data/pieces/D_003701F0.h"
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
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
extern PppSystem *D_00615E60;
extern f32 D_00575A00;
extern s32 D_0061621C;
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;
typedef f32 PppVec4[4] __attribute__((aligned(16)));
void func_001a9098(void *, void *);
typedef struct {
    u8 pad[0x9D];
    u8 unk9D;  /* +0x9D */
} PppObjectB;
f32 func_001a9350(PppVec4);
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
    PlatVu0SubVector(a, w->target, PPP_WORK(f32, obj, e, 0));
    PlatVu0Normalize(a, a);
    PlatVu0CopyVector(b, q);
    len = func_001a9350(b);
    PlatVu0Normalize(b, b);
    PlatVu0AddVector(c.f, b, a);
    if (c.d[0] == 0 && c.d[1] == 0)
        a[func_001a8f30() % 3] += 0.05f;
    PlatVu0InterVector(a, a, b, w->rate);
    PlatVu0Normalize(a, a);
    PlatVu0ScaleVector(a, a, len);
    func_001a9098(q, a);
}

/* pppKeGrvEffFrame (from hand/nostrict/text_00190000_h63.c). */
void func_001a9110(void *, void *, PppVec4);
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
    PlatVu0SubVector(a, t->pos, PPP_WORK(f32, obj, e, 0));
    len = func_001a9350(a);
    PlatVu0Normalize(a, a);
    if (len < t->range) {
        PlatVu0ScaleVector(a, a, (1.0f - len / t->range) * t->force);
        func_001a9110(q, q, a);
    }
}

/* pppKeHitBornFrame (from hand/nostrict/text_00190000_h64.c). */
typedef struct {
    u8 pad[0x80];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem_93e68;
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject_93e68;
u8 *func_00182588(PppSystem_93e68 *, PppSlot *);
typedef struct {
    s32 frame;
    s32 slot;  /* +0x4 */
    s32 off;   /* +0x8 */
    u8 c;      /* +0xC */
} PppHitBornKey;
#define D_00615E60 ((PppSystem_93e68 *) D_00615E60)
void pppKeHitBornFrame(PppObject_93e68 *obj, PppHitBornKey *key, PppEntry *e) {
    u8 *f = PPP_WORK(u8, obj, e, 2);
    u8 *w1;
    PppSlot *slot;
    u8 *inst;

    if (*f & 2)
        return;
    if (obj->frame == key->frame) {
        if (key->c)
            *f |= 1;
        else
            *f &= 0xFE;
    }
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w1 = PPP_WORK(u8, obj, e, 1);
    if (!(w1[0x10] & 1))
        return;
    if (key->slot == -1)
        return;
    slot = &D_00615E60->slots[key->slot];
    inst = 0;
    if (slot) {
        inst = func_00182588(D_00615E60, slot);
        *(void **) (inst + 4) = obj;
    }
    {
        u8 fl = *f;
        u8 *w0 = PPP_WORK(u8, obj, e, 0);
        u8 *dst = inst + key->off + 0xA0;
        if (!(fl & 1)) {
            *f = fl | 2;
            func_001a9098(dst, w1);
        } else {
            func_001a9098(dst, w0);
        }
    }
}
#undef D_00615E60

/* pppKeHitChkPxBFrame (from hand/nostrict/text_00190000_h64.c). */
typedef struct {
    u8 pad[0x80];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem_93fe0;
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject_93fe0;
s32 func_001a8f70(void *);
void func_001a90f8(void *, void *, void *);
typedef struct {
    f32 r;
    f32 *pos;
} PppHitTgt;
typedef struct {
    PppVec4 v;
    u8 flags;       /* +0x10 */
    PppHitTgt *tgt; /* +0x14 */
} PppHitChkWork;
typedef struct {
    PppVec4 a;
    PppVec4 b; /* +0x10 */
    f32 r;     /* +0x20 */
    f32 t;     /* +0x24 */
} PppHitQ;
#define D_00615E60 ((PppSystem_93fe0 *) D_00615E60)
void pppKeHitChkPxBFrame(PppObject_93fe0 *obj, PppHitBornKey *key, PppEntry *e) {
    PppHitQ q;
    PppVec4 c;
    PppHitChkWork *w = PPP_WORK(PppHitChkWork, obj, e, 2);
    PppHitTgt *t;
    u8 *w1, *w0;
    u8 fl = w->flags;

    if (fl & 1)
        return;
    if (obj->frame == key->frame) {
        if (key->slot != -1)
            w->tgt = (PppHitTgt *) (D_00615E60->slots[key->slot].inst + key->off + 0xA0);
        else
            w->tgt = (PppHitTgt *) &D_00575A00;
        if (key->c)
            w->flags = fl | 2;
        if (obj->frame == 0 && obj->unk9D == 0)
            return;
    }
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    t = w->tgt;
    if (t == (PppHitTgt *) &D_00575A00)
        return;
    w0 = PPP_WORK(u8, obj, e, 0);
    w1 = PPP_WORK(u8, obj, e, 1);
    if (t->r == 0.0f)
        return;
    q.r = t->r;
    PlatVu0SubVector(q.a, (f32 *) w0, t->pos);
    PlatVu0CopyVector(q.b, (f32 *) w1);
    if (!func_001a8f70(&q))
        return;
    if (q.t < 0.0f || q.t > 1.0f)
        return;
    w->flags |= 1;
    PlatVu0ScaleVector(c, q.b, q.t);
    PlatVu0AddVector(c, c, q.a);
    PlatVu0AddVector(w->v, w->tgt->pos, c);
    if (w->flags & 2) {
        func_001a90f8(w1, w, w0);
        obj->frame = 0xFFFF0000;
    }
}
#undef D_00615E60

