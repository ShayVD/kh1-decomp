/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

#include "data/pieces/D_002E26A0.h"

s32 func_001d4538(s32 arg0) {
  int new_var;
  s8 *new_var2;
  void *temp_v0;
  void *temp_v1;
  new_var = (*((s32 *) (((s8 *) arg0) + 0x180))) * 4;
  temp_v0 = new_var + arg0;
  new_var2 = ((s8 *) temp_v0) + 0x184;
  temp_v1 = *((M2C_UNK *) (((s8 *) ((s8 *) (&D_002E26A0))) + ((*((s32 *) new_var2)) * 4)));
  if (temp_v1 != 0)
  {
    *((s32 *) (((s8 *) (((*((s32 *) (((s8 *) arg0) + 0x180))) * 4) + arg0)) + 0x184)) = (s32) (*((f32 *) (((s8 *) temp_v1) + 0x18)));
  }
  return 2;
}
