/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

s32 func_001ba3d8();
s32 func_001ba3f0(s32);

s32 func_001eeb20(void) {
  s32 temp_a0;
  s32 temp_v0;
  s32 var_s0;
  s32 var_s2;
  s32 var_v0;
  var_s0 = 0;
  var_s2 = 0;
  temp_v0 = func_001ba3d8();
  var_v0 = 0;
  if (temp_v0 > 0)
  {
    do
    {
      temp_a0 = var_s0;
      var_s0 += 1;
      var_s2 += func_001ba3f0(temp_a0);
    }
    while (var_s0 < temp_v0);
    var_v0 = var_s2;
  }
  return var_s2;
}

s32 func_001efc68(s32 arg0, s32 arg1, s32 arg2) {
  int new_var;
  new_var = arg0 + (arg2 * 2);
  return arg1 + (*((u16 *) (((s8 *) new_var) + (-2))));
}
