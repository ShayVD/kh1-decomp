/* 10w off, mode hand/nostrict_nogcse (or hand/nogcse; -fno-gcse needed for the q[0] reload): only global-alloc swap out<->p<->slt(i<n-2): orig out=s4,slt=s5,p=s6; ours slt=s4,p=s5,out=s6. */
#include "common.h"
typedef struct { f32 v[4]; } V4f;
typedef struct { f32 c[4]; } Seg;
typedef struct { Seg s[3]; } Seg3;
void func_002495c8(Seg *, f32, f32, f32, f32);
void func_00249618(Seg3 *out, V4f *p, s32 n) {
    s32 i, j;
    s32 m = n - 1;
    for (i = 0; i < m; i++, out++, p++) {
        Seg *o = out->s;
        f32 *q = p->v;
        for (j = 0; j < 3; j++, o++, q++) {
            f32 t0, t1;
            f32 a = q[0];
            f32 b = q[4];
            if (i > 0) t0 = (b - q[-4]) * 0.5f;
            else t0 = b - a;
            if (i < n - 2) t1 = (q[8] - q[0]) * 0.5f;
            else t1 = t0;
            func_002495c8(o, a, b, t0, t1);
        }
    }
}
