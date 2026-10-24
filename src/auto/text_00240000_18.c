/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

void func_0024b008(s32 arg0, s32 *arg1) {
  s32 *var_a2;
  s32 *var_v1;
  s32 temp_v0;
  s32 var_a0;
  s32 var_a3;
  s32 var_a4;
  var_a0 = arg0;
  var_a4 = 0;
  do
  {
 do { var_a2 = var_a0 + 0x20; var_v1 = arg1; var_a3 = 3; loop_2: temp_v0 = *var_v1; var_v1 += 1; var_a3 -= 1; *var_a2 = temp_v0; var_a2 += 1; if (var_a3 >= 0) { goto loop_2; } } while (0);
    var_a4 += 1;
    var_a0 += 0x10;
  }
  while (var_a4 < 4);
}
