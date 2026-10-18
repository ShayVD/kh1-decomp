/* 00249718: 3 LCS words off (10 pos), hand, no context (s9 drafts 12w). NEW: identical if/else arms around everything after t2 (`if (o) { X } else { X }`, cross-jumped away in jump2, so no extra code) make t2/t3 global pseudos and give the original FP registers everywhere (1.0f f4, t2 f5, t3 f6, rows exact). Left: in this head={t2} arms={t3,rows} shape, mul t3 (ready at cycle 0 in the arm block, highest prio) is issued before the four row-0 loads; the orig issues the loads first (as when t2 and t3 are in the same block). With t2 AND t3 inside the arms (sibling file /tmp/claude-0/s10/w7/near/00249718_8w_alt.c shape) the schedule is exact but global-alloc takes t3 (8 refs, live 46, prio .52) before t2 (10 refs, live 60, .50), so t2/t3 swap f5/f6 (8w). Writing row 2 as c1*t2 + c0*t3 fixes the prio but swaps row-2 loads (4w). Identical arms are odd source: maybe an #ifdef-ed debug difference between the arms in the original. */
#include "common.h"
typedef struct { f32 v[4]; } V4f;
typedef struct { f32 c[4]; } Seg;
typedef struct { Seg s[3]; } Seg3;
void func_00249718(V4f *o, Seg3 *s, f32 t) {
    f32 t2, t3;
    t2 = t * t;
    if (o) { t3 = t2 * t; o->v[0] = s->s[0].c[0] * t3 + s->s[0].c[1] * t2 + s->s[0].c[2] * t + s->s[0].c[3]; o->v[1] = s->s[1].c[0] * t3 + s->s[1].c[1] * t2 + s->s[1].c[2] * t + s->s[1].c[3]; o->v[2] = s->s[2].c[0] * t3 + s->s[2].c[1] * t2 + s->s[2].c[2] * t + s->s[2].c[3]; o->v[3] = 1.0f; } else { t3 = t2 * t; o->v[0] = s->s[0].c[0] * t3 + s->s[0].c[1] * t2 + s->s[0].c[2] * t + s->s[0].c[3]; o->v[1] = s->s[1].c[0] * t3 + s->s[1].c[1] * t2 + s->s[1].c[2] * t + s->s[1].c[3]; o->v[2] = s->s[2].c[0] * t3 + s->s[2].c[1] * t2 + s->s[2].c[2] * t + s->s[2].c[3]; o->v[3] = 1.0f; }
}
