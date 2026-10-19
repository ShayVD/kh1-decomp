/* 00110618 near miss: 103 words off by lchk difflib LCS (was 158, w21), 93 orig-unmatched by true DP LCS (was 149 w21 / 135 w14 probe); size 1088 vs 1072; mode hand (strict), no context. New (s12w6): (1) sx2/sy2 are the SAME variables as sxd/syd (one global pseudo set twice: orig sxd and sx2 both f28, syd and sy2 both f29), which puts d f20, n f21, fa f23 like the original; (2) an early f32 fbn = -n + fb used by the second ViewScreen body (orig computes fb - n before the first call) gives a f25 like the original. Statement order hill-climbed (true LCS, calls fixed): matrix-store order is not natural. Left: fb (stack param, REG_EQUIV mem) gets no register (orig f24) and is reloaded from 256(sp) three times (+4 words), fbn lands in f24 (orig fb-n f28), sxd/syd vs cz/az pairs: sxd f31 syd f29 cz f28 az f26 (orig sxd f28 syd f29 cz f30 az f31). */
/* 00110618 163w LCS, hand, 1072 vs 1072: natural-order version of near/00110618_158w.c (see its header). */
#include "common.h"
typedef f32 Mtx[4][4] __attribute__((aligned(16)));
void sceVu0UnitMatrix(Mtx);
void sceVu0MulMatrix(Mtx, Mtx, Mtx);

static inline void vcm(Mtx vc, f32 scrw, f32 scrh, f32 scrz, f32 zmin, f32 zmax) {
    f32 az, cz;
    cz = (zmax + zmin) / (zmax - zmin);
    az = zmax * zmin * -2.0f / (zmax - zmin);
    sceVu0UnitMatrix(vc);
    vc[0][0] = 2.0f * scrz / scrw;
    vc[1][1] = 2.0f * scrz / scrh;
    vc[2][2] = cz;
    vc[3][2] = az;
    vc[2][3] = 1.0f;
    vc[3][3] = 0.0f;
}

void func_00110618(Mtx m0, Mtx m1, Mtx m2, Mtx m3, Mtx m4, Mtx m5,
                   f32 d, f32 a, f32 px, f32 py, f32 pz, f32 l, f32 r, f32 n, f32 fb, f32 fa) {
    Mtx mt;
    f32 az, cz;
    f32 sxd, syd, fbn;

    sxd = n * 320.0f / d;
    syd = n * 229.0f / d;
    fbn = -n + fb;
    cz = (-r * n + l * fa) / (-n + fa);
    az = fa * n * (-l + r) / (-n + fa);
    sceVu0UnitMatrix(m2);
    m2[2][2] = 0.0f;
    m2[0][0] = d;
    m2[1][1] = d;
    m2[3][2] = 1.0f;
    sceVu0UnitMatrix(mt);
    mt[0][0] = a;
    m2[2][3] = 1.0f;
    mt[3][0] = py;
    mt[3][1] = pz;
    mt[3][2] = cz;
    mt[2][2] = az;
    mt[1][1] = px;
    m2[3][3] = 0.0f;
    sceVu0MulMatrix(m2, mt, m2);
    vcm(m3, sxd * 2.0f, syd * 2.0f, n, n, fa);
    cz = (-r * n + l * fb) / fbn;
    az = fb * n * (-l + r) / fbn;
    sceVu0UnitMatrix(m0);
    m0[3][2] = 1.0f;
    m0[2][2] = 0.0f;
    m0[2][3] = 1.0f;
    m0[0][0] = d;
    m0[1][1] = d;
    m0[3][3] = 0.0f;
    sceVu0UnitMatrix(mt);
    mt[0][0] = a;
    mt[1][1] = px;
    mt[3][0] = py;
    mt[2][2] = az;
    mt[3][2] = cz;
    mt[3][1] = pz;
    sceVu0MulMatrix(m0, mt, m0);
    vcm(m1, sxd * 2.0f, syd * 2.0f, n, n, fb);
    sxd = n * 2045.0f / d;
    syd = n * 360.5f / d;
    vcm(m4, sxd * 2.0f, syd * 2.0f, n, n, fb);
    sceVu0UnitMatrix(m5);
    m5[0][0] = d * a * sxd / n;
    m5[1][1] = d * px * syd / n;
    m5[2][2] = (l - r) * 0.5f;
    m5[3][0] = py;
    m5[3][1] = pz;
    m5[3][2] = (r + l) * 0.5f;
    m5[3][3] = 1.0f;
}
