/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00106cd0(void *, s32);
void *func_00106ca8(s32);
void func_001090e8(s32, s32, s32, s32);
void func_00109180(s32, s32);

void func_001091f8(s32 arg0, s32 arg1) {
    func_001090e8(arg0, 0x80, 0xE0, 0x3600);
    func_00109180(arg1, 0x3A00);
}

void func_00109230(s32 arg0, s32 arg1) {
    func_001090e8(arg0, 0x80, 0x30, 0x3A00);
    func_00109180(arg1, 0x3C00);
}

void func_0010c540(s32 arg0, void **arg1) {
    s32 temp_s1;
    void *temp_v0;

    temp_s1 = (arg0 * 3) + 1;
    temp_v0 = func_00106ca8(temp_s1);
    M2C_FIELD(temp_v0, s64 *, 8) = 0x535316;
    M2C_FIELD(temp_v0, s64 *, 0) = (s64) (arg0 | 0x8000 | ((s64) 0xC800 << 0x2F));
    func_00106cd0(temp_v0, temp_s1);
    *arg1 = temp_v0 + 0x10;
}
