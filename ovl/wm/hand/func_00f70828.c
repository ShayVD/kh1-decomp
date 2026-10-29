/* wm.x func_00f70828: matched by hand. */
#include "ovl.h"

typedef struct { s32 x0, x4; u32 x8; u32 xC; u32 x10; } Pad;
typedef struct { u8 pad[12]; u16 xc; u16 xe; u16 x10; u16 x12; u8 pad2[10]; s16 x1e; } Lay;
typedef struct { u8 pad[208]; u16 hd0; u16 hd2; u8 pad2[4]; s16 hd8; s16 hda; } Obj;
typedef struct { u8 pad[6]; u8 b6; } Win;
extern Pad D_002C5AD0;
extern s32 D_00FB4A70;
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
extern u16 D_00FB4D58;
extern u16 D_00FB4D5C;
extern s32 D_00FB4D68;
extern u16 D_00FB4D6C;
extern u16 D_00FB4D70;
extern u16 D_00FB4D74;
extern s32 D_00FB4D88;
extern s32 D_00FB4D8C;
extern s32 D_00FB4D90;
extern s32 D_00FB4D94;
extern s32 D_00FB4D98;
extern s32 D_00FB4D9C;
extern s32 D_00FB4DA0;
extern s16 D_00FB5968[];
extern Lay D_00FB5980;
extern Lay D_00FB59B0;
extern s16 D_00FB59D8[];
extern s32 D_0108F188;
extern s32 D_0108F18C;
extern s32 D_0108F1B8;
extern s32 D_0108F254;
extern s32 D_0108F2B8;
extern s32 D_0108F2BC;
extern s32 D_0108F2C0;
extern s16 D_0108F2E8[];
void func_0011d768(s32);
s32 func_001ba3f0(s32);
s32 func_001efea8(s32);
Obj *func_001f31a8(Lay *, s32);
void func_001f3dc0(s32);
void func_0020bda8(s32);
void func_0020be10(s32);
void func_0024e468(s32);
s32 func_00f47110(void);
void func_00f6ade8(s32);
void func_00f6b5d0(s32, s32, s32);
void *func_00f6b6a0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_00f70828(void)
{
    s32 t, k, r, idx, n, cur, old, x;
    u32 b;
    Obj *o;
    Obj *o2;
    Win *w;

    D_0108F254 = 0;
    t = D_00FB4A70;
    func_00f6b6a0(9, 2, 0, 1, 0, D_00FB4C98, 76, 0, D_00FB4C9C, D_00FB4CA0, 0, 0, 0, D_00FB4CA4, D_00FB4CA8, D_00FB4CAC, D_00FB4CB0, 256, func_00f47110() == 0 ? t : 1);
    func_00f6b6a0(9, 0, 2, 1, 0, 15, 11, 4, D_00FB4C24, D_00FB4C28, 0, D_00FB4C2C, 0, 0, 0, 0, 0, 256, t);
    D_0108F2BC = 0;
    D_0108F2C0 = 0;
    for (;;) {
        k = 0;
        if (func_001ba3f0(64) <= 0) k = func_001ba3f0(65) < 1;
        D_00FB5980.x1e = 7 - k;
        D_00FB5980.xc = D_00FB4D58;
        D_00FB5980.xe = D_00FB4D5C;
        D_0108F2B8 = 0;
        D_0108F188 = 0;
        o = func_001f31a8(&D_00FB5980, 1);
        o->hd0 = D_0108F2BC;
        o->hd2 = D_0108F2C0;
        while (D_0108F188 == 0) func_0024e468(1);
        r = D_0108F2B8;
        if (r == -1) {
            func_00f6b5d0(9, 0, D_00FB4A70);
            func_0024e468(D_00FB4A70);
            func_00f6ade8(9);
            if (D_0108F1B8 > 0) D_0108F1B8 = -1;
            break;
        }
        cur = 0;
        D_00FB59B0.xc = D_00FB4D68;
        D_00FB59B0.xe = D_00FB4D6C;
        D_00FB59B0.x10 = D_00FB4D70;
        D_00FB59B0.x12 = D_00FB4D74;
        D_0108F188 = 0;
        o2 = func_001f31a8(&D_00FB59B0, 1);
        func_001f3dc0(D_0108F18C);
        idx = D_0108F2E8[D_0108F2B8];
        func_00f6b6a0(8, 3, 0, 2, 0, 0, 0, 0, 0, D_00FB4D24 + 12, 0, D_00FB4D20, 2, D_00FB4CB8, D_00FB4CBC, D_00FB4CC0, D_00FB4CC4, 256, t);
        x = D_00FB4D20 + D_00FB4DA0;
        func_00f6b6a0(8, 3, 0, 2, 0, 0, 0, 0, x, D_00FB4D24 + 12, 0, D_00FB4D68 - x, 2, D_00FB4CB8, D_00FB4CBC, D_00FB4CC0, D_00FB4CC4, 256, t);
        func_00f6b6a0(8, 0, 2, 1, 0, 15, D_00FB5968[idx], 7, D_00FB4D20, D_00FB4D24, 0, D_00FB4DA0, 0, 0, 0, 0, 0, 256, t);
        w = func_00f6b6a0(8, 12, 0, 2, 0, 15, D_00FB59D8[idx], 0, D_00FB4D88, D_00FB4D8C, 0, 0, 0, D_00FB4D90, D_00FB4D94, D_00FB4D98, D_00FB4D9C, 256, t);
        w->b6 = 0;
        func_0020be10(16);
        for (; n = func_001efea8(D_00FB59D8[idx]), old = cur, !(D_002C5AD0.x8 & 0x4000);) {
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
        func_00f6b5d0(8, 0, D_00FB4A70);
        D_0108F188 = 1;
        func_0024e468(D_00FB4A70);
        func_00f6ade8(8);
    }
    D_0108F254 = 1;
    if (D_0108F1B8 > 0) D_0108F1B8 = -1;
}
