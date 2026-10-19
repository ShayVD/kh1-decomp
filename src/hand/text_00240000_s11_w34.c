#include "common.h"

/* 00249718 (hand, strict). FLAGGED dead set: `if (t < 0) t2 = 0;` at the top is a one-path
   set of t2 that the real `t2 = t * t;` overwrites; life1 deletes it so it costs no code.
   Without it the function is 11w (6w with an integer test on o). */
typedef struct { f32 v[4]; } V4f;
typedef struct { f32 c[4]; } Seg;
typedef struct { Seg s[3]; } Seg3;
void func_00249718(V4f *o, Seg3 *s, f32 t) {
    f32 t2, t3;
    if (t < 0) t2 = 0; /* dead set (flagged) */
    t2 = t * t;
    t3 = t2 * t;
    o->v[0] = s->s[0].c[0] * t3 + s->s[0].c[1] * t2 + s->s[0].c[2] * t + s->s[0].c[3];
    o->v[1] = s->s[1].c[0] * t3 + s->s[1].c[1] * t2 + s->s[1].c[2] * t + s->s[1].c[3];
    o->v[2] = s->s[2].c[0] * t3 + s->s[2].c[1] * t2 + s->s[2].c[2] * t + s->s[2].c[3];
    o->v[3] = 1.0f;
}
