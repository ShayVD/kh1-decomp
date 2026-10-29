/* gb.x func_00f333f8 near miss: 280 words differ, score 220 (ours 1360 bytes, original 1392). Camera fly-in/out over 30 frames: the GbXf D_00F80960 (v[4], pos, rot) is copied to a local xf, start vectors are built from World fields (s32 at 4308/4312 * PI / 2048, u16 166/170 * 200 * 0.5, the p5C.y nibble at 88, f32 at 136) and the D_00F56DC4 box, then func_001be988 interpolates rot/pos/v[0] each frame (in reverse when arg != 2), followed by func_001bebd0 and func_00f36020. Logic is complete. PI must be written 3.1415926f to get 0x40490fda. Left: (1) the original keeps a dead division-by-30 trap (li v1,30; beqzl v1; break) next to the i / 2 shift in both branches (ours, written i * 15 / 30, folds cleanly; a variable n = 30 gives a real div, 368); (2) the setup store order and the 1.0f register (f4 in the original). A 300 s hill climb over the setup block cut words differ to 263 but raised the score to 256. wm twin: func_00f5a4f0 (same score). */
typedef struct { OvlVec v[4]; OvlVec pos; OvlVec rot; } GbXf;
typedef struct { u8 pad[4]; u32 ax : 4; u32 ay : 4; u32 az : 4; u32 ar : 4; u32 bx : 4; u32 by : 4; u32 bz : 4; u32 br : 4; } Box;
extern u8 *D_00F56DC0;
extern Box *D_00F56DC4;
extern u8 D_00F56DC8[];
extern s32 D_00F56D98;
extern GbXf D_00F80960;
extern s32 D_00F809C0;
extern OvlMtx D_00F80860[4];
void func_00f33380(s32);
void func_00f29400(s32);
void func_00f25518(GbXf *);
void func_001bea58(f32 *, f32 *);
void func_00f20248(s32);
void func_00f20290(s32);
void func_001c0078(s32);
void func_001bfac8(void);
void func_001be988(f32 *, f32 *, f32 *, s32, s32);
void func_00f32728(s32, s32);
void func_001be9f0(f32 *);
void func_001bebd0(OvlMtx *, GbXf *, void *);
void func_00f36020(s32, s32, void *, s32, s32, void *, void *);
void func_00f2b9b8(void *, Box *, s32);
s32 func_001c00e8(s32, void *, kh1_u128);
void func_00f333a0(void);

void func_00f333f8(s32 arg) {
    OvlVec v[5];
    f32 ra[3];
    f32 rb[3];
    GbXf xf;
    s32 h;
    s32 i;
    s32 base;
    s32 k;
    func_00f33380(128);
    h = *(s16 *)(D_00F56DC0 + 118);
    func_00f29400(0);
    if (arg == 2) {
        func_00f25518(&D_00F80960);
        D_00F80960.v[0][2] += *(u16 *)(D_00F56DC0 + 166) * 100;
    }
    xf = D_00F80960;
    v[0][0] = (s32)D_00F56DC4->ax;
    v[0][1] = (s32)D_00F56DC4->ay;
    v[0][2] = (s32)D_00F56DC4->az;
    v[1][0] = (s32)D_00F56DC4->bx;
    v[1][1] = (s32)D_00F56DC4->by;
    v[1][2] = (s32)D_00F56DC4->bz;
    v[2][0] = *(s32 *)(D_00F56DC0 + 4308) * 3.1415926f * 0.00048828125f;
    v[2][1] = *(s32 *)(D_00F56DC0 + 4312) * 3.1415926f * 0.00048828125f;
    v[2][2] = 0.0f;
    v[2][3] = 0.0f;
    v[3][0] = -(*(u16 *)(D_00F56DC0 + 166) * 200.0f) * 0.5f;
    v[3][1] = ((u16)(*(u64 *)(D_00F56DC0 + 88) >> 36) & 0xF) * 200.0f;
    v[3][2] = -(*(u16 *)(D_00F56DC0 + 170) * 200.0f) * 0.5f;
    v[3][3] = 0.0f;
    v[4][0] = 0.0f;
    v[4][1] = 0.0f;
    v[4][2] = *(f32 *)(D_00F56DC0 + 136);
    v[4][3] = 0.0f;
    D_00F80960.v[1][0] = 0.0f;
    D_00F80960.v[1][1] = 0.0f;
    D_00F80960.v[1][2] = 1.0f;
    D_00F80960.v[1][3] = 1.0f;
    D_00F80960.v[2][0] = 0.0f;
    D_00F80960.v[2][1] = 1.0f;
    D_00F80960.v[2][2] = 0.0f;
    D_00F80960.v[2][3] = 1.0f;
    D_00F80960.v[3][0] = 0.0f;
    D_00F80960.v[3][1] = 0.0f;
    D_00F80960.v[3][2] = 0.0f;
    D_00F80960.v[3][3] = 0.0f;
    for (i = 0; i < 3; i++) {
        ra[i] = 0.0f;
        rb[i] = 0.0f;
    }
    if (arg == 2) {
        func_001bea58(v[2], xf.rot);
        rb[1] = 1.5707963f;
    } else {
        func_001bea58(xf.rot, v[2]);
        ra[1] = 1.5707963f;
    }
    if (arg == 2) {
        func_00f20248(12);
    } else {
        func_001c0078(D_00F809C0);
        func_001bfac8();
    }
    base = h * 15;
    for (i = 0; i < 30; i++) {
        if (arg == 2) {
            func_001be988(D_00F80960.rot, v[2], xf.rot, i, 30);
            func_001be988(D_00F80960.pos, v[3], xf.pos, i, 30);
            func_001be988(D_00F80960.v[0], v[4], xf.v[0], i, 30);
            k = base + i * 15 / 30;
            func_00f32728(5, k);
        } else {
            func_001be988(D_00F80960.rot, xf.rot, v[2], i, 30);
            func_001be988(D_00F80960.pos, xf.pos, v[3], i, 30);
            func_001be988(D_00F80960.v[0], xf.v[0], v[4], i, 30);
            func_00f32728(5, base + i * 15 / 30);
            k = base - i * 15 / 30;
        }
        func_001be9f0(D_00F80960.rot);
        func_001bebd0(D_00F80860, &D_00F80960, D_00F56DC0 + 4112);
        func_00f32728(5, k % 45);
        if (D_00F56D98 == 0) {
            func_00f36020(1, 12160, D_00F56DC8, 1776, 1824, D_00F80860, D_00F56DC0 + 160);
            func_00f2b9b8(D_00F56DC8, D_00F56DC4, 0);
        }
        if (i < 29) {
            func_001bfac8();
        }
    }
    if (arg == 2) {
        D_00F809C0 = func_001c00e8(-1, func_00f333a0, 0);
    } else {
        func_00f20290(12);
        func_00f29400(1);
    }
}
