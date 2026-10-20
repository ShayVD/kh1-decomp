/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001f31a8(M2C_UNK *, M2C_UNK);
M2C_UNK func_0021af38(s32);
M2C_UNK func_0021b820();
M2C_UNK func_0021ccd0(s32, M2C_UNK);
extern M2C_UNK D_003F3B40;
extern M2C_UNK D_003F3E18;
extern M2C_UNK D_003F4488;
extern M2C_UNK D_003F47B8;
extern M2C_UNK D_003F4BD0;
extern s32 D_00304BE8;
extern s32 D_003E8E08;
extern s32 D_003F34C0;
extern s32 D_00641BC4;
extern s32 D_00642C70;
extern s32 D_00642CD0;
extern s32 D_00642D24;
extern u32 D_003E3D68;
extern u32 D_00642C58;
extern void *D_003F34B8;
s32 func_001ee5f0(s32);
void func_001f9010(s32);
void func_001f9438(s32, s32, s32, s32, s32, s32, s32);

void func_00212270(void) {
    if (D_00641BC4 != 3) {
        func_001f31a8(&D_003F3B40, 0);
        D_003F34C0 |= 2;
    }
}

void func_00214380(s32 arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, *(M2C_UNK *)((s8 *)(s8 *)&D_003F3E18 + (D_00642C70 * 4)), 0x11, 0x80C87850);
}

void func_00215388(s32 arg0) {
    s32 var_s0;

    func_001f9010(0x17);
    var_s0 = 0xBD;
    if (D_00642C58 != 0) {
        var_s0 = 0xBF;
        if ((u32) D_00642C58 < (u32) D_003E3D68) {
            var_s0 = 0xBE;
            D_003E8E08 = func_001ee5f0((s32) M2C_FIELD((D_00642C58 + D_00304BE8), u8 *, 0x48E));
        }
    }
    func_001f9438(arg0, 0, 0xAE, 0xC, var_s0, 0x11, 0x80C87850);
}

void func_002165e0(s32 arg0) {
    func_001f9010(0x17);
    func_001f9438(arg0, 0, 0xAE, 0xC, *(M2C_UNK *)((s8 *)(s8 *)&D_003F4488 + (D_00642CD0 * 4)), 0x11, 0x80C87850);
}

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
