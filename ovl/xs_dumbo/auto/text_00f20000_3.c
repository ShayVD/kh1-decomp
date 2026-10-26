/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern f32 D_00F3CA84;
extern f32 D_00F3CA8C;
extern s32 D_00F23204;
extern s32 D_00F23208;
extern s32 D_00F2320C;
extern s32 D_00F3CA88;
s32 func_00131b08(s32);
s32 func_00f20238();
u32 func_00148768(s32, s32, s32, s32, f32);
void func_00f200b0(M2C_UNK, f32);
void func_00f20150(M2C_UNK);
void func_00f203a0();

void func_00f20408(void) {
    if (func_00131b08(D_00F23204) != 0) {
        func_00f200b0(0xC9, 0);
        D_00F3CA84 = 1.2e+02f;
        D_00F2320C = func_00f20238();
        func_00f203a0();
        func_00f20150(2);
    }
}

void func_00f209d0(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0) = (s32) ((M2C_FIELD(arg0, s32 *, 0) | 0x03000080) & ~2);
    D_00F3CA88 = func_00148768(D_00F23208, 6, arg0, 0x8003, 0.0f);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), f32 *, 0xCC) = 0.1308997f;
    D_00F3CA8C = 5e+01f;
}
