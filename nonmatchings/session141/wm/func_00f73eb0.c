/* Round 35 (wgb): wm.x func_00f73eb0 near miss: 105 -> 99 words, score 152 -> 150. port.py of gb func_00f4cdb8's round 35 draft. Earlier header below. */
/* score 152 (1424 vs 1424, was 358). func_001bc520 takes no arguments and func_001f31a8 takes 2; m2c invents the rest. The pad loop is a goto loop with its test at the bottom. Icons are reached through `pp = ic`. The selection is `sel++; sel &= 1;` with a byte offset `idx = sel * 4` (with `(sel+1)&1` gcc uses xori). Left: the scheduling and order of the global stores in the prologue and the epilogue (120 orders of the end block tried, best kept), and the temp register numbering in the icon loop. */
typedef struct { s16 v[2]; } S2;
typedef struct { u8 pad[4]; u8 on; } Ic;
typedef struct { u8 pad[16]; s32 x10; } Win;
typedef struct { u8 pad[8]; u32 x8; } Pad;
typedef struct { u8 pad[12]; u16 xc; u16 xe; u8 pad2[14]; s16 x1e; } Lay;
extern Pad D_002C5AD0;
extern f32 D_00FB4A60;
extern s32 D_00FB4A70;
extern f32 D_00FB4AB0;
extern u16 D_00FB4B0C;
extern u16 D_00FB4B30;
extern s32 D_00FB4B38;
extern s32 D_00FB4B3C;
extern s32 D_00FB4B6C;
extern s32 D_00FB4B70;
extern s32 D_00FB4C24;
extern s32 D_00FB4C28;
extern s32 D_00FB4C2C;
extern s32 D_00FB4C98;
extern s32 D_00FB4C9C;
extern s32 D_00FB4CA0;
extern s32 D_00FB4CA4;
extern s32 D_00FB4CA8;
extern s32 D_00FB4CAC;
extern s32 D_00FB4CB0;
extern s32 D_00FB4D3C;
extern s32 D_00FB4D40;
extern s32 D_00FB4D50;
extern s32 D_00FB5A64;
extern Lay D_00FB5A70;
extern S2 D_00FBA1E8;
extern S2 D_00FBA1F0;
extern s32 D_0108F188;
extern s32 D_0108F18C;
extern s32 D_0108F1AC;
extern s32 D_0108F1B8;
extern s32 D_0108F1CC;
extern s32 D_0108F1D0;
extern s32 D_0108F1D4;
extern f32 D_0108F1E8;
extern s32 D_0108F528;
extern s32 D_0108F52C;
extern s32 D_0108F530;
void func_0011d768(s32);
s16 func_001bc520(void);
void func_001be470(s32 *);
s32 func_001f31a8(Lay *, s32);
void func_001f3dc0(s32);
void func_0024e468(s32);
s32 func_00f47110(void);
void func_00f6ade8(s32);
void func_00f6b5b0(Ic *, f32, f32);
void func_00f6b5d0(s32, s32, s32);
void *func_00f6b6a0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f72a70(s32, Win *);
void func_00f72f40(s32, Win *);
void func_00f74978(Ic *, s32);

void func_00f73eb0(void)
{
    Ic *ic[2];
    s32 tbl[2];
    S2 a;
    S2 b;
    s16 *pa;
    s32 i, sel, idx, mode, r, ptr;
    Win *w;
    u32 pad;
    s16 t;
    Ic **pp;

    a = D_00FBA1E8;
    b = D_00FBA1F0;
    D_0108F1AC = 0;
    D_0108F528 = 0;
    D_0108F1CC = D_00FB4D3C;
    D_0108F1D0 = D_00FB4D40;
    sel = 0;
    D_00FB4A60 = D_00FB4AB0;
    mode = D_00FB4A70;
    D_0108F1D4 = D_00FB4D50;
    pa = a.v;
    D_00FB5A64 = 0;
    D_0108F530 = 0;
    D_0108F52C = 0;
    D_0108F1E8 = 128.0f;
    t = func_001bc520();
    D_00FB5A70.xc = D_00FB4B0C;
    D_00FB5A70.xe = D_00FB4B30;
    D_0108F188 = 0;
    D_00FB5A70.x1e = t;
    r = func_001f31a8(&D_00FB5A70, 1);
    func_001f3dc0(D_0108F18C);
    w = func_00f6b6a0(13, 2, 0, 2, 0, D_00FB4C98, b.v[0], 0, D_00FB4C9C, D_00FB4CA0, 0, 0, 0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, func_00f47110() == 0 ? mode : 1);
    func_00f6b6a0(13, 0, 2, 1, 0, 15, 5, 4, D_00FB4C24, D_00FB4C28, 0, D_00FB4C2C, 0, 0, 0, 0, 0, 256, mode);
    pp = ic;
    ptr = D_00FB4B3C;
    for (i = 0; i < 2; i++) {
        pp[i] = func_00f6b6a0(13, 0, 2, 1, 0, 15, *pa++, 1, D_00FB4B38, ptr, 0, D_00FB4B70, 0, 0, 0, 0, 0, 0, mode);
        ptr += D_00FB4B6C;
    }
    pp[0]->on = 1;
    pp[1]->on = 0;
    idx = 0;
    func_00f74978(pp[0], 8);
    for (i = 0; i < 2; i++) {
        func_00f6b5b0(pp[i], 256.0f, D_00FB4A70);
        func_0024e468(2);
    }
    tbl[0] = 0;
    tbl[1] = 1;
    goto test;
loop:
    {
        if (pad & 0x2000) {
            func_0011d768(2);
            for (i = 0; i < 2; i++) {
                func_00f6b5b0(pp[i], 0.0f, D_00FB4A70);
            }
            if (sel == 0) D_0108F52C = 1;
            else D_0108F52C = 2;
            func_001f3dc0(r);
            func_0024e468(D_00FB4A70);
            if (sel == 0) func_00f72f40(r, w);
            else func_00f72a70(r, w);
            for (i = 0; i < 2; i++) {
                func_00f6b5b0(pp[i], 256.0f, D_00FB4A70);
                func_0024e468(2);
            }
            func_0024e468(16);
            D_0108F52C = 0;
            func_001f3dc0(D_0108F18C);
            pad = 0;
        }
        if (pad & 0x50) {
            sel++; sel &= 1;
            func_0011d768(1);
            idx = sel * 4;
        }
        (*(Ic **)((u8 *)pp + idx))->on = 1;
        (*(Ic **)((u8 *)pp + (((sel + 1) & 1) << 2)))->on = 0;
        w->x10 = b.v[sel];
        func_00f74978((*(Ic **)((u8 *)pp + idx)), 8);
        func_0024e468(1);
    }
test:
    pad = D_002C5AD0.x8;
    pad |= pad >> 24;
    if (!(pad & 0x4000)) goto loop;
    func_0011d768(3);
    D_00FB4A60 = D_00FB4AB0;
    D_0108F528 = 1;
    D_0108F1CC = D_00FB4D3C;
    D_0108F1D0 = D_00FB4D40;
    D_0108F1D4 = D_00FB4D50;
    D_0108F1E8 = 128.0f;
    func_00f6b5d0(13, 0, D_00FB4A70);
    func_0024e468(D_00FB4A70);
    func_00f6ade8(13);
    if (D_0108F1B8 > 0) D_0108F1B8 = -1;
    func_001be470(&D_0108F1B8);
}
