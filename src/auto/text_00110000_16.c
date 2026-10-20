/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_004D.h"

extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_002BC134;
extern s32 D_002BCAE0;
extern s32 D_002BCDA0;
extern s32 D_002BCDA8;
extern s32 D_004D9244;
f32 func_001195d8(s32, s32);
s32 func_00111660(s32, s32);
s32 func_00112b18(void);
s32 func_001191c8(s32, s32, s32);
s32 func_0011c338(s32, s32, s32, s32, s32, s32);
void D_00F20000(M2C_UNK, s32);
void FlushCache(M2C_UNK);
void func_00115940(s32);

void func_00110fc8(void) {
    D_002BCAE0 = 1;
    FlushCache(2);
    D_00F20000(0, D_004D9244);
}

void func_00112bb8(s32 arg0) {
    s32 temp_v0;

    D_002BCDA8 = arg0;
    temp_v0 = *(M2C_UNK *)((s32) ((arg0 << 6)) + (s32) D_002BCDA0);
    D_002BC130 = temp_v0;
    D_002BC134 = func_00111660(D_002BC128, temp_v0);
    func_00112b18();
}

void func_00116200(s32 arg0, s32 arg1) {
    u64 temp_a1;

    temp_a1 = (u64) *(u8 *)arg1 >> 4;
    if ((temp_a1 != 7) && (temp_a1 != 5)) {
        func_00115940(arg0);
    }
}

void func_001162b0(s32 arg0, s32 arg1) {
    u64 temp_a1;

    temp_a1 = (u64) *(u8 *)arg1 >> 4;
    if ((temp_a1 != 7) && (temp_a1 != 9) && (temp_a1 != 5)) {
        func_00115940(arg0);
    }
}

s32 func_00119710(s32 arg0) {
    s32 sp[16];    s32 temp_s1;
    s32 var_v0;

    func_001195d8(arg0, (s32) sp);
    temp_s1 = func_0011c338((s32) sp, arg0, arg0 + 0x10, (s32) &M2C_FIELD(sp, M2C_UNK *, 0x20), -1, (s32) &M2C_FIELD(sp, M2C_UNK *, 0x30));
    var_v0 = func_001191c8((s32) sp, arg0, 8);
    if (!((temp_s1 != -1) || (var_v0 != temp_s1))) {
        return var_v0;
    }
    var_v0 = 1;
    return var_v0;
}
