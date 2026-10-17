/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_002E26A0;

s32 func_001d44b8(s32 arg0) {
  s32 *new_var;
  void *temp_v0;
  void *temp_v1;
  temp_v0 = ((*((s32 *) (((s8 *) arg0) + 0x180))) * 4) + arg0;
  new_var = (s32 *) (((s8 *) temp_v0) + 0x184);
  temp_v1 = *((M2C_UNK *) (((s8 *) ((s8 *) (&D_002E26A0))) + ((*new_var) * 4)));
  if (temp_v1 != 0)
  {
    *new_var = (s32) (*((f32 *) (((s8 *) temp_v1) + 0x10)));
  }
  return 2;
}
