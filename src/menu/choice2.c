/* A two-row choice screen (docs/modules.md "Session 43"), 0x0022e458-0x0022ebe8.
 * func_0022eb00 opens it by itself (D_003F7774 = 1, the task func_0022eab8):
 * a backdrop D_003F7750 (func_0022ea88) and the list D_003F7720
 * (func_0022e460).  The answer is D_003F7778 (0 when cancelled); on a choice
 * the chosen row brightens along a sine (D_006469E8, 8 frames) and the
 * window closes.  Each row is drawn by func_00201440 from the names
 * D_003F76C0[row + 2 * highlighted] with the colours D_003F7710, the cursor
 * row fading in (D_006469D8, 10 frames) and the other out; D_006469EC /
 * D_006469F4 count 40 frames while the window is in states 2 and 5.  What
 * it asks is not known; not proved by a boot. */
#include "common.h"
#include "platform/pad.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_00425BC8.h"
#include "text/textwin.h"

extern s32 D_003F7774;
extern s32 D_003F7778;
extern char D_003F76C0[][20];
extern s32 D_003F7710[];
extern u8 D_003F7720[], D_003F7750[];
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

void func_0011d768(s32);
s16 *func_0011ef10(s32, void *);
void func_001efb78(s32);
void func_001f3110(void);
void *func_001f31a8(void *, s32);
void func_001f3840(void *);
void func_001f3e20(void *, void *);
void func_001f3e90(void *, void *);
s32 func_001f40c8(void);
s32 func_001f42b8(void *);
void func_001f82b0(void);
s32 func_001fd518(void *);
void func_001fd648(void *, s32);
void func_001fd858(void *);
s32 func_001fe570(void *);
void func_00201440(void *, s32, s32, s32, s32, s32, s32, void *, s32);
s32 func_00205938(void *, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
void func_0020b968(void);
void func_0020b998(void);
void func_0020bb90(s32, s32);
void func_0020bd18(void *, s32);
void func_0020bda8(s32);
void func_0020be10(s32);
f32 sinf(f32);

void func_0022e458(void) {

}

void func_0022e460(TextWin *a0) {
    s32 v[2];
    s32 base, cur, half, sel, c;

    base = a0->x90;
    cur = base;
    half = base / 2;
    if (func_001f42b8(a0)) {
        switch (D_006469E4) {
        case 0:
            if (D_00425BC8->x8 & PAD_CROSS) {
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
    switch (a0->state) {
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
            break;
        case 2:
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
            break;
        case 2:
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

s32 func_0022ea88(TextWin *arg0) {
    return func_00205938(arg0, 0x40000000);
}

void func_0022eaa0(void) {
    func_001efb78(0);
}

s32 func_0022eab8(void) {
    if (func_001f40c8() != 0) {
        func_001f82b0();
        func_0020b998();
        return 0;
    }
    D_003F7774 = 0;
    return 4;
}

void func_0022eb00(s32 arg0) {
    TextWin *o[2];
    func_001f3110();
    o[0] = func_001f31a8(D_003F7750, 44);
    if (o[0] != NULL) {
        o[1] = func_001f31a8(D_003F7720, 45);
        if (o[1] != NULL) {
            func_001f3e90(o[0], o[1]);
            func_001f3e20(o[1], o[0]);
            o[1]->xa0 = 0;
        }
    }
    D_006469DC = 0;
    D_006469E4 = 0;
    D_006469EC = 0;
    D_006469F4 = 0;
    D_003F7774 = 1;
    D_006469D0 = 0;
    D_006469D4 = 0;
    func_0020b968();
    func_0020bb90(0x153, 0xA4);
    func_0020bda8(0x28);
    func_0011ef10(0x2BFE9, func_0022eab8)[1] = arg0;
}
