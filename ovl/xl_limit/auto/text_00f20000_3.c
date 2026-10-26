/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_00F23E08;
extern s32 D_00F23E10;
s32 func_0012cab8(s32);
s32 func_00f20208(void);
void func_00131500(s32);
void func_00148068(s32, f32);

s32 func_00f211b0(s32 arg0) {
    func_0012cab8(0);
    func_00131500(arg0);
    *(M2C_UNK *)arg0 = (s32) (*(M2C_UNK *)arg0 & 0xFEDFFF7F);
    func_00148068(D_00F23E08, 8.0f);
    return func_00f20208();
}

s32 func_00f21620(s32 arg0) {
    func_00131500(arg0);
    func_0012cab8(0);
    *(M2C_UNK *)arg0 = (s32) (*(M2C_UNK *)arg0 & 0xFEDFFF7F);
    func_00148068(D_00F23E10, 3e+01f);
    return func_00f20208();
}
