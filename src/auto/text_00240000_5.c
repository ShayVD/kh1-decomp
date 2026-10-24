/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_00248788(s32 *);
M2C_UNK func_0024aac8(M2C_UNK *);
M2C_UNK func_0024af40(M2C_UNK *, void *, M2C_UNK *);
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_0045D6E0;
extern M2C_UNK D_0045E190;
extern M2C_UNK D_0045E198;
extern M2C_UNK D_0045E1A0;
extern M2C_UNK D_0045E1A8;
extern M2C_UNK D_0045E1B8;
extern M2C_UNK D_0045E1C0;
extern M2C_UNK D_0045E1C8;
extern M2C_UNK D_0045E1E0;
extern M2C_UNK D_00668370; /* src/data/bss_0066.c: s32 D_00668370[0x2ac] */
extern M2C_UNK func_00246aa8;
extern s32 D_00669700;
s32 func_0011ef38(M2C_UNK *);

void func_00246bc8(void) {
    memset(&D_00668370, 0, 0xAB0);
    func_0024aac8(&D_0045D6E0);
    func_0024af40(&D_0045E190, (s8 *)&D_00668370 + 0x20, &D_0045D6E0);
    func_0024af40(&D_0045E198, (s8 *)&D_00668370 + 0xE0, &D_0045D6E0);
    func_0024af40(&D_0045E1A0, (s8 *)&D_00668370 + 0x1A0, &D_0045D6E0);
    func_0024af40(&D_0045E1A8, (s8 *)&D_00668370 + 0x260, &D_0045D6E0);
    func_0024af40(&D_0045E1B8, (s8 *)&D_00668370 + 0x4A0, &D_0045D6E0);
    func_0024af40(&D_0045E1C0, (s8 *)&D_00668370 + 0x560, &D_0045D6E0);
    func_0024af40(&D_0045E1C8, (s8 *)&D_00668370 + 0x620, &D_0045D6E0);
    func_0024af40(&D_0045E1E0, (s8 *)&D_00668370 + 0x9E0, &D_0045D6E0);
    if (func_0011ef38(&func_00246aa8) == 0) {
        func_0011ef10(0x28489, &func_00246aa8);
    }
}

void func_00248b00(void) {
    D_00669700 = 0;
    func_00248788((s8 *)&D_00669700 + 0x14);
}

void func_0024b058(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_a4;

    temp_a1 = (arg1 * 0x10) + 0x7000;
    temp_a2 = (arg2 * 0x10) + 0x7400;
    temp_a4 = ((arg2 + arg4) * 0x10) + 0x7400;
    temp_a3 = ((arg1 + arg3) * 0x10) + 0x7000;
    M2C_FIELD(arg0, s32 *, 0xA0) = temp_a1;
    M2C_FIELD(arg0, s32 *, 0xA4) = temp_a2;
    M2C_FIELD(arg0, s32 *, 0xA8) = -0x100;
    M2C_FIELD(arg0, s32 *, 0xAC) = 0;
    M2C_FIELD(arg0, s32 *, 0xB0) = temp_a1;
    M2C_FIELD(arg0, s32 *, 0xB4) = temp_a4;
    M2C_FIELD(arg0, s32 *, 0xB8) = -0x100;
    M2C_FIELD(arg0, s32 *, 0xBC) = 0;
    M2C_FIELD(arg0, s32 *, 0xC0) = temp_a3;
    M2C_FIELD(arg0, s32 *, 0xC4) = temp_a2;
    M2C_FIELD(arg0, s32 *, 0xC8) = -0x100;
    M2C_FIELD(arg0, s32 *, 0xCC) = 0;
    M2C_FIELD(arg0, s32 *, 0xD0) = temp_a3;
    M2C_FIELD(arg0, s32 *, 0xD4) = temp_a4;
    M2C_FIELD(arg0, s32 *, 0xD8) = -0x100;
    M2C_FIELD(arg0, s32 *, 0xDC) = 0;
}
#include "data/data_0045.h"
