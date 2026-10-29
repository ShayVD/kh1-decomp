/* 204 words / score 377 (852 vs 856); logic complete (40-step lerp of 8 palette entries between D_00379F28/D_0037A028 rows, j==0 also writes world colours). Frame 112 vs 96 (ours spills &D_00F56DC0 with sq); orig hoists D_0037A028 into s8 and 40 into s3, does all six divides before the j==0 block; scheduling differs throughout. No variants tried yet */
typedef struct { u8 pad0[0x40]; u8 c0[4]; u8 c1[4]; } GbWorld;
extern GbWorld *D_00F56DC0;
extern s32 D_00F806C8;
extern u64 D_00F806D0[];
extern u8 D_00379F28[];
extern u8 D_0037A028[];
s32 func_00f31030(s32);
void func_00f32728(s32, s32);
void func_001bfac8(void);
void func_00f2e0b0(void);

void func_00f31650(s32 dir) {
    s32 old = D_00F806C8;
    s32 cur;
    s32 delay;
    u64 *out;
    s32 t, j, a, b;
    s32 r0, g0, b0, r1, g1, b1;
    if (dir == 0) {
        D_00F806C8 = old - 1;
        delay = 40;
    } else {
        delay = 60;
        D_00F806C8 = old + 1;
    }
    cur = D_00F806C8;
    for (t = 0; t < 40; t++) {
        out = D_00F806D0;
        for (j = 0; j < 8; j++) {
            a = func_00f31030(old + j) * 4;
            b = func_00f31030(cur + j) * 4;
            r0 = (D_00379F28[a] * (40 - t) + D_00379F28[b] * t) / 40;
            g0 = (D_00379F28[a + 1] * (40 - t) + D_00379F28[b + 1] * t) / 40;
            b0 = (D_00379F28[a + 2] * (40 - t) + D_00379F28[b + 2] * t) / 40;
            r1 = (D_0037A028[a] * (40 - t) + D_0037A028[b] * t) / 40;
            g1 = (D_0037A028[a + 1] * (40 - t) + D_0037A028[b + 1] * t) / 40;
            b1 = (D_0037A028[a + 2] * (40 - t) + D_0037A028[b + 2] * t) / 40;
            if (j == 0) {
                D_00F56DC0->c0[0] = r0;
                D_00F56DC0->c0[1] = g0;
                D_00F56DC0->c0[2] = b0;
                D_00F56DC0->c1[0] = r1;
                D_00F56DC0->c1[1] = g1;
                D_00F56DC0->c1[2] = b1;
            }
            *out++ = (r0 / 2) | 0x3F80000000000000 | ((u64)(b0 / 2) << 16 | 0x66000000) | ((g0 / 2) << 8);
        }
        func_00f32728(7, delay + t / 2);
        func_001bfac8();
    }
    a = func_00f31030(D_00F806C8) * 4;
    D_00F56DC0->c0[0] = D_00379F28[a];
    D_00F56DC0->c0[1] = D_00379F28[a + 1];
    D_00F56DC0->c0[2] = D_00379F28[a + 2];
    D_00F56DC0->c1[0] = D_0037A028[a];
    D_00F56DC0->c1[1] = D_0037A028[a + 1];
    D_00F56DC0->c1[2] = D_0037A028[a + 2];
    func_00f2e0b0();
}
