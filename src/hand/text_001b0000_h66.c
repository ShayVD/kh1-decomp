#include "common.h"
#include "data/types/vm_rec.h"
#include "data/bss_0062.h"

double asin(double);
double cos(double);
double atan2(double, double);
f32 acosf(f32);
#include "data/types/fvec.h"
typedef FVec4 V4;
f32 sinf(f32);
f32 sqrtf(f32);
void func_001bf290(f32 *q);
#include "data/pieces/D_0039A580.h"
#include "data/pieces/D_0038D170.h"
extern u32 D_002C5958;
extern f32 D_002BBDFC;
#include "data/pieces/D_0037A380.h"
extern u8 D_00389C90[];

void func_001bea58(f32 *a, f32 *b) {
    s32 i;
    for (i = 0; i < 4; i++) {
        f32 x = a[i], y = b[i];
        f32 xa = x, ya = y;
        double d;
        f32 d1;
        if (x < 0.0f) xa = x + 6.2831850051879883f;
        if (y < 0.0f) ya = y + 6.2831850051879883f;
        d = ya - xa;
        if (d < 0.0) d = 0.0 - d;
        d1 = d;
        d = y - x;
        if (d < 0.0) d = 0.0 - d;
        if (d1 < (f32)d) { a[i] = xa; b[i] = ya; }
        else { a[i] = x; b[i] = y; }
    }
}

void func_001bf0e8(V4 *pos, V4 *rot, f32 *m) {
    f32 rx, ry, rz = 0.0f, c;
    pos->x = m[12];
    pos->y = m[13];
    pos->z = m[14];
    pos->w = 1.0f;
    ry = -asin(m[2]);
    c = cos(ry);
    if (c > -0.0009999999310821295f && c < 0.0009999999310821295f) {
        rx = rz;
        rz = acosf(m[5]);
    } else {
        rx = atan2(m[6], m[10]);
        rz = asin(m[1] / c);
        if (m[0] < 0.0f) rz = 3.1415925621986389f - rz;
    }
    rot->x = rx;
    rot->y = ry;
    rot->z = rz;
    rot->w = 1.0f;
}

void func_001bf3e8(f32 m[4][4], V4 *q) {
    m[0][0] = 1.0f - 2.0f * (q->y * q->y + q->z * q->z);
    m[1][0] = 2.0f * (q->x * q->y - q->w * q->z);
    m[2][0] = 2.0f * (q->x * q->z + q->w * q->y);
    m[3][0] = 0.0f;
    m[0][1] = 2.0f * (q->x * q->y + q->w * q->z);
    m[1][1] = 1.0f - 2.0f * (q->x * q->x + q->z * q->z);
    m[2][1] = 2.0f * (q->y * q->z - q->w * q->x);
    m[3][1] = 0.0f;
    m[0][2] = 2.0f * (q->x * q->z - q->w * q->y);
    m[1][2] = 2.0f * (q->y * q->z + q->w * q->x);
    m[2][2] = 1.0f - 2.0f * (q->x * q->x + q->y * q->y);
    m[3][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;
}

void func_001bf710(f32 *d, f32 *a, f32 *b, f32 t) {
    f32 th, s, sa, sb;
    s32 i;
    th = acosf(a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3]);
    s = sinf(th);
    sa = sinf(th * (1.0f - t));
    sb = sinf(th * t);
    if (s > -0.01f && s < 0.01f) {
        d[0] = a[0];
        d[1] = a[1];
        d[2] = a[2];
        d[3] = a[3];
        return;
    }
    s = 1.0f / s;
    for (i = 0; i < 4; i++) d[i] = (a[i] * sa + b[i] * sb) * s;
}

void func_001bf888(f32 *q, f32 m[4][4]) {
    s32 i, j, k;
    f32 s, t; f32 *p;
    i = 0;
    if (m[1][1] > m[0][0]) i = 1;
    if (m[2][2] > m[i][i]) i = 2;
    j = (i + 1) % 3;
    k = (j + 1) % 3;

    q[i] = s = sqrtf(m[i][i] - m[j][j] - m[k][k] + 1.0f) * 0.5f;
    if (s == 0.0f) {
        func_001bf290(q);
        return;
    }
    t = s * 4.0f;
    q[j] = (m[i][j] + m[j][i]) / t;
    q[k] = (m[i][k] + m[k][i]) / t;
    q[3] = (m[j][k] - m[k][j]) / t;
}

/* func_001c5168, func_001c5b88, func_001c6720 and func_001c6890 are in src/camera/camera.c. */

/* func_001c91e8, func_001c9ac8, func_001c9e80 and func_001ca800 are in src/camera/camera.c. */
#include "data/data_002B.h"
#include "data/data_002E.h"
#include "data/data_0037.h"
#include "data/data_0038.h"
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003C.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDFC.h"
