/* 22w off (hand, strict): only the two inner id loops differ (orig keeps id in a1, loads table base first, q++ in bnez slot). */
#include "common.h"
typedef struct { f32 min[3]; f32 max[3]; u16 n; u16 ids[1]; } Node368;
typedef struct { f32 v[4]; } V4q;
typedef struct { V4q lo[3]; V4q hi[3]; } Box368;
typedef struct { u8 pad[0x10]; s32 fl; } Tri368;
typedef struct { u8 pad[0x18]; u16 cnt; } Out368;
extern s32 D_002C12C4;
extern s32 D_004E0428[];
extern void (*D_002BD178[])(s32, s32 *);
extern void (*D_002BD1A8[])(s32, s32 *);
extern Box368 D_002C1260;
extern Node368 **D_002A6244;
extern Tri368 *D_002A6238;
s32 func_00115d58(void);
void func_001158c8(Out368 *);

static inline s32 overlap(f32 *mn, f32 *mx, Box368 *b) {
    if (mn[0] <= b->hi[0].v[0] && b->lo[0].v[0] <= mx[0]
        && b->hi[1].v[0] >= mn[1] && b->lo[1].v[0] <= mx[1]
        && b->hi[2].v[0] >= mn[2] && b->lo[2].v[0] <= mx[2]) return 1;
    return 0;
}
static inline s32 inside(f32 *mn, f32 *mx, Box368 *b) {
    if (b->lo[0].v[0] < mn[0] && b->hi[0].v[0] > mx[0]
        && b->lo[1].v[0] < mn[1] && b->hi[1].v[0] > mx[1]
        && b->lo[2].v[0] < mn[2] && b->hi[2].v[0] > mx[2]) return 1;
    return 0;
}

static inline void each(Node368 *nd, void (*f)(s32, s32 *)) {
    s32 i;
    u16 *q = nd->ids;
    for (i = 0; i < nd->n; i++) {
        s32 id = *q++;
        Tri368 *t = &D_002A6238[id];
        if (!(t->fl & 1)) f(id, &t->fl);
    }
}
void func_00116368(Out368 *o, s32 k) {
    s32 n, i, j;
    u16 *q;
    s32 *p;
    Node368 *nd;
    void (*f1)(s32, s32 *);
    void (*f2)(s32, s32 *);
    D_002C12C4 = 0;
    n = func_00115d58();
    p = D_004E0428;
    func_001158c8(o);
    f2 = D_002BD1A8[k];
    f1 = D_002BD178[k];
    for (j = 0; j < n; j++) {
        nd = D_002A6244[*p++];
        if (overlap(nd->min, nd->max, &D_002C1260)) {
            if (inside(nd->min, nd->max, &D_002C1260)) each(nd, f1);
            else each(nd, f2);
        }
    }
    o->cnt = *(u16 *)&D_002C12C4;
}
