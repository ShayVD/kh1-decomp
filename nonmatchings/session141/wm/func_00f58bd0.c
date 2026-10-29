/* 190 words, score 289 (964 vs 968; was 206/309). Round 33 wwm2: hill2 (c[5] before c[4] in the loop, c[0] last in the tail block); ctx2 and interleave give nothing. Earlier header: 206 words left (round 12): 40-frame palette crossfade with sound (sibling of func_00f58748). Target hoists D_00379F28, D_0037A028 and &D_00F9B540 into s5..s7 and keeps dir, spd and to on the stack (frame 144 vs our 160). We do not hoist, and we keep c1+1 and c1+2 live instead. */
typedef struct { u8 pad[64]; u8 c[8]; } G58bd0;
typedef struct { s8 t[40]; } T58bd0;
extern G58bd0 *D_00F9B540;
extern s32 D_0108CE88;
extern T58bd0 D_00FB7830;
extern u8 D_00379F28[];
extern u8 D_0037A028[];
s32 func_00f58128(s32);
void func_0011d140(s32, s32);
void func_00f58aa0(void);
void func_001c01b0(s32, void (*)(void), s32, s32);
void func_00f59820(s32, s32);
void func_00f584d0(s32, s32, s32, s32);
void func_001bfac8(void);
void func_00f551a8(void);

void func_00f58bd0(s32 dir) {
    T58bd0 tbl;
    s32 from;
    s32 to;
    s32 spd;
    s32 i;
    s32 h;
    s32 c0;
    s32 c1;

    tbl = D_00FB7830;
    from = D_0108CE88;
    if (dir == 0) {
        D_0108CE88 = from - 1;
        spd = 40;
    } else {
        D_0108CE88 = from + 1;
        spd = 60;
    }
    to = D_0108CE88 & 7;
    D_0108CE88 = to;
    func_0011d140(0xE2D5, 0);
    for (i = 0; i < 40; i++) {
        if (i / 4 < 8 && (i & 3) == 0) {
            c0 = i / 4;
            if (dir) c0 = 8 - c0;
            func_001c01b0(-1, func_00f58aa0, c0 & 7, func_00f58128(from + c0));
        }
        c0 = func_00f58128(from) * 4;
        h = i / 2;
        c1 = func_00f58128(to) * 4;
        D_00F9B540->c[0] = D_00379F28[c0] + (D_00379F28[c1] - D_00379F28[c0]) * i / 40;
        D_00F9B540->c[1] = D_00379F28[c0 + 1] + (D_00379F28[c1 + 1] - D_00379F28[c0 + 1]) * i / 40;
        D_00F9B540->c[2] = D_00379F28[c0 + 2] + (D_00379F28[c1 + 2] - D_00379F28[c0 + 2]) * i / 40;
        D_00F9B540->c[6] = D_0037A028[c0 + 2] + (D_0037A028[c1 + 2] - D_0037A028[c0 + 2]) * i / 40;
        D_00F9B540->c[5] = D_0037A028[c0 + 1] + (D_0037A028[c1 + 1] - D_0037A028[c0 + 1]) * i / 40;
        D_00F9B540->c[4] = D_0037A028[c0] + (D_0037A028[c1] - D_0037A028[c0]) * i / 40;
        func_00f59820(7, spd + h);
        if (dir) h = (39 - i) / 2;
        if (tbl.t[h] >= 0) {
            { u8 *q = &D_00379F28[c1]; func_00f584d0(tbl.t[h], q[0], q[1], q[2]); }
        }
        func_001bfac8();
    }
    D_00F9B540->c[1] = D_00379F28[c1 + 1];
    D_00F9B540->c[2] = D_00379F28[c1 + 2];
    D_00F9B540->c[4] = D_0037A028[c1];
    D_00F9B540->c[5] = D_0037A028[c1 + 1];
    D_00F9B540->c[0] = D_00379F28[c1];
    D_00F9B540->c[6] = D_0037A028[c1 + 2];
    func_00f551a8();
}
