#include "common.h"
/* func_0016fc60: MATCH hand/nostrict */
#define A a
#define B b
typedef struct { f32 x, y, z, w; } V4FC;
typedef struct { u8 pad0[0x10]; V4FC pos; } ChrFC;
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
    if (p == 0 || !func_00122ff8(p)) return 0; return func_0012f040(p, part);
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

typedef struct { f32 x, y, z, len; } SegB;
#include "data/data_0048.h"
#include "data/pieces/D_002C5958.h"
