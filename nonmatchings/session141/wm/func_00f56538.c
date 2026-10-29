/* 115 words left (520 vs 584): target spills induction vars to stack (frame 128 vs 112), n in s8, reloads &D_00F9B548 each call. Explicit counters variant was worse (131). */
typedef struct { u8 pad[0x4C]; u16 f4C; u8 pad2[0x84 - 0x4E]; s16 f84; } W56538;
void func_001bfac8(void);
s32 func_00f4aa20(s32);
s32 func_00f4aaf8(s32);
void func_00f55670(void *);
void func_00f55758(void *, s32, s32, s32, s32);
void func_00f55880(void *, s32);
void func_00f55900(void *);
extern W56538 *D_00F9B540;
extern u8 D_00F9B548[];

void func_00f56538(s32 n) {
    s32 m0;
    s32 m1;
    s32 m2;
    s32 m3;
    s32 i;

    m2 = D_00F9B540->f84;
    m3 = func_00f4aa20(m2);
    m1 = func_00f4aaf8(m2);
    m0 = func_00f4aaf8(m1);
    for (i = 0; i < n; i++) {
        func_00f55670(D_00F9B548);
        func_00f55758(D_00F9B548, m0, i * 272 / n - 704, i * 5 * 32 / n + 192, i * 5 * 16 / n);
        func_00f55758(D_00F9B548, m1, (n - i) * -432 / n, i * 5 * 32 / n + 352, i * 48 / n + 80);
        func_00f55758(D_00F9B548, m2, i * 432 / n, -(i * 5 * 32) / n + 512, 128 - i * 48 / n);
        func_00f55758(D_00F9B548, m3, i * 272 / n + 432, -(i * 5 * 32) / n + 352, (n - i) * 80 / n);
        func_00f55880(D_00F9B548, D_00F9B540->f4C - 1);
        func_00f55900(D_00F9B548);
        func_001bfac8();
    }
}
