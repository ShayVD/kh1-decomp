/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001047c8();
M2C_UNK func_001195d8(s32, void *);
s32 func_001191c8(void *, s32, M2C_UNK);
s32 func_0011c338(void *, s32, s32, M2C_UNK *, M2C_UNK, M2C_UNK *);
void func_00104528();

s32 func_00119688(s32 arg0) {
  M2C_UNK *new_var;
  s32 sp[16];
  s32 temp_s0;
  s32 temp_s1;
  s32 var_v0;
  func_001047c8();
  func_001195d8(arg0, sp);
  new_var = &(*((M2C_UNK *) (((s8 *) sp) + 0x30)));
  temp_s1 = func_0011c338(sp, arg0, arg0 + 0x10, &(*((M2C_UNK *) (((s8 *) sp) + 0x20))), -1, new_var);
  temp_s0 = func_001191c8(sp, arg0, 8);
  func_00104528();
  var_v0 = -1;
  if (!((temp_s1 != (-1)) || (temp_s0 != temp_s1)))
  {
    return var_v0;
  }
  ;
  return 1;
}
