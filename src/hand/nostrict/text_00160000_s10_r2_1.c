#include "common.h"
#include "data/bss_0057.h"
/* func_0016ea58 (hand/nostrict): the target search is matched func_001711d0 written as a static inline helper (inl_001711d0, its exact body); the set1/set2 gotos written out as separate w1->w38 |= 8 / w2->w38 |= 8 statements (jump2 cross-jumps them; the extra refs give w1/w2 s4/s5 over the hoisted const 2), the d2<d1 arm as one && / || condition, w2 = 0 before w1 = 0. */

#include "data/types/nostrict_text_00160000_s10_r2_1.h"
extern f32 D_0048E950;
extern EntEA *func_00123158(ChrEA *, EntEA *);
extern s32 func_00123368(EntEA *);
extern void func_0012ec60(EntEA *, s32, f32 *);
extern s32 func_0012ee70(EntEA *, s32);
extern s32 func_0012f040(void *, s32);
extern s32 func_00141200(EntEA *, s32);
extern s32 func_00153d78(ChrEA *);
extern f32 func_00267390(void *, void *);
extern void func_00267530(void *, void *, void *);

static inline void inl_001711d0(ChrEA *self, LockEA *out, f32 r) {
    f32 a[4];
    f32 b[4];
    EntEA *p;
    s32 i;
    f32 best, d;
    out->f4 = -1;
    out->f0 = 0;
    if (r <= 0.0f) best = D_0048E950;
    else best = r * r;
    p = 0;
    while ((p = func_00123158(self, p)) != 0) {
        if (((s32)(p->f370 >> 37) & 3) != 2) continue;
        if (!func_00123368(p)) continue;
        if (func_00141200(p, 0)) continue;
        for (i = -1; (i = func_0012ee70(p, i)) >= 0;) {
            if (!func_0012f040(p, i)) continue;
            func_0012ec60(p, i, a);
            func_00267530(b, a, &self->pos);
            d = func_00267390(b, b);
            if (d < best) {
                out->f0 = p;
                best = d;
                out->f4 = i;
            }
        }
    }
}

static inline s32 inl_dead(ChrEA *c) {
    if (func_00153d78(c) || (c->flags & 0x200)) return 1;
    return 0;
}
#include "data/bss_0057_typed.h"
#include "data/data_0048.h"
