/* drafttwins.py: score 149 -> 144, port.py of the gb twin func_00f2b9b8 draft. Earlier header below. */
/* drafttwins.py: score 175 -> 149, port.py of the gb twin func_00f2b9b8 draft. Earlier header below. */
typedef struct {
    u8 pad0[136];
    f32 f136;
    u8 pad140[28];
    u16 x8 : 16;
} Wdim;
typedef struct {
    u8 pad0[88];
    u64 lo : 32;
    u64 fa : 4;
    u64 fb : 28;
    u8 pad96[40];
    f32 f136;
} Wm333;
typedef struct { OvlVec v[4]; OvlVec pos; OvlVec rot; } GbXf;
typedef struct {
    void *x0;
    u8 *x4;
    u8 x8[1];
} Ctx;
typedef struct { u8 pad[6]; u16 x6; u16 x8; u16 xA; } GbDims;
typedef struct { u8 pad[0x25C]; s32 x25C; s32 x260; } D61880;
extern u8 *D_00F9B540;
extern s32 D_00F9B648;
extern OvlMtx D_00F9B580;
extern OvlMtx D_00F9B600;
extern OvlMtx D_0108CD50;
extern OvlMtx D_0108CE10;
extern f32 D_00FA5AF8;
extern f32 D_00FA5B08;
extern s32 D_00FA5AFC;
extern s32 D_00FA5B00;
extern s32 D_00FA5B04;
extern s32 D_00FA5B34;
extern D61880 D_00FA6000;
void sceVu0ViewScreenMatrix(OvlMtx, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void sceVu0CopyMatrix(OvlMtx, OvlMtx);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0TransMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0RotMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0RotMatrixX(OvlMtx, OvlMtx, f32);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void func_001bebd0(OvlMtx, GbXf *, void *);
void *func_00f66ac8(void *);
void *func_00f4e0b0(void *, s32, s32);
s32 func_00f66ae0(void *);
void func_00f66f78(s32, s32);
u64 *func_00f66b78(void *);
void func_00f66b90(void *);
s32 func_00f4a328(s32, Ctx *, void *, s32, s32, void *);
void *func_00f528f8(OvlMtx, void *);
void *func_00f5e8a8(u64, s32, s32, s32, s32, s32, u64, s32, OvlMtx, void *);
void *func_00f54050(void *, OvlMtx);
s32 func_00f530f8(s32, Ctx *);
void func_00f504a8(void);
s32 func_00f53af0(s32, Ctx *, void *);

void func_00f52ab0(Ctx *c, void *box, s32 flag) {
    OvlMtx m;
    OvlMtx m2;
    OvlVec v;
    GbXf xf;
    OvlMtx vs;
    u8 *g;
    f32 *pos;
    f32 *rot;
    f32 *cam;
    GbXf *px;
    u64 *p;
    s32 i;
    s32 r;
    if (D_00F9B648 != 0) {
        return;
    }
    D_00F9B648 = 1;
    sceVu0ViewScreenMatrix(vs, 512.0f, 1.0f, 1.0f, 2064.0f, 2080.0f, 1.0f, 16777000.0f, 1.0f, 65536.0f);
    g = D_00F9B540 + 160;
    px = &xf;
    sceVu0CopyMatrix(D_00F9B580, vs);
    cam = (f32 *)D_0108CD50;
    sceVu0UnitMatrix(D_00F9B600);
    pos = xf.pos;
    sceVu0TransMatrix(D_00F9B600, D_00F9B600, pos);
    rot = xf.rot;
    sceVu0RotMatrix(D_00F9B600, D_00F9B600, rot);
    D_00F9B600[3][2] -= px->v[0][2];
    pos[0] = -(((GbDims *)g)->x6 * 200.0f) * 0.5f;
    rot[2] = 0.0f;
    rot[3] = 0.0f;
    rot[1] = *(s32 *)(D_00F9B540 + 4312) * 3.1415926f * 0.00048828125f;
    pos[1] = ((u16)((Wm333 *)D_00F9B540)->fb & 0xF) * 200.0f;
    xf.v[0][0] = 0.0f;
    rot[0] = *(s32 *)(D_00F9B540 + 4308) * 3.1415926f * 0.00048828125f;
    pos[3] = 0.0f;
    pos[2] = -(((GbDims *)g)->xA * 200.0f) * 0.5f;
    xf.v[0][1] = 0.0f;
    px->v[0][2] = *(f32 *)(D_00F9B540 + 136);
    xf.v[0][3] = 0.0f;
    xf.v[1][0] = 0.0f;
    xf.v[1][1] = 0.0f;
    xf.v[1][2] = 1.0f;
    xf.v[1][3] = 1.0f;
    xf.v[2][0] = 0.0f;
    xf.v[2][1] = 1.0f;
    xf.v[2][3] = 1.0f;
    xf.v[2][2] = 0.0f;
    xf.v[3][0] = 0.0f;
    xf.v[3][1] = 0.0f;
    xf.v[3][2] = 0.0f;
    xf.v[3][3] = 0.0f;
    func_001bebd0((f32 (*)[4])cam, px, D_00F9B540 + 4112);
    for (i = 0; i < 15; i++) {
        cam[i] *= D_00FA5AF8;
    }
    cam[i] *= D_00FA5B08;
    c->x0 = func_00f66ac8(c->x0);
    c->x0 = func_00f4e0b0(c->x0, 1776, 1824);
    func_00f66f78(10080, func_00f66ae0(c->x0));
    if (flag) {
        func_00f4a328(10081, c, D_0108CD50, D_00FA5AFC, (u16)(*(u64 *)(D_00F9B540 + 88) >> 36) & 0xF, 0);
    }
    v[2] = 0.0f;
    v[0] = (((GbDims *)g)->x6 >> 1) * 200.0f;
    v[1] = ((u16)(*(u64 *)(D_00F9B540 + 88) >> 36) & 0xF) * 200.0f - 50.0f;
    sceVu0UnitMatrix(m);
    sceVu0TransMatrix(m, m, v);
    sceVu0RotMatrixX(m, m, 3.1415926f);
    sceVu0MulMatrix(m, D_0108CE10, m);
    c->x0 = func_00f66ac8(c->x0);
    p = func_00f66b78(c->x0);
    p[1] = 66;
    p[3] = 71;
    p[2] = 0x5000D;
    p[5] = 24;
    p[4] = 0x720000006F00;
    p[0] = 0x8000000048;
    c->x0 = p + 6;
    func_00f66b90(p + 6);
    c->x0 = func_00f528f8(m, c->x0);
    p = func_00f66b78(c->x0);
    p[1] = 66;
    p[0] = 68;
    c->x0 = p + 2;
    func_00f66b90(p + 2);
    func_00f66f78(10361, func_00f66ae0(c->x0));
    if (*(s16 *)(D_00F9B540 + 122) != 0) {
        c->x0 = func_00f66ac8(c->x0);
        v[3] = 1.0f;
        v[0] = 0.0f;
        v[2] = 0.0f;
        v[1] = -(((Wdim *)D_00F9B540)->x8 * 200.0f);
        sceVu0UnitMatrix(m);
        sceVu0TransMatrix(m, m, v);
        sceVu0MulMatrix(m, D_0108CE10, m);
        c->x0 = func_00f5e8a8(D_00FA5B00 * 90 / 128, ((GbDims *)g)->x6, ((GbDims *)g)->x8, ((GbDims *)g)->xA,
                              D_00FA6000.x25C, D_00FA6000.x260, *(u64 *)(D_00F9B540 + 8944), 63, m, c->x0);
        v[1] = -((((u16)(*(u64 *)(D_00F9B540 + 88) >> 36) & 0xF) + 1) * 200.0f);
        sceVu0UnitMatrix(m);
        sceVu0TransMatrix(m, m, v);
        sceVu0MulMatrix(m, D_0108CE10, m);
        c->x0 = func_00f54050(c->x0, D_0108CE10);
        func_00f66f78(10362, func_00f66ae0(c->x0));
    }
    r = 0;
    if (D_00FA5B34 < 2 && D_00FA5B04 == 128) {
        r = func_00f530f8(10240, c);
    }
    if (r == 0) {
        func_00f504a8();
    }
    func_00f53af0(10490, c, box);
}
