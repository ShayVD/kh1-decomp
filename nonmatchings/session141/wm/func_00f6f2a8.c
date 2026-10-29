/* score 835 (4396 vs 4464 bytes): full structure (item count, 3+1 icon build, help window, pad loop with wrap nav, kind-3 guard dialog, 4-way switch, exit). Tried icon pointer var/ip base, chained-store order, s16 tables; remaining: 0.0f/128.0f not hoisted to f20/f21 at entry, icons base not in s8, sel*2 PRE slot sp7C. Round 25 wwm2. */
typedef struct { u8 pad[8]; u32 x8; u32 x10; } Pad;
typedef struct { u8 pad[16]; s32 x10; } Win;
typedef struct { u8 pad[12]; s16 xc; s16 xe; u8 pad10[14]; s16 x1e; } Lay;
typedef struct { u8 x0; u8 x1; u8 x2; u8 x3; u8 x4; u8 pad5[3]; s16 x8; u8 padA[2]; s16 xc; u8 padE[2]; s32 x10; f32 x14; f32 x18; f32 x1c; f32 x20; u8 pad24[8]; f32 x2c; f32 x30; } Ic;
typedef struct { u8 pad[8]; u8 x8; u8 pad9[87]; } Item;
extern Pad D_002C5AD0;
extern s32 D_00FB4A50;
extern s32 D_00FB4A58;
extern s32 D_00FB4A5C;
extern f32 D_00FB4A60;
extern s32 D_00FB4A70;
extern f32 D_00FB4AB0;
extern f32 D_00FB4AB4;
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
extern s32 D_00FB4CB8;
extern s32 D_00FB4CBC;
extern s32 D_00FB4CC0;
extern s32 D_00FB4CC4;
extern s32 D_00FB4D20;
extern s32 D_00FB4D24;
extern u16 D_00FB4D28;
extern u16 D_00FB4D2C;
extern s32 D_00FB4D3C;
extern s32 D_00FB4D40;
extern s32 D_00FB4D44;
extern s32 D_00FB4D48;
extern s32 D_00FB4D50;
extern s32 D_00FB4D54;
extern Lay D_00FB5930;
extern s16 D_00FB5958[];
extern u16 D_00FB5960[];
extern s16 D_0108F168[];
extern s8 D_0108F170[];
extern s16 D_0108F178[];
extern s32 D_0108F18C;
extern s32 D_0108F1B8;
extern s32 D_0108F1CC;
extern s32 D_0108F1D0;
extern s32 D_0108F1D4;
extern f32 D_0108F1E8;
extern s32 D_0108F290;
extern s32 D_0108F298;
extern s32 D_0108F2AC;
extern s32 D_0108F2B0;
extern s32 D_0108F2B4;
void func_0011d768(s32);
Item *func_001bc4e0(void);
s32 func_001bc510(void);
void func_001bd7f8(s32);
s32 func_001be278(void);
void func_001be320(s32);
s32 func_001f31a8(Lay *, s32);
void func_001f3dc0(s32);
s32 func_001f44a0(Lay *);
void func_0020bda8(s32);
void func_0020be10(s32);
void func_0024d1c8(s32 *, s32, s32, s32);
s32 func_0024d408(void);
void func_0024e468(s32);
s32 func_00f47110(void);
s32 func_00f68e50(s32);
Ic *func_00f6a480(void);
void func_00f6ade8(s32);
void func_00f6ae60(Win *);
void func_00f6b5b0(Ic *, f32, f32);
void func_00f6b5d0(s32, s32, s32);
Win *func_00f6b6a0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00f6cf78(void);
void func_00f6ed80(void *);
void func_00f71b68(void);
void func_00f73eb0(void);
void func_00f74978(Ic *, s32);

#define MAKE(n, nm) \
    pp = &icons[n]; \
    *pp = func_00f6a480(); \
    (*pp)->x0 = 4; \
    (*pp)->x1 = 0; \
    (*pp)->x2 = 2; \
    (*pp)->x3 = 0; \
    (*pp)->xc = 1; \
    (*pp)->x10 = nm; \
    D_0108F168[n] = nm; \
    (*pp)->x20 = (*pp)->x18 = (f32)x; \
    (*pp)->x2c = (*pp)->x30 = 0.0f; \
    (*pp)->x1c = (*pp)->x14 = (f32)D_00FB4D20; \
    (*pp)->x8 = D_00FB4B70; \
    if (n == sel) { \
        (*pp)->x4 = 1; \
        func_00f74978(*pp, 8); \
    } else { \
        (*pp)->x4 = 0; \
    } \
    D_0108F170[n] = n; \
    D_0108F178[n] = D_00FB5960[n];

void func_00f6f2a8(void)
{
    Ic *icons[4];
    Ic **pp;
    s32 lay;
    s32 mode;
    Win *help;
    Win *w;
    Item *items;
    s32 sel, old, n, i, k, x, cnt;
    u32 t;
    s32 v;

    sel = 0;
    mode = D_00FB4A70;
    for (;;) {
    items = func_001bc4e0();
    k = func_001bc510() - 1;
    cnt = 0;
    for (i = 0; i < k; i++) {
        if (items[i + 1].x8 == 0) {
            cnt++;
        }
    }
    D_0108F2B0 = -999;
    D_00FB5930.x1e = cnt;
    D_00FB5930.xc = D_00FB4D28;
    D_00FB5930.xe = D_00FB4D2C;
    D_0108F2B4 = 0;
    D_0108F290 = 0;
    lay = func_001f31a8(&D_00FB5930, 1);
    func_001f3dc0(D_0108F18C);
    func_00f6b6a0(4, 0, 2, 1, 0, 15, 3, 4, D_00FB4C24, D_00FB4C28, 0, D_00FB4C2C, 0, 0, 0, 0, 0, 256, mode);
    x = D_00FB4D24;
    MAKE(0, 31)
    x += D_00FB4B6C;
    MAKE(1, 35)
    x += D_00FB4B6C;
    MAKE(2, 5)
    x += D_00FB4B6C;
    n = 3;
    if (func_00f6cf78() >= 3) {
        MAKE(n, 7)
        n++;
    }
    help = func_00f6b6a0(4, 2, 0, 1, 0, D_00FB4C98, D_0108F178[sel], 0, D_00FB4C9C, D_00FB4CA0, 0, 0, 0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, func_00f47110() == 0 ? mode : 1);
    D_0108F1E8 = 128.0f;
    D_0108F2AC = D_0108F170[sel];
    for (i = 0; i < n; i++) {
        func_00f6b5b0(icons[i], 256.0f, (f32)D_00FB4A70);
        func_0024e468(2);
    }
    for (;;) {
        if (D_002C5AD0.x8 & 0x4000) {
            func_0011d768(3);
            break;
        }
        old = sel;
        t = D_002C5AD0.x8;
        if (((t | t >> 24) & 0x10) && sel == 0) {
            sel = n - 1;
        } else {
            t = D_002C5AD0.x10;
            if ((t | t >> 24) & 0x10) {
                sel--;
                if (sel < 0) {
                    sel = 0;
                }
            }
        }
        t = D_002C5AD0.x8;
        if (((t | t >> 24) & 0x40) && sel == n - 1) {
            sel = 0;
        } else {
            t = D_002C5AD0.x10;
            if ((t | t >> 24) & 0x40) {
                sel++;
                if (sel >= n) {
                    sel = n - 1;
                }
            }
        }
        help->x10 = D_0108F178[sel];
        D_00FB4A50 = D_00FB5958[sel];
        for (i = 0; i < n; i++) {
            if (i == sel) {
                icons[sel]->x4 = 1;
                func_00f74978(icons[sel], 8);
            } else {
                icons[i]->x4 = 0;
            }
        }
        if (sel != old) {
            func_0011d768(1);
        }
        if (D_002C5AD0.x8 & 0x2000) {
            D_0108F290 = 0;
            if (D_0108F170[sel] == 3 && func_00f68e50(3) < 2) {
                func_0011d768(4);
                func_0020be10(16);
                w = func_00f6b6a0(6, 8, 2, 4, 0, 15, 0x3A, 4, 0xA0, 0xD8, 0, 0, 0, 0, 0, 0, 0, 256, D_00FB4A70);
                func_0024e468(D_00FB4A70);
                while (!(D_002C5AD0.x8 & 0x6000)) {
                    func_0024e468(1);
                }
                if (!(D_002C5AD0.x8 & 0x2000)) {
                    func_0011d768(3);
                } else {
                    func_0011d768(2);
                }
                func_0020bda8(16);
                func_00f6b5d0(6, 0, D_00FB4A70);
                func_0024e468(D_00FB4A70);
                func_00f6ae60(w);
                continue;
            }
            func_00f6b5d0(4, 0, D_00FB4A70);
            func_0024e468(D_00FB4A70);
            func_00f6ade8(4);
            if (D_0108F1B8 > 0) {
                D_0108F1B8 = -1;
            }
            if ((u32)(D_0108F170[sel] - 2) >= 2) {
                func_00f6b6a0(0x13, 3, 0, 2, 0, 0, 0, 0, 0, D_00FB4B3C + 12, 0, D_00FB4B38, 2, D_00FB4CB8, D_00FB4CBC, D_00FB4CC0, D_00FB4CC4, 256, mode);
                func_00f6b6a0(0x13, 0, 2, 1, 0, 15, D_0108F168[sel], 7, D_00FB4B38, D_00FB4B3C, 0, D_00FB4B70, 0, 0, 0, 0, 0, 256, mode);
                func_00f6b6a0(0x13, 2, 0, 2, 0, D_00FB4C98, D_0108F178[sel], 0, D_00FB4C9C, D_00FB4CA0, 0, 0, 0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, func_00f47110() == 0 ? mode : 1);
            }
            func_0011d768(2);
            D_0108F2AC = D_0108F170[sel];
            func_0024e468(1);
            switch (D_0108F170[sel]) {
            case 0:
                D_0108F290 = 1;
                D_0108F2B0 = -999;
                D_0108F2B4 = 0;
                func_001f3dc0(lay);
                while (D_0108F2B0 < -1) {
                    func_0024e468(1);
                }
                func_00f6b5d0(0x13, 0, D_00FB4A70);
                func_0024e468(D_00FB4A70);
                func_00f6ade8(0x13);
                while (func_001f44a0(&D_00FB5930) != 0) {
                    func_0024e468(1);
                }
                if (D_0108F2B0 >= 0) {
                    func_001be320(D_0108F2B0);
                }
                v = func_001be278() + 1;
                D_00FB4A58 = v;
                D_00FB4A5C = v;
                goto next;
            case 1:
                D_0108F290 = 1;
                D_0108F2B0 = -999;
                D_0108F2B4 = 0;
                func_001f3dc0(lay);
                while (D_0108F2B0 < -1) {
                    func_0024e468(1);
                }
                if (D_0108F2B0 >= 0) {
                    D_0108F2B4 = 1;
                    D_0108F1E8 = 0.0f;
                    func_00f6b5d0(2, 0, D_00FB4A70);
                    func_00f6b5d0(0x13, 0, D_00FB4A70);
                    func_0020be10(16);
                    func_0024e468(D_00FB4A70);
                    func_00f6ade8(0x13);
                    while (func_001f44a0(&D_00FB5930) != 0) {
                        func_0024e468(1);
                    }
                    func_00f6ed80((u8 *)func_001bc4e0() + D_0108F2B0 * 0x60 + 0x94);
                    func_0024d1c8(&D_0108F298, D_0108F2B0, 0, 0);
                    while (func_0024d408() == 0) {
                        func_0024e468(1);
                    }
                    func_0020bda8(16);
                    D_0108F1E8 = 128.0f;
                    func_00f6b5d0(2, 256, D_00FB4A70);
                } else {
                    func_00f6b5d0(0x13, 0, D_00FB4A70);
                    func_0024e468(D_00FB4A70);
                    func_00f6ade8(0x13);
                    while (func_001f44a0(&D_00FB5930) != 0) {
                        func_0024e468(1);
                    }
                    D_0108F1E8 = 128.0f;
                }
                v = func_001be278() + 1;
                D_00FB4A58 = v;
                D_00FB4A5C = v;
                goto next;
            case 2:
                D_0108F2B4 = 1;
                func_00f6b5d0(2, 0, D_00FB4A70);
                func_00f6b5d0(0x13, 0, D_00FB4A70);
                D_0108F1E8 = 0.0f;
                func_0024e468(D_00FB4A70);
                while (func_001f44a0(&D_00FB5930) != 0) {
                    func_0024e468(1);
                }
                func_00f6ade8(0x13);
                D_0108F1E8 = 128.0f;
                D_0108F1CC = D_00FB4D44;
                D_0108F1D0 = D_00FB4D48;
                D_0108F1D4 = D_00FB4D54;
                D_00FB4A60 = D_00FB4AB4;
                func_001bd7f8(D_0108F2B0);
                func_00f73eb0();
                func_00f6b5d0(2, 256, D_00FB4A70);
                v = func_001be278() + 1;
                D_00FB4A58 = v;
                D_00FB4A5C = v;
                goto next;
            case 3:
                D_0108F2B4 = 1;
                func_00f6b5d0(2, 0, D_00FB4A70);
                func_00f6b5d0(0x13, 0, D_00FB4A70);
                D_0108F1E8 = 0.0f;
                func_0024e468(D_00FB4A70);
                while (func_001f44a0(&D_00FB5930) != 0) {
                    func_0024e468(1);
                }
                func_00f6ade8(0x13);
                D_0108F1E8 = 128.0f;
                D_0108F1CC = D_00FB4D44;
                D_0108F1D0 = D_00FB4D48;
                D_0108F1D4 = D_00FB4D54;
                D_00FB4A60 = D_00FB4AB4;
                func_00f71b68();
                D_0108F1CC = D_00FB4D3C;
                D_0108F1D0 = D_00FB4D40;
                D_0108F1D4 = D_00FB4D50;
                D_00FB4A60 = D_00FB4AB0;
                D_0108F1E8 = 128.0f;
                func_00f6b5d0(2, 256, D_00FB4A70);
                v = func_001be278() + 1;
                D_00FB4A58 = v;
                D_00FB4A5C = v;
                goto next;
            }
        }
        func_0024e468(1);
    }
    D_0108F1E8 = 0.0f;
    func_00f6b5d0(4, 0, D_00FB4A70);
    D_0108F2B4 = 1;
    func_0024e468(D_00FB4A70 + 1);
    func_00f6ade8(4);
    if (D_0108F1B8 > 0) {
        D_0108F1B8 = -1;
    }
    while (func_001f44a0(&D_00FB5930) != 0) {
        func_0024e468(1);
    }
    return;
next:;
    }
}
