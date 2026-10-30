/* drafttwins.py: score 102 -> 84, port.py of the wm twin func_00f53758 draft. Earlier header below. */
/* Round 35 (wgb): gb.x func_00f2c660 near miss: 104 -> 58 words, score 180 -> 102 (920 = 920). Statement order from a dependency-safe statement-order hill climb (round 35 hill3.py: only orders that keep every read/write conflict in place): y0 before y1 and z0 after them, first = 0 between the vertex stores, and the D_00F61880 tw/th/tu/tv loads and the w/h/x/y math interleaved with the packet stores. Left: scheduling of the packet block. Tried: ctx2 (no change). Earlier header below. */
typedef struct { u16 x : 4; u16 y : 4; u16 z : 4; u16 r : 4; } GbPos;
typedef struct { u8 pad0[0x2200]; u64 tex[1]; } GbWorld;
typedef struct { s16 idx; s16 pad2; s32 u; s32 v; s32 w; s32 h; } GbTbl;
extern GbWorld *D_00F56DC0;
extern GbTbl D_00F61880[];
extern s32 D_00F61384;
void sceVu0RotTransPers(int *v0, float (*m0)[4], float *v1, int mode);
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);

u64 *func_00f2c660(GbPos pos, GbPos size, f32 (*mtx)[4], s32 idx, u64 *p) {
    f32 x0, y0, z0, x1, y1, z1;
    GbTbl *t;
    s32 i, first;
    s32 x, y, cx, w, h;
    s32 tu, tv, tw, th;
    s32 out[4];
    s32 minx, maxx, miny;
    OvlVec v[8];
    x0 = pos.x * 200.0f;
    x1 = x0 + size.x * 200.0f;
    y0 = -(f32)pos.y * 200.0f;
    y1 = y0 - size.y * 200.0f;
    z0 = pos.z * 200.0f;
    z1 = z0 + size.z * 200.0f;
    v[0][0] = x0; v[0][1] = y0; v[0][2] = z0;
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
        first = 1;
            miny = out[1];
    }
    cx = (maxx - minx) / 2;
    p = func_00f3fa80(p);
    p[1] = 20;
    p[0] = 0;
    p += 2;
    th = D_00F61880[idx].h;
    tw = D_00F61880[idx].w;
    p[0] = D_00F56DC0->tex[idx];
    p[1] = 6;
    p += 2;
    p[1] = 0;
    h = (th - 1) << 4;
    p[0] = 342;
    p += 2;
    w = tw - 1;
    p[0] = ((u64)D_00F61384 << 24) | 0x3F80000000808080;
    p[1] = 1;
    tu = D_00F61880[idx].u;
    x = minx + cx - (w << 3);
    p += 2;
    y = miny - h;
    tv = D_00F61880[idx].v;
    p[1] = 3;
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
    func_00f3fa98(p);
    return p;
}
