/* Round 35 (wgb): wm.x func_00f53758 near miss: 152 -> 58 words, score 253 -> 102 (now 920 = 920). port.py of gb func_00f2c660's round 35 draft (statement order from the dependency-safe hill climb). Earlier header below. */
/* 152 words left (round 12): bounding box of 8 nibble-packed vertices through sceVu0RotTransPers, then a GIF sprite packet. Logic believed right; register allocation differs throughout (try v[] as a flat array or computing corners in the loop). */
typedef struct { u16 x : 4; u16 y : 4; u16 z : 4; u16 r : 4; } GbPos;
typedef struct { u8 pad0[0x2200]; u64 tex[1]; } GbWorld;
typedef struct { s16 idx; s16 pad2; s32 u; s32 v; s32 w; s32 h; } GbTbl;
extern GbWorld *D_00F9B540;
extern GbTbl D_00FA6000[];
extern s32 D_00FA5B04;
void sceVu0RotTransPers(int *v0, float (*m0)[4], float *v1, int mode);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);

u64 *func_00f53758(GbPos pos, GbPos size, f32 (*mtx)[4], s32 idx, u64 *p) {
    s32 out[4];
    OvlVec v[8];
    f32 x0, y0, z0, x1, y1, z1;
    s32 i, first;
    s32 minx, maxx, miny;
    s32 x, y, cx, w, h;
    GbTbl *t;
    s32 tu, tv, tw, th;
    x0 = pos.x * 200.0f;
    x1 = x0 + size.x * 200.0f;
    y0 = -(f32)pos.y * 200.0f;
    y1 = y0 - size.y * 200.0f;
    z0 = pos.z * 200.0f;
    v[0][0] = x0; v[0][1] = y0; v[0][2] = z0;
    z1 = z0 + size.z * 200.0f;
    v[1][0] = x1; v[1][1] = y0; v[1][2] = z0;
    v[2][0] = x0; v[2][1] = y1; v[2][2] = z0;
    v[3][0] = x1; v[3][1] = y1; v[3][2] = z0;
    v[4][0] = x0; v[4][1] = y0; v[4][2] = z1;
    first = 0;
    v[5][0] = x1; v[5][1] = y0; v[5][2] = z1;
    v[6][0] = x0; v[6][1] = y1; v[6][2] = z1;
    v[7][0] = x1; v[7][1] = y1; v[7][2] = z1;
    for (i = 0; i < 8; i++) {
        v[i][3] = 1.0f;
        sceVu0RotTransPers(out, mtx, v[i], 0);
        if (!first || out[0] < minx)
            minx = out[0];
        if (!first || maxx < out[0])
            maxx = out[0];
        if (!first || out[1] < miny)
            miny = out[1];
        first = 1;
    }
    cx = (maxx - minx) / 2;
    p = func_00f66b78(p);
    p[1] = 20;
    p[0] = 0;
    p += 2;
    tw = D_00FA6000[idx].w;
    p[0] = D_00F9B540->tex[idx];
    p[1] = 6;
    p += 2;
    p[1] = 0;
    th = D_00FA6000[idx].h;
    p[0] = 342;
    h = (th - 1) << 4;
    p += 2;
    w = tw - 1;
    p[0] = ((u64)D_00FA5B04 << 24) | 0x3F80000000808080;
    p[1] = 1;
    tu = D_00FA6000[idx].u;
    y = miny - h;
    p += 2;
    p[1] = 3;
    x = minx + cx - (w << 3);
    tv = D_00FA6000[idx].v;
    p[0] = (tu << 4) | ((u64)(tv << 4) << 16);
    p += 2;
    p[0] = x | ((u64)y << 16) | 0x100000000;
    p[1] = 5;
    p += 2;
    p[0] = ((tu + tw) << 4) | ((u64)((tv + th) << 4) << 16);
    p[1] = 3;
    p += 2;
    p[0] = (x + (w << 4)) | ((u64)(y + h) << 16) | 0x100000000;
    p[1] = 5;
    p += 2;
    p[0] = 96;
    p[1] = 20;
    p += 2;
    func_00f66b90(p);
    return p;
}
