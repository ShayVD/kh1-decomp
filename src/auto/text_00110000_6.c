/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
M2C_UNK func_00176388(M2C_UNK);
M2C_UNK strcpy(s32, s32);
extern M2C_UNK D_002BCC28[];
M2C_UNK D_004E42C0[0x80] ALIGNED(64);
extern M2C_UNK func_001129c8;
extern s32 D_002B6474;
#include "data/pieces/D_002BCB60.h"
extern s32 D_002BCDE4;
extern s32 D_002BCDEC;
extern s32 D_004D9320;
extern s32 D_004D9330; /* src/data/bss_004D.c: u32 D_004D9330 */
extern s8 D_002BCB68;
#include "data/pieces/D_002BBDF4.h"
extern volatile s32 D_002BD114;
s32 func_00110360(void);
s32 func_0011ef10(s32, s32);
u32 func_00111b08();
u32 func_00232cc0(M2C_UNK);
void func_00114810(void);
void func_00114820(void);
void func_0011c778(void);
void func_0011c798(void);
void func_00122330(void);
#include "vm/script_vm.h"

void func_00110448(s32 arg0) {
    D_002BBDF4 = arg0;
}

void func_00111288(void) {
    D_002BCB60 = (Ctx_2bcb60 *)(func_00232cc0(3));
}

void func_00111600(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a3;
    s32 var_a5;
    s8 *temp_v0;

    if (arg0 != 0x14) {
        var_a3 = 0;
        var_a5 = 0;
        if (arg0 > 0) {
            do {
                temp_v0 = var_a3 + &D_002BCB68;
                var_a3 += 1;
                var_a5 += *temp_v0;
            } while (var_a3 < arg0);
        }
        M2C_FIELD((var_a5 + arg1 + ((s32)D_002BCB60)), s8 *, 0x6C) = (s8) arg2;
    }
}

s8 func_00111660(s32 arg0, s32 arg1) {
    s32 var_a2;
    s32 var_a4;
    s8 *temp_v0;

    var_a2 = 0;
    var_a4 = 0;
    if (arg0 > 0) {
        do {
            temp_v0 = var_a2 + &D_002BCB68;
            var_a2 += 1;
            var_a4 += *temp_v0;
        } while (var_a2 < arg0);
    }
    return M2C_FIELD((var_a4 + arg1 + ((s32)D_002BCB60)), s8 *, 0x6C);
}

u32 func_00111b10(void) {
    return func_00111b08() / 216000U;
}

void func_00112270(s32 arg0, s32 arg1) {
    strcpy(arg1, *(M2C_UNK *)((s8 *)&D_002BCC28 + (arg0 * 4)));
}

s32 func_00112ad8(void) {
    func_001c1f60();
    D_002B6474 = 0;
    func_00122330();
    func_0011ef10(0x2E62F, (s32) &func_001129c8);
    return 4;
}

void func_001134d8(s32 arg0) {
    D_002BCDE4 = arg0;
    if (arg0 != 0) {
        D_002BCDEC = 0;
        func_001c2ec8((s8 *) arg0, 0);
        return;
    }
    func_00110360();
}

void func_00114220(void) {
    func_00176388(1);
    D_004D9330 = 1;
    D_004D9320 = 1;
}

void func_00114840(void) {
    D_004D9320 = 0;
    D_004D9330 = 0;
    func_00114820();
    D_002BD114 = 0;
    func_00114810();
    func_0011c778();
    func_0011c798();
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_0048CF70[];
extern u8 D_0048CF78[];
extern u8 D_0048CF80[];
extern u8 D_0048CF88[];
extern u8 D_0048CF90[];
extern u8 D_0048CF98[];
extern u8 D_0048CFA0[];
extern u8 D_0048CFA8[];
extern u8 D_0048CFB0[];
extern u8 D_0048CFB8[];
extern u8 D_0048CFC0[];
extern u8 D_0048CFC8[];
extern u8 D_0048CFD0[];
extern u8 D_0048CFD8[];
extern u8 D_0048CFE0[];
extern u8 D_0048CFE8[];
extern u8 D_0048CFF0[];
M2C_UNK D_002BCC28[0x16] ALIGNED(8) = {
    (s32)D_0048CFF0, (s32)D_0048CFE8, (s32)D_0048CFE0, (s32)D_0048CFD8,
    (s32)D_0048CFD0, (s32)D_0048CFC8, (s32)D_0048CFC0, (s32)D_0048CFB8,
    (s32)D_0048CFB0, (s32)D_0048CFA8, (s32)D_0048CFA0, (s32)D_0048CF98,
    (s32)D_0048CF90, (s32)D_0048CF88, (s32)D_0048CFB8, (s32)D_0048CF80,
    (s32)D_0048CF78, (s32)D_0048CFB8, (s32)D_0048CFB8, (s32)D_0048CFB8,
    (s32)D_0048CF70, 0,
};
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/data_003F.h"
#include "data/data_0048.h"
#include "data/pieces/D_002BD114.h"
