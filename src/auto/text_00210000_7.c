/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
M2C_UNK func_0021af38(s32);
M2C_UNK func_0021b820();
M2C_UNK func_0021ccd0(s32, M2C_UNK);
extern M2C_UNK D_003F47B8;
extern M2C_UNK D_003F4BD0;
extern s32 D_00642D24;
#include "data/pieces/D_003F34B8.h"
void func_001f9010(s32);
void func_001f9438(s32, s32, s32, s32, s32, s32, s32);

void func_002192e8(s32 arg0) {
    M2C_FIELD(D_003F34B8, s32 *, 4) = arg0;
}

void func_00219478(s32 arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, *(M2C_UNK *)((s8 *)(s8 *)&D_003F47B8 + (M2C_FIELD(arg0, s32 *, 0x24) * 4)), 0x11, 0x80C87850);
}

void func_00219f38(s32 arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, *(M2C_UNK *)((s8 *)(s8 *)&D_003F4BD0 + (D_00642D24 * 4)), 0x11, 0x80C87850);
}

void func_0021f7d8(s32 arg0) {
    func_0021b820();
    func_0021ccd0(arg0, 1);
    func_0021af38(arg0);
}
#include "data/bss_0064_mixed.h"
#include "data/data_003F.h"
