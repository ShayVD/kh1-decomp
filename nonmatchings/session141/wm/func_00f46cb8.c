/* Round 36 (wgb): wm.x func_00f46cb8 near miss: 216 -> 210 words, score 109 -> 83 (aligned diff 77 -> 57). Statement order from tools/ovl/hill3.py (score-ranked, strict dependency rules). Tried: hill3 sweep of every gb RANKING row and wm RANKING rows 1-100 (85-90 s, seed 1; strict rules; the order kept passes hill3.py --check against the previous draft), and port.py from the twin (not better). Earlier header below. */
/* score 109 (1100 vs 1088). Event/scene runner: init D_00FB6408 and call its fn, wait while D_0037A378.b1, free D_01080828[2], dispatch D_00F9B304, restore D_002C5958.b3. Unused s32 buf[24] reproduces the 192-byte frame (143 -> 109). Left: the D_00FB6408.fn args are loaded into t-regs and moved (orig loads straight into a2/a3/t0, 12 bytes), and a few lui placements. Tried field reads as args, assignment-in-args, locals, unprototyped fn. Round 26 wwm2. */
typedef struct { u32 b0 : 1; u32 b1 : 1; } WmFlags;
typedef struct { u32 b0 : 3; u32 b3 : 1; } Cfg;
typedef struct { s32 x0; s32 x4; s32 x8; s32 xc; s32 x10; s32 x14; u8 pad18[16]; s32 x28[2]; u8 pad30[8]; void (*fn)(s32, s32, s32, s32, s32); } Gfx;
extern s32 D_002BCDEC;
extern Cfg D_002C5958;
extern s32 D_002E27A4;
extern WmFlags D_0037A378;
extern s32 D_00F85088;
extern s32 D_00F85094;
extern void *D_00F864C0;
extern s32 D_00F87308;
extern s32 D_00F9B2EC;
extern s32 D_00F9B2F0;
extern s32 D_00F9B2F4;
extern s32 D_00F9B2F8;
extern s32 D_00F9B2FC;
extern s32 D_00F9B300;
extern s32 D_00F9B304;
extern s32 D_00F9B320;
extern s32 D_00F9B324;
extern s32 D_00F9B328;
extern Gfx D_00FB6408;
extern s8 D_01080558;
extern s32 D_010807F8;
extern s32 D_01080828[2];
extern s32 D_01080830[2];
extern s32 D_01080838[2];
extern s32 D_01080840[2];
extern s32 D_01080848[2];
extern s32 D_01080904;
extern s32 D_010809B0;
void func_001ba708(s32);
void func_001bfac8(void);
void func_001c0078(s32);
void func_001c0310(s32, void (*)(void), s32);
void func_001c2ec8(s32, s32);
void func_00f200e8(s32);
void func_00f201c0(void);
void func_00f202b0(s32, s32);
void func_00f2abe8(s32, s32);
void func_00f309d0(s32);
void func_00f3a4c8(void);
s32 func_00f43e30(s32);
void func_00f43eb8(void);
void func_00f43ef8(void);
void func_00f44ea0(void);
void func_00f46a58(void);
void func_00f46c78(void);

void func_00f46cb8(s32 id, s32 how)
{
    s32 h;
    s32 i;
    s32 save;
    s32 once;
    s32 buf[24];

    save = D_002C5958.b3;
    D_010807F8 = 0;
    D_010809B0 = 0;
    once = 0;
    h = func_00f43e30(id);
    if (h == 0) {
        return;
    }
    func_00f44ea0();
    D_002BCDEC = 1;
    while (D_00F9B2EC != 0) {
        func_001bfac8();
    }
    D_00F9B2F4 = 0;
    D_00F9B304 = 0;
    D_00F9B2EC = 1;
    for (i = 0; i < 2; i++) {
        D_01080830[i] = 0;
        D_01080828[i] = 0;
    }
    D_00F9B328 = 0;
    D_00FB6408.x0 = 0x2E00;
    D_00FB6408.xc = D_00F9B320;
    D_00FB6408.x4 = 0x2F00;
    D_00FB6408.x10 = D_00F9B324;
    D_00FB6408.x14 = 0x3600;
    D_00FB6408.x8 = D_01080904;
    D_00FB6408.fn(0x2F00, 0x3600, D_01080904, D_00F9B320, D_00F9B324);
    if (D_00F864C0 != NULL) {
        func_00f2abe8(26, D_01080558);
    }
    for (i = 0; i < 2; i++) {
        D_01080840[i] = 0;
        D_01080848[i] = 0;
        D_01080838[i] = 0;
        D_00FB6408.x28[i] = 0;
    }
    func_00f43eb8();
    D_002E27A4 = 0;
    func_001c2ec8(h, 0);
    if (save == 0) {
        D_002C5958.b3 = 0;
    }
    while (D_0037A378.b1 == 1) {
        func_00f46a58();
        func_00f43ef8();
        if (D_010809B0 == 1) {
            func_001ba708(1);
            func_00f309d0(1);
        }
        D_010809B0++;
        if (D_010809B0 >= 3) {
            D_00F9B2F0 = 1;
        }
        if (D_010807F8 != 0 && once == 0) {
            once = 1;
            func_00f3a4c8();
        }
        func_001bfac8();
    }
    for (i = 0; i < 2; i++) {
        if (D_01080828[i] != 0) {
            func_001c0078(D_01080828[i]);
        }
    }
    D_00F87308 = D_00F9B2F4;
    switch (D_00F9B304) {
    case 1:
        func_00f202b0(D_00F9B2F8, D_00F9B2FC);
        break;
    case 2:
        if (how == 0 && D_00F9B300 == 93) {
            D_00F85088 = 1;
        }
        func_00f200e8(D_00F9B300);
        break;
    case 3:
        func_00f201c0();
        break;
    }
    if (how == 2) {
        D_002C5958.b3 = 0;
    } else {
        D_002C5958.b3 = save;
    }
    D_00F9B2EC = 0;
    D_00F85094 = 0;
    func_001ba708(0);
    if (how != 1 || id != 64) {
        if (D_00F9B2F0 != 0) {
            func_001c0310(-1, func_00f46c78, 4);
        } else {
            func_00f309d0(0);
        }
    }
    D_00F9B2F0 = 0;
}
