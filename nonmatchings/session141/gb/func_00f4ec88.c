/* drafttwins.py: score 2430 -> 2412, port.py of the wm twin func_00f75d80 draft. Earlier header below. */
/* Round 48 wwm2: the hill3o order from b1f42fe2 (gb func_00f4ec88 near miss, score 2430 -> 2412, port of wm func_00f75d80 (wwm2 r) moved a control line (break/case/label/return/goto) or broke a dependency, so its score 1758 was not valid. Restored the last valid statement order: score 2430. Earlier header below. */
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
extern P2 D_00F74150, D_00F74158, D_00F74160;
extern s32 D_00F702D0, D_00F702D4, D_00F702D8, D_00F702DC, D_00F702F0;
extern f32 D_00F702E0, D_00F70334;
extern s32 D_00F82D8C, D_00F82D90, D_00F82D94, D_00F82D98, D_00F82D9C, D_00F82DA0, D_00F82DA4;
extern s32 D_00F82A0C, D_00F82A10, D_00F82A14, D_00F82A28;
extern s32 D_00F705C4, D_00F705C8, D_00F705D4, D_00F705A8, D_00F705AC;
extern Cfg D_00F71350;
extern s32 D_00F829CC, D_00F829E4, D_00F829F8;
extern s32 D_00F704A4, D_00F704A8, D_00F704AC;
extern s32 D_00F70518, D_00F7051C, D_00F70520, D_00F70524, D_00F70528, D_00F7052C, D_00F70530;
extern s32 D_00F70538, D_00F7053C, D_00F70540, D_00F70544;
extern s32 D_00F705A0, D_00F705A4, D_00F703EC, D_00F703F0, D_00F703B8, D_00F703BC;
extern s32 D_00F70624, D_00F70628, D_00F70634;
extern Pad D_002C5AD0;
extern u8 D_00F82AD8[];
u8 *func_001bc4e0(void); CONTEXT_ONLY u8 * func_001bc4e0() { return 0; }
s32 func_001bc510(void); CONTEXT_ONLY s32 func_001bc510() { return 0; }
Snd *func_001f31a8(Cfg *, s32);
void func_001f3dc0(s32);
Item *func_00f445a8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00f20018(void);
Item *func_00f43388(void);
void func_00f4d880(Item *, s32);
void func_00f444b8(Item *, f32, f32);
void func_0024e468(s32);
void func_0011d768(s32);
void func_00f4d8c0(s32, s32, s32);
void func_00f444d8(s32, s32, s32);
void func_00f43cf0(s32);
void func_00f43d68(Item *);
s32 func_001be278(void); CONTEXT_ONLY s32 func_001be278() { return 0; }
s32 func_001be010(s32);
void func_001be320(s32);
void func_001be430(s32);
void func_0020be10(s32);
void func_0020bda8(s32);
void func_00f47c88(s32);
void func_0024d1c8(void *, s32, s32, s32);
s32 func_0024d408(void);
s32 func_0024cf80(void); CONTEXT_ONLY s32 func_0024cf80() { return 0; }
s32 func_0024cf90(void);

#define HILITE(s0)                                                              \
    if (D_00F829E4) {                                                           \
        func_00f4d8c0((s32)s0->x14 + D_00F70634 + 90, (s32)s0->x18, 8);         \
    } else {                                                                    \
        func_00f4d8c0((s32)s0->x14 + 90, (s32)s0->x18, 8);                      \
    }                                                                           \
    func_0024e468(1);
#define TOGGLE()                                        \
    if ((b | (b >> 24)) & 0xA0) {                        \
        func_0011d768(1);                               \
        D_00F829E4 ^= 1;                                \
        b = D_002C5AD0.x8;                              \
    }

void func_00f4ec88(void) {
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
    t0 = D_00F74150;
    t1 = D_00F74158;
    t2 = D_00F74160;
    wait = D_00F702F0;
    D_00F702D0 = 10;
    D_00F82D8C = 0;
    base = func_001bc4e0();
    n = func_001bc510();
    cnt = 0;
    rec = base + 96;
    for (i = n - 1, k = 0; i > 0; i--) {
        if (base[104 + k] == 0) cnt++;
        k += 96;
    }
    D_00F82A0C = D_00F705C4;
    D_00F82A10 = D_00F705C8;
    D_00F82A14 = D_00F705D4;
    D_00F71350.x1E = cnt;
    D_00F82D9C = 0;
    D_00F702E0 = D_00F70334;
    D_00F82D94 = -999;
    D_00F82DA0 = 0;
    D_00F71350.xC = D_00F705A8;
    idx = 0;
    D_00F82D98 = 0;
    D_00F82D90 = 0;
    D_00F71350.xE = D_00F705AC;
    D_00F82DA4 = 0;
    snd = func_001f31a8(&D_00F71350, 1);
    func_001f3dc0(D_00F829CC);
    func_00f445a8(18, 0, 2, 1, 0, 15, 1, 4, D_00F704A4, D_00F704A8, 0, D_00F704AC, 0, 0, 0, 0, 0, 256, wait);
main:
    D_00F702DC = 0;
    D_00F702D4 = 0;
    v = 1;
    D_00F702D8 = 0;
    if (func_00f20018() == 0) v = wait;
    r = func_00f445a8(17, 2, 0, 1, 0, D_00F70518, t0.v[idx / 2], 0, D_00F7051C, D_00F70520, 0, 0, 0,
                      D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, v);
    y = D_00F705A4;
    items[0] = func_00f43388();
    items[0]->x0 = 17;
    items[0]->x1 = 0;
    items[0]->x2 = 2;
    items[0]->x3 = 0;
    items[0]->x10 = 33;
    items[0]->xC = 1;
    items[0]->x14 = D_00F705A0;
    items[0]->x20 = y;
    items[0]->x18 = y;
    items[0]->x30 = 0.0f;
    items[0]->x8 = D_00F703F0;
    items[0]->x2C = 0.0f;
    items[0]->x1C = D_00F705A0;
    if (sel == 0) {
        items[0]->x4 = 1;
        func_00f4d880(items[0], 8);
    } else {
        items[0]->x4 = 0;
    }
    y += D_00F703EC;
    items[1] = func_00f43388();
    items[1]->x0 = 17;
    items[1]->x1 = 0;
    items[1]->x2 = 2;
    items[1]->x3 = 0;
    items[1]->x10 = 37;
    items[1]->x18 = y;
    items[1]->x1C = D_00F705A0;
    items[1]->x20 = y;
    items[1]->xC = 1;
    items[1]->x30 = 0.0f;
    items[1]->x2C = 0.0f;
    items[1]->x14 = D_00F705A0;
    items[1]->x8 = D_00F703F0;
    if (sel == 1) {
        items[1]->x4 = 1;
        func_00f4d880(items[1], 8);
    } else {
        items[1]->x4 = 0;
    }
    for (i = 0; i < 2; i++) {
        func_00f444b8(items[i], 256.0f, D_00F702F0);
        func_0024e468(2);
    }
    func_0024e468(D_00F702F0);
    for (;;) {
        b = D_002C5AD0.x8;
        if (b & 0x4000) {
            func_0011d768(3);
            func_0024e468(1);
            if (D_00F82D8C != 0) goto leave;
            func_001f3dc0(D_00F829CC);
            D_00F829E4 = 1;
            s0 = func_00f445a8(6, 10, 2, 4, 0, 15, 225, 4, D_00F70624, D_00F70628 - 8, 0, D_00F70634, 0, 0, 0, 0, 0, 256, D_00F702F0);
            for (;;) {
                b = D_002C5AD0.x8;
                if (b & 0x4000) {
                    func_0011d768(3);
                    sel = 0;
                    func_00f444b8(s0, 0.0f, D_00F702F0);
                    func_0024e468(D_00F702F0);
                    D_00F82D9C = 0;
                    goto apply;
                }
                if (D_00F829E4 != 0 && (b & 0x2000)) {
                    func_0011d768(2);
                    func_00f444b8(s0, 0.0f, D_00F702F0);
                    goto leave;
                }
                TOGGLE();
                if (b & 0x2000) {
                    func_0011d768(2);
                    sel = 0;
                    func_00f444b8(s0, 0.0f, D_00F702F0);
                    idx = 0;
                    func_0024e468(D_00F702F0);
                    D_00F82D9C = 0;
                    goto next;
                }
                HILITE(s0);
            }
        }
        if (b & 0x2000) {
            func_0011d768(2);
            D_00F702D4 = 0;
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
    apply:
        idx = sel * 2;
        D_00F82D9C = sel;
        r->x10 = t0.v[sel];
        if (sel != old) func_0011d768(1);
        for (i = 0; i < 2; i++) {
            if (i == sel) {
                items[sel]->x4 = 1;
                func_00f4d880(items[sel], 8);
            } else {
                items[i]->x4 = 0;
            }
        }
        func_0024e468(1);
    }
leave:
    D_00F82D98 = -1;
    func_00f444d8(17, 0, D_00F702F0);
    func_00f444d8(18, 0, D_00F702F0);
    func_0024e468(D_00F702F0);
    func_00f43cf0(17);
    func_00f43cf0(18);
    if (D_00F829F8 > 0) D_00F829F8 = -1;
    v = func_001be278() + 1;
    D_00F702DC = v;
    D_00F702D4 = 0;
    D_00F702D8 = v;
    return;
next:
    func_0024e468(1);
    D_00F82D94 = -999;
    D_00F82D98 = 1;
    func_001f3dc0((s32)snd);
    func_00f444d8(17, 0, D_00F702F0);
    func_0024e468(D_00F702F0);
    func_00f43cf0(17);
    v = 1;
    if (D_00F829F8 > 0) D_00F829F8 = -1;
    if (func_00f20018() == 0) v = D_00F702F0;
    func_00f445a8(17, 2, 0, 1, 0, D_00F70518, t1.v[idx / 2], 0, D_00F7051C, D_00F70520, 0, 0, 0,
                  D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, v);
    func_00f445a8(17, 3, 0, 2, 0, 0, 0, 0, 0, D_00F703BC + 12, 0, D_00F703B8, 2,
                  D_00F70538, D_00F7053C, D_00F70540, D_00F70544, 256, wait);
    func_00f445a8(17, 0, 2, 1, 0, 15, t2.v[idx / 2], 7, D_00F703B8, D_00F703BC, 0, D_00F703F0, 0, 0, 0, 0, 0, 256, wait);
state:
    while (D_00F82D94 < -1) {
        func_0024e468(1);
    }
    D_00F82D98 = 0;
    snd->xD2 = D_00F82DA4;
    snd->xD0 = D_00F82DA0;
    if (sel != 0) {
        if (D_00F82D90 == 0) goto end;
        func_001f3dc0(D_00F829CC);
        if (D_00F82D90 == 2) {
            func_0020be10(16);
            s0 = func_00f445a8(6, 8, 2, 4, 0, 15, 238, 4, D_00F70624, D_00F70628, 0, D_00F70634, 0, 0, 0, 0, 0, 256, D_00F702F0);
            while (!(D_002C5AD0.x8 & 0x6000)) {
                func_0024e468(1);
            }
            if (D_002C5AD0.x8 & 0x2000) {
                func_0011d768(2);
            } else {
                func_0011d768(3);
            }
            func_00f444b8(s0, 0.0f, D_00F702F0);
            func_0024e468(D_00F702F0);
            func_00f43d68(s0);
            D_00F82D90 = 0;
            func_001f3dc0((s32)snd);
            func_0020bda8(16);
            D_00F82D98 = 1;
            D_00F82D94 = -999;
            goto state;
        }
        if (func_001be278() == D_00F82D94) {
            func_0020be10(16);
            s0 = func_00f445a8(6, 8, 2, 4, 0, 15, 232, 4, 160, 216, 0, 0, 0, 0, 0, 0, 0, 256, D_00F702F0);
            func_0024e468(D_00F702F0);
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
            func_00f444b8(s0, 0.0f, D_00F702F0);
            func_0024e468(D_00F702F0);
            func_00f43d68(s0);
            D_00F82D98 = 1;
            D_00F82D90 = 0;
            D_00F82D94 = -999;
            func_001f3dc0((s32)snd);
            goto state;
        }
        if (D_00F82D94 < 0) goto end;
        D_00F829E4 = 1;
        s0 = func_00f445a8(6, 9, 2, 4, 0, 15, 43, 4, D_00F70624, D_00F70628, 0, D_00F70634, 0, 0, 0, 0, 0, 256, D_00F702F0);
        for (;;) {
            b = D_002C5AD0.x8;
            if (b & 0x4000) goto yes4;
            if (D_00F829E4 == 0) {
                if (b & 0x2000) {
                    if (func_001be278() == D_00F82D94) {
                        func_0011d768(4);
                    } else {
                        func_0011d768(2);
                        func_00f444b8(s0, 0.0f, D_00F702F0);
                        func_0024e468(D_00F702F0);
                        func_00f43d68(s0);
                        D_00F82D90 = 0;
                        if (D_00F82D94 >= 0) func_001be430(D_00F82D94);
                        goto end;
                    }
                }
            } else if (b & 0x2000) {
            yes4:
                if (b & 0x2000) {
                    func_0011d768(2);
                } else {
                    func_0011d768(3);
                }
                func_00f444b8(s0, 0.0f, D_00F702F0);
                goto close;
            }
            b = D_002C5AD0.x8;
            TOGGLE();
            HILITE(s0);
        }
    }
    if (D_00F82D90 != 0) {
        func_001f3dc0(D_00F829CC);
        D_00F829E4 = 1;
        s0 = func_00f445a8(6, 10, 2, 4, 0, 15, 42, 4, D_00F70624, D_00F70628, 0, D_00F70634, 0, 0, 0, 0, 0, 256, D_00F702F0);
        for (;;) {
            b = D_002C5AD0.x8;
            if ((b & 0x4000) || (D_00F829E4 != 0 && (b & 0x2000))) {
                if (b & 0x2000) {
                    func_0011d768(2);
                } else {
                    func_0011d768(3);
                }
                func_00f444b8(s0, 0.0f, D_00F702F0);
                goto close;
            }
            if (D_00F829E4 == 0 && (b & 0x2000)) break;
            TOGGLE();
            HILITE(s0);
        }
        func_0011d768(2);
        func_00f444b8(s0, 0.0f, D_00F702F0);
        func_0024e468(D_00F702F0);
        func_00f43d68(s0);
        D_00F82D90 = 0;
        if (D_00F82D94 < 0) goto end;
        s2 = func_001be010(D_00F82D94);
        D_00F82D8C = 1;
        if (func_001be278() == s2) goto end;
        if (rec[s2 * 96 + 2] == 0) goto end;
        func_0024e468(1);
        func_001f3dc0(D_00F829CC);
        D_00F829E4 = 1;
        s0 = func_00f445a8(6, 10, 2, 4, 0, 15, 226, 4, D_00F70624, D_00F70628 - 8, 0, D_00F70634, 0, 0, 0, 0, 0, 256, D_00F702F0);
        for (;;) {
            b = D_002C5AD0.x8;
            if ((b & 0x4000) || (D_00F829E4 != 0 && (b & 0x2000))) {
                if (b & 0x2000) {
                    func_0011d768(2);
                } else {
                    func_0011d768(3);
                }
                func_00f444b8(s0, 0.0f, D_00F702F0);
                func_0024e468(D_00F702F0);
                func_00f43d68(s0);
                goto end;
            }
            b = D_002C5AD0.x8;
            TOGGLE();
            if (b & 0x2000) {
                func_0011d768(2);
                func_00f444b8(s0, 0.0f, D_00F702F0);
                func_0024e468(D_00F702F0);
                func_00f43d68(s0);
                func_001be320(s2);
                snd->xD0 = 0;
                snd->xD2 = 0;
                goto end;
            }
            HILITE(s0);
        }
    }
    if (D_00F82D94 < 0) goto end;
    D_00F82A28 = 0;
    func_00f444d8(18, 0, D_00F702F0);
    func_00f444d8(17, 0, D_00F702F0);
    func_00f444d8(2, 0, D_00F702F0);
    func_0020be10(16);
    func_0024e468(D_00F702F0);
    snd->x90 = 0;
    func_00f47c88(0);
    func_0024d1c8(D_00F82AD8, D_00F82D94, 1, 0);
    while (func_0024d408() == 0) {
        func_0024e468(1);
    }
    func_0020bda8(16);
    *(f32 *)&D_00F82A28 = 128.0f;
    func_00f444d8(17, 256, D_00F702F0);
    func_00f444d8(18, 256, D_00F702F0);
    func_00f444d8(2, 256, D_00F702F0);
    func_0024e468(D_00F702F0);
    snd->x90 = 128;
    if (func_0024cf80() == 0) {
        D_00F82D90 = 0;
        func_001f3dc0((s32)snd);
        D_00F82D94 = -999;
        D_00F82D98 = 1;
        goto state;
    }
    s2 = func_0024cf90();
    if (rec[s2 * 96 + 2] != 0) {
        func_0024e468(1);
        func_001f3dc0(D_00F829CC);
        D_00F829E4 = 1;
        s0 = func_00f445a8(6, 10, 2, 4, 0, 15, 226, 4, D_00F70624, D_00F70628 - 8, 0, D_00F70634, 0, 0, 0, 0, 0, 256, D_00F702F0);
        for (;;) {
            b = D_002C5AD0.x8;
            if ((b & 0x4000) || (D_00F829E4 != 0 && (b & 0x2000))) {
                if (b & 0x2000) {
                    func_0011d768(2);
                } else {
                    func_0011d768(3);
                }
                func_00f444b8(s0, 0.0f, D_00F702F0);
                func_0024e468(D_00F702F0);
                func_00f43d68(s0);
                break;
            }
            b = D_002C5AD0.x8;
            TOGGLE();
            if (b & 0x2000) {
                func_0011d768(2);
                func_00f444b8(s0, 0.0f, D_00F702F0);
                func_0024e468(D_00F702F0);
                func_00f43d68(s0);
                func_001be320(s2);
                snd->xD0 = 0;
                snd->xD2 = 0;
                break;
            }
            HILITE(s0);
        }
    }
    D_00F82D8C = 1;
    func_001f3dc0(D_00F829CC);
    goto end;
close:
    func_0024e468(D_00F702F0);
    func_00f43d68(s0);
    D_00F82D90 = 0;
    func_001f3dc0((s32)snd);
    D_00F82D94 = -999;
    D_00F82D98 = 1;
    goto state;
end:
    func_00f444d8(17, 0, D_00F702F0);
    func_0024e468(D_00F702F0);
    func_00f43cf0(17);
    if (D_00F829F8 > 0) D_00F829F8 = -1;
    goto main;
}
