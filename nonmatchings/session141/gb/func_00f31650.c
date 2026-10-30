/* drafttwins.py: score 331 -> 329, port.py of the wm twin func_00f58748 draft. Earlier header below. */
/* Round 41 wwm2: score 377 -> 331, port.py of the wm twin func_00f58748 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
typedef struct { u8 pad[64]; u8 r; u8 g; u8 b; u8 pad2; u8 r2; u8 g2; u8 b2; } G58748;
extern G58748 *D_00F56DC0;
extern s32 D_00F806C8;
extern u64 D_00F806D0[];
extern u8 D_00379F28[];
extern u8 D_0037A028[];
s32 func_00f31030(s32);
void func_00f32728(s32, s32);
void func_001bfac8(void); CONTEXT_ONLY void func_001bfac8() {}
void func_00f2e0b0(void); CONTEXT_ONLY void func_00f2e0b0() {}

void func_00f31650(s32 dir) {
    s32 to;
    s32 r, g, b, r2, g2, b2;
    s32 spd;
    s32 j;
    s32 c0;
    s32 i;
    s32 from;
    u64 *out;
    s32 c1;

    from = D_00F806C8;
    if (dir == 0) {
        D_00F806C8 = from - 1;
        spd = 40;
    } else {
        spd = 60;
        D_00F806C8 = from + 1;
    }
    to = D_00F806C8;
    for (i = 0; i < 40; i++) {
        out = D_00F806D0;
        for (j = 0; j < 8; j++) {
            c0 = func_00f31030(from + j) * 4;
            c1 = func_00f31030(to + j) * 4;
            r2 = (D_0037A028[c0] * (40 - i) + D_0037A028[c1] * i) / 40;
            b2 = (D_0037A028[c0 + 2] * (40 - i) + D_0037A028[c1 + 2] * i) / 40;
            r = (D_00379F28[c0] * (40 - i) + D_00379F28[c1] * i) / 40;
            g = (D_00379F28[c0 + 1] * (40 - i) + D_00379F28[c1 + 1] * i) / 40;
            g2 = (D_0037A028[c0 + 1] * (40 - i) + D_0037A028[c1 + 1] * i) / 40;
            b = (D_00379F28[c0 + 2] * (40 - i) + D_00379F28[c1 + 2] * i) / 40;
            if (j == 0) {
                D_00F56DC0->r = r;
                D_00F56DC0->g2 = g2;
                D_00F56DC0->b = b;
                D_00F56DC0->b2 = b2;
                D_00F56DC0->r2 = r2;
                D_00F56DC0->g = g;
            }
            *out++ = (r / 2) | ((u64)0xFE00 << 46) | ((u64)(b / 2) << 16) | 0x66000000 | ((g / 2) << 8);
        }
        func_00f32728(7, spd + i / 2);
        func_001bfac8();
    }
    c0 = func_00f31030(D_00F806C8) * 4;
    D_00F56DC0->r = D_00379F28[c0];
    D_00F56DC0->r2 = D_0037A028[c0];
    D_00F56DC0->g = D_00379F28[c0 + 1];
    D_00F56DC0->g2 = D_0037A028[c0 + 1];
    D_00F56DC0->b = D_00379F28[c0 + 2];
    D_00F56DC0->b2 = D_0037A028[c0 + 2];
    func_00f2e0b0();
}
