/* score 660 (3904 vs 3848 bytes): full structure (empty-case wait, mode1 swap-select, mode2 delete, back/re-find, end cleanup); remaining diffs are block placement (wait loop, end block). Round 25 draft wwm2. */
typedef struct { s16 v[2]; } S2;
typedef struct { u8 pad[16]; s32 x10; } Win;
typedef struct { u8 pad[8]; u32 x8; u32 x10; } Pad;
typedef struct { u8 pad[4]; s8 x4; } Ic4;
typedef struct { u8 pad[9]; s8 x9; } Ic9;
extern Pad D_002C5AD0;
extern s32 D_00FB4A58;
extern s32 D_00FB4A5C;
extern s32 D_00FB4A70;
extern s32 D_00FB4B64;
extern s32 D_00FB4B68;
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
extern s32 D_00FB4CB8;
extern s32 D_00FB4CBC;
extern s32 D_00FB4CC0;
extern s32 D_00FB4CC4;
extern s32 D_00FB4DC0;
extern s32 D_00FB4DC4;
extern s32 D_00FB4DD8, D_00FB4DDC, D_00FB4DE0, D_00FB4DE4;
extern s32 D_00FB4DE8, D_00FB4DEC, D_00FB4DF0, D_00FB4DF4;
extern S2 D_00FBA128;
extern s32 D_0108F1B8;
extern s32 D_0108F1E8;
extern s32 D_0108F308;
extern Ic9 *D_0108F310[];
extern s32 D_0108F388[];
extern s32 D_0108F3B0;
extern Ic9 *D_0108F3C8[];
extern Ic4 *D_0108F3F0[];
extern s32 D_0108F418;
extern s32 D_0108F41C;
extern s32 D_0108F420;
extern s32 D_0108F424;
void func_0011d768(s32);
void func_001be4d8(void);
void func_0020bda8(s32);
void func_0020be10(s32);
void func_0024e468(s32);
s32 func_00f47110(void);
void func_00f6ade8(s32);
void func_00f6b5d0(s32, s32, s32);
Win *func_00f6b6a0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00f710f0(s32, s32);
void func_00f71140(s32, s32);
void func_00f712b8(s32, s32);
s32 func_00f71b58(void);
void func_00f71748(Win *, Win *, Win *, Win *, Win *, Win *);

void func_00f71b68(void)
{
    S2 ic;
    Win *wt;
    Win *help;
    Win *wa;
    Win *wb;
    Win *w0;
    Win *w1;
    Win *w2;
    Win *w3;
    s32 col;
    s32 pcol;
    s32 prow;
    s32 half;
    s32 flag;
    s32 save;
    s32 mode, row, done, n, t, v;
    u32 trig, held;

    mode = D_00FB4A70;
    ic = D_00FBA128;
    D_0108F424 = -1;
    save = D_00FB4A58;
    flag = 0;
    w0 = func_00f6b6a0(10, 3, 0, 2, 0, 0, 0, 0, 0, 0, 0, 120, 2, D_00FB4DD8, D_00FB4DDC, D_00FB4DE0, D_00FB4DE4, 256, mode);
    w1 = func_00f6b6a0(10, 3, 0, 2, 0, 0, 0, 0, 300, 0, 0, 120, 2, D_00FB4DD8, D_00FB4DDC, D_00FB4DE0, D_00FB4DE4, 256, mode);
    w2 = func_00f6b6a0(10, 3, 0, 2, 0, 0, 0, 0, 0, 0, 0, 120, 2, D_00FB4DE8, D_00FB4DEC, D_00FB4DF0, D_00FB4DF4, 256, mode);
    w3 = func_00f6b6a0(10, 3, 0, 2, 0, 0, 0, 0, 300, 0, 0, 120, 2, D_00FB4DE8, D_00FB4DEC, D_00FB4DF0, D_00FB4DF4, 256, mode);
    wa = func_00f6b6a0(10, 1, 0, 2, 0, 15, 83, 0, 100, D_00FB4DC0 - 32, 0, 0, 0, D_00FB4DD8, D_00FB4DDC, D_00FB4DE0, D_00FB4DE4, 256, mode);
    wb = func_00f6b6a0(10, 1, 0, 2, 0, 15, 84, 0, 100, D_00FB4DC4 - 32, 0, 0, 0, D_00FB4DE8, D_00FB4DEC, D_00FB4DF0, D_00FB4DF4, 256, mode);
    help = func_00f6b6a0(10, 2, 0, 2, 0, D_00FB4C98, 53, 0, D_00FB4C9C, D_00FB4CA0, 0, 0, 0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, func_00f47110() == 0 ? mode : 1);
    func_00f6b6a0(10, 0, 2, 1, 0, 15, 7, 4, D_00FB4C24, D_00FB4C28, 0, D_00FB4C2C, 0, 0, 0, 0, 0, 256, mode);
    wt = func_00f6b6a0(10, 0, 2, 1, 0, 15, ic.v[0], 7, D_00FB4B64, D_00FB4B68, 0, D_00FB4B70, 0, 0, 0, 0, 0, 256, mode);
    func_00f6b6a0(10, 3, 0, 2, 0, 0, 0, 0, 0, D_00FB4B68 + 12, 0, D_00FB4B64, 2, D_00FB4CB8, D_00FB4CBC, D_00FB4CC0, D_00FB4CC4, 256, mode);
    func_00f71748(wa, wb, w0, w1, w2, w3);
    if (D_0108F3B0 == 0 && D_0108F308 == 0) {
        func_0020be10(16);
        while (!(D_002C5AD0.x8 & 0x6000)) func_0024e468(1);
        flag = 1;
        func_0011d768(3);
        goto end;
    }
    row = 0;
    col = 0;
    half = D_0108F308 / 2;
    if (!func_00f71b58()) {
        func_00f712b8(0, 0);
        goto mode2;
    }
    func_00f71140(0, 0);
    func_0024e468(D_00FB4A70);
mode1:
    wt->x10 = ic.v[0];
    done = 0;
    help->x10 = 53;
    for (;;) {
        pcol = col;
        trig = D_002C5AD0.x10;
        trig |= trig >> 24;
        held = D_002C5AD0.x8;
        prow = row;
        if (held & 0x2000) {
            func_0011d768(2);
            if (D_0108F418 < 0) {
                D_0108F418 = row * 2 + col;
                help->x10 = 54;
                goto chk;
            }
            if (D_0108F418 == row * 2 + col) {
                func_0011d768(4);
                trig = 0;
                held = 0;
                goto cancel;
            }
            D_0108F420 = row * 2 + col;
            func_0024e468(1);
            help->x10 = 55;
            do {
                if (!(D_002C5AD0.x8 & 0x6000)) {
                    n = 0;
                    do {
                        D_0108F41C = 1;
                        n++;
                        func_00f71140(col, row);
                        func_0024e468(1);
                    } while (n < 20 && !(D_002C5AD0.x8 & 0x6000));
                }
                held = D_002C5AD0.x8;
                t = held & 0x6000;
                if (t) break;
                n = 0;
                do {
                    D_0108F41C = 0;
                    n++;
                    func_00f71140(col, row);
                    func_0024e468(1);
                    if (n >= 20) break;
                    held = D_002C5AD0.x8;
                    t = held & 0x6000;
                } while (!t);
            } while (!t);
            if (held & 0x4000) {
                D_0108F420 = -1;
                trig = 0;
                func_0011d768(3);
                D_0108F41C = 0;
                held = 0;
                help->x10 = 54;
                goto cancel;
            }
            func_0011d768(2);
            col = 0;
            prow = 0;
            pcol = 0;
            D_0108F310[D_0108F418]->x9 = D_0108F388[D_0108F420] + 1;
            row = 0;
            D_0108F310[D_0108F420]->x9 = D_0108F388[D_0108F418] + 1;
            func_00f6b5d0(11, 0, D_00FB4A70);
            func_0024e468(D_00FB4A70);
            func_00f6ade8(11);
            func_00f71748(wa, wb, w0, w1, w2, w3);
            func_00f71140(0, 0);
            help->x10 = 53;
        chk:
            held = 0;
            if (!func_00f71b58()) done = 1;
            trig = 0;
        }
    cancel:
        if (held & 0x4000) {
            if (D_0108F418 < 0) {
                func_0011d768(3);
                done = -1;
                goto out;
            }
            D_0108F418 = -1;
            trig = 0;
            help->x10 = 53;
            func_0011d768(3);
        }
        if (trig & 0x40) {
            n = row + 1;
            trig = 0;
            if (func_00f710f0(col, n)) {
                row = n;
            } else if (row == 0) {
                if (D_0108F418 < 0) done = 1;
            } else if (func_00f710f0(col - 1, n)) {
                col = col - 1;
                row = n;
            } else if (D_0108F418 < 0) {
                done = 1;
            }
        }
        if (done == 0) {
            if (trig & 0x10) {
                n = row - 1;
                trig = 0;
                if (func_00f710f0(col, n)) row = n;
            }
            if (trig & 0x80) {
                n = col - 1;
                trig = 0;
                if (func_00f710f0(n, row)) col = n;
            }
            if (trig & 0x20) {
                n = col + 1;
                if (func_00f710f0(n, row)) col = n;
            }
            func_00f71140(col, row);
        } else if (D_0108F3B0 == 0) {
            col = pcol;
            done = 0;
            row = prow;
        } else {
            pcol = -1;
            prow = -1;
        }
        if (col != pcol || row != prow) func_0011d768(1);
        if (done) break;
        func_0024e468(1);
    }
out:
    if (done < 0) goto end;
    func_00f71140(-1, -1);
    half = row;
    func_0024e468(1);
mode2:
    pcol = col;
    row = 0;
    prow = 0;
    wt->x10 = ic.v[1];
    help->x10 = 57;
    D_0108F424 = -1;
    for (;;) {
        trig = D_002C5AD0.x10;
        held = D_002C5AD0.x8;
        trig |= trig >> 24;
        if (held & 0x4000) {
            D_0108F424 = -1;
            func_0011d768(3);
            if (!func_00f71b58()) goto end;
            goto back1;
        }
        if (held & 0x2000) {
            func_0011d768(2);
            help->x10 = 55;
            func_0024e468(1);
            do {
                D_0108F3F0[row * 2]->x4 = 1;
                D_0108F3F0[row * 2 + 1]->x4 = 1;
                D_0108F424 = row;
                if (!(D_002C5AD0.x8 & 0x6000)) {
                    n = 0;
                    do {
                        func_0024e468(1);
                        n++;
                    } while (n < 20 && !(D_002C5AD0.x8 & 0x6000));
                }
                D_0108F3F0[row * 2]->x4 = 0;
                D_0108F3F0[row * 2 + 1]->x4 = 0;
                D_0108F424 = -2;
                held = D_002C5AD0.x8;
                t = held & 0x6000;
                if (t) break;
                n = 0;
                do {
                    func_0024e468(1);
                    n++;
                    if (n >= 20) break;
                    held = D_002C5AD0.x8;
                    t = held & 0x6000;
                } while (!t);
            } while (!t);
            func_0011d768(3);
            D_0108F424 = -1;
            if (held & 0x2000) {
                func_0011d768(2);
                D_0108F3C8[row * 2]->x9 = 0;
                D_0108F3C8[row * 2 + 1]->x9 = 0;
                func_00f6b5d0(11, 0, D_00FB4A70);
                func_0024e468(D_00FB4A70);
                func_00f6ade8(11);
                func_00f71748(wa, wb, w0, w1, w2, w3);
                if (D_0108F3B0 == 0) {
                    col = 0;
                    goto back;
                }
                func_00f71140(-1, -1);
                row = 0;
                col = 0;
            }
            help->x10 = 57;
            trig = 0;
        }
        v = D_0108F3B0 / 2;
        if (trig & 0x40) {
            row++;
            trig = 0;
            if (row >= v) row = v - 1;
        }
        if (trig & 0x10) {
            row--;
            if (row < 0) {
                row = 0;
                if (func_00f71b58() && half >= 0) {
                    func_0011d768(1);
                    goto back1;
                }
            }
            trig = 0;
        }
        if (trig & 0xA0) col = (col + 1) & 1;
        if (col != pcol || row != prow) {
            prow = row;
            pcol = col;
            func_0011d768(1);
        }
        func_00f712b8(col, row);
        func_0024e468(1);
    }
back1:
    func_00f712b8(-1, -1);
back:
    D_0108F424 = -1;
    row = 0;
    while (func_00f710f0(col, row)) row++;
    if (row) row--;
    if (!func_00f710f0(col, row)) col = (col + 1) & 1;
    func_00f71140(col, row);
    func_0024e468(1);
    goto mode1;
end:
    D_0108F1E8 = 0;
    func_00f6b5d0(11, 0, D_00FB4A70);
    func_00f6b5d0(10, 0, D_00FB4A70);
    func_0024e468(D_00FB4A70);
    func_00f6ade8(10);
    func_00f6ade8(11);
    if (D_0108F1B8 > 0) D_0108F1B8 = -1;
    func_001be4d8();
    D_00FB4A58 = save;
    D_00FB4A5C = save;
    if (flag) func_0020bda8(16);
}
