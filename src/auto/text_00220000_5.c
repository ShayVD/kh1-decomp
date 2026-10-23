/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
M2C_UNK func_001f36b8(s32);
M2C_UNK func_00205938(s32, M2C_UNK);
extern f32 D_002BBDFC;
extern f32 D_006469B8; /* src/data/bss_0064.c: s32 D_006469B8[0x6] */
s32 func_001f4400();
void func_001f9438(s32, s32, s32, s32, s32, s32, s32);

void func_0022d398(s32 arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8 != 0.0f)) {
        temp_f0 = D_006469B8 - D_002BBDFC;
        D_006469B8 = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_00205938(arg0, 0x33000000);
}

void func_0022da10(s32 arg0) {
    func_001f9438(arg0, 2, 0x100, 0x90, 0x5F, 0x12, 0x801E4696);
}

void func_0022de50(s32 arg0) {
    func_001f9438(arg0, 2, 0x100, 0x90, 0x1CE, 0x12, 0x801E4696);
}
#include "data/pieces/D_002BBDFC.h"
