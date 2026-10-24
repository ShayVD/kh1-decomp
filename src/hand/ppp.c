/* ppp component callbacks (include/ppp.h), by hand. Each finds its work
 * area in the program object at entry->offsets[k] past +0xA0. */
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
    f32 x, y, z;
} PppVec3;

void pppVertexApCon(void *obj, PppEntry *e) {
    PppS16x2 *w = PPP_WORK(PppS16x2, obj, e, 0);

    w->a = 0;
    w->b = 0;
}

void pppKeBornRnd5Con(void *obj, PppEntry *e) {
    PppS16S8 *w = PPP_WORK(PppS16S8, obj, e, 0);

    w->a = 0;
    w->b = 0;
}

void pppPointCon(void *obj, PppEntry *e) {
    PppVec3 *w = PPP_WORK(PppVec3, obj, e, 0);

    w->x = w->y = w->z = 0.0f;
}

typedef unsigned int u128 __attribute__((mode(TI)));

/* The object a program runs in: +0x0C is its frame counter, which the
 * frame callbacks compare with their keyframe's. */
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;

/* A keyframe: the frame it applies at, then the class's values. */
typedef struct {
    s32 frame; /* +0x0 */
    f32 a, b;  /* +0x4, +0x8 */
} PppKey;

typedef struct {
    f32 x, y, z;
    s32 n;
} PppVtMime;

void pppVtMimeCon(void *obj, PppEntry *e) {
    PppVtMime *w = PPP_WORK(PppVtMime, obj, e, 0);

    w->x = w->y = w->z = 0.0f;
    w->n = 0;
}

void pppDrawMdlTsCon(void *obj, PppEntry *e) {
    f32 *w = PPP_WORK(f32, obj, e, 2);

    w[0] = w[1] = w[2] = w[3] = w[4] = w[5] = 0.0f;
}
