/* score 4 (nofill mode: save as func_00f74440.nofill.c): only the a0/a1 arg-move order before __cmpdf2 in the two inner "if (d<0) d=0-d" blocks (0xf74620, 0xf746c8) is swapped. Tried: inline DABS, ptr inline, z var, ternary, copy temps, reversed compare, separate d2; permuter cannot parse OvlMtx. */
extern s32 D_00FB4A54;
extern s32 D_00FB4A58;
extern s32 D_00FB4A70;
extern s32 D_0108F1BC;
extern s32 D_0108F1C0;
extern s32 D_0108F1C4;
extern s32 D_0108F1C8;
extern s32 D_0108F1D8;
extern s32 D_0108F1E0;
extern f32 D_0108F1E4;
extern f32 D_0108F1E8;
extern s32 D_0108F1F8;
extern s32 D_0108F1FC;
extern s32 D_0108F200;
f32 *func_001bc4e0(void);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0TransMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void sceVu0RotMatrix(OvlMtx, OvlMtx, OvlVec);
void func_00f60898(s32, s32, s32, s32, s32, OvlMtx, s32, f32);
void func_00f606a0(s32, s32, s32, s32, s32, OvlMtx, s32, f32);

static inline double DABS(double x) {
    double z = 0.0;
    if (x < z) x = z - x;
    return x;
}

void func_00f74440(void) {
    OvlMtx m0;
    OvlMtx m1;
    OvlVec rv;
    OvlVec tv;
    s32 idx;
    f32 *e;
    f32 m;
    f32 sc;
    double d;

    rv[0] = 0.43633226f;
    rv[3] = 1.0f;
    rv[1] = 0.43633226f;
    rv[2] = 0.0f;
    idx = D_00FB4A58;
    sceVu0UnitMatrix(m0);
    sceVu0UnitMatrix(m1);
    if (D_00FB4A54) idx = 0;
    e = func_001bc4e0() + idx * 24;
    if (D_0108F1BC == 4) {
        tv[0] = 0.0f;
        tv[1] = 0.0f;
        tv[2] = 0.0f;
    } else {
        tv[0] = -((e[8] - e[4]) * 0.5f + e[4]);
        tv[1] = (e[9] - e[5]) * 0.5f + e[5];
        tv[2] = -((e[10] - e[6]) * 0.5f + e[6]);
    }
    tv[3] = 1.0f;
    sceVu0TransMatrix(m1, m1, tv);
    m = DABS(e[8] - e[4]);
    if (m < DABS(d = e[9] - e[5])) { if (d < 0.0) d = 0.0 - d; m = d; }
    if (m < DABS(d = e[10] - e[6])) { if (d < 0.0) d = 0.0 - d; m = d; }
    if (m == 0.0f) m = 1.0f;
    sc = (f32)D_0108F1D8 / m;
    if (D_0108F1BC == 4) sc = 0.46f;
    m0[0][0] = sc;
    m0[1][1] = sc;
    m0[2][2] = sc;
    do {} while (0);
    sceVu0MulMatrix(m0, m0, m1);
    sceVu0RotMatrix(m0, m0, rv);
    if (D_0108F1E4 != D_0108F1E8) {
        if (D_0108F1E8 < D_0108F1E4) {
            D_0108F1E4 = D_0108F1E4 - 128.0f / (f32)D_00FB4A70;
            if (D_0108F1E4 < D_0108F1E8) D_0108F1E4 = D_0108F1E8;
        } else {
            D_0108F1E4 = D_0108F1E4 + 128.0f / (f32)D_00FB4A70;
            if (D_0108F1E8 < D_0108F1E4) D_0108F1E4 = D_0108F1E8;
        }
    }
    if (D_0108F1BC != 4) {
        func_00f60898(D_0108F1BC, D_0108F1C4, D_0108F1C8, idx, 0, m0, (s32)((f32)D_0108F1E0 * D_0108F1E4 * 0.0078125f), 0.5f);
    } else {
        func_00f606a0(4, D_0108F1FC, D_0108F200, D_0108F1F8, 0, m0, (s32)((f32)D_0108F1E0 * D_0108F1E4 * 0.0078125f), 1.0f);
        D_0108F1C0 = 1;
    }
}
