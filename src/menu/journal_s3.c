/* Page 5's section 3 (D_003F5A00[3]; docs/modules.md "Session 42"),
 * 0x002205e0-0x002210f8.  Opener func_002210b0 keeps the section's window in
 * D_00643428; set up func_002210c0 (counts, D_003F5C24 = "not empty"), reset
 * func_002210f0 (empty).
 *
 * func_002205e0 counts the 99 entries func_001eb318(i) has (D_00643430[i],
 * D_0064342C in all, D_003F5C3C once all 99 are there) by group
 * D_003F61E0[i / 3] (nine groups: D_00643610 found, D_00643638 in all,
 * D_006435E8 missing; D_006435C0 lists the D_006435BC groups with any).
 * func_002208b8 lists the groups with their missing counts (message 17),
 * func_00220c28 (journal_s3.nofill.c) draws the 99 as a grid of numbered
 * boxes.  Group names are messages 8 + group (func_002207f0).  Not proved by
 * a boot; 99 numbered collectibles in nine groups. */
#include "common.h"
#include "platform/pad.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003E8E08.h"
#include "data/pieces/D_003E90A0.h"
#include "data/pieces/D_003F61E0.h"
#include "menu/journal.h"

extern JsWin *D_00643428; /* src/data/bss_0064.c: s32 D_00643428 */
extern s32 D_003F5C24;
extern s32 D_003F5C3C;
extern u8 D_003F6270[], D_003F62A0[];
extern u8 D_003F62D0[], D_003F6300[];
s32 D_006435E8[0xa] ALIGNED(8);
s32 D_00643610[0xa] ALIGNED(16);
s32 D_00643638[0xa] ALIGNED(8);
s32 D_006435BC ALIGNED(4);
s32 D_006435C0[0xa] ALIGNED(16);

void func_0011d768(s32);
s32 func_001eb318(s32);
void *func_001f31a8(void *, s32);
void func_001f3758(void *);
void func_001f3e48(void *, void *);
s32 func_001f42b8(void *);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
void func_002072e0(s32);
void func_0021af38(void *);
s32 func_0021b800(s32);
void func_0021b820(void);
void func_0021c9a0(void *, s32, s32);
void func_0021cb00(void *, s32, s32, s32, s32);
void func_0021cb88(void *, s32, s32, s32, s32);
void func_0021ccd0(void *, s32);

void func_002205e0(void) {
    s32 i;
    for (i = 0; i < 9; i++) {
        D_006435E8[i] = 0;
        D_00643610[i] = 0;
        D_00643638[i] = 0;
    }
    D_0064342C = 0;
    for (i = 0; i < 99; i++) {
        if ((D_00643430[i] = func_001eb318(i))) {
            D_00643610[D_003F61E0[i / 3]]++;
            D_0064342C++;
        }
    }
    D_006435BC = 0;
    for (i = 0; i < 9; i++) {
        if (D_00643610[i]) {
            D_006435C0[D_006435BC] = i;
            D_006435BC++;
        }
    }
    for (i = 0; i < 33; i++) D_00643638[D_003F61E0[i]] += 3;
    for (i = 0; i < 9; i++) D_006435E8[i] = D_00643638[i] - D_00643610[i];
    D_003F5C3C = D_0064342C == 99;
}

s32 func_002207f0(s32 i) {
    return func_0021b800(i + 8);
}

s32 func_00220808(s32 i) {
    return func_0021b800(D_003F61E0[i / 3] + 8);
}

void func_00220848(JsWin *arg0) {
    if ((func_001f42b8(arg0) != 0) && (D_00425BC8->x8 & PAD_CROSS)) {
        func_001f3758(D_00643428->x10);
        func_0011d768(3);
    }
    func_0021b820();
    func_0021ccd0(arg0, 3);
    func_0021af38(arg0);
}

void func_002208b8(JsWin *a) {
    s32 i, y;
    y = 86;
    func_0021b820();
    func_0021c9a0(a, 16, 72);
    func_0021cb00(a, 32, 108, 9, 30);
    func_0021cb00(a, 280, 108, 9, 30);
    for (i = 0; i < D_006435BC; i++) {
        func_001f94f0(a, 0, 280, y, func_002207f0(D_006435C0[i]), 15, 0x80461E00);
        (*(s32 *)&D_003E8E08) = D_006435E8[D_006435C0[i]];
        func_001f94f0(a, 0, 465, y, func_0021b800(17), 15, 0x80461E00);
        y += 30;
    }
    if (D_006435BC < 9) {
        func_001f94f0(a, 0, 280, y, func_0021b800(80), 15, 0x80461E00);
        (*(s32 *)&D_003E8E08) = 99;
        for (i = 0; i < D_006435BC; i++) (*(s32 *)&D_003E8E08) -= D_00643638[D_006435C0[i]];
        func_001f94f0(a, 0, 465, y, func_0021b800(17), 15, 0x80461E00);
    }
}

void func_00220af0(JsWin *a0) {
    JsWin *b[2];
    if (func_001f42b8(a0) != 0) {
        s32 fl = D_00425BC8->x8;
        if (fl & PAD_CROSS) {
            func_001f3758(D_00643428);
            func_0011d768(3);
        } else if (fl & PAD_TRIANGLE) {
            func_0011d768(2);
            func_001f3758(D_00643428->x10);
            b[0] = func_001f31a8(D_003F62A0, 50);
            if (b[0] != 0) {
                func_001f3e48(b[0], a0);
                b[0]->xa0 = D_003E90A0.x64;
                b[1] = func_001f31a8(D_003F6270, 50);
                if (b[1] != 0) {
                    func_001f3e48(b[1], b[0]);
                    b[1]->xa0 = b[0]->xa0 + D_003E90A0.x64;
                }
            }
        }
    }
    func_0021b820();
    func_0021cb88(a0, 176, 8, 320, 7);
}

void func_00220fe8(JsWin *a0) {
    JsWin *a[2];
    a[0] = func_001f31a8(D_003F6300, 50);
    if (a[0]) {
        func_001f3e48(a[0], a0);
        a[1] = func_001f31a8(D_003F62D0, 50);
        if (a[1]) func_001f3e48(a[1], a[0]);
    }
}

void func_00221058(JsWin *arg0) {
    if (func_001f42b8(arg0) != 0) {
        func_00220fe8(arg0);
    }
}

void func_00221098(void) {
    func_002072e0(3);
}

void func_002210b0(JsWin *a) {
    D_00643428 = a;
}

void func_002210c0(void) {
    func_002205e0();
    D_003F5C24 = D_0064342C != 0;
}

void func_002210f0(void) {

}
