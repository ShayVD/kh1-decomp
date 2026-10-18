/* 00249718 12w, hand (same count as w6/s6 drafts; sibling types from func_00249618: Seg3, V4f v[4]). NEW FINDING (r2_3 s9): the original allocation (1.0f f4, t2 f5, t3 f6) is exactly what gcc gives when t2/t3 are GLOBAL pseudos: local-alloc then only has the temps and the 1.0f const (gets f4, the first free reg) and global-alloc gives t2 f5, t3 f6. Proof: adding `extern s32 D_X; if (D_X) D_X = 0;` right after t3 = t2 * t gives exactly the original FP registers for every row (extra code of course). So the original source has a block boundary between t2/t3 and their uses at flow1 that leaves no code in the final binary (and that sched1/sched2 can still move the row-0 loads and the li.s across). Not found: do{}while(0) (barrier, 16-35w), unused label (deleted), for(i<1), while(1){...break;} (18w, keeps the boundary but blocks scheduling), switch(0), if(s), -funroll-loops on a 3-row loop, (k<<1)&1 tests (not folded). */
#include "common.h"
typedef struct { f32 v[4]; } V4f;
typedef struct { f32 c[4]; } Seg;
typedef struct { Seg s[3]; } Seg3;
void func_00249718(V4f *o, Seg3 *s, f32 t) {
    f32 t2 = t * t;
    f32 t3 = t2 * t;
    o->v[0] = s->s[0].c[0] * t3 + s->s[0].c[1] * t2 + s->s[0].c[2] * t + s->s[0].c[3];
    o->v[1] = s->s[1].c[0] * t3 + s->s[1].c[1] * t2 + s->s[1].c[2] * t + s->s[1].c[3];
    o->v[2] = s->s[2].c[0] * t3 + s->s[2].c[1] * t2 + s->s[2].c[2] * t + s->s[2].c[3];
    o->v[3] = 1.0f;
}
