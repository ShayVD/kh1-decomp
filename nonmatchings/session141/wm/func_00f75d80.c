/* Round 48 wwm2: the hill3o order from 53001ba1 (wm func_00f75d80 near miss, score 2412 -> 1758, hill3o statement order (wwm2 rou) moved a control line (break/case/label/return/goto) or broke a dependency, so its score 1758 was not valid. Restored the last valid statement order: score 2412. Earlier header below. */
/* NEAR MISS 1531 words, score 2430 (6200 vs 6344 bytes). Port of gb func_00f4ec88 (same score; port.py mapped every symbol). Structurally complete draft, not polished; see the gb file for notes. Round 19 (wwm1): score 2430 -> 2412 with sclimb.py (CONTEXT_ONLY toggles plus dependency-checked statement moves). */
typedef struct {
    u8 x0, x1, x2, x3, x4, x5;
    u8 pad6[2];
    u16 x8, xA, xC;
    u16 padE;
    s32 x10;
    f32 x14, x18, x1C, x20;
    u8 pad24[8];
    f32 x2C, x30;
} Item;
typedef struct { s16 v[2]; } P2;
typedef struct { u32 x0, x4, x8, xC, x10; } Pad;
typedef struct { u8 pad[12]; u16 xC, xE; u8 pad10[14]; u16 x1E; } Cfg;
typedef struct { u8 pad[0x90]; s32 x90; u8 pad94[0xD0 - 0x94]; u16 xD0, xD2; } Snd;
extern P2 D_00FBA200, D_00FBA208, D_00FBA210;
extern s32 D_00FB4A50, D_00FB4A54, D_00FB4A58, D_00FB4A5C, D_00FB4A70;
extern f32 D_00FB4A60, D_00FB4AB4;
extern s32 D_0108F54C, D_0108F550, D_0108F554, D_0108F558, D_0108F55C, D_0108F560, D_0108F564;
extern s32 D_0108F1CC, D_0108F1D0, D_0108F1D4, D_0108F1E8;
extern s32 D_00FB4D44, D_00FB4D48, D_00FB4D54, D_00FB4D28, D_00FB4D2C;
extern Cfg D_00FB5AD0;
extern s32 D_0108F18C, D_0108F1A4, D_0108F1B8;
extern s32 D_00FB4C24, D_00FB4C28, D_00FB4C2C;
extern s32 D_00FB4C98, D_00FB4C9C, D_00FB4CA0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0;
extern s32 D_00FB4CB8, D_00FB4CBC, D_00FB4CC0, D_00FB4CC4;
extern s32 D_00FB4D20, D_00FB4D24, D_00FB4B6C, D_00FB4B70, D_00FB4B38, D_00FB4B3C;
extern s32 D_00FB4DA4, D_00FB4DA8, D_00FB4DB4;
extern Pad D_002C5AD0;
extern u8 D_0108F298[];
u8 *func_001bc4e0(void); CONTEXT_ONLY u8 * func_001bc4e0() { return 0; }
s32 func_001bc510(void); CONTEXT_ONLY s32 func_001bc510() { return 0; }
Snd *func_001f31a8(Cfg *);
void func_001f3dc0(s32);
Item *func_00f6b6a0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00f47110(void);
Item *func_00f6a480(void);
void func_00f74978(Item *, s32);
void func_00f6b5b0(Item *, f32, f32);
void func_0024e468(s32);
void func_0011d768(s32);
void func_00f749b8(s32, s32, s32);
void func_00f6b5d0(s32, s32, s32);
void func_00f6ade8(s32);
void func_00f6ae60(Item *);
s32 func_001be278(void); CONTEXT_ONLY s32 func_001be278() { return 0; }
s32 func_001be010(void);
void func_001be320(s32);
void func_001be430(void);
void func_0020be10(s32);
void func_0020bda8(s32);
void func_00f6ed80(s32);
void func_0024d1c8(void *, s32, s32, s32);
s32 func_0024d408(void);
s32 func_0024cf80(void); CONTEXT_ONLY s32 func_0024cf80() { return 0; }
s32 func_0024cf90(void);

#define HILITE(s0)                                                              \
    if (D_0108F1A4) {                                                           \
        func_00f749b8((s32)s0->x14 + D_00FB4DB4 + 90, (s32)s0->x18, 8);         \
    } else {                                                                    \
        func_00f749b8((s32)s0->x14 + 90, (s32)s0->x18, 8);                      \
    }                                                                           \
    func_0024e468(1);
#define TOGGLE()                                        \
    if ((b | (b >> 24)) & 0xA0) {                        \
        func_0011d768(1);                               \
        D_0108F1A4 ^= 1;                                \
        b = D_002C5AD0.x8;                              \
    }

void func_00f75d80(void) {
    Item *items[4];
    P2 t0;
    u8 *rec;
    s32 pad2[2];
    P2 t1;
    s32 pad1[2];
    s32 wait;
    Item *s0;
    s32 y;
    s32 idx;
    u8 *base;
    u32 b;
    Item *r;
    s32 n, i, cnt, k, v;
    Snd *snd;
    s32 old;
    P2 t2;
    s32 pad0[2];
    s32 sel;
    s32 s2;

    sel = 0;
    t0 = D_00FBA200;
    t1 = D_00FBA208;
    t2 = D_00FBA210;
    wait = D_00FB4A70;
    D_00FB4A50 = 10;
    D_0108F54C = 0;
    base = func_001bc4e0();
    n = func_001bc510();
    cnt = 0;
    rec = base + 96;
    for (i = 0; i < n - 1; i++) {
        if (base[i * 96 + 104] == 0) cnt++;
    }
    D_0108F1CC = D_00FB4D44;
    D_0108F1D0 = D_00FB4D48;
    D_0108F1D4 = D_00FB4D54;
    D_00FB5AD0.x1E = cnt;
    D_0108F55C = 0;
    D_00FB4A60 = D_00FB4AB4;
    D_0108F554 = -999;
    D_0108F560 = 0;
    D_00FB5AD0.xC = D_00FB4D28;
    idx = 0;
    D_0108F558 = 0;
    D_0108F550 = 0;
    D_00FB5AD0.xE = D_00FB4D2C;
    D_0108F564 = 0;
    snd = func_001f31a8(&D_00FB5AD0);
    func_001f3dc0(D_0108F18C);
    func_00f6b6a0(18, 0, 2, 1, 0, 15, 1, 4, D_00FB4C24, D_00FB4C28, 0, D_00FB4C2C, 0, 0, 0, 0, 0, 256, wait);
main:
    D_00FB4A5C = 0;
    D_00FB4A54 = 0;
    v = 1;
    D_00FB4A58 = 0;
    if (func_00f47110() == 0) v = wait;
    r = func_00f6b6a0(17, 2, 0, 1, 0, D_00FB4C98, t0.v[idx / 2], 0, D_00FB4C9C, D_00FB4CA0, 0, 0, 0,
                      D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, v);
    y = D_00FB4D24;
    items[0] = func_00f6a480();
    items[0]->x0 = 17;
    items[0]->x1 = 0;
    items[0]->x2 = 2;
    items[0]->x3 = 0;
    items[0]->x10 = 33;
    items[0]->xC = 1;
    items[0]->x14 = D_00FB4D20;
    items[0]->x20 = y;
    items[0]->x18 = y;
    items[0]->x30 = 0.0f;
    items[0]->x8 = D_00FB4B70;
    items[0]->x2C = 0.0f;
    items[0]->x1C = D_00FB4D20;
    if (sel == 0) {
        items[0]->x4 = 1;
        func_00f74978(items[0], 8);
    } else {
        items[0]->x4 = 0;
    }
    y += D_00FB4B6C;
    items[1] = func_00f6a480();
    items[1]->x0 = 17;
    items[1]->x1 = 0;
    items[1]->x2 = 2;
    items[1]->x3 = 0;
    items[1]->x10 = 37;
    items[1]->x18 = y;
    items[1]->x1C = D_00FB4D20;
    items[1]->x20 = y;
    items[1]->xC = 1;
    items[1]->x30 = 0.0f;
    items[1]->x2C = 0.0f;
    items[1]->x14 = D_00FB4D20;
    items[1]->x8 = D_00FB4B70;
    if (sel == 1) {
        items[1]->x4 = 1;
        func_00f74978(items[1], 8);
    } else {
        items[1]->x4 = 0;
    }
    for (i = 0; i < 2; i++) {
        func_00f6b5b0(items[i], 256.0f, D_00FB4A70);
        func_0024e468(2);
    }
    func_0024e468(D_00FB4A70);
    for (;;) {
        b = D_002C5AD0.x8;
        if (b & 0x4000) {
            func_0011d768(3);
            func_0024e468(1);
            if (D_0108F54C == 0) {
                func_001f3dc0(D_0108F18C);
                D_0108F1A4 = 1;
                s0 = func_00f6b6a0(6, 10, 2, 4, 0, 15, 225, 4, D_00FB4DA4, D_00FB4DA8 - 8, 0, D_00FB4DB4, 0, 0, 0, 0, 0, 256, D_00FB4A70);
                goto t1;
            body:
                    TOGGLE();
                    if (b & 0x2000) {
                        func_0011d768(2);
                        sel = 0;
                        func_00f6b5b0(s0, 0.0f, D_00FB4A70);
                        idx = 0;
                        func_0024e468(D_00FB4A70);
                        D_0108F55C = 0;
                        goto next;
                    }
                    HILITE(s0);
            t1:
                b = D_002C5AD0.x8;
                if (b & 0x4000) goto yes;
                if (D_0108F1A4 == 0) goto body;
                if (!(b & 0x2000)) goto body;
                func_0011d768(2);
                func_00f6b5b0(s0, 0.0f, D_00FB4A70);
            }
            D_0108F558 = -1;
            func_00f6b5d0(17, 0, D_00FB4A70);
            func_00f6b5d0(18, 0, D_00FB4A70);
            func_0024e468(D_00FB4A70);
            func_00f6ade8(17);
            func_00f6ade8(18);
            if (D_0108F1B8 > 0) D_0108F1B8 = -1;
            v = func_001be278() + 1;
            D_00FB4A5C = v;
            D_00FB4A54 = 0;
            D_00FB4A58 = v;
            return;
        }
        if (b & 0x2000) {
            func_0011d768(2);
            D_00FB4A54 = 0;
            goto next;
        }
        old = sel;
        if (((b | (b >> 24)) & 0x10) && sel == 0) {
            sel = 1;
        } else {
            b = D_002C5AD0.x10;
            if ((b | (b >> 24)) & 0x10) {
                sel--;
                if (sel < 0) sel = 0;
            }
        }
        b = D_002C5AD0.x8;
        if (((b | (b >> 24)) & 0x40) && sel == 1) {
            sel = 0;
        } else {
            b = D_002C5AD0.x10;
            if ((b | (b >> 24)) & 0x40) {
                sel++;
                if (sel >= 2) sel = 1;
            }
        }
        goto apply;
    yes:
        func_0011d768(3);
        sel = 0;
        func_00f6b5b0(s0, 0.0f, D_00FB4A70);
        func_0024e468(D_00FB4A70);
        D_0108F55C = 0;
    apply:
        idx = sel * 2;
        D_0108F55C = sel;
        r->x10 = t0.v[sel];
        if (sel != old) func_0011d768(1);
        for (i = 0; i < 2; i++) {
            if (i == sel) {
                items[sel]->x4 = 1;
                func_00f74978(items[sel], 8);
            } else {
                items[i]->x4 = 0;
            }
        }
        func_0024e468(1);
    }
next:
    func_0024e468(1);
    D_0108F554 = -999;
    D_0108F558 = 1;
    func_001f3dc0((s32)snd);
    func_00f6b5d0(17, 0, D_00FB4A70);
    func_0024e468(D_00FB4A70);
    func_00f6ade8(17);
    v = 1;
    if (D_0108F1B8 > 0) D_0108F1B8 = -1;
    if (func_00f47110() == 0) v = D_00FB4A70;
    func_00f6b6a0(17, 2, 0, 1, 0, D_00FB4C98, t1.v[idx / 2], 0, D_00FB4C9C, D_00FB4CA0, 0, 0, 0,
                  D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, v);
    func_00f6b6a0(17, 3, 0, 2, 0, 0, 0, 0, 0, D_00FB4B3C + 12, 0, D_00FB4B38, 2,
                  D_00FB4CB8, D_00FB4CBC, D_00FB4CC0, D_00FB4CC4, 256, wait);
    func_00f6b6a0(17, 0, 2, 1, 0, 15, t2.v[idx / 2], 7, D_00FB4B38, D_00FB4B3C, 0, D_00FB4B70, 0, 0, 0, 0, 0, 256, wait);
state:
    while (D_0108F554 < -1) {
        func_0024e468(1);
    }
    D_0108F558 = 0;
    snd->xD2 = D_0108F564;
    snd->xD0 = D_0108F560;
    if (sel != 0) goto selA;
    if (D_0108F550 != 0) {
        func_001f3dc0(D_0108F18C);
        D_0108F1A4 = 1;
        s0 = func_00f6b6a0(6, 10, 2, 4, 0, 15, 42, 4, D_00FB4DA4, D_00FB4DA8, 0, D_00FB4DB4, 0, 0, 0, 0, 0, 256, D_00FB4A70);
        for (;;) {
            b = D_002C5AD0.x8;
            if ((b & 0x4000) || (D_0108F1A4 != 0 && (b & 0x2000))) {
                if (b & 0x2000) {
                    func_0011d768(2);
                } else {
                    func_0011d768(3);
                }
                func_00f6b5b0(s0, 0.0f, D_00FB4A70);
                goto close;
            }
            if (D_0108F1A4 == 0 && (b & 0x2000)) break;
            TOGGLE();
            HILITE(s0);
        }
        func_0011d768(2);
        func_00f6b5b0(s0, 0.0f, D_00FB4A70);
        func_0024e468(D_00FB4A70);
        func_00f6ae60(s0);
        D_0108F550 = 0;
        if (D_0108F554 < 0) goto end;
        s2 = func_001be010();
        D_0108F54C = 1;
        if (func_001be278() == s2) goto end;
        if (rec[s2 * 96 + 2] == 0) goto end;
        func_0024e468(1);
        func_001f3dc0(D_0108F18C);
        D_0108F1A4 = 1;
        s0 = func_00f6b6a0(6, 10, 2, 4, 0, 15, 226, 4, D_00FB4DA4, D_00FB4DA8 - 8, 0, D_00FB4DB4, 0, 0, 0, 0, 0, 256, D_00FB4A70);
        for (;;) {
            b = D_002C5AD0.x8;
            if ((b & 0x4000) || (D_0108F1A4 != 0 && (b & 0x2000))) {
                if (b & 0x2000) {
                    func_0011d768(2);
                } else {
                    func_0011d768(3);
                }
                func_00f6b5b0(s0, 0.0f, D_00FB4A70);
                func_0024e468(D_00FB4A70);
                func_00f6ae60(s0);
                break;
            }
            b = D_002C5AD0.x8;
            TOGGLE();
            if (b & 0x2000) {
                func_0011d768(2);
                func_00f6b5b0(s0, 0.0f, D_00FB4A70);
                func_0024e468(D_00FB4A70);
                func_00f6ae60(s0);
                func_001be320(s2);
                snd->xD0 = 0;
                snd->xD2 = 0;
                goto end;
            }
            HILITE(s0);
        }
        goto end;
    }
    if (D_0108F554 < 0) goto end;
    D_0108F1E8 = 0;
    func_00f6b5d0(18, 0, D_00FB4A70);
    func_00f6b5d0(17, 0, D_00FB4A70);
    func_00f6b5d0(2, 0, D_00FB4A70);
    func_0020be10(16);
    func_0024e468(D_00FB4A70);
    snd->x90 = 0;
    func_00f6ed80(0);
    func_0024d1c8(D_0108F298, D_0108F554, 1, 0);
    while (func_0024d408() == 0) {
        func_0024e468(1);
    }
    func_0020bda8(16);
    *(f32 *)&D_0108F1E8 = 128.0f;
    func_00f6b5d0(17, 256, D_00FB4A70);
    func_00f6b5d0(18, 256, D_00FB4A70);
    func_00f6b5d0(2, 256, D_00FB4A70);
    func_0024e468(D_00FB4A70);
    snd->x90 = 128;
    if (func_0024cf80() == 0) {
        D_0108F550 = 0;
        func_001f3dc0((s32)snd);
        D_0108F554 = -999;
        D_0108F558 = 1;
        goto state;
    }
    s2 = func_0024cf90();
    if (rec[s2 * 96 + 2] != 0) {
        func_0024e468(1);
        func_001f3dc0(D_0108F18C);
        D_0108F1A4 = 1;
        s0 = func_00f6b6a0(6, 10, 2, 4, 0, 15, 226, 4, D_00FB4DA4, D_00FB4DA8 - 8, 0, D_00FB4DB4, 0, 0, 0, 0, 0, 256, D_00FB4A70);
        for (;;) {
            b = D_002C5AD0.x8;
            if ((b & 0x4000) || (D_0108F1A4 != 0 && (b & 0x2000))) {
                if (b & 0x2000) {
                    func_0011d768(2);
                } else {
                    func_0011d768(3);
                }
                func_00f6b5b0(s0, 0.0f, D_00FB4A70);
                func_0024e468(D_00FB4A70);
                func_00f6ae60(s0);
                break;
            }
            b = D_002C5AD0.x8;
            TOGGLE();
            if (b & 0x2000) {
                func_0011d768(2);
                func_00f6b5b0(s0, 0.0f, D_00FB4A70);
                func_0024e468(D_00FB4A70);
                func_00f6ae60(s0);
                func_001be320(s2);
                snd->xD0 = 0;
                snd->xD2 = 0;
                break;
            }
            HILITE(s0);
        }
    }
    D_0108F54C = 1;
    func_001f3dc0(D_0108F18C);
    goto end;
selA:
    if (D_0108F550 == 0) goto end;
    func_001f3dc0(D_0108F18C);
    if (D_0108F550 == 2) {
        func_0020be10(16);
        s0 = func_00f6b6a0(6, 8, 2, 4, 0, 15, 238, 4, D_00FB4DA4, D_00FB4DA8, 0, D_00FB4DB4, 0, 0, 0, 0, 0, 256, D_00FB4A70);
        while (!(D_002C5AD0.x8 & 0x6000)) {
            func_0024e468(1);
        }
        if (D_002C5AD0.x8 & 0x2000) {
            func_0011d768(2);
        } else {
            func_0011d768(3);
        }
        func_00f6b5b0(s0, 0.0f, D_00FB4A70);
        func_0024e468(D_00FB4A70);
        func_00f6ae60(s0);
        D_0108F550 = 0;
        func_001f3dc0((s32)snd);
        func_0020bda8(16);
        D_0108F558 = 1;
        D_0108F554 = -999;
        goto state;
    }
    if (func_001be278() == D_0108F554) {
        func_0020be10(16);
        s0 = func_00f6b6a0(6, 8, 2, 4, 0, 15, 232, 4, 160, 216, 0, 0, 0, 0, 0, 0, 0, 256, D_00FB4A70);
        func_0024e468(D_00FB4A70);
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
        func_0020bda8(16);
        func_00f6b5b0(s0, 0.0f, D_00FB4A70);
        func_0024e468(D_00FB4A70);
        func_00f6ae60(s0);
        D_0108F558 = 1;
        D_0108F550 = 0;
        D_0108F554 = -999;
        func_001f3dc0((s32)snd);
        goto state;
    }
    if (D_0108F554 < 0) goto end;
    D_0108F1A4 = 1;
    s0 = func_00f6b6a0(6, 9, 2, 4, 0, 15, 43, 4, D_00FB4DA4, D_00FB4DA8, 0, D_00FB4DB4, 0, 0, 0, 0, 0, 256, D_00FB4A70);
    for (;;) {
        b = D_002C5AD0.x8;
        if (b & 0x4000) break;
        if (D_0108F1A4 == 0) {
            if (b & 0x2000) {
                if (func_001be278() == D_0108F554) {
                    func_0011d768(4);
                } else {
                    func_0011d768(2);
                    func_00f6b5b0(s0, 0.0f, D_00FB4A70);
                    func_0024e468(D_00FB4A70);
                    func_00f6ae60(s0);
                    D_0108F550 = 0;
                    if (D_0108F554 >= 0) func_001be430();
                    goto end;
                }
            }
        } else if (b & 0x2000) break;
        b = D_002C5AD0.x8;
        TOGGLE();
        HILITE(s0);
    }
    if (b & 0x2000) {
        func_0011d768(2);
    } else {
        func_0011d768(3);
    }
    func_00f6b5b0(s0, 0.0f, D_00FB4A70);
close:
    func_0024e468(D_00FB4A70);
    func_00f6ae60(s0);
    D_0108F550 = 0;
    func_001f3dc0((s32)snd);
    D_0108F554 = -999;
    D_0108F558 = 1;
    goto state;
end:
    func_00f6b5d0(17, 0, D_00FB4A70);
    func_0024e468(D_00FB4A70);
    func_00f6ade8(17);
    if (D_0108F1B8 > 0) D_0108F1B8 = -1;
    goto main;
}
