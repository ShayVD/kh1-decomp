/* gb.x func_00f3bda8: matched by hand. */
#include "ovl.h"

typedef struct { f32 t; f32 s; f32 pad[2]; OvlVec tan; OvlVec pos; } GbKey;
typedef struct { u8 pad[8]; s32 n; GbKey *keys; } GbCurve;
void sceVu0ApplyMatrix(f32 *, OvlMtx, f32 *);

void func_00f3bda8(f32 t, f32 *out, GbCurve *c) {
    OvlVec p0;
    OvlVec p1;
    OvlMtx m;
    OvlVec h;
    GbKey *k = c->keys;
    GbKey *a, *b;
    f32 u, u2, u3;
    s32 i, n;
    n = c->n;
    for (i = 0; i < n; i++) {
        if (t == k[i].t) {
            out[0] = k[i].pos[0];
            out[1] = k[i].pos[1];
            out[2] = k[i].pos[2];
            out[3] = 1.0f;
            return;
        }
        if (t < k[i].t)
            break;
    }
    if (i >= n)
        i = n - 1;
    if (i <= 0)
        i = 1;
    a = &k[i - 1];
    b = &k[i];
    m[0][0] = a->pos[0];
    m[0][1] = a->pos[1];
    m[0][2] = a->pos[2];
    m[1][0] = b->pos[0];
    m[1][1] = b->pos[1];
    m[1][2] = b->pos[2];
    m[2][0] = a->tan[0] * a->s;
    m[2][1] = a->tan[1] * a->s;
    m[2][2] = a->tan[2] * a->s;
    m[3][0] = b->tan[0] * b->s;
    m[3][1] = b->tan[1] * b->s;
    m[3][2] = b->tan[2] * b->s;
    u = (t - a->t) / (b->t - a->t);
    u2 = u * u;
    u3 = u2 * u;
    h[0] = 2 * u3 - 3 * u2 + 1.0f;
    h[1] = -2 * u3 + 3 * u2;
    h[2] = u3 - 2 * u2 + u;
    h[3] = u3 - u2;
    sceVu0ApplyMatrix(out, m, h);
    out[3] = 1.0f;
}
