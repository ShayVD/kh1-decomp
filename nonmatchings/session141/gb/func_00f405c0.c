/* 29 words / score 54: original keeps w copied in t3/t8 across the packet build; a 600s permuter run did not close it. Twin func_00f40438 (calls func_00f3e388) should follow once this matches. */
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
} GbArgs;
extern u8 D_00379F28[][4];
extern u8 D_0037A028[][4];
void func_00f3e0d8(s32, GbWork *, void *, GbArgs *, s32, GbMode *, s32);

void func_00f405c0(s32 flag, s32 x, GbWork *w, s32 c, s32 a4, s32 a5, GbUVTbl *t) {
    GbMode m;
    GbArgs a;
    void *buf;
    s32 i;
    a.col = (GbCol *)((u8 *)w + 0xD0);
    buf = (u8 *)w + 0x1E0;
    if (t != NULL) {
        a.tex = (u8 *)w + 0x1E0;
        buf = (u8 *)w + 0x2F0;
        for (i = 0; i < 4; i++) {
            w->uv[i][0] = t->uv[i].u;
            w->uv[i][1] = t->uv[i].v;
        }
        a.x4 = 0;
    } else {
        a.x4 = 0;
        a.tex = NULL;
    }
    a.col->c0[0] = D_00379F28[c][0];
    a.col->c0[1] = D_00379F28[c][1];
    a.col->c0[2] = D_00379F28[c][2];
    a.col->c0[3] = 128.0f;
    a.col->c1[0] = D_0037A028[c][0];
    a.col->c1[1] = D_0037A028[c][1];
    a.col->c1[2] = D_0037A028[c][2];
    a.col->c1[3] = 128.0f;
    if (flag) {
        m.mode = 4;
        m.b = 0;
        m.c = 0;
    } else {
        m.mode = 5;
        m.b = 1;
        m.c = 1;
    }
    func_00f3e0d8(x, w, buf, &a, a4, &m, a5);
}
