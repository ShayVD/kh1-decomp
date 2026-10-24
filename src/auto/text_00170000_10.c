/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0057.h"
#include "data/pieces/D_0035BD40.h"
extern M2C_UNK D_00575310; /* src/data/bss_0057.c: TalkEA D_00575310 */
f32 func_001224c8(s32, s32, s32, f32);
s32 func_001226f0(s32, s32, s32);
s32 func_00153d78();
s32 func_00232cc0(M2C_UNK);
void func_00121eb0(s32);
void func_0016f3d0(s32, s32);

s32 func_00170dd8(s32 arg0, s32 arg1) {
    s32 var_v0;
    u32 *temp_a0;

    temp_a0 = func_00232cc0(6) + (arg0 * 4);
    var_v0 = -1;
    if (arg1 == -1) {
        return var_v0;
    }
    var_v0 = ((u32) *temp_a0 >> (arg1 * 2)) & 3;
    return var_v0;
}

void func_00170e48(s32 arg0) {
    s32 temp_s0;

    temp_s0 = M2C_FIELD(arg0, s32 *, 0x144);
    func_0016f3d0(arg0, temp_s0);
    *(M2C_UNK *)((s8 *)(s8 *)&D_0035BD40.i + (*(M2C_UNK *)temp_s0 * 4)) = 0;
    func_00121eb0(M2C_FIELD(arg0, s32 *, 0x144));
}

void func_00170fa8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0) {
    if ((*(M2C_UNK *)((s32) ((*(M2C_UNK *)arg1 * 8)) + (s32) &D_00575310) != 0) || (*(M2C_UNK *)((s32) ((*(M2C_UNK *)arg1 * 8)) + (s32) &D_00575310) = func_001226f0(1, 9, 0xA), (*(M2C_UNK *)((s32) ((*(M2C_UNK *)arg1 * 8)) + (s32) &D_00575310) != 0))) {
        func_001224c8(*(M2C_UNK *)((s32) ((*(M2C_UNK *)arg1 * 8)) + (s32) &D_00575310), arg3, 0, fparg0);
        M2C_FIELD(((s8 *)&D_00575310 + (*(M2C_UNK *)arg1 * 8)), s32 *, 4) = arg2;
    }
}

s32 func_00171ef0(s32 *arg0) {
    s32 var_v0;

    var_v0 = func_00153d78();
    if (!((var_v0 != 0) || (*arg0 & 0x200))) {
        return var_v0;
    }
    var_v0 = 1;
    return var_v0;
}
#include "data/bss_0057_mixed.h"
#include "data/data_0035.h"
