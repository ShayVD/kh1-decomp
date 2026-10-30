/* Round 50 (wgb): score 49 -> 47 (420 vs 416 bytes). The f405c0 recipe: tex = (u8 *)w; o = tex; tex = o + 0xD0; a.col = (GbCol *)tex; c0 = (f32 *)tex; tex = o + 0x1E0; colours written through c0 (writing them through a.col reloads it from the stack), and the uv copy over ps = &t->uv[0].v and dd = o + 500 with ps[-1] / dd[-1] (the target's +12 / +500 offsets). The instruction multiset is now the target's plus one move: ours copies w twice (move t1,s2; move t3,t1), the target once. Tried six forms of the copy chain (o = w directly, tex += 0xD0, c0 first, w + 0x1E0) and passing w instead of o: none drop the move (47-89). Earlier header below. */
/* Round 43 (wgb): score 55 -> 49 (412 vs 416 bytes). msd showed that the target counts the uv copy loop down (li 3 / bgez) over two pointers, so the loop is now written over a GbUV pointer and an f32 pointer; loop.c then reverses it as in the target. Left: the target's pointers are offset by +4 (t + 12 and w + 500, with u read at -4); the move t1,s2 / move a1,t1 copies; and 4 bytes. An inline helper taking w and col did not produce the moves (61). Earlier header below. */
/* Round 36 (wgb): gb.x func_00f37448 near miss: 65 -> 77 words, score 83 -> 55 (aligned diff 61 -> 39). Statement order from tools/ovl/hill3.py (score-ranked, strict dependency rules). Tried: hill3 sweep of every gb RANKING row and wm RANKING rows 1-100 (85-90 s, seed 1; strict rules; the order kept passes hill3.py --check against the previous draft), and port.py from the twin (not better). Earlier header below. */
/* 77 words / score 55 (428 vs 416): logic right; GbArgs needs the extra s32+OvlVec padding for the 96-byte frame. Same blocker as f36ee0/f405c0: the original copies w through t1 (move t1,s2; move a1,t1) and a.col through t1, which looks like an inlined helper taking w. Round 18 (wwm1): 65 raw words after sclimb.py statement and declaration moves. */
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
extern GbMap *D_00F56DC0;
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
void func_00f3e0d8(s32, GbWork *, void *, GbArgs *, s32, GbMode *, s32);

extern GbUVTbl *D_00F813CC[];
s32 func_00f23860(s32);

void func_00f37448(s32 x, GbWork *w, s32 id, s32 c, s32 a4) {
    GbMode m;
    GbUVTbl *t;
    u8 *tex;
    u8 *o;
    f32 *c0;
    f32 *ps, *dd;
    s32 i, r;
    GbArgs a;
    r = func_00f23860(id - 1);
    tex = (u8 *)w;
    o = tex;
    tex = o + 0xD0;
    a.col = (GbCol *)tex;
    c0 = (f32 *)tex;
    tex = o + 0x1E0;
    t = D_00F813CC[id];
    c0[4] = D_00379F28[c][0];
    c0[5] = D_00379F28[c][1];
    c0[6] = D_00379F28[c][2];
    c0[7] = 128.0f;
    c0[8] = D_0037A028[c][0];
    c0[9] = D_0037A028[c][1];
    c0[10] = D_0037A028[c][2];
    c0[11] = 128.0f;
    if (t != NULL) {
        a.tex = tex;
        tex = o + 0x2F0;
        ps = &t->uv[0].v;
        dd = (f32 *)(o + 500);
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
    m.b = 1;
    m.mode = 5;
    m.c = 1;
    func_00f3e0d8(x, (GbWork *)o, tex, &a, r, &m, a4);
}
