/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0062.h"
#include "data/bss_0063.h"

M2C_UNK func_00111be8();
M2C_UNK func_00147840();
M2C_UNK func_001ef948();
M2C_UNK func_001efaa8();
M2C_UNK func_001efc10(u16);
M2C_UNK func_001efd20(s32, s32);
M2C_UNK func_001f2eb8();
M2C_UNK func_0020d748();
M2C_UNK func_0022bd20();
M2C_UNK func_0022d138();
M2C_UNK func_0022d728();
M2C_UNK func_0022db90();
M2C_UNK func_0022dfd0();
M2C_UNK func_0022e458();
M2C_UNK func_0022ebe8();
M2C_UNK func_0022ebf0();
M2C_UNK func_002319c0();
M2C_UNK func_00232790();
M2C_UNK func_00232ac8();
M2C_UNK func_00233610();
M2C_UNK func_00233a80();
#include "data/pieces/D_003DC390.h"
extern M2C_UNK D_003E3CB8;
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_003DABD0.h"
extern s32 D_003DD258;
extern s32 D_003DD28C;
f32 func_001edc50(s32);
f32 func_001edcd8(f32);
s32 func_001efc68();
#include "vm/script_vm.h"
void memset(s32, s32, s32);

/* func_001e07a8, func_001e0d68, func_001e1088, func_001e10b8, func_001e1438, func_001e1480, func_001e1688, func_001e1bf8, func_001e2470 are in src/screen/screen.c. */









/* func_001e27b0, func_001e2f88, func_001e3178, func_001e3a98, func_001e3b28, func_001e3da8, func_001e4048, func_001e4250, func_001e4558 are in src/shop/shop.c. */









/* func_001e6388, func_001e6438, func_001e64e0, func_001e6c68, func_001e6e08, func_001e7d80 are in src/list/list.c. */






/* func_001e7e78, func_001e8060, func_001e8388, func_001e86a0 are in src/event/sound.c. */




/* func_001e92b8 is in src/screen/wave.c. */

/* func_001e9dc8 is in src/vm/vm_util.c. */

/* func_001ea580 is in src/vm/vm_ent.c. */

void func_001ee470(void) {
    func_00111be8();
}

s32 func_001ee488(u32 arg0) {
    s32 temp_v1;
    s32 var_a1;
    s32 var_lo;
    u32 var_a0;

    var_a0 = arg0;
    var_lo = 0;
    var_a1 = 1;
    do {
        temp_v1 = var_a0 & 0xF;
        var_a0 = var_a0 >> 4;
        var_lo += temp_v1 * var_a1;
        var_a1 *= 0xA;
    } while (var_a0 != 0);
    return var_lo;
}

void func_001ee520(void) {
    func_00233610();
    func_00233a80();
    func_001efaa8();
    func_001f2eb8();
    func_001ef948();
    func_0020d748();
    func_0022bd20();
    func_0022d138();
    func_0022d728();
    func_0022db90();
    func_0022dfd0();
    func_0022e458();
    func_0022ebe8();
    func_0022ebf0();
    func_002319c0();
    func_00232790();
    func_00232ac8();
}

void func_001ee5b8(void) {
    s32 sp[4];
    memset((s32) sp, 0, 0x10);
    func_001edc50((s32) sp);
    func_001edcd8(0.0f);
}

void func_001ee618(s32 arg0) {
    func_001efc10(*(M2C_UNK *)((s8 *)(s8 *)&D_003E3CB8 + (M2C_FIELD((arg0 + ((s32)D_00304BE8)), u8 *, 0x48E) * 2)));
}

void func_001ee680(void) {
    func_00147840();
}

void func_001efc80(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001efd20(func_001efc68(), arg3);
}
#include "data/data_003D.h"
#include "data/data_003F.h"
#include "data/data_003E.h"
#include "data/pieces/D_003DD258.h"
#include "data/pieces/D_003DD28C.h"
