/* 217 words / score 367 (980 vs 968). Logic complete; sibling of f31650 (same palette lerp family). Orig hoists &D_00379F28/&D_0037A028/&D_00F56DC0 into s5/s6/s7, keeps old in s8 and 40 in s3; ours spills old and base. Frame 144 vs ours 160. No variants tried. */
typedef struct { u8 pad0[0x40]; u8 c0[4]; u8 c1[4]; } GbWorld;
typedef struct { s8 v[40]; } GbSeq;
extern GbWorld *D_00F56DC0;
extern s32 D_00F806C8;
extern GbSeq D_00F71780;
extern u8 D_00379F28[];
extern u8 D_0037A028[];
s32 func_00f31030(s32);
void func_0011d140(s32, s32);
void func_001c01b0(s32, void *, s32, s32);
void func_00f319a8(void);
void func_00f32728(s32, s32);
void func_00f313d8(s32, s32, s32, s32);
void func_001bfac8(void);
void func_00f2e0b0(void);

void func_00f31ad8(s32 dir) {
    GbSeq seq = D_00F71780;
    s32 old = D_00F806C8;
    s32 cur, base, i, k, n, a, b, h;
    if (dir == 0) {
        D_00F806C8 = old - 1;
        base = 40;
    } else {
        D_00F806C8 = old + 1;
        base = 60;
    }
    cur = D_00F806C8 & 7;
    D_00F806C8 = cur;
    func_0011d140(0xE2D5, 0);
    for (i = 0; i < 40; i++) {
        k = i / 4;
        if (k < 8 && (i & 3) == 0) {
            n = k;
            if (dir)
                n = 8 - n;
            func_001c01b0(-1, func_00f319a8, n & 7, func_00f31030(old + n));
        }
        a = func_00f31030(old) * 4;
        h = i / 2;
        b = func_00f31030(cur) * 4;
        D_00F56DC0->c0[0] = (D_00379F28[b] - D_00379F28[a]) * i / 40 + D_00379F28[a];
        D_00F56DC0->c0[1] = (D_00379F28[b + 1] - D_00379F28[a + 1]) * i / 40 + D_00379F28[a + 1];
        D_00F56DC0->c0[2] = (D_00379F28[b + 2] - D_00379F28[a + 2]) * i / 40 + D_00379F28[a + 2];
        D_00F56DC0->c1[0] = (D_0037A028[b] - D_0037A028[a]) * i / 40 + D_0037A028[a];
        D_00F56DC0->c1[1] = (D_0037A028[b + 1] - D_0037A028[a + 1]) * i / 40 + D_0037A028[a + 1];
        D_00F56DC0->c1[2] = (D_0037A028[b + 2] - D_0037A028[a + 2]) * i / 40 + D_0037A028[a + 2];
        func_00f32728(7, base + h);
        if (dir)
            h = (39 - i) / 2;
        if (seq.v[h] >= 0)
            func_00f313d8(seq.v[h], D_00379F28[b], D_00379F28[b + 1], D_00379F28[b + 2]);
        func_001bfac8();
    }
    D_00F56DC0->c0[0] = D_00379F28[b];
    D_00F56DC0->c0[1] = D_00379F28[b + 1];
    D_00F56DC0->c0[2] = D_00379F28[b + 2];
    D_00F56DC0->c1[0] = D_0037A028[b];
    D_00F56DC0->c1[1] = D_0037A028[b + 1];
    D_00F56DC0->c1[2] = D_0037A028[b + 2];
    func_00f2e0b0();
}
