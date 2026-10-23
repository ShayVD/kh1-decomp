/* func_00109770: hand (strict). inl_fin as a plain-brace macro (not static inline), stores 6B80, BBDE0, 95160, BBE14, BBE04, BBE18. */
#include "common.h"

void func_00109388(void);
void func_001094f0(void);
void func_0015eda8(void);
void func_0015ee10(void);
void func_00120748(void *, void *, void (*)(void), s32);
void func_00109630(void);
void func_00232da0(void);
void func_001586a8(s32);
s32 func_00111830(void);
void func_00109588(void);
void func_001095b0(void);
void func_0015f018(void);
void func_001ba870(void);
void func_001ba7e0(void);
void func_00111020(s32);
s32 func_00111090(void);
void func_00111060(void);
s32 func_00111110(void);
s32 func_001110f0(void);
void func_001104e0(void);
void func_0010ff60(s32);
s32 func_00111150(void);
void func_00105f28(void);
void func_0010fd40(void);
void func_00114880(void);
s32 func_00109658(void);
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
extern u8 D_00F20000[];
extern volatile s32 D_002BBE08;
#include "data/pieces/D_002BBDE0.h"
extern volatile s32 D_00495160;
extern volatile s32 D_00495164;
extern s32 D_002B647C, D_002B6474, D_002B6480, D_002B6774, D_002B6770;
extern s32 D_002C1360, D_002C1384;
extern s32 D_002BBE0C, D_002BBE04, D_002BBE14, D_002BBE18;
extern s32 D_002C5AD4, D_002C5AD8;
extern s32 D_002A6B80;
#include "data/pieces/D_002BC148.h"
#include "data/pieces/D_002BCDC8.h"
extern s32 D_002BCDA8, D_002BC128, D_002BCDD8, D_002BCDDC;

#define inl_fin(k) { \
    D_002A6B80 = 1; \
    D_002BBDE0 = k; \
    D_00495160 = 0; \
    D_002BBE14 = 0; \
    D_002BBE04 = 3; \
    D_002BBE18 = 0; \
    func_001104e0(); \
    func_0010ff60(254); }

/* rodata */
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

#include "data/bss_0049_mixed.h"
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/data_0048.h"
#include "data/pieces/D_002C5AD0.h"
#include "data/pieces/D_002BBE04.h"
#include "data/pieces/D_002BC128.h"
