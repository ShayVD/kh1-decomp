/* Round 42 (wgb): score 172 -> 120 (124 -> 85 words differ, size exact). The frame count is now a local n = 30, used for the loop bound, the func_001be988 count arguments and the helper's divisor. Because the divisor is no longer a literal at loop time, loop.c no longer hoists a 30 into s8: s8 now holds sp+64 (v[4]) as in the target, and the trap's 30 is loaded in each arm. Statement order from hill3 with the size guard (420 s, seed 42); the first arm now has the same shape as the second (call with base + helper, then k = base + i * 15 / 30), which fixes the k register. Left: the setup block schedule before the loop. Earlier header below. */
/* Round 41 (wgb): score 174 -> 172, size now exact (1392 bytes, 278 -> 124 words differ). The inline helper part5a4f0 is now used in both arms, so both of the target's li 30 / beqzl / break 7 checks appear. Box.ax is declared u16 ax : 4, because the target reads ax with its own lhu 4 while the other fields come out of one lw 4. Statement order from hill3 (400 s, seed 7). What is left: loop.c hoists the two 30s into one register that gets s8, whereas in the target s8 holds sp+64 (v[4]) and 30 is rematerialised as li v1,30 in each arm. Under nostrict the size is also exact, but the separate Box loads cost more. Earlier header below. */
/* Round 42 wwm2: score 196 -> 174, port.py of the wm twin func_00f5a4f0 draft. Earlier header below. */
/* Round 41 wwm2: score 220 -> 196, port.py of the wm twin func_00f5a4f0 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
typedef struct { OvlVec v[4]; OvlVec pos; OvlVec rot; } GbXf;
typedef struct { u8 pad[4]; u16 ax : 4; u32 ay : 4; u32 az : 4; u32 ar : 4; u32 bx : 4; u32 by : 4; u32 bz : 4; u32 br : 4; } Box;
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

static inline s32 part5a4f0(s32 t, s32 n) {
    s32 q = t / n;
    return t * 15 / 30;
}

void func_00f333f8(s32 arg) {
    OvlVec v[5];
    f32 ra[3];
    f32 rb[3];
    GbXf xf;
    s32 h;
    s32 i;
    s32 base;
    s32 k;
    s32 n;
    func_00f33380(128);
    h = *(s16 *)(D_00F56DC0 + 118);
    func_00f29400(0);
    if (arg == 2) {
        func_00f25518(&D_00F80960);
        D_00F80960.v[0][2] += *(u16 *)(D_00F56DC0 + 166) * 100;
    }
    xf = D_00F80960;
    v[2][1] = *(s32 *)(D_00F56DC0 + 4312) * 3.1415926f * 0.00048828125f;
    v[0][0] = (s32)D_00F56DC4->ax;
    v[4][3] = 0.0f;
    v[2][3] = 0.0f;
    v[2][0] = *(s32 *)(D_00F56DC0 + 4308) * 3.1415926f * 0.00048828125f;
    v[0][1] = (s32)D_00F56DC4->ay;
    v[3][1] = ((u16)(*(u64 *)(D_00F56DC0 + 88) >> 36) & 0xF) * 200.0f;
    v[0][2] = (s32)D_00F56DC4->az;
    v[1][0] = (s32)D_00F56DC4->bx;
    v[2][2] = 0.0f;
    v[3][2] = -(*(u16 *)(D_00F56DC0 + 170) * 200.0f) * 0.5f;
    v[3][3] = 0.0f;
    v[4][0] = 0.0f;
    v[1][2] = (s32)D_00F56DC4->bz;
    v[4][1] = 0.0f;
    v[1][1] = (s32)D_00F56DC4->by;
    v[4][2] = *(f32 *)(D_00F56DC0 + 136);
    v[3][0] = -(*(u16 *)(D_00F56DC0 + 166) * 200.0f) * 0.5f;
    D_00F80960.v[1][0] = 0.0f;
    D_00F80960.v[1][1] = 0.0f;
    D_00F80960.v[1][2] = 1.0f;
    D_00F80960.v[2][1] = 1.0f;
    D_00F80960.v[2][0] = 0.0f;
    D_00F80960.v[1][3] = 1.0f;
    D_00F80960.v[3][3] = 0.0f;
    D_00F80960.v[2][2] = 0.0f;
    D_00F80960.v[3][0] = 0.0f;
    D_00F80960.v[3][1] = 0.0f;
    D_00F80960.v[3][2] = 0.0f;
    D_00F80960.v[2][3] = 1.0f;
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
    n = 30;
    for (i = 0; i < n; i++) {
        if (arg == 2) {
            func_001be988(D_00F80960.rot, v[2], xf.rot, i, n);
            func_001be988(D_00F80960.pos, v[3], xf.pos, i, n);
            func_001be988(D_00F80960.v[0], v[4], xf.v[0], i, n);
            func_00f32728(5, base + part5a4f0(i, n));
            k = base + i * 15 / 30;
        } else {
            func_001be988(D_00F80960.rot, xf.rot, v[2], i, n);
            func_001be988(D_00F80960.pos, xf.pos, v[3], i, n);
            func_001be988(D_00F80960.v[0], xf.v[0], v[4], i, n);
            func_00f32728(5, base + part5a4f0(i, n));
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
