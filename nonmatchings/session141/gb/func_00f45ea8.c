/* Round 41 wwm2: score 216 -> 180, port.py of the wm twin func_00f6cfa0 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* gb.x func_00f45ea8 near miss: 307 words differ, score 216 (ours 2176 bytes, original 2160). Port of wm func_00f6cfa0 (nonmatchings/session141/wm) via tools/ovl/port.py, at the same score; see that file for the findings and what is left. */
/* score 216 (2176 vs 2160). Menu with 6 entries (codes {1,2,5,6,8,9}, labels {1,3,9,11,213,13}). The navigation loop is a for loop whose condition holds the confirm check (pad 0x2000, then for entry 0 an e[cur+1].a8 test that plays sound 4 and stays in the loop). The switch needs explicit case 1/2/7/8 labels so the jump table spans 1..9. Item 9 opens a sub-loop over D_00F71148/D_00F71150 and then does goto top. Left: the init-store schedule, register numbering (y/i, s8 = hi(D_00F702F0) in the original), the item loop re-reading *pc instead of reusing it, and where the func_0011d768(2) block is placed in the pad-wait loop. */
typedef struct { s32 x0, x4; u32 x8; u32 xC; u32 x10; } Pad;
typedef struct Win {
    s8 b0, b1, b2, b3, b4, b5, b6, b7;
    s16 h8, hA, hC;
    s16 padE;
    s32 x10;
    f32 x, y, tx, ty, vx, vy;
    f32 a, at, as;
} Win;
typedef struct { u8 a0; u8 pad1[7]; u8 a8; u8 pad9; u8 aA; u8 padB[85]; } Ent;
typedef struct { s16 v[6]; } Tbl;
extern Pad D_002C5AD0;
extern s32 D_00F702D0;
extern s32 D_00F702F0;
extern s32 D_00F703E4;
extern s32 D_00F703E8;
extern s32 D_00F703EC;
extern u16 D_00F703F0;
extern s32 D_00F70518;
extern s32 D_00F7051C;
extern s32 D_00F70520;
extern s32 D_00F70524;
extern s32 D_00F70528;
extern s32 D_00F7052C;
extern s32 D_00F70530;
extern s32 D_00F70734;
extern s8 D_00F7073A;
extern Tbl D_00F71160;
extern s8 D_00F71148[];
extern s16 D_00F71150[];
extern Tbl D_00F82998;
extern s32 D_00F829C4;
extern s32 D_00F829D4;
extern s32 D_00F829D8;
extern s32 D_00F829DC;
extern s32 D_00F829E0;
extern s32 D_00F829E8;
extern s32 D_00F829F8;
extern s32 D_00F82A28;
extern s32 D_00F82AC0;
void func_00106880(s32);
void func_0011d768(s32);
Ent *func_001bc4e0(void);
s32 func_001be278(void);
void func_0020bc48(s32, s32, s32);
void func_0020bda8(s32);
void func_0020be10(s32);
void func_0024e468(s32);
s32 func_00f20018(void);
void func_00f21e48(void);
s32 func_00f22ee8(void);
void func_00f22f08(void);
void func_00f26430(s32);
Win *func_00f43388(void);
void func_00f43cf0(s32);
void func_00f43d68(Win *);
void func_00f444b8(Win *, f32, f32);
void func_00f444d8(s32, s32, s32);
Win *func_00f445a8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f4d880(Win *, s32);
void func_00f4d8c0(s32, s32, s32);
s32 func_00f51360(s32);

s32 func_00f45ea8(void)
{
    Win *w[6];
    s16 lst[6];
    s8 codes[6];
    Win *w2;
    s32 t;
    Win **pw;
    Win *w3;
    s16 *pl;
    s8 *pc;
    Ent *p;
    s32 i, k, sel, old, r;
    s32 y;

    t = D_00F702F0;
    if (func_00f20018()) {
        D_00F71160.v[0] = 227;
    } else {
        D_00F71160.v[0] = 2;
    }
    pl = lst;
    sel = 0;
    lst[0] = 1;
    if (D_00F70734 >= 0) sel = D_00F70734;
    lst[5] = 13;
    lst[1] = 3;
    pw = w;
    codes[0] = 1;
    codes[1] = 2;
    codes[2] = 5;
    lst[2] = 9;
    D_00F82998.v[0] = D_00F71160.v[0];
    lst[3] = 11;
    D_00F82998.v[1] = D_00F71160.v[1];
    y = D_00F703E8;
    lst[4] = 213;
    codes[3] = 6;
    D_00F82998.v[2] = D_00F71160.v[2];
    codes[5] = 9;
    D_00F82998.v[3] = D_00F71160.v[3];
    D_00F82998.v[4] = D_00F71160.v[4];
    D_00F82998.v[5] = D_00F71160.v[5];
    codes[4] = 8;
    D_00F702D0 = codes[sel];
    for (i = 0; i < 6; i++) {
        *pw = func_00f43388();
        (*pw)->b0 = 1;
        (*pw)->b1 = 0;
        (*pw)->b2 = 2;
        (*pw)->b3 = 0;
        (*pw)->hC = 1;
        (*pw)->x10 = *pl;
        (*pw)->y = (*pw)->ty = y;
        (*pw)->a = (*pw)->at = 0;
        (*pw)->tx = (*pw)->x = D_00F703E4;
        (*pw)->h8 = D_00F703F0;
        if (i == sel) {
            (*pw)->b4 = 1;
            func_00f4d880(*pw, 8);
        } else {
            (*pw)->b4 = 0;
        }
        y += D_00F703EC;
        pl++;
        pw++;
    }
    if (D_00F829DC == 0) {
        D_00F829E0 = 0;
        D_00F829DC = 1;
        func_0024e468(2);
        D_00F829E0 = 16;
    }
    w2 = func_00f445a8(1, 2, 0, 1, 0, D_00F70518, D_00F82998.v[sel], 0, D_00F7051C, D_00F70520, 0, 0, 0, D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, func_00f20018() == 0 ? t : 1);
    if (func_00f22ee8() && !func_00f20018()) {
        D_00F829E8 = 1;
        func_00f22f08();
        func_00f4d8c0(368, 212, 0);
        func_0020bc48(D_00F829E0, D_00F829D4, D_00F829D8);
        pw = w;
        for (k = 5; k >= 0; k--) {
            func_00f444b8(*pw++, 256.0f, D_00F702F0);
            func_0024e468(2);
        }
        if (func_00f51360(1) == 0) {
            func_0011d768(2);
            func_00106880(30);
            func_0024e468(60);
            D_00F829C4 = 0;
            D_00F7073A = 3;
            D_00F70734 = -1;
            func_00f26430(0);
            for (;;) func_0024e468(1);
        }
    } else {
        pw = w;
        for (k = 5; k >= 0; k--) {
            func_00f444b8(*pw++, 256.0f, D_00F702F0);
            func_0024e468(2);
        }
    }
    func_00f21e48();
top:
    for (; !(D_002C5AD0.x8 & 0x2000) || (sel == 0 ? (p = func_001bc4e0(), p[func_001be278() + 1].a8 ? (func_0011d768(4), 1) : (func_0011d768(2), 0)) : (func_0011d768(2), 0));) {
        old = sel;
        if (((D_002C5AD0.x8 | D_002C5AD0.x8 >> 24) & 0x10) && sel == 0) {
            sel = 5;
        } else if ((D_002C5AD0.x10 | D_002C5AD0.x10 >> 24) & 0x10) {
            sel--;
            if (sel < 0) sel = 0;
        }
        if (((D_002C5AD0.x8 | D_002C5AD0.x8 >> 24) & 0x40) && sel == 5) {
            sel = 0;
        } else if ((D_002C5AD0.x10 | D_002C5AD0.x10 >> 24) & 0x40) {
            sel++;
            if (sel >= 6) sel = 5;
        }
        w2->x10 = D_00F82998.v[sel];
        pw = w;
        for (i = 0; i < 6; i++) {
            if (i == sel) {
                (*pw)->b4 = 1;
                func_00f4d880(*pw, 8);
            } else {
                (*pw)->b4 = 0;
            }
            pw++;
        }
        D_00F702D0 = codes[sel];
        if (sel != old) func_0011d768(1);
        func_0024e468(1);
    }
    r = codes[sel];
    D_00F70734 = sel;
    switch (r) {
    case 1:
    case 2:
    case 7:
    case 8:
        break;
    case 3:
    case 4:
    case 5:
    case 6:
        D_00F82AC0 = 1;
        break;
    case 9:
        p = func_001bc4e0();
        p = &p[func_001be278() + 1];
        if (p->aA & 0xF) {
            w3 = 0;
            func_0011d768(4);
            func_0020be10(16);
            if (D_00F71148[0] != 0) {
                pc = D_00F71148;
                pl = D_00F71150;
                do {
                    if (*pc & p->aA) {
                        if (w3 == 0) {
                            w3 = func_00f445a8(6, 8, 2, 4, 0, 15, *pl, 4, 160, 216, 0, 0, 0, 0, 0, 0, 0, 256, D_00F702F0);
                            func_0024e468(D_00F702F0);
                        }
                        w3->x10 = *pl;
                        func_0024e468(1);
                        for (;;) {
                            u32 b = D_002C5AD0.x8;
                            if (b & 0x2000) {
                                func_0011d768(2);
                                break;
                            }
                            if (b & 0x4000) {
                                func_0011d768(3);
                                break;
                            }
                            func_0024e468(1);
                        }
                    }
                    pl++;
                    pc++;
                } while (*pc);
            }
            func_0020bda8(16);
            func_00f444d8(6, 0, D_00F702F0);
            func_0024e468(D_00F702F0);
            if (w3) func_00f43d68(w3);
            goto top;
        }
        break;
    }
    if (r == 9) {
        func_00106880(30);
        func_0024e468(58);
        D_00F82AC0 = 1;
        func_0024e468(2);
    } else {
        func_00f444d8(1, 0, D_00F702F0);
        pw = &w[5];
        D_00F82A28 = 0;
        for (k = 5; k >= 0; k--) {
            func_00f444b8(*pw--, 0.0f, D_00F702F0);
            func_0024e468(2);
        }
        func_0024e468(11);
    }
    func_00f43cf0(1);
    if (D_00F829F8 > 0) D_00F829F8 = -1;
    return r;
}
