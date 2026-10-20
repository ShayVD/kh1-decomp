/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0057.h"

extern M2C_UNK D_002C58A0;
extern M2C_UNK D_002C58D0;
extern M2C_UNK D_0035BD40;
extern M2C_UNK D_00362660;
extern M2C_UNK D_00362670;
extern M2C_UNK D_00575310; /* src/data/bss_0057.c: TalkEA D_00575310 */
extern f32 D_005758C0;
extern s32 D_002E26A0;
extern s32 D_0035C6F0;
extern void *D_00575894;
f32 func_00120c88(f32);
f32 func_001224c8(s32, s32, s32, f32);
s32 func_001226f0(s32, s32, s32);
s32 func_00153d78();
s32 func_00232cc0(M2C_UNK);
void func_00121eb0(s32);
void func_0016f3d0(s32, s32);
void func_0017f178();
void func_00181b30(void);
void func_002672f8(M2C_UNK *, void *, M2C_UNK *);
void func_00267518(s32, M2C_UNK *, M2C_UNK *);
void func_002675a8(M2C_UNK *, M2C_UNK *);
void func_00267768(void *, M2C_UNK *, f32);
void func_00267810(void *, void *, f32);

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
    *(M2C_UNK *)((s8 *)(s8 *)&D_0035BD40 + (*(M2C_UNK *)temp_s0 * 4)) = 0;
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

s32 func_00175b70(void) {
    if (D_0035C6F0 == 0) {
        return 0;
    }
    func_00181b30();
    return 0;
}

void func_00177900(s32 arg0, M2C_UNK *arg1, f32 fparg0) {
    s32 sp[20];    f32 temp_f20;

    func_0017f178();
    func_002672f8(arg1, D_002E26A0 + 0xD0, &D_00362670);
    temp_f20 = func_00120c88(fparg0);
    func_00267768(sp, &D_002C58D0, func_00120c88(M2C_FIELD(&D_00362660, f32 *, 0)));
    func_00267810(sp, sp, temp_f20);
    func_002675a8(&M2C_FIELD(sp, M2C_UNK *, 0x40), &D_002C58A0);
    M2C_FIELD(sp, f32 *, 0x48) = M2C_FIELD(&D_00362660, f32 *, 0xC);
    func_002672f8(&M2C_FIELD(sp, M2C_UNK *, 0x40), sp, &M2C_FIELD(sp, M2C_UNK *, 0x40));
    func_00267518(arg0, arg1, &M2C_FIELD(sp, M2C_UNK *, 0x40));
}

void func_00179690(void) {
    M2C_FIELD(D_00575894, s32 *, 0) = (s32) (M2C_FIELD(D_00575894, s32 *, 0) | 1);
    if (D_005758C0 > 0.0f) {
        M2C_FIELD(D_00575894, f32 *, 0x64) = (f32) (1.0f / (D_005758C0 * 0.6f));
        return;
    }
    M2C_FIELD(D_00575894, f32 *, 0x64) = 1.0f;
}
#include "data/bss_0057_mixed.h"
#include "data/data_0035.h"
