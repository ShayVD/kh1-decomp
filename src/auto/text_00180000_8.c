/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00267328(void *, M2C_UNK *, void *);
M2C_UNK func_00267548(void *, void *, M2C_UNK *);
M2C_UNK func_00267560(void *, void *, f32);
#include "data/pieces/D_003701F0.h"
extern M2C_UNK D_00616040; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
extern f32 D_00615FC0[];
extern void *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */

void pppDrawMatrixNoRotFrame(void) {
    void *temp_a0;

    func_00267560(D_00615E68 + 0x50, D_00615E68 + 0x10, M2C_FIELD((M2C_UNK *)&D_003701F0, f32 *, 0));
    func_00267560(D_00615E68 + 0x60, D_00615E68 + 0x20, M2C_FIELD((M2C_UNK *)&D_003701F0, f32 *, 4));
    func_00267560(D_00615E68 + 0x70, D_00615E68 + 0x30, M2C_FIELD((M2C_UNK *)&D_003701F0, f32 *, 8));
    func_00267548(D_00615E68 + 0x80, D_00615E68 + 0x40, (M2C_UNK *)&D_003701F0);
    M2C_FIELD(D_00615E68, f32 *, 0x80) = (f32) (M2C_FIELD(D_00615E68, f32 *, 0x80) + D_00615FC0[12]);
    M2C_FIELD(D_00615E68, f32 *, 0x84) = (f32) (M2C_FIELD(D_00615E68, f32 *, 0x84) + D_00615FC0[13]);
    M2C_FIELD(D_00615E68, f32 *, 0x88) = (f32) (M2C_FIELD(D_00615E68, f32 *, 0x88) + D_00615FC0[14]);
    M2C_FIELD(D_00615E68, f32 *, 0x8C) = 1.0f;
    temp_a0 = D_00615E68 + 0x50;
    func_00267328(temp_a0, &D_00616040, temp_a0);
}
