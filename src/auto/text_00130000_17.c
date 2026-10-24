/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0052.h"
#include "data/pieces/D_002C58A0.h"
M2C_UNK D_0052A158[0x240] ALIGNED(8);
f32 func_0014cce0(s32, f32);
s32 func_00130340(s32, s32, f32);
s32 func_0014f600(s32);
s32 func_002675a8(s32, s32);

s32 func_0013f108(s32 arg0) {
  s8 *new_var;
  s32 temp_v0;
  new_var = (s8 *) arg0;
  temp_v0 = *((s32 *) (0x398 + new_var));
  if (temp_v0 != 0)
  {
    if (func_0014f600(temp_v0) != 0)
    {
      if ((*((s32 *) (new_var + 0x70))) == 0)
      {
        func_0014cce0(arg0, 1e+01f);
        func_002675a8(arg0 + 0x3C0, (s32) (&D_002C58A0));
        func_00130340(arg0, 0x10006, 8.0f);
        return 1;
        goto block_4;
      }
    }
    return 0;
  }
  block_4:
  return 0;

}
