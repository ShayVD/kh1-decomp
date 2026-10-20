/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001aab98(void *, void *);
M2C_UNK func_002672f8(s32, void *, s32);
M2C_UNK func_00267328(void *, M2C_UNK *, void *);
M2C_UNK func_00267560(s32, s32, f32);
M2C_UNK func_002675b8(void *, s32);
M2C_UNK func_00267620(void *);
extern M2C_UNK D_00615EB0; /* src/data/bss_0061.c: u8 D_00615EB0[0x40] */
extern M2C_UNK D_00616040; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
extern s32 D_00615E68;

void pppRyjDrawMatrixWorldDttFrFrame(s32 arg0, s32 arg1, void *arg2) {
    s32 sp[16];    void *temp_a0;
    void *temp_s1;

    temp_s1 = arg0 + M2C_FIELD(M2C_FIELD(arg2, void **, 0xC), s32 *, 4) + 0xA0;
    func_00267620(sp);
    M2C_FIELD(sp, f32 *, 0x30) = M2C_FIELD(temp_s1, f32 *, 0x40);
    M2C_FIELD(sp, f32 *, 0x34) = M2C_FIELD(temp_s1, f32 *, 0x44);
    M2C_FIELD(sp, f32 *, 0x38) = M2C_FIELD(temp_s1, f32 *, 0x48);
    func_00267328(sp, &D_00615EB0, sp);
    func_00267560(D_00615E68 + 0x50, D_00615E68 + 0x10, M2C_FIELD(temp_s1, f32 *, 0x50));
    func_00267560(D_00615E68 + 0x60, D_00615E68 + 0x20, M2C_FIELD(temp_s1, f32 *, 0x54));
    func_00267560(D_00615E68 + 0x70, D_00615E68 + 0x30, M2C_FIELD(temp_s1, f32 *, 0x58));
    func_002672f8(D_00615E68 + 0x80, sp, D_00615E68 + 0x40);
    func_002675b8(temp_s1, D_00615E68 + 0x50);
    temp_a0 = D_00615E68 + 0x50;
    func_00267328(temp_a0, &D_00616040, temp_a0);
}

void func_001aadd0(s32 arg0) {
    void *temp_a0;

    temp_a0 = arg0 + 0x10;
    func_001aab98(temp_a0, temp_a0 + M2C_FIELD(temp_a0, s32 *, 0x3C));
}
