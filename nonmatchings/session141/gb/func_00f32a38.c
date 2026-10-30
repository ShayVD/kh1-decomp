/* Round 36 (wgb): gb.x func_00f32a38 near miss: 460 -> 456 words, score 273 -> 259 (aligned diff 170 -> 164). Statement order from tools/ovl/hill3.py (score-ranked, strict dependency rules). Tried: hill3 sweep of every gb RANKING row and wm RANKING rows 1-100 (85-90 s, seed 1; strict rules; the order kept passes hill3.py --check against the previous draft), and port.py from the twin (not better). Earlier header below. */
/* NEAR MISS 460 words, score 273 (2364 vs 2376 bytes). Ring/compass draw: per-entry func_00f3d5c8 sprites via jump table, then 4+2 rotated quads through func_00f270c0. Tried: case order (4/5/7 before 3), sz=108 variable (gives the cvt.s.w f22), oy=0x8540 variable (s1), modes (norlo 331, nostrict 403, nogcse 676). Left: scheduling around the 13824/19 stack args, tex kept in t4 vs reloaded, 12 bytes short. */
extern u8 *D_00F56DC0;
extern s32 D_00F80710[];
extern s32 D_00F80750[];
extern u64 D_00F80790[];
extern s32 D_00F61624;
extern s32 D_00F717B0;
typedef struct { u8 pad[0x2C0]; s32 x2C0; s32 x2C4; s32 x2C8; s32 x2CC; u8 pad2D0[4]; s32 x2D4; s32 x2D8; s32 x2DC; s32 x2E0; } D61880;
extern D61880 D_00F61880;
void sceVu0UnitMatrix(OvlMtx);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void sceVu0RotMatrixZ(OvlMtx, OvlMtx, f32);
s32 func_00f3d4f0(void *);
s32 func_00f3d4f8(s32, void *);
void func_00f3d518(s32 *, s32, void *);
u64 *func_00f3d5c8(u64 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, u64, void *);
void func_00f3fe80(s32, u64 *);
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3f9e8(u64 *);
u64 *func_00f26fb8(u64 *, s32, s32);
u64 *func_00f270c0(u64 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, u64, u64);

void func_00f32a38(u64 **pp, s32 t, void *tbl) {
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

    n = func_00f3d4f0(tbl);
    for (i = 0; i < n; i++) {
        k = func_00f3d4f8(i, tbl);
        func_00f3d518(xy, i, tbl);
        if (D_00F80710[k] == 0) continue;
        if (*(s32 *)(D_00F56DC0 + 148) == 0 && k == 7) continue;
        if (D_00F61624 == 0 && k == 7) continue;
        tex = D_00F80790[k];
        switch (k) {
        case 0:
            continue;
        case 4:
        case 5:
        case 7:
            id = D_00F80750[k];
            break;
        case 3:
            id = D_00F80750[4];
            tex = D_00F80790[4];
            break;
        default:
            id = 0;
            break;
        }
        q = func_00f3d5c8(*pp, xy[0], xy[1], id, i, 12800, 512, 512, 19, 13824, tex, tbl);
        if (q != 0) {
            if (k == 3) {
                id = 10640;
            } else if (i < 2) {
                id = 10040;
            } else {
                id = i + 10800;
            }
            func_00f3fe80(id, *pp);
            *pp = q;
        }
    }
    oy = 0x8540;
    tex = D_00F80790[2];
    *pp = func_00f3f9d0(*pp);
    *pp = func_00f26fb8(*pp, 1792, 1856);
    u0 = (D_00F61880.x2C0 + 1) * 16;
    u1 = u0 + (D_00F61880.x2C8 - 3) * 16;
    v0 = (D_00F61880.x2C4 + 1) * 16;
    v1 = v0 + (D_00F61880.x2CC - 3) * 16;
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
    v[0][1] = 1376.0f;
    v[1][0] = 0.0f;
    v[1][1] = 1376.0f;
    v[2][0] = 1376.0f;
    v[2][1] = 1376.0f;
    v[3][0] = -1376.0f;
    v[3][1] = 0.0f;
    sceVu0MulMatrix(v, m, v);
    for (i = 0; i < 4; i++) {
        X[i] = 0x8130 + (s32)v[i][0];
        Y[i] = oy - (s32)v[i][1];
    }
    v[0][0] = 1376.0f;
    v[0][1] = 0.0f;
    v[1][0] = -1376.0f;
    v[1][1] = -1376.0f;
    v[2][0] = 0.0f;
    v[2][1] = -1376.0f;
    v[3][1] = -1376.0f;
    v[3][0] = 1376.0f;
    sceVu0MulMatrix(v, m, v);
    for (i = 0; i < 4; i++) {
        X[i + 4] = 0x8130 + (s32)v[i][0];
        Y[i + 4] = oy - (s32)v[i][1];
    }
    *pp = func_00f270c0(*pp, 0x8130, 0x8540, X[3], Y[3], X[1], Y[1], X[0], Y[0], 0, u1, v1, u0, v1, u1, v0, u0, v0, tex, *(u64 *)(D_00F56DC0 + 8984));
    *pp = func_00f270c0(*pp, 0x8130, 0x8540, X[4], Y[4], X[1], Y[1], X[2], Y[2], 0, u1, v1, u0, v1, u1, v0, u0, v0, tex, *(u64 *)(D_00F56DC0 + 8984));
    *pp = func_00f270c0(*pp, 0x8130, 0x8540, X[3], Y[3], X[6], Y[6], X[5], Y[5], 0, u1, v1, u0, v1, u1, v0, u0, v0, tex, *(u64 *)(D_00F56DC0 + 8984));
    *pp = func_00f270c0(*pp, 0x8130, 0x8540, X[4], Y[4], X[6], Y[6], X[7], Y[7], 0, u1, v1, u0, v1, u1, v0, u0, v0, tex, *(u64 *)(D_00F56DC0 + 8984));
    u0 = (D_00F61880.x2D4 + 1) * 16;
    v0 = (D_00F61880.x2D8 + 1) * 16;
    cx[1] = 31840;
    u1 = u0 + (D_00F61880.x2DC - 2) * 16;
    v1 = v0 + (D_00F61880.x2E0 - 2) * 16;
    cx[0] = 0x85F0;
    cy[0] = 32448;
    cy[1] = 32448;
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
        v[1][0] = sz * 8.0f;
        v[0][0] = D_00F717B0 * 8.0f;
        v[1][1] = sz * 8.0f;
        v[2][0] = D_00F717B0 * 8.0f;
        v[0][1] = sz * 8.0f;
        v[3][0] = sz * 8.0f;
        v[2][1] = D_00F717B0 * 8.0f;
        v[3][1] = D_00F717B0 * 8.0f;
        sceVu0MulMatrix(v, m, v);
        for (i = 0; i < 4; i++) {
            X[i] = cx[j] + (s32)v[i][0];
            Y[i] = cy[j] - (s32)v[i][1];
        }
        *pp = func_00f270c0(*pp, X[0], Y[0], X[1], Y[1], X[2], Y[2], X[3], Y[3], 0, u0, v0, u1, v0, u0, v1, u1, v1, tex, *(u64 *)(D_00F56DC0 + 8992));
    }
    func_00f3fe80(10043, func_00f3f9e8(*pp));
    *pp = func_00f3f9d0(*pp);
    *pp = func_00f26fb8(*pp, 1792, 1856);
    func_00f3fe80(255, func_00f3f9e8(*pp));
}
