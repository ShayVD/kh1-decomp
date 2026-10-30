/* gb.x func_00f49730: matched by hand. */
#include "ovl.h"

typedef struct { s32 x0, x4; u32 x8; u32 xC; u32 x10; } Pad;
typedef struct { u8 pad[12]; u16 xc; u16 xe; u16 x10; u16 x12; u8 pad2[10]; s16 x1e; } Lay;
typedef struct { u8 pad[208]; u16 hd0; u16 hd2; u8 pad2[4]; s16 hd8; s16 hda; } Obj;
typedef struct { u8 pad[6]; u8 b6; } Win;
extern Pad D_002C5AD0;
extern s32 D_00F702F0;
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
extern u16 D_00F705D8;
extern u16 D_00F705DC;
extern s32 D_00F705E8;
extern u16 D_00F705EC;
extern u16 D_00F705F0;
extern u16 D_00F705F4;
extern s32 D_00F70608;
extern s32 D_00F7060C;
extern s32 D_00F70610;
extern s32 D_00F70614;
extern s32 D_00F70618;
extern s32 D_00F7061C;
extern s32 D_00F70620;
extern s16 D_00F711E8[];
extern Lay D_00F71200;
extern Lay D_00F71230;
extern s16 D_00F71258[];
extern s32 D_00F829C8;
extern s32 D_00F829CC;
extern s32 D_00F829F8;
extern s32 D_00F82A94;
extern s32 D_00F82AF8;
extern s32 D_00F82AFC;
extern s32 D_00F82B00;
extern s16 D_00F82B28[];
void func_0011d768(s32);
s32 func_001ba3f0(s32);
s32 func_001efea8(s32);
Obj *func_001f31a8(Lay *, s32);
void func_001f3dc0(s32);
void func_0020bda8(s32);
void func_0020be10(s32);
void func_0024e468(s32);
s32 func_00f20018(void);
void func_00f43cf0(s32);
void func_00f444d8(s32, s32, s32);
void *func_00f445a8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_00f49730(void)
{
    s32 t, k, r, idx, n, cur, old, x;
    u32 b;
    Obj *o;
    Obj *o2;
    Win *w;

    D_00F82A94 = 0;
    t = D_00F702F0;
    func_00f445a8(9, 2, 0, 1, 0, D_00F70518, 76, 0, D_00F7051C, D_00F70520, 0, 0, 0, D_00F70524, D_00F70528, D_00F7052C, D_00F70530, 256, func_00f20018() == 0 ? t : 1);
    func_00f445a8(9, 0, 2, 1, 0, 15, 11, 4, D_00F704A4, D_00F704A8, 0, D_00F704AC, 0, 0, 0, 0, 0, 256, t);
    D_00F82AFC = 0;
    D_00F82B00 = 0;
    for (;;) {
        k = 0;
        if (func_001ba3f0(64) <= 0) k = func_001ba3f0(65) < 1;
        D_00F71200.x1e = 7 - k;
        D_00F71200.xc = D_00F705D8;
        D_00F71200.xe = D_00F705DC;
        D_00F82AF8 = 0;
        D_00F829C8 = 0;
        o = func_001f31a8(&D_00F71200, 1);
        o->hd0 = D_00F82AFC;
        o->hd2 = D_00F82B00;
        while (D_00F829C8 == 0) func_0024e468(1);
        r = D_00F82AF8;
        if (r == -1) {
            func_00f444d8(9, 0, D_00F702F0);
            func_0024e468(D_00F702F0);
            func_00f43cf0(9);
            if (D_00F829F8 > 0) D_00F829F8 = -1;
            break;
        }
        cur = 0;
        D_00F71230.xc = D_00F705E8;
        D_00F71230.xe = D_00F705EC;
        D_00F71230.x10 = D_00F705F0;
        D_00F71230.x12 = D_00F705F4;
        D_00F829C8 = 0;
        o2 = func_001f31a8(&D_00F71230, 1);
        func_001f3dc0(D_00F829CC);
        idx = D_00F82B28[D_00F82AF8];
        func_00f445a8(8, 3, 0, 2, 0, 0, 0, 0, 0, D_00F705A4 + 12, 0, D_00F705A0, 2, D_00F70538, D_00F7053C, D_00F70540, D_00F70544, 256, t);
        x = D_00F705A0 + D_00F70620;
        func_00f445a8(8, 3, 0, 2, 0, 0, 0, 0, x, D_00F705A4 + 12, 0, D_00F705E8 - x, 2, D_00F70538, D_00F7053C, D_00F70540, D_00F70544, 256, t);
        func_00f445a8(8, 0, 2, 1, 0, 15, D_00F711E8[idx], 7, D_00F705A0, D_00F705A4, 0, D_00F70620, 0, 0, 0, 0, 0, 256, t);
        w = func_00f445a8(8, 12, 0, 2, 0, 15, D_00F71258[idx], 0, D_00F70608, D_00F7060C, 0, 0, 0, D_00F70610, D_00F70614, D_00F70618, D_00F7061C, 256, t);
        w->b6 = 0;
        func_0020be10(16);
        for (; n = func_001efea8(D_00F71258[idx]), old = cur, !(D_002C5AD0.x8 & 0x4000);) {
        if (n) {
            b = D_002C5AD0.x10 | D_002C5AD0.x10 >> 24;
            if (b & 0x20) {
                cur++;
                if (cur >= n) cur = n - 1;
            }
            if (b & 0x80) {
                cur--;
                if (cur < 0) cur = 0;
            }
            w->b6 = cur;
        }
        if (old != cur) func_0011d768(1);
        o2->hd8 = n;
        o2->hda = cur << 4;
        func_0024e468(1);
        }
        func_0011d768(3);
        func_0020bda8(16);
        func_00f444d8(8, 0, D_00F702F0);
        D_00F829C8 = 1;
        func_0024e468(D_00F702F0);
        func_00f43cf0(8);
    }
    D_00F82A94 = 1;
    if (D_00F829F8 > 0) D_00F829F8 = -1;
}
