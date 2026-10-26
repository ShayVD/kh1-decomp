/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00FA6A88;
extern s32 D_00F21C34;
extern s32 D_00F21C38;
extern s32 D_00F21C44;
s32 func_00148768(s32, s32, s32, s32, f32);
s32 func_00148968(s32, s32, s32);
s32 func_00f20140(void);
s32 sceVu0CopyVector(s32, s32);

void func_00f201d8(void) {
    func_00148968(D_00F21C38, D_00F21C44, 9);
    func_00148968(D_00F21C38, D_00F21C44, 8);
    M2C_FIELD(&D_00FA6A88, s32 *, 0) = func_00148968(D_00F21C38, D_00F21C44, 1);
    M2C_FIELD(&D_00FA6A88, s32 *, 4) = func_00148768(D_00F21C44, 2, D_00F21C34, 0x30, 1.0f);
    func_00f20140();
}

void func_00f21ad0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_hi;
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 8);
    temp_hi = (s32) ((M2C_FIELD(arg0, s32 *, 0xC) - arg1) + temp_v1) % temp_v1;
    M2C_FIELD(arg0, s32 *, 0x10) = temp_hi;
    sceVu0CopyVector(arg2, M2C_FIELD(arg0, s32 *, 0) + (temp_hi * 0x10));
}
