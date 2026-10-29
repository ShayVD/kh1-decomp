/* gb.x func_00f3bba0: matched by hand. */
#include "ovl.h"

typedef struct {
    f32 t;
    f32 s;
    f32 pad[2];
    f32 p[4];
    f32 tan[4];
} Key;

typedef struct {
    u8 pad[8];
    s32 n;
    Key *k;
} Spl;

void func_00f3bba0(f32 *out, s32 norm, Spl *sp, f32 t) {
    f32 v[8];
    f32 m[4][4] __attribute__((aligned(16)));
    f32 h[4] __attribute__((aligned(16)));
    Key *k;
    Key *k0;
    Key *k1;
    s32 i;
    s32 n;
    f32 u;
    f32 uu;

    out[3] = 1.0f;
    n = sp->n;
    k = sp->k;
    for (i = 0; i < n; i++) {
        if (t == k[i].t) {
            out[0] = k[i].p[0];
            out[1] = k[i].p[1];
            out[2] = k[i].p[2];
            goto end;
        }
        if (t < k[i].t) {
            break;
        }
    }
    if (i >= n) {
        i = n - 1;
    }
    if (i <= 0) {
        i = 1;
    }
    k0 = &k[i - 1];
    k1 = &k[i];
    m[0][0] = k0->tan[0];
    m[0][1] = k0->tan[1];
    m[0][2] = k0->tan[2];
    m[1][0] = k1->tan[0];
    m[1][1] = k1->tan[1];
    m[1][2] = k1->tan[2];
    m[2][0] = k0->p[0] * k0->s;
    m[2][1] = k0->p[1] * k0->s;
    m[2][2] = k0->p[2] * k0->s;
    m[3][0] = k1->p[0] * k1->s;
    m[3][1] = k1->p[1] * k1->s;
    m[3][2] = k1->p[2] * k1->s;
    u = (t - k0->t) / (k1->t - k0->t);
    uu = u * u;
    h[0] = uu * 6.0f - u * 6.0f;
    h[1] = uu * -6.0f + u * 6.0f;
    h[2] = uu * 3.0f - u * 4.0f + 1.0f;
    h[3] = uu * 3.0f - (u + u);
    sceVu0ApplyMatrix(out, m, h);
    out[3] = 1.0f;
end:
    if (norm) {
        sceVu0Normalize(out, out);
    }
}
