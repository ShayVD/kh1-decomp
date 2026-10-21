/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_002672f8(s32, M2C_UNK *, s32);
M2C_UNK func_00267328(s32, M2C_UNK *, s32);
M2C_UNK func_00267560(s32, s32, f32);
M2C_UNK func_002675b8(s32, s32);
#include "data/pieces/D_003701F0.h"
extern M2C_UNK D_00615FC0;
extern M2C_UNK D_00616040; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
extern s32 D_00615E68;

void pppKeDMatFrFrame(s32 arg0, s32 arg1, void *arg2) {
  s32 temp_a0;
  int new_var;
  s32 temp_s2;
  temp_s2 = arg0 + (*((s32 *) (((s8 *) (*((void **) (((s8 *) arg2) + 0xC)))) + 4)));
  func_00267560(D_00615E68 + 0x50, D_00615E68 + 0x10, *((f32 *) (((s8 *) &D_003701F0) + 0)));
  func_00267560(D_00615E68 + 0x60, D_00615E68 + 0x20, *((f32 *) (((s8 *) &D_003701F0) + 4)));
  func_00267560(D_00615E68 + 0x70, D_00615E68 + 0x30, *((f32 *) (((s8 *) &D_003701F0) + 8)));
  new_var = temp_s2 + 0xA0;
  func_002672f8(D_00615E68 + 0x80, &D_00615FC0, D_00615E68 + 0x40);
  func_002675b8(new_var, D_00615E68 + 0x50);
  temp_a0 = D_00615E68 + 0x50;
  func_00267328(temp_a0, &D_00616040, temp_a0);
}
