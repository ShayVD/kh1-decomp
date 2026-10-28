/* 81 words / score 18 (408 vs 416 bytes): frame fixed by an extra OvlVec pad in GbArgs; rest is register copies v0=w, v1=col, a1=w that inline col_of/buf_of/draw_quad helpers did not reproduce. */
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
s32 func_00f23860(s32);
s32 func_00f23908(s32);
void func_00f3e388(s32, GbWork *, void *, GbArgs *, s32, s32, GbMode *, f32);

void func_00f36ee0(s32 x, GbWork *w, s32 id, s32 id2, u8 *c0, u8 *c1) {
    GbMode m;
    GbArgs a;
    void *buf;
    s32 r = func_00f23860(id - 1);
    s32 r2 = 0;
    if (id2 > 0)
        r2 = func_00f23908(id2 - 1);
    a.x4 = 0;
    a.tex = NULL;
    a.col = (GbCol *)((u8 *)w + 0xD0);
    buf = (u8 *)w + 0x1E0;
    if (c0 != NULL) {
        a.col->c0[0] = c0[0];
        a.col->c0[1] = c0[1];
        a.col->c0[2] = c0[2];
        a.col->c0[3] = c0[3];
    } else {
        a.col->c0[0] = 255.0f;
        a.col->c0[1] = 255.0f;
        a.col->c0[2] = 255.0f;
        a.col->c0[3] = 128.0f;
    }
    if (c1 != NULL) {
        a.col->c1[0] = c1[0];
        a.col->c1[1] = c1[1];
        a.col->c1[2] = c1[2];
        a.col->c1[3] = c1[3];
    } else {
        a.col->c1[0] = 128.0f;
        a.col->c1[1] = 128.0f;
        a.col->c1[2] = 128.0f;
        a.col->c1[3] = 128.0f;
    }
    m.mode = 5;
    m.b = 1;
    m.c = 1;
    func_00f3e388(x, w, buf, &a, r, r2, &m, 0.0f);
}
