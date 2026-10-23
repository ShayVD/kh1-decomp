/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK func_001efbb8(s32);
M2C_UNK func_00206ea8(s32);
M2C_UNK func_00207140(s32);
M2C_UNK func_00219288();
M2C_UNK func_002192c0();
M2C_UNK func_0021b820();
M2C_UNK func_0021c780(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_0021cb00(s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0021cb88(s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
#include "data/pieces/D_003F34B8.h"
extern s32 D_003F34C8;
extern s32 D_003F34CC;
extern s32 D_003F34F0;
extern s32 D_003F350C;
extern s32 D_00643110;
extern s32 D_00643114;
extern u16 D_003F5C60;
s32 func_0010ef90(s32, s32);
#include "vm/script_vm.h"
s32 func_00219440();
void func_0010eee0(s32, s32, s32, s32);
void func_001eb0a0(s32, s32);
void func_00207830(s32, s32, s32, s32, s32, s32, s32);
void func_0021c450(s32, s32, s32, s32);

void func_00218f58(s32 arg0) {
    func_00207830(arg0, 4, 2, 0, 0, 0x7A, 0x6D);
}

void func_00219298(void) {
    func_00219288();
}

void func_002192b0(s32 arg0) {
    *(*(s32 **)&D_003F34B8) = arg0;
}

void func_002192d0(void) {
    func_002192c0();
}

void func_00219458(void) {
    func_001efbb8(func_00219440());
}

void func_002194d0(void) {
    D_003F34CC += 1;
    D_003F34C8 -= 1;
}

void func_0021ccd0(s32 arg0, s32 arg1) {
    s32 sp[4];
    s32 temp_v0;
    u32 temp_a0;

    func_0021c450(arg0, 0x14, 0x59, 0xDC);
    temp_v0 = (s32) func_001c2df0((s8 *) D_003F34F0, arg1);
    temp_a0 = 0xDC - func_0010ef90(temp_v0, (s32) sp);
    func_0010eee0(((s32) (temp_a0 + (temp_a0 >> 0x1F)) >> 1) + 0x14, 0x7F - (M2C_FIELD(sp, M2C_UNK *, 0x0) * 0xE), M2C_FIELD(arg0, s32 *, 0x90), temp_v0);
}

s32 func_0021dbb8(void) {
    s32 temp_v0;
    u16 *var_s0;
    u16 temp_a0;
    u32 var_s1;

    var_s0 = &D_003F5C60;
    var_s1 = 0;
    do {
        temp_a0 = *var_s0;
        var_s0 += 1;
        func_001eb0a0((s32) temp_a0, 1);
        var_s1 += 1;
        temp_v0 = var_s1 < 0x17U;
    } while (temp_v0 != 0);
    return temp_v0;
}

void func_0021e508(void) {
    D_003F350C += 1;
    D_003F34C8 -= 1;
}

void func_0021e890(void) {

}

void func_0021ed48(void *arg0) {
    func_00207140(M2C_FIELD(arg0, s32 *, 0x40));
}

void func_0021f390(s32 arg0) {
    func_0021b820();
    func_0021cb88(arg0, 0xB0, 8, 0x140, 1);
}

void func_0021f3c8(s32 arg0) {
    func_0021b820();
    func_0021c780(arg0, 0x10, 0x48);
    func_0021cb00(arg0, 0x118, 0x6C, 9, 0x1E);
}

void func_0021f810(s32 arg0) {
    func_0021b820();
    func_0021c780(arg0, 0x10, 0x48);
    func_0021cb00(arg0, 0x118, 0x6C, 9, 0x1E);
}

void func_0021faf8(s32 arg0) {
    D_00643110 = arg0;
    D_00643114 = 0;
}

void func_0021ff50(void *arg0) {
    func_00206ea8(M2C_FIELD(arg0, s32 *, 0x24));
}
#include "data/data_003F.h"
#include "data/pieces/D_003F34C8.h"
