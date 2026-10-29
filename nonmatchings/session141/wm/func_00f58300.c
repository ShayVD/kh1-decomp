/* 89 words left (452 vs 464): constant hoisting/order differs. */
void func_0011d140(s32, s32);
s32 func_00f58128(s32);
void func_00f59820(s32, s32);
void func_00f59870(s32, s32, s32, s32, s32);
void func_00f55358(s32);
void func_001bfac8(void);
extern u8 D_00379F28[];
extern s32 D_0108CE88;
extern u64 D_0108CE90[8];

void func_00f58300(void) {
    s32 n = 40;
    s32 i;
    s32 j;
    u8 *c;
    s32 a;

    func_0011d140(0xE2D7, 0);
    for (i = 0; i < n; i++) {
        for (j = 0; j < 8; j++) {
            c = &D_00379F28[func_00f58128(D_0108CE88 + j) * 4];
            a = (n - i) * 102 / n;
            D_0108CE90[j] = (u64)(c[0] >> 1) | ((u64)0x3F800000 << 32)
                | (((u64)(c[2] >> 1) << 16) | ((u64)(c[1] >> 1) << 8)) | ((u64)a << 24);
        }
        func_00f59820(7, (39 - i) / 2);
        func_00f59870(5, i * 93 / n + 35, i * 93 / n + 35, i * 63 / n + 65, 128);
        func_00f55358(i * 58 / n + 70);
        func_001bfac8();
    }
    func_00f59820(7, 0);
    func_00f59870(5, 128, 128, 128, 128);
    func_00f55358(128);
}
