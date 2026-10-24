/* Two texture spots slid over triangle meshes, default flags
 * (docs/modules.md "Session 51"): func_00174fc0 intersects a segment with a
 * list of triangles and returns the hit's texture coordinates, and
 * func_00175820 a segment with a plane.  texspot.nostrict.c moves the two
 * spots toward a target (func_001752a0), loads the meshes and the GS packet
 * from a file (func_00175708) and draws them (func_00175600).  What the spots
 * show (perhaps a model's eyes) is a guess.  Read from the code, not proved
 * by a boot. */
#include "common.h"
#include "data/types/text_00160000_b05.h"
#include "data/pieces/D_0035C490.h"
#include "data/types/text_00170000_h38.h"
#include "data/types/text_00170000_h38_p.h"

/* func_00174fc0 (from hand/text_00160000_b05.c). */
typedef struct { f32 x, y, z; } V3;
typedef struct {
    V4 pl; V4 org; V4 e[3]; f32 uv0[4]; f32 uv1[4]; f32 uv2[4];
} Tri;
extern V4 D_0035C660[];
f32 func_00162950(V3 *, void *);
void func_00267530(void *, void *, void *);
void func_002675a8(void *, void *);
void func_002672f8(f32 *, f32 (*)[4], V4 *);
s32 func_00162ab8(V4 *, f32 *, V4 *, V4 *, f32 *);
void func_002674f0(f32 *, f32 *, V4 *, f32);
static inline s32 inl_00175820(V3 *a, V3 *b, void *pl, V4 *out) {
    f32 da = func_00162950(a, pl);
    f32 db = func_00162950(b, pl);
    f32 t;
    if (fabsf(da - db) < 1.17549449095213395e-38f) return 0;
    t = -da / (db - da);
    out->x = (b->x - a->x) * t + a->x;
    out->y = (b->y - a->y) * t + a->y;
    out->z = (b->z - a->z) * t + a->z;
    out->w = 1.0f;
    return 1;
}
static inline void inl_uv(Tri *t, f32 u, f32 v, f32 *out, f32 s) {
    f32 uv[4];
    f32 tmp[4];
    u32 j;
    uv[3] = uv[2] = 0.0f;
    out[0] = uv[0] = (t->uv1[0] - t->uv0[0]) * u + (t->uv2[0] - t->uv0[0]) * v + t->uv0[0];
    uv[1] = out[1] = (t->uv1[1] - t->uv0[1]) * u + (t->uv2[1] - t->uv0[1]) * v + t->uv0[1];
    for (j = 0; j < 8; j++) {
        if (func_00162ab8(&D_0035C490, uv, &D_0035C660[j], &D_0035C660[j + 1], tmp)) func_002675a8(uv, tmp);
    }
    func_002674f0(uv, uv, &D_0035C490, s);
    out[0] = uv[0];
    out[1] = uv[1];
}
s32 func_00174fc0(V3 *a, V3 *b, Tri *t, s32 n, f32 *out, f32 s) {
    f32 m[4][4];
    V4 h;
    f32 r[4];
    f32 d[4];
    s32 i;
    f32 u, v;
    func_00267530(d, b, a);
    m[3][0] = m[3][1] = m[3][2] = m[3][3] = 0.0f;
    for (i = 0; i < n; i++, t++) {
        if (!inl_00175820(a, b, t, &h)) continue;
        func_002675a8(m[0], &t->e[0]);
        func_002675a8(m[1], &t->e[1]);
        func_002675a8(m[2], &t->e[2]);
        func_00267530(&h, &h, &t->org);
        func_002672f8(r, m, &h);
        if (0.0f <= r[0] && r[0] <= 1.0f && 0.0f <= r[1] && r[1] <= 1.0f && r[0] + r[1] <= 1.0f) {
            inl_uv(t, r[0], r[1], out, s);
            return 1;
        }
    }
    return 0;
}

/* func_00175820 (from hand/text_00170000_h38.c). */
s32 func_00175820(V3 *a, V3 *b, void *pl, V4 *out) {
    f32 da = func_00162950(a, pl);
    f32 db = func_00162950(b, pl);
    f32 t;
    if (fabsf(da - db) < 1.17549449095213395e-38f) return 0;
    t = -da / (db - da);
    out->x = (b->x - a->x) * t + a->x;
    out->y = (b->y - a->y) * t + a->y;
    out->z = (b->z - a->z) * t + a->z;
    out->w = 1.0f;
    return 1;
}

