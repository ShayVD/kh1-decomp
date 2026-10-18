/* 00110618 158w LCS (climbed store order; 163 with the natural SDK statement order, near/00110618_163w_natural.c), mode hand, 1072 vs 1072 (right size), no context. FINDING (s11w21): the body is two sceVu0ViewScreenMatrix bodies written out (SDK expression shapes: cz = (-zmax*nearz + zmin*farz)/(-nearz+farz); az = farz*nearz*(-zmin+zmax)/(-nearz+farz); one function-level work matrix mt and one az/cz pair) plus three static inline sceVu0ViewClipMatrix calls (scrw = sxd*2.0f; az = zmax*zmin*-2.0f/(zmax-zmin)). Opcode multiset is identical to the original and the spill set is exactly the original's (px,py,pz,l,r at 64..80, rn 84, w 88, n2 92, with rn/w stored and reloaded at once as in the original). Inline vsm too gives 1068 bytes (param copies) and an inline-local Mtx gives a 320-byte frame. Left: local-alloc (single block: every FP pseudo is local-alloc's) hands out f20.. in qty priority order: ours fa f20, d f22, n f23, fan f24; original d f20, n f21, fan f22, fa f23, fb f24, a f25. Expression forms, declaration order and az/cz order are all insensitive (canonicalised). The s10 w14 probe (136, unnatural order, flat temps) stays lower by LCS. */
#include "common.h"
typedef f32 Mtx[4][4] __attribute__((aligned(16)));
void sceVu0UnitMatrix(Mtx);
void sceVu0MulMatrix(Mtx, Mtx, Mtx);

static inline void vcm(Mtx vc, f32 scrw, f32 scrh, f32 scrz, f32 zmin, f32 zmax) {
    f32 az, cz;
    cz = (zmax + zmin) / (zmax - zmin);
    az = zmax * zmin * -2.0f / (zmax - zmin);
    sceVu0UnitMatrix(vc);
    vc[1][1] = 2.0f * scrz / scrh;
    vc[2][3] = 1.0f;
    vc[2][2] = cz;
    vc[3][2] = az;
    vc[0][0] = 2.0f * scrz / scrw;
    vc[3][3] = 0.0f;
}

void func_00110618(Mtx m0, Mtx m1, Mtx m2, Mtx m3, Mtx m4, Mtx m5,
                   f32 d, f32 a, f32 px, f32 py, f32 pz, f32 l, f32 r, f32 n, f32 fb, f32 fa) {
    Mtx mt;
    f32 az, cz;
    f32 sxd = n * 320.0f / d;
    f32 syd = n * 229.0f / d;
    f32 sx2, sy2;

    cz = (-r * n + l * fa) / (-n + fa);
    az = fa * n * (-l + r) / (-n + fa);
    sceVu0UnitMatrix(m2);
    m2[0][0] = d;
    m2[1][1] = d;
    m2[2][2] = 0.0f;
    m2[3][3] = 0.0f;
    m2[3][2] = 1.0f;
    m2[2][3] = 1.0f;
    sceVu0UnitMatrix(mt);
    mt[3][0] = py;
    mt[2][2] = az;
    mt[3][1] = pz;
    mt[0][0] = a;
    mt[1][1] = px;
    mt[3][2] = cz;
    sceVu0MulMatrix(m2, mt, m2);
    vcm(m3, sxd * 2.0f, syd * 2.0f, n, n, fa);
    az = fb * n * (-l + r) / (-n + fb);
    cz = (-r * n + l * fb) / (-n + fb);
    sceVu0UnitMatrix(m0);
    m0[3][2] = 1.0f;
    m0[0][0] = d;
    m0[2][2] = 0.0f;
    m0[2][3] = 1.0f;
    m0[1][1] = d;
    m0[3][3] = 0.0f;
    sceVu0UnitMatrix(mt);
    mt[0][0] = a;
    mt[2][2] = az;
    mt[1][1] = px;
    mt[3][0] = py;
    mt[3][1] = pz;
    mt[3][2] = cz;
    sceVu0MulMatrix(m0, mt, m0);
    vcm(m1, sxd * 2.0f, syd * 2.0f, n, n, fb);
    sx2 = n * 2045.0f / d;
    sy2 = n * 360.5f / d;
    vcm(m4, sx2 * 2.0f, sy2 * 2.0f, n, n, fb);
    sceVu0UnitMatrix(m5);
    m5[0][0] = d * a * sx2 / n;
    m5[3][0] = py;
    m5[1][1] = d * px * sy2 / n;
    m5[2][2] = (l - r) * 0.5f;
    m5[3][1] = pz;
    m5[3][3] = 1.0f;
    m5[3][2] = (r + l) * 0.5f;
}
