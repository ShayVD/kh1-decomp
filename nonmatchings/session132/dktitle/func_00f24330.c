/* dktitle.x func_00f24330: near-miss draft (session 132), not byte-identical; the port runs it (ovl/dktitle/drafts.tsv). */
#include "ovl.h"


typedef union { kh1_u128 q; u64 ul[2]; s32 i[4]; f32 f[4]; } QW;

static inline void ad2(QW *p, u32 lo, u32 hi, u64 a) { p->ul[1] = a; p->i[0] = lo; p->i[1] = hi; }
static inline void ad(QW *p, u64 d, u64 a) { p->ul[1] = a; p->ul[0] = d; }

QW *func_00f24330(s32 *x, s32 *y, s32 *z, s32 *q, s32 w, s32 h, f32 *s, f32 *t,
                  s32 psm, s32 cbp, s32 col, u8 *rgba, s64 alpha, s32 fbmsk, s64 test, s32 n, QW *pk, s32 tbp) {
    s32 tw, th, i, j;
    s32 r, g, b, a;

    cbp = tbp + cbp;
    tw = 1;
    if (w > 16) tw = 5;
    if (w > 32) tw = 6;
    if (w > 64) tw = 7;
    if (w > 128) tw = 8;
    if (w > 256) tw = 9;
    if (w > 512) tw = 10;
    th = 1;
    if (h > 16) th = 5;
    if (h > 32) th = 6;
    if (h > 64) th = 7;
    if (h > 128) th = 8;
    if (h > 256) th = 9;
    if (h > 512) th = 10;
    pk[0].q = KH1_Q(0);
    if (fbmsk) pk[1].ul[0] = 0x1000000000000008; else pk[1].ul[0] = 0x1000000000000007;
    pk[1].ul[1] = 14;
    ad(&pk[2], 0, 0x3F);
    ad(&pk[3], (u64)tbp | (u64)(w / 64) << 14 | (u64)psm << 20 | (u64)tw << 26 | (u64)th << 30 | (u64)1 << 34 | (u64)cbp << 37 | (u64)1 << 61, 6);
    ad(&pk[4], alpha, 0x42);
    ad(&pk[5], test, 0x47);
    ad(&pk[6], 0, 0x49);
    ad2(&pk[7], 0x7000, 0x7400, 0x18);
    ad(&pk[8], 0x60, 0x14);
    i = 9;
    if (fbmsk) {
        ad(&pk[i], (u64)fbmsk << 32 | 0x800D0, 0x4C);
        i++;
        if (n == 3) pk[i].ul[0] = (u64)9 << 60 | (u64)0x13 << 47 | (u64)1 << 46 | 1;
        else pk[i].ul[0] = (u64)(n * 3) << 60 | (u64)0x14 << 47 | (u64)1 << 46 | 1;
    } else {
        if (n == 3) pk[i].ul[0] = (u64)9 << 60 | (u64)0x53 << 47 | (u64)1 << 46 | 0x8001;
        else pk[i].ul[0] = (u64)(n * 3) << 60 | (u64)0x54 << 47 | (u64)1 << 46 | 0x8001;
    }
    pk[i++].ul[1] = 0x412412412412;
    if (col) {
        r = rgba[0]; g = rgba[1]; b = rgba[2]; a = rgba[3];
    } else {
        r = 64; g = 64; b = 64; a = 96;
    }
    for (j = 0; j < n; j++) {
        f32 qf = q[j];
        pk[i].f[0] = s[j] / qf;
        pk[i].f[1] = t[j] / qf;
        pk[i].f[2] = 1.0f / qf;
        pk[i].i[3] = 0;
        i++;
        pk[i].i[0] = r; pk[i].i[1] = g; pk[i].i[2] = b; pk[i].i[3] = a;
        i++;
        pk[i].i[0] = x[j]; pk[i].i[1] = y[j]; pk[i].i[2] = 0xFFFFFF; pk[i].i[3] = 0;
        i++;
    }
    if (fbmsk) {
        ad(&pk[i], 0x1000000000008001, 14);
        i++;
        ad(&pk[i], 0x800D0, 0x4C);
        i++;
    }
    pk[0].i[0] = (i - 1) | 0x10000000;
    return &pk[i];
}
