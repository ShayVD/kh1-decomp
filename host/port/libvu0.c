/* libvu0 in C for every port platform (docs/vita-port-plan.md section 1, vu.h):
 * the sceVu0 routines the game calls through include/platform/vu.h, with the
 * signatures of include/sce/libvu0.h.  Each follows the PS2 library the game
 * links (src/sdk/libvu0/vu0.s and the C parts in src/sdk/), field for field:
 * which lanes it writes, which it copies and which it zeroes.  The VU's own
 * float rules (no denormals, NaN or infinity) are not modelled.  Not part of
 * the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/vu.h"
#include "sce/libvu0.h"

f32 cosf(f32);
f32 sinf(f32);

typedef f32 Mtx[4][4];

/* v0 = m0[0] v1.x + m0[1] v1.y + m0[2] v1.z + m0[3] v1.w */
void sceVu0ApplyMatrix(float *v0, float (*m0)[4], float *v1) {
    PlatVu0Apply(v0, m0, v1);
}

/* row i of m0 = row i of m2 by m1 (m0 may be m1 or m2) */
void sceVu0MulMatrix(float (*m0)[4], float (*m1)[4], float (*m2)[4]) {
    Mtx a, r;
    int i;
    __builtin_memcpy(a, m1, sizeof(a));
    for (i = 0; i < 4; i++)
        PlatVu0Apply(r[i], a, m2[i]);
    __builtin_memcpy(m0, r, sizeof(r));
}

void sceVu0OuterProduct(float *v0, float *v1, float *v2) {
    PlatVu0Cross3(v0, v1, v2);
}

float sceVu0InnerProduct(float *v0, float *v1) {
    return PlatVu0Dot3(v0, v1);
}

/* xyz / |xyz|, w 0 */
void sceVu0Normalize(float *v0, float *v1) {
    PlatVu0Normalize3(v0, v1);
}

void sceVu0TransposeMatrix(float (*m0)[4], float (*m1)[4]) {
    Mtx r;
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            r[i][j] = m1[j][i];
    __builtin_memcpy(m0, r, sizeof(r));
}

/* the inverse of a rigid transform: rows 0-2 the transposed 3x3 (w 0), row 3
 * minus the translation by it, w kept */
void sceVu0InversMatrix(float (*m0)[4], float (*m1)[4]) {
    Mtx r;
    f32 t[4];
    int i, j;
    __builtin_memcpy(t, m1[3], 16);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++)
            r[i][j] = m1[j][i];
        r[i][3] = 0.0f;
    }
    for (j = 0; j < 3; j++)
        r[3][j] = -(r[0][j] * t[0] + r[1][j] * t[1] + r[2][j] * t[2]);
    r[3][3] = t[3];
    __builtin_memcpy(m0, r, sizeof(r));
}

void sceVu0DivVector(float *v0, float *v1, float q) {
    PlatVu0Scale4(v0, v1, 1.0f / q);
}

void sceVu0DivVectorXYZ(float *v0, float *v1, float q) {
    PlatVu0Scale3W(v0, v1, 1.0f / q);
}

/* v1 t + v2 (1 - t) */
void sceVu0InterVector(float *v0, float *v1, float *v2, float t) {
    f32 u = 1.0f - t;
    int i;
    for (i = 0; i < 4; i++)
        v0[i] = v1[i] * t + v2[i] * u;
}

void sceVu0InterVectorXYZ(float *v0, float *v1, float *v2, float t) {
    f32 u = 1.0f - t, w = v1[3];
    int i;
    for (i = 0; i < 3; i++)
        v0[i] = v1[i] * t + v2[i] * u;
    v0[3] = w;
}

void sceVu0AddVector(float *v0, float *v1, float *v2) {
    PlatVu0Add4(v0, v1, v2);
}

void sceVu0SubVector(float *v0, float *v1, float *v2) {
    PlatVu0Sub4(v0, v1, v2);
}

void sceVu0MulVector(float *v0, float *v1, float *v2) {
    int i;
    for (i = 0; i < 4; i++)
        v0[i] = v1[i] * v2[i];
}

void sceVu0ScaleVector(float *v0, float *v1, float t) {
    PlatVu0Scale4(v0, v1, t);
}

void sceVu0ScaleVectorXYZ(float *v0, float *v1, float s) {
    PlatVu0Scale3W(v0, v1, s);
}

/* m1 with tv added to its translation */
void sceVu0TransMatrix(float (*m0)[4], float (*m1)[4], float *tv) {
    f32 t[4];
    int i;
    for (i = 0; i < 3; i++)
        t[i] = m1[3][i] + tv[i];
    t[3] = m1[3][3];
    if (m0 != m1)
        __builtin_memcpy(m0, m1, 48);
    __builtin_memcpy(m0[3], t, 16);
}

void sceVu0CopyVector(float *v0, float *v1) {
    __builtin_memcpy(v0, v1, 16);
}

void sceVu0CopyVectorXYZ(float *v0, float *v1) {
    v0[0] = v1[0];
    v0[1] = v1[1];
    v0[2] = v1[2];
}

void sceVu0CopyMatrix(float (*m0)[4], float (*m1)[4]) {
    __builtin_memcpy(m0, m1, 64);
}

void sceVu0FTOI4Vector(int *v0, float *v1) {
    int i;
    for (i = 0; i < 4; i++)
        v0[i] = PlatVu0Ftoi4(v1[i]);
}

void sceVu0FTOI0Vector(int *v0, float *v1) {
    int i;
    for (i = 0; i < 4; i++)
        v0[i] = PlatVu0Ftoi0(v1[i]);
}

void sceVu0ITOF4Vector(float *v0, int *v1) {
    int i;
    for (i = 0; i < 4; i++)
        v0[i] = (f32)v1[i] / 16.0f;
}

void sceVu0ITOF0Vector(float *v0, int *v1) {
    int i;
    for (i = 0; i < 4; i++)
        v0[i] = (f32)v1[i];
}

void sceVu0UnitMatrix(float (*m0)[4]) {
    __builtin_memset(m0, 0, 64);
    m0[0][0] = m0[1][1] = m0[2][2] = m0[3][3] = 1.0f;
}

/* m0 = each row of m1 by the rotation r (the library takes sin / cos by a
 * series, _sceVu0ecossin; libm's are close to it) */
static void rot_rows(float (*m0)[4], float (*m1)[4], Mtx r) {
    sceVu0MulMatrix(m0, r, m1);
}

/* rows (c, s, 0, 0) (-s, c, 0, 0) (0, 0, 1, 0) (0, 0, 0, 1) */
void sceVu0RotMatrixZ(float (*m0)[4], float (*m1)[4], float rz) {
    Mtx r;
    f32 c = cosf(rz), s = sinf(rz);
    sceVu0UnitMatrix(r);
    r[0][0] = c;
    r[0][1] = s;
    r[1][0] = -s;
    r[1][1] = c;
    rot_rows(m0, m1, r);
}

/* rows (1, 0, 0, 0) (0, c, s, 0) (0, -s, c, 0) (0, 0, 0, 1) */
void sceVu0RotMatrixX(float (*m0)[4], float (*m1)[4], float rx) {
    Mtx r;
    f32 c = cosf(rx), s = sinf(rx);
    sceVu0UnitMatrix(r);
    r[1][1] = c;
    r[1][2] = s;
    r[2][1] = -s;
    r[2][2] = c;
    rot_rows(m0, m1, r);
}

/* rows (c, 0, -s, 0) (0, 1, 0, 0) (s, 0, c, 0) (0, 0, 0, 1) */
void sceVu0RotMatrixY(float (*m0)[4], float (*m1)[4], float ry) {
    Mtx r;
    f32 c = cosf(ry), s = sinf(ry);
    sceVu0UnitMatrix(r);
    r[0][0] = c;
    r[0][2] = -s;
    r[2][0] = s;
    r[2][2] = c;
    rot_rows(m0, m1, r);
}

/* Z, then Y, then X */
void sceVu0RotMatrix(float (*m0)[4], float (*m1)[4], float *rot) {
    sceVu0RotMatrixZ(m0, m1, rot[2]);
    sceVu0RotMatrixY(m0, m0, rot[1]);
    sceVu0RotMatrixX(m0, m0, rot[0]);
}

void sceVu0ClampVector(float *v0, float *v1, float min, float max) {
    int i;
    for (i = 0; i < 4; i++) {
        f32 x = v1[i] > min ? v1[i] : min;
        v0[i] = x < max ? x : max;
    }
}

/* the camera's frame (x = yd x zd, z = zd, y = z x x, all normalized, at p),
 * inverted */
void sceVu0CameraMatrix(float (*m)[4], float *p, float *zd, float *yd) {
    Mtx c;
    f32 t[4];
    sceVu0UnitMatrix(c);
    sceVu0OuterProduct(t, yd, zd);
    sceVu0Normalize(c[0], t);
    sceVu0Normalize(c[2], zd);
    sceVu0OuterProduct(c[1], c[2], c[0]);
    sceVu0TransMatrix(c, c, p);
    sceVu0InversMatrix(m, c);
}

/* the three light directions negated and normalized, transposed */
void sceVu0NormalLightMatrix(float (*m)[4], float *l0, float *l1, float *l2) {
    f32 v[4];
    sceVu0ScaleVector(v, l0, -1.0f);
    sceVu0Normalize(m[0], v);
    sceVu0ScaleVector(v, l1, -1.0f);
    sceVu0Normalize(m[1], v);
    sceVu0ScaleVector(v, l2, -1.0f);
    sceVu0Normalize(m[2], v);
    m[3][0] = m[3][1] = m[3][2] = 0.0f;
    m[3][3] = 1.0f;
    sceVu0TransposeMatrix(m, m);
}

void sceVu0LightColorMatrix(float (*m)[4], float *c0, float *c1, float *c2, float *a) {
    sceVu0CopyVector(m[0], c0);
    sceVu0CopyVector(m[1], c1);
    sceVu0CopyVector(m[2], c2);
    sceVu0CopyVector(m[3], a);
}

void sceVu0ViewScreenMatrix(float (*m)[4], float scrz, float ax, float ay, float cx, float cy,
                            float zmin, float zmax, float nearz, float farz) {
    Mtx mt;
    f32 az, cz;
    cz = (-zmax * nearz + zmin * farz) / (-nearz + farz);
    az = farz * nearz * (-zmin + zmax) / (-nearz + farz);
    sceVu0UnitMatrix(m);
    m[0][0] = scrz;
    m[1][1] = scrz;
    m[2][2] = 0.0f;
    m[3][2] = 1.0f;
    m[2][3] = 1.0f;
    m[3][3] = 0.0f;
    sceVu0UnitMatrix(mt);
    mt[0][0] = ax;
    mt[1][1] = ay;
    mt[2][2] = az;
    mt[3][0] = cx;
    mt[3][1] = cy;
    mt[3][2] = cz;
    sceVu0MulMatrix(m, mt, m);
}

/* as src/sdk/gcc991111_01/text_00260000_s7_w6.c: a parallel light (mode 1)
 * or a point light onto the plane n */
void sceVu0DropShadowMatrix(float (*m)[4], float *n, float lx, float ly, float lz, int mode) {
    f32 nx = n[0], ny = n[1], nz = n[2], d, s;
    if (mode) {
        d = 1.0f - (lx * nx + ly * ny + lz * nz);
        m[0][0] = lx * nx + d;
        m[1][0] = ly * nx;
        m[2][0] = lz * nx;
        m[3][0] = -nx;
        m[0][1] = lx * ny;
        m[1][1] = ly * ny + d;
        m[2][1] = lz * ny;
        m[3][1] = -ny;
        m[0][2] = lx * nz;
        m[1][2] = ly * nz;
        m[2][2] = lz * nz + d;
        m[3][2] = -nz;
        m[0][3] = lx;
        m[1][3] = ly;
        m[2][3] = lz;
        m[3][3] = d - 1.0f;
    } else {
        d = lx * nx + ly * ny + lz * nz;
        s = -1.0f / d;
        m[0][0] = s * (lx * nx - d);
        m[1][0] = s * (ly * nx);
        m[2][0] = s * (lz * nx);
        m[3][0] = s * -nx;
        m[0][1] = s * (lx * ny);
        m[1][1] = s * (ly * ny - d);
        m[2][1] = s * (lz * ny);
        m[3][1] = s * -ny;
        m[0][2] = s * (lx * nz);
        m[1][2] = s * (ly * nz);
        m[2][2] = s * (lz * nz - d);
        m[3][2] = s * -nz;
        m[0][3] = 0.0f;
        m[1][3] = 0.0f;
        m[2][3] = 0.0f;
        m[3][3] = s * -d;
    }
}

/* v1 by m0, xyz divided by w, ftoi4 (z and w ftoi0 when mode is set) */
void sceVu0RotTransPers(int *v0, float (*m0)[4], float *v1, int mode) {
    f32 v[4], q;
    PlatVu0Apply(v, m0, v1);
    q = 1.0f / v[3];
    v[0] *= q;
    v[1] *= q;
    v[2] *= q;
    v0[0] = PlatVu0Ftoi4(v[0]);
    v0[1] = PlatVu0Ftoi4(v[1]);
    v0[2] = mode ? PlatVu0Ftoi0(v[2]) : PlatVu0Ftoi4(v[2]);
    v0[3] = mode ? PlatVu0Ftoi0(v[3]) : PlatVu0Ftoi4(v[3]);
}

/* n vertices (the loop runs once for n 0, as the library's does not check) */
void sceVu0RotTransPersN(int *v0, float (*m0)[4], float *v1, int n, int mode) {
    do {
        sceVu0RotTransPers(v0, m0, v1, mode);
        v0 += 4;
        v1 += 4;
    } while (--n != 0);
}

/* the sticky zero / sign flags (0x40 / 0x80) of x, y, w and 4096 - x,
 * 4096 - y: 0 when the point is inside the 4096 x 4096 screen with w > 0 */
static int clip_screen(const f32 *v) {
    f32 t[5];
    int f = 0, i;
    t[0] = v[0];
    t[1] = v[1];
    t[2] = v[3];
    t[3] = 4096.0f - v[0];
    t[4] = 4096.0f - v[1];
    for (i = 0; i < 5; i++) {
        if (t[i] == 0.0f)
            f |= 0x40;
        if (PlatVu0Bits(t[i]) & 0x80000000)
            f |= 0x80;
    }
    return f;
}

int sceVu0ClipScreen(float *v0) {
    return clip_screen(v0);
}

int sceVu0ClipScreen3(float *v0, float *v1, float *v2) {
    return clip_screen(v0) | clip_screen(v1) | clip_screen(v2);
}

/* 0 as soon as one of the n vertices vm (by ms) is strictly inside the box
 * minv * w .. maxv * w in x and y with minv.w < w < maxv.w, else 1 */
int sceVu0ClipAll(float *minv, float *maxv, float (*ms)[4], float *vm, int n) {
    f32 v[4], t[6];
    int i, f;
    do {
        PlatVu0Apply(v, ms, vm);
        t[0] = v[0] - minv[0] * v[3];
        t[1] = v[1] - minv[1] * v[3];
        t[2] = v[3] - minv[3];
        t[3] = maxv[0] * v[3] - v[0];
        t[4] = maxv[1] * v[3] - v[1];
        t[5] = maxv[3] - v[3];
        f = 0;
        for (i = 0; i < 6; i++)
            if (t[i] == 0.0f || (PlatVu0Bits(t[i]) & 0x80000000))
                f = 1;
        if (!f)
            return 0;
        vm += 4;
    } while (--n != 0);
    return 1;
}

/* the VU0 reset: nothing to do off the EE */
void sceVpu0Reset(void) {}
