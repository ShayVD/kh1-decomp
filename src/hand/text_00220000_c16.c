#include "common.h"
#include "data/bss_0064.h"
typedef struct O98 {
    u8 pad[0xc];
    struct O98 *xc;
    s32 x10;
    u8 pad14[0x24 - 0x14];
    union { s32 i; u16 h; } x24;
    u8 p0[0x8c - 0x28];
    s32 x8c;
    s32 x90;
    u8 p1[0xa0 - 0x94];
    f32 xa0;
    u8 p2[0xb0 - 0xa4];
    s32 xb0;
    s32 xb4;
    u8 p3[0xba - 0xb8];
    s16 xba;
    s16 xbc;
    s16 xbe;
    s16 xc0;
    s16 xc2;
    s16 xc4;
    s16 xc6;
    s16 xc8;
    s16 xca;
    s16 xcc;
    s16 xce;
    s16 xd0;
    s16 xd2;
    u8 p6[0xd8 - 0xd4];
    s16 xd8;
    s16 xda;
} O98;
#include "data/pieces/D_00425BC8.h"
void func_0011d768(s32);
s32 func_001f42b8(void);
s32 func_001fe570(void *);
void func_00201440(void *, s32, s32, s32, s32, s32, s32, void *, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
#include "data/types/text_00220000_c16.h"
s32 func_001fd518(void *);
void func_001fd858(void *);
void func_0020bd18(void *, s32);
void func_0020be10(s32);

extern s32 D_003F7778;
extern f32 D_002BBDFC;
extern s32 D_006469D0;
extern s32 D_006469D4;
f32 D_006469D8 ALIGNED(8);
extern s32 D_006469DC;
f32 D_006469E0 ALIGNED(16);
extern s32 D_006469E4;
f32 D_006469E8 ALIGNED(8);
extern s32 D_006469EC;
f32 D_006469F0 ALIGNED(16);
extern s32 D_006469F4;
f32 D_006469F8 ALIGNED(8);
extern char D_003F76C0[][20];
extern s32 D_003F7710[];
void func_001fd648(void *, s32);
void func_001f3840(void *);
f32 sinf(f32);

void func_0022e460(O98 *a0) {
    s32 v[2];
    s32 base, cur, half, sel, c;

    base = a0->x90;
    cur = base;
    half = base / 2;
    if (func_001f42b8()) {
        switch (D_006469E4) {
        case 0:
            if (D_00425BC8->x8 & 0x4000) {
                D_003F7778 = 0;
                func_001fd648(a0, 0);
                func_0011d768(3);
            } else {
                func_001fd858(a0);
                func_0020bd18(a0, 8);
                D_003F7778 = func_001fd518(a0);
                if (func_001fe570(a0)) {
                    D_006469E4++;
                }
            }
            break;
        case 1:
            D_006469E8 = 0.0f;
            D_006469E4 = 2;

        case 2:
            D_006469E8 += D_002BBDFC;
            if (D_006469E8 <= 8.0f) {
                cur = (f32)base + (f32)(255 - base) * sinf(D_006469E8 * 3.1415928f * 0.125f);
            } else {
                cur = base;
                func_001f3840(a0);
                func_0020be10(16);
            }
            break;
        }
    }
    switch (a0->x8c) {
    case 2:
        switch (D_006469EC) {
        case 0:
            D_006469EC = 1;
            D_006469F0 = 40.0f;
        case 1:
            D_006469F0 -= D_002BBDFC;
            if (!(D_006469F0 > 0.0f)) {
                D_006469EC++;
            }
            break;        case 2:
            break;
        }
        break;
    case 5:
        switch (D_006469F4) {
        case 0:
            D_006469F4 = 1;
            D_006469F8 = 40.0f;
        case 1:
            D_006469F8 -= D_002BBDFC;
            if (!(D_006469F8 > 0.0f)) {
                D_006469F4++;
            }
            break;        case 2:
            break;
        }
        break;
    }
    sel = func_001fd518(a0);
    v[sel] = cur;
    if (D_006469D0 != sel) {
        D_006469D4 = 0;
        D_006469DC = 0;
    }
    D_006469D0 = sel;
    switch (D_006469D4) {
    case 0:
        D_006469D4 = 1;
        D_006469D8 = 10.0f;
    case 1:
        D_006469D8 -= D_002BBDFC;
        if (D_006469D8 > 0.0f) {
            v[sel ^ 1] = (f32)half + (f32)(cur - half) * D_006469D8 / 10.0f;
        } else {
            v[sel ^ 1] = half;
            D_006469D4++;
        }
        break;
    case 2:
        v[sel ^ 1] = half;
        break;
    }
    switch (D_006469DC) {
    case 0:
        D_006469DC = 1;
        D_006469E0 = 8.0f;
    case 1:
        D_006469D8 -= D_002BBDFC;
        if (D_006469D8 > 0.0f) {
            v[sel] = (f32)cur + (f32)(half - cur) * D_006469D8 * 0.125f;
        } else {
            v[sel] = cur;
            D_006469DC++;
        }
        break;
    case 2:
        v[sel] = cur;
        break;
    }
    c = D_003F7710[sel];
    a0->x90 = v[0];

    func_002066b0(a0, 0, 176, 174, c, 0x330096ff);
    func_00201440(a0, 2, 2, 173, 164, 166, 256, D_003F76C0[sel], 99);
    func_002066b0(a0, 339, 176, 173, 0x330096ff, c);
    c = D_003F7710[sel + 2];
    a0->x90 = v[1];

    func_002066b0(a0, 0, 206, 174, c, 0x33ffc12c);
    func_00201440(a0, 2, 2, 173, 194, 166, 256, D_003F76C0[sel + 2], 100);
    func_002066b0(a0, 339, 206, 173, 0x33ffc12c, c);
    a0->x90 = base;
}
#include "data/bss_0064_typed.h"
#include "data/data_003F.h"
#include "data/pieces/D_002BBDFC.h"
