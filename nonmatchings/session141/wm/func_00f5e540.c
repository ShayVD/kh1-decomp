/* Round 52 (wgb): score 47 -> 39, port.py of gb func_00f37448 (hill3 statement order). Earlier header below. */
/* Round 50 (wgb): score 49 -> 47, port.py of gb func_00f37448 (see that file; unused gb extern D_00F56DC0 mapped to wm D_00F9B540 by hand). Earlier header below. */
/* Round 43 (wgb): score 55 -> 49, port.py of gb func_00f37448 (unused gb extern D_00F56DC0 mapped to wm D_00F9B540 by hand). Earlier header below. */
/* Round 36 (wgb): wm.x func_00f5e540 near miss: 79 -> 77 words, score 83 -> 55 (aligned diff 52 -> 39). port.py of gb func_00f37448's round 36 draft, the round 36 order from tools/ovl/hill3.py (score-ranked, strict dependency rules). See the gb file for what is left. Earlier header below. */
/* 79 words (420 vs 416). Structure is right (color fill, b1 {col, 0, f1E0|0}, a6 = f2F0 or f1E0, 4-pair UV copy, b0 {5,1,1}); left: scheduling of the color loads and the odd move t1,s2 / move a1,t1 copy of obj. Tried r3 a6-temp draft (80), clean versions a-e. */
typedef struct { u16 a, b, c, flags, d, e; } GbEnt;
typedef struct {
    u8 pad0[4];
    u16 count;
    u16 w;
    u16 pad8;
    u16 h;
    u8 padc[0x70 - 0xC];
    GbEnt ents[1];
} GbHdr;
typedef struct {
    u8 pad0[0xA0];
    GbHdr hdr;
} GbMap;
typedef struct { u8 pad0[4]; u16 used; u8 pad6[8]; u16 kind; } GbCell;
typedef struct { u8 pad0[8]; GbCell cells[1]; } GbGrid;
extern GbMap *D_00F9B540;
typedef struct {
    u8 pad0[0x10];
    OvlVec c0;
    OvlVec c1;
} GbCol;
typedef struct {
    u8 pad0[0x1F0];
    OvlVec uv[4];
} GbWork;
typedef struct {
    f32 u, v;
} GbUV;
typedef struct {
    u8 pad0[8];
    GbUV uv[4];
} GbUVTbl;
typedef struct {
    s32 mode;
    s32 b;
    s32 c;
} GbMode;
typedef struct {
    GbCol *col;
    s32 x4;
    void *tex;
    s32 xc;
    OvlVec pad;
} GbArgs;
extern u8 D_00379F28[][4];
extern u8 D_0037A028[][4];
void *func_00f651d0(s32, GbWork *, void *, GbArgs *, s32, GbMode *, s32);

extern GbUVTbl *D_0108DB8C[];
s32 func_00f4a958(s32);

void *func_00f5e540(s32 x, GbWork *w, s32 id, s32 c, s32 a4) {
    GbMode m;
    GbUVTbl *t;
    u8 *tex;
    u8 *o;
    f32 *c0;
    f32 *ps, *dd;
    s32 i, r;
    GbArgs a;
    r = func_00f4a958(id - 1);
    tex = (u8 *)w;
    o = tex;
    tex = o + 0xD0;
    a.col = (GbCol *)tex;
    c0 = (f32 *)tex;
    c0[4] = D_00379F28[c][0];
    c0[5] = D_00379F28[c][1];
    c0[6] = D_00379F28[c][2];
    tex = o + 0x1E0;
    c0[8] = D_0037A028[c][0];
    t = D_0108DB8C[id];
    c0[9] = D_0037A028[c][1];
    c0[10] = D_0037A028[c][2];
    c0[7] = 128.0f;
    c0[11] = 128.0f;
    if (t != NULL) {
        a.tex = tex;
        tex = o + 0x2F0;
        dd = (f32 *)(o + 500);
        ps = &t->uv[0].v;
        for (i = 0; i < 4; i++) {
            dd[-1] = ps[-1];
            dd[0] = ps[0];
            ps += 2;
            dd += 4;
        }
        a.x4 = 0;
    } else {
        a.x4 = 0;
        a.tex = NULL;
    }
    m.mode = 5;
    m.b = 1;
    m.c = 1;
    return func_00f651d0(x, (GbWork *)o, tex, &a, r, &m, a4);
}
