/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0054.h"
#include "data/pieces/D_00304C70.h"
extern s32 D_002C5958;
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00350CE0.h"
s32 func_00130340(s32, s32, f32);
s32 func_00130398(s32, s32, f32);
s32 func_00130578(s32, s32, f32);
s32 func_0014f658(s32, s32);
void func_0011d1e0(s32, s32, s32, s32);
void func_00141ab8(s32);

void func_0014cc38(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x3B0) = 0;
    M2C_FIELD(arg0, s32 *, 0x3D0) = 0;
    M2C_FIELD(arg0, f32 *, 0x3B4) = (f32) M2C_FIELD(arg0, f32 *, 0x14);
    func_0014f658(arg0, 2);
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xFFFEFFFF);
}

void func_0014cd38(s32 arg0) {
    s32 temp_v0;

    if (!(M2C_FIELD(arg0, f32 *, 0x3B8) <= (M2C_FIELD(arg0, f32 *, 0x3B0) + 6.0f))) {
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 0x178) != 0) {
        return;
    }
    temp_v0 = M2C_FIELD(arg0, s32 *, 0x3D0);
    if (M2C_FIELD(arg0, s32 *, 0x164) != (temp_v0 + 4)) {
        return;
    }
    func_00130340(arg0, temp_v0 + 5, 6.0f);
    func_00130578(arg0, M2C_FIELD(arg0, s32 *, 0x3D0) + 6, 0.0f);
}

void func_0014dcd8(Actor *arg0) {
    if (arg0->unk3D4 > 100.0f) {
        func_00130398(arg0, 0x75, 8.0f);
        func_0014f658(arg0, 8);
        arg0->unk3C4 = (f32) (arg0->unk3C4 * 0.3f);
        M2C_FIELD(arg0, s32 *, 0x3B0) = 0;
    }
}

void func_0014f398(s32 arg0) {
    func_00141ab8(M2C_FIELD(arg0, s32 *, 0x6C));
    M2C_FIELD(arg0, s32 *, 0x6C) = (s32) &D_00304C70;
}
#include "data/data_0030.h"
