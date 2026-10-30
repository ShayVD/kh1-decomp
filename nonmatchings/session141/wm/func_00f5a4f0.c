/* drafttwins.py: score 172 -> 120, port.py of the gb twin func_00f333f8 draft. Earlier header below. */
/* drafttwins.py: score 174 -> 172, port.py of the gb twin func_00f333f8 draft. Earlier header below. */
typedef struct { OvlVec v[4]; OvlVec pos; OvlVec rot; } GbXf;
typedef struct { u8 pad[4]; u16 ax : 4; u32 ay : 4; u32 az : 4; u32 ar : 4; u32 bx : 4; u32 by : 4; u32 bz : 4; u32 br : 4; } Box;
extern u8 *D_00F9B540;
extern Box *D_00F9B544;
extern u8 D_00F9B548[];
extern s32 D_00F9B518;
extern GbXf D_0108D120;
extern s32 D_0108D180;
extern OvlMtx D_0108D020[4];
void func_00f5a478(s32);
void func_00f504f8(s32);
void func_00f4c610(GbXf *);
void func_001bea58(f32 *, f32 *);
void func_00f47340(s32);
void func_00f47388(s32);
void func_001c0078(s32);
void func_001bfac8(void);
void func_001be988(f32 *, f32 *, f32 *, s32, s32);
void func_00f59820(s32, s32);
void func_001be9f0(f32 *);
void func_001bebd0(OvlMtx *, GbXf *, void *);
void func_00f5d118(s32, s32, void *, s32, s32, void *, void *);
void func_00f52ab0(void *, Box *, s32);
s32 func_001c00e8(s32, void *, kh1_u128);
void func_00f5a498(void);

static inline s32 part5a4f0(s32 t, s32 n) {
    s32 q = t / n;
    return t * 15 / 30;
}

void func_00f5a4f0(s32 arg) {
    OvlVec v[5];
    f32 ra[3];
    f32 rb[3];
    GbXf xf;
    s32 h;
    s32 i;
    s32 base;
    s32 k;
    s32 n;
    func_00f5a478(128);
    h = *(s16 *)(D_00F9B540 + 118);
    func_00f504f8(0);
    if (arg == 2) {
        func_00f4c610(&D_0108D120);
        D_0108D120.v[0][2] += *(u16 *)(D_00F9B540 + 166) * 100;
    }
    xf = D_0108D120;
    v[2][1] = *(s32 *)(D_00F9B540 + 4312) * 3.1415926f * 0.00048828125f;
    v[0][0] = (s32)D_00F9B544->ax;
    v[4][3] = 0.0f;
    v[2][3] = 0.0f;
    v[2][0] = *(s32 *)(D_00F9B540 + 4308) * 3.1415926f * 0.00048828125f;
    v[0][1] = (s32)D_00F9B544->ay;
    v[3][1] = ((u16)(*(u64 *)(D_00F9B540 + 88) >> 36) & 0xF) * 200.0f;
    v[0][2] = (s32)D_00F9B544->az;
    v[1][0] = (s32)D_00F9B544->bx;
    v[2][2] = 0.0f;
    v[3][2] = -(*(u16 *)(D_00F9B540 + 170) * 200.0f) * 0.5f;
    v[3][3] = 0.0f;
    v[4][0] = 0.0f;
    v[1][2] = (s32)D_00F9B544->bz;
    v[4][1] = 0.0f;
    v[1][1] = (s32)D_00F9B544->by;
    v[4][2] = *(f32 *)(D_00F9B540 + 136);
    v[3][0] = -(*(u16 *)(D_00F9B540 + 166) * 200.0f) * 0.5f;
    D_0108D120.v[1][0] = 0.0f;
    D_0108D120.v[1][1] = 0.0f;
    D_0108D120.v[1][2] = 1.0f;
    D_0108D120.v[2][1] = 1.0f;
    D_0108D120.v[2][0] = 0.0f;
    D_0108D120.v[1][3] = 1.0f;
    D_0108D120.v[3][3] = 0.0f;
    D_0108D120.v[2][2] = 0.0f;
    D_0108D120.v[3][0] = 0.0f;
    D_0108D120.v[3][1] = 0.0f;
    D_0108D120.v[3][2] = 0.0f;
    D_0108D120.v[2][3] = 1.0f;
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
        func_00f47340(12);
    } else {
        func_001c0078(D_0108D180);
        func_001bfac8();
    }
    base = h * 15;
    n = 30;
    for (i = 0; i < n; i++) {
        if (arg == 2) {
            func_001be988(D_0108D120.rot, v[2], xf.rot, i, n);
            func_001be988(D_0108D120.pos, v[3], xf.pos, i, n);
            func_001be988(D_0108D120.v[0], v[4], xf.v[0], i, n);
            func_00f59820(5, base + part5a4f0(i, n));
            k = base + i * 15 / 30;
        } else {
            func_001be988(D_0108D120.rot, xf.rot, v[2], i, n);
            func_001be988(D_0108D120.pos, xf.pos, v[3], i, n);
            func_001be988(D_0108D120.v[0], xf.v[0], v[4], i, n);
            func_00f59820(5, base + part5a4f0(i, n));
            k = base - i * 15 / 30;
        }
        func_001be9f0(D_0108D120.rot);
        func_001bebd0(D_0108D020, &D_0108D120, D_00F9B540 + 4112);
        func_00f59820(5, k % 45);
        if (D_00F9B518 == 0) {
            func_00f5d118(1, 12160, D_00F9B548, 1776, 1824, D_0108D020, D_00F9B540 + 160);
            func_00f52ab0(D_00F9B548, D_00F9B544, 0);
        }
        if (i < 29) {
            func_001bfac8();
        }
    }
    if (arg == 2) {
        D_0108D180 = func_001c00e8(-1, func_00f5a498, 0);
    } else {
        func_00f47388(12);
        func_00f504f8(1);
    }
}
