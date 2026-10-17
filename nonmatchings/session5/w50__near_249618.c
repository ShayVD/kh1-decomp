#include "common.h"
typedef struct { f32 v[4]; } V4f;
typedef struct { f32 c[4]; } Seg;
typedef struct { Seg s[3]; } Seg3;
void func_002495c8(Seg *, f32, f32, f32, f32);
void func_00249618(Seg3 *out, V4f *p, s32 n) {
    s32 i, j;
    for (i = 0; i < n - 1; i++, out++, p++) {
        Seg *o = out->s;
        f32 *q = p->v;
        for (j = 0; j < 3; j++, o++, q++) {
            f32 t0, t1;
            if (i > 0) t0 = (q[4] - q[-4]) * 0.5f;
            else t0 = q[4] - q[0];
            if (i < n - 2) t1 = (q[8] - q[0]) * 0.5f;
            else t1 = t0;
            func_002495c8(o, q[0], q[4], t0, t1);
        }
    }
}
