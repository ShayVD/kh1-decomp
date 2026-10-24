/* The pause and the menus opened from the field (a guess at the name),
 * 0x00113de0-0x00114880: func_00114280 toggles the pause on the start
 * button (D_002C5AD0[2] & 8), pauses the sound (func_00113e28, "ERROR:sound
 * pause"), and opens the menu chosen by func_001140a0 in D_002BD118
 * (func_0020d6c8, func_0022daa0, func_0022e368, func_002295a0 ...) through
 * the frame tasks func_00113f60 / func_00114028. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "m2c.h"
#include "data/bss_004D.h"
#include "data/bss_004E.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002BCB60.h"
#include "data/pieces/D_002BCDAC.h"
#include "data/pieces/D_002BD118.h"
#include "common.h"
#include "data/pieces/D_002BBE20.h"
#include "data/pieces/D_002BBE60.h"
#include "data/pieces/D_002BBEA0.h"
#include "data/pieces/D_002BBEE0.h"
#include "data/pieces/D_002BBF20.h"
#include "data/pieces/D_002BBF60.h"
#include "data/pieces/D_002BBFA0.h"
#include "data/pieces/D_002BBFE0.h"
#include "data/pieces/D_002BC020.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002BCDA0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002C5968.h"
#include "data/pieces/D_002B6778.h"
#include "data/pieces/D_002BBDE0.h"
#include "vm/script_vm.h"
#include "data/pieces/D_002BBDF0.h"
#include "data/pieces/D_002BBDF4.h"
#include "data/pieces/D_002BBDF8.h"
#include "data/types/text_00110000_h52.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002BCCA0.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_002BCD60.h"
#include "data/pieces/D_002A6210.h"
#include "data/pieces/D_002A6220.h"

/* func_00113de0 (from auto/text_00110000.c). */
void func_00113de0(void) {
    D_004D9328 = 0;
    D_004D932C = 0;
}

/* func_00113df8 (from auto/text_00110000.c). */
M2C_UNK func_001ed1c8();
void func_00113df8(s32 arg0) {
    func_001ed1c8();
    D_004D932C = arg0;
}

/* func_00113e28 (from hand/text_00110000_s9_w5.c). */
extern char D_0048D010[];
void func_001edba0(void);
void func_001104e0(void);
int printf(const char *, ...);
#define func_001ed1c8 ((void (*)(s32)) func_001ed1c8)
/* func_00113e28: printf takes only the format (the string has no %d); the
 * value in a1 is just D+2 allocated to the first free register. */
void func_00113e28(s32 a) {
    if (a == 0) {
        if (--D_004D9328 != 0) return;
        if (D_004D932C == 1) {
            func_00113df8(a);
            func_001edba0();
            func_001104e0();
            func_00113df8(1);
            return;
        }
        func_00113df8(a);
        return;
    }
    func_001ed1c8(2);
    if (++D_004D9328 != 0) return;
    D_004D9328++;
    printf(D_0048D010);
}
#undef func_001ed1c8

/* func_00113ee0 (from auto/text_00110000_18.c). */
M2C_UNK func_00102a48(M2C_UNK, M2C_UNK);
extern s32 D_004D9330;
s32 func_00113ee0(void) {
  int *new_var2;
  int new_var;
  new_var2 = &new_var;
  new_var = 4;
  func_00102a48(0x80, 0x20);
  return ((D_004D9330 ^ (*new_var2)) == 0) ? (0) : (4);
}

/* func_00113f18 (from auto/text_00110000_3.c). */
void *func_0011ef10(M2C_UNK, M2C_UNK *);
s32 func_00113f18(void) {
    M2C_FIELD(func_0011ef10(0x2903, &func_00113ee0), s16 *, 2) = 1;
    func_00102a48(0x80, 0x10);
    D_004D9330 = 3;
    return 4;
}

/* func_00113f60 (from auto/text_00110000_4.c). */
M2C_UNK func_0010a3e8();
s32 func_00113f60(void) {
    M2C_FIELD(func_0011ef10(0x2E643, &func_00113f18), s16 *, 2) = 1;
    func_0010a3e8();
    func_00102a48(0x80, 0x10);
    return 4;
}

/* func_00113fa8 (from hand/text_00110000_s6_02.c). */
extern s32 D_003F6E28;
extern volatile s32 D_002BD114;
extern s32 D_004D9320;
s32 func_00112d80(void);
s32 sceGsSyncPath(s32, s32);
void func_00121ee0(s32);
void func_00176388(s32);
#define func_00102a48 ((s32 (*)(s32, s32)) func_00102a48)
s32 func_00113fa8(void) {
    func_00102a48(128, 0);
    if (D_003F6E28) {
        D_003F6E28 = 0;
        func_00112d80();
    }
    D_004D9330 = 0;
    D_002BD114 = 0;
    sceGsSyncPath(0, 0);
    func_00121ee0(D_002B6778);
    func_00176388(0);
    D_004D9320 = 0;
    return 4;
}
#undef func_00102a48

/* func_00114028 (from auto/text_00110000.c). */
s32 func_00114028(void) {
    func_00102a48(0x80, 0x10);
    M2C_FIELD(func_0011ef10(0x2E643, &func_00113fa8), s16 *, 2) = -1;
    return 4;
}

/* func_00114068 (from auto/text_00110000.c). */
s32 func_00114068(void) {
    func_00102a48(0x80, 0x20);
    return 4;
}

/* func_00114090 (from auto/text_00110000.c). */
void func_00114090(void) {
    D_002BD118 = 1;
}

/* func_001140a0 (from hand/text_00110000_h52.c). */
extern s32 D_002BD11C;
typedef Bits_37a378 Bits52;
extern s32 D_002C130C;
extern s32 D_002C1308;
extern s32 D_002BC0BC;
extern s32 D_002A6204;
s32 func_001336a0(void);
extern Bits52 D_002C5958_001140a0 __asm__("D_002C5958");
#define D_002C5958 D_002C5958_001140a0
s32 func_001140a0(void) {
    s32 *p;
    if (D_004D9320 == 0) {
        p = &D_002BD118;
        *p = 0;
        if (D_002C5958.b0 == 1) *p = 2;
        if (D_002C5958.b4 == 1) *p = 2;
        if ((*(Bits_37a378 *)&D_0037A378).b1 == 1) *p = 1;
        if ((*(Bits_37a378 *)&D_0037A378).b3 == 1) *p = 3;
        if (D_002BD11C == 1) *p = D_002BD11C;
        if (D_002C1308) *p = 4;
        if (D_002C130C) *p = 5;
        if (D_002BBDE0 == 5) *p = 7;
        if (func_001336a0()) *p = 2;
        if (*p == 0) {
            if ((*(s32 *)&D_002BC070) != 128 || D_002BC0BC || D_002A6204) D_002BD118 = 1;
        }
    }
    return D_002BD118;
}
#undef D_002C5958

/* func_00114200 (from auto/text_00110000.c). */
extern s32 D_002C596C;
void func_00114200(void) {
    D_002C596C = 1;
}

/* func_00114210 (from auto/text_00110000.c). */
void func_00114210(void) {
    D_002C596C = 0;
}

/* func_00114220 (from auto/text_00110000_6.c). */
#define func_00176388 ((M2C_UNK (*)(M2C_UNK)) func_00176388)
void func_00114220(void) {
    func_00176388(1);
    D_004D9330 = 1;
    D_004D9320 = 1;
}
#undef func_00176388

/* func_00114250 (from auto/text_00110000_11.c). */
extern s32 D_002BBE0C;
s32 func_0011d768(s32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_00114250(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4, f32 fparg5, f32 fparg6, f32 fparg7) {
    D_002BD114 = 1;
    D_002BBE0C = 0;
    func_0011d768(6, fparg0, fparg1, fparg2, fparg3, fparg4, fparg5, fparg6, fparg7);
}

/* func_00114280 (from hand/text_00100000_c00.c). */
typedef struct { s16 h0; s16 h2; } Tsk;
extern volatile s32 D_002BBE08;
extern s32 D_002B6774;
extern s32 D_004D933C;
extern s32 D_004D9338;
extern volatile s32 D_004D9364;
extern f32 D_002BBDFC;
extern volatile s32 D_002C5AD0[3];
extern s32 D_004D9324;
extern s32 D_002C5AD8;
extern s32 (*D_0046A6A4)(void);
extern s32 D_002B6478;
extern s32 D_003F34A4;
extern s32 D_002BD110;
extern s32 D_003F76B4;
void func_00113a00(void);
void func_00113af8(s32);
void func_001220d0(void);
void func_0010fd40(void);
s32 func_00109658(void);
s32 func_0010f918(void);
void func_00113ab0(s32);
void func_0011c778(void);
void func_0011c798(void);
void func_00157668(void);
void func_0020d6c8(s32);
void func_0022daa0(s32);
void func_0022e368(s32);
void func_00111510(void);
void func_002295a0(s32, s32);
void func_002297a0(s32);
void func_001dcd98(s32);
extern volatile s32 D_002C1308_00114280 __asm__("D_002C1308");
#define D_002C1308 D_002C1308_00114280
extern u32 D_004D9330_00114280 __asm__("D_004D9330");
#define D_004D9330 D_004D9330_00114280
#define func_0011ef10 ((Tsk *(*)(s32, void (*)(void))) func_0011ef10)
#define func_00114250 ((void (*)(void)) func_00114250)
s32 func_00114280(void) {
    u32 s;
    s32 save;
    f32 fsave;

    s = D_002BBDE0;
    if (s != 3 && s != 5) {
        return 1;
    }
    if (D_002B6774 != 0) {
        return 1;
    }
    if (D_004D9334 != 0) {
        return 1;
    }
    switch (D_002BD118) {
    case 1:
    case 2:
        D_004D933C = 1;
        D_004D9338 = 0;
        D_004D9340 = 0;
        D_004D9364 = 0;
        save = D_002BBE0C;
        fsave = D_002BBDFC;
        do {
            if (D_004D9364 == 0 && (D_002C5AD0[2] & 8)) {
                D_002BBE0C = 0;
                D_004D9338 ^= 1;
                D_004D9364 = 1;
                D_004D9348 = 0;
                D_004D9344 = 0;
                switch (D_004D9340) {
                case 0:
                    if (D_002BD118 == 2) {
                        func_00113df8(1);
                    } else {
                        func_00113e28(1);
                    }
                    D_004D9340 = 1;
                    D_004D934C = 128;
                    D_004D9350 = 128;
                    D_004D9354 = 255;
                    D_004D9358 = 0;
                    D_004D935C = 0;
                    D_004D9360 = 0;
                    break;
                case 1:
                    D_004D9340 = 2;
                    func_00113a00();
                    break;
                }
                D_002BD114 ^= 1;
            }
            if (D_004D9340 != 0) {
                func_00113af8(D_004D9338);
                D_002BD114 = 1;
                func_001220d0();
                func_0010fd40();
                if (func_00109658() == 0) {
                    goto end;
                }
                if (func_0010f918()) {
                    func_00113ab0(D_004D9338);
                }
                func_001104e0();
            } else {
                D_004D933C = 0;
                D_002BD114 = 0;
                D_002BBE0C = save;
                D_002BBDFC = fsave;
            }
        } while (D_004D933C != 0);
        break;
    case 4:
        if (D_002C1308 != 0) {
            func_00114220();
            D_004D9324 = D_002C1308;
            func_0011c778();
        }
        break;
    case 5:
        if (D_002C130C != 0) {
            func_00114220();
            func_0011c798();
        }
        break;
    case 3:
    default:
        if (D_004D9330 == 0 && (D_002C5AD8 & 8)) {
            func_00114220();
        }
        break;
    }
    switch (D_004D9330) {
    case 0:
        D_002C596C = 0;
        break;
    case 1:
        func_00114200();
        func_0011ef10(0x2e644, func_00113f60)->h2 = 1;
        D_004D9330 = 2;
        break;
    case 2:
        func_00114200();
        break;
    case 3:
        func_00114200();
        func_00113df8(1);
        switch (D_002BD118) {
        case 0:
            func_00114250();
            D_002B6478 = D_0046A6A4();
            func_00157668();
            func_0020d6c8(1);
            break;
        case 3:
            func_00114250();
            func_0022daa0(1);
            break;
        case 7:
            func_00114250();
            func_0022e368(1);
            break;
        case 4:
            func_00114250();
            func_00111510();
            func_00157668();
            func_002295a0(1, D_004D9324);
            break;
        case 5:
            func_00114250();
            func_00157668();
            func_002297a0(1);
            break;
        }
        D_004D9330 = 4;
        break;
    case 4:
        func_00114200();
        if (D_003F34A4 == 0) {
            if (D_003F6E28 != 0) {
                D_002BD110 = 1;
            }
            if (D_002BD118 == 3) {
                func_001dcd98(D_003F76B4);
            }
            func_00113df8(0);
            D_004D9330 = 5;
        }
        break;
    case 5:
        D_002BBE0C = 1;
        func_0011ef10(0x2e645, func_00114028)->h2 = -1;
        func_00114210();
        D_004D9330 = 6;
        break;
    case 6:
        func_00114210();
        break;
    default:
        func_00114210();
        break;
    }
end:
    return D_002BBE08;
}
#undef D_002C1308
#undef D_004D9330
#undef func_0011ef10
#undef func_00114250

/* func_00114800 (from auto/text_00110000.c). */
void func_00114800(void) {
    D_002BD11C = 1;
}

/* func_00114810 (from auto/text_00110000.c). */
void func_00114810(void) {
    D_002BD11C = 0;
}

/* func_00114820 (from auto/text_00110000.c). */
void func_00114820(void) {
    D_004D9334 = 1;
}

/* func_00114830 (from auto/text_00110000.c). */
void func_00114830(void) {
    D_004D9334 = 0;
}

/* func_00114840 (from auto/text_00110000_6.c). */
void func_00114840(void) {
    D_004D9320 = 0;
    D_004D9330 = 0;
    func_00114820();
    D_002BD114 = 0;
    func_00114810();
    func_0011c778();
    func_0011c798();
}

