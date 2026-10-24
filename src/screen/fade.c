/* A screen colour overlay (a guess at the name), 0x001137f8-0x00113de0:
 * func_001137f8 writes the colour D_004D934C ... D_004D9360 into the GS
 * packet D_002BCE00 and sends it, func_00113af8 steps its sequences by
 * D_004D9340 / D_004D9344; src/game/pause.c sets the colour when it
 * pauses. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "platform/gs.h"
#include "data/bss_004D.h"
#include "data/bss_0049.h"
#include "data/types/text_00100000_h2.h"
#include "data/pieces/D_002B677C.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002B6778.h"
#include "data/types/text_00100000_h2_p.h"
#include "data/pieces/D_002B75A0.h"
#include "data/pieces/D_002BD118.h"
#include "data/pieces/D_002BBDF0.h"
#include "data/pieces/D_002BBDF8.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002BCB60.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002BC148.h"
#include "vm/script_vm.h"
#include "data/types/text_00100000_h2_p2.h"
#include "data/pieces/D_002BCDC8.h"
#include "data/pieces/D_002BCDA0.h"
#include "data/pieces/D_002BCDA4.h"
#include "m2c.h"
#include "data/pieces/D_002BCCA0.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_002BCD60.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/bss_004E.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002BCDAC.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002C5968.h"

/* func_001137f8 (from hand/text_00110000_s12_s12w10.c). */
extern u64 D_002BCE00[];
extern u8 D_002BD100[];
void func_001104e0(void);
void func_0010f580(void);
void func_0010f5d0(void);
s32 func_00106b18(void *);
u8 *func_001efc10(s32);
void func_001f1ed8(s32, s32, s32, u8 *, s32);
void func_001137f8(void) {
    s32 col;
    u64 a, b;
    u64 *p = D_002BCE00;
    col = D_004D934C;
    col |= D_004D9358 << 24;
    col |= (D_004D9354 << 16) | (D_004D9350 << 8);
    b = ((s64)D_004D935C << 24) | 0x100000000;
    a = ((s64)D_004D9360 << 24) | 0x100D17A88;
    p[0x140/8] = a;
    p[0x160/8] = a;
    p[0x180/8] = a;
    p[0x190/8] = a;
    p[0x1A0/8] = a;
    p[0x1B0/8] = a;
    p[0x1D0/8] = a;
    p[0x1F0/8] = a;
    p[0x230/8] = a;
    p[0x250/8] = a;
    p[0x270/8] = a;
    p[0x280/8] = a;
    p[0x290/8] = a;
    p[0x2A0/8] = a;
    p[0x2C0/8] = a;
    p[0x2E0/8] = a;
    p[0x50/8] = b;
    p[0x70/8] = b;
    p[0x90/8] = b;
    p[0xA0/8] = b;
    p[0xB0/8] = b;
    p[0xC0/8] = b;
    p[0xE0/8] = b;
    p[0x100/8] = b;
    func_001104e0();
    func_0010f580();
    func_00106b18(D_002BD100);
    func_001f1ed8(col, 182, 54, func_001efc10(5), 18);
    func_001f1ed8(col, 214, 54, func_001efc10(6), 18);
    func_001f1ed8(col, 246, 54, func_001efc10(7), 18);
    func_001f1ed8(col, 278, 54, func_001efc10(8), 18);
    func_001f1ed8(col, 310, 54, func_001efc10(9), 18);
    func_0010f5d0();
    PlatGsSyncPath(0, 0);
    *(volatile u64 *)0x12000000 = 0xff03;
    *(volatile u64 *)0x12000070 = 0x11b0;
    *(volatile u64 *)0x12000080 = 0x0007f9ff020d227cUL;
}

/* func_00113a00 (from hand/text_00100000_h2.c). */
void func_00113a00(void) {
    D_004D934C = 205;
    D_004D9350 = 135;
    D_004D9354 = 50;
    D_004D9358 = 128;
    D_004D935C = 76;
    D_004D9360 = 128;
}

/* func_00113a48 (from auto/text_00110000_11.c). */
extern volatile s32 D_002C5AD0[];
extern volatile s32 D_002C5BB0[];
void func_00113a48(void) {
    D_002C5AD0[2] = 0;
    D_002C5AD0[1] = 0;
    D_002C5BB0[27] = 0;
    D_002C5BB0[1] = 0;
    D_002C5BB0[2] = 0;
    D_002C5BB0[12] = 0;
    D_002C5BB0[13] = 0;
    D_002C5BB0[14] = 0;
    D_002C5BB0[15] = 0;
    D_002C5BB0[16] = 0;
    D_002C5BB0[17] = 0;
    D_002C5BB0[18] = 0;
    D_002C5BB0[19] = 0;
    D_002C5BB0[20] = 0;
    D_002C5BB0[21] = 0;
    D_002C5BB0[22] = 0;
    D_002C5BB0[23] = 0;
    D_002C5BB0[24] = 0;
    D_002C5BB0[25] = 0;
    D_002C5BB0[26] = 0;
}

/* func_00113ab0 (from auto/text_00110000.c). */
extern s64 D_12000000;
#define func_001104e0 ((M2C_UNK (*)()) func_001104e0)
#define func_001137f8 ((M2C_UNK (*)()) func_001137f8)
#define func_00113a00 ((M2C_UNK (*)()) func_00113a00)
void func_00113ab0(s32 arg0) {
    if (arg0 == 0) {
        func_001104e0();
        D_12000000 = 0x22;
        return;
    }
    func_00113a00();
    func_001137f8();
}
#undef func_001104e0
#undef func_001137f8
#undef func_00113a00

/* func_00113af8 (from hand/text_00110000_s6_02.c). */
extern s32 D_004D9364;
void func_00113df8(s32);
void func_00113e28(s32);
static inline void add6(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    D_004D934C += a;
    D_004D9350 += b;
    D_004D9354 += c;
    D_004D9358 += d;
    D_004D935C += e;
    D_004D9360 += f;
}
void func_00113af8(void) {
    switch (D_004D9340) {
    case 1:
        switch (D_004D9344) {
        case 0:
            if (D_004D9348 < 2) {
                add6(0, 0, 0, 50, 15, 25);
                break;
            }
            D_004D9344 = 1;
        case 1:
            if (D_004D9348 < 5) {
                add6(25, 2, -68, 9, 15, 25);
                break;
            }
            D_004D9344 = 2;
        case 2:
            D_004D9364 = 0;
            func_00113a00();
            break;
        }
        break;
    case 2:
        switch (D_004D9344) {
        case 0:
            if (D_004D9348 < 2) {
                add6(0, 0, 0, -14, -15, -25);
                break;
            }
            D_004D9344 = 1;
        case 1:
            if (D_004D9348 < 5) {
                add6(-25, -2, 68, -33, -15, -25);
                break;
            }
            D_004D9344 = 2;
        case 2:
            func_00113ab0(0);
            if (D_002BD118 == 2) func_00113df8(0);
            else func_00113e28(0);
            D_004D9340 = 0;
            return;

        }
        break;
    case 0:
    default:
        return;
    }
    func_001137f8();
    D_004D9348++;
}

