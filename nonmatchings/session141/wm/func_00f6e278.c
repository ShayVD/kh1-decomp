/* Round 36 (wwm2): wm.x func_00f6e278 near miss: score 268 -> 202 (565 -> 444 words, 2816 vs 2824); statement order from the score-ranked dependency-safe hill3 (r35/hill3.py, two passes, seeds 362/363 then 364). Earlier header below. */
/* score 268 (2808 vs 2824 bytes). Menu setup (like f73eb0): 6 info windows, an icon row from func_00f6a480, then 4 + 3 windows (the last gets x40 = func_00f6dfd8), then a loop until D_0108F188: copy item bytes x2..x4 into the 3 counters (zero when x5 == 0 and x6 < 71), refresh D_003E8E08, and draw the D_0108F28C icon (jump table 0x40..0x46 at 0x00FBA100, default first) with D_0108F248.x0/x8 swapped around func_00f693e0. The draft scored 401. Putting default first plus `t = e->x6 >= 71;` gave 410, then two hill2 passes over the declaration, prologue, icon-field and colour-store order gave 268. Left: the original reaches D_00FB4CC8/CD0/CD4 through a raw `lui 0xfb; move; addiu` (no symbol; treating them as an array made it worse, 498), the prologue register choice (i in s1), and the 16 bytes it lacks. */
typedef struct { u8 x0; u8 x1; u8 pad2; u8 x3; u8 pad4; u8 x5; u8 pad6[2]; s16 x8; s16 xa; s16 xc; u8 padE[2]; s32 x10; f32 x14; f32 x18; f32 x1c; f32 x20; u8 pad24[8]; f32 x2c; f32 x30; u8 pad34[4]; u8 x38; u8 x39; u8 x3a; u8 x3b; } Ic;
typedef struct { u8 pad[16]; s32 x10; u8 pad2[44]; void *x40; } Win;
typedef struct { u8 pad[2]; u8 x2; u8 x3; u8 x4; u8 x5; u8 x6; u8 pad7[9]; } It;
typedef struct { u8 pad[12]; u16 xc; u16 xe; u8 pad2[14]; s16 x1e; } Lay;
typedef struct { s32 x0; s32 x4; s32 x8; } Swp;
extern void *D_003E8E08;
extern s32 D_00FB4A58;
extern s32 D_00FB4A70;
extern s32 D_00FB4B84;
extern s32 D_00FB4B88;
extern u16 D_00FB4B8C;
extern s32 D_00FB4B90;
extern s32 D_00FB4B94;
extern s32 D_00FB4B98;
extern s32 D_00FB4BAC;
extern s32 D_00FB4BB0;
extern u8 D_00FB4BBC;
extern u8 D_00FB4BC0;
extern u8 D_00FB4BC4;
extern u8 D_00FB4BC8;
extern s32 D_00FB4C24;
extern s32 D_00FB4C28;
extern s32 D_00FB4C2C;
extern u16 D_00FB4C40;
extern u16 D_00FB4C44;
extern s32 D_00FB4C90;
extern s32 D_00FB4C94;
extern s32 D_00FB4C98;
extern s32 D_00FB4C9C;
extern s32 D_00FB4CA0;
extern s32 D_00FB4CA4;
extern s32 D_00FB4CA8;
extern s32 D_00FB4CAC;
extern s32 D_00FB4CB0;
extern s32 D_00FB4CB4;
extern s32 D_00FB4CC8;
extern s32 D_00FB4CCC;
extern s32 D_00FB4CD0;
extern s32 D_00FB4CD4;
extern s32 D_00FB4D0C;
extern s32 D_00FB4D10;
extern s32 D_00FB4D14;
extern s32 D_00FB4D18;
extern s32 D_00FB4F6C;
extern Lay D_00FB58F0;
extern u8 D_00FB8928[];
extern s32 D_0108F188;
extern s32 D_0108F1B8;
extern s32 D_0108F1BC;
extern s32 D_0108F1C0;
extern s32 D_0108F1D4;
extern s32 D_0108F1E8;
extern f32 D_0108F1EC;
extern f32 D_0108F1F0;
extern s32 D_0108F1F8;
extern s32 D_0108F1FC;
extern s32 D_0108F200;
extern s32 D_0108F204;
extern Swp D_0108F248;
extern s32 D_0108F254;
extern s32 D_0108F288;
extern s32 D_0108F28C;
void *func_001ba268(s32);
It *func_001bc4d0(void);
s32 func_001bc500(void);
s32 func_001f0118(s32, s32);
s32 func_001f31a8(Lay *, s32);
void func_0024e468(s32);
s32 func_00f47110(void);
void func_00f693e0(s32, s32, s32, s32, s32, s32, s32, u8 *, s32, u64, s32, u64);
void func_00f6a448(void);
Ic *func_00f6a480(void);
void func_00f6ade8(s32);
void func_00f6b5b0(Ic *, f32, f32);
void func_00f6b5d0(s32, s32, s32);
Win *func_00f6b6a0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f6dfd8(void);

void func_00f6e278(void)
{
    Win *w[3];
    s32 a, b;
    u32 cw, ch;
    It *e;
    s32 save;
    Ic *ic;
    It *items;
    u8 col[4];
    s32 mode, i, x, n, t;
    s32 fmt;
    D_0108F1E8 = 0;
    D_0108F1BC = 4;
    D_0108F204 = 0;
    D_0108F1D4 = 400;
    D_0108F1C0 = 0;
    i = 0;
    mode = D_00FB4A70;
    D_0108F200 = 190;
    D_0108F1F8 = 0;
    D_0108F1FC = 430;

    save = D_00FB4A58;
    D_0108F288 = 0;
    D_0108F254 = 0;
    func_00f6b6a0(3, 6, 0, 1, 0, 15, 0, 0, D_00FB4B90, D_00FB4B94, 0, D_00FB4B98, (D_00FB4BAC + 1) * D_00FB4BB0, 10, 10, 10, 100, 256, mode);
    x = D_00FB4B88 + D_00FB4BB0 + D_00FB4BB0;
    for (; i < D_00FB4BAC / 2; i++) {
        ic = func_00f6a480();
        ic->x0 = 3;
        ic->xc = 2;
        ic->x3 = 0;
        ic->x10 = 0;
        ic->x1 = 3;
        ic->x5 = 15;
        ic->x1c = D_00FB4B84 + 2;
        ic->x2c = 0.0f;
        ic->x14 = D_00FB4B84 + 2;
        ic->xa = D_00FB4BB0 - 1;
        ic->x20 = x;
        ic->x8 = D_00FB4B8C - 4;
        ic->x38 = D_00FB4BBC;
        ic->x3a = D_00FB4BC4;
        ic->x39 = D_00FB4BC0;
        ic->x18 = x;
        ic->x3b = D_00FB4BC8;
        ic->x30 = 0.0f;
        func_00f6b5b0(ic, 256.0f, mode);
        x += D_00FB4BB0 * 2;
    }
    func_00f6b6a0(3, 0, 2, 1, 0, 15, 9, 4, D_00FB4C24, D_00FB4C28, 0, D_00FB4C2C, 0, 0, 0, 0, 0, 256, mode);
    func_001bc4d0();
    n = 0;
    for (i = 0; i < func_001bc500(); i++) n++;
    D_0108F1F0 = 128.0f;
    D_0108F1EC = 128.0f;
    D_00FB58F0.x1e = n;
    D_0108F28C = 0;
    D_00FB58F0.xc = D_00FB4C40;
    D_0108F188 = 0;
    D_00FB58F0.xe = D_00FB4C44;
    func_001f31a8(&D_00FB58F0, 1);
    D_003E8E08 = D_00FB8928;
    func_00f6b6a0(3, 2, 0, 1, 0, D_00FB4C98, 82, 0, D_00FB4C9C, D_00FB4CA0, 0, 0, 0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, func_00f47110() == 0 ? mode : 1);
    func_00f6b6a0(3, 1, 0, 1, 0, 15, 59, 0, D_00FB4CC8, D_00FB4CCC, 0, 0, 0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, mode);
    func_00f6b6a0(3, 1, 0, 1, 0, 15, 60, 0, D_00FB4CD0, D_00FB4CCC, 0, 0, 0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, mode);
    func_00f6b6a0(3, 1, 0, 1, 0, 15, 61, 0, D_00FB4CD4, D_00FB4CCC, 0, 0, 0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, mode);
    items = func_001bc4d0();
    func_00f6a448();
    w[0] = func_00f6b6a0(3, 5, 0, 3, 4, D_00FB4C98, 0, 0, D_00FB4CC8 + func_001f0118(59, D_00FB4C98) + D_00FB4CB4, D_00FB4CCC - 1, 0, 0, 0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, mode);
    w[1] = func_00f6b6a0(3, 5, 0, 3, 4, D_00FB4C98, 0, 0, D_00FB4CD0 + func_001f0118(60, D_00FB4C98) + D_00FB4CB4, D_00FB4CCC - 1, 0, 0, 0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, mode);
    w[2] = func_00f6b6a0(3, 5, 0, 3, 4, D_00FB4C98, 0, 0, D_00FB4CD4 + func_001f0118(61, D_00FB4C98) + D_00FB4CB4, D_00FB4CCC - 1, 0, 0, 0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, mode);
    func_00f6b6a0(3, 7, 0, 3, 0, 15, 0, 0, 0, 0, 0, 0, 0, D_00FB4D0C, D_00FB4D10, D_00FB4D14, D_00FB4D18, 256, mode)->x40 = func_00f6dfd8;
    for (;;) {
        e = &items[D_0108F288];
        t = e->x6 >= 71;
        if (e->x5 == 0 && !t) {
            w[0]->x10 = 0;
            w[1]->x10 = 0;
            w[2]->x10 = 0;
        } else {
            w[0]->x10 = items[D_0108F288].x2;
            w[1]->x10 = items[D_0108F288].x3;
            w[2]->x10 = items[D_0108F288].x4;
        }
        D_003E8E08 = func_001ba268(items[D_0108F288].x6);
        if (D_0108F188) break;
        a = 0;
        switch (D_0108F28C) {
        default:
            b = 0;
            cw = 0;
            ch = 0;
            fmt = 0;
            break;
        case 0x40:
            ch = 64;
            cw = 64;
            a = 0x20000;
            b = 0x21000;
            fmt = 8;
            break;
        case 0x41:
            a = 0x1EC00;
            b = 0x1FC00;
            cw = 64;
            ch = 64;
            fmt = 8;
            break;
        case 0x42:
        case 0x43:
            a = 0x1D800;
            b = 0x1E800;
            cw = 64;
            ch = 64;
            fmt = 8;
            break;
        case 0x44:
        case 0x45:
        case 0x46:
            a = 0x1C400;
            b = 0x1D400;
            cw = 64;
            ch = 64;
            fmt = 8;
            break;
        }
        if (cw) {
            col[2] = 0x80;
            col[1] = 0x80;
            t = D_0108F248.x0;
            col[0] = 0x80;
            D_0108F248.x0 = D_0108F248.x8;
            col[3] = 0x80;
            func_00f693e0(D_00FB4F6C + a, D_00FB4F6C + b, D_00FB4C90 - (cw >> 1), D_00FB4C94 - (ch >> 1), cw, ch, fmt, col, 0, 68, 0, 0x5001D);
            D_0108F248.x8 = D_0108F248.x0;
            D_0108F248.x0 = t;
        }
        func_0024e468(1);
    }
    func_00f6b5d0(3, 0, D_00FB4A70);
    D_0108F1E8 = 0;
    func_0024e468(D_00FB4A70 + 1);
    D_0108F254 = 1;
    D_00FB4A58 = save;
    D_0108F1BC = 0;
    D_0108F204 = 1;
    func_00f6ade8(3);
    if (D_0108F1B8 > 0) D_0108F1B8 = -1;
}
