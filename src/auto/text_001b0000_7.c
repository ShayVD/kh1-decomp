/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001ba930(M2C_UNK, M2C_UNK);
extern M2C_UNK D_00009B40;
extern M2C_UNK D_00009B44;
extern M2C_UNK D_00009B48;
extern M2C_UNK D_00009B4C;
extern M2C_UNK D_00009B50;
extern M2C_UNK D_00009B54;
extern M2C_UNK D_00009B58;
extern M2C_UNK D_00009B5C;
extern M2C_UNK D_00009B60;
s32 func_00232cc0(M2C_UNK);
void *func_001ba9a8();

void func_001b9cb0(void) {
    s32 temp_v0;

    temp_v0 = func_00232cc0(4);
    if (*(M2C_UNK *)((s8 *)&D_00009B40 + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B40 + temp_v0) = 0x4000;
    }
    if (*(M2C_UNK *)((s8 *)&D_00009B44 + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B44 + temp_v0) = 0x8000;
    }
    if (*(M2C_UNK *)((s8 *)&D_00009B48 + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B48 + temp_v0) = 0x400;
    }
    if (*(M2C_UNK *)((s8 *)&D_00009B4C + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B4C + temp_v0) = 0x2000;
    }
    if (*(M2C_UNK *)((s8 *)&D_00009B50 + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B50 + temp_v0) = 0x2000;
    }
    if (*(M2C_UNK *)((s8 *)&D_00009B54 + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B54 + temp_v0) = 0x2000;
    }
    if (*(M2C_UNK *)((s8 *)&D_00009B58 + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B58 + temp_v0) = 0x1000;
    }
    if (*(M2C_UNK *)((s8 *)&D_00009B5C + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B5C + temp_v0) = 0x1000;
    }
    if (*(M2C_UNK *)((s8 *)&D_00009B60 + temp_v0) == 0) {
        *(M2C_UNK *)((s8 *)&D_00009B60 + temp_v0) = 0x1000;
    }
}

void func_001babe8(void) {
    void *temp_v0;

    temp_v0 = func_001ba9a8();
    M2C_FIELD(temp_v0, u8 *, 0x31) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x31) + 1);
    func_001ba930(0, 4);
    func_001ba930(1, 4);
    func_001ba930(2, 4);
    func_001ba930(3, 4);
    func_001ba930(4, 4);
    func_001ba930(5, 4);
    func_001ba930(6, 4);
    func_001ba930(7, 4);
    func_001ba930(8, 4);
    func_001ba930(9, 4);
    func_001ba930(0xA, 3);
    func_001ba930(0xB, 2);
    func_001ba930(0xC, 4);
    func_001ba930(0xD, 4);
    func_001ba930(0xE, 4);
    func_001ba930(0xF, 0x1F);
    func_001ba930(0x10, 0x1F);
    func_001ba930(0x11, 0x1F);
    func_001ba930(0x12, 0x1F);
    func_001ba930(0x13, 0x1F);
    func_001ba930(0x14, 0x1F);
    func_001ba930(0x15, 0x1F);
    func_001ba930(0x16, 0x1F);
    func_001ba930(0x17, 0x1F);
    func_001ba930(0x18, 0x1F);
    func_001ba930(0x22, -1);
    func_001ba930(0x23, -1);
    func_001ba930(0x24, -1);
    func_001ba930(0x25, -1);
    func_001ba930(0x26, -1);
}
