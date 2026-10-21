#include "common.h"
/* func_001124f8: matched in session 8 (w7): func_001ed170 takes one s32 argument, called with D_002C1380. */
typedef struct { s32 x0, x4, x8, xc, x10, x14, x18, x1c, x20, x24, x28, x2c, x30, x34, x38; } MapHdr;
#include "data/types/text_00110000_s8_w7.h"
#include "data/pieces/D_002BC0A8.h"
typedef Fl0A8_2BC0A8 Fl0A8;
extern MapHdr *D_004D92DC; /* src/data/bss_004D.c: void *D_004D92DC */
extern s32 D_002BCC90, D_002BCC94, D_002BCDE0;
#include "data/pieces/D_002BCC9C.h"
#include "data/pieces/D_002BCDAC.h"
extern u32 D_002BCDB0;
#include "data/pieces/D_002BCDA4.h"
#include "data/pieces/D_002BCDA0.h"
extern s32 D_002BCDD8, D_002BCDA8, D_002BC128, D_002BC130, D_002BC134, D_002BCDDC, D_002BC12C, D_002BC734;
extern s32 D_002BCB30, D_002C12C0, D_002C1380, D_002C1360, D_002C1384;
#include "data/pieces/D_002A3F50.h"
extern s32 D_002C1378[2];
#include "data/pieces/D_002E27A4.h"
s32 func_00111660(s32, s32);
void func_00112320(void);
void func_001119d0(void);
void func_00103280(f32, f32, f32, f32);
void func_00110e38(f32, f32, f32, f32);
void func_001124c0(void);
s32 func_001ed170(s32);
u8 *func_001eaff8(void);

void func_001124f8(void) {
    MapHdr *h = D_004D92DC;
    s32 *sub;
    f32 one;
    s32 t;
    sub = (s32 *)((u8 *)h + h->x10);
    D_002BCC90 = (s32)h + h->x18;
    t = D_002BCDD8;
    D_002BCC9C = (s32)h + h->x20;
    D_002BCC94 = (s32)h + h->x30;
    D_002BCDE0 = (s32)h + h->x38;
    D_002BCDAC = (Room *)((u8 *)sub + sub[0]);
    D_002BCDB0 = (u32)sub[1] >> 6;
    D_002BCDA0 = (Room *)((u8 *)sub + sub[2]);
    D_002BCDA4 = (u32)sub[3] >> 6;
    if (t) {
        D_002BC130 = D_002BCDA0[D_002BCDA8].x0;
        D_002BC134 = func_00111660(D_002BC128, D_002BC130);
        func_00112320();
        if (D_002BCDDC == 0) func_001119d0();
    }
    D_002BC12C = D_002BCDAC[D_002BC130].x0;
    one = 1.0f;
    func_00103280(one, one, one, one);
    func_00110e38(one, one, one, one);
    D_002BC734 = D_002BCDAC[D_002BC130].fl.b1;
    if (D_002BC734) func_00110e38(one, 0.9f, one, 0.05f);
    D_002BC0A8.fl0A8.b2 = !D_002BCDAC[D_002BC130].fl.b0;
    D_002BC0A8.fl0A8.b3 = !D_002BCDAC[D_002BC130].fl.b2;
    func_001124c0();
    D_002BCB30 = D_002BCDAC[D_002BC130].fl.b3;
    D_002C12C0 = D_002BCDAC[D_002BC130].fl.b6;
    D_002C1380 = D_002BCDAC[D_002BC130].x14;
    D_002C1360 = D_002BCDAC[D_002BC130].x18;
    D_002C1384 = D_002BCDAC[D_002BC130].x1c;
    (*(s32 (*)[2])&D_002A3F50)[0] = D_002BCDAC[D_002BC130].x20;
    (*(s32 (*)[2])&D_002A3F50)[1] = D_002BCDAC[D_002BC130].x24;
    func_001ed170(D_002C1380);
    D_002C1378[0] = D_002BCDAC[D_002BC130].x8;
    D_002C1378[1] = D_002BCDAC[D_002BC130].xc;
    if (D_002BC128 == 3 && *func_001eaff8() >= 43) {
        D_002C1378[0] = D_002BCDAC[D_002BC130].x28;
        D_002C1378[1] = D_002BCDAC[D_002BC130].x2c;
    }
    D_002E27A4 = 0;
}
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/pieces/D_002C1378.h"
#include "data/pieces/D_002BC128.h"
