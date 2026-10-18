/* 00110618 167w LCS (was 175), mode hand, 1064 vs 1072. Fix: m5[0][0] = d * a * sx2 / n (orig computes d*a right after t[0][0]=a; the s6 draft lacked d). Off: FP allocation; orig computes sxd, syd, n2 and sxd+sxd before the first UnitMatrix and spills px,py,pz,l,r,-r*n,w,n2; ours lets sched2 sink the sxd/syd divs across the calls (callee-saved FP regs do not block sched across calls). Hill-climbing the top statement order gave nothing. */
#include "common.h"
typedef f32 Mtx[4][4] __attribute__((aligned(16)));
void sceVu0UnitMatrix(Mtx);
void sceVu0MulMatrix(Mtx, Mtx, Mtx);

void func_00110618(Mtx m0, Mtx m1, Mtx m2, Mtx m3, Mtx m4, Mtx m5,
                   f32 d, f32 a, f32 px, f32 py, f32 pz, f32 l, f32 r, f32 n, f32 fb, f32 fa) {
    Mtx t;
    f32 w, rn, n2, fan, dfa, dfb, fbn;
    f32 a22, a32, zza, zwa, b22, b32, zzb, zwb;
    f32 sx, sy, sxd, syd, sx2, sy2;
    w = r - l;
    rn = -r * n;
    fan = fa * n;
    dfa = fa - n;
    sxd = n * 320.0f / d;
    syd = n * 229.0f / d;
    n2 = n + n;
    a22 = fan * w / dfa;
    a32 = (rn + l * fa) / dfa;
    zza = (fa + n) / dfa;
    dfb = fb - n;

    sceVu0UnitMatrix(m2);
    m2[0][0] = d;
    m2[3][2] = 1.0f;
    m2[2][3] = 1.0f;
    m2[1][1] = d;
    m2[2][2] = 0.0f;
    m2[3][3] = 0.0f;
    sceVu0UnitMatrix(t);
    t[2][2] = a22;
    t[3][2] = a32;
    t[0][0] = a;
    t[1][1] = px;
    t[3][0] = py;
    t[3][1] = pz;
    sceVu0MulMatrix(m2, t, m2);

    sceVu0UnitMatrix(m3);
    m3[3][3] = 0.0f;
    m3[2][3] = 1.0f;
    zwa = fan * -2.0f / dfa;
    sx = n2 / (sxd + sxd);
    sy = n2 / (syd + syd);
    fbn = fb * n;
    b22 = fbn * w / dfb;
    b32 = (rn + l * fb) / dfb;
    zzb = (fb + n) / dfb;
    m3[2][2] = zza;
    m3[0][0] = sx;
    m3[3][2] = zwa;
    m3[1][1] = sy;

    sceVu0UnitMatrix(m0);
    m0[0][0] = d;
    m0[3][2] = 1.0f;
    m0[2][3] = 1.0f;
    m0[1][1] = d;
    m0[2][2] = 0.0f;
    m0[3][3] = 0.0f;
    sceVu0UnitMatrix(t);
    t[2][2] = b22;
    t[3][2] = b32;
    t[0][0] = a;
    t[1][1] = px;
    t[3][0] = py;
    t[3][1] = pz;
    sceVu0MulMatrix(m0, t, m0);

    sceVu0UnitMatrix(m1);
    zwb = fbn * -2.0f / dfb;
    sx2 = n * 2045.0f / d;
    sy2 = n * 360.5f / d;
    m1[0][0] = sx;
    m1[1][1] = sy;
    m1[2][2] = zzb;
    m1[2][3] = 1.0f;
    m1[3][3] = 0.0f;
    m1[3][2] = zwb;

    sceVu0UnitMatrix(m4);
    m4[2][2] = zzb;
    m4[3][2] = zwb;
    m4[2][3] = 1.0f;
    m4[3][3] = 0.0f;
    m4[0][0] = n2 / (sx2 + sx2);
    m4[1][1] = n2 / (sy2 + sy2);

    sceVu0UnitMatrix(m5);
    m5[0][0] = a * d * sx2 / n;
    m5[3][3] = 1.0f;
    m5[3][0] = py;
    m5[3][1] = pz;
    m5[3][2] = (r + l) * 0.5f;
    m5[2][2] = (l - r) * 0.5f;
    m5[1][1] = d * px * sy2 / n;
}
