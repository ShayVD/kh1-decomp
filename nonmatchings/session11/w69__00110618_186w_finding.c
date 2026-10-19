/* 00110618 FINDING (186 LCS, hand, 1064 vs 1072: worse than w21 158w; saved for the finding only). The original computes fb - n (sub.s $f28,$f24,$f21) at the top, before the first sceVu0UnitMatrix call. sched1 only moves an insn across calls when its pseudos already cross a call (REG_N_CALLS_CROSSED > 0): in the w21 natural draft fb - n (r146) is born after the first MulMatrix and dies before the next call, so insn 201 gets deps on calls 78/111/148 and stays late. An explicit early "f32 fbn = fb - n;" used by the second ViewScreen body crosses calls and sched1 hoists the fb load and fb - n to the top like the original; but it also loses 2 insns (vcm(m1) shares it) and reshuffles the FP allocation. The original likely computes it in a shape that crosses a call without being CSEd away. */
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
    f32 sxd = n * 320.0f / d;
    f32 syd = n * 229.0f / d;
    f32 sx2, sy2;
    f32 fbn = fb - n;

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
    mt[0][0] = a;
    mt[1][1] = px;
    mt[2][2] = az;
    mt[3][0] = py;
    mt[3][1] = pz;
    mt[3][2] = cz;
    sceVu0MulMatrix(m2, mt, m2);
    vcm(m3, sxd * 2.0f, syd * 2.0f, n, n, fa);
    cz = (-r * n + l * fb) / fbn;
    az = fb * n * (-l + r) / fbn;
    sceVu0UnitMatrix(m0);
    m0[0][0] = d;
    m0[1][1] = d;
    m0[2][2] = 0.0f;
    m0[3][3] = 0.0f;
    m0[3][2] = 1.0f;
    m0[2][3] = 1.0f;
    sceVu0UnitMatrix(mt);
    mt[0][0] = a;
    mt[1][1] = px;
    mt[2][2] = az;
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
    m5[1][1] = d * px * sy2 / n;
    m5[2][2] = (l - r) * 0.5f;
    m5[3][0] = py;
    m5[3][1] = pz;
    m5[3][2] = (r + l) * 0.5f;
    m5[3][3] = 1.0f;
}
