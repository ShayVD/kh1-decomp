/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00123a88(s32, void *);
M2C_UNK func_00137688(void *, f32);
M2C_UNK func_00267530(s32, s32, s32);
M2C_UNK func_002675a8(s32, s32);
extern s32 D_0035BD40;
extern volatile unsigned char D_00575020;
f32 func_001376e8(void *, s32);
f32 func_00162c20(s32);

void func_00168530(void *arg0) {
  s32 *var_v0;
  s32 *var_v1;
  s32 temp_s0;
  s32 temp_s2;
  s32 var_a0;
  void *temp_s3;
  temp_s3 = *((void **) (((s8 *) arg0) + 0x144));
  temp_s0 = temp_s3 + 0xE0;
  temp_s2 = temp_s3 + 0xF0;
  func_00267530(temp_s0, D_0035BD40 + 0x10, arg0 + 0x10);
  func_002675a8(temp_s2, temp_s3 + 0xE0);
  *((s32 *) (((s8 *) temp_s3) + 0xF4)) = 0;
  *((f32 *) (((s8 *) temp_s3) + 0xEC)) = func_00162c20(temp_s3 + 0xE0);
  *((f32 *) (((s8 *) temp_s3) + 0xFC)) = func_00162c20(temp_s2);
  func_00123a88(*((s32 *) (((s8 *) arg0) + 4)), (&D_00575020) + ((*((s32 *) (((s8 *) temp_s3) + 0))) * 0x10));
  func_00137688(arg0, func_001376e8(arg0, temp_s2));
  var_a0 = 4;
  var_v1 = temp_s3 + 0x154;
  var_v0 = temp_s3 + 0x140;
  do
  {
    var_a0 -= 1;
    *var_v0 = 0;
    *var_v1 = 0;
    var_v1 -= 1;
    var_v0 -= 1;
  }
  while (var_a0 > 0);
  *((s32 *) (((s8 *) temp_s3) + 0x58)) = 0;
}
