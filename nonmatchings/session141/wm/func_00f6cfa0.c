/* score 216 (2176 vs 2160). Menu with 6 entries (codes {1,2,5,6,8,9}, labels {1,3,9,11,213,13}). The navigation loop is a for loop whose condition holds the confirm check (pad 0x2000, then for entry 0 an e[cur+1].a8 test that plays sound 4 and stays in the loop). The switch needs explicit case 1/2/7/8 labels so the jump table spans 1..9. Item 9 opens a sub-loop over D_00FB58C8/D_00FB58D0 and then does goto top. Left: the init-store schedule, register numbering (y/i, s8 = hi(D_00FB4A70) in the original), the item loop re-reading *pc instead of reusing it, and where the func_0011d768(2) block is placed in the pad-wait loop. */
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
extern s32 D_00FB4A50;
extern s32 D_00FB4A70;
extern s32 D_00FB4B64;
extern s32 D_00FB4B68;
extern s32 D_00FB4B6C;
extern u16 D_00FB4B70;
extern s32 D_00FB4C98;
extern s32 D_00FB4C9C;
extern s32 D_00FB4CA0;
extern s32 D_00FB4CA4;
extern s32 D_00FB4CA8;
extern s32 D_00FB4CAC;
extern s32 D_00FB4CB0;
extern s32 D_00FB4EB4;
extern s8 D_00FB4EBA;
extern Tbl D_00FB58E0;
extern s8 D_00FB58C8[];
extern s16 D_00FB58D0[];
extern Tbl D_0108F158;
extern s32 D_0108F184;
extern s32 D_0108F194;
extern s32 D_0108F198;
extern s32 D_0108F19C;
extern s32 D_0108F1A0;
extern s32 D_0108F1A8;
extern s32 D_0108F1B8;
extern s32 D_0108F1E8;
extern s32 D_0108F280;
void func_00106880(s32);
void func_0011d768(s32);
Ent *func_001bc4e0(void);
s32 func_001be278(void);
void func_0020bc48(s32, s32, s32);
void func_0020bda8(s32);
void func_0020be10(s32);
void func_0024e468(s32);
s32 func_00f47110(void);
void func_00f48f40(void);
s32 func_00f49fe0(void);
void func_00f4a000(void);
void func_00f4d528(s32);
Win *func_00f6a480(void);
void func_00f6ade8(s32);
void func_00f6ae60(Win *);
void func_00f6b5b0(Win *, f32, f32);
void func_00f6b5d0(s32, s32, s32);
Win *func_00f6b6a0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f74978(Win *, s32);
void func_00f749b8(s32, s32, s32);
s32 func_00f78458(s32);

s32 func_00f6cfa0(void)
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

    t = D_00FB4A70;
    if (func_00f47110()) {
        D_00FB58E0.v[0] = 227;
    } else {
        D_00FB58E0.v[0] = 2;
    }
    pl = lst;
    lst[0] = 1;
    sel = 0;
    if (D_00FB4EB4 >= 0) sel = D_00FB4EB4;
    codes[0] = 1;
    lst[1] = 3;
    codes[1] = 2;
    codes[2] = 5;
    lst[3] = 11;
    codes[3] = 6;
    lst[4] = 213;
    codes[4] = 8;
    lst[5] = 13;
    codes[5] = 9;
    lst[2] = 9;
    D_0108F158.v[0] = D_00FB58E0.v[0];
    D_0108F158.v[1] = D_00FB58E0.v[1];
    D_0108F158.v[2] = D_00FB58E0.v[2];
    D_0108F158.v[3] = D_00FB58E0.v[3];
    D_0108F158.v[4] = D_00FB58E0.v[4];
    D_0108F158.v[5] = D_00FB58E0.v[5];
    D_00FB4A50 = codes[sel];
    y = D_00FB4B68;
    pw = w;
    for (i = 0; i < 6; i++) {
        *pw = func_00f6a480();
        (*pw)->b0 = 1;
        (*pw)->b1 = 0;
        (*pw)->b2 = 2;
        (*pw)->b3 = 0;
        (*pw)->hC = 1;
        (*pw)->x10 = *pl;
        (*pw)->y = (*pw)->ty = y;
        (*pw)->a = (*pw)->at = 0;
        (*pw)->tx = (*pw)->x = D_00FB4B64;
        (*pw)->h8 = D_00FB4B70;
        if (i == sel) {
            (*pw)->b4 = 1;
            func_00f74978(*pw, 8);
        } else {
            (*pw)->b4 = 0;
        }
        pl++;
        pw++;
        y += D_00FB4B6C;
    }
    if (D_0108F19C == 0) {
        D_0108F19C = 1;
        D_0108F1A0 = 0;
        func_0024e468(2);
        D_0108F1A0 = 16;
    }
    w2 = func_00f6b6a0(1, 2, 0, 1, 0, D_00FB4C98, D_0108F158.v[sel], 0, D_00FB4C9C, D_00FB4CA0, 0, 0, 0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, func_00f47110() == 0 ? t : 1);
    if (func_00f49fe0() && !func_00f47110()) {
        D_0108F1A8 = 1;
        func_00f4a000();
        func_00f749b8(368, 212, 0);
        func_0020bc48(D_0108F1A0, D_0108F194, D_0108F198);
        pw = w;
        for (k = 5; k >= 0; k--) {
            func_00f6b5b0(*pw++, 256.0f, D_00FB4A70);
            func_0024e468(2);
        }
        if (func_00f78458(1) == 0) {
            func_0011d768(2);
            func_00106880(30);
            func_0024e468(60);
            D_00FB4EBA = 3;
            D_00FB4EB4 = -1;
            D_0108F184 = 0;
            func_00f4d528(0);
            for (;;) func_0024e468(1);
        }
    } else {
        pw = w;
        for (k = 5; k >= 0; k--) {
            func_00f6b5b0(*pw++, 256.0f, D_00FB4A70);
            func_0024e468(2);
        }
    }
    func_00f48f40();
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
        w2->x10 = D_0108F158.v[sel];
        pw = w;
        for (i = 0; i < 6; i++) {
            if (i == sel) {
                (*pw)->b4 = 1;
                func_00f74978(*pw, 8);
            } else {
                (*pw)->b4 = 0;
            }
            pw++;
        }
        D_00FB4A50 = codes[sel];
        if (sel != old) func_0011d768(1);
        func_0024e468(1);
    }
    D_00FB4EB4 = sel;
    r = codes[sel];
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
        D_0108F280 = 1;
        break;
    case 9:
        p = func_001bc4e0();
        p = &p[func_001be278() + 1];
        if (p->aA & 0xF) {
            w3 = 0;
            func_0011d768(4);
            func_0020be10(16);
            if (D_00FB58C8[0] != 0) {
                pl = D_00FB58D0;
                pc = D_00FB58C8;
                do {
                    if (*pc & p->aA) {
                        if (w3 == 0) {
                            w3 = func_00f6b6a0(6, 8, 2, 4, 0, 15, *pl, 4, 160, 216, 0, 0, 0, 0, 0, 0, 0, 256, D_00FB4A70);
                            func_0024e468(D_00FB4A70);
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
                    pc++;
                    pl++;
                } while (*pc);
            }
            func_0020bda8(16);
            func_00f6b5d0(6, 0, D_00FB4A70);
            func_0024e468(D_00FB4A70);
            if (w3) func_00f6ae60(w3);
            goto top;
        }
        break;
    }
    if (r == 9) {
        func_00106880(30);
        func_0024e468(58);
        D_0108F280 = 1;
        func_0024e468(2);
    } else {
        func_00f6b5d0(1, 0, D_00FB4A70);
        D_0108F1E8 = 0;
        pw = &w[5];
        for (k = 5; k >= 0; k--) {
            func_00f6b5b0(*pw--, 0.0f, D_00FB4A70);
            func_0024e468(2);
        }
        func_0024e468(11);
    }
    func_00f6ade8(1);
    if (D_0108F1B8 > 0) D_0108F1B8 = -1;
    return r;
}
