/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_004D.h"

M2C_UNK D_00F20000(M2C_UNK, M2C_UNK);
M2C_UNK func_00109558(M2C_UNK);
M2C_UNK func_0010fea0();
M2C_UNK func_001100a8();
M2C_UNK func_001104c0();
M2C_UNK func_00112270(s32, M2C_UNK *);
M2C_UNK func_00114820();
M2C_UNK func_0011cb08(void *);
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_00120748(void *, s32, M2C_UNK *, M2C_UNK);
M2C_UNK func_001ec7d0(M2C_UNK);
M2C_UNK func_001ed128(M2C_UNK, M2C_UNK);
M2C_UNK func_002485d0();
M2C_UNK func_002485e0();
M2C_UNK func_0024b138();
M2C_UNK func_00265350(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_002654f0();
M2C_UNK func_00266c30(M2C_UNK);
M2C_UNK func_00267fe0();
M2C_UNK func_0026aaa0();
M2C_UNK func_0026ab38();
M2C_UNK func_0026abf0();
M2C_UNK sceCdRead(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK sceIpuInit();
M2C_UNK sceIpuSync();
M2C_UNK sprintf(M2C_UNK *, M2C_UNK *, s32);
M2C_UNK strcat(M2C_UNK *, M2C_UNK *);
M2C_UNK strcpy(M2C_UNK *, M2C_UNK *);
extern M2C_UNK D_002BCC80;
extern M2C_UNK D_002BCC88;
#include "data/pieces/D_002BCCA0.h"
#include "data/pieces/D_002BCCE0.h"
extern M2C_UNK D_002BCD20;
#include "data/pieces/D_002BCD60.h"
extern M2C_UNK D_0048CFF8;
extern M2C_UNK D_0048D000;
extern M2C_UNK func_001017e8;
extern M2C_UNK func_00112840;
extern M2C_UNK func_00113558;
extern f32 D_002BBDEC;
extern s32 D_002A3F40;
extern s32 D_002A3F44;
extern s32 D_002BBE04;
extern s32 D_002BBE0C;
extern s32 D_002BBE18;
extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_002BCAE0;
extern s32 D_002BCB34;
extern s32 D_002BCDC0;
extern s32 D_004D8EC0[];
extern s32 D_004D90FC;
extern s32 D_004D9280;
extern s32 D_004D92E0;
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC070.h"
extern volatile s32 D_002BD114;
extern volatile s32 D_002C5AD0[];
extern volatile s32 D_002C5BB0[];
s32 func_0011d768(s32, f32, f32, f32, f32, f32, f32, f32, f32);
s32 func_001559f0(M2C_UNK, M2C_UNK);
void func_001017b8(void);
void func_00111130(void);
void func_00113e28(s32);
void func_00114830(void);
void func_001edb48(s32);

void func_00110020(s32 arg0, s32 arg1) {
    D_004D90FC = 1;
    D_004D8EC0[6] = (s32) ((((D_004D8EC0[6] & ~0xFFF) | (arg0 & 0xFFF)) & 0xFF800FFF) | ((arg1 & 0x7FF) << 0xC));
}

void func_00110068(void) {
    func_002654f0();
    func_00266c30(1);
    func_00267fe0();
    D_002BBDEC = 1.0f;
    func_0010fea0();
}

void func_001101e8(void) {
    func_00265350(0, 1, 2, 0);
    func_001104c0();
    func_001100a8();
}

void func_00110360(void) {
    D_002BC070[0] = 0x80;
    D_002BC070[3] = 0x80;
    D_002BC070[2] = 0x80;
    D_002BC070[1] = 0x80;
}

void func_00110380(void) {
    D_002BC070[0] = 0;
    D_002BC070[3] = 0;
    D_002BC070[2] = 0;
    D_002BC070[1] = 0;
}

void func_00111150(void) {
    D_00F20000(5, 0);
}

void func_001111b0(void) {
    if ((D_002BBDE0 == 3) && (D_002A3F44 == 1)) {
        D_002A3F44 = 0;
        func_001017b8();
    }
    func_001edb48(9);
    func_00114830();
    D_002BBE04 = 3;
    D_002BBE18 = 0;
    func_00111130();
    D_002BCAE0 = 0;
    D_002BCB34 = 1;
    func_00113e28(0);
}

void func_00111238(void) {
    sceCdRead(0, 0, 0, 0);
    func_0024b138();
    func_0026ab38();
    func_0026abf0();
    func_0026aaa0();
    sceIpuInit();
    sceIpuSync();
}

void func_00112230(void) {
    D_004D9280 = 1;
    func_002485d0();
    func_002485e0();
}

void func_00112258(void) {

}

void func_00112320(void) {
    s32 sp[20];
    func_00112270(D_002BC128, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    sprintf(sp, &D_0048CFF8, D_002BC130 + 1);
    if (M2C_FIELD(sp, s8 *, 0x0) == 0x20) {
        M2C_FIELD(sp, s8 *, 0x0) = 0x30;
    }
    strcpy((M2C_UNK *)&D_002BCCA0, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    strcat((M2C_UNK *)&D_002BCCA0, &D_002BCC80);
    strcpy((M2C_UNK *)&D_002BCD60, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    strcat((M2C_UNK *)&D_002BCD60, sp);
    strcat((M2C_UNK *)&D_002BCD60, &D_002BCC88);
    strcpy(&D_002BCD20, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    strcat(&D_002BCD20, sp);
}

void func_00112400(s32 arg0) {
    s32 sp[20];
    func_00112270(D_002BC128, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    sprintf(sp, &D_0048CFF8, arg0 + 1);
    if (M2C_FIELD(sp, s8 *, 0x0) == 0x20) {
        M2C_FIELD(sp, s8 *, 0x0) = 0x30;
    }
    strcpy((M2C_UNK *)&D_002BCCE0, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    strcat((M2C_UNK *)&D_002BCCE0, &D_0048D000);
    strcat((M2C_UNK *)&D_002BCCE0, sp);
}

void func_00112820(void) {
    func_0011ef10(0xC350, &func_001017e8);
}

void func_00112928(void) {
    s32 sp[16];
    func_0011cb08(sp);
    func_00120748(sp, func_001559f0(0x34, 4), &func_00112840, 0);
}

void func_00112c08(s32 arg0) {
    D_002A3F40 = arg0;
    D_002BCDC0 = 1;
}

void func_00112e98(void) {
    func_001ec7d0(2);
    func_001ed128(3, -9);
    func_001ed128(0, -1);
    func_001ed128(3, -1);
    func_001ed128(0, 0);
    func_001ed128(0, 1);
    func_001ed128(1, 0);
    func_001ed128(1, 1);
    func_001ed128(0, -8);
    func_001ed128(3, -8);
    func_001ed128(0, -3);
    func_001ed128(3, -3);
    func_001ed128(0, -4);
    func_001ed128(3, -4);
    func_001ed128(0, -5);
    func_001ed128(3, -5);
    func_001ed128(0, -6);
    func_001ed128(3, -6);
    func_001ed128(0, -7);
    func_001ed128(3, -7);
    func_001ed128(3, -0xA);
}

void func_00112fa0(void) {
    func_00114820();
    func_00109558(9);
}

s32 func_00112fc0(void) {
    return D_004D92E0;
}

void func_00113688(void) {
    func_0011ef10(0xC2EC, &func_00113558);
}

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

void func_00114250(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4, f32 fparg5, f32 fparg6, f32 fparg7) {
    D_002BD114 = 1;
    D_002BBE0C = 0;
    func_0011d768(6, fparg0, fparg1, fparg2, fparg3, fparg4, fparg5, fparg6, fparg7);
}
#include "data/bss_004D_mixed.h"
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/data_0048.h"
#include "data/data_002C.h"
#include "data/pieces/D_002BBDEC.h"
#include "data/pieces/D_002BBE04.h"
#include "data/pieces/D_002BC128.h"
#include "data/pieces/D_002BD114.h"
