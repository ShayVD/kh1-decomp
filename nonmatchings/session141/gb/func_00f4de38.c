/* Round 48 wwm2: the hill3o order from a482da1b (gb func_00f4de38 near miss, score 290 -> 190, port of wm func_00f74f30 (wwm2 rou) moved a control line (break/case/label/return/goto) or broke a dependency, so its score 182 was not valid. Restored the last valid statement order: score 290. Earlier header below. */
/* score 290 (2168 vs 2184). Port of the wm func_00f74f30 near miss (same score), with symbols mapped by portmap2.py plus D_00F829D4 by hand. Same remaining issue as wm: the window clamp compiles to movn where the original uses a branch-likely; see nonmatchings/session141/wm/func_00f74f30.c. */
typedef struct { s32 x0, x4; u32 x8; u32 xC; u32 x10; } Pad;
typedef struct { u8 pad[12]; u16 xc; u16 xe; u16 x10; u16 x12; u8 pad2[10]; s16 x1e; } Lay;
typedef struct { u8 pad[208]; u16 hd0; u16 hd2; } Obj;
typedef struct { u8 a0; u8 pad1[7]; u8 a8; u8 pad9[87]; } Ent;
typedef struct { u8 pad[16]; s32 x10; } Win;
typedef struct { s16 v[2]; } SPair;
typedef struct { u8 pad[6]; s16 x6; } Sel;
extern Pad D_002C5AD0;
extern s32 D_00F702D0;
extern s32 D_00F702D4;
extern s32 D_00F702D8;
extern s32 D_00F702DC;
extern s32 D_00F702F0;
extern s32 D_00F703B8;
extern s32 D_00F703BC;
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
extern u16 D_00F705A8;
extern u16 D_00F705AC;
extern s32 D_00F70634;
extern s8 D_00F7073A;
extern Sel D_00F71150;
extern Lay D_00F71320;
extern SPair D_00F74148;
extern s32 D_00F829C4;
extern s32 D_00F829CC;
extern s32 D_00F829D4;
extern s32 D_00F829D8;
extern s32 D_00F829E4;
extern s32 D_00F829F8;
extern s32 D_00F82A28;
extern s32 D_00F82A34;
extern s32 D_00F82D74;
extern s32 D_00F82D78;
extern s32 D_00F82D7C;
extern s32 D_00F82D80;
extern s32 D_00F82D84;
extern s32 D_00F82D88;
void func_00106880(s32);
void func_0011d768(s32);
Ent *func_001bc4e0(void);
s32 func_001bc510(void);
s32 func_001be278(void);
Obj *func_001f31a8(Lay *, s32);
void func_001f3dc0(s32);
void func_0020bda8(s32);
void func_0020be10(s32);
void func_0024e468(s32);
s32 func_00f20018(void);
void func_00f399f8(s32);
void func_00f43cf0(s32);
void func_00f43d68(Win *);
void func_00f444d8(s32, s32, s32);
Win *func_00f445a8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_00f4de38(void)
{
    SPair c;
    Win *w;
    Win *w2;
    Obj *o;
    Ent *e;
    s32 t, n, cnt, i, v, s, res;
    u32 b;

    t = D_00F702F0;
    c = D_00F74148;
    D_00F702D0 = 10;
    func_00f445a8(16, 3, 0, 2, 0, 0, 0, 0, 0, D_00F703BC + 12, 0, D_00F703B8, 2, D_00F70538, D_00F7053C, D_00F70540, D_00F70544, 256, t);
    func_00f445a8(16, 0, 2, 1, 0, 15, 155, 7, D_00F703B8, D_00F703BC, 0, D_00F703F0, 0, 0, 0, 0, 0, 256, t);
    w = func_00f445a8(16, 2, 0, 2, 0, D_00F70518, c.v[0], 0, D_00F7051C, D_00F70520, 0, 0, 0, D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, func_00f20018() == 0 ? t : 1);
    func_00f445a8(16, 0, 2, 1, 0, 15, 1, 4, D_00F704A4, D_00F704A8, 0, D_00F704AC, 0, 0, 0, 0, 0, 256, t);
    e = func_001bc4e0();
    n = func_001bc510() - 1;
    cnt = 0;
    for (i = 0; i < n; i++) {
        if (e[i + 1].a8 == 1) cnt++;
    }
    for (i = 0; i < n; i++) {
    }
    v = 0;
    if (n >= 9) {
        v = cnt;
        if (n < v + 8) v = n - 8;
    }
    D_00F82D84 = v * 16;
    D_00F82D88 = (cnt - v) * 16;
    D_00F82D74 = -999;
    D_00F82D80 = 1;
    D_00F82D78 = 1;
    D_00F82D7C = 0;
    D_00F71320.x1e = func_001bc510() - 1;
    D_00F71320.xc = D_00F705A8;
    D_00F71320.xe = D_00F705AC;
    o = func_001f31a8(&D_00F71320, 1);
    o->hd0 = D_00F82D84;
    o->hd2 = D_00F82D88;
    for (;;) {
        w->x10 = c.v[D_00F82A34];
        if (D_00F82D7C == 1) {
            o->hd0 = D_00F82D84;
            o->hd2 = D_00F82D88;
            D_00F82D78 = 0;
            s = D_00F71150.x6;
            func_0020be10(16);
            func_001f3dc0(D_00F829CC);
            w2 = func_00f445a8(6, 8, 2, 4, 0, 15, s, 4, 160, 216, 0, 0, 0, 0, 0, 0, 0, 256, D_00F702F0);
            func_0024e468(D_00F702F0);
            w2->x10 = s;
            func_0024e468(1);
            for (;;) {
                b = D_002C5AD0.x8;
                if (b & 0x4000) {
                    func_0011d768(3);
                    break;
                }
                if (b & 0x2000) {
                    func_0011d768(2);
                    break;
                }
                func_0024e468(1);
            }
            D_00F82D74 = -999;
            func_00f444d8(6, 0, D_00F702F0);
            func_0024e468(D_00F702F0);
            func_00f43d68(w2);
            func_0020bda8(16);
            D_00F82D7C = 0;
            D_00F82D78 = 1;
            func_001f3dc0((s32)o);
        }
        if (D_00F82D7C == 2 || D_00F82D7C == 3) {
            o->hd0 = D_00F82D84;
            s = D_00F82D7C == 2 ? 39 : 233;
            res = 1;
            o->hd2 = D_00F82D88;
            D_00F82D78 = 0;
            D_00F829E4 = 1;
            func_001f3dc0(D_00F829CC);
            w2 = func_00f445a8(6, 9, 2, 4, 0, 15, s, 4, 160, 208, 0, D_00F70634, 0, 0, 0, 0, 0, 256, D_00F702F0);
            w2->x10 = s;
            func_0024e468(D_00F702F0);
            func_0024e468(1);
            for (;;) {
                b = D_002C5AD0.x8;
                if (b & 0x4000) {
                    res = 1;
                    func_0011d768(3);
                    break;
                }
                if (b & 0x2000) {
                    func_0011d768(2);
                    if (D_00F829E4 == 0) {
                        D_00F829D4 = 258;
                        D_00F829D8 = 212;
                        D_00F82D80 = 0;
                    }
                    break;
                }
                if ((b | b >> 24) & 0xA0) {
                    func_0011d768(1);
                    res = D_00F829E4 ^= 1;
                }
                D_00F829D4 = D_00F829E4 ? 368 : 258;
                D_00F829D8 = 212;
                func_0024e468(1);
            }
            if (!res) {
                D_00F82D7C = -1;
                func_00f444d8(6, 0, D_00F702F0);
                func_0024e468(D_00F702F0);
                func_00f43d68(w2);
            } else {
                D_00F82D74 = -999;
                D_00F82D7C = 0;
                func_00f444d8(6, 0, D_00F702F0);
                func_0024e468(D_00F702F0);
                func_00f43d68(w2);
                D_00F82D78 = 1;
                func_001f3dc0((s32)o);
            }
        }
        if (D_00F82D74 >= -1) break;
        func_0024e468(1);
    }
    func_001f3dc0(D_00F829CC);
    if (D_00F82D74 >= 0) {
        func_0020be10(16);
        func_00f444d8(-1, 0, D_00F702F0);
        func_0024e468(D_00F702F0);
        func_00f43cf0(-1);
        D_00F702D4 = D_00F82D74 + 1;
        func_00f399f8(D_00F82D74);
        D_00F82A34 = 0;
        func_00106880(30);
        func_0024e468(60);
        D_00F7073A = 2;
        D_00F829C4 = 0;
        if (D_00F829F8 > 0) D_00F829F8 = -1;
        for (;;) func_0024e468(1);
    }
    D_00F82A28 = 0;
    func_00f444d8(16, 0, D_00F702F0);
    func_0024e468(D_00F702F0);
    func_00f43cf0(16);
    D_00F702D8 = D_00F702DC = func_001be278() + 1;
    D_00F82A34 = 0;
    if (D_00F829F8 > 0) D_00F829F8 = -1;
}
