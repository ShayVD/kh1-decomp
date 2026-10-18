/* 00249718 alt: 8 LCS, hand. Arms contain t2 = t*t; t3 = t2*t too: schedule exact, only t2/t3 f5/f6 swapped (global-alloc prio t3 .52 > t2 .50; need t2 live <= 1.25*t3 live or t2 refs >= 11). */
#include "common.h"
typedef struct { f32 v[4]; } V4f;
typedef struct { f32 c[4]; } Seg;
typedef struct { Seg s[3]; } Seg3;
void func_00249718(V4f *o, Seg3 *s, f32 t) {
    f32 t2, t3;
    if (o) { t2 = t * t; t3 = t2 * t; o->v[0] = s->s[0].c[0] * t3 + s->s[0].c[1] * t2 + s->s[0].c[2] * t + s->s[0].c[3]; o->v[1] = s->s[1].c[0] * t3 + s->s[1].c[1] * t2 + s->s[1].c[2] * t + s->s[1].c[3]; o->v[2] = s->s[2].c[0] * t3 + s->s[2].c[1] * t2 + s->s[2].c[2] * t + s->s[2].c[3]; o->v[3] = 1.0f; } else { t2 = t * t; t3 = t2 * t; o->v[0] = s->s[0].c[0] * t3 + s->s[0].c[1] * t2 + s->s[0].c[2] * t + s->s[0].c[3]; o->v[1] = s->s[1].c[0] * t3 + s->s[1].c[1] * t2 + s->s[1].c[2] * t + s->s[1].c[3]; o->v[2] = s->s[2].c[0] * t3 + s->s[2].c[1] * t2 + s->s[2].c[2] * t + s->s[2].c[3]; o->v[3] = 1.0f; }
}
