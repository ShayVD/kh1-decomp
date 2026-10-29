/* 90 words / score 64 (368 vs 392); same body as the tail of f37270 (f37270 likely inlines it). Orig copies w twice at entry (move t3,a2; move t8,t3) and keeps the uv loop unreduced on the source side ((uv+8)+i*8, (uv+12)+i*8) while the dest is reduced; GbArgs is 16 bytes (frame 48). Tried inline wrapper / colour / uv helpers (copies always coalesce), all flag modes (norlo 88/60), and -O1 by hand (no) */
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
    s32 mode;
    s32 b;
    s32 c;
} GbMode;
typedef struct {
    GbCol *col;
    s32 x4;
    void *tex;
    s32 xc;
} GbArgs;
void func_00f3e388(s32, GbWork *, void *, GbArgs *, s32, s32, GbMode *, f32);
extern u8 D_00379F28[];
extern u8 D_0037A028[];

void func_00f40438(s32 flag, s32 x, GbWork *w, s32 ci, s32 r, s32 r2, f32 (*uv)[2], f32 f) {
    GbMode m;
    GbArgs a;
    void *buf;
    s32 i;
    a.col = (GbCol *)((u8 *)w + 0xD0);
    buf = (u8 *)w + 0x1E0;
    if (uv != NULL) {
        a.tex = buf;
        buf = (u8 *)w + 0x2F0;
        for (i = 0; i < 4; i++) {
            w->uv[i][0] = uv[i + 1][0];
            w->uv[i][1] = uv[i + 1][1];
        }
        a.x4 = 0;
    } else {
        a.x4 = 0;
        a.tex = NULL;
    }
    a.col->c0[0] = D_00379F28[ci * 4];
    a.col->c0[1] = D_00379F28[ci * 4 + 1];
    a.col->c0[2] = D_00379F28[ci * 4 + 2];
    a.col->c0[3] = 128.0f;
    a.col->c1[0] = D_0037A028[ci * 4];
    a.col->c1[1] = D_0037A028[ci * 4 + 1];
    a.col->c1[2] = D_0037A028[ci * 4 + 2];
    a.col->c1[3] = 128.0f;
    if (flag) {
        m.mode = 4;
        m.b = 0;
        m.c = 0;
    } else {
        m.mode = 5;
        m.c = 1;
        m.b = 1;
    }
    func_00f3e388(x, w, buf, &a, r, r2, &m, f);
}
