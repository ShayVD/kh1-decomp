/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00121fc4(M2C_UNK *, M2C_UNK *);
M2C_UNK func_00267370(M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK func_00267518(M2C_UNK *, M2C_UNK *, s32);
M2C_UNK func_00267560(s32, M2C_UNK *, f32);
M2C_UNK func_00267e90(M2C_UNK *, M2C_UNK *, f32);
extern f32 D_002BBDFC;
void func_002673b8(M2C_UNK *, M2C_UNK *);

void func_0015def8(void *arg0, s32 arg1) {
  s32 sp[8];
  M2C_UNK *temp_s1;
  f32 var_f12;
  temp_s1 = arg0 + 0xC0;
  func_00267370(sp, temp_s1, arg0 + 0x20);
  func_002673b8(sp, sp);
  func_00267370(&(*((M2C_UNK *) (((s8 *) sp) + 0x10))), sp, temp_s1);
  func_002673b8(&(*((M2C_UNK *) (((s8 *) sp) + 0x10))), &(*((M2C_UNK *) (((s8 *) sp) + 0x10))));
  func_00267e90(&(*((M2C_UNK *) (((s8 *) sp) + 0x10))), &(*((M2C_UNK *) (((s8 *) sp) + 0x10))), D_002BBDFC * 0.5f);
  func_00267518(&(*((M2C_UNK *) (((s8 *) sp) + 0x10))), &(*((M2C_UNK *) (((s8 *) sp) + 0x10))), (*((s32 *) (((s8 *) arg0) + 0x148))) + 0x110);
  func_00121fc4(&(*((M2C_UNK *) (((s8 *) sp) + 0x10))), &(*((M2C_UNK *) (((s8 *) sp) + 0x10))));
  var_f12 = *((f32 *) (((s8 *) sp) + 0x1C));
  if (var_f12 > 16.0f)
  {
    var_f12 = 16.0f;
    *((f32 *) (((s8 *) sp) + 0x1C)) = 16.0f;
  }
  func_00267560((*((s32 *) (((s8 *) arg0) + 0x148))) + 0x110, &(*((M2C_UNK *) (((s8 *) sp) + 0x10))), var_f12);
  func_00267560(arg1, (*((s32 *) (((s8 *) arg0) + 0x148))) + 0x110, D_002BBDFC);
}
#include "data/pieces/D_002BBDFC.h"
