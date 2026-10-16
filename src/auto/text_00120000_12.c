/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00116660(void *);
M2C_UNK func_001166e8(void *);
M2C_UNK func_00121fc4(M2C_UNK *, s32);
M2C_UNK func_00267560(M2C_UNK *, M2C_UNK *, f32);
void func_002675a8(void *, M2C_UNK *);

void func_0012af88(void *arg0) {
  s32 sp[36];
  f32 temp_f0;
  f32 temp_f0_2;
  func_00116660(sp);
  temp_f0 = *((f32 *) (((s8 *) arg0) + 8));
  *((f32 *) (((s8 *) sp) + 0x24)) = temp_f0;
  *((f32 *) (((s8 *) sp) + 0x20)) = temp_f0;
  func_002675a8(sp, *((M2C_UNK **) (((s8 *) arg0) + 0)));
  *((f32 *) (((s8 *) sp) + 0xC)) = 1.0f;
  func_00121fc4(&(*((M2C_UNK *) (((s8 *) sp) + 0x80))), *((s32 *) (((s8 *) arg0) + 4)));
  do
  {
    temp_f0_2 = *((f32 *) (((s8 *) arg0) + 8));
    if (temp_f0_2 < (*((f32 *) (((s8 *) sp) + 0x8C))))
    {
      func_00267560(&(*((M2C_UNK *) (((s8 *) sp) + 0x10))), &(*((M2C_UNK *) (((s8 *) sp) + 0x80))), temp_f0_2);
      *((f32 *) (((s8 *) sp) + 0x8C)) -= *((f32 *) (((s8 *) arg0) + 8));
    }
    else
    {
      func_00267560(&(*((M2C_UNK *) (((s8 *) sp) + 0x10))), &(*((M2C_UNK *) (((s8 *) sp) + 0x80))), *((f32 *) (((s8 *) sp) + 0x8C)));
      *((f32 *) (((s8 *) sp) + 0x8C)) = 0.0f;
    }
    *((f32 *) (((s8 *) sp) + 0x1C)) = 1.0f;
    *((s32 *) (((s8 *) sp) + 0x28)) = 1;
    func_001166e8(sp);
    func_002675a8(sp, &(*((M2C_UNK *) (((s8 *) sp) + 0x40))));
  }
  while ((*((f32 *) (((s8 *) sp) + 0x8C))) > 0.0f);
  func_002675a8(*((void **) (((s8 *) arg0) + 0xC)), &(*((M2C_UNK *) (((s8 *) sp) + 0x40))));
  *((M2C_UNK **) (((s8 *) arg0) + 0)) = (M2C_UNK *) ((*((M2C_UNK *) (((s8 *) sp) + 0x30))) & 1);
}
