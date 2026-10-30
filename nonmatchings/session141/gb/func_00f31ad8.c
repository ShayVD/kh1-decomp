/* drafttwins.py: score 289 -> 287, port.py of the wm twin func_00f58bd0 draft. Earlier header below. */
/* Round 41 wwm2: score 367 -> 289, port.py of the wm twin func_00f58bd0 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
typedef struct { u8 pad[64]; u8 c[8]; } G58bd0;
typedef struct { s8 t[40]; } T58bd0;
extern G58bd0 *D_00F56DC0;
extern s32 D_00F806C8;
extern T58bd0 D_00F71780;
extern u8 D_00379F28[];
extern u8 D_0037A028[];
s32 func_00f31030(s32);
void func_0011d140(s32, s32);
void func_00f319a8(void);
void func_001c01b0(s32, void (*)(void), s32, s32);
void func_00f32728(s32, s32);
void func_00f313d8(s32, s32, s32, s32);
void func_001bfac8(void);
void func_00f2e0b0(void);

void func_00f31ad8(s32 dir) {
    T58bd0 tbl;
    s32 spd;
    s32 to;
    s32 h;
    s32 i;
    s32 from;
    s32 c0;
    s32 c1;

    tbl = D_00F71780;
    from = D_00F806C8;
    if (dir == 0) {
        D_00F806C8 = from - 1;
        spd = 40;
    } else {
        D_00F806C8 = from + 1;
        spd = 60;
    }
    to = D_00F806C8 & 7;
    D_00F806C8 = to;
    func_0011d140(0xE2D5, 0);
    for (i = 0; i < 40; i++) {
        if (i / 4 < 8 && (i & 3) == 0) {
            c0 = i / 4;
            if (dir) c0 = 8 - c0;
            func_001c01b0(-1, func_00f319a8, c0 & 7, func_00f31030(from + c0));
        }
        c0 = func_00f31030(from) * 4;
        h = i / 2;
        c1 = func_00f31030(to) * 4;
        D_00F56DC0->c[0] = D_00379F28[c0] + (D_00379F28[c1] - D_00379F28[c0]) * i / 40;
        D_00F56DC0->c[1] = D_00379F28[c0 + 1] + (D_00379F28[c1 + 1] - D_00379F28[c0 + 1]) * i / 40;
        D_00F56DC0->c[2] = D_00379F28[c0 + 2] + (D_00379F28[c1 + 2] - D_00379F28[c0 + 2]) * i / 40;
        D_00F56DC0->c[6] = D_0037A028[c0 + 2] + (D_0037A028[c1 + 2] - D_0037A028[c0 + 2]) * i / 40;
        D_00F56DC0->c[5] = D_0037A028[c0 + 1] + (D_0037A028[c1 + 1] - D_0037A028[c0 + 1]) * i / 40;
        D_00F56DC0->c[4] = D_0037A028[c0] + (D_0037A028[c1] - D_0037A028[c0]) * i / 40;
        func_00f32728(7, spd + h);
        if (dir) h = (39 - i) / 2;
        if (tbl.t[h] >= 0) {
            { u8 *q = &D_00379F28[c1]; func_00f313d8(tbl.t[h], q[0], q[1], q[2]); }
        }
        func_001bfac8();
    }
    D_00F56DC0->c[1] = D_00379F28[c1 + 1];
    D_00F56DC0->c[2] = D_00379F28[c1 + 2];
    D_00F56DC0->c[4] = D_0037A028[c1];
    D_00F56DC0->c[5] = D_0037A028[c1 + 1];
    D_00F56DC0->c[0] = D_00379F28[c1];
    D_00F56DC0->c[6] = D_0037A028[c1 + 2];
    func_00f2e0b0();
}
