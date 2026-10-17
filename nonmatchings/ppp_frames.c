/* ppp frame callbacks, drafts (types from src/hand/ppp.c). All three need
 * the original's store/load order: gcc 2.96's -fstrict-aliasing (on at -O2)
 * lets ours hoist the key's float load above the pointer store (HitBall)
 * or skip reloading entry->offsets after the float stores (GrvTgt, which
 * matches with -fno-strict-aliasing, but 7 matched game functions then
 * break). The real field types probably make the accesses alias.
 * MegaPlaceShapeFrame: the original keeps `obj` in a2 and the entry in
 * a3 (register choice). */
#include "ppp.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef struct {
    s16 a, b;
} PppS16x2;

typedef struct {
    s16 a;
    s8 b;
} PppS16S8;

typedef struct {
    u64 a;
    s32 b;
} PppU64S32;

typedef struct {
    s32 a, b;
} PppS32x2;

typedef struct {
    f32 x, y, z;
} PppVec3;


typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame;
} PppObject;

typedef struct {
    s32 frame;
    f32 a, b;
} PppKey;

typedef struct {
    f32 f;  /* +0x0 */
    void *p; /* +0x4 */
} PppHitBall;

void pppKeHitBallFrame(PppObject *obj, PppKey *key, PppEntry *e) {
    if (obj->frame == key->frame) {
        void *w0 = PPP_WORK(void, obj, e, 0);
        PppHitBall *w1 = PPP_WORK(PppHitBall, obj, e, 1);

        w1->p = w0;
        w1->f = key->a;
    }
}

typedef struct {
    f32 a, b;  /* +0x0 */
    void *p;   /* +0x8 */
} PppGrvTgt;

void pppKeGrvTgtFrame(PppObject *obj, PppKey *key, PppEntry *e) {
    if (obj->frame == key->frame) {
        PppGrvTgt *w = PPP_WORK(PppGrvTgt, obj, e, 1);

        w->a = key->a;
        w->b = key->b;
        w->p = PPP_WORK(void, obj, e, 0);
    }
}

s32 func_0019e028(void *);

void pppRyjMegaPlaceShapeFrame(PppObject *obj, PppKey *key, PppEntry *e) {
    u8 *done = PPP_WORK(u8, obj, e, 1);

    if (!*done) {
        if (func_0019e028(PPP_WORK(void, obj, e, 0)))
            *done = 1;
    }
}
