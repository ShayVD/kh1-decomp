/* ppp component callbacks around 0x193e00-0x1a0800 (worker 64). This
 * region was built without strict aliasing. */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef int u128 __attribute__((mode(TI)));
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
typedef f32 PppVec4[4] __attribute__((aligned(16)));

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

typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject;

/* The current draw matrices. */

/* Models and shapes. */

/* Parameter block of func_001aaf88 (model draw). */
extern f32 D_00575A00; /* src/data/bss_0057.c: u8 D_00575A00[0x10] */
u8 *func_00182588(PppSystem *, PppSlot *);
void func_001a9098(void *, void *);
void func_00267530(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
s32 func_001a8f70(void *);
void func_00267560(f32 *, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_001a90f8(void *, void *, void *);

static inline void vu0ScaleRow(f32 *row, f32 s) {
    __asm__ volatile(
        "qmtc2 %1, $vf9\n"
        "lqc2 $vf10, 0(%0)\n"
        "vmulx.xyz $vf10xyz, $vf10xyz, $vf9x\n"
        "sqc2 $vf10, 0(%0)\n"
        : : "r"(row), "r"(s));
}

typedef struct {
    s32 frame;
    s32 slot;  /* +0x4 */
    s32 off;   /* +0x8 */
    u8 c;      /* +0xC */
} PppHitBornKey;

void pppKeHitBornFrame(PppObject *obj, PppHitBornKey *key, PppEntry *e) {
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

void pppKeHitChkPxBFrame(PppObject *obj, PppHitBornKey *key, PppEntry *e) {
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
    func_00267530(q.a, (f32 *) w0, t->pos);
    func_002675a8(q.b, (f32 *) w1);
    if (!func_001a8f70(&q))
        return;
    if (q.t < 0.0f || q.t > 1.0f)
        return;
    w->flags |= 1;
    func_00267560(c, q.b, q.t);
    func_00267518(c, c, q.a);
    func_00267518(w->v, w->tgt->pos, c);
    if (w->flags & 2) {
        func_001a90f8(w1, w, w0);
        obj->frame = 0xFFFF0000;
    }
}

/* Hand-written VU0 routine: the asm body addresses its 16-byte work
 * buffer through $sp. */

/* Hand-written VU0 routine: the asm body addresses its 16-byte work
 * buffer through $sp. */

/* Quicksort of D_0061E310 by ->w, largest first. The second recursive
 * call is a tail call that gcc turns into a jump. */

/* needs make: uses rodata (switch jump table) */
