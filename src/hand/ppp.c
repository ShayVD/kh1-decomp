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
    u64 a;
    s32 b;
} PppU64S32;

typedef struct {
    s32 a, b;
} PppS32x2;

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

void pppKeMdlDttCon(void *obj, PppEntry *e) {
    PppU64S32 *w = PPP_WORK(PppU64S32, obj, e, 0);

    w->a = 0;
    w->b = 0;
}

void pppKeLnsLpSftCon(void *obj, PppEntry *e) {
    PppS32x2 *w = PPP_WORK(PppS32x2, obj, e, 0);

    w->a = 0;
    w->b = 0;
}

void pppPointCon(void *obj, PppEntry *e) {
    PppVec3 *w = PPP_WORK(PppVec3, obj, e, 0);

    w->x = w->y = w->z = 0.0f;
}
