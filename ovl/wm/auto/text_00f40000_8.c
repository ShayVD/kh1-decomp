/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_002BC080;
extern f32 D_002BC098;
extern s32 D_002BBE04;
extern s32 D_002BC090;
extern s32 D_002BC094;
extern s32 D_002BC09C;
extern s32 D_002BC0A0;
extern s32 D_002BC0A4;

void func_00f43d10(void) {
    D_002BBE04 = 4;
    M2C_FIELD(&D_002BC080, s32 *, 0) = 0x80;
    M2C_FIELD(&D_002BC080, s32 *, 4) = 0x80;
    M2C_FIELD(&D_002BC080, s32 *, 8) = 0x80;
    M2C_FIELD(&D_002BC080, s32 *, 0xC) = 0x70;
    D_002BC090 = 0x100;
    D_002BC094 = 0xC0;
    D_002BC098 = 0.04f;
    D_002BC09C = 0x10;
    D_002BC0A0 = 0;
    D_002BC0A4 = 0;
}
