/* The HUD's math helpers, nogcse part (docs/modules.md "Session 46"):
 * func_00249618 builds the Hermite segments (x, y, z) through n points, the
 * tangents from the neighbours (Catmull-Rom; one-sided at the ends). */
#include "common.h"

typedef struct { f32 v[4]; } V4f;
typedef struct { f32 c[4]; } Seg;
typedef struct { Seg s[3]; } Seg3;
void func_002495c8(Seg *, f32, f32, f32, f32);

void func_00249618(Seg3 *dst, V4f *p, s32 n) {
    s32 i, j;
    s32 m = n - 1;
    Seg3 *out = dst;
    for (i = 0; i < m; i++, p++, out++) {
        for (j = 0; j < 3; j++) {
            f32 t0, t1;
            f32 a = p->v[j];
            f32 b = p[1].v[j];
            if (i > 0) t0 = (b - p[-1].v[j]) * 0.5f;
            else t0 = b - a;
            if (i < n - 2) t1 = (p[2].v[j] - p->v[j]) * 0.5f;
            else t1 = t0;
            func_002495c8(&out->s[j], a, b, t0, t1);
        }
    }
}
