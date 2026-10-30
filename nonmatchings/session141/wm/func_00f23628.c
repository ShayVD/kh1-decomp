/* Round 36 (wgb): wm.x func_00f23628 near miss: 128 -> 127 words, score 81 -> 73 (aligned diff 57 -> 53). Statement order from tools/ovl/hill3.py (score-ranked, strict dependency rules). Tried: hill3 sweep of every gb RANKING row and wm RANKING rows 1-100 (85-90 s, seed 1; strict rules; the order kept passes hill3.py --check against the previous draft), and port.py from the twin (not better). Earlier header below. */
/* 128 words left (596 vs 568): globals D_00F850BC/C0/C4/D_00F8C23C must stay as %hi in s-regs with %lo uses (target) instead of full addresses; frame 80 vs 64. func_00f66240-style m2c extra args not the issue here. Tried call/ternary shapes and all modes. Round 22 (wwm1): the if/else at line(s) 87 with the arms swapped and the test negated (ifswap.py): score 83 -> 81. */
typedef struct { s16 a; s16 b; } P23628;
typedef struct { s32 x; u8 pad[0x54]; } E23628;
void func_001ba708(s32);
void func_001bb480(void);
void func_00114820(void);
void func_00f44500(void);
void func_00f46cb8(s32, s32);
s32 func_00f23018(s32, s32);
void func_00f20360(void);
P23628 *func_00f2b598(s32, s32);
void func_00f20160(s32, s32);
extern s32 D_00F850A8;
extern s32 D_00F850BC;
extern s32 D_00F850C0;
extern s32 D_00F850C4;
extern s32 D_00F850D8;
extern f32 D_00F85200[4][4];
extern s32 D_00F87300;
extern s32 D_00F87304;
extern s32 D_00F87350;
extern E23628 D_00F87E98[];
extern s32 D_00F8C23C;
extern s32 D_00F9B2EC;
extern s32 D_00FB652C;
extern s32 D_00FBAA90;
extern s32 D_00FBAA94;
extern s32 D_00FBB320;
extern s32 D_00FBB324;

void func_00f23628(void) {
    f32 v[4];
    s32 r;
    s32 a, b;
    P23628 *p;

    D_00F850A8 = 1;
    func_001ba708(1);
    D_00FBAA90 = 0;
    D_00FBAA94 = 1;
    v[0] = 0;
    D_00F9B2EC = 0;
    v[3] = 1.0f;
    D_00FBB320 = 0;
    v[2] = 1600.0f;
    v[1] = 0;
    D_00FBB324 = 0;
    sceVu0UnitMatrix(D_00F85200);
    sceVu0TransMatrix(D_00F85200, D_00F85200, v);
    func_001bb480();
    func_00114820();
    func_00f44500();
    func_00f46cb8(67, 0);
    D_00F850BC = 0;
    D_00F850C0 = 0;
    D_00F850C4 = 0;
    if (D_00F8C23C != 0) {
        r = func_00f23018(D_00F850D8, 1);
    } else {
        r = func_00f23018(D_00F850D8, 0);
    }
    D_00F8C23C = 0;
    D_00F850D8 = D_00FB652C;
    if (r < 0) {
        func_00f20360();
    }
    if (D_00F850BC != 0) {
        p = func_00f2b598(99, D_00F850D8);
        if (p == NULL) {
            p = func_00f2b598(99, 3);
        }
        D_00F87304 = p->a;
        D_00F87300 = D_00F87E98[p->a].x;
        p = func_00f2b598(99, r);
        D_00F850BC = 1;
    } else {
        p = func_00f2b598(D_00F850D8, r);
        a = D_00F850D8;
        if (a == 27) a = 13;
        b = r;
        if (b == 27) b = 13;
        if (a == b) {
            D_00F850C0 = 1;
            D_00F850C4 = 1;
        }
    }
    if (p == NULL) {
        a = 3;
        b = -1;
    } else {
        a = p->a;
        b = p->b;
    }
    D_00F87350 = 0;
    func_00f20160(a > 0 ? a : 3, b);
}
