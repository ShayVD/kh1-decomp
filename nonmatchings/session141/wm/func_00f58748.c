/* 202 words left (round 12): 40-frame palette crossfade (D_00379F28/D_0037A028 -> D_0108CE90). Frame is 112 vs 96 in the target, so locals are wrong; a 2D-array table variant was worse. Start by getting the frame size right. Round 19 (wwm1): 202 -> 191 raw words with sclimb.py (CONTEXT_ONLY toggles plus dependency-checked statement moves). */
typedef struct { u8 pad[64]; u8 r; u8 g; u8 b; u8 pad2; u8 r2; u8 g2; u8 b2; } G58748;
extern G58748 *D_00F9B540;
extern s32 D_0108CE88;
extern u64 D_0108CE90[];
extern u8 D_00379F28[];
extern u8 D_0037A028[];
s32 func_00f58128(s32);
void func_00f59820(s32, s32);
void func_001bfac8(void); CONTEXT_ONLY void func_001bfac8() {}
void func_00f551a8(void); CONTEXT_ONLY void func_00f551a8() {}

void func_00f58748(s32 dir) {
    s32 r, g, b, r2, g2, b2;
    s32 from;
    s32 i;
    s32 to;
    s32 c0;
    s32 spd;
    s32 j;
    s32 c1;
    u64 *out;

    from = D_0108CE88;
    if (dir == 0) {
        spd = 40;
        D_0108CE88 = from - 1;
    } else {
        D_0108CE88 = from + 1;
        spd = 60;
    }
    to = D_0108CE88;
    for (i = 0; i < 40; i++) {
        out = D_0108CE90;
        for (j = 0; j < 8; j++) {
            c0 = func_00f58128(from + j) * 4;
            c1 = func_00f58128(to + j) * 4;
            r = (D_00379F28[c0] * (40 - i) + D_00379F28[c1] * i) / 40;
            r2 = (D_0037A028[c0] * (40 - i) + D_0037A028[c1] * i) / 40;
            b2 = (D_0037A028[c0 + 2] * (40 - i) + D_0037A028[c1 + 2] * i) / 40;
            g2 = (D_0037A028[c0 + 1] * (40 - i) + D_0037A028[c1 + 1] * i) / 40;
            g = (D_00379F28[c0 + 1] * (40 - i) + D_00379F28[c1 + 1] * i) / 40;
            b = (D_00379F28[c0 + 2] * (40 - i) + D_00379F28[c1 + 2] * i) / 40;
            if (j == 0) {
                D_00F9B540->b = b;
                D_00F9B540->g2 = g2;
                D_00F9B540->r = r;
                D_00F9B540->g = g;
                D_00F9B540->r2 = r2;
                D_00F9B540->b2 = b2;
            }
            *out++ = (r / 2) | ((u64)0xFE00 << 46) | ((u64)(b / 2) << 16) | 0x66000000 | ((g / 2) << 8);
        }
        func_00f59820(7, spd + i / 2);
        func_001bfac8();
    }
    c0 = func_00f58128(D_0108CE88) * 4;
    D_00F9B540->r = D_00379F28[c0];
    D_00F9B540->b = D_00379F28[c0 + 2];
    D_00F9B540->g2 = D_0037A028[c0 + 1];
    D_00F9B540->r2 = D_0037A028[c0];
    D_00F9B540->b2 = D_0037A028[c0 + 2];
    D_00F9B540->g = D_00379F28[c0 + 1];
    func_00f551a8();
}
