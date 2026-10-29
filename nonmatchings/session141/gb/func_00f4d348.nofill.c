/* gb.x func_00f4d348 near miss (nofill mode): 4 words differ, score 4 (1208 = 1208 bytes). Port of wm func_00f74440's near miss (port.py). Only the a0/a1 move order before __cmpdf2 in the two inner if (d < 0) blocks differs: the original sets a1 before a0. Round 15 tried 24 compare/subtract spellings (d < 0.0, 0.0 > d, d < z, z > d, d < 0, !(d >= 0.0) crossed with 0.0 - d, z - d, -d, 0 - d); all stay at 4. */
extern s32 D_00F702D4;
extern s32 D_00F702D8;
extern s32 D_00F702F0;
extern s32 D_00F829FC;
extern s32 D_00F82A00;
extern s32 D_00F82A04;
extern s32 D_00F82A08;
extern s32 D_00F82A18;
extern s32 D_00F82A20;
extern f32 D_00F82A24;
extern f32 D_00F82A28;
extern s32 D_00F82A38;
extern s32 D_00F82A3C;
extern s32 D_00F82A40;
f32 *func_001bc4e0(void);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0TransMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void sceVu0RotMatrix(OvlMtx, OvlMtx, OvlVec);
void func_00f397a0(s32, s32, s32, s32, s32, OvlMtx, s32, f32);
void func_00f395a8(s32, s32, s32, s32, s32, OvlMtx, s32, f32);

static inline double DABS(double x) {
    double z = 0.0;
    if (x < z) x = z - x;
    return x;
}

void func_00f4d348(void) {
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
    idx = D_00F702D8;
    sceVu0UnitMatrix(m0);
    sceVu0UnitMatrix(m1);
    if (D_00F702D4) idx = 0;
    e = func_001bc4e0() + idx * 24;
    if (D_00F829FC == 4) {
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
    sc = (f32)D_00F82A18 / m;
    if (D_00F829FC == 4) sc = 0.46f;
    m0[0][0] = sc;
    m0[1][1] = sc;
    m0[2][2] = sc;
    do {} while (0);
    sceVu0MulMatrix(m0, m0, m1);
    sceVu0RotMatrix(m0, m0, rv);
    if (D_00F82A24 != D_00F82A28) {
        if (D_00F82A28 < D_00F82A24) {
            D_00F82A24 = D_00F82A24 - 128.0f / (f32)D_00F702F0;
            if (D_00F82A24 < D_00F82A28) D_00F82A24 = D_00F82A28;
        } else {
            D_00F82A24 = D_00F82A24 + 128.0f / (f32)D_00F702F0;
            if (D_00F82A28 < D_00F82A24) D_00F82A24 = D_00F82A28;
        }
    }
    if (D_00F829FC != 4) {
        func_00f397a0(D_00F829FC, D_00F82A04, D_00F82A08, idx, 0, m0, (s32)((f32)D_00F82A20 * D_00F82A24 * 0.0078125f), 0.5f);
    } else {
        func_00f395a8(4, D_00F82A3C, D_00F82A40, D_00F82A38, 0, m0, (s32)((f32)D_00F82A20 * D_00F82A24 * 0.0078125f), 1.0f);
        D_00F82A00 = 1;
    }
}
