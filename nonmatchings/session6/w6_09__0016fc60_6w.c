/* 6w off (nostrict; strict same): inl_valid tail block order - orig bnezl v0->call block, fallthrough b join/v1=0; ours beqz v0->zero block */
#include "common.h"
#define A a
#define B b
typedef struct { f32 x, y, z, w; } V4FC;
typedef struct { u8 pad0[0x10]; V4FC pos; } ChrFC;
typedef struct { u8 pad0[0x90]; void *p90; s32 part; } WkFC;
extern u32 D_002C5958;
extern f32 D_0048E9EC;
extern s32 func_00122ff8(void *);
extern void func_0012ec60(void *, s32, f32 *);
extern s32 func_0012ee70(void *, s32);
extern s32 func_0012f040(void *, s32);
extern f32 func_00267390(void *, void *);
extern void func_00267530(void *, void *, void *);

static inline s32 inl_valid(void *p, s32 part) {
    if (!(D_002C5958 & 1)) return 0;
    if (p == 0) return 0;
    if (func_00122ff8(p)) return func_0012f040(p, part);
    return 0;
}

static inline s32 inl_best(void *p, ChrFC *c) {
    f32 a[4];
    f32 b[4];
    s32 i, best;
    f32 bd, d;
    best = -1;
    if (p != 0) {
        i = -1;
        bd = D_0048E9EC;
        while ((i = func_0012ee70(p, i)) >= 0) {
            if (!func_0012f040(p, i)) continue;
            func_0012ec60(p, i, a);
            func_00267530(b, a, &c->pos);
            d = func_00267390(b, b);
            if (d < bd) {
                bd = d;
                best = i;
            }
        }
    }
    return best;
}

void func_0016fc60(ChrFC *c, WkFC *w) {
    if (func_00122ff8(w->p90)) {
        if (w->part < 0 || !inl_valid(w->p90, w->part)) w->part = inl_best(w->p90, c);
    } else {
        w->p90 = 0;
    }
}
