/* The boot and the game's states (a guess at the name),
 * 0x00109268-0x00109cd0: func_00109288 starts the systems at boot,
 * func_00109558 asks for a state (D_00495160), func_00109770 runs the
 * state machine (loading the overlay at D_00F20000 for some states),
 * func_00109658 the frame of the field. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "m2c.h"
#include "data/bss_0049.h"
#include "data/bss_004D.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002A6238.h"
#include "common.h"
#include "data/pieces/D_0037A378.h"
#include "data/types/text_00100000_h28.h"
#include "data/pieces/D_002BC0C0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002A6234.h"
#include "data/types/text_00100000_h28_p.h"
#include "data/pieces/D_002B1C60.h"
#include "data/pieces/D_002AA060.h"
#include "data/pieces/D_002A62B0.h"
#include "data/pieces/D_002A3F60.h"
#include "data/pieces/D_002A4060.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002A3E20.h"
#include "data/pieces/D_002A3F30.h"
#include "data/pieces/D_002A3F50.h"
#include "data/pieces/D_002A62D0.h"
#include "data/pieces/D_002BBDE4.h"
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "data/pieces/D_002B7590.h"
#include "data/pieces/D_002BBAA0.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002A3F48.h"
#include "data/pieces/D_002B6778.h"
#include "data/pieces/D_002BC148.h"
#include "data/pieces/D_002BCDC8.h"

/* func_00109268 (from auto/text_00100000.c). */
extern s32 D_002B6484;
void func_00109268(void) {
    D_002B6484 = 0;
}

/* func_00109278 (from auto/text_00100000.c). */
void func_00109278(void) {
    D_002B6484 = 1;
}

/* func_00109288 (from hand/text_00100000_h28.c). */
typedef struct { u8 pad[0x18]; s32 (*f18)(s32); s32 (*f1c)(void); } Api;
typedef struct { u8 pad[0xc]; s32 v; } Res;
extern Api D_0046A688;
extern Res *func_00120190(char *);
extern char D_0048CCA0[];
extern char D_0048CCB8[];
extern s32 D_002B6478;
extern s32 D_002BC73C;
extern u8 D_002B6460[];
extern void func_00110068(void);
extern void func_00110448(s32);
extern void func_0011ecd8(void *, char *);
extern void func_0011f988(void);
extern void func_001ec7d0(s32);
extern void func_001ee4b8(void);
extern void func_00232ad0(s32);
extern void func_0010c278(void);
void func_00109288(void) {
    Res *r;
    D_002BBDE4 = 7;
    func_00110068();
    func_0010c278();
    func_001ee4b8();
    func_00232ad0(-1);
    func_0011ecd8(D_002B6460, D_0048CCA0);
    r = func_00120190(D_0048CCB8);
    if (r != NULL) {
        D_0046A688.f18(r->v);
    } else {
        D_0046A688.f18(0);
    }
    D_002B6478 = D_0046A688.f1c();
    func_00110448(0);
    D_002BC73C = 0;
    func_001ec7d0(0);
    func_0011f988();
}

/* func_00109360 (from auto/text_00100000_9.c). */
M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
s32 func_00109360(void) {
    func_0011f130((M2C_UNK *)&D_002BC720, 0);
    return 0;
}

/* func_001094f0 (from auto/text_00100000_4.c). */
extern M2C_UNK D_002BC320;
extern s32 D_0035C6F0;
s32 func_0011ef10(s32, s32);
void func_001103a0(void);
void func_0011efa8(s32, s32, s32, s32);
void func_00175918(void);
void func_00175980(void);
void func_001094f0(void) {
    func_001103a0();
    func_00175918();
    func_00175980();
    D_0035C6F0 = 1;
    func_0011efa8((s32) (M2C_UNK *)&D_002BC720, (s32) &D_002BC320, 0x20, 0x20);
    func_0011ef10(0x2E662, (s32) &func_00109360);
}

/* func_00109558 (from auto/text_00100000_9.c). */
extern volatile s32 D_00495160;
extern volatile s32 D_00495164;
s32 func_0010a0d8(void);
void func_00109558(s32 arg0) {
    D_00495164 = arg0;
    D_00495160 = 2;
    func_0010a0d8();
}

/* func_00109588 (from auto/text_00100000.c). */
M2C_UNK func_00101660();
M2C_UNK func_001559f0(M2C_UNK, M2C_UNK);
extern s32 D_002BCDD8;
void func_00109588(void) {
    D_002BCDD8 = 0;
    func_00101660();
    func_001559f0(0, 0x40);
}

/* func_001095b0 (from auto/text_00100000_9.c). */
M2C_UNK func_00100360();
M2C_UNK func_00122130();
M2C_UNK func_0015f018();
M2C_UNK func_001c06f8();
M2C_UNK func_00236f18();
M2C_UNK func_0024b990();
void func_001095b0(void) {
    func_00122130();
    func_0015f018();
    func_00100360();
    func_001c06f8();
    func_00236f18();
    func_0024b990();
    (*(volatile s8 **)&D_002BC140) = &D_002E2700;
    (*(volatile s8 **)&D_002BC144) = &D_002E2740;
    D_002BBDE0 = 3;
    D_00495160 = 0;
}

/* func_00109630 (from auto/text_00100000.c): the loaded overlay's entry at
 * D_00F20000, called as a function (func_00109770 below loads it there and
 * views the address as data). */
void func_002583e0(s32);
void D_00F20000(s32, s32);
void func_00109630(void) {
    func_002583e0(2);
    D_00F20000(0, 0);
}

/* func_00109658 (from hand/text_00100000_h28.c). */
typedef struct { u64 a; s32 b; } Pad8;
extern Pad8 D_002BCA00;
extern s32 D_002BCAE0;
extern s32 func_0010c200(void);
extern s32 func_0010fd40(void);
extern s32 func_00111150(void);
extern s32 func_001ecfd8(void);
extern void func_0010ff60(s32);
extern void func_001104e0(void);
extern void func_00111190(void);
extern void func_001111b0(void);
extern void func_00114820(void);
extern void func_001220d0(void);
extern void func_00176c60(s32);
extern void func_00239488(void);
extern volatile s32 D_002BBE08;
s32 func_00109658(void) {
    if (D_002B6484 == 0 && (D_002BCA00.a & 0xF0900000000ull) == 0xF0900000000ull && (D_002BCA00.b & 0xF09)
        && func_0010c200() == 0 && func_001ecfd8() == 0) {
        D_002BBE08 = 0;
        func_001ec7d0(1);
        func_00114820();
        func_00239488();
        func_00176c60(0);
        func_0010fd40();
        if (D_002BCAE0 != 0) {
            do {
                func_001220d0();
                func_00111190();
                func_001104e0();
            } while (func_00111150() != 1);
            func_001111b0();
        }
        func_001104e0();
        func_0010ff60(0);
    }
    return D_002BBE08;
}

/* func_00109770 (from hand/text_00100000_s7_w32.c). */
void func_00109388(void);
void func_0015eda8(void);
void func_0015ee10(void);
void func_00120748(void *, void *, void (*)(void), s32);
void func_00109630(void);
void func_00232da0(void);
void func_001586a8(s32);
s32 func_00111830(void);
void func_001ba870(void);
void func_001ba7e0(void);
void func_00111020(s32);
s32 func_00111090(void);
void func_00111060(void);
s32 func_00111110(void);
s32 func_001110f0(void);
void func_00105f28(void);
void func_00114880(void);
void func_001140a0(void);
s32 func_00114280(void);
void func_0010f918(void);
void func_0011eeb0(void);
void func_0011de90(void);
void func_0010f8b8(void);
void func_00106000(s32);
void func_0010a3c0(void);
void func_0011edc8(void);
void func_0010a320(void);
extern char D_0048CCC8[];
extern u8 D_00F20000_data[] __asm__("D_00F20000");
#define D_00F20000 D_00F20000_data
extern s32 D_002B6770;
extern s32 D_002B6774;
extern s32 D_002B647C;
extern s32 D_002B6474;
extern s32 D_002B6480;
extern s32 D_002C1360;
extern s32 D_002C1384;
extern s32 D_002BBE0C;
extern s32 D_002BBE04;
extern s32 D_002BBE14;
extern s32 D_002BBE18;
extern s32 D_002C5AD8;
extern s32 D_002C5AD4;
extern s32 D_002A6B80;
extern s32 D_002BCDA8;
extern s32 D_002BC128;
extern s32 D_002BCDDC;
#define inl_fin(k) { \
    D_002A6B80 = 1; \
    D_002BBDE0 = k; \
    D_00495160 = 0; \
    D_002BBE14 = 0; \
    D_002BBE04 = 3; \
    D_002BBE18 = 0; \
    func_001104e0(); \
    func_0010ff60(254); }
#define func_0015f018 ((void (*)(void)) func_0015f018)
#define func_0010fd40 ((void (*)(void)) func_0010fd40)
/* func_00109770: hand (strict). inl_fin as a plain-brace macro (not static inline), stores 6B80, BBDE0, 95160, BBE14, BBE04, BBE18. */
void func_00109770(void) {
    s32 k;
    func_00109388();
    func_001094f0();
    func_0015eda8();
    while (D_002BBE08 != 0) {
        switch (D_002BBDE0) {
        case 0:
            func_00120748(D_0048CCC8, D_00F20000, func_00109630, 0);
            D_002BBDE0 = 1;
            D_00495160 = 0;
            break;
        case 10:
            func_00232da0();
            func_001586a8(15);
            func_00111830();
            D_002B647C = 1;
            D_002B6474 = 1;
            goto c2;
        case 15:
            func_00111830();
            D_002B6480 = 1;
        case 2:
        c2:
            func_00109588();
        case 8:
        case 9:
            func_001095b0();
            break;
        case 4:
            D_002C1360 = 10000;
            D_002C1384 = 10000;
            func_0015f018();
            func_001ba870();
            D_002BBDE0 = 5;
            D_00495160 = 0;
            break;
        case 6:
            D_002C1360 = 10000;
            D_002C1384 = 10000;
            func_001ba7e0();
            D_002BBDE0 = 7;
            D_00495160 = 0;
            break;
        case 11:
            if (D_002B6774 == 0) {
                D_002BBE0C = 1;
                func_00111020(3);
                D_002BBDE0 = 12;
                D_00495160 = 0;
            }
            break;
        case 12:
            if (func_00111090() == 2) {
                func_00111060();
                D_002BBDE0 = 13;
                D_00495160 = 0;
            }
            break;
        case 13:
            if (D_002C5AD4 != 0) {
                inl_fin(14);
                break;
            }
            if (func_00111110() >= func_001110f0() - 1) {
                D_002A6B80 = 1;
            }
            if (func_00111090() == 4) {
                D_002A6B80 = 1;
                func_001104e0();
                func_0010ff60(254);
                D_002BBDE0 = 0;
                D_00495160 = 0;
            }
            break;
        case 16:
            if (D_002B6774 == 0) {
                D_002BBE0C = 1;
                func_00111020(5);
                D_002BBDE0 = 17;
                D_00495160 = 0;
            }
            break;
        case 17:
            if (func_00111090() == 2) {
                func_00111060();
                D_002BBDE0 = 18;
                D_00495160 = 0;
            }
            break;
        case 18:
            if (D_002C5AD8 & 8) {
                inl_fin(19);
                break;
            }
            if (func_00111110() >= func_001110f0() - 1) {
                D_002A6B80 = 1;
            }
            if (func_00111090() == 4) {
                D_002A6B80 = 1;
                func_001104e0();
                func_0010ff60(254);
                D_002BBDE0 = 0;
                D_00495160 = 0;
            }
            break;
        case 14:
        case 19:
            if (func_00111150() == 1) {
                D_002BBDE0 = 0;
                D_00495160 = 0;
            }
            break;
        }
        func_00105f28();
        func_0010fd40();
        func_00114880();
        if (func_00109658()) {
            func_001140a0();
            if (func_00114280()) {
                func_0010f918();
                func_0011eeb0();
                func_0011de90();
                func_0010f8b8();
                func_001104e0();
                func_00106000(D_002BBE04);
                if (D_00495160 != 0) {
                    D_00495160--;
                    func_0010a3c0();
                    if (D_00495160 == 0) {
                        func_0015ee10();
                        func_0011edc8();
                        func_0015eda8();
                        D_002BBDE0 = D_00495164;
                        switch (D_002BBDE0) {
                        case 8:
                            D_002BC128 = D_002BC148[2];
                            D_002BCDA8 = D_002BC148[3];
                            D_002BCDD8 = 1;
                            D_002BCDDC = 0;
                            break;
                        case 9:
                            D_002BC128 = (*(s32 (*)[4])&D_002BCDC8)[0];
                            D_002BCDA8 = (*(s32 (*)[4])&D_002BCDC8)[2];
                            D_002BCDD8 = 1;
                            D_002BCDDC = 1;
                            break;
                        }
                        func_001094f0();
                        func_0010a320();
                        D_002B6770 = 0;
                    }
                }
            }
        }
    }
    func_0015ee10();
}
#undef func_0015f018
#undef func_0010fd40
#undef inl_fin

