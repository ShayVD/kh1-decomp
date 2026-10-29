/* gb.x func_00f2b9b8 near miss: 123 words differ, score 185 (ours 1564 bytes, original 1568). Per-frame scene draw, guarded once per frame by D_00F56EC8. It sets up the view-screen matrix and the D_00F56E80 camera from a local GbXf (pos/rot are read before they are written, as in the original), runs func_001bebd0 into D_00F80590 and scales it, then calls func_00f23230 (when flag is set), the backdrop packets with func_00f2b800, the optional func_00f377b0 / func_00f2cf58 pass (World x7A), func_00f2c000 / func_00f293b0 and func_00f2c9f8. Logic is complete. Findings: an unused OvlMtx m2 is needed for the frame layout; pointer locals px/cam/pos/rot set in the original's order give the prologue and s-register map; cam[i] after the scale loop (i == 15) gives the cam + 60 address. Left: (1) the 3-pair packet before func_00f2b800 uses separate p+16 / p+32 / p+48 bases in the original, where ours copies p into t1 (same idiom as f2c9f8; a static inline pk() helper gives the bases but scores 181 / 237 words); (2) the setup block's float scheduling (a 300 s hill climb did not help). wm twin: func_00f52ab0 (same score). */
typedef struct { OvlVec v[4]; OvlVec pos; OvlVec rot; } GbXf;
typedef struct {
    void *x0;
    u8 *x4;
    u8 x8[1];
} Ctx;
typedef struct { u8 pad[6]; u16 x6; u16 x8; u16 xA; } GbDims;
typedef struct { u8 pad[0x25C]; s32 x25C; s32 x260; } D61880;
extern u8 *D_00F56DC0;
extern s32 D_00F56EC8;
extern OvlMtx D_00F56E00;
extern OvlMtx D_00F56E80;
extern OvlMtx D_00F80590;
extern OvlMtx D_00F80650;
extern f32 D_00F61378;
extern f32 D_00F61388;
extern s32 D_00F6137C;
extern s32 D_00F61380;
extern s32 D_00F61384;
extern s32 D_00F613B4;
extern D61880 D_00F61880;
void sceVu0ViewScreenMatrix(OvlMtx, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void sceVu0CopyMatrix(OvlMtx, OvlMtx);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0TransMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0RotMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0RotMatrixX(OvlMtx, OvlMtx, f32);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void func_001bebd0(OvlMtx, GbXf *, void *);
void *func_00f3f9d0(void *);
void *func_00f26fb8(void *, s32, s32);
s32 func_00f3f9e8(void *);
void func_00f3fe80(s32, s32);
u64 *func_00f3fa80(void *);
void func_00f3fa98(void *);
s32 func_00f23230(s32, Ctx *, void *, s32, s32, void *);
void *func_00f2b800(OvlMtx, void *);
void *func_00f377b0(s32, s32, s32, s32, s32, s32, u64, s32, OvlMtx, void *);
void *func_00f2cf58(void *, OvlMtx);
s32 func_00f2c000(s32, Ctx *);
void func_00f293b0(void);
s32 func_00f2c9f8(s32, Ctx *, void *);

void func_00f2b9b8(Ctx *c, void *box, s32 flag) {
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
    if (D_00F56EC8 != 0) {
        return;
    }
    D_00F56EC8 = 1;
    sceVu0ViewScreenMatrix(vs, 512.0f, 1.0f, 1.0f, 2064.0f, 2080.0f, 1.0f, 16777000.0f, 1.0f, 65536.0f);
    g = D_00F56DC0 + 160;
    px = &xf;
    sceVu0CopyMatrix(D_00F56E00, vs);
    cam = (f32 *)D_00F80590;
    sceVu0UnitMatrix(D_00F56E80);
    pos = xf.pos;
    sceVu0TransMatrix(D_00F56E80, D_00F56E80, pos);
    rot = xf.rot;
    sceVu0RotMatrix(D_00F56E80, D_00F56E80, rot);
    D_00F56E80[3][2] -= px->v[0][2];
    rot[0] = *(s32 *)(D_00F56DC0 + 4308) * 3.1415926f * 0.00048828125f;
    rot[1] = *(s32 *)(D_00F56DC0 + 4312) * 3.1415926f * 0.00048828125f;
    rot[2] = 0.0f;
    rot[3] = 0.0f;
    pos[0] = -(((GbDims *)g)->x6 * 200.0f) * 0.5f;
    pos[1] = ((u16)(*(u64 *)(D_00F56DC0 + 88) >> 36) & 0xF) * 200.0f;
    pos[2] = -(((GbDims *)g)->xA * 200.0f) * 0.5f;
    pos[3] = 0.0f;
    xf.v[0][0] = 0.0f;
    xf.v[0][1] = 0.0f;
    px->v[0][2] = *(f32 *)(D_00F56DC0 + 136);
    xf.v[0][3] = 0.0f;
    xf.v[1][0] = 0.0f;
    xf.v[1][1] = 0.0f;
    xf.v[1][2] = 1.0f;
    xf.v[1][3] = 1.0f;
    xf.v[2][0] = 0.0f;
    xf.v[2][1] = 1.0f;
    xf.v[2][2] = 0.0f;
    xf.v[2][3] = 1.0f;
    xf.v[3][0] = 0.0f;
    xf.v[3][1] = 0.0f;
    xf.v[3][2] = 0.0f;
    xf.v[3][3] = 0.0f;
    func_001bebd0((f32 (*)[4])cam, px, D_00F56DC0 + 4112);
    for (i = 0; i < 15; i++) {
        cam[i] *= D_00F61378;
    }
    cam[i] *= D_00F61388;
    c->x0 = func_00f3f9d0(c->x0);
    c->x0 = func_00f26fb8(c->x0, 1776, 1824);
    func_00f3fe80(10080, func_00f3f9e8(c->x0));
    if (flag) {
        func_00f23230(10081, c, D_00F80590, D_00F6137C, (u16)(*(u64 *)(D_00F56DC0 + 88) >> 36) & 0xF, 0);
    }
    v[0] = (((GbDims *)g)->x6 >> 1) * 200.0f;
    v[1] = ((u16)(*(u64 *)(D_00F56DC0 + 88) >> 36) & 0xF) * 200.0f - 50.0f;
    v[2] = 0.0f;
    sceVu0UnitMatrix(m);
    sceVu0TransMatrix(m, m, v);
    sceVu0RotMatrixX(m, m, 3.1415926f);
    sceVu0MulMatrix(m, D_00F80650, m);
    c->x0 = func_00f3f9d0(c->x0);
    p = func_00f3fa80(c->x0);
    p[0] = 0x8000000048;
    p[1] = 66;
    p[2] = 0x5000D;
    p[3] = 71;
    p[4] = 0x720000006F00;
    p[5] = 24;
    c->x0 = p + 6;
    func_00f3fa98(p + 6);
    c->x0 = func_00f2b800(m, c->x0);
    p = func_00f3fa80(c->x0);
    p[0] = 68;
    p[1] = 66;
    c->x0 = p + 2;
    func_00f3fa98(p + 2);
    func_00f3fe80(10361, func_00f3f9e8(c->x0));
    if (*(s16 *)(D_00F56DC0 + 122) != 0) {
        c->x0 = func_00f3f9d0(c->x0);
        v[0] = 0.0f;
        v[3] = 1.0f;
        v[2] = 0.0f;
        v[1] = -(((GbDims *)g)->x8 * 200.0f);
        sceVu0UnitMatrix(m);
        sceVu0TransMatrix(m, m, v);
        sceVu0MulMatrix(m, D_00F80650, m);
        c->x0 = func_00f377b0(D_00F61380 * 90 / 128, ((GbDims *)g)->x6, ((GbDims *)g)->x8, ((GbDims *)g)->xA,
                              D_00F61880.x25C, D_00F61880.x260, *(u64 *)(D_00F56DC0 + 8944), 63, m, c->x0);
        v[1] = -((((u16)(*(u64 *)(D_00F56DC0 + 88) >> 36) & 0xF) + 1) * 200.0f);
        sceVu0UnitMatrix(m);
        sceVu0TransMatrix(m, m, v);
        sceVu0MulMatrix(m, D_00F80650, m);
        c->x0 = func_00f2cf58(c->x0, D_00F80650);
        func_00f3fe80(10362, func_00f3f9e8(c->x0));
    }
    r = 0;
    if (D_00F613B4 < 2 && D_00F61384 == 128) {
        r = func_00f2c000(10240, c);
    }
    if (r == 0) {
        func_00f293b0();
    }
    func_00f2c9f8(10490, c, box);
}
