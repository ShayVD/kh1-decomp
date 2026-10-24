/* Matrix helpers of the model code, without strict aliasing
 * (docs/modules.md "Session 52"): rotation and scale matrices
 * (func_001625c8, func_001626f0, func_001628a0), func_00162ab8 and the
 * look-at style builder func_00162d00.  The VU0 routines stay in
 * src/hand/vu0.c.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "platform/math.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_00351BC8.h"
#include "data/types/nostrict_text_00150000_h36.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/types/nostrict_text_00150000_h59.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_003519E0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/types/nostrict_text_00140000_b04.h"

/* func_001625c8 (from hand/nostrict/text_00150000_h36.c). */
f32 func_00162c20(f32 *);
void func_001625c8(f32 (*src)[4], f32 (*dst)[4]) {
    f32 sx, sy, sz;
    f32 v[4];
    f32 z;
    PlatVu0CopyMatrix(dst, src);
    sx = func_00162c20(dst[0]);
    sy = func_00162c20(dst[1]);
    sz = func_00162c20(dst[2]);
    PlatVu0TransposeMatrix(dst, dst);
    dst[0][3] = dst[1][3] = dst[2][3] = dst[3][0] = dst[3][1] = dst[3][2] = 0.0f;
    dst[3][3] = 1.0f;
    PlatVu0DivVectorXYZ(dst[0], dst[0], sx);
    PlatVu0DivVectorXYZ(dst[1], dst[1], sy);
    PlatVu0DivVectorXYZ(dst[2], dst[2], sz);
    PlatVu0ApplyMatrix(v, dst, src[3]);
    dst[3][0] = -v[0];
    dst[3][1] = -v[1];
    dst[3][2] = -v[2];
}

/* func_001626f0 (from hand/nostrict/text_00150000_h36.c). */
void func_001626f0(f32 *scale, f32 *rot, f32 *trans, f32 (*m)[4]) {
    s32 i;
    f32 z;
    PlatVu0UnitMatrix(m);
    for (i = 0; i < 3; i++) m[i][i] = scale[i];
    if (rot[0] != 0.0f) PlatVu0RotMatrixX(m, m, rot[0]);
    if (rot[1] != 0.0f) PlatVu0RotMatrixY(m, m, rot[1]);
    if (rot[2] != 0.0f) PlatVu0RotMatrixZ(m, m, rot[2]);
    m[3][0] = trans[0];
    m[3][1] = trans[1];
    m[3][2] = trans[2];
}

/* func_001628a0 (from hand/nostrict/text_00150000_h36.c). */
void func_001628a0(f32 (*dst)[4], f32 (*src)[4], f32 *out) {
    PlatVu0CopyMatrix(dst, src);
    out[0] = PlatSqrtf(PlatVu0InnerProduct(dst[0], dst[0]));
    out[1] = PlatSqrtf(PlatVu0InnerProduct(dst[1], dst[1]));
    out[2] = PlatSqrtf(PlatVu0InnerProduct(dst[2], dst[2]));
    PlatVu0DivVectorXYZ(dst[0], dst[0], out[0]);
    PlatVu0DivVectorXYZ(dst[1], dst[1], out[1]);
    PlatVu0DivVectorXYZ(dst[2], dst[2], out[2]);
}

/* func_001629e8 (from hand/nostrict/text_00150000_s6_08.c). */
f32 func_001629e8(void) {
    u32 r;
    __asm__ volatile(
        "qmtc2 %1, $vf1\n"
        "vrnext.w $vf2w, R\n"
        "vitof0.x $vf1x, $vf1x\n"
        "vsub.w $vf2w, $vf2w, $vf0w\n"
        "vmulw.x $vf1x, $vf1x, $vf2w\n"
        "vftoi0.x $vf1x, $vf1x\n"
        "qmfc2 %0, $vf1\n"
        : "=r"(r)
        : "r"(30001));
    return (f32)r / 30000.0f;
}

/* func_00162ab8 (from hand/nostrict/text_00150000_h59.c). */
s32 func_00162ab8(f32 *p0, f32 *p1, f32 *q0, f32 *q1, f32 *out) {
    f32 m[4];
    f32 n[4];
    f32 a[4];
    f32 b[4];
    f32 da, db;
    PlatVu0AddVector(m, q0, q1);
    PlatVu0ScaleVector(m, m, 0.5f);
    n[0] = q1[1] - m[1];
    n[1] = m[0] - q1[0];
    PlatVu0SubVector(a, p0, m);
    PlatVu0SubVector(b, p1, m);
    da = PlatVu0InnerProduct(a, n);
    db = PlatVu0InnerProduct(b, n);
    if (da * db >= 0.0f) return 0;
    db = fabsf(db);
    da = fabsf(da);
    PlatVu0ScaleVector(a, p0, db);
    PlatVu0ScaleVector(b, p1, da);
    PlatVu0AddVector(out, a, b);
    PlatVu0ScaleVector(out, out, 1.0f / (da + db));
    return 1;
}

/* func_00162d00 (from hand/nostrict/text_00140000_b04.c). */
void func_00162c5c(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_00162d00(f32 *tgt, s32 flip, f32 (*m0)[4], f32 (*m1)[4], f32 *pole, f32 l1, f32 l2, f32 rot, f32 rot2) {
    f32 d[4];
    f32 u[4];
    f32 w[4];
    f32 p[4];
    f32 m[4][4];
    f32 r[4][4];
    f32 n[4][4];
    f32 dist;
    f32 c;
    f32 s;
    f32 x;
    f32 y;
    f32 t;

    p[0] = m0[3][0];
    p[1] = m0[3][1];
    p[2] = m0[3][2];
    d[0] = tgt[0] - p[0];
    d[1] = tgt[1] - p[1];
    d[2] = tgt[2] - p[2];
    dist = func_00162c20(d);
    if (pole) {
        u[0] = pole[0] - p[0];
        u[1] = pole[1] - p[1];
        u[2] = pole[2] - p[2];
        func_00162c20(u);
        PlatVu0OuterProduct(w, d, u);
        func_00162c20(w);
        PlatVu0OuterProduct(u, w, d);
        func_00162c20(u);
    } else {
        u[0] = -d[1];
        u[1] = d[0];
        u[2] = 0.0f;
        func_00162c20(u);
        PlatVu0OuterProduct(w, d, u);
        PlatVu0Normalize(w, w);
    }
    m[0][3] = 0.0f;
    m[0][0] = d[0];
    m[0][1] = d[1];
    m[0][2] = d[2];
    m[1][0] = u[0];
    m[1][1] = u[1];
    m[1][2] = u[2];
    m[1][3] = 0.0f;
    m[2][0] = w[0];
    m[2][1] = w[1];
    m[2][2] = w[2];
    m[2][3] = 0.0f;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
    if (rot != 0.0f) {
        PlatVu0UnitMatrix(r);
        PlatVu0RotMatrixX(r, r, rot);
        func_00162c5c(m, m, r);
    }
    if (!m1) {
        PlatVu0CopyMatrix(m0, m);
        m0[3][0] = p[0];
        m0[3][1] = p[1];
        m0[3][2] = p[2];
        return;
    }
    c = (dist * dist - l1 * l1 - l2 * l2) / ((l1 + l1) * l2);
    if (c > 1.0f) {
        c = 1.0f;
    } else if (c < -1.0f) {
        c = -1.0f;
    }
    t = 1.0f - c * c;
    if (t < 0.0f) t = 0.0f;
    if (flip) {
        s = -PlatSqrtf(t);
    } else {
        s = PlatSqrtf(t);
    }
    m1[0][2] = 0.0f;
    m1[0][0] = c;
    m1[1][0] = -s;
    m1[0][1] = s;
    m1[0][3] = 0.0f;
    m1[1][1] = c;
    m1[1][2] = 0.0f;
    m1[1][3] = 0.0f;
    m1[2][0] = 0.0f;
    m1[2][1] = 0.0f;
    m1[2][2] = 1.0f;
    m1[2][3] = 0.0f;
    m1[3][0] = l1;
    m1[3][1] = 0.0f;
    m1[3][2] = 0.0f;
    m1[3][3] = 1.0f;
    if (rot2 != 0.0f) {
        PlatVu0UnitMatrix(r);
        PlatVu0RotMatrixX(r, r, rot2);
        func_00162c5c(m1, m1, r);
    }
    y = -(l2 * s) * dist;
    x = (l1 + l2 * c) * dist;
    dist = PlatSqrtf(x * x + y * y);
    y = y / dist;
    x = x / dist;
    n[0][0] = x;
    n[0][1] = y;
    n[0][2] = 0.0f;
    n[0][3] = 0.0f;
    n[1][0] = -y;
    n[1][1] = x;
    n[1][2] = 0.0f;
    n[1][3] = 0.0f;
    n[2][0] = 0.0f;
    n[2][1] = 0.0f;
    n[2][2] = 1.0f;
    n[2][3] = 0.0f;
    n[3][0] = 0.0f;
    n[3][1] = 0.0f;
    n[3][2] = 0.0f;
    n[3][3] = 1.0f;
    func_00162c5c(m0, m, n);
    m0[3][0] = p[0];
    m0[3][1] = p[1];
    m0[3][2] = p[2];
}

