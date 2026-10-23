/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00122768(M2C_UNK *);
M2C_UNK func_00122bd8();
M2C_UNK func_0012cb40(M2C_UNK *, s32, s32);
M2C_UNK func_001318e8(s32, s32, void *);
M2C_UNK func_00146380(s32, s32, M2C_UNK);
M2C_UNK func_0024f318(s32, M2C_UNK *, s32, M2C_UNK, M2C_UNK *);
M2C_UNK func_002672f8(s32, void *, s32);
M2C_UNK func_00267518(s32, s32, void *);
M2C_UNK func_002675a8(s32, s32);
M2C_UNK func_002676c0(void *, M2C_UNK *, f32);
M2C_UNK func_00267810(void *, M2C_UNK *, f32);
M2C_UNK func_00267e90(void *, s32, f32);
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002C5C80.h"
extern M2C_UNK D_002E2FD8;
extern M2C_UNK D_004E4A00; /* src/data/bss_004E.c: FileEnt D_004E4A00[0xe00] */
extern M2C_UNK func_00120170;
extern f32 D_002BBDFC;
#include "data/pieces/D_002E2700.h"
extern s32 D_002C5C30;
extern s32 D_00524F44; /* src/data/bss_0052.c: u32 D_00524F44 */
f32 atan2f(f32, f32);
f32 func_00120c88(f32);
s32 func_001200f8();
s32 func_00122ff8(s32);
s32 func_00123488();

void func_00120190(void) {
    func_0024f318(func_001200f8(), &D_004E4A00, D_002C5C30, 0x10, &func_00120170);
}

void func_00122c08(void) {
    s8 *var_s0;
    s32 var_s1;

    var_s0 = &D_002C5C80;
    var_s1 = 0x1E;
    do {
        if ((M2C_FIELD(var_s0, s32 *, 0) != 0) && (M2C_FIELD(var_s0, s32 *, 4) & 8)) {
            func_00122768(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x40;
    } while (var_s1 >= 0);
    func_00122bd8();
}

void func_00123b10(s32 arg0, s32 arg1) {
    func_002675a8(func_00123488() + 0x40, arg1);
}

void func_00129068(void *arg0) {
    s32 sp[16];
    s32 temp_a0;

    func_00267810(sp, ((M2C_UNK *)&D_002C58D0), func_00120c88((M2C_FIELD(arg0, f32 *, 4) / 180.0f) * 3.141592979f));
    temp_a0 = M2C_FIELD(arg0, s32 *, 0);
    func_002672f8(temp_a0, sp, temp_a0);
}

void func_001290d8(void *arg0) {
    s32 sp[16];
    s32 temp_a0;

    func_002676c0(sp, ((M2C_UNK *)&D_002C58D0), func_00120c88((M2C_FIELD(arg0, f32 *, 4) / 180.0f) * 3.141592979f));
    temp_a0 = M2C_FIELD(arg0, s32 *, 0);
    func_002672f8(temp_a0, sp, temp_a0);
}

void func_00129148(void *arg0) {
    s32 sp[4];
    s32 temp_a0;

    func_00267e90(sp, M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, f32 *, 8) * D_002BBDFC);
    temp_a0 = M2C_FIELD(arg0, s32 *, 0);
    func_00267518(temp_a0, temp_a0, sp);
}

void func_00129b70(void *arg0) {
    s32 sp[16];
    func_001318e8(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 8) | 0x1000, sp);
    func_002672f8(M2C_FIELD(arg0, s32 *, 0xC), sp, M2C_FIELD(arg0, s32 *, 4));
}

void func_00129c88(s32 *arg0) {
    *arg0 = func_00122ff8(*arg0);
}

void func_0012a530(void *arg0) {
    func_002675a8(*M2C_FIELD(arg0, s32 **, 0), M2C_FIELD(arg0, s32 *, 4));
}

void func_0012a608(void *arg0) {
    func_002675a8(M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 8), M2C_FIELD(arg0, s32 *, 4));
}

void func_0012a6c0(f32 *arg0) {
    *arg0 = atan2f(D_002E2700[0][2], D_002E2700[2][2]);
}

void func_0012b260(void *arg0) {
    func_00146380(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), 1);
}

s32 func_0012cc38(s32 arg0, s32 arg1) {
    if (!(((s32) D_00524F44 >> arg0) & 1)) {
        func_0012cb40(&D_002E2FD8, arg0, arg1);
        D_00524F44 |= 1 << arg0;
        return 1;
    }
    return 0;
}
#include "data/data_002C.h"
#include "data/pieces/D_002BBDFC.h"
