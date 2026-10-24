/* VU0 state shared by every port platform (the host build and the Vita):
 * what the game's inline VU0 asm keeps in VU0 registers across calls.
 * include/platform/vu.h's off-EE side reads and writes it. Not part of the
 * PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/vu.h"

f32 cosf(f32);
f32 sinf(f32);

/* the random register R (vrinit / vrxor / vrnext / vrget): a float in [1, 2) */
u32 PlatVu0R = 0x3F800000;

/* VU0 microprogram P21 (src/hand/vu0.c's func_00162cd0, docs/renderer-spec.md):
 * rows 0-2 of Rx(x) * Ry(y) * Rz(z) in the row-vector convention. The VU0
 * code takes sin / cos by a Taylor series; libm's are close to it. */
void PlatVu0RotRows(f32 (*out)[4], const f32 *rot) {
    f32 t[3][3];
    f32 cx = cosf(rot[0]), sx = sinf(rot[0]);
    f32 cy = cosf(rot[1]), sy = sinf(rot[1]);
    f32 cz = cosf(rot[2]), sz = sinf(rot[2]);
    int i, j, k;
    /* Rx rows (1,0,0) (0,cx,sx) (0,-sx,cx); Ry (cy,0,-sy) (0,1,0) (sy,0,cy);
     * Rz (cz,sz,0) (-sz,cz,0) (0,0,1) */
    f32 rx[3][3] = {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    f32 ry[3][3] = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    f32 rz[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 1}};
    rx[1][1] = cx; rx[1][2] = sx; rx[2][1] = -sx; rx[2][2] = cx;
    ry[0][0] = cy; ry[0][2] = -sy; ry[2][0] = sy; ry[2][2] = cy;
    rz[0][0] = cz; rz[0][1] = sz; rz[1][0] = -sz; rz[1][1] = cz;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            t[i][j] = 0.0f;
            for (k = 0; k < 3; k++)
                t[i][j] += rx[i][k] * ry[k][j];
        }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            out[i][j] = 0.0f;
            for (k = 0; k < 3; k++)
                out[i][j] += t[i][k] * rz[k][j];
        }
        out[i][3] = 0.0f;
    }
}

/* The VU0 register file (vu.h, tools/host/vu2c.py). */
PlatVu0Regs PlatVu0 = {{{0.0f, 0.0f, 0.0f, 1.0f}}};

static void vu0_set(int d, int mask, const f32 *r) {
    u32 mac = 0, st = 0;
    int i;
    for (i = 0; i < 4; i++) {
        if (!(mask & (8 >> i)))
            continue;
        if (r[i] == 0.0f)
            mac |= 8 >> i;
        if (PlatVu0Bits(r[i]) & 0x80000000)
            mac |= 0x80 >> i;
        if (d == PLAT_VU0_ACC)
            PlatVu0.acc[i] = r[i];
        else if (d != 0)
            PlatVu0.vf[d][i] = r[i];
    }
    if (mac & 0x0f)
        st |= 1;
    if (mac & 0xf0)
        st |= 2;
    PlatVu0.mac = mac;
    PlatVu0.stat = (PlatVu0.stat & ~3u) | st | (st << 6);
}

void PlatVu0Fmac(int op, int d, int mask, int s, int t, int bc) {
    f32 r[4], a, b;
    int i;
    for (i = 0; i < 4; i++) {
        a = PlatVu0.vf[s][i];
        b = bc < 0 ? PlatVu0.vf[t][i] : bc == PLAT_VU0_BC_Q ? PlatVu0.q : PlatVu0.vf[t][bc];
        switch (op) {
        case PLAT_VU0_ADD: r[i] = a + b; break;
        case PLAT_VU0_SUB: r[i] = a - b; break;
        case PLAT_VU0_MUL: r[i] = a * b; break;
        case PLAT_VU0_MADD: r[i] = PlatVu0.acc[i] + a * b; break;
        case PLAT_VU0_MSUB: r[i] = PlatVu0.acc[i] - a * b; break;
        case PLAT_VU0_MAX: r[i] = a > b ? a : b; break;
        default: r[i] = a < b ? a : b; break;
        }
    }
    if (op == PLAT_VU0_MAX || op == PLAT_VU0_MINI) {
        /* no flags */
        for (i = 0; i < 4; i++)
            if ((mask & (8 >> i)) && d > 0)
                PlatVu0.vf[d][i] = r[i];
        return;
    }
    vu0_set(d, mask, r);
}

/* ACC.xyz = (s.y t.z, s.z t.x, s.x t.y); d.xyz = ACC - (s.y t.z, s.z t.x, s.x t.y) */
void PlatVu0Opmula(int s, int t) {
    f32 *a = PlatVu0.vf[s], *b = PlatVu0.vf[t], r[4];
    r[0] = a[1] * b[2];
    r[1] = a[2] * b[0];
    r[2] = a[0] * b[1];
    r[3] = 0.0f;
    vu0_set(PLAT_VU0_ACC, 0xe, r);
}
void PlatVu0Opmsub(int d, int s, int t) {
    f32 *a = PlatVu0.vf[s], *b = PlatVu0.vf[t], r[4];
    r[0] = PlatVu0.acc[0] - a[1] * b[2];
    r[1] = PlatVu0.acc[1] - a[2] * b[0];
    r[2] = PlatVu0.acc[2] - a[0] * b[1];
    r[3] = 0.0f;
    vu0_set(d, 0xe, r);
}

void PlatVu0Move(int d, int mask, int s) {
    f32 r[4];
    int i;
    __builtin_memcpy(r, PlatVu0.vf[s], 16);
    for (i = 0; i < 4; i++)
        if ((mask & (8 >> i)) && d != 0)
            PlatVu0.vf[d][i] = r[i];
}

void PlatVu0Ftoi(int d, int mask, int s, int frac) {
    f32 r[4];
    int i;
    for (i = 0; i < 4; i++)
        r[i] = PlatVu0Float((u32)PlatVu0Ftoi0(PlatVu0.vf[s][i] * (f32)(1 << frac)));
    for (i = 0; i < 4; i++)
        if ((mask & (8 >> i)) && d != 0)
            PlatVu0.vf[d][i] = r[i];
}

void PlatVu0Itof(int d, int mask, int s, int frac) {
    f32 r[4];
    int i;
    for (i = 0; i < 4; i++)
        r[i] = (f32)(s32)PlatVu0Bits(PlatVu0.vf[s][i]) / (f32)(1 << frac);
    for (i = 0; i < 4; i++)
        if ((mask & (8 >> i)) && d != 0)
            PlatVu0.vf[d][i] = r[i];
}

void PlatVu0Div(int s, int sf, int t, int tf) { PlatVu0.q = PlatVu0.vf[s][sf] / PlatVu0.vf[t][tf]; }
void PlatVu0SqrtQ(int t, int tf) { PlatVu0.q = PlatVu0Sqrt(PlatVu0.vf[t][tf]); }
void PlatVu0Lq(int n, const void *p) {
    if (n != 0)
        __builtin_memcpy(PlatVu0.vf[n], p, 16);
}
void PlatVu0Sq(int n, void *p) { __builtin_memcpy(p, PlatVu0.vf[n], 16); }
/* the GPR's upper 64 bits are not modelled: z and w 0 */
void PlatVu0Qmtc2(int n, u64 v) {
    if (n == 0)
        return;
    PlatVu0.vf[n][0] = PlatVu0Float((u32)v);
    PlatVu0.vf[n][1] = PlatVu0Float((u32)(v >> 32));
    PlatVu0.vf[n][2] = 0.0f;
    PlatVu0.vf[n][3] = 0.0f;
}
u64 PlatVu0Qmfc2(int n) {
    return PlatVu0Bits(PlatVu0.vf[n][0]) | (u64)PlatVu0Bits(PlatVu0.vf[n][1]) << 32;
}
