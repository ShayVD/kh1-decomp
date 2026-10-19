/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001158a8(M2C_UNK *, s32);
M2C_UNK func_00115940();
M2C_UNK func_0011c7a8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0011c7c0(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0011c838(M2C_UNK, s32, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0011cbe0(M2C_UNK, s32, s32, M2C_UNK *);
M2C_UNK func_0011e8d0(M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK, s32);
M2C_UNK func_00176388(M2C_UNK);
M2C_UNK sceDbcInit();
M2C_UNK scePad2Init(M2C_UNK);
M2C_UNK scePcStart(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK strcpy(s32, s32);
extern M2C_UNK D_002BCC28;
extern M2C_UNK D_002C5A88;
extern M2C_UNK D_004E2458;
M2C_UNK D_004E42C0[0x80] ALIGNED(64);
extern M2C_UNK func_001129c8;
extern M2C_UNK func_0011e700;
extern s32 D_002A62F0;
extern s32 D_002B6474;
extern s32 D_002BCB60;
extern s32 D_002BCDE4;
extern s32 D_002BCDEC;
extern s32 D_002C12C0;
extern s32 D_002C1364;
extern s32 D_002C1378;
extern s32 D_003F34A4;
extern s32 D_003F720C;
extern s32 D_004D9320;
extern s32 D_004D9330;
extern s32 D_004E44C0;
extern s8 D_002BCB68;
extern s8 D_002C1260;
extern volatile s32 D_002BBDF4;
extern volatile s32 D_002BD114;
s32 func_00104c38(s32, s32);
s32 func_00110360(void);
s32 func_0011a868(s32, s32, s32);
s32 func_0011aa18(s32, s32, s32);
s32 func_0011b0c0(s32, s32);
s32 func_0011cfa8(s32, s32, s32, s32, s32);
s32 func_0011ef10(s32, s32);
u32 func_00111b08();
u32 func_00232cc0(M2C_UNK);
u32 scePad2CreateSocket(M2C_UNK *, M2C_UNK *);
void func_00104f10(s32, s32);
void func_00109558(s32);
void func_00114810(void);
void func_00114820(void);
void func_00115408(s32, s32, s32, s32);
void func_00116628(s32);
void func_001178b8(s32);
void func_00118060(s32, s32, s32, s32);
void func_00118378(s32, s32, s32, s32);
void func_0011a978(s32, s32, s32);
void func_0011c5e8(void);
void func_0011c710(void);
void func_0011c778(void);
void func_0011c798(void);
void func_00122330(void);
void func_001c07a8(void);
void func_001c1f60(void);
void func_001c2ec8(s32, s32);

void func_00110448(s32 arg0) {
    D_002BBDF4 = arg0;
}

void func_00111288(void) {
    D_002BCB60 = func_00232cc0(3);
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
        M2C_FIELD((var_a5 + arg1 + D_002BCB60), s8 *, 0x6C) = (s8) arg2;
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
    return M2C_FIELD((var_a4 + arg1 + D_002BCB60), s8 *, 0x6C);
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
        func_001c2ec8(arg0, 0);
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

void func_00114f18(s32 arg0, s32 arg1) {
    if (arg1 == -1) {
        func_001178b8(arg0);
        return;
    }
    func_0011b0c0(arg1, arg0);
}

s32 func_00115018(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == -1) {
        return func_00104c38(arg1, arg2);
    }
    return func_0011a868(arg0, arg1, arg2);
}

void func_00115058(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == -1) {
        func_00104c38(arg1, arg2);
        return;
    }
    func_0011aa18(arg0, arg1, arg2);
}

void func_00115098(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == -1) {
        func_00104f10(arg1, arg2);
        return;
    }
    func_0011a978(arg0, arg1, arg2);
}

void func_001158c8(s32 arg0) {
    func_001158a8(&D_002C1260, arg0);
    func_001158a8(&D_002C1260 + 0x30, arg0 + 0xC);
    func_001158a8(&D_002C1260 + 0x10, arg0 + 4);
    func_001158a8(&D_002C1260 + 0x40, arg0 + 0x10);
    func_001158a8(&D_002C1260 + 0x20, arg0 + 8);
    func_001158a8(&D_002C1260 + 0x50, arg0 + 0x14);
}

void func_00116130(s32 arg0, s32 *arg1) {
    if (!(*arg1 & 0x106)) {
        func_00115940();
    }
}

void func_00116160(s32 arg0, s32 *arg1) {
    if ((*arg1 & 0x406) == 0x400) {
        func_00115940();
    }
}

void func_00116198(s32 arg0, s32 *arg1) {
    if ((*arg1 & 0xF6) == 0x20) {
        func_00115940();
    }
}

void func_001161d0(s32 arg0, s32 *arg1) {
    if (!(*arg1 & 0xE)) {
        func_00115940();
    }
}

void func_00116240(s32 arg0, s32 *arg1) {
    if (!(*arg1 & 0x10006)) {
        func_00115940();
    }
}

void func_00116278(s32 arg0, s32 *arg1) {
    if ((*arg1 & 0xF6) == 0x50) {
        func_00115940();
    }
}

void func_00116330(s32 arg0, u32 *arg1) {
    if (!(((u32) *arg1 >> 0x11) & 1)) {
        func_00115940();
    }
}

void func_00116660(s32 arg0) {
    func_00116628(arg0);
    M2C_FIELD(arg0, s16 *, 0x3C) = -1;
}

void func_00118548(s32 arg0) {
    if (D_002A62F0 != 0) {
        func_00118060(arg0, 9, 1, -1);
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x34) = -1;
    M2C_FIELD(arg0, s16 *, 0x30) = -1;
}

void func_00118590(s32 arg0, s32 arg1) {
    s16 temp_a0;

    func_00118378(arg0, 5, arg1, -1);
    if (D_002C12C0 != 0) {
        temp_a0 = M2C_FIELD(arg0, s16 *, 0x30);
        if ((temp_a0 != -1) && (M2C_FIELD(arg0, s32 *, 0x34) == -1)) {
            func_00115408((s32) temp_a0, arg0 + 0x20, arg0 + 0x24, 1);
        }
    }
}

void func_00118608(s32 arg0) {
    func_00118060(arg0, 3, 0, -1);
}

void func_00118628(s32 arg0, s32 arg1) {
    func_00118060(arg0, 3, 0, arg1);
}

void func_00118648(s32 arg0) {
    func_00118060(arg0, 0xA, 1, -1);
}

s32 func_0011ab38(s32 arg0, s32 arg1) {
    return *(M2C_UNK *)((s8 *)&D_004E2458 + (arg0 << 6)) + (arg1 * 0x14) + 0x10;
}

u8 func_0011ab60(s32 arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 0x14) + *(M2C_UNK *)((s8 *)&D_004E2458 + (arg0 << 6))), u8 *, 0xB);
}

s32 func_0011c630(void) {
    if (D_003F34A4 == 0) {
        if (D_003F720C == 1) {
            func_0011c5e8();
            func_00109558(0xF);
            func_001c07a8();
            return 4;
        }
        func_0011c710();
        return 4;
    }
    return 0;
}

void func_0011cf88(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s8 arg4, void *arg5, s32 arg6) {
    M2C_FIELD(arg5, s32 *, 0xC) = arg6;
    M2C_FIELD(arg5, s32 *, 0) = arg0;
    M2C_FIELD(arg5, s32 *, 0x10) = arg1;
    M2C_FIELD(arg5, s32 *, 4) = arg2;
    M2C_FIELD(arg5, s32 *, 8) = arg3;
    M2C_FIELD(arg5, s8 *, 0x16) = arg4;
    M2C_FIELD(arg5, s8 *, 0x15) = 0;
}

void func_0011d1e0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_0011cfa8(arg0, arg1, arg2, arg3, 0);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s8 *, 0x14) = 1;
    }
}

void func_0011d210(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_0011cfa8(arg0, arg1, arg2, arg3, 1);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s8 *, 0x14) = 2;
    }
}

void func_0011d240(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_0011cfa8(arg0, arg1, arg2, arg3, 2);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s8 *, 0x14) = 1;
    }
}

void func_0011d270(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_0011cfa8(arg0, arg1, arg2, arg3, 3);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s8 *, 0x14) = 2;
    }
}

void func_0011d2a0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_0011cfa8(arg0, arg1, arg2, arg3, 4);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s8 *, 0x14) = 2;
    }
}

void func_0011d768(s32 arg0) {
    func_0011c838(2, arg0, 0, 0x3FFF, 0x3FFF);
}

void func_0011e480(void) {
    func_0011c7c0(0, 0, 0x3C0);
    func_0011c7a8(1, 0, 0x3000, 0xF0, 0, 0xF0);
    D_002C1364 = 1;
}

void func_0011e7c8(s32 arg0, s32 arg1, s32 arg2) {
    func_0011cbe0(0, arg2, D_002C1378, &func_0011e700);
}

void func_0011e9a8(s32 arg0, s32 arg1) {
    func_0011e8d0(0, 0x3000, 0, arg0, 0, arg1);
}

void func_0011ea10(s32 arg0, s32 arg1) {
    func_0011e8d0(0, 0x3000, 0, arg0, 1, arg1);
}

void func_0011fa88(void) {
    sceDbcInit();
    scePad2Init(0);
    D_004E44C0 = scePad2CreateSocket(&D_002C5A88, &D_004E42C0);
}

s32 func_0011fad0(void) {
    scePcStart(0x8000F8DE, 0, 0);
    return 0;
}
