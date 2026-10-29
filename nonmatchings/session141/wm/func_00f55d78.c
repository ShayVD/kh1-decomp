/* 120 words left (524 vs 616): twin of f56538; m[4] array fixes the prologue, but target spills induction vars (frame 128) and keeps i*-432 as a mult. Tried 30 expression spellings. */
typedef struct { u8 pad[0x4C]; u16 f4C; u8 pad2[0x84 - 0x4E]; s16 f84; } W55d78;
void func_001bfac8(void);
s32 func_00f4aa20(s32);
s32 func_00f4aaf8(s32);
void func_00f55670(void *);
void func_00f55758(void *, s32, s32, s32, s32);
void func_00f55880(void *, s32);
void func_00f55900(void *);
extern W55d78 *D_00F9B540;
extern u8 D_00F9B548[];

void func_00f55d78(s32 n) {
    s32 m[4];
    s32 i;

    m[1] = D_00F9B540->f84;
    m[2] = func_00f4aa20(m[1]);
    m[0] = func_00f4aaf8(m[1]);
    m[3] = func_00f4aa20(m[2]);
    for (i = 0; i < n; i++) {
        func_00f55670(D_00F9B548);
        func_00f55758(D_00F9B548, m[0], (n - i) * 272 / n - 704, (n - i) * 5 * 32 / n + 192, (n - i) * 5 * 16 / n);
        func_00f55758(D_00F9B548, m[1], i * -432 / n, (n - i) * 5 * 32 / n + 352, 128 - i * 48 / n);
        func_00f55758(D_00F9B548, m[2], (n - i) * 432 / n, i * 5 * 32 / n + 352, i * 48 / n + 80);
        func_00f55758(D_00F9B548, m[3], (n - i) * 272 / n + 432, i * 5 * 32 / n + 192, i * 5 * 16 / n);
        func_00f55880(D_00F9B548, D_00F9B540->f4C - 1);
        func_00f55900(D_00F9B548);
        func_001bfac8();
    }
}
