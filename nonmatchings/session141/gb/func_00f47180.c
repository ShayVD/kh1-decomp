/* Round 41 (wgb): score 200 -> 186, statement order from hill3 (300 s, seed 41, default mode). Earlier header below. */
/* drafttwins.py: score 202 -> 200, port.py of the wm twin func_00f6e278 draft. Earlier header below. */
/* Round 41 wwm2: score 268 -> 202, port.py of the wm twin func_00f6e278 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
typedef struct { u8 x0; u8 x1; u8 pad2; u8 x3; u8 pad4; u8 x5; u8 pad6[2]; s16 x8; s16 xa; s16 xc; u8 padE[2]; s32 x10; f32 x14; f32 x18; f32 x1c; f32 x20; u8 pad24[8]; f32 x2c; f32 x30; u8 pad34[4]; u8 x38; u8 x39; u8 x3a; u8 x3b; } Ic;
typedef struct { u8 pad[16]; s32 x10; u8 pad2[44]; void *x40; } Win;
typedef struct { u8 pad[2]; u8 x2; u8 x3; u8 x4; u8 x5; u8 x6; u8 pad7[9]; } It;
typedef struct { u8 pad[12]; u16 xc; u16 xe; u8 pad2[14]; s16 x1e; } Lay;
typedef struct { s32 x0; s32 x4; s32 x8; } Swp;
extern void *D_003E8E08;
extern s32 D_00F702D8;
extern s32 D_00F702F0;
extern s32 D_00F70404;
extern s32 D_00F70408;
extern u16 D_00F7040C;
extern s32 D_00F70410;
extern s32 D_00F70414;
extern s32 D_00F70418;
extern s32 D_00F7042C;
extern s32 D_00F70430;
extern u8 D_00F7043C;
extern u8 D_00F70440;
extern u8 D_00F70444;
extern u8 D_00F70448;
extern s32 D_00F704A4;
extern s32 D_00F704A8;
extern s32 D_00F704AC;
extern u16 D_00F704C0;
extern u16 D_00F704C4;
extern s32 D_00F70510;
extern s32 D_00F70514;
extern s32 D_00F70518;
extern s32 D_00F7051C;
extern s32 D_00F70520;
extern s32 D_00F70524;
extern s32 D_00F70528;
extern s32 D_00F7052C;
extern s32 D_00F70530;
extern s32 D_00F70534;
extern s32 D_00F70548;
extern s32 D_00F7054C;
extern s32 D_00F70550;
extern s32 D_00F70554;
extern s32 D_00F7058C;
extern s32 D_00F70590;
extern s32 D_00F70594;
extern s32 D_00F70598;
extern s32 D_00F707EC;
extern Lay D_00F71170;
extern u8 D_00F72878[];
extern s32 D_00F829C8;
extern s32 D_00F829F8;
extern s32 D_00F829FC;
extern s32 D_00F82A00;
extern s32 D_00F82A14;
extern s32 D_00F82A28;
extern f32 D_00F82A2C;
extern f32 D_00F82A30;
extern s32 D_00F82A38;
extern s32 D_00F82A3C;
extern s32 D_00F82A40;
extern s32 D_00F82A44;
extern Swp D_00F82A88;
extern s32 D_00F82A94;
extern s32 D_00F82AC8;
extern s32 D_00F82ACC;
void *func_001ba268(s32);
It *func_001bc4d0(void);
s32 func_001bc500(void);
s32 func_001f0118(s32, s32);
s32 func_001f31a8(Lay *, s32);
void func_0024e468(s32);
s32 func_00f20018(void);
void func_00f422e8(s32, s32, s32, s32, s32, s32, s32, u8 *, s32, u64, s32, u64);
void func_00f43350(void);
Ic *func_00f43388(void);
void func_00f43cf0(s32);
void func_00f444b8(Ic *, f32, f32);
void func_00f444d8(s32, s32, s32);
Win *func_00f445a8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f46ee0(void);

void func_00f47180(void)
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
    mode = D_00F702F0;
    D_00F82A28 = 0;
    D_00F829FC = 4;
    D_00F82A14 = 400;
    D_00F82A00 = 0;
    i = 0;
    D_00F82A3C = 430;
    D_00F82A44 = 0;
    D_00F82A38 = 0;
    D_00F82A40 = 190;

    D_00F82AC8 = 0;
    D_00F82A94 = 0;
    save = D_00F702D8;
    func_00f445a8(3, 6, 0, 1, 0, 15, 0, 0, D_00F70410, D_00F70414, 0, D_00F70418, (D_00F7042C + 1) * D_00F70430, 10, 10, 10, 100, 256, mode);
    x = D_00F70408 + D_00F70430 + D_00F70430;
    for (; i < D_00F7042C / 2; i++) {
        ic = func_00f43388();
        ic->x0 = 3;
        ic->x1 = 3;
        ic->xc = 2;
        ic->x10 = 0;
        ic->x3 = 0;
        ic->x5 = 15;
        ic->x1c = D_00F70404 + 2;
        ic->x2c = 0.0f;
        ic->x14 = D_00F70404 + 2;
        ic->xa = D_00F70430 - 1;
        ic->x20 = x;
        ic->x8 = D_00F7040C - 4;
        ic->x38 = D_00F7043C;
        ic->x39 = D_00F70440;
        ic->x3a = D_00F70444;
        ic->x18 = x;
        ic->x30 = 0.0f;
        ic->x3b = D_00F70448;
        func_00f444b8(ic, 256.0f, mode);
        x += D_00F70430 * 2;
    }
    func_00f445a8(3, 0, 2, 1, 0, 15, 9, 4, D_00F704A4, D_00F704A8, 0, D_00F704AC, 0, 0, 0, 0, 0, 256, mode);
    func_001bc4d0();
    n = 0;
    for (i = 0; i < func_001bc500(); i++) n++;
    D_00F82A30 = 128.0f;
    D_00F71170.x1e = n;
    D_00F82A2C = 128.0f;
    D_00F82ACC = 0;
    D_00F71170.xc = D_00F704C0;
    D_00F829C8 = 0;
    D_00F71170.xe = D_00F704C4;
    func_001f31a8(&D_00F71170, 1);
    D_003E8E08 = D_00F72878;
    func_00f445a8(3, 2, 0, 1, 0, D_00F70518, 82, 0, D_00F7051C, D_00F70520, 0, 0, 0, D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, func_00f20018() == 0 ? mode : 1);
    func_00f445a8(3, 1, 0, 1, 0, 15, 59, 0, D_00F70548, D_00F7054C, 0, 0, 0, D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, mode);
    func_00f445a8(3, 1, 0, 1, 0, 15, 60, 0, D_00F70550, D_00F7054C, 0, 0, 0, D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, mode);
    func_00f445a8(3, 1, 0, 1, 0, 15, 61, 0, D_00F70554, D_00F7054C, 0, 0, 0, D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, mode);
    items = func_001bc4d0();
    func_00f43350();
    w[0] = func_00f445a8(3, 5, 0, 3, 4, D_00F70518, 0, 0, D_00F70548 + func_001f0118(59, D_00F70518) + D_00F70534, D_00F7054C - 1, 0, 0, 0, D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, mode);
    w[1] = func_00f445a8(3, 5, 0, 3, 4, D_00F70518, 0, 0, D_00F70550 + func_001f0118(60, D_00F70518) + D_00F70534, D_00F7054C - 1, 0, 0, 0, D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, mode);
    w[2] = func_00f445a8(3, 5, 0, 3, 4, D_00F70518, 0, 0, D_00F70554 + func_001f0118(61, D_00F70518) + D_00F70534, D_00F7054C - 1, 0, 0, 0, D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, mode);
    func_00f445a8(3, 7, 0, 3, 0, 15, 0, 0, 0, 0, 0, 0, 0, D_00F7058C, D_00F70590, D_00F70594, D_00F70598, 256, mode)->x40 = func_00f46ee0;
    for (;;) {
        e = (It *)(D_00F82AC8 * sizeof(It) + (u32)items);
        t = e->x6 >= 71;
        if (e->x5 == 0 && !t) {
            w[0]->x10 = 0;
            w[1]->x10 = 0;
            w[2]->x10 = 0;
        } else {
            w[0]->x10 = items[D_00F82AC8].x2;
            w[1]->x10 = items[D_00F82AC8].x3;
            w[2]->x10 = items[D_00F82AC8].x4;
        }
        D_003E8E08 = func_001ba268(items[D_00F82AC8].x6);
        if (D_00F829C8) break;
        a = 0;
        switch (D_00F82ACC) {
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
            t = D_00F82A88.x0;
            col[0] = 0x80;
            col[3] = 0x80;
            D_00F82A88.x0 = D_00F82A88.x8;
            func_00f422e8(D_00F707EC + a, D_00F707EC + b, D_00F70510 - (cw >> 1), D_00F70514 - (ch >> 1), cw, ch, fmt, col, 0, 68, 0, 0x5001D);
            D_00F82A88.x8 = D_00F82A88.x0;
            D_00F82A88.x0 = t;
        }
        func_0024e468(1);
    }
    func_00f444d8(3, 0, D_00F702F0);
    D_00F82A28 = 0;
    func_0024e468(D_00F702F0 + 1);
    D_00F82A94 = 1;
    D_00F702D8 = save;
    D_00F829FC = 0;
    D_00F82A44 = 1;
    func_00f43cf0(3);
    if (D_00F829F8 > 0) D_00F829F8 = -1;
}
