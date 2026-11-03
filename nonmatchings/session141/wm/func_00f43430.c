/* score 2 (2 words; was 8). Round 34 wwm2: the -dg dump showed global-alloc giving the D_00F9B1CC address (5 refs, live 128) s5 before D_00F9B1C8 (live 136). Swapping the two stores in the init block and in all three branches flips them (4 words); then enumerating the four branch stores (24 orders for branches 1 and 3 together, 24 for branch 2) gave 2 with C4, C8, CC, AC in branches 1 and 3. Left: `move s0,v0` and `move s1,sp` before the buf loop are swapped; for-init, while, index, count-down, p placement and all 24 declaration orders do not change it. Earlier header: score 8 (6 words; was 10). Round 30 wwm2: a CONTEXT_ONLY definition of func_00f41320 above the function (the call becomes nothrow) fixes the beqz/beqzl after func_00f40c98. Left: s5/s6 for the D_00F9B1C8/D_00F9B1CC addresses and the buf-loop move; hill2 over the four store blocks found nothing more. Earlier header: 7 words (656 bytes). Structure right (cross-jumped f46cb8(64,1)+4 stores tails, buf loop via *p++, main wait loop). Left: s5/s6 swapped for D_00F9B1C8/D_00F9B1CC addresses, buf-loop move order, and beqz vs beqzl after func_00f40c98. hill2 over the 4 store blocks plus loop/condition forms (2x5 min), and a 10-min permuter run (best was not semantics-preserving). Round 10: hill2 over loop forms (while/for/do, five shapes of the B2C0/f41c28 test, five f40c98 forms), f41320 prototypes and p = buf placements: still 7. Round 17 (wwm1): a CONTEXT_ONLY func_00f41320 above it takes this to 6 words (two addiu bases and two stores swapped); ctx2.py singles and pairs. */
typedef struct { u8 pad[32]; s32 x20; } S43430;
extern S43430 D_00F87310;
extern s32 D_002C5958, D_00F9B1C8, D_00F9B1CC, D_00F9B1C4, D_00F850AC, D_00F850E0, D_00F850D0;
extern s32 D_00F9B2D0, D_00F9B2BC, D_00F9B1C0, D_00F850D8, D_00F850BC, D_00F850C0, D_00F8C23C, D_00F9B2C0;
void func_00114820(void);
s32 func_001c00e8(s32, void *, kh1_u128);
void func_00f432f0(void);
void func_00f42f20(void);
void func_00f309d0(s32);
void func_00f344e0(s32);
s32 func_00f3ff98(s32, s32, s32);
void func_00f3a510(void);
void func_00f32ac8(void);
void func_00f3cac8(void);
void func_001be820(void *, s32);
s32 func_00f2b2f8(s32);
void func_00f307b0(void);
void func_00f422c0(void);
void func_001c0310(s32, void *, s32);
void func_00f40f58(void);
void func_00f46cb8(s32, s32);
s32 func_00f35c08(s32 *);
void func_00f42818(void);
void func_00f35e10(void);
s32 func_00f40c98(void);
#ifdef KH1_PS2
void func_00f41320(void);
CONTEXT_ONLY void func_00f41320() {}
#else /* the definition returns f32: an x86 caller of a void one leaves it on the x87 stack */
f32 func_00f41320(void);
#endif
s32 func_00f41c28(void);
void func_001bfac8(void);

void func_00f43430(void) {
    s32 buf[8];
    s32 n;
    s32 i;
    s32 *p;

    func_00114820();
    func_001c00e8(10, func_00f432f0, KH1_Q(0));
    func_001c00e8(15, func_00f42f20, KH1_Q(0));
    func_00f309d0(0);
    func_00f344e0(0);
    D_00F9B1C8 = 0;
    D_00F9B1CC = 0;
    D_00F9B1C4 = 0;
    D_00F850AC = 0;
    D_00F9B2D0 = func_00f3ff98(D_00F850E0, 0, D_00F850D0);
    func_00f3a510();
    func_00f32ac8();
    func_00f3cac8();
    D_00F9B2BC = 1;
    D_00F9B1C0 = 0;
    func_001be820(&D_00F87310, 64);
    D_00F87310.x20 = func_00f2b2f8(D_00F850D8);
    func_00f307b0();
    D_002C5958 |= 8;
    if (D_00F850BC) {
        func_00f422c0();
        func_00f344e0(0);
        func_00f46cb8(64, 1);
        D_00F9B1C4 = 1;
        D_00F9B1C8 = 1;
        D_00F9B1CC = 1;
        D_00F850AC = 1;
    } else if (D_00F850C0 == 0) {
        func_001c0310(-1, func_00f40f58, 60);
        func_00f46cb8(64, 1);
        D_00F9B1C4 = 1;
        D_00F9B1C8 = 1;
        D_00F9B1CC = 1;
        D_00F850AC = 1;
        func_00f309d0(0);
        D_002C5958 |= 8;
        n = func_00f35c08(buf);
        p = buf;
        for (i = 0; i < n; i++) func_00f46cb8(*p++, 2);
        func_00f42818();
        D_002C5958 &= ~8;
    } else {
        func_00f46cb8(64, 1);
        D_00F9B1C4 = 1;
        D_00F9B1C8 = 1;
        D_00F9B1CC = 1;
        D_00F850AC = 1;
    }
    while (1) {
        if (D_00F8C23C == 0) {
            func_00f35e10();
            if (func_00f40c98()) {
                func_00f41320();
            }
            if (D_00F9B2C0 && !func_00f41c28()) return;
        }
        func_001bfac8();
    }
}
