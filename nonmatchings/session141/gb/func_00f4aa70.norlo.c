/* Round 48 wwm2: score 660 -> 619 under the norlo build mode (tools/ovl/modescan.py). Earlier header below. */
/* Round 48 wwm2: the hill3o order from 0657d46c (gb func_00f4aa70 near miss, score 660 -> 584, port of wm func_00f71b68 (wwm2 rou) moved a control line (break/case/label/return/goto) or broke a dependency, so its score 551 was not valid. Restored the last valid statement order: score 660. Earlier header below. */
/* score 660: gb port of wm f71b68 via portmap2; same remaining block-placement diffs. Round 25 draft wwm2. */
typedef struct { s16 v[2]; } S2;
typedef struct { u8 pad[16]; s32 x10; } Win;
typedef struct { u8 pad[8]; u32 x8; u32 x10; } Pad;
typedef struct { u8 pad[4]; s8 x4; } Ic4;
typedef struct { u8 pad[9]; s8 x9; } Ic9;
extern Pad D_002C5AD0;
extern s32 D_00F702D8;
extern s32 D_00F702DC;
extern s32 D_00F702F0;
extern s32 D_00F703E4;
extern s32 D_00F703E8;
extern s32 D_00F703F0;
extern s32 D_00F704A4;
extern s32 D_00F704A8;
extern s32 D_00F704AC;
extern s32 D_00F70518;
extern s32 D_00F7051C;
extern s32 D_00F70520;
extern s32 D_00F70524;
extern s32 D_00F70528;
extern s32 D_00F7052C;
extern s32 D_00F70530;
extern s32 D_00F70538;
extern s32 D_00F7053C;
extern s32 D_00F70540;
extern s32 D_00F70544;
extern s32 D_00F70640;
extern s32 D_00F70644;
extern s32 D_00F70658, D_00F7065C, D_00F70660, D_00F70664;
extern s32 D_00F70668, D_00F7066C, D_00F70670, D_00F70674;
extern S2 D_00F74078;
extern s32 D_00F829F8;
extern s32 D_00F82A28;
extern s32 D_00F82B48;
extern Ic9 *D_00F82B50[];
extern s32 D_00F82BC8[];
extern s32 D_00F82BF0;
extern Ic9 *D_00F82C08[];
extern Ic4 *D_00F82C30[];
extern s32 D_00F82C58;
extern s32 D_00F82C5C;
extern s32 D_00F82C60;
extern s32 D_00F82C64;
void func_0011d768(s32);
void func_001be4d8(void); CONTEXT_ONLY void func_001be4d8() {}
void func_0020bda8(s32);
void func_0020be10(s32);
void func_0024e468(s32);
s32 func_00f20018(void);
void func_00f43cf0(s32);
void func_00f444d8(s32, s32, s32);
Win *func_00f445a8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00f49ff8(s32, s32);
void func_00f4a048(s32, s32);
void func_00f4a1c0(s32, s32);
s32 func_00f4aa60(void); CONTEXT_ONLY s32 func_00f4aa60() { return 0; }
void func_00f4a650(Win *, Win *, Win *, Win *, Win *, Win *);

void func_00f4aa70(void)
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

    mode = D_00F702F0;
    ic = D_00F74078;
    D_00F82C64 = -1;
    save = D_00F702D8;
    flag = 0;
    w0 = func_00f445a8(10, 3, 0, 2, 0, 0, 0, 0, 0, 0, 0, 120, 2, D_00F70658, D_00F7065C, D_00F70660, D_00F70664, 256, mode);
    w1 = func_00f445a8(10, 3, 0, 2, 0, 0, 0, 0, 300, 0, 0, 120, 2, D_00F70658, D_00F7065C, D_00F70660, D_00F70664, 256, mode);
    w2 = func_00f445a8(10, 3, 0, 2, 0, 0, 0, 0, 0, 0, 0, 120, 2, D_00F70668, D_00F7066C, D_00F70670, D_00F70674, 256, mode);
    w3 = func_00f445a8(10, 3, 0, 2, 0, 0, 0, 0, 300, 0, 0, 120, 2, D_00F70668, D_00F7066C, D_00F70670, D_00F70674, 256, mode);
    wa = func_00f445a8(10, 1, 0, 2, 0, 15, 83, 0, 100, D_00F70640 - 32, 0, 0, 0, D_00F70658, D_00F7065C, D_00F70660, D_00F70664, 256, mode);
    wb = func_00f445a8(10, 1, 0, 2, 0, 15, 84, 0, 100, D_00F70644 - 32, 0, 0, 0, D_00F70668, D_00F7066C, D_00F70670, D_00F70674, 256, mode);
    help = func_00f445a8(10, 2, 0, 2, 0, D_00F70518, 53, 0, D_00F7051C, D_00F70520, 0, 0, 0, D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, func_00f20018() == 0 ? mode : 1);
    func_00f445a8(10, 0, 2, 1, 0, 15, 7, 4, D_00F704A4, D_00F704A8, 0, D_00F704AC, 0, 0, 0, 0, 0, 256, mode);
    wt = func_00f445a8(10, 0, 2, 1, 0, 15, ic.v[0], 7, D_00F703E4, D_00F703E8, 0, D_00F703F0, 0, 0, 0, 0, 0, 256, mode);
    func_00f445a8(10, 3, 0, 2, 0, 0, 0, 0, 0, D_00F703E8 + 12, 0, D_00F703E4, 2, D_00F70538, D_00F7053C, D_00F70540, D_00F70544, 256, mode);
    func_00f4a650(wa, wb, w0, w1, w2, w3);
    if (D_00F82BF0 == 0 && D_00F82B48 == 0) {
        func_0020be10(16);
        while (!(D_002C5AD0.x8 & 0x6000)) func_0024e468(1);
        flag = 1;
        func_0011d768(3);
        goto end;
    }
    row = 0;
    col = 0;
    half = D_00F82B48 / 2;
    if (!func_00f4aa60()) {
        func_00f4a1c0(0, 0);
        goto mode2;
    }
    func_00f4a048(0, 0);
    func_0024e468(D_00F702F0);
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
            if (D_00F82C58 < 0) {
                D_00F82C58 = row * 2 + col;
                help->x10 = 54;
                goto chk;
            }
            if (D_00F82C58 == row * 2 + col) {
                func_0011d768(4);
                trig = 0;
                held = 0;
                goto cancel;
            }
            D_00F82C60 = row * 2 + col;
            func_0024e468(1);
            help->x10 = 55;
            do {
                if (!(D_002C5AD0.x8 & 0x6000)) {
                    n = 0;
                    do {
                        D_00F82C5C = 1;
                        n++;
                        func_00f4a048(col, row);
                        func_0024e468(1);
                    } while (n < 20 && !(D_002C5AD0.x8 & 0x6000));
                }
                held = D_002C5AD0.x8;
                t = held & 0x6000;
                if (t) break;
                n = 0;
                do {
                    D_00F82C5C = 0;
                    n++;
                    func_00f4a048(col, row);
                    func_0024e468(1);
                    if (n >= 20) break;
                    held = D_002C5AD0.x8;
                    t = held & 0x6000;
                } while (!t);
            } while (!t);
            if (held & 0x4000) {
                D_00F82C60 = -1;
                trig = 0;
                func_0011d768(3);
                D_00F82C5C = 0;
                held = 0;
                help->x10 = 54;
                goto cancel;
            }
            func_0011d768(2);
            col = 0;
            prow = 0;
            pcol = 0;
            D_00F82B50[D_00F82C58]->x9 = D_00F82BC8[D_00F82C60] + 1;
            row = 0;
            D_00F82B50[D_00F82C60]->x9 = D_00F82BC8[D_00F82C58] + 1;
            func_00f444d8(11, 0, D_00F702F0);
            func_0024e468(D_00F702F0);
            func_00f43cf0(11);
            func_00f4a650(wa, wb, w0, w1, w2, w3);
            func_00f4a048(0, 0);
            help->x10 = 53;
        chk:
            held = 0;
            if (!func_00f4aa60()) done = 1;
            trig = 0;
        }
    cancel:
        if (held & 0x4000) {
            if (D_00F82C58 < 0) {
                func_0011d768(3);
                done = -1;
                goto out;
            }
            D_00F82C58 = -1;
            trig = 0;
            help->x10 = 53;
            func_0011d768(3);
        }
        if (trig & 0x40) {
            n = row + 1;
            trig = 0;
            if (func_00f49ff8(col, n)) {
                row = n;
            } else if (row == 0) {
                if (D_00F82C58 < 0) done = 1;
            } else if (func_00f49ff8(col - 1, n)) {
                col = col - 1;
                row = n;
            } else if (D_00F82C58 < 0) {
                done = 1;
            }
        }
        if (done == 0) {
            if (trig & 0x10) {
                n = row - 1;
                trig = 0;
                if (func_00f49ff8(col, n)) row = n;
            }
            if (trig & 0x80) {
                n = col - 1;
                trig = 0;
                if (func_00f49ff8(n, row)) col = n;
            }
            if (trig & 0x20) {
                n = col + 1;
                if (func_00f49ff8(n, row)) col = n;
            }
            func_00f4a048(col, row);
        } else if (D_00F82BF0 == 0) {
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
    func_00f4a048(-1, -1);
    half = row;
    func_0024e468(1);
mode2:
    pcol = col;
    row = 0;
    prow = 0;
    wt->x10 = ic.v[1];
    help->x10 = 57;
    D_00F82C64 = -1;
    for (;;) {
        trig = D_002C5AD0.x10;
        held = D_002C5AD0.x8;
        trig |= trig >> 24;
        if (held & 0x4000) {
            D_00F82C64 = -1;
            func_0011d768(3);
            if (!func_00f4aa60()) goto end;
            goto back1;
        }
        if (held & 0x2000) {
            func_0011d768(2);
            help->x10 = 55;
            func_0024e468(1);
            do {
                D_00F82C30[row * 2]->x4 = 1;
                D_00F82C30[row * 2 + 1]->x4 = 1;
                D_00F82C64 = row;
                if (!(D_002C5AD0.x8 & 0x6000)) {
                    n = 0;
                    do {
                        func_0024e468(1);
                        n++;
                    } while (n < 20 && !(D_002C5AD0.x8 & 0x6000));
                }
                D_00F82C30[row * 2]->x4 = 0;
                D_00F82C30[row * 2 + 1]->x4 = 0;
                D_00F82C64 = -2;
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
            D_00F82C64 = -1;
            if (held & 0x2000) {
                func_0011d768(2);
                D_00F82C08[row * 2]->x9 = 0;
                D_00F82C08[row * 2 + 1]->x9 = 0;
                func_00f444d8(11, 0, D_00F702F0);
                func_0024e468(D_00F702F0);
                func_00f43cf0(11);
                func_00f4a650(wa, wb, w0, w1, w2, w3);
                if (D_00F82BF0 == 0) {
                    col = 0;
                    goto back;
                }
                func_00f4a048(-1, -1);
                row = 0;
                col = 0;
            }
            help->x10 = 57;
            trig = 0;
        }
        v = D_00F82BF0 / 2;
        if (trig & 0x40) {
            row++;
            trig = 0;
            if (row >= v) row = v - 1;
        }
        if (trig & 0x10) {
            row--;
            if (row < 0) {
                row = 0;
                if (func_00f4aa60() && half >= 0) {
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
        func_00f4a1c0(col, row);
        func_0024e468(1);
    }
back1:
    func_00f4a1c0(-1, -1);
back:
    D_00F82C64 = -1;
    row = 0;
    while (func_00f49ff8(col, row)) row++;
    if (row) row--;
    if (!func_00f49ff8(col, row)) col = (col + 1) & 1;
    func_00f4a048(col, row);
    func_0024e468(1);
    goto mode1;
end:
    D_00F82A28 = 0;
    func_00f444d8(11, 0, D_00F702F0);
    func_00f444d8(10, 0, D_00F702F0);
    func_0024e468(D_00F702F0);
    func_00f43cf0(10);
    func_00f43cf0(11);
    if (D_00F829F8 > 0) D_00F829F8 = -1;
    func_001be4d8();
    D_00F702D8 = save;
    D_00F702DC = save;
    if (flag) func_0020bda8(16);
}
