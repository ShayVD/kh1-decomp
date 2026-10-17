#include "common.h"
#include "ppp.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

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

u8 *func_00182588(PppSystem *, PppSlot *);

static inline u8 *inl_spawn(PppSystem *sys, s32 id, void *o) {
    PppSlot *s = &sys->slots[id];
    u8 *i = 0;

    if (s) {
        i = func_00182588(sys, s);
        *(void **) (i + 4) = o;
    }
    return i;
}

typedef struct { f32 x, y, z, w; } V4;

typedef struct {
    s32 frame;
    u8 n;          /* +0x04 */
    u8 pad5[3];
    s32 slot;      /* +0x08 */
    s32 off;       /* +0x0C */
    s32 off10;     /* +0x10 */
} BornKey;

typedef struct {
    u8 *p;
    s32 pad4;
    f32 f8;
} BornWork;

void func_001a9098(u8 *, u8 *);
void func_002675a8(V4 *, u8 *);
void func_00267530(V4 *, u8 *, V4 *);
void func_00267560(V4 *, V4 *, f32);
void func_001a9110(u8 *, V4 *, V4 *);

CONTEXT_ONLY void func_0018e348(void *obj, BornKey *key, PppEntry *e) {
    V4 a, b, c;
    u8 *inst;
    u8 *d;
    BornWork *w;
    f32 t, s;

    inst = inl_spawn(D_00615E60, key->slot, obj);
    d = inst + key->off + 0xA0;
    func_001a9098(d, (u8 *) obj + e->offsets[1] + 0xA0);

    w = PPP_WORK(BornWork, obj, e, 0);
    if (w->p == 0) {
        w->f8 = 1.0f / (f32) (key->n + 1);
    } else {
        func_002675a8(&a, w->p);
        func_00267530(&b, d, &a);
        t = (f32) key->n;
        s = w->f8;
        while (0.0f < t) {
            u8 *d2;
            inst = inl_spawn(D_00615E60, key->slot, obj);
            d2 = inst + key->off + 0xA0;
            func_00267560(&c, &b, s * t);
            t -= 1.0f;
            func_001a9110(d2, &a, &c);
        }
    }
    w->p = d;
}

void pppKeBornPtCmplFrame(void *obj, BornKey *key, PppEntry *e) {
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->slot == -1 || key->off10 == -1)
        return;
    do { func_0018e348(obj, key, e); } while (0);
}
