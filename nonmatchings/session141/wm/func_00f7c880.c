/* func_00f7c880: score 64, 111 words differ. case 2: c[0] address not taken from the giv Round 30 (wgb, no gain): *D_0108FAA0[i] or ((u8 *)D_0108FAA0)[i * 4] for the case-2 [0] store, a chained store (56 words), D_0108FA98[i] = 0 after a = 0, a = [i][3] read before the switch (loses the s2 giv, worse), CONTEXT_ONLY callees (ctx2). Round 20 (wwm1): tools/ovl/i2a.py, the two constant initializers as ordered assignments: 111 -> 107 words, score 64 -> 50. Round 23 (wwm1): score 50 -> 48 with w4.py (dependency-checked statement order plus if/else polarity flips). */
extern s32 D_0108FA60[2];
extern s32 D_0108FA98[2];
extern u8 D_0108FAA0[2][4];
s32 func_00f20018(void);
void func_00f7a1a8(u8 (*)[4], s32 *, s32 *, s32);
void func_00f7c2e8(s32);
void func_00f7c510(s32);
void func_00f7b9a0(void);

void func_00f7c880(s32 *arg) {
    s32 xs[4];
    s32 ys[4];
    u8 col[4][4];
    s32 i;
    s32 a;
    s32 done;
    s32 v;

    done = 0;
    a = 0;
    for (i = 0; i < 2; i++) {
        D_0108FA60[i] = arg[i];
    }
    for (i = 0; i < 2; i++) {
        if (D_0108FA98[i] == 0) {
            continue;
        }
        switch (D_0108FA98[i]) {
        case 1:
            a = D_0108FAA0[i][3] + 16;
            if (a >= 128) {
                a = 128;
            }
            D_0108FAA0[i][3] = a;
            D_0108FAA0[i][2] = a;
            D_0108FAA0[i][1] = a;
            D_0108FAA0[i][0] = a;
            break;
        case 2:
            a = D_0108FAA0[i][3] - 16;
            if (a < 0) {
                D_0108FA98[i] = 0;
                a = 0;
            }
            D_0108FAA0[i][3] = a;
            D_0108FAA0[i][2] = a;
            D_0108FAA0[i][1] = a;
            D_0108FAA0[i][0] = a;
            break;
        }
        if (!done && func_00f20018()) {
            v = a * 58 / 128;
            col[0][0] = 0;
            col[1][0] = 0;
            col[2][0] = 0;
            col[3][0] = 0;
            col[0][1] = 0;
            col[1][1] = 0;
            col[2][1] = 0;
            col[3][1] = 0;
            col[0][2] = 0;
            col[1][2] = 0;
            col[2][2] = 0;
            col[1][3] = v;
            col[3][2] = 0;
            col[0][3] = v;
            col[2][3] = v;
            xs[0] = 0;
            ys[0] = 42;
            xs[1] = 512;
            ys[1] = 42;
            xs[2] = 0;
            col[3][3] = v;
            done = 1;
            ys[2] = 384;
            xs[3] = 512;
            ys[3] = 384;
            func_00f7a1a8(col, xs, ys, 68);
        }
        func_00f7c2e8(i);
        func_00f7c510(i);
    }
    if (D_0108FA60[0] != arg[0]) {
        func_00f7b9a0();
    }
    for (i = 0; i < 2; i++) {
        arg[i] = D_0108FA60[i];
    }
}
