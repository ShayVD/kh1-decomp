/* Round 41 wwm2: score 223 -> 27, port.py of the gb twin func_00f2ec80 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* 120 words left (524 vs 616): twin of f56538; m[4] array fixes the prologue, but target spills induction vars (frame 128) and keeps i*-432 as a mult. Tried 30 expression spellings. */

typedef struct { u8 pad[0x4C]; u16 kind; u8 pad4e[0x84 - 0x4E]; s16 id; } GbState;
extern GbState *D_00F9B540;
extern u8 D_00F9B548[];
void func_001bfac8(void);
s32 func_00f4aa20(s32);
s32 func_00f4aaf8(s32);
void func_00f55670(void *);
void func_00f55758(void *, s32, s32, s32, s32);
void func_00f55880(void *, s32);
void func_00f55900(void *);

void func_00f55d78(s32 n) {
    s32 prev, cur, next, next2;
    s32 t;
    s32 y0, y1, y2, y3, x0, x1, x2, x3, h0, h1, h2, h3;
    s32 i;
    cur = D_00F9B540->id;
    next = func_00f4aa20(cur);
    prev = func_00f4aaf8(cur);
    next2 = func_00f4aa20(next);
    for (i = 0; i < n; i++) {
        func_00f55670(D_00F9B548);
        h0 = (5 * (n - i) << 4) / n;
        t = 0x30 * i / n;
        h1 = 0x80 - t;
        h2 = t + 0x50;
        h3 = (5 * i << 4) / n;
        t = 0x110 * (n - i) / n;
        x0 = t - 0x2C0;
        x3 = t + 0x1B0;
        x1 = -0x1B0 * i / n;
        t = (5 * (n - i) << 5) / n;
        y0 = t + 0xC0;
        y1 = t + 0x160;
        t = (5 * i << 5) / n;
        y2 = t + 0x160;
        y3 = t + 0xC0;
        x2 = 0x1B0 * (n - i) / n;
        func_00f55758(D_00F9B548, prev, x0, y0, h0);
        func_00f55758(D_00F9B548, cur, x1, y1, h1);
        func_00f55758(D_00F9B548, next, x2, y2, h2);
        func_00f55758(D_00F9B548, next2, x3, y3, h3);
        func_00f55880(D_00F9B548, D_00F9B540->kind - 1);
        func_00f55900(D_00F9B548);
        func_001bfac8();
    }
}
