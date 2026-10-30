/* Round 48 wwm2: the hill3o order from 7989fb08 (wm func_00f74f30 near miss, score 190 -> 182, hill3o statement order (wwm2 round) moved a control line (break/case/label/return/goto) or broke a dependency, so its score 182 was not valid. Restored the last valid statement order: score 190. Earlier header below. */
/* Round 36 (wwm2): wm.x func_00f74f30 near miss: score 290 -> 190 (355 -> 351 words, 2176 vs 2184); statement order from the score-ranked dependency-safe hill3 (r35/hill3.py, 120 s, seed 363). Earlier header below. */
/* score 290 (2168 vs 2184). The state machine was read from the asm: four func_00f6b6a0 setup calls, then the 0x60-stride count loop over func_001bc4e0()+1 entries (.a8 == 1). An empty for loop follows, which ee-gcc pads with short-loop nops, and both loops match. Then a for(;;) loop handles D_0108F53C == 1 (confirm box) and D_0108F53C in {2,3} (yes/no box with a D_0108F1A4 toggle), retrying while D_0108F534 < -1. Two tails: D_0108F534 >= 0 ends in an endless wait, and the other path stores D_00FB4A58/5C. Left: the window calc (v = 0; if (n >= 9) { v = cnt; if (n < v + 8) v = n - 8; }) compiles to movn here, while the original uses a branch-likely with a duplicated subu and copies cnt through an extra register. Tried an if/else chain, do-while(0) barriers, goto and an inline helper, with no change. After that point the s-register numbering is shifted by one (o is s3 in the original, s4 here), and the pad loop tests 0x2000 before 0x4000. */
typedef struct { s32 x0, x4; u32 x8; u32 xC; u32 x10; } Pad;
typedef struct { u8 pad[12]; u16 xc; u16 xe; u16 x10; u16 x12; u8 pad2[10]; s16 x1e; } Lay;
typedef struct { u8 pad[208]; u16 hd0; u16 hd2; } Obj;
typedef struct { u8 a0; u8 pad1[7]; u8 a8; u8 pad9[87]; } Ent;
typedef struct { u8 pad[16]; s32 x10; } Win;
typedef struct { s16 v[2]; } SPair;
typedef struct { u8 pad[6]; s16 x6; } Sel;
extern Pad D_002C5AD0;
extern s32 D_00FB4A50;
extern s32 D_00FB4A54;
extern s32 D_00FB4A58;
extern s32 D_00FB4A5C;
extern s32 D_00FB4A70;
extern s32 D_00FB4B38;
extern s32 D_00FB4B3C;
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
extern u16 D_00FB4D28;
extern u16 D_00FB4D2C;
extern s32 D_00FB4DB4;
extern s8 D_00FB4EBA;
extern Sel D_00FB58D0;
extern Lay D_00FB5AA0;
extern SPair D_00FBA1F8;
extern s32 D_0108F184;
extern s32 D_0108F18C;
extern s32 D_0108F194;
extern s32 D_0108F198;
extern s32 D_0108F1A4;
extern s32 D_0108F1B8;
extern s32 D_0108F1E8;
extern s32 D_0108F1F4;
extern s32 D_0108F534;
extern s32 D_0108F538;
extern s32 D_0108F53C;
extern s32 D_0108F540;
extern s32 D_0108F544;
extern s32 D_0108F548;
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
s32 func_00f47110(void);
void func_00f60af0(s32);
void func_00f6ade8(s32);
void func_00f6ae60(Win *);
void func_00f6b5d0(s32, s32, s32);
Win *func_00f6b6a0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_00f74f30(void)
{
    SPair c;
    Win *w;
    Win *w2;
    Obj *o;
    Ent *e;
    s32 t, n, cnt, i, v, s, res;
    u32 b;

    c = D_00FBA1F8;
    t = D_00FB4A70;
    D_00FB4A50 = 10;
    func_00f6b6a0(16, 3, 0, 2, 0, 0, 0, 0, 0, D_00FB4B3C + 12, 0, D_00FB4B38, 2, D_00FB4CB8, D_00FB4CBC, D_00FB4CC0, D_00FB4CC4, 256, t);
    func_00f6b6a0(16, 0, 2, 1, 0, 15, 155, 7, D_00FB4B38, D_00FB4B3C, 0, D_00FB4B70, 0, 0, 0, 0, 0, 256, t);
    w = func_00f6b6a0(16, 2, 0, 2, 0, D_00FB4C98, c.v[0], 0, D_00FB4C9C, D_00FB4CA0, 0, 0, 0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, func_00f47110() == 0 ? t : 1);
    func_00f6b6a0(16, 0, 2, 1, 0, 15, 1, 4, D_00FB4C24, D_00FB4C28, 0, D_00FB4C2C, 0, 0, 0, 0, 0, 256, t);
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
    D_0108F53C = 0;
    D_0108F538 = 1;
    D_0108F540 = 1;
    D_0108F534 = -999;
    D_0108F548 = (cnt - v) * 16;
    D_0108F544 = v * 16;
    D_00FB5AA0.x1e = func_001bc510() - 1;
    D_00FB5AA0.xc = D_00FB4D28;
    D_00FB5AA0.xe = D_00FB4D2C;
    o = func_001f31a8(&D_00FB5AA0, 1);
    o->hd0 = D_0108F544;
    o->hd2 = D_0108F548;
    for (;;) {
        w->x10 = c.v[D_0108F1F4];
        if (D_0108F53C == 1) {
            o->hd0 = D_0108F544;
            o->hd2 = D_0108F548;
            D_0108F538 = 0;
            s = D_00FB58D0.x6;
            func_0020be10(16);
            func_001f3dc0(D_0108F18C);
            w2 = func_00f6b6a0(6, 8, 2, 4, 0, 15, s, 4, 160, 216, 0, 0, 0, 0, 0, 0, 0, 256, D_00FB4A70);
            func_0024e468(D_00FB4A70);
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
            D_0108F534 = -999;
            func_00f6b5d0(6, 0, D_00FB4A70);
            func_0024e468(D_00FB4A70);
            func_00f6ae60(w2);
            func_0020bda8(16);
            D_0108F53C = 0;
            D_0108F538 = 1;
            func_001f3dc0((s32)o);
        }
        if (D_0108F53C == 2 || D_0108F53C == 3) {
            o->hd0 = D_0108F544;
            o->hd2 = D_0108F548;
            D_0108F538 = 0;
            s = D_0108F53C == 2 ? 39 : 233;
            D_0108F1A4 = 1;
            res = 1;
            func_001f3dc0(D_0108F18C);
            w2 = func_00f6b6a0(6, 9, 2, 4, 0, 15, s, 4, 160, 208, 0, D_00FB4DB4, 0, 0, 0, 0, 0, 256, D_00FB4A70);
            w2->x10 = s;
            func_0024e468(D_00FB4A70);
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
                    if (D_0108F1A4 == 0) {
                        D_0108F194 = 258;
                        D_0108F198 = 212;
                        D_0108F540 = 0;
                    }
                    break;
                }
                if ((b | b >> 24) & 0xA0) {
                    func_0011d768(1);
                    res = D_0108F1A4 ^= 1;
                }
                D_0108F194 = D_0108F1A4 ? 368 : 258;
                D_0108F198 = 212;
                func_0024e468(1);
            }
            if (!res) {
                D_0108F53C = -1;
                func_00f6b5d0(6, 0, D_00FB4A70);
                func_0024e468(D_00FB4A70);
                func_00f6ae60(w2);
            } else {
                D_0108F534 = -999;
                D_0108F53C = 0;
                func_00f6b5d0(6, 0, D_00FB4A70);
                func_0024e468(D_00FB4A70);
                func_00f6ae60(w2);
                D_0108F538 = 1;
                func_001f3dc0((s32)o);
            }
        }
        if (D_0108F534 >= -1) break;
        func_0024e468(1);
    }
    func_001f3dc0(D_0108F18C);
    if (D_0108F534 >= 0) {
        func_0020be10(16);
        func_00f6b5d0(-1, 0, D_00FB4A70);
        func_0024e468(D_00FB4A70);
        func_00f6ade8(-1);
        D_00FB4A54 = D_0108F534 + 1;
        func_00f60af0(D_0108F534);
        D_0108F1F4 = 0;
        func_00106880(30);
        func_0024e468(60);
        D_0108F184 = 0;
        D_00FB4EBA = 2;
        if (D_0108F1B8 > 0) D_0108F1B8 = -1;
        for (;;) func_0024e468(1);
    }
    D_0108F1E8 = 0;
    func_00f6b5d0(16, 0, D_00FB4A70);
    func_0024e468(D_00FB4A70);
    func_00f6ade8(16);
    D_00FB4A58 = D_00FB4A5C = func_001be278() + 1;
    D_0108F1F4 = 0;
    if (D_0108F1B8 > 0) D_0108F1B8 = -1;
}
