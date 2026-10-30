/* Round 46 wwm2: score 713 -> 709, func_0020be10 declared s32. Earlier header below. */
/* Round 41 wwm2: score 837 -> 713, port.py of the wm twin func_00f6f2a8 draft (r41/twins.py pairs wm and gb drafts with the same target mnemonics). Earlier header below. */
/* score 837: gb port of wm f6f2a8 via portmap2; same remaining diffs. Round 25 wwm2. */
typedef struct { u8 pad[8]; u32 x8; u32 x10; } Pad;
typedef struct { u8 pad[16]; s32 x10; } Win;
typedef struct { u8 pad[12]; s16 xc; s16 xe; u8 pad10[14]; s16 x1e; } Lay;
typedef struct { u8 x0; u8 x1; u8 x2; u8 x3; u8 x4; u8 pad5[3]; s16 x8; u8 padA[2]; s16 xc; u8 padE[2]; s32 x10; f32 x14; f32 x18; f32 x1c; f32 x20; u8 pad24[8]; f32 x2c; f32 x30; } Ic;
typedef struct { u8 pad[8]; u8 x8; u8 pad9[87]; } Item;
extern Pad D_002C5AD0;
extern s32 D_00F702D0;
extern s32 D_00F702D8;
extern s32 D_00F702DC;
extern f32 D_00F702E0;
extern s32 D_00F702F0;
extern f32 D_00F70330;
extern f32 D_00F70334;
extern s32 D_00F703B8;
extern s32 D_00F703BC;
extern s32 D_00F703EC;
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
extern s32 D_00F705A0;
extern s32 D_00F705A4;
extern u16 D_00F705A8;
extern u16 D_00F705AC;
extern s32 D_00F705BC;
extern s32 D_00F705C0;
extern s32 D_00F705C4;
extern s32 D_00F705C8;
extern s32 D_00F705D0;
extern s32 D_00F705D4;
extern Lay D_00F711B0;
extern s16 D_00F711D8[];
extern u16 D_00F711E0[];
extern s16 D_00F829A8[];
extern s8 D_00F829B0[];
extern s16 D_00F829B8[];
extern s32 D_00F829CC;
extern s32 D_00F829F8;
extern s32 D_00F82A0C;
extern s32 D_00F82A10;
extern s32 D_00F82A14;
extern f32 D_00F82A28;
extern s32 D_00F82AD0;
extern s32 D_00F82AD8;
extern s32 D_00F82AEC;
extern s32 D_00F82AF0;
extern s32 D_00F82AF4;
void func_0011d768(s32);
Item *func_001bc4e0(void);
s32 func_001bc510(void); CONTEXT_ONLY s32 func_001bc510() { return 0; }
void func_001bd7f8(s32);
s32 func_001be278(void);
void func_001be320(s32);
s32 func_001f31a8(Lay *, s32);
void func_001f3dc0(s32);
s32 func_001f44a0(Lay *);
void func_0020bda8(s32);
s32 func_0020be10(s32);
void func_0024d1c8(s32 *, s32, s32, s32);
s32 func_0024d408(void);
void func_0024e468(s32);
s32 func_00f20018(void);
s32 func_00f41d58(s32);
Ic *func_00f43388(void); CONTEXT_ONLY Ic * func_00f43388() { return 0; }
void func_00f43cf0(s32);
void func_00f43d68(Win *);
void func_00f444b8(Ic *, f32, f32);
void func_00f444d8(s32, s32, s32);
Win *func_00f445a8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00f45e80(void); CONTEXT_ONLY s32 func_00f45e80() { return 0; }
void func_00f47c88(void *);
void func_00f4aa70(void);
void func_00f4cdb8(void); CONTEXT_ONLY void func_00f4cdb8() {}
void func_00f4d880(Ic *, s32);

#define MAKE(n, nm) \
    pp = &icons[n]; \
    *pp = func_00f43388(); \
    (*pp)->x0 = 4; \
    (*pp)->x1 = 0; \
    (*pp)->x2 = 2; \
    (*pp)->x3 = 0; \
    (*pp)->xc = 1; \
    (*pp)->x10 = nm; \
    D_00F829A8[n] = nm; \
    (*pp)->x20 = (*pp)->x18 = (f32)x; \
    (*pp)->x2c = (*pp)->x30 = 0.0f; \
    (*pp)->x1c = (*pp)->x14 = (f32)D_00F705A0; \
    (*pp)->x8 = D_00F703F0; \
    if (n == sel) { \
        (*pp)->x4 = 1; \
        func_00f4d880(*pp, 8); \
    } else { \
        (*pp)->x4 = 0; \
    } \
    D_00F829B0[n] = n; \
    D_00F829B8[n] = D_00F711E0[n];

void func_00f481b0(void)
{
    s32 v;
    Item *items;
    u32 t;
    Ic **pp;
    Win *w;
    Ic *icons[4];
    s32 sel, old, n, i, k, x, cnt;
    s32 lay;
    s32 mode;
    Win *help;

    sel = 0;
    mode = D_00F702F0;
    for (;;) {
    items = func_001bc4e0();
    k = func_001bc510() - 1;
    cnt = 0;
    for (i = 0; i < k; i++) {
        if (items[i + 1].x8 == 0) {
            cnt++;
        }
    }
    D_00F82AF0 = -999;
    D_00F82AD0 = 0;
    D_00F82AF4 = 0;
    D_00F711B0.x1e = cnt;
    D_00F711B0.xc = D_00F705A8;
    D_00F711B0.xe = D_00F705AC;
    lay = func_001f31a8(&D_00F711B0, 1);
    func_001f3dc0(D_00F829CC);
    func_00f445a8(4, 0, 2, 1, 0, 15, 3, 4, D_00F704A4, D_00F704A8, 0, D_00F704AC, 0, 0, 0, 0, 0, 256, mode);
    x = D_00F705A4;
    MAKE(0, 31)
    x += D_00F703EC;
    MAKE(1, 35)
    x += D_00F703EC;
    MAKE(2, 5)
    n = 3;
    x += D_00F703EC;
    if (func_00f45e80() >= 3) {
        MAKE(n, 7)
        n++;
    }
    help = func_00f445a8(4, 2, 0, 1, 0, D_00F70518, D_00F829B8[sel], 0, D_00F7051C, D_00F70520, 0, 0, 0, D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, func_00f20018() == 0 ? mode : 1);
    D_00F82AEC = D_00F829B0[sel];
    D_00F82A28 = 128.0f;
    for (i = 0; i < n; i++) {
        func_00f444b8(icons[i], 256.0f, (f32)D_00F702F0);
        func_0024e468(2);
    }
    for (;;) {
        if (D_002C5AD0.x8 & 0x4000) {
            func_0011d768(3);
            break;
        }
        t = D_002C5AD0.x8;
        old = sel;
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
        help->x10 = D_00F829B8[sel];
        D_00F702D0 = D_00F711D8[sel];
        for (i = 0; i < n; i++) {
            if (i == sel) {
                icons[sel]->x4 = 1;
                func_00f4d880(icons[sel], 8);
            } else {
                icons[i]->x4 = 0;
            }
        }
        if (sel != old) {
            func_0011d768(1);
        }
        if (D_002C5AD0.x8 & 0x2000) {
            D_00F82AD0 = 0;
            if (D_00F829B0[sel] == 3 && func_00f41d58(3) < 2) {
                func_0011d768(4);
                func_0020be10(16);
                w = func_00f445a8(6, 8, 2, 4, 0, 15, 0x3A, 4, 0xA0, 0xD8, 0, 0, 0, 0, 0, 0, 0, 256, D_00F702F0);
                func_0024e468(D_00F702F0);
                while (!(D_002C5AD0.x8 & 0x6000)) {
                    func_0024e468(1);
                }
                if (!(D_002C5AD0.x8 & 0x2000)) {
                    func_0011d768(3);
                } else {
                    func_0011d768(2);
                }
                func_0020bda8(16);
                func_00f444d8(6, 0, D_00F702F0);
                func_0024e468(D_00F702F0);
                func_00f43d68(w);
                continue;
            }
            func_00f444d8(4, 0, D_00F702F0);
            func_0024e468(D_00F702F0);
            func_00f43cf0(4);
            if (D_00F829F8 > 0) {
                D_00F829F8 = -1;
            }
            if ((u32)(D_00F829B0[sel] - 2) >= 2) {
                func_00f445a8(0x13, 3, 0, 2, 0, 0, 0, 0, 0, D_00F703BC + 12, 0, D_00F703B8, 2, D_00F70538, D_00F7053C, D_00F70540, D_00F70544, 256, mode);
                func_00f445a8(0x13, 0, 2, 1, 0, 15, D_00F829A8[sel], 7, D_00F703B8, D_00F703BC, 0, D_00F703F0, 0, 0, 0, 0, 0, 256, mode);
                func_00f445a8(0x13, 2, 0, 2, 0, D_00F70518, D_00F829B8[sel], 0, D_00F7051C, D_00F70520, 0, 0, 0, D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, func_00f20018() == 0 ? mode : 1);
            }
            func_0011d768(2);
            D_00F82AEC = D_00F829B0[sel];
            func_0024e468(1);
            switch (D_00F829B0[sel]) {
            case 0:
                D_00F82AD0 = 1;
                D_00F82AF4 = 0;
                D_00F82AF0 = -999;
                func_001f3dc0(lay);
                while (D_00F82AF0 < -1) {
                    func_0024e468(1);
                }
                func_00f444d8(0x13, 0, D_00F702F0);
                func_0024e468(D_00F702F0);
                func_00f43cf0(0x13);
                while (func_001f44a0(&D_00F711B0) != 0) {
                    func_0024e468(1);
                }
                if (D_00F82AF0 >= 0) {
                    func_001be320(D_00F82AF0);
                }
                v = func_001be278() + 1;
                D_00F702D8 = v;
                D_00F702DC = v;
                goto next;
            case 1:
                D_00F82AD0 = 1;
                D_00F82AF4 = 0;
                D_00F82AF0 = -999;
                func_001f3dc0(lay);
                while (D_00F82AF0 < -1) {
                    func_0024e468(1);
                }
                if (D_00F82AF0 >= 0) {
                    D_00F82A28 = 0.0f;
                    D_00F82AF4 = 1;
                    func_00f444d8(2, 0, D_00F702F0);
                    func_00f444d8(0x13, 0, D_00F702F0);
                    func_0020be10(16);
                    func_0024e468(D_00F702F0);
                    func_00f43cf0(0x13);
                    while (func_001f44a0(&D_00F711B0) != 0) {
                        func_0024e468(1);
                    }
                    func_00f47c88((u8 *)func_001bc4e0() + D_00F82AF0 * 0x60 + 0x94);
                    func_0024d1c8(&D_00F82AD8, D_00F82AF0, 0, 0);
                    while (func_0024d408() == 0) {
                        func_0024e468(1);
                    }
                    func_0020bda8(16);
                    D_00F82A28 = 128.0f;
                    func_00f444d8(2, 256, D_00F702F0);
                } else {
                    func_00f444d8(0x13, 0, D_00F702F0);
                    func_0024e468(D_00F702F0);
                    func_00f43cf0(0x13);
                    while (func_001f44a0(&D_00F711B0) != 0) {
                        func_0024e468(1);
                    }
                    D_00F82A28 = 128.0f;
                }
                v = func_001be278() + 1;
                D_00F702D8 = v;
                D_00F702DC = v;
                goto next;
            case 2:
                D_00F82AF4 = 1;
                func_00f444d8(2, 0, D_00F702F0);
                func_00f444d8(0x13, 0, D_00F702F0);
                D_00F82A28 = 0.0f;
                func_0024e468(D_00F702F0);
                while (func_001f44a0(&D_00F711B0) != 0) {
                    func_0024e468(1);
                }
                func_00f43cf0(0x13);
                D_00F82A28 = 128.0f;
                D_00F82A0C = D_00F705C4;
                D_00F82A10 = D_00F705C8;
                D_00F82A14 = D_00F705D4;
                D_00F702E0 = D_00F70334;
                func_001bd7f8(D_00F82AF0);
                func_00f4cdb8();
                func_00f444d8(2, 256, D_00F702F0);
                v = func_001be278() + 1;
                D_00F702D8 = v;
                D_00F702DC = v;
                goto next;
            case 3:
                D_00F82AF4 = 1;
                func_00f444d8(2, 0, D_00F702F0);
                func_00f444d8(0x13, 0, D_00F702F0);
                D_00F82A28 = 0.0f;
                func_0024e468(D_00F702F0);
                while (func_001f44a0(&D_00F711B0) != 0) {
                    func_0024e468(1);
                }
                func_00f43cf0(0x13);
                D_00F82A28 = 128.0f;
                D_00F82A0C = D_00F705C4;
                D_00F82A10 = D_00F705C8;
                D_00F82A14 = D_00F705D4;
                D_00F702E0 = D_00F70334;
                func_00f4aa70();
                D_00F82A0C = D_00F705BC;
                D_00F82A10 = D_00F705C0;
                D_00F82A14 = D_00F705D0;
                D_00F702E0 = D_00F70330;
                D_00F82A28 = 128.0f;
                func_00f444d8(2, 256, D_00F702F0);
                v = func_001be278() + 1;
                D_00F702DC = v;
                D_00F702D8 = v;
                goto next;
            }
        }
        func_0024e468(1);
    }
    D_00F82A28 = 0.0f;
    func_00f444d8(4, 0, D_00F702F0);
    D_00F82AF4 = 1;
    func_0024e468(D_00F702F0 + 1);
    func_00f43cf0(4);
    if (D_00F829F8 > 0) {
        D_00F829F8 = -1;
    }
    while (func_001f44a0(&D_00F711B0) != 0) {
        func_0024e468(1);
    }
    return;
next:;
    }
}
