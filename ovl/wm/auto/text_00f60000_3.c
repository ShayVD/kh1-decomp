/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_00F9B518;
extern s32 D_00F9B544;
extern void *D_00F9B540;
s32 func_001bb678();
void func_00f47f40();
void func_00f4b338(s32, M2C_UNK);
void func_00f4b878(s32);
void func_00f4c728();
void func_00f55330(M2C_UNK);
void func_00f55378(M2C_UNK);
void func_00f59870(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
void func_00f5a478(M2C_UNK);
void func_00f601f0(s32);

void func_00f60448(s32 arg0) {
    f32 unused_frame[4][4] __attribute__((aligned(16)));
    u16 temp_s0;

    func_00f5a478(0);
    func_00f55330(0);
    func_00f55378(0);
    func_00f59870(-1, 0x23, 0x23, 0x41, 0);
    func_00f59870(2, 0x80, 0x80, 0x80, 0x80);
    func_00f59870(0, 0x80, 0x80, 0x80, 0x80);
    func_00f59870(5, 0x80, 0x80, 0x80, 0);
    D_00F9B518 = 1;
    func_00f601f0(arg0);
    func_00f4b878(D_00F9B544);
    func_00f4b338(D_00F9B544, 0);
    func_00f4c728();
    temp_s0 = M2C_FIELD(D_00F9B540, u16 *, 0xA6);
    if (temp_s0 != func_001bb678()) {
        func_00f47f40();
    }
    D_00F9B518 = 0;
}
