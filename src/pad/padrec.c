/* The pad's stand-ins (docs/modules.md "Session 44"), 0x00233610-0x002336f8.
 * D_00425BC8 points at the pad the game reads: the real one D_002C5AD0
 * (func_00233610 resets to it) or D_00647710, which func_002336f8 (once a
 * frame, from the top menu and the load screen's task) fills from one of
 * three sources: a recording (func_00233650(buf, n) records n frames of the
 * real pad's three words x4 / x8 / x10 into buf, func_00233670 stops), a
 * replay (func_00233680(buf, n) plays such a buffer back, func_002336a0
 * stops) and a script (func_002336b0(p): pairs of (button, frames), 0-5
 * the buttons 0x10 / 0x40 / 0x80 / 0x20 (the d-pad, both halves) and 0x2000
 * / 0x4000, 6 a pause, 7 the end; each press is followed by a frame with
 * nothing held).  D_006477A4 counts the frames with nothing held
 * (func_002336e8 reads it, func_002336d8 clears it): most likely the title
 * screen's idle timer for the demo.  On the Vita this sits above the pad
 * wrapper (include/platform/pad.h) and needs no change.  Not proved by a
 * boot. */
#include "common.h"
#include "data/bss_0064.h"
#include "data/pieces/D_00425BC8.h"

typedef PadSt_425bc8 Cfg;
/* One frame of a recording: the pad's words x4, x8 and x10. */
typedef struct { u32 a; s32 b; u32 c; } Rec;

extern Cfg D_002C5AD0;
extern Cfg D_00647710;
extern s32 D_00647780;
extern Rec *D_00647784; /* src/data/bss_0064.c: s32 D_00647784 */
extern s32 D_00647788;
extern s32 D_0064778C;
extern Rec *D_00647790; /* src/data/bss_0064.c: s32 D_00647790 */
extern s32 D_00647794;
extern s32 D_00647798;
extern u8 *D_0064779C; /* src/data/bss_0064.c: s32 D_0064779C */
s32 D_006477A0 ALIGNED(16);
extern f32 D_006477A4;
extern f32 D_002BBDFC;

void func_002336d8(void);

void func_00233610(void) {
    D_00425BC8 = &D_002C5AD0;
    D_00647780 = 0;
    D_0064778C = 0;
    D_00647798 = 0;
    func_002336d8();
}

void func_00233650(Rec *a, s32 b) {
    D_00647780 = 1;
    D_00647784 = a;
    D_00647788 = b;
}

void func_00233670(void) {
    D_00647780 = 0;
}

void func_00233680(Rec *a, s32 b) {
    D_0064778C = 1;
    D_00647790 = a;
    D_00647794 = b;
}

void func_002336a0(void) {
    D_0064778C = 0;
}

void func_002336b0(u8 *a) {
    D_00647798 = 1;
    D_0064779C = a;
}

void func_002336c8(void) {
    D_00647798 = 0;
}

void func_002336d8(void) {
    D_006477A4 = 0;
}

f32 func_002336e8(void) {
    return D_006477A4;
}

void func_002336f8(void) {
    Rec *p;
    switch (D_00647780) {
    case 0:
        break;
    case 1:
        if (--D_00647788) {
            D_00647784->a = D_002C5AD0.x4;
            D_00647784->b = D_002C5AD0.x8;
            D_00647784->c = D_002C5AD0.x10;
            D_00647784++;
        } else {
            D_00647780 = 0;
        }
        break;
    }
    switch (D_0064778C) {
    case 0:
        break;
    case 1:
        if (--D_00647794) {
            D_00425BC8 = (void *)(&D_00647710);
            D_00647710.x4 = D_00647790->a;
            D_00647710.x8 = D_00647790->b;
            D_00647710.x10 = D_00647790->c;
            D_00647790++;
        } else {
            D_0064778C = 0;
            D_00425BC8 = (void *)(&D_002C5AD0);
        }
        break;
    }
    switch (D_00647798) {
    case 1:
        D_00425BC8 = (void *)(&D_00647710);
        switch (*D_0064779C) {
        case 0:
            D_00647710.x4 = 0x10000010;
            D_00647710.x8 = 0x10000010;
            D_00647710.x10 = 0x10000010;
            D_006477A0 = D_0064779C[1];
            D_0064779C += 2;
            if (D_006477A0) D_00647798 = 2;
            break;
        case 1:
            D_00647710.x4 = 0x40000040;
            D_00647710.x8 = 0x40000040;
            D_00647710.x10 = 0x40000040;
            D_006477A0 = D_0064779C[1];
            D_0064779C += 2;
            if (D_006477A0) D_00647798 = 2;
            break;
        case 2:
            D_00647710.x4 = 0x80000080;
            D_00647710.x8 = 0x80000080;
            D_00647710.x10 = 0x80000080;
            D_006477A0 = D_0064779C[1];
            D_0064779C += 2;
            if (D_006477A0) D_00647798 = 2;
            break;
        case 3:
            D_00647710.x4 = 0x20000020;
            D_00647710.x8 = 0x20000020;
            D_00647710.x10 = 0x20000020;
            D_006477A0 = D_0064779C[1];
            D_0064779C += 2;
            if (D_006477A0) D_00647798 = 2;
            break;
        case 4:
            D_00647710.x4 = 0x2000;
            D_00647710.x8 = 0x2000;
            D_00647710.x10 = 0x2000;
            D_006477A0 = D_0064779C[1];
            D_0064779C += 2;
            if (D_006477A0) D_00647798 = 2;
            break;
        case 5:
            D_00647710.x4 = 0x4000;
            D_00647710.x8 = 0x4000;
            D_00647710.x10 = 0x4000;
            D_006477A0 = D_0064779C[1];
            D_0064779C += 2;
            if (D_006477A0) D_00647798 = 2;
            break;
        case 6:
            D_006477A0 = D_0064779C[1];
            D_0064779C += 2;
            if (D_006477A0) D_00647798 = 2;
            break;
        case 7:
            D_00647798 = 0;
            D_00425BC8 = (void *)(&D_002C5AD0);
            break;
        }
        break;
    case 2:
        D_00425BC8 = (void *)(&D_00647710);
        D_00647710.x4 = 0;
        D_00647710.x8 = 0;
        D_00647710.x10 = 0;
        if (--D_006477A0 <= 0) D_00647798 = 1;
        break;
    case 0:
        break;
    }
    if (D_00425BC8->x4) D_006477A4 = 0.0f;
    else D_006477A4 += D_002BBDFC;
}

#include "data/data_003F.h"
#include "data/data_0042.h"
#include "data/data_003E.h"
#include "data/pieces/D_002BBDFC.h"
