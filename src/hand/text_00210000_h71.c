#include "common.h"
#include "data/bss_0064.h"
#include "data/pieces/D_003F2C40.h"
typedef E20_3F2C40 E20;
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);

#include "data/pieces/D_003F34C4.h"
typedef f32 Mtx[4][4];
void func_0021b820(void);
extern s32 D_00643200[];
s32 func_0021b800(s32);
s32 func_00207088(s32);

extern s32 D_00643200[];
s32 func_00207088(s32);
s32 D_006435E8[0xa] ALIGNED(8);
s32 D_00643610[0xa] ALIGNED(16);
s32 D_00643638[0xa] ALIGNED(8);
extern s32 D_0064342C;
extern s32 D_00643430[];
#include "data/pieces/D_003F61E0.h"
s32 D_006435BC ALIGNED(4);
s32 D_006435C0[0xa] ALIGNED(16);
extern s32 D_003F5C3C;
s32 func_001eb318(s32);

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

#include "data/pieces/D_003E8E08.h"
void func_0021b820(void);
void func_0021c9a0(void *, s32, s32);
void func_0021cb00(void *, s32, s32, s32, s32);
s32 func_002207f0(s32);
s32 func_0021b800(s32);

void func_002208b8(void *a) {
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
void func_0021cb00(void *, s32, s32, s32, s32);
#include "vm/script_vm.h"

#include "data/data_003F.h"
#include "data/data_003E.h"
