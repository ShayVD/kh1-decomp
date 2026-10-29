/* Round 36 (wwm2): wm.x func_00f59b30 near miss: score 273 -> 259 (460 -> 456 words, 2364 vs 2376); statement order from the score-ranked dependency-safe hill3 (r35/hill3.py, 120 s, seed 363). Earlier header below. */
/* NEAR MISS 460 words, score 273 (2364 vs 2376 bytes). Port of gb func_00f32a38 (same score); tables mapped by hand: D_0108CED0/D_0108CF50 = gb D_00F80710/D_00F80790. See the gb file for what was tried. */
extern u8 *D_00F9B540;
extern s32 D_0108CED0[];
extern s32 D_0108CF10[];
extern u64 D_0108CF50[];
extern s32 D_00FA5DA4;
extern s32 D_00FB7860;
typedef struct { u8 pad[0x2C0]; s32 x2C0; s32 x2C4; s32 x2C8; s32 x2CC; u8 pad2D0[4]; s32 x2D4; s32 x2D8; s32 x2DC; s32 x2E0; } D61880;
extern D61880 D_00FA6000;
void sceVu0UnitMatrix(OvlMtx);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void sceVu0RotMatrixZ(OvlMtx, OvlMtx, f32);
s32 func_00f645e8(void *);
s32 func_00f645f0(s32, void *);
void func_00f64610(s32 *, s32, void *);
u64 *func_00f646c0(u64 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, u64, void *);
void func_00f66f78(s32, u64 *);
u64 *func_00f66ac8(u64 *);
u64 *func_00f66ae0(u64 *);
u64 *func_00f4e0b0(u64 *, s32, s32);
u64 *func_00f4e1b8(u64 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, u64, u64);

void func_00f59b30(u64 **pp, s32 t, void *tbl) {
    OvlMtx v;
    OvlMtx m;
    s32 X[8];
    s32 Y[8];
    f32 ang[4];
    s32 cx[4];
    s32 cy[4];
    s32 xy[4];
    u64 tex;
    s32 n, i, j, k, id;
    s32 u0, v0, u1, v1;
    f32 a;
    u64 *q;
    s32 sz;
    s32 oy;

    n = func_00f645e8(tbl);
    for (i = 0; i < n; i++) {
        k = func_00f645f0(i, tbl);
        func_00f64610(xy, i, tbl);
        if (D_0108CED0[k] == 0) continue;
        if (*(s32 *)(D_00F9B540 + 148) == 0 && k == 7) continue;
        if (D_00FA5DA4 == 0 && k == 7) continue;
        tex = D_0108CF50[k];
        switch (k) {
        case 0:
            continue;
        case 4:
        case 5:
        case 7:
            id = D_0108CF10[k];
            break;
        case 3:
            id = D_0108CF10[4];
            tex = D_0108CF50[4];
            break;
        default:
            id = 0;
            break;
        }
        q = func_00f646c0(*pp, xy[0], xy[1], id, i, 12800, 512, 512, 19, 13824, tex, tbl);
        if (q != 0) {
            if (k == 3) {
                id = 10640;
            } else if (i < 2) {
                id = 10040;
            } else {
                id = i + 10800;
            }
            func_00f66f78(id, *pp);
            *pp = q;
        }
    }
    oy = 0x8540;
    tex = D_0108CF50[2];
    *pp = func_00f66ac8(*pp);
    *pp = func_00f4e0b0(*pp, 1792, 1856);
    u0 = (D_00FA6000.x2C0 + 1) * 16;
    v0 = (D_00FA6000.x2C4 + 1) * 16;
    u1 = u0 + (D_00FA6000.x2C8 - 3) * 16;
    v1 = v0 + (D_00FA6000.x2CC - 3) * 16;
    a = -(f32)(t % 4320) * 360.0f / 4320.0f + 180.0f + 31.2f;
    if (a > 180.0f) a -= 360.0f;
    ang[0] = a * 3.1415926f / 180.0f;
    sceVu0UnitMatrix(m);
    sceVu0RotMatrixZ(m, m, ang[0]);
    for (i = 3; i >= 0; i--) {
        v[3 - i][2] = 0.0f;
        v[3 - i][3] = 1.0f;
    }
    v[0][0] = -1376.0f;
    v[3][0] = -1376.0f;
    v[0][1] = 1376.0f;
    v[1][0] = 0.0f;
    v[1][1] = 1376.0f;
    v[2][0] = 1376.0f;
    v[3][1] = 0.0f;
    v[2][1] = 1376.0f;
    sceVu0MulMatrix(v, m, v);
    for (i = 0; i < 4; i++) {
        X[i] = 0x8130 + (s32)v[i][0];
        Y[i] = oy - (s32)v[i][1];
    }
    v[0][0] = 1376.0f;
    v[0][1] = 0.0f;
    v[3][0] = 1376.0f;
    v[1][0] = -1376.0f;
    v[1][1] = -1376.0f;
    v[2][0] = 0.0f;
    v[2][1] = -1376.0f;
    v[3][1] = -1376.0f;
    sceVu0MulMatrix(v, m, v);
    for (i = 0; i < 4; i++) {
        X[i + 4] = 0x8130 + (s32)v[i][0];
        Y[i + 4] = oy - (s32)v[i][1];
    }
    *pp = func_00f4e1b8(*pp, 0x8130, 0x8540, X[3], Y[3], X[1], Y[1], X[0], Y[0], 0, u1, v1, u0, v1, u1, v0, u0, v0, tex, *(u64 *)(D_00F9B540 + 8984));
    *pp = func_00f4e1b8(*pp, 0x8130, 0x8540, X[4], Y[4], X[1], Y[1], X[2], Y[2], 0, u1, v1, u0, v1, u1, v0, u0, v0, tex, *(u64 *)(D_00F9B540 + 8984));
    *pp = func_00f4e1b8(*pp, 0x8130, 0x8540, X[3], Y[3], X[6], Y[6], X[5], Y[5], 0, u1, v1, u0, v1, u1, v0, u0, v0, tex, *(u64 *)(D_00F9B540 + 8984));
    *pp = func_00f4e1b8(*pp, 0x8130, 0x8540, X[4], Y[4], X[6], Y[6], X[7], Y[7], 0, u1, v1, u0, v1, u1, v0, u0, v0, tex, *(u64 *)(D_00F9B540 + 8984));
    cx[1] = 31840;
    u0 = (D_00FA6000.x2D4 + 1) * 16;
    v0 = (D_00FA6000.x2D8 + 1) * 16;
    u1 = u0 + (D_00FA6000.x2DC - 2) * 16;
    cy[0] = 32448;
    v1 = v0 + (D_00FA6000.x2E0 - 2) * 16;
    cy[1] = 32448;
    cx[0] = 0x85F0;
    a = (f32)(t % 2700) * 360.0f / 2700.0f - 180.0f;
    ang[0] = a * 3.1415926f / 180.0f;
    a -= 28.0f;
    if (a < -180.0f) a += 360.0f;
    sz = 108;
    ang[1] = a * 3.1415926f / 180.0f;
    for (j = 0; j < 2; j++) {
        sceVu0UnitMatrix(m);
        sceVu0RotMatrixZ(m, m, ang[j]);
        for (i = 3; i >= 0; i--) {
            v[3 - i][2] = 0.0f;
            v[3 - i][3] = 1.0f;
        }
        v[0][1] = sz * 8.0f;
        v[0][0] = D_00FB7860 * 8.0f;
        v[1][0] = sz * 8.0f;
        v[1][1] = sz * 8.0f;
        v[2][0] = D_00FB7860 * 8.0f;
        v[3][0] = sz * 8.0f;
        v[2][1] = D_00FB7860 * 8.0f;
        v[3][1] = D_00FB7860 * 8.0f;
        sceVu0MulMatrix(v, m, v);
        for (i = 0; i < 4; i++) {
            X[i] = cx[j] + (s32)v[i][0];
            Y[i] = cy[j] - (s32)v[i][1];
        }
        *pp = func_00f4e1b8(*pp, X[0], Y[0], X[1], Y[1], X[2], Y[2], X[3], Y[3], 0, u0, v0, u1, v0, u0, v1, u1, v1, tex, *(u64 *)(D_00F9B540 + 8992));
    }
    func_00f66f78(10043, func_00f66ae0(*pp));
    *pp = func_00f66ac8(*pp);
    *pp = func_00f4e0b0(*pp, 1792, 1856);
    func_00f66f78(255, func_00f66ae0(*pp));
}
